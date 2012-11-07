solution "template"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include" }
files { "include/**.h" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }
targetdir "build/debug"

configuration "Release"
defines { "NDEBUG" }
flags { "OptimizeSpeed",
	"ExtraWarnings",
	"FatalWarnings",
	"NoFramePointer" }
targetdir "build/release"

project "template"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "template" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
