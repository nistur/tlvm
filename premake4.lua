solution "template"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

defines { "TMPL_BUILD" }

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

project "template-dynamic"
kind "SharedLib"
files { "src/**.c", "src/**.cpp" }
targetname "template"

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "template" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
