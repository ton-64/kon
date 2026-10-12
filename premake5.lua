workspace "kon_workspace"
  configurations { "debug", "release" }
  targetdir "bin/%{cfg.buildcfg}"
  objdir "bin/obj/%{cfg.buildcfg}"

project "kon"
  kind "SharedLib"
  language "C"
  cdialect "C99"
    
  files {
    "src/**.h",
    "src/**.c"
  }

  filter "configurations:debug"
    symbols "On"
    optimize "Off"

  filter "configurations:release"
    defines { "NDEBUG" }
    optimize "Speed"

  filter {}

newoption {
  trigger = "with-sandbox",
  description = "Include sandbox in the generated workspace"
}

if _OPTIONS["with-sandbox"] then
  project "kon_sandbox"
    kind "ConsoleApp"
    language "C"
    cdialect "C99"

    files {
      "sandbox/src/**.h",
      "sandbox/src/**.c"
    }

    includedirs {
      "src"
    }

    links { "kon" }
end
