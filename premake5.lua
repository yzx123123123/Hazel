workspace "Hazel"
    architecture "x64"
    startproject "Sandbox"
    configurations
    {
        "DeBug",
        "Release",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


--  include directories relative to root folder (solution directory)
IncludeDir ={}
IncludeDir["GLFW"] ="Hazel/vendor/GLFW/include"
IncludeDir["Glad"] ="Hazel/vendor/Glad/include"
IncludeDir["ImGui"] ="Hazel/vendor/imgui"
IncludeDir["glm"] ="Hazel/vendor/glm"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"




project "Hazel"
     location "Hazel"
     kind "SharedLib"
     language "C++"
     staticruntime "off"

     targetdir("bin/" .. outputdir .. "/%{prj.name}")
     objdir("bin-int/" .. outputdir .. "/%{prj.name}")

     pchheader "hzpch.h"
     pchsource "Hazel/src/hzpch.cpp"

     files
     {
         "%{prj.name}/src/**.h",
         "%{prj.name}/src/**.cpp",
         "%{prj.name}/vendor/glm/glm/**.hpp",
		 "%{prj.name}/vendor/glm/glm/**.inl",
     }

     includedirs
     {
         "%{prj.name}/src",
         "%{prj.name}/vendor/spdlog/include",
         "%{IncludeDir.GLFW}",
         "%{IncludeDir.Glad}",
         "%{IncludeDir.ImGui}",
         "%{IncludeDir.glm}"
     }

     links{
         "GLFW",
         "Glad",
         "ImGui",
         "opengl32.lib"
     }

     filter "system:windows"
     cppdialect "C++17"
     --staticruntime "On"
     systemversion "latest"
     buildoptions { "/utf-8" }


     defines{
         "HZ_PLATFORM_WINDOWS",
         "HZ_BUILD_DLL",
         "GLFW_INCLUDE_NONE"
     }

     postbuildcommands
     {
        -- ("{COPY} %{cfg.buildtarget.relpath} \" ../bin/"  .. outputdir .. "/Sandbox")
        ("{COPY} %{cfg.buildtarget.relpath} \"../bin/"  .. outputdir .. "/Sandbox/\"")
     }

     filter "configurations:Debug"
        defines "HZ_DEBUG"
        --buildoptions "/MDd"
        runtime "Debug"
        symbols "On"
      

     filter "configurations:Release"
        defines "HZ_RELEASE"
        --buildoptions "/MDd"
        runtime "Release"
        optimize "On"

     filter "configurations:Dist"
        defines "HZ_DIST"
       -- buildoptions "/MDd"
        runtime "Release"
        optimize "On"



project "Sandbox"
     location "Sandbox"
     kind "ConsoleApp"

     language "C++"
     staticruntime "off"

     targetdir("bin/" .. outputdir .. "/%{prj.name}")
     objdir("bin-int/" .. outputdir .. "/%{prj.name}")

     files
     {
         "%{prj.name}/src/**.h",
         "%{prj.name}/src/**.cpp"
     }

     includedirs
     {
         "Hazel/vendor/spdlog/include",
         "Hazel/src",
         --"%{IncludeDir.ImGui}",
         "%{IncludeDir.glm}"

     }
     
     links{
         "Hazel"
     }

     filter "system:windows"
     cppdialect "C++17"
    -- staticruntime "On"
     systemversion "10.0.22621.0"
     buildoptions { "/utf-8" }


     defines{
         "HZ_PLATFORM_WINDOWS"
         
     }

     

     filter "configurations:Debug"
        defines "HZ_DEBUG"
       -- buildoptions "/MDd"
       runtime "Debug"
        symbols "On"
      

     filter "configurations:Release"
        defines "HZ_RELEASE"
       -- buildoptions "/MDd"
        runtime "Release"
        optimize "On"

     filter "configurations:Dist"
        defines "HZ_DIST"
       -- buildoptions "/MDd"
        runtime "Release"
        optimize "On"