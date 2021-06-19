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

include "RodskaEngine/vendor/GLFW"
include "RodskaEngine/vendor/GLAD"
include "RodskaEngine/vendor/imgui"

project "RodskaEngine"
	location "RodskaEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	pchheader "rdskpch.h"
	pchsource "RodskaEngine/src/rdskpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
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
		"%{IncludeDir.glm}"
	}

	links 
	{
		"GLFW",
		"GLAD",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RDSK_PLATFORM_WINDOWS",
			"RDSK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/TestingSandbox")
		}

	filter "configurations:Debug"
		defines "RDSK_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "RDSK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RDSK_DIST"
		optimize "On"

project "TestingSandbox"
	location "TestingSandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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
		"%{IncludeDir.imgui}",

	}

	links 
	{
		"RodskaEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RDSK_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "RDSK_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "RDSK_RELEASE"
		buildoptions "/MDd"
		optimize "On"

	filter "configurations:Dist"
		defines "RDSK_DIST"
		buildoptions "/MDd"
		optimize "On"