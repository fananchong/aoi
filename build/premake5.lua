workspace "aoi"
    configurations { "Debug", "Release" }
    platforms { "x32", "x64" }
    targetdir "../bin/"
    objdir "obj/%{cfg.platform}/%{cfg.buildcfg}"
    language "C++"
    includedirs {
        "..",
    }
    flags {
        "C++11",
        "StaticRuntime",
    }

    filter "configurations:Debug"
    defines { "_DEBUG" }
    symbols "On"
    libdirs { }
    filter "configurations:Release"
    defines { "NDEBUG" }
    libdirs { }
    optimize "On"
    filter { }  
    
    
    
project "aoi"
    kind "StaticLib"
    targetname "aoi"
    files {
        "../*.h",
        "../impl/*.h",
    }
    
project "test1"
    kind "ConsoleApp"
    targetname "test1"
    libdirs { "../../bin" }
    files {
        "../tests/test1/*.h",
        "../tests/test1/*.cpp",
    }
    
project "test2"
    kind "ConsoleApp"
    targetname "test2"
    libdirs { "../../bin" }
    files {
        "../tests/test2/*.h",
        "../tests/test2/*.cpp",
    }
    