LibDir = {}

workspace "RodskaEngine"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}	

	startproject "RodskaEditor"

outputdir =  "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

monoArch = "x64"
LibDir["mono"] = "%{wks.location}/RodskaEngine/vendor/mono/msvc/build/sgen/%{monoArch}/lib/%{cfg.buildcfg}"


IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/RodskaEngine/vendor/glfw/include"
IncludeDir["GLAD"] = "%{wks.location}/RodskaEngine/vendor/GLAD/include"
IncludeDir["imgui"] = "%{wks.location}/RodskaEngine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/RodskaEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/RodskaEngine/vendor/stb_image"
IncludeDir["tinyobjloader"] = "%{wks.location}/RodskaEngine/vendor/tinyobjloader"
IncludeDir["entt"] = "%{wks.location}/RodskaEngine/vendor/entt/include"
IncludeDir["yamlcpp"] = "%{wks.location}/RodskaEngine/vendor/yaml-cpp/include"
IncludeDir["cmdparser"] = "%{wks.location}/RodskaEngine/vendor/cmdparser"
IncludeDir["DirectXTK"] = "%{wks.location}/RodskaEngine/vendor/DirectXTK/Inc"
IncludeDir["mono"] = "%{wks.location}/RodskaEngine/vendor/mono/msvc/include"

group "Dependencies"
	include "RodskaEngine/vendor/glfw"
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

group "Projects"
	include "RodskaEditor"
	include "RodskaEngine"

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