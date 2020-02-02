project "BwAi"
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".", 
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
        "../../include/bwai/*.h",
    }
    
    configuration { "Debug" }
        targetname "BwAi"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwAi"
        kind    "StaticLib"