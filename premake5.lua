workspace "RodskaEngine"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}	

outputdir =  "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
LibDir = {}

monoArch = "x64"

LibDir["mono"] = "%{wks.location}/RodskaEngine/vendor/mono/msvc/build/sgen/%{monoArch}/lib/%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["GLFW"] = "RodskaEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "RodskaEngine/vendor/GLAD/include"
IncludeDir["imgui"] = "RodskaEngine/vendor/imgui"
IncludeDir["glm"] = "RodskaEngine/vendor/glm"
IncludeDir["stb_image"] = "RodskaEngine/vendor/stb_image"
IncludeDir["tinyobjloader"] = "RodskaEngine/vendor/tinyobjloader"
IncludeDir["entt"] = "RodskaEngine/vendor/entt/include"
IncludeDir["yamlcpp"] = "RodskaEngine/vendor/yaml-cpp/include"
IncludeDir["cmdparser"] = "RodskaEngine/vendor/cmdparser"
IncludeDir["pythonw"] = "C:/Program Files/Python38/Include"
IncludeDir["DirectXTK"] = "RodskaEngine/vendor/DirectXTK/Inc"
IncludeDir["ImGuizmo"] = "RodskaEngine/vendor/ImGuizmo"
IncludeDir["mono"] = "RodskaEngine/vendor/mono/msvc/include"

group "Dependencies"
	include "RodskaEngine/vendor/GLFW"
	include "RodskaEngine/vendor/GLAD"
	include "RodskaEngine/vendor/imgui"
	include "RodskaEngine/vendor/tinyobjloader"
	include "RodskaEngine/vendor/yaml-cpp"
	group "DirectX"
		externalproject "DirectXTK_Desktop_2022"
			location "RodskaEngine/vendor/DirectXTK"
			uuid "8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942"
			kind "StaticLib"
			language "C++"
		externalproject "DirectXTK_Desktop_2022_Win10"
			location "RodskaEngine/vendor/DirectXTK"
			uuid "E0B52AE7-E160-4D32-BF3F-910B785E5A8E"
			kind "StaticLib"
			language "C++"
			
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
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/**.h",
		"%{prj.name}/vendor/ImGuizmo/**.cpp",

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
		"%{IncludeDir.yamlcpp}",
		"%{IncludeDir.DirectXTK}",
		"%{IncludeDir.ImGuizmo}",
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
		"C:/Program Files/Python38/libs/python38_d.lib",
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
			"%{IncludeDir.pythonw}"
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

	filter("files:RodskaEngine/vendor/ImGuizmo/**.cpp")
		flags { "NoPCH" }
	


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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/assets/shaders/DirectX/**.hlsl"
	}



	includedirs
	{
		"RodskaEngine/vendor/spdlog/include",
		"RodskaEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yamlcpp}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.mono}"

	}

	links 
	{
		"RodskaEngine",
	}

	defines {
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

		filter("files:**Shader11.hlsl")
			local shader_dir = "%{prj.name}/assets/shaders/DirectX"
			shadermodel("5.0")
			shaderassembler("AssemblyCode")
			shaderobjectfileoutput(shader_dir.."/compiled/%{file.basename}"..".11.cso")
			shaderassembleroutput(shader_dir.."/compiled/%{file.basename}"..".11.asm")
			filter("files:**PixelShader11.hlsl")		
				removeflags("ExcludeFromBuild")
				shadertype("Pixel")

			filter("files:**VertexShader11.hlsl")
				removeflags("ExcludeFromBuild")
				shadertype("Vertex")
			
			shaderoptions({"/WX"})
	
	filter("files:**Shader12.hlsl")
			local shader_dir = "%{prj.name}/assets/shaders/DirectX"
			shadermodel("5.1")
			shaderassembler("AssemblyCode")
			shaderobjectfileoutput(shader_dir.."/compiled/%{file.basename}"..".12.cso")
			shaderassembleroutput(shader_dir.."/compiled/%{file.basename}"..".12.asm")
			filter("files:**PixelShader12.hlsl")		
				shadertype("Pixel")

			filter("files:**VertexShader12.hlsl")
				shadertype("Vertex")
			
			shaderoptions({"/WX"})

group "Modules"
	project "ScriptCore"
		location "Rodska-ScriptCore"
		kind "SharedLib"
		language "C#"
		dotnetframework "4.7.2"
		namespace "Rodska"
	
		targetdir ("%{wks.location}/RodskaEditor/modules/Scripts")
		objdir ("%{wks.location}/RodskaEditor/modules/Scripts/Intermediates")
	
		files 
		{
			"%{wks.location}/%{cfg.location}/Source/**.cs",
			"%{wks.location}/%{cfg.location}/Properties/**.cs",

		}
	
		filter "configurations:Debug"
			optimize "Off"
			symbols "Default"

		filter "configurations:Release"
			optimize "On"
			symbols "Default"

		filter "configurations:Dist"
			optimize "Full"
			symbols "Off"