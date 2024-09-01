#include "ModelLayer.h"

#include <imgui.h>

static bool kFirstMouse = true;
static float kLastX = 800.0f / 2.0f;
static float kLastY = 600.0f / 2.0f;

static void ProcessInput(GLFWwindow* window, Camera* camera)
{
    static float lastTime = glfwGetTime();
    static float deltaTime = 0.0f;

    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

static void GlfwCursorPosCallback(double xpos, double ypos, Camera* camera)
{
    if (kFirstMouse)
    {
        kLastX = xpos;
        kLastY = ypos;
        kFirstMouse = false;
    }

    float xoffset = xpos - kLastX;
    float yoffset = kLastY - ypos;
    kLastX = xpos;
    kLastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

ModelLayer::ModelLayer(Application* application)
    : m_Application(application), m_FrameBuffer(FrameBuffer(m_Application->GetWidth(), m_Application->GetHeight())),
    m_ShaderProgram("D:\\Projects\\Github\\LearnOpenGl\\shaders\\chapter3\\model_loading.vert", "D:\\Projects\\Github\\LearnOpenGl\\shaders\\chapter3\\model_loading.frag"),
    m_Model("D:\\Projects\\Github\\LearnOpenGl\\resources\\model\\nanosuit\\nanosuit.obj"),
    m_Camera(glm::vec3(0.0f, 0.0f, 6.0f))
{

}

void ModelLayer::Render(double time)
{
    static glm::vec3 s_BackGroundColor(0.200f, 0.200f, 0.200f);
    ProcessInput(m_Application->GetWindow(), &m_Camera);

//    double xpos, ypos;
//    glfwGetCursorPos(m_Application->GetWindow(), &xpos, &ypos);
//    GlfwCursorPosCallback(xpos, ypos, &m_Camera);

    ImGui::Begin("Editor");
    ImGui::ColorEdit3("Bg", &s_BackGroundColor[0]);
    m_Application->SetClearColor(s_BackGroundColor);

    ImGui::End();


    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Viewport");
    ImVec2 size = ImGui::GetContentRegionAvail();

    int width, height;
    glfwGetFramebufferSize(m_Application->GetWindow(), &width, &height);
    m_FrameBuffer.RescaleFramebuffer(width, height);

    glm::mat4 projection = glm::perspective(glm::radians(m_Camera.GetZoom()), (float)width / (float)height, 0.1f, 100.0f);

    m_FrameBuffer.BindFrameBuffer(true);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

    m_ShaderProgram.Use();
    m_ShaderProgram.SetMat4("Projection", projection);
    m_ShaderProgram.SetMat4("View", m_Camera.GetViewMatrix());
    m_ShaderProgram.SetMat4("Model", model);
    m_Model.Draw(&m_ShaderProgram);

    m_FrameBuffer.UnbindFrameBuffer();

    ImGui::Image(reinterpret_cast<ImTextureID>(m_FrameBuffer.GetTextureID()), size, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::PopStyleVar(2);
    ImGui::End();
}