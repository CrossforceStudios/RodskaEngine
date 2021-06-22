workspace "RodskaEngine"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}	

outputdir =  "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "RodskaEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "RodskaEngine/vendor/GLAD/include"
IncludeDir["imgui"] = "RodskaEngine/vendor/imgui"
IncludeDir["glm"] = "RodskaEngine/vendor/glm"
IncludeDir["stb_image"] = "RodskaEngine/vendor/stb_image"

group "Dependencies"
	include "RodskaEngine/vendor/GLFW"
	include "RodskaEngine/vendor/GLAD"
	include "RodskaEngine/vendor/imgui"


group ""

project "RodskaEngine"
	location "RodskaEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	pchheader "rdskpch.h"
	pchsource "RodskaEngine/src/rdskpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"

	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"

	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	links 
	{
		"GLFW",
		"GLAD",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RDSK_PLATFORM_WINDOWS",
			"RDSK_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "RDSK_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "RDSK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RDSK_DIST"
		runtime "Release"
		optimize "on"

project "TestingSandbox"
	location "TestingSandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	staticruntime "on"
	cppdialect "C++17"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"RodskaEngine/vendor/spdlog/include",
		"RodskaEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",

	}

	links 
	{
		"RodskaEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RDSK_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "RDSK_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "RDSK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RDSK_DIST"
		runtime "Release"
		optimize "on"