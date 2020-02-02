project "BwCore"
    pchheader "stdafx.h"
	--pchheader "../../src/bwcore/stdafx.h"
    pchsource "stdafx.cpp"
    includedirs { "." }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h", 

        "../../include/bwapplet/**.h",
        "../../include/bwcontrol/**.h",
        "../../include/bwcore/**.h",
        "../../include/bwdocument/**.h",
        "../../include/bwesp/**.h",
        "../../include/bwmessaging/**.h",
        "../../include/bwscheduling/**.h",
        "../../include/bwstd/**.h",
    }
    
    configuration { "Debug" }
        targetname "BwCore"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwCore"
        kind    "StaticLib"