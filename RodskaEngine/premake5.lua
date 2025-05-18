project "RodskaEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	pchheader "rdskpch.h"
	pchsource "%{wks.location}/RodskaEngine/src/rdskpch.cpp"




	files 
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",

		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/ImGuizmo/**.h",
		"vendor/ImGuizmo/**.cpp",

	}

	includedirs
	{
		"%{wks.location}/%{prj.name}/src",
		"%{wks.location}/%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.tinyobjloader}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yamlcpp}",
		"%{IncludeDir.DirectXTK}",
		"%{IncludeDir.mono}"


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
		"opengl32.lib",
		"runtimeobject.lib",
		"%{LibDir.mono}/libmono-static-sgen.lib",

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

		links {
			"Ws2_32.lib",
			"Winmm.lib",
			"Version.lib",
			"Bcrypt.lib"
		}

		includedirs {

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

	filter("files:vendor/ImGuizmo/**.cpp")
		flags { "NoPCH" }
	