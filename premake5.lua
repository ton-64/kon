newoption {
  trigger = "include-sandbox",
  description = "Include sandbox in the generated workspace"
}

newoption {
  trigger = "sokol-experimental",
  description = "Enable Sokol experimental features"
}

workspace "kon_workspace"
  configurations { "debug", "release" }
  targetdir "bin/%{cfg.buildcfg}"
  objdir "bin/obj/%{cfg.buildcfg}"

project "kon"
  kind "StaticLib"
  language "C"
  cdialect "C99"
  
  files {
    "src/**.h",
    "src/**.c"
  }

  includedirs {
    "deps"
  }
  
  filter "configurations:debug"
    defines { "KON_DEBUG" }
    symbols "On"
    optimize "Off"

  filter "configurations:release"
    defines { "KON_RELEASE" }
    optimize "Speed"

  filter { "options:sokol-experimental" }
    defines { "KON_SOKOL_EXPERIMENTAL" }

-- Unix systems wont link the needed dependencies of a library 
function kon_linkSys()
  filter { "system:windows or system:linux or system:bsd ", "options:sokol-experimental" }
    links { "vulkan" }

  filter { "system:windows or system:linux or system:bsd", "options:not sokol-experimental" }
    links { "GL" }

  filter { "system:linux or system:bsd" }
    links {
      "pthread",
      "dl",
      "m",
      
      "X11",
      "Xi",
      "Xcursor",
      "Xrandr"
    }
          
  filter {}
end

  kon_linkSys()

filter { "options:include-sandbox" }
  project "kon_sandbox"
    kind "ConsoleApp"
    language "C"
    cdialect "C99"
    
    files {
      "sandbox/src/**.h",
      "sandbox/src/**.c"
    }

    includedirs {
      "src",
      "deps"
    }

    links {
      "kon"
    }
    kon_linkSys()
