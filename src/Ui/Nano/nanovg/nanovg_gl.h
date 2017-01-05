//
// Copyright (c) 2009-2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
#ifndef NANOVG_GL_H
#define NANOVG_GL_H

#ifdef __cplusplus
extern "C" {
#endif

	// Create flags

	enum NVGcreateFlags {
		// Flag indicating if geometry based anti-aliasing is used (may not be needed when using MSAA).
		NVG_ANTIALIAS = 1 << 0,
		// Flag indicating if strokes should be drawn using stencil buffer. The rendering will be a little
		// slower, but path overlaps (i.e. self-intersecting or sharp turns) will be drawn just once.
		NVG_STENCIL_STROKES = 1 << 1,
		// Flag indicating that additional debug checks are done.
		NVG_DEBUG = 1 << 2,
	};

#if defined NANOVG_GL2_IMPLEMENTATION
#  define NANOVG_GL2 1
#  define NANOVG_GL_IMPLEMENTATION 1
#elif defined NANOVG_GL3_IMPLEMENTATION
#  define NANOVG_GL3 1
#  define NANOVG_GL_IMPLEMENTATION 1
#  define NANOVG_GL_USE_UNIFORMBUFFER 1
#elif defined NANOVG_GLES2_IMPLEMENTATION
#  define NANOVG_GLES2 1
#  define NANOVG_GL_IMPLEMENTATION 1
#elif defined NANOVG_GLES3_IMPLEMENTATION
#  define NANOVG_GLES3 1
#  define NANOVG_GL_IMPLEMENTATION 1
#endif

#define NANOVG_GL_USE_STATE_FILTER (1)

	// NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER is 1 vertices will be transformed in vertex shader,
	// i.e. vertex shader constants will change for every primitive. If 0 vertices
	// are transformed on CPU and vertex shader constants are only set once.
	// Note: only works if NVG_TRANSFORM_IN_BACKEND is used.
#define NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER 1

	// Creates NanoVG contexts for different OpenGL (ES) versions.
	// Flags should be combination of the create flags above.

#if defined NANOVG_GL2

	NVGcontext* nvgCreateGL2(int flags);
	void nvgDeleteGL2(NVGcontext* ctx);

	int nvglCreateImageFromHandleGL2(NVGcontext* ctx, GLuint textureId, int w, int h, int flags, GLuint target);
	GLuint nvglImageFromHandleGL2(NVGcontext* ctx, int image);

#endif

#if defined NANOVG_GL3

	NVGcontext* nvgCreateGL3(int flags);
	void nvgDeleteGL3(NVGcontext* ctx);

	int nvglCreateImageFromHandleGL3(NVGcontext* ctx, GLuint textureId, int w, int h, int flags, GLuint target);
	GLuint nvglImageHandleGL3(NVGcontext* ctx, int image);

#endif

#if defined NANOVG_GLES2

	NVGcontext* nvgCreateGLES2(int flags);
	void nvgDeleteGLES2(NVGcontext* ctx);

	int nvglCreateImageFromHandleGLES2(NVGcontext* ctx, GLuint textureId, int w, int h, int flags, GLuint target);
	GLuint nvglImageHandleGLES2(NVGcontext* ctx, int image);

#endif

#if defined NANOVG_GLES3

	NVGcontext* nvgCreateGLES3(int flags);
	void nvgDeleteGLES3(NVGcontext* ctx);

	int nvglCreateImageFromHandleGLES3(NVGcontext* ctx, GLuint textureId, int w, int h, int flags, GLuint target);
	GLuint nvglImageHandleGLES3(NVGcontext* ctx, int image);

#endif

	// These are additional flags on top of NVGimageFlags.
	enum NVGimageFlagsGL {
		NVG_IMAGE_NODELETE = 1 << 16,	// Do not delete GL texture handle.
	};

#ifdef __cplusplus
}
#endif

#endif /* NANOVG_GL_H */

#ifdef NANOVG_GL_IMPLEMENTATION

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nanovg.h"

enum GLNVGuniformLoc {
	GLNVG_LOC_XFORM,
	GLNVG_LOC_TEX,
	GLNVG_LOC_FRAG,
#if defined NANOVG_GL3
	GLNVG_LOC_TEXRECT,
#endif
	GLNVG_MAX_LOCS
};

enum GLNVGshaderType {
	NSVG_SHADER_FILLGRAD,
	NSVG_SHADER_FILLIMG,
	NSVG_SHADER_SIMPLE,
	NSVG_SHADER_IMG,
	NSVG_SHADER_SOLIDCOLOR
};

#if NANOVG_GL_USE_UNIFORMBUFFER
enum GLNVGuniformBindings {
	GLNVG_FRAG_BINDING = 0,
};
#endif

struct GLNVGshader {
	GLuint prog;
	GLuint frag;
	GLuint vert;
	GLint loc[GLNVG_MAX_LOCS];
};
typedef struct GLNVGshader GLNVGshader;

struct GLNVGtexture {
	int id;
	GLuint tex;
	GLuint target;
	int width, height;
	int type;
	int flags;
};
typedef struct GLNVGtexture GLNVGtexture;

enum GLNVGcallType {
	GLNVG_NONE = 0,
	GLNVG_FILL,
	GLNVG_CONVEXFILL,
	GLNVG_STROKE,
	GLNVG_TRIANGLES,
};

struct GLNVGcall {
	int type;
	int image;
	int pathOffset;
	int pathCount;
	int triangleOffset;
	int triangleCount;
	int uniformOffset;
	float xform[6];
	float bounds[4];
	float opacity;
};
typedef struct GLNVGcall GLNVGcall;

struct GLNVGpath {
	int fillOffset;
	int fillCount;
	int strokeOffset;
	int strokeCount;
};
typedef struct GLNVGpath GLNVGpath;

struct GLNVGfragUniforms {
#if NANOVG_GL_USE_UNIFORMBUFFER
	float scissorMat[12]; // matrices are actually 3 vec4s
	float paintMat[12];
	struct NVGcolor innerCol;
	struct NVGcolor outerCol;
	float scissorExt[2];
	float scissorScale[2];
	float scissorCorners[4];
	float extent[2];
	float radius;
	float feather;
	float strokeMult;
	float strokeThr;
	int texType;
	int type;
#else
	// note: after modifying layout or size of uniform array,
	// don't forget to also update the fragment shader source!
#define NANOVG_GL_UNIFORMARRAY_SIZE 12
	union {
		struct {
			float scissorMat[12]; // matrices are actually 3 vec4s
			float paintMat[12];
			struct NVGcolor innerCol;
			struct NVGcolor outerCol;
			float scissorExt[2];
			float scissorScale[2];
			float scissorCorners[4];
			float extent[2];
			float radius;
			float feather;
			float strokeMult;
			float strokeThr;
			float texType;
			float type;
		};
		float uniformArray[NANOVG_GL_UNIFORMARRAY_SIZE][4];
	};
#endif
};
typedef struct GLNVGfragUniforms GLNVGfragUniforms;

struct GLNVGcontext {
	GLNVGshader shader;
	GLNVGtexture* textures;
	float view[2];
	int ntextures;
	int ctextures;
	int textureId;
	GLuint vertBuf;
#if defined NANOVG_GL3
	GLuint vertArr;
#endif
#if NANOVG_GL_USE_UNIFORMBUFFER
	GLuint fragBuf;
#endif
	int fragSize;
	int flags;

	// Per frame buffers
	GLNVGcall* calls;
	int ccalls;
	int ncalls;
	GLNVGpath* paths;
	int cpaths;
	int npaths;
	struct NVGvertex* verts;
	int cverts;
	int nverts;
	unsigned char* uniforms;
	int cuniforms;
	int nuniforms;

	// cached state
#if NANOVG_GL_USE_STATE_FILTER
	GLuint boundTexture;
	GLuint stencilMask;
	GLenum stencilFunc;
	GLint stencilFuncRef;
	GLuint stencilFuncMask;
#endif
};
typedef struct GLNVGcontext GLNVGcontext;

static int glnvg__maxi(int a, int b) { return a > b ? a : b; }

#ifdef NANOVG_GLES2
static unsigned int glnvg__nearestPow2(unsigned int num)
{
	unsigned n = num > 0 ? num - 1 : 0;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n++;
	return n;
}
#endif

static void glnvg__checkError(GLNVGcontext* gl, const char * str, int lineNo)
{
	GLenum err;
	if((gl->flags & NVG_DEBUG) == 0) return;
	err = glGetError();
	if(err != GL_NO_ERROR) {
		printf("Error %08x after %s (line %d)\n", err, str, lineNo);
		return;
	}
}

static void glnvg__bindTexture(GLNVGcontext* gl, GLuint tex, GLuint target)
{
#if NANOVG_GL_USE_STATE_FILTER
	if(gl->boundTexture != tex)
	{
#if NANOVG_GL3
		// Bind rect texture to slot 1, reusing slots for different sampler types (sampler2D vs 2DRect) does not work in glsl..
		if(target == GL_TEXTURE_RECTANGLE)
		{
			glActiveTexture(GL_TEXTURE1);
		}
#endif
		gl->boundTexture = tex;
		glBindTexture(target, tex);

#if NANOVG_GL3
		if(target == GL_TEXTURE_RECTANGLE)
		{
			glActiveTexture(GL_TEXTURE0);
		}
#endif
	}
#else
	glBindTexture(target, tex);
#endif
}

static void glnvg__stencilMask(GLNVGcontext* gl, GLuint mask)
{
#if NANOVG_GL_USE_STATE_FILTER
	if(gl->stencilMask != mask) {
		gl->stencilMask = mask;
		glStencilMask(mask);
	}
#else
	glStencilMask(mask);
#endif
}

static void glnvg__stencilFunc(GLNVGcontext* gl, GLenum func, GLint ref, GLuint mask)
{
#if NANOVG_GL_USE_STATE_FILTER
	if((gl->stencilFunc != func) ||
		(gl->stencilFuncRef != ref) ||
		(gl->stencilFuncMask != mask)) {

		gl->stencilFunc = func;
		gl->stencilFuncRef = ref;
		gl->stencilFuncMask = mask;
		glStencilFunc(func, ref, mask);
	}
#else
	glStencilFunc(func, ref, mask);
#endif
}

static GLNVGtexture* glnvg__allocTexture(GLNVGcontext* gl)
{
	GLNVGtexture* tex = NULL;
	int i;

	for(i = 0; i < gl->ntextures; i++) {
		if(gl->textures[i].id == 0) {
			tex = &gl->textures[i];
			break;
		}
	}
	if(tex == NULL) {
		if(gl->ntextures + 1 > gl->ctextures) {
			GLNVGtexture* textures;
			int ctextures = glnvg__maxi(gl->ntextures + 1, 4) + gl->ctextures / 2; // 1.5x Overallocate
			textures = (GLNVGtexture*)realloc(gl->textures, sizeof(GLNVGtexture)*ctextures);
			if(textures == NULL) return NULL;
			gl->textures = textures;
			gl->ctextures = ctextures;
		}
		tex = &gl->textures[gl->ntextures++];
	}

	memset(tex, 0, sizeof(*tex));
	tex->id = ++gl->textureId;
	tex->target = GL_TEXTURE_2D;

	return tex;
}

static GLNVGtexture* glnvg__findTexture(GLNVGcontext* gl, int id)
{
	int i;
	for(i = 0; i < gl->ntextures; i++)
		if(gl->textures[i].id == id)
			return &gl->textures[i];
	return NULL;
}

static int glnvg__deleteTexture(GLNVGcontext* gl, int id)
{
	int i;
	for(i = 0; i < gl->ntextures; i++) {
		if(gl->textures[i].id == id) {
			if(gl->textures[i].tex != 0 && (gl->textures[i].flags & NVG_IMAGE_NODELETE) == 0)
				glDeleteTextures(1, &gl->textures[i].tex);
			memset(&gl->textures[i], 0, sizeof(gl->textures[i]));
			return 1;
		}
	}
	return 0;
}

static void glnvg__dumpShaderError(GLuint shader, const char* name, const char* type)
{
	GLchar str[512 + 1];
	GLsizei len = 0;
	glGetShaderInfoLog(shader, 512, &len, str);
	if(len > 512) len = 512;
	str[len] = '\0';
	printf("Shader %s/%s error:\n%s\n", name, type, str);
}

static void glnvg__dumpProgramError(GLuint prog, const char* name)
{
	GLchar str[512 + 1];
	GLsizei len = 0;
	glGetProgramInfoLog(prog, 512, &len, str);
	if(len > 512) len = 512;
	str[len] = '\0';
	printf("Program %s error:\n%s\n", name, str);
}


static int glnvg__createShader(GLNVGshader* shader, const char* name, const char* header, const char* opts, const char* vshader, const char* fshader)
{
	GLint status;
	GLuint prog, vert, frag;
	const char* str[3];
	str[0] = header;
	str[1] = opts != NULL ? opts : "";

	memset(shader, 0, sizeof(*shader));

	prog = glCreateProgram();
	vert = glCreateShader(GL_VERTEX_SHADER);
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	str[2] = vshader;
	glShaderSource(vert, 3, str, 0);
	str[2] = fshader;
	glShaderSource(frag, 3, str, 0);

	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE) {
		glnvg__dumpShaderError(vert, name, "vert");
		return 0;
	}

	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE) {
		glnvg__dumpShaderError(frag, name, "frag");
		return 0;
	}

	glAttachShader(prog, vert);
	glAttachShader(prog, frag);

	glBindAttribLocation(prog, 0, "vertex");
	glBindAttribLocation(prog, 1, "tcoord");

	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if(status != GL_TRUE) {
		glnvg__dumpProgramError(prog, name);
		return 0;
	}

	shader->prog = prog;
	shader->vert = vert;
	shader->frag = frag;

	return 1;
}

static void glnvg__deleteShader(GLNVGshader* shader)
{
	if(shader->prog != 0)
		glDeleteProgram(shader->prog);
	if(shader->vert != 0)
		glDeleteShader(shader->vert);
	if(shader->frag != 0)
		glDeleteShader(shader->frag);
}

static void glnvg__getUniforms(GLNVGshader* shader)
{
	shader->loc[GLNVG_LOC_XFORM] = glGetUniformLocation(shader->prog, "xform");
	shader->loc[GLNVG_LOC_TEX] = glGetUniformLocation(shader->prog, "tex");

#if defined NANOVG_GL3
	shader->loc[GLNVG_LOC_TEXRECT] = glGetUniformLocation(shader->prog, "texRect");
#endif

#if NANOVG_GL_USE_UNIFORMBUFFER
	shader->loc[GLNVG_LOC_FRAG] = glGetUniformBlockIndex(shader->prog, "frag");
#else
	shader->loc[GLNVG_LOC_FRAG] = glGetUniformLocation(shader->prog, "frag");
#endif
}

static int glnvg__renderCreate(void* uptr)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	int align = 4;

	// TODO: mediump float may not be enough for GLES2 in iOS.
	// see the following discussion: https://github.com/memononen/nanovg/issues/46
	static const char* shaderHeader =
#if defined NANOVG_GL2
		"#define NANOVG_GL2 1\n"
#elif defined NANOVG_GL3
		"#version 410 core\n"
		"#define NANOVG_GL3 1\n"
#elif defined NANOVG_GLES2
		"#version 100\n"
		"#define NANOVG_GL2 1\n"
#elif defined NANOVG_GLES3
		"#version 300 es\n"
		"#define NANOVG_GL3 1\n"
#endif

#if NANOVG_GL_USE_UNIFORMBUFFER
		"#define USE_UNIFORMBUFFER 1\n"
#else
		"#define UNIFORMARRAY_SIZE 12\n"
#endif
		"\n";

	static const char* fillVertShader =
		"#ifdef NANOVG_GL3\n"
		"	uniform vec3 xform[3];\n" //[sx kx tx; ky sy ty; 2/viewSize_width, 2/viewSize_heigt, 1]
		"	in vec2 vertex;\n"
		"	in vec2 tcoord;\n"
		"	out vec2 ftcoord;\n"
		"	out vec2 fpos;\n"
		"#else\n"
		"	uniform vec3 xform[3];\n" //[sx kx tx; ky sy ty; 2/viewSize_width, 2/viewSize_heigt, 1]
		"	attribute vec2 vertex;\n"
		"	attribute vec2 tcoord;\n"
		"	varying vec2 ftcoord;\n"
		"	varying vec2 fpos;\n"
		"#endif\n"
		"void main(void) {\n"
		"	ftcoord = tcoord;\n"
#if NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER
		"   vec3 v = vec3(vertex, 1.0);\n"
		"	vec2 pt = vec2(dot(v,xform[0]), dot(v,xform[1]));\n"
#else 
		"   vec2 pt = vertex;\n"
#endif
		"	fpos = pt;\n"
		"	gl_Position = vec4(pt.x*xform[2].x - 1.0, 1.0 - pt.y*xform[2].y, 0, 1);\n"
		"}\n";

	static const char* fillFragShader =
		"#ifdef GL_ES\n"
		"#if defined(GL_FRAGMENT_PRECISION_HIGH) || defined(NANOVG_GL3)\n"
		" precision highp float;\n"
		"#else\n"
		" precision mediump float;\n"
		"#endif\n"
		"#endif\n"
		"#ifdef NANOVG_GL3\n"
		"#ifdef USE_UNIFORMBUFFER\n"
		"	layout(std140) uniform frag {\n"
		"		mat3 scissorMat;\n"
		"		mat3 paintMat;\n"
		"		vec4 innerCol;\n"
		"		vec4 outerCol;\n"
		"		vec2 scissorExt;\n"
		"		vec2 scissorScale;\n"
		"		vec4 scissorCorners;\n"
		"		vec2 extent;\n"
		"		float radius;\n"
		"		float feather;\n"
		"		float strokeMult;\n"
		"		float strokeThr;\n"
		"		int texType;\n"
		"		int type;\n"
		"	};\n"
		"#else\n" // NANOVG_GL3 && !USE_UNIFORMBUFFER
		"	uniform vec4 frag[UNIFORMARRAY_SIZE];\n"
		"#endif\n"
		"	uniform sampler2D tex;\n"
		"	uniform sampler2DRect texRect;\n"
		"	in vec2 ftcoord;\n"
		"	in vec2 fpos;\n"
		"	out vec4 outColor;\n"
		"#else\n" // !NANOVG_GL3
		"	uniform vec4 frag[UNIFORMARRAY_SIZE];\n"
		"	uniform sampler2D tex;\n"
		"	varying vec2 ftcoord;\n"
		"	varying vec2 fpos;\n"
		"#endif\n"
		"#ifndef USE_UNIFORMBUFFER\n"
		"	#define scissorMat mat3(frag[0].xyz, frag[1].xyz, frag[2].xyz)\n"
		"	#define paintMat mat3(frag[3].xyz, frag[4].xyz, frag[5].xyz)\n"
		"	#define innerCol frag[6]\n"
		"	#define outerCol frag[7]\n"
		"	#define scissorExt frag[8].xy\n"
		"	#define scissorScale frag[8].zw\n"
		"	#define scissorCorners frag[9].xyzw\n"
		"	#define extent frag[10].xy\n"
		"	#define radius frag[10].z\n"
		"	#define feather frag[10].w\n"
		"	#define strokeMult frag[11].x\n"
		"	#define strokeThr frag[11].y\n"
		"	#define texType int(frag[11].z)\n"
		"	#define type int(frag[11].w)\n"
		"#endif\n"
		"\n"
		"float sdroundrect(vec2 pt, vec2 ext, float rad) {\n"
		"	vec2 ext2 = ext - vec2(rad,rad);\n"
		"	vec2 d = abs(pt) - ext2;\n"
		"	return min(max(d.x,d.y),0.0) + length(max(d,0.0)) - rad;\n"
		"}\n"
		"\n"
		"// Scissoring\n"
		"float scissorMask(vec2 p) {\n"
		"	vec2 sc = (abs((scissorMat * vec3(p,1.0)).xy) - scissorExt) * scissorScale;\n"
		"	sc = vec2(0.5,0.5) - sc;\n"
		"	return clamp(sc.x,0.0,1.0) * clamp(sc.y,0.0,1.0);\n"
		/*"	float r = scissorCorners.x;\n"
		"	vec2 d = (abs((scissorMat * vec3(p, 1.0)).xy) - (scissorExt - r)) * scissorScale;\n"
		"   float dist = length(max(d, 0.0)) - r;\n"
		"	return clamp(1.0 - dist, 0.0, 1.0);\n"*/
		"}\n"
		"#ifdef EDGE_AA\n"
		"// Stroke - from [0..1] to clipped pyramid, where the slope is 1px.\n"
		"float strokeMask() {\n"
		"	return min(1.0, (1.0-abs(ftcoord.x*2.0-1.0))*strokeMult) * min(1.0, ftcoord.y);\n"
		"}\n"
		"#endif\n"
		"\n"
		"void main(void) {\n"
		"   vec4 result;\n"
		"	float scissor = scissorMask(fpos);\n"
		"#ifdef EDGE_AA\n"
		"	float strokeAlpha = strokeMask();\n"
		"#else\n"
		"	float strokeAlpha = 1.0;\n"
		"#endif\n"
		"	if (type == 0) {			// Gradient\n"
		"		// Calculate gradient color using box gradient\n"
		"		vec2 pt = (paintMat * vec3(fpos,1.0)).xy;\n"
		"		float d = clamp((sdroundrect(pt, extent, radius) + feather*0.5) / feather, 0.0, 1.0);\n"
		"		vec4 color = mix(innerCol,outerCol,d);\n"
		"		// Combine alpha\n"
		"		color *= strokeAlpha * scissor;\n"
		"		result = color;\n"
		"	} else if (type == 1) {		// Image\n"
		"		// Calculate color fron texture\n"
		"#ifdef NANOVG_GL3\n"
		"		vec2 pt = (paintMat * vec3(fpos,1.0)).xy;\n"
		"		vec4 color;\n"
		"		if(texType != 3) color = texture(tex, pt/extent);\n"
		"		else color = texture(texRect,pt);\n"
		"#else\n"
		"		vec2 pt = (paintMat * vec3(fpos,1.0)).xy / extent;\n"
		"		vec4 color = texture2D(tex, pt);\n"
		"#endif\n"
		"		if (texType == 1 || texType == 3) color = vec4(color.xyz*color.w,color.w);"
		"		if (texType == 2) color = vec4(color.x);"
		"		// Apply color tint and alpha.\n"
		"		color *= innerCol;\n"
		"		// Combine alpha\n"
		"		color *= strokeAlpha * scissor;\n"
		"		result = color;\n"
		"	} else if (type == 2) {		// Stencil fill\n"
		"		result = vec4(1,1,1,1);\n"
		"	} else if (type == 3) {		// Textured tris\n"
		"#ifdef NANOVG_GL3\n"
		"		vec4 color;\n"
		"		if(texType != 3) color = texture(tex, ftcoord);\n"
		"		else color = texture(texRect,ftcoord*extent);\n"
		"#else\n"
		"		vec4 color = texture2D(tex, ftcoord);\n"
		"#endif\n"
		"		if (texType == 1) color = vec4(color.xyz*color.w,color.w);"
		"		if (texType == 2) color = vec4(color.x);"
		"		color *= scissor;\n"
		"		result = color * innerCol;\n"
		"	} else if (type == 4) {		// Color solid fill\n"
		"		result = innerCol * scissor;\n"
		"	}\n"
		"#if defined(EDGE_AA) && defined(EDGE_DISCARD)\n"
		"	if (strokeAlpha < strokeThr) discard;\n"
		"#endif\n"
		"#ifdef NANOVG_GL3\n"
		"	outColor = result;\n"
		"#else\n"
		"	gl_FragColor = result;\n"
		"#endif\n"
		"}\n";

	const char* options = NULL;
	glnvg__checkError(gl, "init", __LINE__);

	if(gl->flags & NVG_ANTIALIAS) {
		options = "#define EDGE_AA 1\n"
			"#define EDGE_DISCARD 1\n";
		if((gl->flags & NVG_STENCIL_STROKES) == 0)
			options = "#define EDGE_AA 1\n";
	}

	if(glnvg__createShader(&gl->shader, "shader", shaderHeader, options, fillVertShader, fillFragShader) == 0)
		return 0;

	glnvg__checkError(gl, "uniform locations", __LINE__);
	glnvg__getUniforms(&gl->shader);

	// Create dynamic vertex array
#if defined NANOVG_GL3
	glGenVertexArrays(1, &gl->vertArr);
#endif
	glGenBuffers(1, &gl->vertBuf);

#if NANOVG_GL_USE_UNIFORMBUFFER
	// Create UBOs
	glUniformBlockBinding(gl->shader.prog, gl->shader.loc[GLNVG_LOC_FRAG], GLNVG_FRAG_BINDING);
	glGenBuffers(1, &gl->fragBuf);
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &align);
#endif
	gl->fragSize = sizeof(GLNVGfragUniforms) + align - sizeof(GLNVGfragUniforms) % align;

	glnvg__checkError(gl, "create done", __LINE__);

	glFinish();

	return 1;
}

static int glnvg__renderCreateTexture(void* uptr, int type, int w, int h, int imageFlags, const unsigned char* data)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	GLNVGtexture* tex = glnvg__allocTexture(gl);

	if(tex == NULL) return 0;

#ifdef NANOVG_GLES2
	// Check for non-power of 2.
	if(glnvg__nearestPow2(w) != (unsigned int)w || glnvg__nearestPow2(h) != (unsigned int)h) {
		// No repeat
		if((imageFlags & NVG_IMAGE_REPEATX) != 0 || (imageFlags & NVG_IMAGE_REPEATY) != 0) {
			printf("Repeat X/Y is not supported for non power-of-two textures (%d x %d)\n", w, h);
			imageFlags &= ~(NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
		}
		// No mips. 
		if(imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
			printf("Mip-maps is not support for non power-of-two textures (%d x %d)\n", w, h);
			imageFlags &= ~NVG_IMAGE_GENERATE_MIPMAPS;
		}
	}
#endif

	glGenTextures(1, &tex->tex);
	tex->width = w;
	tex->height = h;
	tex->type = type;
	tex->flags = imageFlags;
	glnvg__bindTexture(gl, tex->tex, tex->target);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
#ifndef NANOVG_GLES2
	glPixelStorei(GL_UNPACK_ROW_LENGTH, tex->width);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
#endif

#if defined (NANOVG_GL2)
	// GL 1.4 and later has support for generating mipmaps using a tex parameter.
	if(imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	}
#endif

	if(type == NVG_TEXTURE_RGBA)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
#if defined(NANOVG_GLES2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w, h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
#elif defined(NANOVG_GLES3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
#endif

	if(imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(imageFlags & NVG_IMAGE_REPEATX)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	if(imageFlags & NVG_IMAGE_REPEATY)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
#ifndef NANOVG_GLES2
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
#endif

	// The new way to build mipmaps on GLES and GL3
#if !defined(NANOVG_GL2)
	if(imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
#endif

	glnvg__checkError(gl, "create tex", __LINE__);
	glnvg__bindTexture(gl, 0, GL_TEXTURE_2D);

	return tex->id;
}


static int glnvg__renderDeleteTexture(void* uptr, int image)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	return glnvg__deleteTexture(gl, image);
}

static int glnvg__renderUpdateTexture(void* uptr, int image, int x, int y, int w, int h, const unsigned char* data)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	GLNVGtexture* tex = glnvg__findTexture(gl, image);

	if(tex == NULL) return 0;
	glnvg__bindTexture(gl, tex->tex, tex->target);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifndef NANOVG_GLES2
	glPixelStorei(GL_UNPACK_ROW_LENGTH, tex->width);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, x);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, y);
#else
	// No support for all of skip, need to update a whole row at a time.
	if(tex->type == NVG_TEXTURE_RGBA)
		data += y*tex->width * 4;
	else
		data += y*tex->width;
	x = 0;
	w = tex->width;
#endif

	if(tex->type == NVG_TEXTURE_RGBA)
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
#ifdef NANOVG_GLES2
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
#else
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RED, GL_UNSIGNED_BYTE, data);
#endif

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
#ifndef NANOVG_GLES2
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
#endif

	glnvg__bindTexture(gl, 0, GL_TEXTURE_2D);

	return 1;
}

static int glnvg__renderGetTextureSize(void* uptr, int image, int* w, int* h)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	GLNVGtexture* tex = glnvg__findTexture(gl, image);
	if(tex == NULL) return 0;
	*w = tex->width;
	*h = tex->height;
	return 1;
}

static void glnvg__xformToMat3x4(float* m3, float* t)
{
	m3[0] = t[0];
	m3[1] = t[1];
	m3[2] = 0.0f;
	m3[3] = 0.0f;
	m3[4] = t[2];
	m3[5] = t[3];
	m3[6] = 0.0f;
	m3[7] = 0.0f;
	m3[8] = t[4];
	m3[9] = t[5];
	m3[10] = 1.0f;
	m3[11] = 0.0f;
}

static NVGcolor glnvg__premulColor(NVGcolor c)
{
	c.r *= c.a;
	c.g *= c.a;
	c.b *= c.a;
	return c;
}

static int glnvg__convertPaint(GLNVGcontext* gl, GLNVGfragUniforms* frag, NVGpaint* paint,
	NVGscissor* scissor, const float * xform, float width, float fringe, float strokeThr)
{
	GLNVGtexture* tex = NULL;
	float invxform[6];

#if NVG_TRANSFORM_IN_BACKEND
	float t[6];
#else
	const float * t = scissor->xform;
#endif

	memset(frag, 0, sizeof(*frag));

	frag->innerCol = glnvg__premulColor(paint->innerColor);
	frag->outerCol = glnvg__premulColor(paint->outerColor);

	if(scissor->extent[0] < -0.5f || scissor->extent[1] < -0.5f) {
		memset(frag->scissorMat, 0, sizeof(frag->scissorMat));
		frag->scissorExt[0] = 1.0f;
		frag->scissorExt[1] = 1.0f;
		frag->scissorScale[0] = 1.0f;
		frag->scissorScale[1] = 1.0f;
	}
	else {
#if NVG_TRANSFORM_IN_BACKEND
		memcpy(t, scissor->xform, sizeof(float) * 6);
		nvgTransformMultiply(t, xform);
#endif
		nvgTransformInverse(invxform, t);
		glnvg__xformToMat3x4(frag->scissorMat, invxform);
		frag->scissorExt[0] = scissor->extent[0];
		frag->scissorExt[1] = scissor->extent[1];
		frag->scissorScale[0] = sqrtf(scissor->xform[0] * scissor->xform[0] + scissor->xform[2] * scissor->xform[2]) / fringe;
		frag->scissorScale[1] = sqrtf(scissor->xform[1] * scissor->xform[1] + scissor->xform[3] * scissor->xform[3]) / fringe;
		frag->scissorCorners[0] = scissor->corners[0];
		frag->scissorCorners[1] = scissor->corners[1];
		frag->scissorCorners[2] = scissor->corners[2];
		frag->scissorCorners[3] = scissor->corners[3];
	}

	memcpy(frag->extent, paint->extent, sizeof(frag->extent));
	frag->strokeMult = (width*0.5f + fringe*0.5f) / fringe;
	frag->strokeThr = strokeThr;

#if NVG_TRANSFORM_IN_BACKEND
	memcpy(t, paint->xform, sizeof(float) * 6);
	nvgTransformMultiply(t, xform);
#else
	t = paint->xform;
#endif

	if(paint->image != 0) {
		tex = glnvg__findTexture(gl, paint->image);
		if(tex == NULL) return 0;
		if((tex->flags & NVG_IMAGE_FLIPY) != 0) {
			float flipped[6];
			nvgTransformScale(flipped, 1.0f, -1.0f);
			nvgTransformMultiply(flipped, t);
			nvgTransformInverse(invxform, flipped);
		}
		else {
			nvgTransformInverse(invxform, t);
		}
		frag->type = NSVG_SHADER_FILLIMG;

		if(tex->type == NVG_TEXTURE_RGBA)
			frag->texType = (tex->flags & NVG_IMAGE_PREMULTIPLIED) ? 0 : 1;
		else
			frag->texType = 2;
#if NANOVG_GL3
		if(tex->target == GL_TEXTURE_RECTANGLE)
			frag->texType = 3;
#endif
	}
	else {
		frag->type = NSVG_SHADER_FILLGRAD;
		frag->radius = paint->radius;
		frag->feather = paint->feather;
		nvgTransformInverse(invxform, t);
	}

	glnvg__xformToMat3x4(frag->paintMat, invxform);

	return 1;
}

static GLNVGfragUniforms* nvg__fragUniformPtr(GLNVGcontext* gl, int i);

static void glnvg__setUniforms(GLNVGcontext* gl, int uniformOffset, int image)
{
#if NANOVG_GL_USE_UNIFORMBUFFER
	glBindBufferRange(GL_UNIFORM_BUFFER, GLNVG_FRAG_BINDING, gl->fragBuf, uniformOffset, sizeof(GLNVGfragUniforms));
#else
	GLNVGfragUniforms* frag = nvg__fragUniformPtr(gl, uniformOffset);
	glUniform4fv(gl->shader.loc[GLNVG_LOC_FRAG], NANOVG_GL_UNIFORMARRAY_SIZE, &(frag->uniformArray[0][0]));
#endif

	if(image != 0) {
		GLNVGtexture* tex = glnvg__findTexture(gl, image);
		glnvg__bindTexture(gl, tex != NULL ? tex->tex : 0, tex != NULL ? tex->target : GL_TEXTURE_2D);
		glnvg__checkError(gl, "tex paint tex", __LINE__);
	}
	else {
		glnvg__bindTexture(gl, 0, GL_TEXTURE_2D);
	}
}

static void glnvg__renderViewport(void* uptr, int width, int height)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	gl->view[0] = (float)width;
	gl->view[1] = (float)height;
}

static void glnvg__fill(GLNVGcontext* gl, GLNVGcall* call)
{
	GLNVGpath* paths = &gl->paths[call->pathOffset];
	int i, npaths = call->pathCount;

	// Draw shapes
	glEnable(GL_STENCIL_TEST);
	glnvg__stencilMask(gl, 0xff);
	glnvg__stencilFunc(gl, GL_ALWAYS, 0, 0xff);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	// set bindpoint for solid loc
	glnvg__setUniforms(gl, call->uniformOffset, 0);
	glnvg__checkError(gl, "fill simple", __LINE__);

	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_INCR_WRAP);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_DECR_WRAP);
	glDisable(GL_CULL_FACE);
	for(i = 0; i < npaths; i++)
		glDrawArrays(GL_TRIANGLE_FAN, paths[i].fillOffset, paths[i].fillCount);
	glEnable(GL_CULL_FACE);

	// Draw anti-aliased pixels
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glnvg__setUniforms(gl, call->uniformOffset + gl->fragSize, call->image);
	glnvg__checkError(gl, "fill fill", __LINE__);

	if(gl->flags & NVG_ANTIALIAS) {
		glnvg__stencilFunc(gl, GL_EQUAL, 0x00, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		// Draw fringes
		for(i = 0; i < npaths; i++)
			glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
	}

	// Draw fill
	glnvg__stencilFunc(gl, GL_NOTEQUAL, 0x0, 0xff);
	glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
	glDrawArrays(GL_TRIANGLES, call->triangleOffset, call->triangleCount);

	glDisable(GL_STENCIL_TEST);
}

static void glnvg__convexFill(GLNVGcontext* gl, GLNVGcall* call)
{
	GLNVGpath* paths = &gl->paths[call->pathOffset];
	int i, npaths = call->pathCount;

	glnvg__setUniforms(gl, call->uniformOffset, call->image);
	glnvg__checkError(gl, "convex fill", __LINE__);

	for(i = 0; i < npaths; i++)
		glDrawArrays(GL_TRIANGLE_FAN, paths[i].fillOffset, paths[i].fillCount);
	if(gl->flags & NVG_ANTIALIAS) {
		// Draw fringes
		for(i = 0; i < npaths; i++)
			glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
	}
}

static void glnvg__stroke(GLNVGcontext* gl, GLNVGcall* call)
{
	GLNVGpath* paths = &gl->paths[call->pathOffset];
	int npaths = call->pathCount, i;

	if(gl->flags & NVG_STENCIL_STROKES) {

		glEnable(GL_STENCIL_TEST);
		glnvg__stencilMask(gl, 0xff);

		// Fill the stroke base without overlap
		glnvg__stencilFunc(gl, GL_EQUAL, 0x0, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		glnvg__setUniforms(gl, call->uniformOffset + gl->fragSize, call->image);
		glnvg__checkError(gl, "stroke fill 0", __LINE__);
		for(i = 0; i < npaths; i++)
			glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);

		// Draw anti-aliased pixels.
		glnvg__setUniforms(gl, call->uniformOffset, call->image);
		glnvg__stencilFunc(gl, GL_EQUAL, 0x00, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		for(i = 0; i < npaths; i++)
			glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);

		// Clear stencil buffer.		
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glnvg__stencilFunc(gl, GL_ALWAYS, 0x0, 0xff);
		glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
		glnvg__checkError(gl, "stroke fill 1", __LINE__);
		for(i = 0; i < npaths; i++)
			glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		glDisable(GL_STENCIL_TEST);

		//		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset + gl->fragSize), paint, scissor, strokeWidth, fringe, 1.0f - 0.5f/255.0f);

	}
	else {
		glnvg__setUniforms(gl, call->uniformOffset, call->image);
		glnvg__checkError(gl, "stroke fill", __LINE__);
		// Draw Strokes
		for(i = 0; i < npaths; i++)
			glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
	}
}

static void glnvg__triangles(GLNVGcontext* gl, GLNVGcall* call)
{
	glnvg__setUniforms(gl, call->uniformOffset, call->image);
	glnvg__checkError(gl, "triangles fill", __LINE__);

	glDrawArrays(GL_TRIANGLES, call->triangleOffset, call->triangleCount);
}

static void glnvg__renderCancel(void* uptr) {
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	gl->nverts = 0;
	gl->npaths = 0;
	gl->ncalls = 0;
	gl->nuniforms = 0;
}

static void glnvg__renderBegin(GLNVGcontext* gl)
{
	if(gl->ncalls > 0) {
		float xform[9];

		// Setup require GL state.
		glUseProgram(gl->shader.prog);

		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_SCISSOR_TEST);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilMask(0xffffffff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);


#if NANOVG_GL3
		//glEnable(GL_TEXTURE_RECTANGLE);
		glBindTexture(GL_TEXTURE_RECTANGLE, 0);
#endif


#if NANOVG_GL_USE_STATE_FILTER
		gl->boundTexture = 0;
		gl->stencilMask = 0xffffffff;
		gl->stencilFunc = GL_ALWAYS;
		gl->stencilFuncRef = 0;
		gl->stencilFuncMask = 0xffffffff;
#endif

#if NANOVG_GL_USE_UNIFORMBUFFER
		// Upload ubo for frag shaders
		glBindBuffer(GL_UNIFORM_BUFFER, gl->fragBuf);
		glBufferData(GL_UNIFORM_BUFFER, gl->nuniforms * gl->fragSize, gl->uniforms, GL_STREAM_DRAW);
#endif

		// Upload vertex data
#if defined NANOVG_GL3
		glBindVertexArray(gl->vertArr);
#endif
		glBindBuffer(GL_ARRAY_BUFFER, gl->vertBuf);
		glBufferData(GL_ARRAY_BUFFER, gl->nverts * sizeof(NVGvertex), gl->verts, GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(NVGvertex), (const GLvoid*)(size_t)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(NVGvertex), (const GLvoid*)(0 + 2 * sizeof(float)));

		// Set view and texture just once per frame.
		glUniform1i(gl->shader.loc[GLNVG_LOC_TEX], 0);
#if defined NANOVG_GL3
		glUniform1i(gl->shader.loc[GLNVG_LOC_TEXRECT], 1);
#endif

		xform[6] = 2.0f / gl->view[0];
		xform[7] = 2.0f / gl->view[1];
		xform[8] = 1.0f;

#if NANOVG_GL_USE_UNIFORMBUFFER
		glBindBuffer(GL_UNIFORM_BUFFER, gl->fragBuf);
#endif

#if !NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER //just set once
		glUniform3fv(gl->shader.loc[GLNVG_LOC_XFORM], 3, xform);
#endif
	}
}

static void glnvg__renderCall(GLNVGcontext * gl, GLNVGcall * call, float * xform)
{
#if NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER
	//transpose for matrix form
	xform[0] = call->xform[0]; xform[1] = call->xform[2]; xform[2] = call->xform[4];
	xform[3] = call->xform[1]; xform[4] = call->xform[3]; xform[5] = call->xform[5];
	glUniform3fv(gl->shader.loc[GLNVG_LOC_XFORM], 3, xform);
#endif

	if(call->type == GLNVG_FILL)
		glnvg__fill(gl, call);
	else if(call->type == GLNVG_CONVEXFILL)
		glnvg__convexFill(gl, call);
	else if(call->type == GLNVG_STROKE)
		glnvg__stroke(gl, call);
	else if(call->type == GLNVG_TRIANGLES)
		glnvg__triangles(gl, call);
}

static void glnvg__renderEnd(GLNVGcontext* gl)
{
	if(gl->ncalls > 0) {
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
#if defined NANOVG_GL3
		glBindVertexArray(0);
#endif
		glDisable(GL_CULL_FACE);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
		glnvg__bindTexture(gl, 0, GL_TEXTURE_2D);
	}

	// Reset calls
	gl->nverts = 0;
	gl->npaths = 0;
	gl->ncalls = 0;
	gl->nuniforms = 0;
}

// Experimental feature: will create a 2D bounding volume hierarchy and try to batch as many
// "similar" (see glnvg_shouldAddCallToBatch for definition of similar) draw calls as possible
// by checking if bounding boxes of primitives are overlapping or not.

static float glnvg__minf(float a, float b) { return a < b ? a : b; }
static float glnvg__maxf(float a, float b) { return a > b ? a : b; }

static void glnvg__transformBounds(const float *bounds, const float* t, float * result)
{
	float x, y;
	const float verts[] =
	{
		bounds[0], bounds[1],
		bounds[0], bounds[3],
		bounds[2], bounds[1],
		bounds[2], bounds[3]
	};

	result[0] = result[1] = 1e6f;
	result[2] = result[3] = -1e6f;

	for(int i = 0; i<8; i += 2)
	{
		x = verts[i] * t[0] + verts[i + 1] * t[2] + t[4];
		y = verts[i] * t[1] + verts[i + 1] * t[3] + t[5];

		result[0] = glnvg__minf(result[0], x);
		result[1] = glnvg__minf(result[1], y);
		result[2] = glnvg__maxf(result[2], x);
		result[3] = glnvg__maxf(result[3], y);
	}
}


//#define BATCH_RENDER_CALLS 1
//#define BATCH_RENDER_HIDE_HIDDEN 1    // this will remove calls that are hidden by other calls
// Note: only axis aligned bounding boxes are checked
// so this will only work when drawing mostly solid rectangular shapes (e.g. UIs)

#if BATCH_RENDER_CALLS

static float glnvg__absf(float a) { return a >= 0.0f ? a : -a; }
static float glnvg__clampf(float a, float mn, float mx) { return a < mn ? mn : (a > mx ? mx : a); }

typedef GLNVGcall GLNVGbatchedCall;

struct GLNVGrenderNode
{
	float bounds[4]; //TODO: SIMD for bounds checks or integer bounds?

	union
	{
		struct {
			struct GLNVGrenderNode *left;
			struct GLNVGrenderNode *right;
		}; //bvh node

		struct {
			void *isNode; //if 0 the node is a leaf and 'call' is valid
			GLNVGcall *call;
		}; //bvh leaf (use the unused memory to store pointer to call)
	};
};
typedef struct GLNVGrenderNode GLNVGrenderNode;

static void glnvg__scissorRect(const NVGscissor * scissor, const float * tx, float * rect)
{
	float ptx[6];
	float ex, ey, tex, tey;
	const float * pxform = scissor->xform;

	ex = scissor->extent[0];
	ey = scissor->extent[1];

	if(tx)
	{
		memcpy(ptx, scissor->xform, sizeof(float) * 6);
		nvgTransformMultiply(ptx, tx);
		pxform = ptx;
	}

	tex = ex*glnvg__absf(pxform[0]) + ey*glnvg__absf(pxform[2]);
	tey = ex*glnvg__absf(pxform[1]) + ey*glnvg__absf(pxform[3]);

	// Intersect rects (x, y, width, height);
	rect[0] = pxform[4] - tex;
	rect[1] = pxform[5] - tey;
	rect[2] = rect[0] + tex * 2;
	rect[3] = rect[1] + tey * 2;
}

void glnvg_worldBounds(const float *bounds, const float* t, const NVGscissor * scissor, const float * screen, float * result)
{
	glnvg__transformBounds(bounds, t, result);

	float clip[4] = { 0.0f, 0.0f, screen[0], screen[1] };

	if(scissor->extent[0] > 0)
	{
		glnvg__scissorRect(scissor, t, clip);
	}

	result[0] = glnvg__clampf(result[0], clip[0], clip[2]);
	result[1] = glnvg__clampf(result[1], clip[1], clip[3]);
	result[2] = glnvg__clampf(result[2], clip[0], clip[2]);
	result[3] = glnvg__clampf(result[3], clip[1], clip[3]);
}

#define GLNVG_MAX_NUMBER_BATCHES 64
#define GLNVG_MAX_NUMBER_CALLS 64 //per batch
#define GLNVG_MAX_NUMBER_NODES GLNVG_MAX_NUMBER_CALLS*GLNVG_MAX_NUMBER_BATCHES*2

struct GLNVGrenderNodePool
{
	GLNVGrenderNode nodePool[GLNVG_MAX_NUMBER_NODES];
	int numNodes;
};
typedef struct GLNVGrenderNodePool GLNVGrenderNodePool;

GLNVGrenderNode* glnvg_nodeInit(GLNVGrenderNodePool *pool, const float * bounds)
{
	GLNVGrenderNode * b = 0;

	if(pool->numNodes < GLNVG_MAX_NUMBER_NODES)
	{
		b = &pool->nodePool[pool->numNodes++];

		if(bounds)
		{
			memcpy(b->bounds, bounds, sizeof(float) * 4);
		}
		else
		{
			b->bounds[0] = b->bounds[1] = 1e6f;
			b->bounds[2] = b->bounds[3] = -1e6f;
		}
		b->left = b->right = 0;
	}

	return b;
}

struct GLNVGrenderBatch
{
	GLNVGrenderNode * root;
	int image;

	GLNVGbatchedCall * calls[GLNVG_MAX_NUMBER_CALLS]; //TODO: we could use an intrusive list instead (have to check GLNVG_MAX_NUMBER_NODES when adding calls)
	int numCalls;
};
typedef struct GLNVGrenderBatch GLNVGrenderBatch;

struct GLNVGrenderBatchPool
{
	GLNVGrenderBatch batches[GLNVG_MAX_NUMBER_BATCHES];
	int numBatches;

	int map[GLNVG_MAX_NUMBER_BATCHES];
};
typedef struct GLNVGrenderBatchPool GLNVGrenderBatchPool;

GLNVGrenderBatch * glnvg_createBatch(GLNVGrenderBatchPool * batch, int img, int insert)
{
	GLNVGrenderBatch * b = 0;

	if(batch->numBatches < GLNVG_MAX_NUMBER_BATCHES)
	{
		int idx = batch->numBatches++;

		b = &batch->batches[idx];
		b->root = 0;
		b->numCalls = 0;
		b->image = img;

		if(insert > idx) insert = idx;

		for(int i = idx; i>insert; --i)
			batch->map[i] = batch->map[i - 1];

		batch->map[insert] = idx;
	}

	return b;
}

static int glnvg_intersectBounds(const float* b, const float* a)
{
	return (b[0] <= a[2] && b[2] >= a[0]) && (b[1] <= a[3] && b[3] >= a[1]);
}

static int glnvg_containsBounds(const float* b, const float* a)
{
	return (a[0] >= b[0] && a[1] >= b[1]) && (a[2] <= b[2] && a[3] <= b[3]);
}

GLNVGrenderNode * glnvg_intersectNode(GLNVGrenderNode * batch, const float* b)
{
	return (batch != 0 && glnvg_intersectBounds(batch->bounds, b) != 0) ? batch : 0;
}

GLNVGrenderNode * glnvg_intersectNodeRecursive(GLNVGrenderNode * batch, const float* b)
{
	GLNVGrenderNode * i = glnvg_intersectNode(batch, b);

	if(i != 0 && batch->isNode != 0)
	{
		i = glnvg_intersectNodeRecursive(batch->left, b);

		if(i == 0)
			i = glnvg_intersectNodeRecursive(batch->right, b);
	}

	return i;
}

GLNVGrenderNode * glnvg_intersectsBatch(const GLNVGrenderBatch * b, const float * bounds)
{
	return glnvg_intersectNodeRecursive(b->root, bounds);
}


void glnvg_intersectNodeInvalidateHiddenRecursive(GLNVGrenderNode * node, const float* b, int * res)
{
	GLNVGrenderNode * i = glnvg_intersectNode(node, b);

	if(i != 0)
	{

		//#define TRY_SHRINK 1
#if TRY_SHRINK //shrink the boundary, if it fully overlaps an axis
		float * bounds = node->bounds;

		int v = b[0] <= bounds[0] && b[2] >= bounds[2];
		int h = b[1] <= bounds[1] && b[3] >= bounds[3];

		if(v) // fully overlaps in x axis
		{
			if(b[3] > bounds[3]) bounds[3] = glnvg__maxf(b[1], bounds[1]);
			else if(b[1] < bounds[1]) bounds[1] = glnvg__minf(b[3], bounds[3]);
		}

		if(h) // fully overlaps in y axis
		{
			if(b[2] > bounds[2]) bounds[2] = glnvg__maxf(b[0], bounds[0]);
			else if(b[0] < bounds[0]) bounds[0] = glnvg__minf(b[2], bounds[2]);
		}
#endif
		if(i->isNode != 0)
		{
			glnvg_intersectNodeInvalidateHiddenRecursive(node->left, b, res);
			glnvg_intersectNodeInvalidateHiddenRecursive(node->right, b, res);
		}
		else
		{
#if TRY_SHRINK
			if(v && h)
#else
			if(glnvg_containsBounds(b, node->bounds))
#endif
			{
				node->call->type = GLNVG_NONE;
			}

			*res = *res + 1;
		}
	}
}

int glnvg_intersectsBatchNoInvalidate(const GLNVGrenderBatch * b, const float * bounds)
{
	GLNVGrenderNode * n = glnvg_intersectNodeRecursive(b->root, bounds);
	if(n && n->isNode == 0) return 1;
	return 0;
}

int glnvg_intersectsBatchInvalidateHidden(const GLNVGrenderBatch * b, const float * bounds, float opacity)
{
	int res = 0;

	if(opacity >= 1.0f)
		glnvg_intersectNodeInvalidateHiddenRecursive(b->root, bounds, &res);
	else
		res = glnvg_intersectsBatchNoInvalidate(b, bounds);

	return res;
}

void glnvg_combineBounds(const float*a, const float *b, float * result)
{
	result[0] = glnvg__minf(a[0], b[0]);
	result[1] = glnvg__minf(a[1], b[1]);
	result[2] = glnvg__maxf(a[2], b[2]);
	result[3] = glnvg__maxf(a[3], b[3]);
}

GLNVGrenderNode * glnvg_expandNodeRecursive(GLNVGrenderNode * batch, const float* b)
{
	GLNVGrenderNode * i = glnvg_intersectNode(batch, b);

	if(i != 0 && batch->isNode != 0)
	{
		glnvg_combineBounds(b, i->bounds, i->bounds); //not for leaf nodes!

		i = glnvg_expandNodeRecursive(batch->left, b);

		if(i == 0)
			i = glnvg_expandNodeRecursive(batch->right, b);
	}

	return i;
}

GLNVGrenderNode * glnvg_appendNode(GLNVGrenderBatch * b, GLNVGrenderNodePool *pool, const float* bounds)
{
	GLNVGrenderNode * node = glnvg_nodeInit(pool, bounds);

	if(node)
	{
		GLNVGrenderNode * intersecting_node = glnvg_expandNodeRecursive(b->root, bounds);

		if(intersecting_node != 0)
		{
			GLNVGrenderNode * move_intersecting = glnvg_nodeInit(pool, intersecting_node->bounds);
			if(move_intersecting)
			{
				glnvg_combineBounds(bounds, intersecting_node->bounds, intersecting_node->bounds);

				if(intersecting_node->isNode == 0)
					move_intersecting->call = intersecting_node->call;

				intersecting_node->left = node;
				intersecting_node->right = move_intersecting;
			}
		}
		else
		{
			GLNVGrenderNode * old_root = b->root;
			GLNVGrenderNode * new_root = glnvg_nodeInit(pool, old_root->bounds);
			if(new_root)
			{
				glnvg_combineBounds(bounds, new_root->bounds, new_root->bounds);

				new_root->right = old_root;
				new_root->left = node;

				b->root = new_root;
			}
		}
	}

	return node;
}

GLNVGrenderNode * glnvg_addCall(GLNVGrenderBatch * b, GLNVGrenderNodePool *pool, GLNVGbatchedCall* call)
{
	GLNVGrenderNode * n = 0;

	if(b->numCalls < GLNVG_MAX_NUMBER_CALLS)
	{
		b->calls[b->numCalls++] = call;

		if(b->numCalls == 1)
		{
			n = glnvg_nodeInit(pool, call->bounds);
			b->root = n;
		}
		else
		{
			n = glnvg_appendNode(b, pool, call->bounds);
		}

		n->call = call;
	}

	return n;
}

//override-able
int glnvg_shouldAddCallToBatch(const GLNVGbatchedCall* call, const GLNVGrenderBatch * batch)
{
	return (call->image == batch->image) ? 1 : 0;
}

static void glnvg__renderBatch(GLNVGcontext* gl, GLNVGrenderBatchPool* batches)
{
	int i;
	float xform[9];

#if DEBUG_PRINT_CONTENTS
	printf("flush batch\n");
	for(int j = 0; j < batches->numBatches; ++j)
	{
		int m = batches->map[j];
		GLNVGrenderBatch * batch = &batches->batches[m];

		printf("%02d-> %02d img=%d call=%d\n", j, m, batch->image, batch->numCalls);
	}
#endif

	if(gl->ncalls > 0) {

		xform[6] = 2.0f / gl->view[0];
		xform[7] = 2.0f / gl->view[1];
		xform[8] = 1.0f;

		for(int j = 0; j < batches->numBatches; ++j)
		{
			int m = batches->map[j];
			GLNVGrenderBatch * batch = &batches->batches[m];

			for(i = 0; i<batch->numCalls; ++i)
			{
				GLNVGcall * call = batch->calls[i];

				if(call->opacity >= 0.0f)
					glnvg__renderCall(gl, call, xform);
			}
		}
	}

	batches->numBatches = 0;
}

static void glnvg__renderFlushBatched(GLNVGcontext* gl)
{
	glnvg__renderBegin(gl);

	GLNVGrenderNodePool pool;
	pool.numNodes = 0;

	GLNVGrenderBatchPool batches;
	batches.numBatches = 0;

	int j, i;
	for(i = 0; i < gl->ncalls; ++i)
	{
		GLNVGcall* call = &gl->calls[i];

		if(call->bounds[2] - call->bounds[0] > 0 &&
			call->bounds[3] - call->bounds[1] > 0)
		{
			int insert = batches.numBatches;
			GLNVGrenderBatch * found = 0;

			for(j = batches.numBatches; j > 0; --j)
			{
				int m = batches.map[j - 1];
				GLNVGrenderBatch * batch = &batches.batches[m];

#if BATCH_RENDER_HIDE_HIDDEN
				int res = glnvg_intersectsBatchInvalidateHidden(batch, call->bounds, call->opacity);
#else
				int res = glnvg_intersectsBatchNoInvalidate(batch, call->bounds);
#endif

				if(glnvg_shouldAddCallToBatch(call, batch) != 0)
				{
					int others = -1;

					// if first found batch - see if there are potentially other batches to add this call
					if(found == 0)
					{
						if(batch->numCalls < GLNVG_MAX_NUMBER_CALLS)
							found = batch;
						else
							insert = j;

						others = 0;

						for(int k = j - 1; k > 0; --k)
						{
							int m = batches.map[k - 1];
							GLNVGrenderBatch * batch = &batches.batches[m];

							if(batch->numCalls < GLNVG_MAX_NUMBER_CALLS &&
								glnvg_shouldAddCallToBatch(call, batch) != 0)
							{
								++others;
								break;
							}
						}
					}
					else
					{
						if(batch->numCalls < GLNVG_MAX_NUMBER_CALLS)
							found = batch;
					}

					//if we already intesect with this batch or there are no similar batches break!
					if(res != 0 || others == 0)
					{
						break;
					}
				}
				else
				{
					//check if intersects with nodes (only leafs)
					if(res != 0)
					{
						//yes: break and add new batch here
						insert = j;
						break;
					}
					else
					{
						//no: continue and see if we can add to existing batch to come
						insert = j + 1;
					}
				}
			}

#if BATCH_RENDER_HIDE_HIDDEN
			// hide hidden calls of remaining batches
			if(call->opacity >= 1.0f)
			{
				for(int k = j - 1; k > 0; --k)
				{
					int m = batches.map[k - 1];
					GLNVGrenderBatch * batch = &batches.batches[m];
					glnvg_intersectsBatchInvalidateHidden(batch, call->bounds, call->opacity);
				}
			}
#endif

			GLNVGrenderNode * added = 0;

			if(found)
			{
				added = glnvg_addCall(found, &pool, call);
				insert = batches.numBatches; //TODO: if adding fails ... where do we add?
			}

			if(added == 0)
			{
				GLNVGrenderBatch * batch = glnvg_createBatch(&batches, call->image, insert);

				if(batch == 0) //flush everything collected so far and try again
				{
					glnvg__renderBatch(gl, &batches);
					pool.numNodes = 0;

					batch = glnvg_createBatch(&batches, call->image, insert);
				}

				if(batch)
				{
					added = glnvg_addCall(batch, &pool, call);
				}
			}
		}
	}

	glnvg__renderBatch(gl, &batches);
	glnvg__renderEnd(gl);
}

#endif


static void glnvg__renderFlush(void* uptr)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;

#if BATCH_RENDER_CALLS
	glnvg__renderFlushBatched(gl);
#else
	float xform[9];
	int i;

	xform[6] = 2.0f / gl->view[0];
	xform[7] = 2.0f / gl->view[1];
	xform[8] = 1.0f;

	glnvg__renderBegin(gl);

	if(gl->ncalls > 0) {
		for(i = 0; i < gl->ncalls; i++) {
			glnvg__renderCall(gl, &gl->calls[i], xform);
		}
	}

	glnvg__renderEnd(gl);
#endif
}

static int glnvg__maxVertCount(const NVGpath* paths, int npaths)
{
	int i, count = 0;
	for(i = 0; i < npaths; i++) {
		count += paths[i].nfill;
		count += paths[i].nstroke;
	}
	return count;
}

static GLNVGcall* glnvg__allocCall(GLNVGcontext* gl)
{
	GLNVGcall* ret = NULL;
	if(gl->ncalls + 1 > gl->ccalls) {
		GLNVGcall* calls;
		int ccalls = glnvg__maxi(gl->ncalls + 1, 128) + gl->ccalls / 2; // 1.5x Overallocate
		calls = (GLNVGcall*)realloc(gl->calls, sizeof(GLNVGcall) * ccalls);
		if(calls == NULL) return NULL;
		gl->calls = calls;
		gl->ccalls = ccalls;
	}
	ret = &gl->calls[gl->ncalls++];
	memset(ret, 0, sizeof(GLNVGcall));
	return ret;
}

static int glnvg__allocPaths(GLNVGcontext* gl, int n)
{
	int ret = 0;
	if(gl->npaths + n > gl->cpaths) {
		GLNVGpath* paths;
		int cpaths = glnvg__maxi(gl->npaths + n, 128) + gl->cpaths / 2; // 1.5x Overallocate
		paths = (GLNVGpath*)realloc(gl->paths, sizeof(GLNVGpath) * cpaths);
		if(paths == NULL) return -1;
		gl->paths = paths;
		gl->cpaths = cpaths;
	}
	ret = gl->npaths;
	gl->npaths += n;
	return ret;
}

static int glnvg__allocVerts(GLNVGcontext* gl, int n)
{
	int ret = 0;
	if(gl->nverts + n > gl->cverts) {
		NVGvertex* verts;
		int cverts = glnvg__maxi(gl->nverts + n, 4096) + gl->cverts / 2; // 1.5x Overallocate
		verts = (NVGvertex*)realloc(gl->verts, sizeof(NVGvertex) * cverts);
		if(verts == NULL) return -1;
		gl->verts = verts;
		gl->cverts = cverts;
	}
	ret = gl->nverts;
	gl->nverts += n;
	return ret;
}

#if !NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER && NVG_TRANSFORM_IN_BACKEND
static void glnvg__transformVerts(const NVGvertex* input, int n, const float* t, NVGvertex* result)
{
	int i;
	const NVGvertex* vtx;

	//?? #pragma clang loop vectorize(enable) interleave(enable)
	for(i = 0; i<n; ++i)
	{
		vtx = input + i;

		result[i].x = vtx->x*t[0] + vtx->y*t[2] + t[4];
		result[i].y = vtx->x*t[1] + vtx->y*t[3] + t[5];
		result[i].u = vtx->u;
		result[i].v = vtx->v;
	}
}
#endif

static int glnvg__allocFragUniforms(GLNVGcontext* gl, int n)
{
	int ret = 0, structSize = gl->fragSize;
	if(gl->nuniforms + n > gl->cuniforms) {
		unsigned char* uniforms;
		int cuniforms = glnvg__maxi(gl->nuniforms + n, 128) + gl->cuniforms / 2; // 1.5x Overallocate
		uniforms = (unsigned char*)realloc(gl->uniforms, structSize * cuniforms);
		if(uniforms == NULL) return -1;
		gl->uniforms = uniforms;
		gl->cuniforms = cuniforms;
	}
	ret = gl->nuniforms * structSize;
	gl->nuniforms += n;
	return ret;
}

static GLNVGfragUniforms* nvg__fragUniformPtr(GLNVGcontext* gl, int i)
{
	return (GLNVGfragUniforms*)&gl->uniforms[i];
}

static void glnvg__vset(NVGvertex* vtx, float x, float y, float u, float v)
{
	vtx->x = x;
	vtx->y = y;
	vtx->u = u;
	vtx->v = v;
}

static void glnvg__renderFill(void* uptr, NVGpaint* paint, NVGscissor* scissor, const float* xform, float fringe,
	const float* bounds, const NVGpath* paths, int npaths)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	GLNVGcall* call = glnvg__allocCall(gl);
	NVGvertex* quad;
	GLNVGfragUniforms* frag;
	int i, maxverts, offset;

	if(call == NULL) return;

	call->type = GLNVG_FILL;
	call->pathOffset = glnvg__allocPaths(gl, npaths);
	if(call->pathOffset == -1) goto error;
	call->pathCount = npaths;
	call->image = paint->image;

	memcpy(call->xform, xform, sizeof(float) * 6);
#if BATCH_RENDER_CALLS
	glnvg_worldBounds(bounds, xform, scissor, gl->view, call->bounds);
	call->opacity = glnvg__maxf(paint->innerColor.a, paint->outerColor.a);
#endif

	if(npaths == 1 && paths[0].convex)
		call->type = GLNVG_CONVEXFILL;

	// Allocate vertices for all the paths.
	maxverts = glnvg__maxVertCount(paths, npaths) + 6;
	offset = glnvg__allocVerts(gl, maxverts);
	if(offset == -1) goto error;

	for(i = 0; i < npaths; i++) {
		GLNVGpath* copy = &gl->paths[call->pathOffset + i];
		const NVGpath* path = &paths[i];
		memset(copy, 0, sizeof(GLNVGpath));
		if(path->nfill > 0) {
			copy->fillOffset = offset;
			copy->fillCount = path->nfill;
#if !NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER && NVG_TRANSFORM_IN_BACKEND
			glnvg__transformVerts(path->fill, path->nfill, xform, &gl->verts[offset]);
#else
			memcpy(&gl->verts[offset], path->fill, sizeof(NVGvertex) * path->nfill);
#endif
			offset += path->nfill;
		}
		if(path->nstroke > 0) {
			copy->strokeOffset = offset;
			copy->strokeCount = path->nstroke;
#if !NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER && NVG_TRANSFORM_IN_BACKEND
			glnvg__transformVerts(path->stroke, path->nstroke, xform, &gl->verts[offset]);
#else
			memcpy(&gl->verts[offset], path->stroke, sizeof(NVGvertex) * path->nstroke);
#endif
			offset += path->nstroke;
		}
	}

	// Quad
	call->triangleOffset = offset;
	call->triangleCount = 6;
	quad = &gl->verts[call->triangleOffset];
	const float * b = bounds;

#if !NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER && NVG_TRANSFORM_IN_BACKEND
	float txBounds[4];
	glnvg__transformBounds(bounds, xform, txBounds);
	b = txBounds;
#endif

	glnvg__vset(&quad[0], b[0], b[3], 0.5f, 1.0f);
	glnvg__vset(&quad[1], b[2], b[3], 0.5f, 1.0f);
	glnvg__vset(&quad[2], b[2], b[1], 0.5f, 1.0f);

	glnvg__vset(&quad[3], b[0], b[3], 0.5f, 1.0f);
	glnvg__vset(&quad[4], b[2], b[1], 0.5f, 1.0f);
	glnvg__vset(&quad[5], b[0], b[1], 0.5f, 1.0f);

	// Setup uniforms for draw calls
	if(call->type == GLNVG_FILL) {
		call->uniformOffset = glnvg__allocFragUniforms(gl, 2);
		if(call->uniformOffset == -1) goto error;
		// Simple shader for stencil
		frag = nvg__fragUniformPtr(gl, call->uniformOffset);
		memset(frag, 0, sizeof(*frag));
		frag->strokeThr = -1.0f;
		frag->type = NSVG_SHADER_SIMPLE;
		// Fill shader
		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset + gl->fragSize), paint, scissor, xform, fringe, fringe, -1.0f);
	}
	else {
		call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
		if(call->uniformOffset == -1) goto error;
		// Fill shader
		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, xform, fringe, fringe, -1.0f);
	}

	return;

error:
	// We get here if call alloc was ok, but something else is not.
	// Roll back the last call to prevent drawing it.
	if(gl->ncalls > 0) gl->ncalls--;
}

static void glnvg__renderStroke(void* uptr, NVGpaint* paint, NVGscissor* scissor, const float* xform, float fringe,
	float strokeWidth, const float* bounds, const NVGpath* paths, int npaths)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	GLNVGcall* call = glnvg__allocCall(gl);
	int i, maxverts, offset;

	if(call == NULL) return;

	call->type = GLNVG_STROKE;
	call->pathOffset = glnvg__allocPaths(gl, npaths);
	if(call->pathOffset == -1) goto error;
	call->pathCount = npaths;
	call->image = paint->image;

	memcpy(call->xform, xform, sizeof(float) * 6);
#if BATCH_RENDER_CALLS
	glnvg_worldBounds(bounds, xform, scissor, gl->view, call->bounds);
	call->opacity = glnvg__maxf(paint->innerColor.a, paint->outerColor.a);
#endif

	// Allocate vertices for all the paths.
	maxverts = glnvg__maxVertCount(paths, npaths);
	offset = glnvg__allocVerts(gl, maxverts);
	if(offset == -1) goto error;

	for(i = 0; i < npaths; i++) {
		GLNVGpath* copy = &gl->paths[call->pathOffset + i];
		const NVGpath* path = &paths[i];
		memset(copy, 0, sizeof(GLNVGpath));
		if(path->nstroke) {
			copy->strokeOffset = offset;
			copy->strokeCount = path->nstroke;
#if !NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER && NVG_TRANSFORM_IN_BACKEND
			glnvg__transformVerts(path->stroke, path->nstroke, xform, &gl->verts[offset]);
#else
			memcpy(&gl->verts[offset], path->stroke, sizeof(NVGvertex) * path->nstroke);
#endif
			offset += path->nstroke;
		}
	}

	if(gl->flags & NVG_STENCIL_STROKES) {
		// Fill shader
		call->uniformOffset = glnvg__allocFragUniforms(gl, 2);
		if(call->uniformOffset == -1) goto error;

		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, xform, strokeWidth, fringe, -1.0f);
		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset + gl->fragSize), paint, scissor, xform, strokeWidth, fringe, 1.0f - 0.5f / 255.0f);

	}
	else {
		// Fill shader
		call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
		if(call->uniformOffset == -1) goto error;
		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, xform, strokeWidth, fringe, -1.0f);
	}

	return;

error:
	// We get here if call alloc was ok, but something else is not.
	// Roll back the last call to prevent drawing it.
	if(gl->ncalls > 0) gl->ncalls--;
}

static void glnvg__renderTriangles(void* uptr, NVGpaint* paint, NVGscissor* scissor, const float* xform,
	const float* bounds, const NVGvertex* verts, int nverts)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	GLNVGcall* call = glnvg__allocCall(gl);
	GLNVGfragUniforms* frag;

	if(call == NULL) return;

	call->type = GLNVG_TRIANGLES;
	call->image = paint->image;

	memcpy(call->xform, xform, sizeof(float) * 6);
#if BATCH_RENDER_CALLS
	glnvg_worldBounds(bounds, xform, scissor, gl->view, call->bounds);
	call->opacity = glnvg__maxf(paint->innerColor.a, paint->outerColor.a);
#endif

	// Allocate vertices for all the paths.
	call->triangleOffset = glnvg__allocVerts(gl, nverts);
	if(call->triangleOffset == -1) goto error;
	call->triangleCount = nverts;

#if !NANOVG_GL_TRANSFORM_IN_VERTEX_SHADER && NVG_TRANSFORM_IN_BACKEND
	glnvg__transformVerts(verts, nverts, xform, &gl->verts[call->triangleOffset]);
#else
	memcpy(&gl->verts[call->triangleOffset], verts, sizeof(NVGvertex) * nverts);
#endif

	// Fill shader
	call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
	if(call->uniformOffset == -1) goto error;
	frag = nvg__fragUniformPtr(gl, call->uniformOffset);
	glnvg__convertPaint(gl, frag, paint, scissor, xform, 1.0f, 1.0f, -1.0f);
	frag->type = paint->image != 0 ? NSVG_SHADER_IMG : NSVG_SHADER_SOLIDCOLOR;

	return;

error:
	// We get here if call alloc was ok, but something else is not.
	// Roll back the last call to prevent drawing it.
	if(gl->ncalls > 0) gl->ncalls--;
}

static void glnvg__renderDelete(void* uptr)
{
	GLNVGcontext* gl = (GLNVGcontext*)uptr;
	int i;
	if(gl == NULL) return;

	glnvg__deleteShader(&gl->shader);

#if NANOVG_GL3
#if NANOVG_GL_USE_UNIFORMBUFFER
	if(gl->fragBuf != 0)
		glDeleteBuffers(1, &gl->fragBuf);
#endif
	if(gl->vertArr != 0)
		glDeleteVertexArrays(1, &gl->vertArr);
#endif
	if(gl->vertBuf != 0)
		glDeleteBuffers(1, &gl->vertBuf);

	for(i = 0; i < gl->ntextures; i++) {
		if(gl->textures[i].tex != 0 && (gl->textures[i].flags & NVG_IMAGE_NODELETE) == 0)
			glDeleteTextures(1, &gl->textures[i].tex);
	}
	free(gl->textures);

	free(gl->paths);
	free(gl->verts);
	free(gl->uniforms);
	free(gl->calls);

	free(gl);
}


#if defined NANOVG_GL2
NVGcontext* nvgCreateGL2(int flags)
#elif defined NANOVG_GL3
NVGcontext* nvgCreateGL3(int flags)
#elif defined NANOVG_GLES2
NVGcontext* nvgCreateGLES2(int flags)
#elif defined NANOVG_GLES3
NVGcontext* nvgCreateGLES3(int flags)
#endif
{
	NVGparams params;
	NVGcontext* ctx = NULL;
	GLNVGcontext* gl = (GLNVGcontext*)malloc(sizeof(GLNVGcontext));
	if(gl == NULL) goto error;
	memset(gl, 0, sizeof(GLNVGcontext));

	memset(&params, 0, sizeof(params));
	params.renderCreate = glnvg__renderCreate;
	params.renderCreateTexture = glnvg__renderCreateTexture;
	params.renderDeleteTexture = glnvg__renderDeleteTexture;
	params.renderUpdateTexture = glnvg__renderUpdateTexture;
	params.renderGetTextureSize = glnvg__renderGetTextureSize;
	params.renderViewport = glnvg__renderViewport;
	params.renderCancel = glnvg__renderCancel;
	params.renderFlush = glnvg__renderFlush;
	params.renderFill = glnvg__renderFill;
	params.renderStroke = glnvg__renderStroke;
	params.renderTriangles = glnvg__renderTriangles;
	params.renderDelete = glnvg__renderDelete;
	params.userPtr = gl;
	params.edgeAntiAlias = flags & NVG_ANTIALIAS ? 1 : 0;

	gl->flags = flags;

	ctx = nvgCreateInternal(&params);
	if(ctx == NULL) goto error;

	return ctx;

error:
	// 'gl' is freed by nvgDeleteInternal.
	if(ctx != NULL) nvgDeleteInternal(ctx);
	return NULL;
}

#if defined NANOVG_GL2
void nvgDeleteGL2(NVGcontext* ctx)
#elif defined NANOVG_GL3
void nvgDeleteGL3(NVGcontext* ctx)
#elif defined NANOVG_GLES2
void nvgDeleteGLES2(NVGcontext* ctx)
#elif defined NANOVG_GLES3
void nvgDeleteGLES3(NVGcontext* ctx)
#endif
{
	nvgDeleteInternal(ctx);
}

#if defined NANOVG_GL2
int nvglCreateImageFromHandleGL2(NVGcontext* ctx, GLuint textureId, int w, int h, int imageFlags, GLuint target)
#elif defined NANOVG_GL3
int nvglCreateImageFromHandleGL3(NVGcontext* ctx, GLuint textureId, int w, int h, int imageFlags, GLuint target)
#elif defined NANOVG_GLES2
int nvglCreateImageFromHandleGLES2(NVGcontext* ctx, GLuint textureId, int w, int h, int imageFlags, GLuint target)
#elif defined NANOVG_GLES3
int nvglCreateImageFromHandleGLES3(NVGcontext* ctx, GLuint textureId, int w, int h, int imageFlags, GLuint target)
#endif
{
	GLNVGcontext* gl = (GLNVGcontext*)nvgInternalParams(ctx)->userPtr;
	GLNVGtexture* tex = glnvg__allocTexture(gl);

	if(tex == NULL) return 0;

	tex->type = NVG_TEXTURE_RGBA;
	tex->tex = textureId;
	tex->flags = imageFlags;
	tex->width = w;
	tex->height = h;
	tex->target = target;

	return tex->id;
}

#if defined NANOVG_GL2
GLuint nvglImageHandleGL2(NVGcontext* ctx, int image)
#elif defined NANOVG_GL3
GLuint nvglImageHandleGL3(NVGcontext* ctx, int image)
#elif defined NANOVG_GLES2
GLuint nvglImageHandleGLES2(NVGcontext* ctx, int image)
#elif defined NANOVG_GLES3
GLuint nvglImageHandleGLES3(NVGcontext* ctx, int image)
#endif
{
	GLNVGcontext* gl = (GLNVGcontext*)nvgInternalParams(ctx)->userPtr;
	GLNVGtexture* tex = glnvg__findTexture(gl, image);
	return tex->tex;
}

#endif /* NANOVG_GL_IMPLEMENTATION */
