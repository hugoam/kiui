-- toyui library

solution "toyui"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64"
	}

	language "C++"
    
    
BUILD_DIR = path.join(path.getabsolute(".."), "build")

dofile("../../toyobj/scripts/toytoolchain.lua")

dofile "../../toyobj/scripts/toyobj.lua"
dofile "toyui.lua"
dofile "example.lua"
