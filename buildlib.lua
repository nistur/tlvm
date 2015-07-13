

project "tlvm"
language "C"
kind "StaticLib"
defines { "TLVM_DEBUG" } -- this is not debug symbols, this is the interface for the tlvm debugger
includedirs { "include", "src/include" }
files { "src/**.c", "src/**.cpp" }

project "tlvm-lite"
language "C"
kind "StaticLib"
includedirs { "include", "src/include" }
excludes{ "src/debug.c", "src/8080/8080_debug.c" }
files { "src/**.c", "src/**.cpp" }
configuration "Release"
defines{ "TLVM_UNSAFE" }

--project "tlvm-dynamic"
--kind "SharedLib"
--files { "src/**.c", "src/**.cpp" }
--targetname "tlvm"