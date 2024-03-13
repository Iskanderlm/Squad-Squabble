workspace "Squad-Squabble"
    location ""
    language "c++"
    cppdialect "c++20"
    platforms { "x64" }
    configurations { "Debug", "Release" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"  


project "Squad-Squabble"
    kind "ConsoleApp"
    location "Build"
    targetdir "bin"
    objdir    "bin/obj"
    defines { "SFML_STATIC" }
    files{ "Source/**.cpp", "Source/**.h" }
    debugdir ""

    includedirs {"SFML/include"}

    libdirs {"SFML/lib"}

    links {
        "opengl32",
        "openal32",
        "freetype",
        "winmm",
        "gdi32",
        "flac",
        "vorbisenc",
        "vorbisfile",
        "vorbis",
        "ogg",
        "ws2_32"
    }

    filter "configurations:Debug"
        links {
            "sfml-audio-s-d",
            "sfml-graphics-s-d",
            "sfml-network-s-d",
            "sfml-system-s-d",
            "sfml-window-s-d"
        }

    filter "configurations:Release"
        links { 
            "sfml-audio-s",
            "sfml-graphics-s",
            "sfml-network-s",
            "sfml-system-s",
            "sfml-window-s"
        }   

    filter ""