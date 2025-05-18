project "RodskaEditor"
	kind "ConsoleApp"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	staticruntime "off"
	cppdialect "C++17"
	
	

		
	files 
	{
		"src/**.h",
		"src/**.cpp",
		"assets/shaders/DirectX/**.hlsl"
	}



	includedirs
	{
		"%{wks.location}/RodskaEngine/vendor/spdlog/include",
		"%{wks.location}/RodskaEngine/src",
		"%{wks.location}/RodskaEngine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.yamlcpp}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.mono}",

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
			local shader_dir = "assets/shaders/DirectX"
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
			local shader_dir = "assets/shaders/DirectX"
			shadermodel("5.1")
			shaderassembler("AssemblyCode")
			shaderobjectfileoutput(shader_dir.."/compiled/%{file.basename}"..".12.cso")
			shaderassembleroutput(shader_dir.."/compiled/%{file.basename}"..".12.asm")
			filter("files:**PixelShader12.hlsl")		
				shadertype("Pixel")

			filter("files:**VertexShader12.hlsl")
				shadertype("Vertex")
			
			shaderoptions({"/WX"})
