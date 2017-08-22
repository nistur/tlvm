--[[
Copyright (c) 2015 Philipp Geyer

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Philipp Geyer
nistur@gmail.com
--]]
if os.is("macosx") then
    premake.tools.gcc.ldflags.flags = nil
end

solution "tlvm"
    configurations { "Debug", "Release" }
    includedirs { "include", "src/include" }
    files { "include/**.h" }
    
    defines { "TLVM_BUILD" }
    
    tlvmcpus = {
       cpu_8080 = true,
       cpu_6800 = false,
       cpu_6303 = false,
    }
    
    for cpu,x in pairs(tlvmcpus) do 
       if x then
          defines {  "TLVM_HAS_" .. cpu:gsub("cpu_", "") }
       end
    end
    
    configuration "Debug"
        defines { "DEBUG" }
        --optimize "Debug"
        flags { "Symbols" }
        targetdir "build/debug"

    configuration "Release"
        defines { "NDEBUG" }
        optimize "Size"
        warnings "Extra"
        flags { "FatalWarnings",
                "NoFramePointer" }
        targetdir "build/release"


	
    dofile("buildlib.lua")

    project "tests"
        language "C++"
        kind "ConsoleApp"
        files { "tests/testsuite/**.cpp" }

        for cpu,x in pairs(tlvmcpus) do 
           if x then
              files{ "tests/" .. cpu:gsub("cpu_", "") .. "/*.cpp" }
           end
        end

        links { "tlvm" }
        defines { "TEST_MAX_TEST=128", "TEST_MAX_GROUP=32" }
        configuration "Debug"
            postbuildcommands("build/debug/tests")
        configuration "Release"
            postbuildcommands("build/release/tests")

    project "tlvm-dbg"
        language "C++"
        kind "ConsoleApp"
        files { "dbg/**.cpp" }
        links { "tlvm", "pthread", "stdc++" }
        defines { "TLVM_DEBUG" }
        
    -- this is 8080 only
    if tlvmcpus.cpu_8080 then
       project "tlvm-dasm"
           language "C++"
           kind "ConsoleApp"
           files { "dasm/**.cpp" }
           links { "tlvm", "pthread" }
           defines { "TLVM_DEBUG" }
    end
