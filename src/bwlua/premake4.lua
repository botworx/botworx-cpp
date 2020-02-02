project "BwLua"
    --pchheader "stdafx.h"
    --pchsource "stdafx.cpp"
    includedirs {
        ".",
        "./lua",
        "../../dependencies/include"
    }
    files {
        "**.c",
        "**.cpp",
        "**.h",
        "**.hpp",
        "../../include/bwlua/*.h",
    }
    excludes { "lua/lua.c", "lua/luac.c" }
    
    configuration { "Debug" }
        targetname "BwLua"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwLua"
        kind    "StaticLib"