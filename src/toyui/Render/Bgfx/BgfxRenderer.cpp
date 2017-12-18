//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toygfx/Config.h>
#include <toygfx/GfxSystem.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/Image.h>

#include <toyui/UiWindow.h>
#include <toyui/Render/Renderer.h>

#include <toygfx/GfxViewport.h>
#include <toygfx/GfxScene.h>
#include <toygfx/GfxItem.h>
#include <toygfx/GfxCamera.h>
#include <toygfx/GfxMaterial.h>
#include <toygfx/GfxParticle.h>
#include <toygfx/GfxMaterial.h>
#include <toygfx/GfxMesh.h>
#include <toygfx/GfxDraw.h>

#include <toygfx/Import/ImporterObj.h>
#include <toygfx/Import/ImporterGltf.h>

#include <toygfx/Render/GfxPipeline.h>

#include <toymath/Stream.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <bx/timer.h>

#include <nanovg_bgfx.h>

#define NANOVG_NULL_IMPLEMENTATION
#include <nanovg_null.h>

#include <fstream>

#define TOY_COMPILE_BGFX_SHADERS

#include <toyui/UiLayout.h>

namespace bgfx
{
	int compileShader(int _argc, const char* _argv[]);
	void getShaderError(char* _outputText, uint16_t& _outputSize);
}

namespace toy
{
	GfxContext::GfxContext(GfxSystem& renderSystem, const string& name, int width, int height, bool fullScreen)
#if TOY_PLATFORM_EMSCRIPTEN
		: EmContext(renderSystem, name, width, height, fullScreen)
#elif TOY_CONTEXT_WINDOWS
		: WinContext(renderSystem, name, width, height, fullScreen)
#else
		: GlfwContext(renderSystem, name, width, height, fullScreen, false)
#endif
		, m_target(nullptr)
	{}

	void GfxContext::init()
	{
		m_target = make_unique<GfxTarget>(as<GfxSystem>(m_renderSystem), m_renderWindow->m_width, m_renderWindow->m_height);
	}

	void GfxContext::addViewport(GfxViewport& viewport)
	{
		m_viewports.push_back(&viewport);
	}

	void GfxContext::render(uint32_t frame, float time, float time_offset)
	{
		for(GfxViewport* pviewport : m_viewports)
		{
			pviewport->cursor(m_inputWindow->m_cursorX, m_inputWindow->m_cursorY);
			pviewport->update();

			Render render(*pviewport, *m_target, frame, time, time_offset);
			pviewport->m_camera.update();
			pviewport->m_scene.render(render);
			//pviewport->m_picker.update(render, frame);
		}
	}

	GfxUiRenderer::GfxUiRenderer(const string& resourcePath)
		: NanoRenderer(resourcePath)
	{
		//m_null = true;
	}

	void GfxUiRenderer::setupContext()
	{
		if(m_null)
			m_ctx = nvgCreateNull();
		else
			m_ctx = nvgCreate(1, 255);

		if(m_ctx == nullptr)
		{
			printf("Could not init nanovg.\n");
			return;
		}
	}

	void GfxUiRenderer::releaseContext()
	{
		if(m_null)
			nvgDeleteNull(m_ctx);
		else
			nvgDelete(m_ctx);
		m_ctx = nullptr;
	}

	GfxSystem::GfxSystem(const string& resourcePath)
		: RenderSystem(resourcePath, true)
		, m_fileReader()
		, m_fileWriter()
		, m_frame(1)
	{
		printf("Gfx System\n");
	}

	GfxSystem::~GfxSystem()
	{}

	bool GfxSystem::init()
	{
		m_importerOBJ = make_unique<ImporterOBJ>(*this);
		m_importerGltf = make_unique<ImporterGltf>(*this);
		return true;
	}

	object_ptr<Context> GfxSystem::createContext(const string& name, int width, int height, bool fullScreen)
	{
		object_ptr<GfxContext> context = make_object<GfxContext>(*this, name, width, height, fullScreen);

		m_contexts.push_back(context.get());

		printf("GfxSystem: Native Handle = %p\n", context->m_renderWindow->m_nativeHandle);
		bgfx::PlatformData pd = {};
		pd.nwh = context->m_renderWindow->m_nativeHandle;
		pd.ndt = context->m_renderWindow->m_nativeTarget;
		bgfx::setPlatformData(pd);

		printf("GfxSystem: bgfx::init\n");
		bgfx::init(); // bgfx::RendererType::OpenGL

		bgfx::reset(width, height, BGFX_RESET_NONE);

		bgfx::setDebug(BGFX_DEBUG_TEXT);

		bgfx::setViewRect(0, 0, 0, width, height);
		bgfx::setViewRect(255, 0, 0, width, height);

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

		m_white_texture = make_object<GfxTexture>(*this, "white.png");
		m_black_texture = make_object<GfxTexture>(*this, "black.png");

		m_pipeline = make_unique<Pipeline>(*this);

		Pipeline& pipeline = static_cast<Pipeline&>(*m_pipeline);

		std::vector<GfxBlock*> unshaded_blocks = { &pipeline.m_depth };
		std::vector<GfxBlock*> pbr_blocks = { &pipeline.m_radiance, &pipeline.m_light, &pipeline.m_shadow, &pipeline.m_reflection, &pipeline.m_gi };

		m_programs["unshaded"] = make_unique<GfxProgram>(*this, "unshaded", unshaded_blocks);
		m_programs["pbr/scene"] = make_unique<GfxProgram>(*this, "pbr/scene", pbr_blocks);

		//m_default_material_overdraw.m_base_block.m_blend_mode = BLEND_MODE_ADD;
		//m_default_material_overdraw.m_unshaded = true; // void fragment() { ALBEDO=vec3(0.4,0.8,0.8); ALPHA=0.2; }

		const bgfx::Caps* caps = bgfx::getCaps();

		float depthScaleOffset[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
		if(caps->homogeneousDepth)
		{
			depthScaleOffset[0] = 0.5f;
			depthScaleOffset[1] = 0.5f;
		}
		//bgfx::setUniform(u_depthScaleOffset, depthScaleOffset);

		//state.max_skeleton_bones = MIN(2048, max_ubo_size / (12 * sizeof(float)));
		//state.scene_shader.add_custom_define("#define MAX_SKELETON_BONES " + itos(state.max_skeleton_bones) + "\n");

		for(GfxBlock* block : m_pipeline->m_gfx_blocks)
			block->init_gfx_block();

		m_timeOffset = bx::getHPCounter();

		context->init();

		this->createDebugMaterials();

		return std::move(context);
	}

	object_ptr<Renderer> GfxSystem::createRenderer(Context& context)
	{
		return make_object<GfxUiRenderer>(m_resourcePath);
	}

	bool GfxSystem::nextFrame()
	{
		bool pursue = true;
		bgfx::touch(0);

		for(auto& window : m_windows)
			pursue &= window->nextFrame();

		for(GfxContext* context : m_contexts)
			context->render(m_frame, m_time, m_timeOffset);

		m_frame = bgfx::frame();
		this->logFPS();

		return pursue;
	}

	string GfxSystem::compileShader(const string& shaderSource, const string& suffix, ShaderType shaderType, const string& defines)
	{
		string sourceSuffix = shaderType == VERTEX_SHADER ? "_vs.sc" : "_fs.sc";
		string sourcePath = m_resourcePath + "shaders/" + shaderSource + sourceSuffix;

		//bool isOpengl = true;
		bool isOpengl = false;
		//bool debug = true;
		bool debug = false;

		string outputSuffix = shaderType == VERTEX_SHADER ? "_vs" : "_fs";
		string outputPath = m_resourcePath + "shaders/compiled/" + shaderSource + suffix + outputSuffix;

		/*std::ifstream file(outputPath);
		if(file.good())
		{
		printf("Shader already compiled : %s\n", outputPath.c_str());
		return outputPath;
		}*/

		printf("Compiling Shader : %s\n", sourcePath.c_str());
		printf("Defines : %s\n", defines.c_str());

		string include = m_resourcePath + "shaders/";
		string varyingPath = m_resourcePath + "shaders/varying.def.sc";

#ifdef TOY_COMPILE_BGFX_SHADERS
		constexpr static size_t numArgs = 18;
#else
		constexpr static size_t numArgs = 16;
#endif
		const char* args[numArgs];
		args[0] = "-f";
		args[1] = sourcePath.c_str();
		args[2] = "-o";
		args[3] = outputPath.c_str();
		args[4] = "--depends";
		args[5] = "-i";
		args[6] = include.c_str();
		args[7] = "--varyingdef";
		args[8] = varyingPath.c_str();
		args[9] = "--platform";
		if(isOpengl)
		{
			args[10] = "linux";
			args[11] = "";
			args[12] = "";

			/*
			args[11] = "--profile";
			#if TOY_PLATFORM_EMSCRIPTEN
			args[12] = "100";
			#else
			args[12] = "140";
			args[12] = "150";
			args[12] = "410";
			#endif
			*/
		}
		else
		{
			args[10] = "windows";
			args[11] = "--profile";
			args[12] = shaderType == VERTEX_SHADER ? "vs_5_0" : "ps_5_0";
		}
		args[13] = "--type";
		args[14] = shaderType == VERTEX_SHADER ? "vertex" : "fragment";
		if(debug)
			args[15] = "--debug";
		else
			args[15] = "-O3";

#ifdef TOY_COMPILE_BGFX_SHADERS
		args[16] = "--define";
		args[17] = defines.c_str();

		int result = bgfx::compileShader(numArgs, args);

		if(result == EXIT_FAILURE)
		{
			char outputText[90000];
			uint16_t outputSize;
			bgfx::getShaderError(outputText, outputSize);

			printf("Failed to compile %s (%s), defines = \"%s\"\n", sourcePath.c_str(), outputPath.c_str(), defines.c_str());
			printf("%s", outputText);
			return "";
		}
#endif

		return outputPath;
	}

	GfxProgram& GfxSystem::getProgram(const string& program)
	{
		if(m_programs.find(program) == m_programs.end())
			m_programs[program] = make_unique<GfxProgram>(*this, program, std::vector<GfxBlock*>{});
		return *m_programs[program];
	}

	GfxTexture& GfxSystem::getTexture(const string& texture)
	{
		if(m_textures.find(texture) == m_textures.end())
			m_textures[texture] = make_unique<GfxTexture>(*this, texture);
		return *m_textures[texture];
	}

	GfxTexture& GfxSystem::loadTexture(const string& path, const string& texture)
	{
		if(m_textures.find(texture) == m_textures.end())
			m_textures[texture] = make_unique<GfxTexture>(*this, path, texture);
		return *m_textures[texture];
	}

	GfxTexture& GfxSystem::loadTextureMem(const string& texture, array<uint8_t> data)
	{
		// @todo
		return *m_textures[texture];
	}

	GfxTexture& GfxSystem::loadTextureRGBA(const string& texture, size_t width, size_t height, array<uint8_t> data)
	{
		if(m_textures.find(texture) == m_textures.end())
			m_textures[texture] = make_unique<GfxTexture>(*this, texture, width, height, data);
		return *m_textures[texture];
	}

	GfxTexture& GfxSystem::fetchImage256(const Image256& image)
	{
		string name = "Image256_" + toString((uintptr_t)&image);
		std::vector<uint8_t> data = image.read();
		return this->loadTextureRGBA(name, image.m_width, image.m_height, { data.data(), data.size() });
	}

	TiledModelConfig GfxSystem::loadTiledModelConfig(const string& name)
	{
		std::ifstream file = std::ifstream(m_resourcePath + "models/" + name + ".tiles");
		ModelConfig model_config = loadModelConfig(name);
		TiledModelConfig tile_model_config = { model_config.m_transform, Unit3, Zero3, {} };

		if(!file.good())
			return tile_model_config;

		for(std::string line; std::getline(file, line);)
		{
			std::istringstream stream(line);

			string command = read<string>(stream);
			if(command == "tile_size")
				tile_model_config.m_tile_size = read<vec3>(stream);
			else if(command == "tile_origin")
				tile_model_config.m_tile_origin = read<vec3>(stream);
			else if(command == "tile")
			{
				string name = read<string>(stream);
				vec3 coord = read<vec3>(stream);
				tile_model_config.m_tiles.push_back({ name, coord });
			}
		}

		return tile_model_config;
	}

	ModelConfig GfxSystem::loadModelConfig(const string& name)
	{
		std::ifstream file = std::ifstream(m_resourcePath + "models/" + name + ".cfg");
		ModelConfig model_config = { mtxIdentity() };

		vec3 scale = Unit3;
		vec3 position = Zero3;
		vec3 rotation = Zero3;
		//quat rotation = { 0.f, 0.f, 0.f, 1.f };

		if(!file.good())
			return model_config;

		for(std::string line; std::getline(file, line);)
		{
			std::istringstream stream(line);

			string command = read<string>(stream);
			if(command == "scale")
				scale = read<vec3>(stream);
			else if(command == "position")
				position = read<vec3>(stream);
			else if(command == "rotation")
				rotation = read<vec3>(stream);
			//else if(command == "rotation")
			//	rotation = read<quat>(stream);
		}

		model_config.m_transform = mtxSRT(scale, rotation, position);

		return model_config;
	}

	void GfxSystem::loadTiledModel(const string& path, const string& name)
	{
		string basepath = m_resourcePath + "models/";
		TiledModelConfig config = loadTiledModelConfig(path + name);

		// @todo implement a TileModel or Tileset
		for(ModelTile& tile : config.m_tiles)
		{
			object_ptr<GfxModel> model = make_object<GfxModel>(*this, tile.m_name, false);
			model->m_tile_index = tile.m_coord;
			m_importerOBJ->import_model(*model, basepath + path, tile.m_name, { config.m_transform }, 0);
			m_models.emplace_back(std::move(model));
		}
	}

	void GfxSystem::loadModel(GfxModel& model)
	{
		string path = m_resourcePath + "models/";
		ModelConfig config = loadModelConfig(model.m_name);

		if(true)
			m_importerOBJ->import_model(model, path, model.m_name, config, 0);
		else
			m_importerGltf->import_model(model, path + "helmet/", model.m_name, config, 0);
	}

	void GfxSystem::logFPS()
	{
		float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));
		m_time = time;

		static size_t frames = 0;
		static float prevtime;


		int64_t now = bx::getHPCounter() - m_timeOffset;
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency());
		const float deltaTime = float(frameTime / freq);
		m_deltaTime = deltaTime;

		if(time - prevtime >= 4.f)
		{
			printf("INFO: fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		++frames;
	}

	UiWindow& GfxSystem::createWindow(const string& name, int width, int height, bool fullScreen, User* user)
	{
		m_windows.emplace_back(make_object<UiWindow>(*this, name, width, height, fullScreen, user));
		return *m_windows.back();
	}

	void GfxSystem::createDebugMaterials()
	{
		m_materials.emplace_back(make_object<GfxMaterial>(*this, "debug", "unshaded", nullptr, false));
		m_materials.emplace_back(make_object<GfxMaterial>(*this, "debug_pbr", "pbr/scene", nullptr, true));
	}

	GfxMaterial& GfxSystem::debugMaterial()
	{
		return *m_materials.front();
	}

	GfxMaterial& GfxSystem::createMaterial(const string& name, const string& shader, const string& texture, bool pbs)
	{
		m_materials.emplace_back(make_object<GfxMaterial>(*this, name, shader, texture, pbs));
		return *m_materials.back();
	}

	GfxMaterial& GfxSystem::fetchMaterial(const string& name)
	{
		for(auto& material : m_materials)
			if(material->m_name == name)
				return *material;

		return *m_materials.front();
	}

	GfxMaterial& GfxSystem::fetchImage256Material(const Image256& image)
	{
		string name = "Image256_" + toString((uintptr_t)&image);
		GfxTexture& texture = this->fetchImage256(image);

		for(auto& material : m_materials)
			if(material->m_name == name)
				return *material;

		m_materials.emplace_back(make_object<GfxMaterial>(*this, name, "unshaded", &texture, false));
		return *m_materials.back();
		//return *m_materials.front();
	}

	GfxModel& GfxSystem::loadModel(const string& name)
	{
		m_models.emplace_back(make_object<GfxModel>(*this, name, false));
		this->loadModel(*m_models.back());
		return *m_models.back();
	}

	GfxModel& GfxSystem::fetchModel(const string& name)
	{
		for(auto& model : m_models)
			if(model->m_name == name)
				return *model;

		return loadModel(name);
	}

	GfxModel& GfxSystem::fetchSymbol(const Symbol& symbol)
	{
		return SymbolIndex::me().symbolModel(*this, symbol);
	}

}
