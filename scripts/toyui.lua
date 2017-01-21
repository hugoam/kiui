-- toy engine
-- toy ui module

project "toyui"
	kind "SharedLib"

	includedirs {
		path.join(TOYOBJ_DIR, "src"),
		path.join(TOYUI_DIR,  "src"),
		path.join(TOYUI_3RDPARTY_DIR, "stb"),
		path.join(TOYUI_3RDPARTY_DIR, "nanovg", "src"),
		path.join(TOYUI_3RDPARTY_DIR, "glfw", "include"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "include"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "win32"),
	}

	files {
        path.join(TOYUI_DIR, "src", "Ui", "**.h"),
        path.join(TOYUI_DIR, "src", "Ui", "**.cpp"),
		path.join(TOYUI_3RDPARTY_DIR, "nanovg", "src", "nanovg.c"),
		path.join(TOYUI_3RDPARTY_DIR, "yaml", "src", "*.c"),
	}
                        
    defines { "UI_EXPORT" }
    
    defines {
        "HAVE_CONFIG_H",
        "YAML_DECLARE_STATIC",
    }
    
    links {
		"toyobj",
	}
    
    configuration { "not toyui-gl" }
        removefiles {
            path.join(TOYUI_DIR, "src", "Ui", "Gl", "**.h"),
            path.join(TOYUI_DIR, "src", "Ui", "Gl", "**.cpp"),
        }
        
    
    configuration { "toyui-gl" }
        links {
            "glfw3",
            "OpenGL32",
        }

	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
