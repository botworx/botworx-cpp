project "BwSteer"
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
        "../../include/bwsteer/*.h",
    }
    
    configuration { "Debug" }
        targetname "BwSteer"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwSteer"
        kind    "StaticLib"