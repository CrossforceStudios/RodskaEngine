#pragma once

#include "RodskaEngine/UI/UICore/ImGuiBackend.h"
#include <GLFW/glfw3.h>
#include <RodskaEngine/Core/Viewport.h>

// Specific OpenGL ES versions
//#define IMGUI_IMPL_OPENGL_ES2     // Auto-detected on Emscripten
//#define IMGUI_IMPL_OPENGL_ES3     // Auto-detected on iOS/Android

// Attempt to auto-detect the default Desktop GL loader based on available header files.
// If auto-detection fails or doesn't select the same GL loader file as used by your application,
// you are likely to get a crash in ImGui_ImplOpenGL3_Init().
// You can explicitly select a loader by using one of the '#define IMGUI_IMPL_OPENGL_LOADER_XXX' in imconfig.h or compiler command-line.
#if !defined(IMGUI_IMPL_OPENGL_ES2) \
 && !defined(IMGUI_IMPL_OPENGL_ES3) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GL3W) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLEW) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

// Try to detect GLES on matching platforms

#if  (defined(__ANDROID__))
#define IMGUI_IMPL_OPENGL_ES3               // Android only -> GL ES 3, "#version 300 es"
#elif defined(__EMSCRIPTEN__)
#define IMGUI_IMPL_OPENGL_ES2               // Emscripten    -> GL ES 2, "#version 100"

// Otherwise try to detect supported Desktop OpenGL loaders..
#elif defined(__has_include)
#if __has_include(<GL/glew.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#elif __has_include(<glad/glad.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#elif __has_include(<glad/gl.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2
#elif __has_include(<GL/gl3w.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GL3W
#elif __has_include(<glbinding/glbinding.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLBINDING3
#elif __has_include(<glbinding/Binding.h>)
#define IMGUI_IMPL_OPENGL_LOADER_GLBINDING2
#else
#error "Cannot detect OpenGL loader!"
#endif
#else
#define IMGUI_IMPL_OPENGL_LOADER_GL3W   // Default to GL3W embedded in our repository
#endif

#endif


namespace RodskaEngine {
    typedef std::tuple<GLchar*, GLchar*> GLShaderPair;
    enum OpenGLClientAPI {
        OpenGLClientAPI_None,
        OpenGLClientAPI_Vulkan,
        OpenGLClientAPI_OpenGL
    };

    struct OpenGLImGuiData {
        GLuint version = 0;
        GLuint FontTexture = 0;
        char GLSLVersion[32] = "";
        GLuint shaderHandle = 0, vertHandle = 0, fragHandle = 0;
        GLuint AttribLocationProjMtx = 0, AttribLocationTex = 0;
        GLuint AttribLocationVtxColor = 0;
        GLuint AttribLocationVtxPos = 0, AttribLocationVtxUV = 0;
        GLuint VboHandle = 0, ElementsHandle = 0;
        bool HasClipOrigin = false;
        OpenGLImGuiData() {};
    };

    struct ImGuiGLFWViewportData {
        GLFWwindow* Window;
        bool        WindowOwned;
        int         IgnoreWindowPosEventFrame;
        int         IgnoreWindowSizeEventFrame;

        ImGuiGLFWViewportData() { Window = NULL; WindowOwned = false; IgnoreWindowSizeEventFrame = IgnoreWindowPosEventFrame = -1; }
        ~ImGuiGLFWViewportData() { RDSK_CORE_ASSERT(Window == NULL, "Window must not be present."); }
    };

    struct ImGuiGLFWData
    {
        GLFWwindow* Window;
        OpenGLClientAPI           ClientApi;
        double                  Time;
        GLFWwindow* MouseWindow;
        bool                    MouseJustPressed[ImGuiMouseButton_COUNT];
        GLFWcursor* MouseCursors[ImGuiMouseCursor_COUNT];
        bool                    InstalledCallbacks;
        GLFWwindow* KeyOwnerWindows[512];

        // Chain GLFW callbacks: our callbacks will call the user's previously installed callbacks, if any.
        GLFWcursorenterfun      PrevUserCallbackCursorEnter;
        GLFWmousebuttonfun      PrevUserCallbackMousebutton;
        GLFWscrollfun           PrevUserCallbackScroll;
        GLFWkeyfun              PrevUserCallbackKey;
        GLFWcharfun             PrevUserCallbackChar;
        GLFWmonitorfun          PrevUserCallbackMonitor;
        bool                    WantUpdateMonitors;

        ImGuiGLFWData() { memset(this, 0, sizeof(*this)); }
    };
	class OpenGLImGuiBackend : public ImGuiBackend {
	public:
        static ImGuiGLFWData* currentData;
        static OpenGLImGuiData currentGLData;
        std::string GLSLVersion = "#version 410";
        void* Viewport;
        OpenGLClientAPI clientAPI;
    public:
        RODSKA_EAPI OpenGLImGuiBackend();
        RODSKA_EAPI ~OpenGLImGuiBackend() {}
        RODSKA_EAPI virtual const bool Init() override;
        RODSKA_EAPI virtual void UpdateMonitors() override;
        RODSKA_EAPI virtual char* GetBackendTag() { return "imgui_impl_rdsk_opengl"; }
        RODSKA_EAPI virtual void NewFrame() override;
        RODSKA_EAPI virtual void Shutdown() override;
        RODSKA_EAPI virtual bool CreateDeviceObjects() override;
        RODSKA_EAPI virtual void DestroyDeviceObjects() override;
        RODSKA_EAPI virtual void RenderDrawData(ImDrawData* data) override;
    public:
        RODSKA_EAPI void addImGuiShader(const std::string& name, const std::string& shaderPath);
    protected:
        virtual void InitPlatformInterface() override;
        virtual void InitRendererInterface() override;
        virtual void ShutdownPlatformInterface() override;
        virtual void ShutdownRendererInterface() override;
    private:
        void UpdateMousePos();
        void UpdateMouseCursor();
        void UpdateGamepads();
        void DestroyFontsTexture();
        GLShaderPair getShaders();
        GLuint renderFragShader(GLShaderPair shaders);
        GLuint renderVertShader(GLShaderPair shaders);
        void renderShaderProgram(GLuint vertHandle, GLuint fragHandle);
        bool CreateFontsTexture();
        bool CheckShader(GLuint handle, const char* desc);
        bool CheckProgram(GLuint handle, const char* desc);
        std::string readFile(const std::string& path);
	private:
        
        std::map<std::string, std::string> m_shaderSources;
	};
};