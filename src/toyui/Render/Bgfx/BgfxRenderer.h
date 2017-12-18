//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_GFXSYSTEM_H
#define TOY_GFXSYSTEM_H

#include <toyobj/Type.h>
#include <toyobj/Iterable/Iterable.h>
#include <toyui/Render/RenderWindow.h>
#include <toyui/UiWindow.h>
#include <toygfx/Types.h>

#include <toyui/Render/RenderWindow.h>
#include <toyui/Nano/NanoRenderer.h>

#if TOY_PLATFORM_EMSCRIPTEN
#include <toyui/Context/Emscripten/EmscriptenContext.h>
#elif TOY_CONTEXT_WINDOWS
#include <toyui/Context/Windows/WindowsContext.h>
#else
#include <toyui/Context/Glfw/GlfwContext.h>
#endif

#include <toygfx/Render/GfxRenderer.h>
#include <toygfx/GfxTarget.h>
#include <toygfx/GfxMaterial.h>

#include <bx/file.h>

namespace toy
{
	struct FilePath
	{
		string path;
		string name;
		string extension;
	};


#if TOY_PLATFORM_EMSCRIPTEN
	class _refl_ TOY_GFX_EXPORT GfxContext : public EmContext
#elif TOY_CONTEXT_WINDOWS
	class _refl_ TOY_GFX_EXPORT GfxContext : public WinContext
#else
	class _refl_ TOY_GFX_EXPORT GfxContext : public GlfwContext
#endif
	{
	public:
		GfxContext(GfxSystem& renderSystem, const string& name, int width, int height, bool fullScreen);

		void init();
		void render(uint32_t frame, float time, float time_offset);

		void addViewport(GfxViewport& viewport);

	protected:
		unique_ptr<GfxTarget> m_target;
		std::vector<GfxViewport*> m_viewports;
	};

	class _refl_ TOY_GFX_EXPORT GfxUiRenderer : public NanoRenderer
	{
	public:
		GfxUiRenderer(const string& resourcePath);

		// init
		virtual void setupContext();
		virtual void releaseContext();
	};

	class _refl_ TOY_GFX_EXPORT GfxSystem : public RenderSystem
	{
	public:
		GfxSystem(const string& resourcePath);
		~GfxSystem();
		
		virtual bool init();

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen);
		virtual object_ptr<Renderer> createRenderer(Context& context);

		virtual bool nextFrame();

		bx::FileReader m_fileReader;
		bx::FileWriter m_fileWriter;
		bx::DefaultAllocator m_allocator;

		string compileShader(const string& shaderSource, const string& suffix, ShaderType shaderType, const string& defines = "");

		GfxProgram& getProgram(const string& program);
		GfxTexture& getTexture(const string& texture);

		GfxTexture& loadTexture(const string& path, const string& texture);
		GfxTexture& loadTextureMem(const string& texture, array<uint8_t> data);
		GfxTexture& loadTextureRGBA(const string& texture, size_t width, size_t height, array<uint8_t> data);

		GfxTexture& fetchImage256(const Image256& image);

		ModelConfig loadModelConfig(const string& name);
		TiledModelConfig loadTiledModelConfig(const string& name);
		void loadModel(GfxModel& model);

		void logFPS();

		GfxMaterial& debugMaterial();
		GfxMaterial& createMaterial(const string& name, const string& shader, const string& texture, bool pbs);
		GfxMaterial& fetchMaterial(const string& name);
		GfxMaterial& fetchImage256Material(const Image256& image);

		void loadTiledModel(const string& path, const string& name);

		GfxModel& loadModel(const string& name);
		GfxModel& fetchModel(const string& name);
		GfxModel& fetchSymbol(const Symbol& symbol);

		UiWindow& createWindow(const string& name, int width, int height, bool fullScreen, User* user = nullptr);
		void createDebugMaterials();

	public:
		std::vector<object_ptr<UiWindow>> m_windows;

		std::vector<GfxContext*> m_contexts;

		std::map<string, unique_ptr<GfxTexture>> m_textures;
		std::map<string, unique_ptr<GfxProgram>> m_programs;
		std::vector<object_ptr<GfxMaterial>> m_materials;
		std::vector<object_ptr<GfxModel>> m_models;

		GfxMaterial* m_debugMaterial;

		unique_ptr<GfxPipeline> m_pipeline;

		unique_ptr<ImporterOBJ> m_importerOBJ;
		unique_ptr<ImporterGltf> m_importerGltf;

		uint32_t m_frame;
		double m_timeOffset;

		float m_time;
		float m_deltaTime;

	public:
		object_ptr<GfxTexture> m_white_texture;
		object_ptr<GfxTexture> m_black_texture;
	};
}

#endif // TOY_GFXSYSTEM_H
