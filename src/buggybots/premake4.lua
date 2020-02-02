
local ogrepath = os.getenv("OGRE_HOME")
local odepath = "C:/AAA/DevDepends/ode"
local bulletpath = "C:/AAA/DevDepends/bullet"
local openmeshpath = "/home/kurt/Deps/OpenMesh"

project "BuggyBots"
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".",
        "../../dependencies/include",
        openmeshpath .. "/src"
        -- ogrepath .. "/include/OGRE",
        -- odepath .. "/include",
        -- bulletpath .. "/src"
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
        "../../include/buggybots/**.h",
    }
    
    configuration { "Debug" }
        targetname "BuggyBots"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BuggyBots"
        kind    "StaticLib"
