workspace "Expl"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "Expl/vendor/glfw/include"
IncludeDir["glad"] = "Expl/vendor/glad/include"
IncludeDir["imgui"] = "Expl/vendor/imgui"

include "Expl/vendor/glfw"
include "Expl/vendor/glad"
include "Expl/vendor/imgui"

project "Expl"
	location "Expl"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

	pchheader "explpch.h"
	pchsource "Expl/src/explpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
	}

	links
	{
		"glfw",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS",
			"EX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../Binaries/" .. outputdir .. "/Sandbox/\"")
		}


	filter "configurations:Debug"
		defines "EX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "EX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EX_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Expl/vendor/spdlog/include",
		"Expl/src"
	}

	links
	{
		"Expl"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "EX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EX_DIST"
		runtime "Release"
		optimize "On"
