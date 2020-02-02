project "BwMia"
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".",
        "../../dependencies/include",
        "../../dependencies/include/lua"
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
        "../../include/bwmia/**.h"
    }
    
    configuration { "Debug" }
        targetname "BwMia"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwMia"
        kind    "StaticLib"