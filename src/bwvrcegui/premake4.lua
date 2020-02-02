
local ogrepath = os.getenv("OGRE_HOME")
local odepath = "C:/AAA/DevDepends/ode"
local ceguipath = "C:/AAA/DevDepends/CEGUI"

project "BwVrCegui"
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".",
        "../../dependencies/include",
        "/usr/include/cegui-0.8.7",
        -- ogrepath .. "/include",
        -- ogrepath .. "/include/OGRE",
        -- odepath .. "/include",
        -- ceguipath .. "/cegui/include"
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
        "../../include/bwvrcegui/**.h",
    }
    
    configuration { "Debug" }
        targetname "BwVrCegui"
        kind    "StaticLib"
	  
	configuration { "Release" }
        targetname "BwVrCegui"
        kind    "StaticLib"
