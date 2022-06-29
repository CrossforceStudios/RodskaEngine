

#include "rdskpch.h"
#include "imgui.h"
#include "OpenGLImGuiBackend.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>   // for glfwGetWin32Window
#endif
#define GLFW_HAS_WINDOW_TOPMOST       (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3200) // 3.2+ GLFW_FLOATING
#define GLFW_HAS_WINDOW_HOVERED       (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3300) // 3.3+ GLFW_HOVERED
#define GLFW_HAS_WINDOW_ALPHA         (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3300) // 3.3+ glfwSetWindowOpacity
#define GLFW_HAS_PER_MONITOR_DPI      (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3300) // 3.3+ glfwGetMonitorContentScale
#define GLFW_HAS_VULKAN               (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3200) // 3.2+ glfwCreateWindowSurface
#ifdef GLFW_RESIZE_NESW_CURSOR        // Let's be nice to people who pulled GLFW between 2019-04-16 (3.4 define) and 2019-11-29 (cursors defines) // FIXME: Remove when GLFW 3.4 is released?
#define GLFW_HAS_NEW_CURSORS          (GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3400) // 3.4+ GLFW_RESIZE_ALL_CURSOR, GLFW_RESIZE_NESW_CURSOR, GLFW_RESIZE_NWSE_CURSOR, GLFW_NOT_ALLOWED_CURSOR
#else
#define GLFW_HAS_NEW_CURSORS          (0)
#endif
#include <stdio.h>
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>     // intptr_t
#else
#include <stdint.h>     // intptr_t
#endif

// GL includes
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#elif defined(IMGUI_IMPL_OPENGL_ES3)
#if (defined(__APPLE__) && (TARGET_OS_IOS || TARGET_OS_TV))
#include <OpenGLES/ES3/gl.h>    // Use GL ES 3
#else
#include <GLES3/gl3.h>          // Use GL ES 3
#endif
#else
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Needs to be initialized with gl3wInit() in user's code
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Needs to be initialized with glewInit() in user's code.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Needs to be initialized with gladLoadGL() in user's code.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>            // Needs to be initialized with gladLoadGL(...) or gladLoaderLoadGL() in user's code.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#endif
#include <glbinding/Binding.h>  // Needs to be initialized with glbinding::Binding::initialize() in user's code.
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#endif
#include <glbinding/glbinding.h>// Needs to be initialized with glbinding::initialize() in user's code.
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
#endif

// Desktop GL 3.2+ has glDrawElementsBaseVertex() which GL ES and WebGL don't have.
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3) && defined(GL_VERSION_3_2)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_VTX_OFFSET
#endif

// Desktop GL 3.3+ has glBindSampler()
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3) && defined(GL_VERSION_3_3)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
#endif

// Desktop GL 3.1+ has GL_PRIMITIVE_RESTART state
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3) && defined(GL_VERSION_3_1)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
#endif

// Desktop GL use extension detection
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_EXTENSIONS
#endif

void openGLFWSetClipboardContents(void* user_data, const char* text) {
    glfwSetClipboardString((GLFWwindow*)user_data, text);
}
const char* openGLFWGetClipboardText(void* user_data) {
    return glfwGetClipboardString((GLFWwindow*)user_data);
}
namespace RodskaEngine {
  
    ImGuiGLFWData* OpenGLImGuiBackend::currentData = new  ImGuiGLFWData();
    OpenGLImGuiData OpenGLImGuiBackend::currentGLData = OpenGLImGuiData();

    void openGLFWOnChar(GLFWwindow* window,  unsigned int c) {
        if (OpenGLImGuiBackend::currentData->PrevUserCallbackChar != NULL && window == OpenGLImGuiBackend::currentData->Window)
            OpenGLImGuiBackend::currentData->PrevUserCallbackChar(window, c);

        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(c);
    }
    void openGLFWOnMouseButton(GLFWwindow* window, int button, int action, int mods) {
            if (OpenGLImGuiBackend::currentData->PrevUserCallbackMousebutton != NULL && window == OpenGLImGuiBackend::currentData->Window)
                OpenGLImGuiBackend::currentData->PrevUserCallbackMousebutton(window, button, action, mods);

            if (action == GLFW_PRESS && button >= 0 && button < IM_ARRAYSIZE(OpenGLImGuiBackend::currentData->MouseJustPressed))
                OpenGLImGuiBackend::currentData->MouseJustPressed[button] = true;
    }
    void openGLFWOnCursorEnter(GLFWwindow* window, int entered) {
        if (OpenGLImGuiBackend::currentData->PrevUserCallbackCursorEnter != NULL)
            OpenGLImGuiBackend::currentData->PrevUserCallbackCursorEnter(window, entered);
        if (entered)
            OpenGLImGuiBackend::currentData->MouseWindow = window;
        if (!entered && OpenGLImGuiBackend::currentData->MouseWindow == window)
            OpenGLImGuiBackend::currentData->MouseWindow = NULL;
    }
    void openGLFWOnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (OpenGLImGuiBackend::currentData->PrevUserCallbackKey != NULL && window == OpenGLImGuiBackend::currentData->Window)
            OpenGLImGuiBackend::currentData->PrevUserCallbackKey(window, key, scancode, action, mods);

        ImGuiIO& io = ImGui::GetIO();
        if (key >= 0 && key < IM_ARRAYSIZE(io.KeysDown))
        {
            if (action == GLFW_PRESS)
                io.KeysDown[key] = true;
            if (action == GLFW_RELEASE)
                io.KeysDown[key] = false;
        }

        // Modifiers are not reliable across systems
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#ifdef _WIN32
        io.KeySuper = false;
#else
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
    }
    void openGLFWOnScroll(GLFWwindow * window, double xoffset, double yoffset)
     {
            if (OpenGLImGuiBackend::currentData->PrevUserCallbackScroll != NULL && window == OpenGLImGuiBackend::currentData->Window)
                OpenGLImGuiBackend::currentData->PrevUserCallbackScroll(window, xoffset, yoffset);

            ImGuiIO& io = ImGui::GetIO();
            io.MouseWheelH += (float)xoffset;
            io.MouseWheel += (float)yoffset;
    }
    void openGLFWOnMonitorUpdate(GLFWmonitor*, int)
    {
        OpenGLImGuiBackend::currentData->WantUpdateMonitors = true;
    }
    void openGLFWOnWindowPos(GLFWwindow* window, int, int)
    {
        if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle(window))
        {
            if (ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData)
            {
                bool ignore_event = (ImGui::GetFrameCount() <= data->IgnoreWindowPosEventFrame + 1);
                //data->IgnoreWindowPosEventFrame = -1;
                if (ignore_event)
                    return;
            }
            viewport->PlatformRequestMove = true;
        }
    }

    void openGLFWOnWindowClose(GLFWwindow* window) {
        if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle(window))
            viewport->PlatformRequestClose = true;
    }

    // We have submitted https://github.com/glfw/glfw/pull/1568 to allow GLFW to support "transparent inputs".
// In the meanwhile we implement custom per-platform workarounds here (FIXME-VIEWPORT: Implement same work-around for Linux/OSX!)
#if !GLFW_HAS_MOUSE_PASSTHROUGH && GLFW_HAS_WINDOW_HOVERED && defined(_WIN32)
    static WNDPROC g_GlfwWndProc = NULL;
    LRESULT CALLBACK WndProcNoInputs(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (msg == WM_NCHITTEST)
        {
            // Let mouse pass-through the window. This will allow the backend to set io.MouseHoveredViewport properly (which is OPTIONAL).
            // The ImGuiViewportFlags_NoInputs flag is set while dragging a viewport, as want to detect the window behind the one we are dragging.
            // If you cannot easily access those viewport flags from your windowing/event code: you may manually synchronize its state e.g. in
            // your main loop after calling UpdatePlatformWindows(). Iterate all viewports/platform windows and pass the flag to your windowing system.
            ImGuiViewport* viewport = (ImGuiViewport*)::GetPropA(hWnd, "IMGUI_VIEWPORT");
            if (viewport->Flags & ImGuiViewportFlags_NoInputs)
                return HTTRANSPARENT;
        }
        return ::CallWindowProc(g_GlfwWndProc, hWnd, msg, wParam, lParam);
    }
#endif

    void openGLFWOnWindowSize(GLFWwindow* window, int, int)
    {
        if (ImGuiViewport* viewport = ImGui::FindViewportByPlatformHandle(window))
        {
            if (ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData)
            {
                bool ignore_event = (ImGui::GetFrameCount() <= data->IgnoreWindowSizeEventFrame + 1);
                //data->IgnoreWindowSizeEventFrame = -1;
                if (ignore_event)
                    return;
            }
            viewport->PlatformRequestResize = true;
        }
    }

    void openGLFWCreateWindow(ImGuiViewport* vp) {
        ImGuiGLFWViewportData* data = IM_NEW(ImGuiGLFWViewportData)();
        vp->PlatformUserData = data;

        // GLFW 3.2 unfortunately always set focus on glfwCreateWindow() if GLFW_VISIBLE is set, regardless of GLFW_FOCUSED
        // With GLFW 3.3, the hint GLFW_FOCUS_ON_SHOW fixes this problem
        glfwWindowHint(GLFW_VISIBLE, false);
        glfwWindowHint(GLFW_FOCUSED, false);
#if GLFW_HAS_FOCUS_ON_SHOW
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
#endif
        glfwWindowHint(GLFW_DECORATED, (vp->Flags & ImGuiViewportFlags_NoDecoration) ? false : true);
#if GLFW_HAS_WINDOW_TOPMOST
        glfwWindowHint(GLFW_FLOATING, (vp->Flags & ImGuiViewportFlags_TopMost) ? true : false);
#endif
        GLFWwindow* share_window = (OpenGLImGuiBackend::currentData->ClientApi == OpenGLClientAPI_OpenGL) ? (GLFWwindow*)OpenGLImGuiBackend::currentData->Window : NULL;
        data->Window = glfwCreateWindow((int)vp->Size.x, (int)vp->Size.y, "No Title Yet", NULL, share_window);
        data->WindowOwned = true;
        vp->PlatformHandle = (void*)data->Window;
#ifdef _WIN32
        vp->PlatformHandleRaw = glfwGetWin32Window(data->Window);
#endif
        glfwSetWindowPos(data->Window, (int)vp->Pos.x, (int)vp->Pos.y);

        // Install GLFW callbacks for secondary viewports
        glfwSetMouseButtonCallback(data->Window, &openGLFWOnMouseButton);
        glfwSetScrollCallback(data->Window, &openGLFWOnScroll);
        glfwSetKeyCallback(data->Window, &openGLFWOnKey);
        glfwSetCharCallback(data->Window, &openGLFWOnChar);
        glfwSetWindowCloseCallback(data->Window, &openGLFWOnWindowClose);
        glfwSetWindowPosCallback(data->Window, &openGLFWOnWindowPos);
        glfwSetWindowSizeCallback(data->Window, &openGLFWOnWindowSize);
        if (OpenGLImGuiBackend::currentData->ClientApi == OpenGLClientAPI_OpenGL)
        {
            glfwMakeContextCurrent(data->Window);
            glfwSwapInterval(0);
        }
    }

    void OpenGLImGuiBackend::UpdateMonitors() {
        ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
        int monitors_count = 0;
        GLFWmonitor** glfw_monitors = glfwGetMonitors(&monitors_count);
        platform_io.Monitors.resize(0);
        for (int n = 0; n < monitors_count; n++)
        {
            ImGuiPlatformMonitor monitor;
            int x, y;
            glfwGetMonitorPos(glfw_monitors[n], &x, &y);
            const GLFWvidmode* vid_mode = glfwGetVideoMode(glfw_monitors[n]);
            monitor.MainPos = monitor.WorkPos = ImVec2((float)x, (float)y);
            monitor.MainSize = monitor.WorkSize = ImVec2((float)vid_mode->width, (float)vid_mode->height);
#if GLFW_HAS_MONITOR_WORK_AREA
            int w, h;
            glfwGetMonitorWorkarea(glfw_monitors[n], &x, &y, &w, &h);
            if (w > 0 && h > 0) // Workaround a small GLFW issue reporting zero on monitor changes: https://github.com/glfw/glfw/pull/1761
            {
                monitor.WorkPos = ImVec2((float)x, (float)y);
                monitor.WorkSize = ImVec2((float)w, (float)h);
            }
#endif
#if GLFW_HAS_PER_MONITOR_DPI
            // Warning: the validity of monitor DPI information on Windows depends on the application DPI awareness settings, which generally needs to be set in the manifest or at runtime.
            float x_scale, y_scale;
            glfwGetMonitorContentScale(glfw_monitors[n], &x_scale, &y_scale);
            monitor.DpiScale = x_scale;
#endif
            platform_io.Monitors.push_back(monitor);
        }
        currentData->WantUpdateMonitors = false;
    }



    void OpenGLImGuiBackend::NewFrame()
    {
        if (!currentGLData.shaderHandle)
            CreateDeviceObjects();
        ImGuiIO& io = ImGui::GetIO();
        RDSK_CORE_ASSERT(io.Fonts->IsBuilt(), "Font atlas not built! It is generally built by the renderer backend. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");
        int w, h;
        int display_w, display_h;
        glfwGetWindowSize((GLFWwindow*)currentData->Window, &w, &h);
        glfwGetFramebufferSize((GLFWwindow*)currentData->Window, &display_w, &display_h);
        io.DisplaySize = ImVec2((float)w, (float)h);
        if (w > 0 && h > 0)
            io.DisplayFramebufferScale = ImVec2((float)display_w / w, (float)display_h / h);
        if (currentData->WantUpdateMonitors)
            UpdateMonitors();

        double current_time = glfwGetTime();
        io.DeltaTime = currentData->Time > 0.0 ? (float)(current_time - currentData->Time) : (float)(1.0f / 60.0f);
        currentData->Time = current_time;
        UpdateMousePos();
        UpdateMouseCursor();
        UpdateGamepads();
    }

    void OpenGLImGuiBackend::Shutdown()
    {
        ShutdownRendererInterface();
        DestroyDeviceObjects();
        ShutdownPlatformInterface();
        if (currentData->InstalledCallbacks)
        {
            glfwSetMouseButtonCallback((GLFWwindow*)currentData->Window, currentData->PrevUserCallbackMousebutton);
            glfwSetScrollCallback((GLFWwindow*)currentData->Window, currentData->PrevUserCallbackScroll);
            glfwSetKeyCallback((GLFWwindow*)currentData->Window, currentData->PrevUserCallbackKey);
            glfwSetCharCallback((GLFWwindow*)currentData->Window, currentData->PrevUserCallbackChar);
            currentData->InstalledCallbacks = false;
        }

        for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
        {
            glfwDestroyCursor(currentData->MouseCursors[cursor_n]);
            currentData->MouseCursors[cursor_n] = NULL;
        }
        currentData->ClientApi = OpenGLClientAPI_None;
        
    }

    bool OpenGLImGuiBackend::CreateDeviceObjects()
    {
        GLint last_texture, last_array_buffer;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
#ifndef IMGUI_IMPL_OPENGL_ES2
        GLint last_vertex_array;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
#endif

        GLShaderPair pair = getShaders();

        currentGLData.vertHandle = renderVertShader(pair);
        currentGLData.fragHandle = renderFragShader(pair);
        renderShaderProgram(currentGLData.vertHandle, currentGLData.fragHandle);
        currentGLData.AttribLocationTex = glGetUniformLocation(currentGLData.shaderHandle, "Texture");
        currentGLData.AttribLocationProjMtx = glGetUniformLocation(currentGLData.shaderHandle, "ProjMtx");
        currentGLData.AttribLocationVtxPos = (GLuint)glGetAttribLocation(currentGLData.shaderHandle, "Position");
        currentGLData.AttribLocationVtxUV = (GLuint)glGetAttribLocation(currentGLData.shaderHandle, "UV");
        currentGLData.AttribLocationVtxColor = (GLuint)glGetAttribLocation(currentGLData.shaderHandle, "Color");

        glGenBuffers(1, &currentGLData.VboHandle);
        glGenBuffers(1, &currentGLData.ElementsHandle);

        CreateFontsTexture();

        // Restore modified GL state
        glBindTexture(GL_TEXTURE_2D, last_texture);
        glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
#ifndef IMGUI_IMPL_OPENGL_ES2
        glBindVertexArray(last_vertex_array);
#endif
        return true;
    }

    void OpenGLImGuiBackend::DestroyDeviceObjects()
    {
        if (currentGLData.VboHandle) { glDeleteBuffers(1, &currentGLData.VboHandle); currentGLData.VboHandle = 0; }
        if (currentGLData.ElementsHandle) { glDeleteBuffers(1, &currentGLData.ElementsHandle); currentGLData.ElementsHandle = 0; }
        if (currentGLData.shaderHandle && currentGLData.vertHandle) { glDetachShader(currentGLData.shaderHandle, currentGLData.vertHandle); }
        if (currentGLData.shaderHandle && currentGLData.fragHandle) { glDetachShader(currentGLData.shaderHandle, currentGLData.fragHandle); }
        if (currentGLData.vertHandle) { glDeleteShader(currentGLData.vertHandle); currentGLData.vertHandle = 0; }
        if (currentGLData.fragHandle) { glDeleteShader(currentGLData.fragHandle); currentGLData.fragHandle = 0; }
        if (currentGLData.shaderHandle) { glDeleteProgram(currentGLData.shaderHandle); currentGLData.shaderHandle = 0; }

        DestroyFontsTexture();
    }

    void OpenGLImGuiBackend::addImGuiShader(const std::string& name, const std::string& shaderPath)
    {
        m_shaderSources[name] = readFile(shaderPath);
    }

    OpenGLImGuiBackend::OpenGLImGuiBackend()
    {
        addImGuiShader("opengl_410_core_vert", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_410_vert.glsl");
        addImGuiShader("opengl_410_core_frag", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_410_frag.glsl");
        addImGuiShader("opengl_300_es_frag", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_300_es_frag.glsl");
        addImGuiShader("opengl_300_es_vert", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_300_es_vert.glsl");
        addImGuiShader("opengl_130_vert", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_130_vert.glsl");
        addImGuiShader("opengl_130_frag", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_130_frag.glsl");
        addImGuiShader("opengl_120_vert", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_120_vert.glsl");
        addImGuiShader("opengl_120_frag", "D:/RodskaEngine/RodskaEditor/assets/shaders/OpenGL/imgui_120_frag.glsl");

    }

    const bool OpenGLImGuiBackend::Init()
    {
        // GLFW 
        ImGuiIO& io = ImGui::GetIO();
        RDSK_CORE_ASSERT(io.BackendPlatformUserData == NULL, "Already initialized a platform backend!");
        currentData = IM_NEW(ImGuiGLFWData)();

        io.BackendPlatformUserData = (void*)currentData;
        io.BackendPlatformName = GetBackendTag();
        io.BackendRendererName = GetBackendTag();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
        io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;    // We can create multi-viewports on the Platform side (optional)
#if GLFW_HAS_MOUSE_PASSTHROUGH || (GLFW_HAS_WINDOW_HOVERED && defined(_WIN32))
        io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport; // We can set io.MouseHoveredViewport correctly (optional, not easy)
#endif
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_VTX_OFFSET
        if (currentGLData.version >= 320)
            io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
#endif
        io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;  // We can create multi-viewports on the Renderer side (optional)
        currentData->Window = (GLFWwindow*)Viewport;
        currentData->Time = 0.0;

        // Keyboard mapping. Dear ImGui will use those indices to peek into the io.KeysDown[] array.
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        io.SetClipboardTextFn = &openGLFWSetClipboardContents;
        io.GetClipboardTextFn = &openGLFWGetClipboardText;
        io.ClipboardUserData = currentData->Window;

      
        // Create mouse cursors
        // (By design, on X11 cursors are user configurable and some cursors may be missing. When a cursor doesn't exist,
        // GLFW will emit an error which will often be printed by the app, so we temporarily disable error reporting.
        // Missing cursors will return NULL and our _UpdateMouseCursor() function will use the Arrow cursor instead.)
        GLFWerrorfun prev_error_callback = glfwSetErrorCallback(NULL);
        currentData->MouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
#if GLFW_HAS_NEW_CURSORS
        currentData->MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
#else
        currentData->MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
        currentData->MouseCursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
#endif
        glfwSetErrorCallback(prev_error_callback);

        currentData->InstalledCallbacks = true;
        currentData->PrevUserCallbackCursorEnter = glfwSetCursorEnterCallback((GLFWwindow*)Viewport, &openGLFWOnCursorEnter);
        currentData->PrevUserCallbackMousebutton = glfwSetMouseButtonCallback((GLFWwindow*)Viewport, &openGLFWOnMouseButton);
        currentData->PrevUserCallbackScroll = glfwSetScrollCallback((GLFWwindow*)Viewport, &openGLFWOnScroll);
        currentData->PrevUserCallbackKey = glfwSetKeyCallback((GLFWwindow*)Viewport, &openGLFWOnKey);
        currentData->PrevUserCallbackChar = glfwSetCharCallback((GLFWwindow*)Viewport, &openGLFWOnChar);

        UpdateMonitors();
        currentData->PrevUserCallbackMonitor = glfwSetMonitorCallback(&openGLFWOnMonitorUpdate);
        ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        main_viewport->PlatformHandle = (void*)currentData->Window;
        #ifdef _WIN32
             main_viewport->PlatformHandleRaw = glfwGetWin32Window((GLFWwindow*)currentData->Window);
        #endif
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            InitPlatformInterface();
        currentData->ClientApi = clientAPI;
#if !defined(IMGUI_IMPL_OPENGL_ES2)
        GLint major = 0;
        GLint minor = 0;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        if (major == 0 && minor == 0)
        {
            // Query GL_VERSION in desktop GL 2.x, the string will start with "<major>.<minor>"
            const char* gl_version = (const char*)glGetString(GL_VERSION);
            sscanf(gl_version, "%d.%d", &major, &minor);
        }
        currentGLData.version = (GLuint)(major * 100 + minor * 10);
#else
        currentGLData.version = 200; // GLES 2
#endif
#if defined(IMGUI_IMPL_OPENGL_ES2)
        if (GLSLVersion.c_str() == NULL)
            GLSLVersion = "#version 100";
#elif defined(IMGUI_IMPL_OPENGL_ES3)
        if (GLSLVersion.c_str() == NULL)
            GLSLVersion = "#version 300 es";
#else
        if (GLSLVersion.c_str() == NULL)
            GLSLVersion = "#version 130";
#endif
        RDSK_CORE_ASSERT((int)strlen(GLSLVersion.c_str()) + 2 < IM_ARRAYSIZE(currentGLData.GLSLVersion), "GLSLVersion is invalid.");
        strcpy(currentGLData.GLSLVersion, GLSLVersion.c_str());
        strcat(currentGLData.GLSLVersion, "\n");
        // Debugging construct to make it easily visible in the IDE and debugger which GL loader has been selected.
        // The code actually never uses the 'gl_loader' variable! It is only here so you can read it!
        // If auto-detection fails or doesn't select the same GL loader file as used by your application,
        // you are likely to get a crash below.
        // You can explicitly select a loader by using '#define IMGUI_IMPL_OPENGL_LOADER_XXX' in imconfig.h or compiler command-line.
        const char* gl_loader = "Unknown";
        IM_UNUSED(gl_loader);
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
        gl_loader = "GL3W";
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
        gl_loader = "GLEW";
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
        gl_loader = "GLAD";
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
        gl_loader = "GLAD2";
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
        gl_loader = "glbinding2";
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
        gl_loader = "glbinding3";
#elif defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
        gl_loader = "custom";
#else
        gl_loader = "none";
#endif
        GLint current_texture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &current_texture);

        // Detect extensions we support
        currentGLData.HasClipOrigin = (currentGLData.version >= 450);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_EXTENSIONS
        GLint num_extensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
        for (GLint i = 0; i < num_extensions; i++)
        {
            const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
            if (extension != NULL && strcmp(extension, "GL_ARB_clip_control") == 0)
                currentGLData.HasClipOrigin = true;
        }
#endif

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            InitRendererInterface();

        return true;
    }
    void openGLFWShowWindow(ImGuiViewport* viewport)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;

#if defined(_WIN32)
        // GLFW hack: Hide icon from task bar
        HWND hwnd = (HWND)viewport->PlatformHandleRaw;
        if (viewport->Flags & ImGuiViewportFlags_NoTaskBarIcon)
        {
            LONG ex_style = ::GetWindowLong(hwnd, GWL_EXSTYLE);
            ex_style &= ~WS_EX_APPWINDOW;
            ex_style |= WS_EX_TOOLWINDOW;
            ::SetWindowLong(hwnd, GWL_EXSTYLE, ex_style);
        }

        // GLFW hack: install hook for WM_NCHITTEST message handler
#if !GLFW_HAS_MOUSE_PASSTHROUGH && GLFW_HAS_WINDOW_HOVERED && defined(_WIN32)
        ::SetPropA(hwnd, "IMGUI_VIEWPORT", viewport);
        if (g_GlfwWndProc == NULL)
            g_GlfwWndProc = (WNDPROC)::GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        ::SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProcNoInputs);
#endif

#if !GLFW_HAS_FOCUS_ON_SHOW
        // GLFW hack: GLFW 3.2 has a bug where glfwShowWindow() also activates/focus the window.
        // The fix was pushed to GLFW repository on 2018/01/09 and should be included in GLFW 3.3 via a GLFW_FOCUS_ON_SHOW window attribute.
        // See https://github.com/glfw/glfw/issues/1189
        // FIXME-VIEWPORT: Implement same work-around for Linux/OSX in the meanwhile.
        if (viewport->Flags & ImGuiViewportFlags_NoFocusOnAppearing)
        {
            ::ShowWindow(hwnd, SW_SHOWNA);
            return;
        }
#endif
#endif

        glfwShowWindow(data->Window);
    }
    void openGLFWDestroyWindow(ImGuiViewport* viewport)
    {
        if (ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData)
        {
            if (data->WindowOwned)
            {
#if !GLFW_HAS_MOUSE_PASSTHROUGH && GLFW_HAS_WINDOW_HOVERED && defined(_WIN32)
                HWND hwnd = (HWND)viewport->PlatformHandleRaw;
                ::RemovePropA(hwnd, "IMGUI_VIEWPORT");
#endif

                // Release any keys that were pressed in the window being destroyed and are still held down,
                // because we will not receive any release events after window is destroyed.
                for (int i = 0; i < IM_ARRAYSIZE(OpenGLImGuiBackend::currentData->KeyOwnerWindows); i++)
                    if (OpenGLImGuiBackend::currentData->KeyOwnerWindows[i] == data->Window)
                        openGLFWOnKey(data->Window, i, 0, GLFW_RELEASE, 0); // Later params are only used for main viewport, on which this function is never called.

                glfwDestroyWindow(data->Window);
            }
            data->Window = NULL;
            IM_DELETE(data);
        }
        viewport->PlatformUserData = viewport->PlatformHandle = NULL;
    }

    void openGLFWSetWindowPos(ImGuiViewport* viewport, ImVec2 pos)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        data->IgnoreWindowPosEventFrame = ImGui::GetFrameCount();
        glfwSetWindowPos(data->Window, (int)pos.x, (int)pos.y);
    }

    ImVec2 openGLFWGetWindowPos(ImGuiViewport* viewport)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        int x = 0, y = 0;
        glfwGetWindowPos(data->Window, &x, &y);
        return ImVec2((float)x, (float)y);
    }

    ImVec2 openGLFWGetWindowSize(ImGuiViewport* viewport)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        int w = 0, h = 0;
        glfwGetWindowSize(data->Window, &w, &h);
        return ImVec2((float)w, (float)h);
    }
     void openGLFWSetWindowSize(ImGuiViewport* viewport, ImVec2 size)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
#if !(__APPLE__ && !GLFW_HAS_OSX_WINDOW_POS_FIX)
        data->IgnoreWindowSizeEventFrame = ImGui::GetFrameCount();
        glfwSetWindowSize(data->Window, (int)size.x, (int)size.y);
#endif
  
    }
    void openGLFWSetWindowFocus(ImGuiViewport* viewport)
     {
#if GLFW_HAS_FOCUS_WINDOW
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
         glfwFocusWindow(data->Window);
#else
         // FIXME: What are the effect of not having this function? At the moment imgui doesn't actually call SetWindowFocus - we set that up ahead, will answer that question later.
         (void)viewport;
#endif
     }
    bool openGLFWGetWindowFocus(ImGuiViewport* viewport)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        return glfwGetWindowAttrib(data->Window, GLFW_FOCUSED) != 0;
    }
    bool openGLFWGetWindowMinimized(ImGuiViewport* viewport)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        return glfwGetWindowAttrib(data->Window, GLFW_ICONIFIED) != 0;
    }
    #if GLFW_HAS_WINDOW_ALPHA
    static void openGLFWSetWindowAlpha(ImGuiViewport* viewport, float alpha)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        glfwSetWindowOpacity(data->Window, alpha);
    }
    #endif
    void openGLFWSetWindowTitle(ImGuiViewport* viewport, const char* title)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        glfwSetWindowTitle(data->Window, title);
    }
     void openGLFWRenderWindow(ImGuiViewport* viewport, void*)
    {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
        if (OpenGLImGuiBackend::currentData->ClientApi == OpenGLClientAPI_OpenGL)
            glfwMakeContextCurrent(data->Window);
    }
    void openGLFWSwapBuffers(ImGuiViewport* viewport, void*)
     {
        ImGuiGLFWViewportData* data = (ImGuiGLFWViewportData*)viewport->PlatformUserData;
         if (OpenGLImGuiBackend::currentData->ClientApi == OpenGLClientAPI_OpenGL)
         {
             glfwMakeContextCurrent(data->Window);
             glfwSwapBuffers(data->Window);
         }
     }
    //--------------------------------------------------------------------------------------------------------
    // IME (Input Method Editor) basic support for e.g. Asian language users
    //--------------------------------------------------------------------------------------------------------

    // We provide a Win32 implementation because this is such a common issue for IME users
    #if defined(_WIN32) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS) && !defined(IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS)
    #define HAS_WIN32_IME   1
    #include <imm.h>
    #ifdef _MSC_VER
    #pragma comment(lib, "imm32")
    #endif
        void openGLFWSetImeInputPos(ImGuiViewport* viewport, ImVec2 pos)
        {
            COMPOSITIONFORM cf = { CFS_FORCE_POSITION, { (LONG)(pos.x - viewport->Pos.x), (LONG)(pos.y - viewport->Pos.y) }, { 0, 0, 0, 0 } };
            if (HWND hwnd = (HWND)viewport->PlatformHandleRaw)
                if (HIMC himc = ::ImmGetContext(hwnd))
                {
                    ::ImmSetCompositionWindow(himc, &cf);
                    ::ImmReleaseContext(hwnd, himc);
                }
        }
    #else
    #define HAS_WIN32_IME   0
    #endif

    void OpenGLImGuiBackend::InitPlatformInterface() {
        ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
        platform_io.Platform_CreateWindow = &openGLFWCreateWindow;
        platform_io.Platform_DestroyWindow = &openGLFWDestroyWindow;
        platform_io.Platform_ShowWindow = &openGLFWShowWindow;
        platform_io.Platform_SetWindowPos = &openGLFWSetWindowPos;
        platform_io.Platform_GetWindowPos = &openGLFWGetWindowPos;
        platform_io.Platform_SetWindowSize = &openGLFWSetWindowSize;
        platform_io.Platform_GetWindowSize = &openGLFWGetWindowSize;
        platform_io.Platform_SetWindowFocus = &openGLFWSetWindowFocus;
        platform_io.Platform_GetWindowFocus = &openGLFWGetWindowFocus;
        platform_io.Platform_GetWindowMinimized = &openGLFWGetWindowMinimized;
        platform_io.Platform_SetWindowTitle = &openGLFWSetWindowTitle;
        platform_io.Platform_RenderWindow = &openGLFWRenderWindow;
        platform_io.Platform_SwapBuffers = &openGLFWSwapBuffers;
#if GLFW_HAS_WINDOW_ALPHA
        platform_io.Platform_SetWindowAlpha = &openGLFWSetWindowAlpha;
#endif
#if HAS_WIN32_IME
        platform_io.Platform_SetImeInputPos = &openGLFWSetImeInputPos;
#endif

        // Register main window handle (which is owned by the main application, not by us)
        // This is mostly for simplicity and consistency, so that our code (e.g. mouse handling etc.) can use same logic for main and secondary viewports.
        ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGuiGLFWViewportData* data = IM_NEW(ImGuiGLFWViewportData)();
        data->Window = (GLFWwindow*)currentData->Window;
        data->WindowOwned = false;
        main_viewport->PlatformUserData = data;
        main_viewport->PlatformHandle = currentData->Window;
    }
    void openGLSetupRenderState(ImDrawData* draw_data, int fb_width, int fb_height, GLuint vertex_array_object)
    {
        // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
        glEnable(GL_SCISSOR_TEST);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
        if (OpenGLImGuiBackend::currentGLData.version >= 310)
            glDisable(GL_PRIMITIVE_RESTART);
#endif
#ifdef GL_POLYGON_MODE
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

        // Support for GL 4.5 rarely used glClipControl(GL_UPPER_LEFT)
#if defined(GL_CLIP_ORIGIN)
        bool clip_origin_lower_left = true;
        if (OpenGLImGuiBackend::currentGLData.HasClipOrigin)
        {
            GLenum current_clip_origin = 0; glGetIntegerv(GL_CLIP_ORIGIN, (GLint*)&current_clip_origin);
            if (current_clip_origin == GL_UPPER_LEFT)
                clip_origin_lower_left = false;
        }
#endif

        // Setup viewport, orthographic projection matrix
        // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
        glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
        float L = draw_data->DisplayPos.x;
        float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
        float T = draw_data->DisplayPos.y;
        float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
#if defined(GL_CLIP_ORIGIN)
        if (!clip_origin_lower_left) { float tmp = T; T = B; B = tmp; } // Swap top and bottom if origin is upper left
#endif
        const float ortho_projection[4][4] =
        {
            { 2.0f / (R - L),   0.0f,         0.0f,   0.0f },
            { 0.0f,         2.0f / (T - B),   0.0f,   0.0f },
            { 0.0f,         0.0f,        -1.0f,   0.0f },
            { (R + L) / (L - R),  (T + B) / (B - T),  0.0f,   1.0f },
        };
        glUseProgram(OpenGLImGuiBackend::currentGLData.shaderHandle);
        glUniform1i(OpenGLImGuiBackend::currentGLData.AttribLocationTex, 0);
        glUniformMatrix4fv(OpenGLImGuiBackend::currentGLData.AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);

#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
        if (OpenGLImGuiBackend::currentGLData.version >= 330)
            glBindSampler(0, 0); // We use combined texture/sampler state. Applications using GL 3.3 may set that otherwise.
#endif

        (void)vertex_array_object;
#ifndef IMGUI_IMPL_OPENGL_ES2
        glBindVertexArray(vertex_array_object);
#endif

        // Bind vertex/index buffers and setup attributes for ImDrawVert
        glBindBuffer(GL_ARRAY_BUFFER, OpenGLImGuiBackend::currentGLData.VboHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OpenGLImGuiBackend::currentGLData.ElementsHandle);
        glEnableVertexAttribArray(OpenGLImGuiBackend::currentGLData.AttribLocationVtxPos);
        glEnableVertexAttribArray(OpenGLImGuiBackend::currentGLData.AttribLocationVtxUV);
        glEnableVertexAttribArray(OpenGLImGuiBackend::currentGLData.AttribLocationVtxColor);
        glVertexAttribPointer(OpenGLImGuiBackend::currentGLData.AttribLocationVtxPos, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos));
        glVertexAttribPointer(OpenGLImGuiBackend::currentGLData.AttribLocationVtxUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv));
        glVertexAttribPointer(OpenGLImGuiBackend::currentGLData.AttribLocationVtxColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col));
    }
    void openGLRenderDrawData(ImDrawData* draw_data) {
        int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
        int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
        if (fb_width <= 0 || fb_height <= 0)
            return;

        // Backup GL state
        GLenum last_active_texture; glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_texture);
        glActiveTexture(GL_TEXTURE0);
        GLuint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&last_program);
        GLuint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&last_texture);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
        GLuint last_sampler; if (OpenGLImGuiBackend::currentGLData.version >= 330) { glGetIntegerv(GL_SAMPLER_BINDING, (GLint*)&last_sampler); }
        else { last_sampler = 0; }
#endif
        GLuint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint*)&last_array_buffer);
#ifndef IMGUI_IMPL_OPENGL_ES2
        GLuint last_vertex_array_object; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&last_vertex_array_object);
#endif
#ifdef GL_POLYGON_MODE
        GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
#endif
        GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
        GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
        GLenum last_blend_src_rgb; glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
        GLenum last_blend_dst_rgb; glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
        GLenum last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha);
        GLenum last_blend_dst_alpha; glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
        GLenum last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb);
        GLenum last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha);
        GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
        GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
        GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
        GLboolean last_enable_stencil_test = glIsEnabled(GL_STENCIL_TEST);
        GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
        GLboolean last_enable_primitive_restart = (OpenGLImGuiBackend::currentGLData.version >= 310) ? glIsEnabled(GL_PRIMITIVE_RESTART) : GL_FALSE;
#endif

        // Setup desired GL state
        // Recreate the VAO every time (this is to easily allow multiple GL contexts to be rendered to. VAO are not shared among GL contexts)
        // The renderer would actually work without any VAO bound, but then our VertexAttrib calls would overwrite the default one currently bound.
        GLuint vertex_array_object = 0;
#ifndef IMGUI_IMPL_OPENGL_ES2
        glGenVertexArrays(1, &vertex_array_object);
#endif
        openGLSetupRenderState(draw_data, fb_width, fb_height, vertex_array_object);

        // Will project scissor/clipping rectangles into framebuffer space
        ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
        ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

        // Render command lists
        for (int n = 0; n < draw_data->CmdListsCount; n++)
        {
            const ImDrawList* cmd_list = draw_data->CmdLists[n];

            // Upload vertex/index buffers
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * (int)sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * (int)sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

            for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
            {
                const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
                if (pcmd->UserCallback != NULL)
                {
                    // User callback, registered via ImDrawList::AddCallback()
                    // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                    if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                        openGLSetupRenderState(draw_data, fb_width, fb_height, vertex_array_object);
                    else
                        pcmd->UserCallback(cmd_list, pcmd);
                }
                else
                {
                    // Project scissor/clipping rectangles into framebuffer space
                    ImVec4 clip_rect;
                    clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
                    clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
                    clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
                    clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

                    if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
                    {
                        // Apply scissor/clipping rectangle
                        glScissor((int)clip_rect.x, (int)(fb_height - clip_rect.w), (int)(clip_rect.z - clip_rect.x), (int)(clip_rect.w - clip_rect.y));

                        // Bind texture, Draw
                        glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->GetTexID());
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_VTX_OFFSET
                        if (OpenGLImGuiBackend::currentGLData.version >= 320)
                            glDrawElementsBaseVertex(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (void*)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx)), (GLint)pcmd->VtxOffset);
                        else
#endif
                            glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (void*)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx)));
                    }
                }
            }
        }
        // Destroy the temporary VAO
#ifndef IMGUI_IMPL_OPENGL_ES2
        glDeleteVertexArrays(1, &vertex_array_object);
#endif

        // Restore modified GL state
        glUseProgram(last_program);
        glBindTexture(GL_TEXTURE_2D, last_texture);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
        if (OpenGLImGuiBackend::currentGLData.version >= 330)
            glBindSampler(0, last_sampler);
#endif
        glActiveTexture(last_active_texture);
#ifndef IMGUI_IMPL_OPENGL_ES2
        glBindVertexArray(last_vertex_array_object);
#endif
        glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
        glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
        glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
        if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
        if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
        if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
        if (last_enable_stencil_test) glEnable(GL_STENCIL_TEST); else glDisable(GL_STENCIL_TEST);
        if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
        if (OpenGLImGuiBackend::currentGLData.version >= 310) { if (last_enable_primitive_restart) glEnable(GL_PRIMITIVE_RESTART); else glDisable(GL_PRIMITIVE_RESTART); }
#endif

#ifdef GL_POLYGON_MODE
        glPolygonMode(GL_FRONT_AND_BACK, (GLenum)last_polygon_mode[0]);
#endif
        glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
        glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
  }
    void openGLRenderWindow(ImGuiViewport* viewport, void*)
    {
        if (!(viewport->Flags & ImGuiViewportFlags_NoRendererClear))
        {
            ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        openGLRenderDrawData(viewport->DrawData);
    }
    void OpenGLImGuiBackend::RenderDrawData(ImDrawData* data) {
        openGLRenderDrawData(data);
    }
    void OpenGLImGuiBackend::InitRendererInterface()
    {
        ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
        platform_io.Renderer_RenderWindow = &openGLRenderWindow;

    }
    void OpenGLImGuiBackend::ShutdownPlatformInterface()
    {

    }

    void OpenGLImGuiBackend::ShutdownRendererInterface()
    {
        ImGui::DestroyPlatformWindows();
    }
    
    void OpenGLImGuiBackend::UpdateMousePos()
    {
            // Update buttons
            ImGuiIO& io = ImGui::GetIO();
            for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
            {
                // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
                io.MouseDown[i] = currentData->MouseJustPressed[i] || glfwGetMouseButton((GLFWwindow*)currentData->Window, i) != 0;
                currentData->MouseJustPressed[i] = false;
            }

            // Update mouse position
            const ImVec2 mouse_pos_backup = io.MousePos;
            io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
            io.MouseHoveredViewport = 0;
            ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
            for (int n = 0; n < platform_io.Viewports.Size; n++)
            {
                ImGuiViewport* viewport = platform_io.Viewports[n];
                GLFWwindow* window = (GLFWwindow*)viewport->PlatformHandle;
                IM_ASSERT(window != NULL);
#ifdef __EMSCRIPTEN__
                const bool focused = true;
                IM_ASSERT(platform_io.Viewports.Size == 1);
#else
                const bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;
#endif
                if (focused)
                {
                    if (io.WantSetMousePos)
                    {
                        glfwSetCursorPos(window, (double)(mouse_pos_backup.x - viewport->Pos.x), (double)(mouse_pos_backup.y - viewport->Pos.y));
                    }
                    else
                    {
                        double mouse_x, mouse_y;
                        glfwGetCursorPos(window, &mouse_x, &mouse_y);
                        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                        {
                            // Multi-viewport mode: mouse position in OS absolute coordinates (io.MousePos is (0,0) when the mouse is on the upper-left of the primary monitor)
                            int window_x, window_y;
                            glfwGetWindowPos(window, &window_x, &window_y);
                            io.MousePos = ImVec2((float)mouse_x + window_x, (float)mouse_y + window_y);
                        }
                        else
                        {
                            // Single viewport mode: mouse position in client window coordinates (io.MousePos is (0,0) when the mouse is on the upper-left corner of the app window)
                            io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
                        }
                    }
                    for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
                        io.MouseDown[i] |= glfwGetMouseButton(window, i) != 0;
                }

                // (Optional) When using multiple viewports: set io.MouseHoveredViewport to the viewport the OS mouse cursor is hovering.
                // Important: this information is not easy to provide and many high-level windowing library won't be able to provide it correctly, because
                // - This is _ignoring_ viewports with the ImGuiViewportFlags_NoInputs flag (pass-through windows).
                // - This is _regardless_ of whether another viewport is focused or being dragged from.
                // If ImGuiBackendFlags_HasMouseHoveredViewport is not set by the backend, imgui will ignore this field and infer the information by relying on the
                // rectangles and last focused time of every viewports it knows about. It will be unaware of other windows that may be sitting between or over your windows.
                // [GLFW] FIXME: This is currently only correct on Win32. See what we do below with the WM_NCHITTEST, missing an equivalent for other systems.
                // See https://github.com/glfw/glfw/issues/1236 if you want to help in making this a GLFW feature.
#if GLFW_HAS_MOUSE_PASSTHROUGH || (GLFW_HAS_WINDOW_HOVERED && defined(_WIN32))
                const bool window_no_input = (viewport->Flags & ImGuiViewportFlags_NoInputs) != 0;
#if GLFW_HAS_MOUSE_PASSTHROUGH
                glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, window_no_input);
#endif
                if (glfwGetWindowAttrib(window, GLFW_HOVERED) && !window_no_input)
                    io.MouseHoveredViewport = viewport->ID;
#endif
        }
    }

    void OpenGLImGuiBackend::UpdateMouseCursor()
    {
        ImGuiIO& io = ImGui::GetIO();
        if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) || glfwGetInputMode((GLFWwindow*)currentData->Window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
            return;

        ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
        ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
        for (int n = 0; n < platform_io.Viewports.Size; n++)
        {
            GLFWwindow* window = (GLFWwindow*)platform_io.Viewports[n]->PlatformHandle;
            if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
            {
                // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }
            else
            {
                // Show OS mouse cursor
                // FIXME-PLATFORM: Unfocused windows seems to fail changing the mouse cursor with GLFW 3.2, but 3.3 works here.
                glfwSetCursor(window, currentData->MouseCursors[imgui_cursor] ? currentData->MouseCursors[imgui_cursor] : currentData->MouseCursors[ImGuiMouseCursor_Arrow]);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
    }
    void OpenGLImGuiBackend::UpdateGamepads()
    {
        ImGuiIO& io = ImGui::GetIO();
        memset(io.NavInputs, 0, sizeof(io.NavInputs));
        if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == 0)
            return;

        // Update gamepad inputs
#define MAP_BUTTON(NAV_NO, BUTTON_NO)       { if (buttons_count > BUTTON_NO && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > AXIS_NO) ? axes[AXIS_NO] : V0; v = (v - V0) / (V1 - V0); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }
        int axes_count = 0, buttons_count = 0;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
        const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
        MAP_BUTTON(ImGuiNavInput_Activate, 0);     // Cross / A
        MAP_BUTTON(ImGuiNavInput_Cancel, 1);     // Circle / B
        MAP_BUTTON(ImGuiNavInput_Menu, 2);     // Square / X
        MAP_BUTTON(ImGuiNavInput_Input, 3);     // Triangle / Y
        MAP_BUTTON(ImGuiNavInput_DpadLeft, 13);    // D-Pad Left
        MAP_BUTTON(ImGuiNavInput_DpadRight, 11);    // D-Pad Right
        MAP_BUTTON(ImGuiNavInput_DpadUp, 10);    // D-Pad Up
        MAP_BUTTON(ImGuiNavInput_DpadDown, 12);    // D-Pad Down
        MAP_BUTTON(ImGuiNavInput_FocusPrev, 4);     // L1 / LB
        MAP_BUTTON(ImGuiNavInput_FocusNext, 5);     // R1 / RB
        MAP_BUTTON(ImGuiNavInput_TweakSlow, 4);     // L1 / LB
        MAP_BUTTON(ImGuiNavInput_TweakFast, 5);     // R1 / RB
        MAP_ANALOG(ImGuiNavInput_LStickLeft, 0, -0.3f, -0.9f);
        MAP_ANALOG(ImGuiNavInput_LStickRight, 0, +0.3f, +0.9f);
        MAP_ANALOG(ImGuiNavInput_LStickUp, 1, +0.3f, +0.9f);
        MAP_ANALOG(ImGuiNavInput_LStickDown, 1, -0.3f, -0.9f);
#undef MAP_BUTTON
#undef MAP_ANALOG
        if (axes_count > 0 && buttons_count > 0)
            io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
        else
            io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
    }
    void OpenGLImGuiBackend::DestroyFontsTexture()
    {
        if (currentGLData.FontTexture)
        {
            ImGuiIO& io = ImGui::GetIO();
            glDeleteTextures(1, &currentGLData.FontTexture);
            io.Fonts->SetTexID(0);
            currentGLData.FontTexture = 0;
        }
    }
    GLShaderPair OpenGLImGuiBackend::getShaders()
    {
        int glsl_version = 130;
        sscanf(GLSLVersion.c_str(), "#version %d", &glsl_version);
         GLchar* frag_shader = NULL;
         GLchar* vert_shader = NULL;
        if (glsl_version < 130) {
            frag_shader = (GLchar*)m_shaderSources["opengl_120_frag"].c_str();
            vert_shader = (GLchar*)m_shaderSources["opengl_120_vert"].c_str();
        } else if(glsl_version >= 410) {
            frag_shader = (GLchar*)m_shaderSources["opengl_410_core_frag"].c_str();
            vert_shader = (GLchar*)m_shaderSources["opengl_410_core_vert"].c_str();
        } else if(glsl_version == 300) {
            frag_shader = (GLchar*)m_shaderSources["opengl_300_es_frag"].c_str();
            vert_shader = (GLchar*)m_shaderSources["opengl_300_es_vert"].c_str();
        } else {
            frag_shader = (GLchar*)m_shaderSources["opengl_130_frag"].c_str();
            vert_shader = (GLchar*)m_shaderSources["opengl_130_vert"].c_str();
        }
        return GLShaderPair(std::pair<GLchar*, GLchar*>(frag_shader, vert_shader));
    }
    GLuint OpenGLImGuiBackend::renderFragShader(GLShaderPair shaders)
    {
        GLchar* shaderString[2] = { (GLchar*)GLSLVersion.c_str(), std::get<0>(shaders) };
        auto fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragHandle, 2, shaderString, NULL);
        glCompileShader(fragHandle);
        CheckShader(fragHandle, "fragment shader");
        return fragHandle;
    }

    GLuint OpenGLImGuiBackend::renderVertShader(GLShaderPair shaders)
    {
        GLchar* shaderString[2] = { (GLchar*)GLSLVersion.c_str(), std::get<1>(shaders) };
        auto vertHandle = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertHandle, 2, shaderString, NULL);
        glCompileShader(vertHandle);
        CheckShader(vertHandle, "vertex shader");
        return vertHandle;
    }

    void OpenGLImGuiBackend::renderShaderProgram(GLuint vertHandle, GLuint fragHandle)
    {
        currentGLData.shaderHandle = glCreateProgram();
        glAttachShader(currentGLData.shaderHandle, vertHandle);
        glAttachShader(currentGLData.shaderHandle, fragHandle);
        glLinkProgram(currentGLData.shaderHandle);
        CheckProgram(currentGLData.shaderHandle, "shader program");
    }

    bool OpenGLImGuiBackend::CreateFontsTexture()
    {
        // Build texture atlas
        ImGuiIO& io = ImGui::GetIO();
        unsigned char* pixels;
        int width, height;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bit (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

        // Upload texture to graphics system
        GLint last_texture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
        glGenTextures(1, &currentGLData.FontTexture);
        glBindTexture(GL_TEXTURE_2D, currentGLData.FontTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifdef GL_UNPACK_ROW_LENGTH
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        // Store our identifier
        io.Fonts->SetTexID((ImTextureID)(intptr_t)currentGLData.FontTexture);

        // Restore state
        glBindTexture(GL_TEXTURE_2D, last_texture);

        return true;
    }



    
    bool OpenGLImGuiBackend::CheckShader(GLuint handle, const char* desc)
    {
        GLint status = 0, log_length = 0;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
        if ((GLboolean)status == GL_FALSE)
            RDSK_CORE_ERROR("[ImGui OpenGL Backend]: failed to compile {0}!", desc);
        if (log_length > 1)
        {
            ImVector<char> buf;
            buf.resize((int)(log_length + 1));
            glGetShaderInfoLog(handle, log_length, NULL, (GLchar*)buf.begin());
            RDSK_CORE_ERROR("{0}", buf.begin());
        }
        return (GLboolean)status == GL_TRUE;
    }

    bool OpenGLImGuiBackend::CheckProgram(GLuint handle, const char* desc)
    {
        GLint status = 0, log_length = 0;
        glGetProgramiv(handle, GL_LINK_STATUS, &status);
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
        if ((GLboolean)status == GL_FALSE)
            RDSK_CORE_ERROR("[ImGui OpenGL Backend]: failed to link {0}! (with GLSL '{1}')", desc, GLSLVersion);
        if (log_length > 1)
        {
            ImVector<char> buf;
            buf.resize((int)(log_length + 1));
            glGetProgramInfoLog(handle, log_length, NULL, (GLchar*)buf.begin());
            RDSK_CORE_ERROR("{0}", buf.begin());
        }
        return (GLboolean)status == GL_TRUE;
    }

   

    std::string OpenGLImGuiBackend::readFile(const std::string& path)
    {
            std::string text;
            std::ifstream textStream(path, std::ios::in | std::ios::binary);
            if (textStream) {
                textStream.seekg(0, std::ios::end);
                text.resize(textStream.tellg());
                textStream.seekg(0, std::ios::beg);
                textStream.read(&text[0], text.size());
                textStream.close();
            }
            else {
                RDSK_CORE_ERROR("Could not open file: {0}", path);
            }
            return text;
    }
}
