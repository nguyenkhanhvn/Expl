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
IncludeDir["spdlog"] = "Expl/vendor/spdlog/include"
IncludeDir["glfw"] = "Expl/vendor/glfw/include"
IncludeDir["glad"] = "Expl/vendor/glad/include"
IncludeDir["imgui"] = "Expl/vendor/imgui"
IncludeDir["glm"] = "Expl/vendor/glm"
IncludeDir["stb"] = "Expl/vendor/stb"
IncludeDir["json"] = "Expl/vendor/json"

include "Expl/vendor/glfw"
include "Expl/vendor/glad"
include "Expl/vendor/imgui"

project "Expl"
	location "Expl"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.json}",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
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
			"GLFW_INCLUDE_NONE",
		}


	filter "configurations:Debug"
		defines "EX_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "EX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EX_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Expl/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.json}",
	}

	links
	{
		"Expl",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "EX_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "EX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EX_DIST"
		runtime "Release"
		optimize "on"
