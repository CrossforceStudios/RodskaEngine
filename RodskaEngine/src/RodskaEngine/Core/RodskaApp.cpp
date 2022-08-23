#include "rdskpch.h"
#include "RodskaApp.h"
#include <glad/glad.h>
#include "RodskaEngine/Graphics/RodskaRenderer.h"
#include "RodskaEngine/Graphics/Camera/OrthographicCamera.h"
#include "ModuleHandler.h"
#include <GLFW/glfw3.h>
#include <RodskaEngine/Scripting/AmethystBackend.h>
#include <Platform/CSharp/CSharpBackend.h>

#ifdef _WIN32 
	#include <Platform/Windows/WindowsECore.h>
#endif
namespace RodskaEngine {

	RodskaApp* RodskaApp::CurrentApp = nullptr;
	std::string get_stem(const std::filesystem::path& p) { return (p.stem().string()); }



	RodskaApp::RodskaApp(int argc, char** argv)
		: m_LastTime((float)glfwGetTime()), m_Parser(argc, argv)
	{
		
		RDSK_CORE_ASSERT(!CurrentApp, "Application already exists!");
		CurrentApp = this;
		#ifdef _WIN32
			InitWinRL();
		#endif
		SceneRegistry = new SceneAdapter();
		{
			m_Parser.enable_help();
			m_Parser.set_optional<std::string>("lang", "slanguage", "csharp", "The scripting language to be used for making games in Rodska Engine.");
		}
		m_Parser.run();
		AmethystBackend::CurrentOutputMode = AmethystMode::StdLog;
		{
			if (m_Parser.get<std::string>("lang") == "csharp") {
				m_LangBackendType = AmethystMode::CSharp;
				m_LangBackend.reset(new CSharpBackend);

			}
		}
		m_Viewport = std::unique_ptr<Viewport>(Viewport::Create());
		m_Viewport->SetEventCallback(RDSK_BIND_EVENT_CB(RodskaApp, OnEvent));
		RodskaRenderer::Init();
		
		
		m_UILayer = new UILayer();
		PushOverlay(m_UILayer);

		
	}



	
	RodskaApp::~RodskaApp() {

	}


	void RodskaApp::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void RodskaApp::PushOverlay(Layer* overlay) {
		m_LayerStack.PushLayer(overlay);
	}

	void RodskaApp::OnEvent(RodskaEvent& e) {
		RodskaEventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(RDSK_BIND_EVENT_CB(RodskaApp, OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(RDSK_BIND_EVENT_CB(RodskaApp, OnWindowResize));

		RDSK_CORE_TRACE("{0}", e.ToString());
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	std::vector<ModuleHandler> RodskaApp::LoadModules(std::string plugPath) {
		std::vector<ModuleHandler> modules;

		const std::filesystem::path pluginPath = std::filesystem::path(plugPath);
		for (auto const& p : std::filesystem::directory_iterator(pluginPath)){
			auto path = p.path();
			if (path.extension().string() == ".dll") {
				RDSK_CORE_INFO("Module Found: {0}", path.string());
				modules.push_back(ModuleHandler(plugPath + get_stem(path)));
			}
		}
		return modules;
	}

	void RodskaApp::Shutdown()
	{

	}

	void RodskaApp::InitAssets(const std::string& assetPath)
	{
		m_assetDir = std::filesystem::path(assetPath);
	}

	const std::string& RodskaApp::getRelativeAsset(const std::string& newPath)
	{
		return (m_assetDir / newPath).string();
	}

	void RodskaApp::SetCSBasePath(const std::string& basePath)
	{
		if (m_LangBackendType == AmethystMode::CSharp) {
			auto backend = std::dynamic_pointer_cast<CSharpBackend>(m_LangBackend);
			backend->SetBase(basePath);
		}
	}

	bool RodskaApp::OnWindowClose(WindowClosedEvent& e) {
		m_IsRunning = false;
		return true;
	}

	void RodskaApp::Close() {
		m_IsRunning = false;
	}

	bool RodskaApp::OnWindowResize(WindowResizeEvent& e) {

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		RodskaRenderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void RodskaApp::InitLangBackend() {
		if (m_Parser.get<std::string>("lang") == "csharp") {
			m_LangBackend->Init();

		}
	}

	void RodskaApp::Run() {
		
		while (m_IsRunning) {
			
			float time = (float)glfwGetTime(); // Platform::GetTime
			TimeStep timestep = time - m_LastTime;
			 m_LastTime = time;
			 m_ElapsedTime += timestep;
			 if (!m_Minimized) {
				 for (Layer* layer : m_LayerStack)
					 layer->OnUpdate(timestep);
			 }
			m_UILayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnGUIRender();
			m_UILayer->End();


			m_Viewport->OnUpdate();
			
		}
	}
}