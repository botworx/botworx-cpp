
local ogrepath = os.getenv("OGRE_HOME")
local odepath = "C:/AAA/DevDepends/ode"
local bulletpath = "C:/AAA/DevDepends/bullet"
local openmeshpath = "/home/kurt/Deps/OpenMesh"

project "BwVr"
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
        "../../include/bwvr/**.h",
    }
    
    configuration { "Debug" }
        targetname "BwVr"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwVr"
        kind    "StaticLib"
