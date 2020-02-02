
-- local boostpath = os.getenv("BOOST_ROOT")

project "AxlConsole"
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".", 
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
    }
    targetdir "../../bin"
    links { "BwAxl", "BwAi", "BwCore", "boost_system", "boost_thread", "pthread", "boost_serialization" }
    libdirs {
      -- boostpath .. "/stage/lib",
    }
    configuration { "Debug" }
        targetname "AxlConsole"
        kind    "ConsoleApp"
	  
	configuration { "Release" }
        targetname "AxlConsole"
        kind    "ConsoleApp"