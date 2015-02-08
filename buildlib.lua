

project "tlvm"
language "C"
kind "StaticLib"
defines { "TLVM_DEBUG" } -- this is not debug symbols, this is the interface for the tlvm debugger
files { "src/**.c", "src/**.cpp" }

project "tlvm-lite"
language "C"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }

--project "tlvm-dynamic"
--kind "SharedLib"
--files { "src/**.c", "src/**.cpp" }
--targetname "tlvm"