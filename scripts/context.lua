        
    configuration { "context-native", "windows" }
        files {
            path.join(TOYUI_DIR, "src/toyui/Context/Windows/**.h"),
            path.join(TOYUI_DIR, "src/toyui/Context/Windows/**.cpp"),
        }
        
    configuration { "asmjs" }
        files {
            path.join(TOYUI_DIR, "src/toyui/Context/Esmcripten/**.h"),
            path.join(TOYUI_DIR, "src/toyui/Context/Emscripten/**.cpp"),
        }
        
    configuration { "context-glfw" }
        includedirs {
            path.join(TOYUI_3RDPARTY_DIR, "glfw", "include"),
        }
    
        files {
            path.join(TOYUI_DIR, "src/toyui/Context/Glfw/**.h"),
            path.join(TOYUI_DIR, "src/toyui/Context/Glfw/**.cpp"),
        }

        links {
            "glfw3",
        }
        
    configuration { "context-ogre" }
        removeflags {
            "NoRTTI",
            "NoExceptions",
        }
        
        includedirs {
            path.join(BUILD_DIR, "ogre"),
            path.join(OGRE_DIR, "OgreMain", "include"),
            path.join(TOY_3RDPARTY_DIR, "OIS", "includes"),
        }
        
        files {
            path.join(TOYUI_DIR, "src/toyui/Context/Ogre/**.h"),
            path.join(TOYUI_DIR, "src/toyui/Context/Ogre/**.cpp"),
        }
        
        links {
            "ogre",
            "ois",
        }
        
    configuration { "context-ogre", "windows" }
        links {
            "dxguid",
            "dinput8",
        }
