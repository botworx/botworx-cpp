project "BwMath"
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".",
        "../../dependencies/include"
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
        "../../include/bwmath/**.h",
    }
    
    configuration { "Debug" }
        targetname "BwMath"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwMath"
        kind    "StaticLib"