project "BwAxl"
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".", 
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
        "../../include/bwaxl/**.h",
    }
    
    configuration { "Debug" }
        targetname "BwAxl"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwAxl"
        kind    "StaticLib"