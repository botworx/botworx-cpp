project "BwAgency"
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
        "../../include/bwagency/**.h",
    }
    
    configuration { "Debug" }
        targetname "BwAgency"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwAgency"
        kind    "StaticLib"