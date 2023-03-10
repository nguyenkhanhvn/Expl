workspace "Expl"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Shipping"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Expl"
	location "Expl"
	kind "SharedLib"
	language "C++"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS",
			"EX_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdir .. "/Sandbox")
		}


	filter "configurations:Debug"
		defines "EX_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "EX_RELEASE"
		optimize "On"

	filter "configurations:Shipping"
		defines "EX_SHIPPING"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"Expl/vendor/spdlog/include",
		"Expl/Source"
	}

	links
	{
		"Expl"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EX_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "EX_RELEASE"
		optimize "On"

	filter "configurations:Shipping"
		defines "EX_SHIPPING"
		optimize "On"
