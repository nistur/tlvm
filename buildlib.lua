
local function addfiles()
   files { "src/*.c" }
   
   for cpu,x in pairs(tlvmcpus) do 
      if x then
         files{ "src/" .. cpu:gsub("cpu_", "") .. "/*.c" }
      end
   end

end

project "tlvm"
    language "C"
    kind "StaticLib"
    defines { "TLVM_DEBUG" } -- this is not debug symbols, this is the interface for the tlvm debugger
    includedirs { "include", "src/include" }
    addfiles()

project "tlvm-lite"
    language "C"
    kind "StaticLib"
    includedirs { "include", "src/include" }
    addfiles()
    excludes{ "src/debug.c", "src/8080/8080_debug.c" }
    configuration "Release"
    defines{ "TLVM_UNSAFE" }

--project "tlvm-dynamic"
--kind "SharedLib"
--files { "src/**.c", "src/**.cpp" }
--targetname "tlvm"