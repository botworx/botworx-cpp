
-- local wxpath = os.getenv("WXWIN")
-- local boostpath = os.getenv("BOOST_ROOT")

project "Botworx"
    -- defines { "WXUSINGDLL", "wxMSVC_VERSION_AUTO", "_UNICODE", "UNICODE" }
    -- defines { "wxMSVC_VERSION_AUTO", "_UNICODE", "UNICODE" }
    -- flags { "WinMain" }
    pchheader "stdafx.h"
    pchsource "stdafx.cpp"
    includedirs {
        ".",
        "../../dependencies/include",
        -- wxpath .. "/include",
        -- wxpath .. "/include/msvc"
    }
    files {
        "stdafx.cpp",
        "**.cpp",
        "**.h",
        "../../include/bwbotworx/**.h"
    }
    wx_config {Unicode="yes", Version="3.0", Libs="core, base, adv, xml, aui, stc"}
    targetdir "../../bin"
    links { "BwAgency", "BwMia", "BwAxl", "BwAi", "BwCore", "BwLua", "boost_system", "boost_thread", "pthread", "boost_serialization", "boost_filesystem" }
    libdirs {
      --"C:/AAA/DevDepends/boost_1_51/lib",
      -- boostpath .. "/stage/lib",
      --"C:/AAA/DevDepends/wxWidgets/lib/vc100_dll"
      -- wxpath .. "/lib/vc110_x64_lib"
    }
    configuration { "Debug" }
        targetname "Botworx"
        kind    "WindowedApp"
        --includedirs {
        --    wxpath .. "/lib/vc_ia64_lib/mswud"
        --}
	  
    configuration { "Release" }
        targetname "Botworx"
        kind    "WindowedApp"
        --includedirs {
        --   wxpath .. "/lib/vc_lib/mswu"
        --}
        