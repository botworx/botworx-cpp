
local ogrepath = os.getenv("OGRE_HOME")
local odepath = "C:/AAA/DevDepends/ode"
local bulletpath = "C:/AAA/DevDepends/bullet"
local ceguipath = "C:/AAA/DevDepends/CEGUI"
local openmeshpath = "/home/kurt/Deps/OpenMesh"

project "BuggyBotsApp"
    -- flags { "WinMain" }
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".",
        "./include",
        "../../dependencies/include",
        "/usr/include/cegui-0.8.7",
        openmeshpath .. "/src"
        -- ogrepath .. "/include/OGRE",
        -- odepath .. "/include",
        -- bulletpath .. "/src",
        -- ceguipath .. "/cegui/include"
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h"
    }
    targetdir "../../bin"
    links { 
        "BuggyBots",
        "BwVrCegui",
        "BwVr", 
        "BwSteer",
        "BwMath", 
        "BwCore",
        "BwLua",
        "boost_system",
        "boost_thread",
        "pthread",
        "boost_serialization",
        "boost_filesystem",
        "ode",
        "OgreMain",
        "CEGUIBase-0",
        "CEGUIOgreRenderer-0",
        "OIS",
        "OpenMeshCore"
    }
    libdirs {
        -- "C:/AAA/DevDepends/boost_1_51/lib",
        -- "C:/AAA/DevDepends/wxWidgets/lib/vc100_dll",
        -- ogrepath .. "/lib",
        -- ceguipath .. "/lib",
        -- bulletpath .. "/lib",
        openmeshpath .. "/build/Build/lib"
    }
    configuration { "Debug" }
        targetname "BuggyBotsApp"
        kind    "WindowedApp"
        links {
            -- "OgreMain_d",
            -- "OIS_d",
            -- "CEGUIBase_d",
            -- "CEGUIOgreRenderer_d",
            -- "ode_singled",
            -- "BulletCollision_vs2010_debug",
            -- "LinearMath_vs2010_debug",
            -- "libOpenMeshCored"
        }        
        libdirs {
            -- odepath .. "/lib/DebugSingle"
        }
        
	  
	configuration { "Release" }
        targetname "BuggyBotsApp"
        kind    "WindowedApp"