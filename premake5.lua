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
IncludeDir["tinyobjloader"] = "RodskaEngine/vendor/tinyobjloader"
IncludeDir["entt"] = "RodskaEngine/vendor/entt/include"
IncludeDir["yamlcpp"] = "RodskaEngine/vendor/yaml-cpp/include"

group "Dependencies"
	include "RodskaEngine/vendor/GLFW"
	include "RodskaEngine/vendor/GLAD"
	include "RodskaEngine/vendor/imgui"
	include "RodskaEngine/vendor/tinyobjloader"
	include "RodskaEngine/vendor/yaml-cpp"


group ""

project "RodskaEngine"
	location "RodskaEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	pchheader "rdskpch.h"
	pchsource "RodskaEngine/src/rdskpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",

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
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.tinyobjloader}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yamlcpp}"
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
		"tinyobjloader",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RDSK_PLATFORM_WINDOWS",
			"RDSK_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"RDSK_DYNAMIC_LINK"
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

project "RodskaEditor"
	location "RodskaEditor"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	staticruntime "off"
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
		"%{IncludeDir.entt}",
		"%{IncludeDir.yamlcpp}"

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

group "Modules"
	project "ScriptCore"
		location "ScriptCore"
		kind "SharedLib"
		language "C++"
		staticruntime "off"
		cppdialect "C++17"
	
		targetdir ("RodskaEditor/plugins")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
		files 
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.hpp"
		}
	
		includedirs
		{
			"RodskaEngine/src",
			"RodskaEngine/vendor/spdlog/include",
			"%{IncludeDir.glm}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.entt}",
			"%{IncludeDir.yamlcpp}"
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
				"RDSK_MOD_BUILD_DLL",
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
	