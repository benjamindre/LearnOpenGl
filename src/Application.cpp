#include "Application.h"

#include <stb_image.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

#include <cassert>

static const char* kGlslVersion = "#version 130";

static void GlfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Application::Application(int width, int height, std::string_view title)
    : m_Width(width), m_Height(height), m_Title(title), m_ClearColor(glm::vec3(0.0f)), m_GlDepthTest(false),
    m_GlfWwindow(nullptr)
{
    glfwSetErrorCallback(GlfwErrorCallback);

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    m_GlfWwindow = glfwCreateWindow(m_Width, m_Height, m_Title.data(), nullptr, nullptr);
    if (!m_GlfWwindow)
    {
        assert(false && "glfwCreateWindow failed.");
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_GlfWwindow);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(m_GlfWwindow, ViewportResizeCallback);

    // 初始化 glad
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        assert(false && "gladLoadGLLoader failed.");
        glfwTerminate();
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    ImGui_ImplGlfw_InitForOpenGL(m_GlfWwindow, true);
    ImGui_ImplOpenGL3_Init(kGlslVersion);
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_GlfWwindow);
    glfwTerminate();
}

void Application::Run(const SRef<DockSpace>& dockSpace) const
{
    while (!glfwWindowShouldClose(m_GlfWwindow))
    {
        double glfwTime = glfwGetTime();
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (dockSpace)
            dockSpace->Render();

        ImGui::Render();

        glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, 1.0f);
        if (m_GlDepthTest)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        else
            glClear(GL_COLOR_BUFFER_BIT);


        for (auto& layer : m_Layers)
            layer->Render(glfwTime);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(m_GlfWwindow);
    }
}

void Application::SetIcon(std::string_view filename) const
{
    int channels;
    GLFWimage iconImage;
    iconImage.pixels = stbi_load(filename.data(), &iconImage.width, &iconImage.height, &channels, 0);

    glfwSetWindowIcon(m_GlfWwindow, 1, &iconImage);

    stbi_image_free(iconImage.pixels);
}

void Application::SetIniFilename(const char* filename)
{
    ImGui::GetIO().IniFilename = filename;
}


void Application::SetClearColor(const glm::vec3& color)
{
    m_ClearColor = color;
}

void Application::GlEnable(uint32_t model)
{
    if (model == GL_DEPTH_TEST)
        m_GlDepthTest = true;

    glEnable(model);
}

void Application::PushLayer(SRef<IOpenGlLayer>&& layer)
{
    m_Layers.emplace_back(layer);
}


void Application::ViewportResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}