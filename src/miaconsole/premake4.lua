
-- local boostpath = os.getenv("BOOST_ROOT")

project "MiaConsole"
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
    -- links { "BwCore", "BwAi", "BwAxl", "BwMia", "BwLua" }
    links { "BwMia", "BwAxl", "BwAi", "BwCore", "BwLua", "boost_system", "boost_thread", "pthread", "boost_serialization", "boost_filesystem" }
    libdirs {
      -- boostpath .. "/stage/lib",
      }
    configuration { "Debug" }
        targetname "MiaConsole"
        kind    "ConsoleApp"
	  
	configuration { "Release" }
        targetname "MiaConsole"
        kind    "ConsoleApp"