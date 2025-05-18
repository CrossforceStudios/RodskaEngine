
#include "rdskpch.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "RodskaEngine/UI/UICore/ImGuiBackend.h"
#include "Platform/OpenGL/OpenGLImGuiBackend.h"

#include "UILayer.h"
#include <RodskaEngine/Core/RodskaApp.h>
#include <RodskaEngine/EventSystem/MouseInputEvent.h>
#include "ImGuizmo.h"

namespace RodskaEngine {

	Ref<ImGuiFontLibrary> UILayer::Fonts = nullptr;

	UILayer::UILayer()
	: Layer("DebugUI") {
		m_DarkTheme = CreateRef<Theme>();

	}

	UILayer::~UILayer() {

	}

	void UILayer::OnAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Fonts = CreateRef<ImGuiFontLibrary>("MainIM");
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		Fonts->SetFont("AtkinsonHDefault", "E:/RW/RodskaEngine/RodskaEditor/assets/fonts/AtkinsonHyperlegible-Regular.ttf", 18.0f);
		io.FontDefault = Fonts->GetFont("AtkinsonHDefault");
		Fonts->SetFont("AtkinsonHBold","E:/RW/RodskaEngine/RodskaEditor/assets/fonts/AtkinsonHyperlegible-Bold.ttf", 18.0f);
		SetupTheme();
		// Setup Dear ImGui style
		m_DarkTheme->Apply();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		RodskaApp& app = RodskaApp::Get();
		m_Backend = ImGuiBackend::Create();
		switch (RodskaRenderer::GetRHI()) {
		case RHIAPI::RHI::OpenGL:
			auto& backend = (std::dynamic_pointer_cast<OpenGLImGuiBackend>(m_Backend));
			backend->GLSLVersion = "#version 410";
			backend->clientAPI = OpenGLClientAPI_OpenGL;
			backend->Viewport = app.GetViewport().GetNativeWindow();
			break;
		}
		m_Backend->Init();
	}

	void UILayer::OnDetach() {
		m_Backend->Shutdown();
		ImGui::DestroyContext();

	}

	void UILayer::Begin() {
		m_Backend->NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}
	
	void UILayer::End() {
		ImGuiIO& io = ImGui::GetIO();
		RodskaApp& app = RodskaApp::Get();
		io.DisplaySize = ImVec2((float)app.GetViewport().GetWidth(), (float)app.GetViewport().GetHeight());
		ImGui::Render();
		m_Backend->RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			switch (RodskaRenderer::GetRHI()) {
			case RHIAPI::RHI::OpenGL:
				glfwMakeContextCurrent(backup_current_context);
				break;
			}
		}


	}

	void UILayer::SetupTheme()
	{
		m_DarkTheme->AddStyleColor(ImGuiCol_WindowBg, TempVec4{ 0.11f, 0.115f, 0.12f, 1.0f});


		m_DarkTheme->AddStyleColor(ImGuiCol_Header, TempVec4{ 0.21f, 0.215f, 0.22f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_HeaderHovered, TempVec4{ 0.31f, 0.315f, 0.32f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_HeaderActive, TempVec4{ 0.16f, 0.165f, 0.17f, 1.0f });

		m_DarkTheme->AddStyleColor(ImGuiCol_Button, TempVec4{ 0.21f, 0.215f, 0.22f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_ButtonHovered, TempVec4{ 0.31f, 0.315f, 0.32f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_ButtonActive, TempVec4{ 0.16f, 0.165f, 0.17f, 1.0f });

		m_DarkTheme->AddStyleColor(ImGuiCol_FrameBg, TempVec4{ 0.21f, 0.215f, 0.22f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_FrameBgHovered, TempVec4{ 0.31f, 0.315f, 0.32f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_FrameBgActive, TempVec4{ 0.16f, 0.165f, 0.17f, 1.0f });

		m_DarkTheme->AddStyleColor(ImGuiCol_Tab, TempVec4{ 0.21f, 0.215f, 0.22f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_TabHovered, TempVec4{ 0.38f, 0.385f, 0.39f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_TabActive, TempVec4{ 0.28f, 0.285f, 0.29f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_TabUnfocused, TempVec4{ 0.16f, 0.165f, 0.17f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_TabUnfocusedActive, TempVec4{ 0.21f, 0.215f, 0.22f, 1.0f });

		m_DarkTheme->AddStyleColor(ImGuiCol_TitleBg, TempVec4{ 0.16f, 0.165f, 0.17f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_TitleBgActive, TempVec4{ 0.16f, 0.165f, 0.17f, 1.0f });
		m_DarkTheme->AddStyleColor(ImGuiCol_TitleBgCollapsed, TempVec4{ 0.16f, 0.165f, 0.17f, 1.0f });
	}

	void UILayer::OnGUIRender() {
		static bool show = true;
	}

}