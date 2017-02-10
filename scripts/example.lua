-- toyui
-- toyui example application

project "example"
	kind "ConsoleApp"
    
	includedirs {
		path.join(TOYOBJ_DIR, "src"),
		path.join(TOYUI_DIR, "src"),
		path.join(TOYUI_DIR, "example"),
	}

	files {
        path.join(TOYUI_DIR, "example", "**.h"),
        path.join(TOYUI_DIR, "example", "**.cpp"),
	}
    
    defines { "TOYUI_DRAW_CACHE" }
    
    links {
		"toyobj",
		"toyui",
	}
        
    configuration { "asmjs" }
        linkoptions {
            "-s USE_WEBGL2=1",
            "-s FULL_ES3=1",
            "-s TOTAL_MEMORY=268435456",
            "--preload-file ../../../data/",
        }
    
    configuration { "not asmjs" }
        defines {
            "TOYUI_RESOURCE_PATH=\"" .. path.join(TOYUI_DIR, "data") .. "/\"",
        }
    
	configuration {}
    
    dofile(path.join(TOYUI_DIR, "scripts/context.lua"))
