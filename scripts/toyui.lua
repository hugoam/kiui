-- toy engine
-- toy ui module

TOY_NANOVG_DIR = path.join(TOYUI_3RDPARTY_DIR, "nanovg-layers")

project "toyui"
	kind "SharedLib"

	includedirs {
		path.join(TOYOBJ_DIR, "src"),
		path.join(TOYUI_DIR,  "src"),
		path.join(TOYUI_3RDPARTY_DIR, "stb"),
		path.join(TOYUI_3RDPARTY_DIR, "glfw", "include"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "include"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "win32"),
		path.join(TOYUI_3RDPARTY_DIR, "rectpacking"),
		path.join(TOY_NANOVG_DIR, "src"),
	}

	files {
        path.join(TOYUI_DIR, "src", "**.h"),
        path.join(TOYUI_DIR, "src", "**.cpp"),
		path.join(TOYUI_3RDPARTY_DIR, "rectpacking", "**.cpp"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "src", "*.c"),
        path.join(TOY_NANOVG_DIR, "src", "nanovg.c"),
	}
    
    removefiles {
        path.join(TOYUI_DIR, "src", "toyui/Context/**.h"),
        path.join(TOYUI_DIR, "src", "toyui/Context/**.cpp"),
    }
        
    defines { "UI_EXPORT" }
    
    defines { "TOYUI_DRAW_CACHE" }
    
    defines {
        "HAVE_CONFIG_H",
        "YAML_DECLARE_STATIC",
    }
    
    links {
		"toyobj",
        "glew32",
        "OpenGL32",
	}
    
    configuration { "not asmjs" }
        defines { "NANOVG_GLEW" }

	configuration {}
