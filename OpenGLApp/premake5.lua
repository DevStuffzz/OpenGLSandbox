project "OpenGLApp"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.cpp", "**.hpp" }

   includedirs
   {
      "../vendor/imgui",
      "../vendor/glfw/include",
      "../vendor/glm/",
      "../vendor/glad/include/"
   }

   
	links 
	{ 
		"GLFW",
      "Glad",
      "ImGui",
		"opengl32.lib"
	}

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      defines { "_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"