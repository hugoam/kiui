-- toy engine
-- toy ui module

project "toyui"
	kind "SharedLib"
	--kind "StaticLib"

	includedirs {
		path.join(TOYOBJ_DIR, "src"),
		path.join(TOYUI_DIR,  "src"),
		path.join(TOYUI_3RDPARTY_DIR, "stb"),
		path.join(TOYUI_3RDPARTY_DIR, "glfw", "include"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "include"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "win32"),
		path.join(TOY_NANOVG_DIR, "src"),
	}

	files {
        path.join(TOYUI_DIR, "src", "**.h"),
        path.join(TOYUI_DIR, "src", "**.cpp"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "src", "*.c"),
        path.join(TOY_NANOVG_DIR, "src", "nanovg.c"),
	}
       
    defines { "UI_EXPORT" }
    
    defines {
        "NANOVG_GLEW",
        "HAVE_CONFIG_H",
        "YAML_DECLARE_STATIC",
    }
    
    links {
		"toyobj",
        "OpenGL32",
	}
    
    configuration { "not context-native or not windows" }
        removefiles {
            path.join(TOYUI_DIR, "src/toyui/Context/WindowsContext.h"),
            path.join(TOYUI_DIR, "src/toyui/Context/WindowsContext.cpp"),
        }
        
    configuration { "not context-glfw" }
        removefiles {
            path.join(TOYUI_DIR, "src/toyui/Context/GlfwContext.h"),
            path.join(TOYUI_DIR, "src/toyui/Context/GlfwContext.cpp"),
        }
        
    configuration { "context-glfw" }
        links {
            "glfw3",
            "glew32",
        }
        
    configuration { "not asmjs" }
        removefiles {
            path.join(TOYUI_DIR, "src/toyui/Context/EmscriptenContext.h"),
            path.join(TOYUI_DIR, "src/toyui/Context/EmscriptenContext.cpp"),
        }
        
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
