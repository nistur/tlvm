solution "tlvm"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

defines { "TLVM_BUILD" }

-- Processor specific defines
defines { "TLVM_HAS_8080" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }
targetdir "build/debug"

configuration "Release"
defines { "NDEBUG" }
flags { "OptimizeSize",
	"ExtraWarnings",
	"FatalWarnings",
	"NoFramePointer" }
targetdir "build/release"

project "tlvm"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }

--project "tlvm-dynamic"
--kind "SharedLib"
--files { "src/**.c", "src/**.cpp" }
--targetname "tlvm"

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "tlvm" }
defines { "TEST_MAX_TEST=128", "TEST_MAX_GROUP=32" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
