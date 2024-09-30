#include "ChapterLayer.h"

#include <vector>
#include <imgui.h>

// 包含坐标、法线和纹理坐标
static float verticesNAndT[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

static const glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};
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

ChapterLayer::ChapterLayer(Application* application, int width, int height)
    : m_Application(application), m_FrameBuffer(FrameBuffer(width, height)),
    m_BoxEmission("D:\\Projects\\Github\\LearnOpenGl\\resources\\images\\matrix.jpg"),
    m_BoxDiffuse("D:\\Projects\\Github\\LearnOpenGl\\resources\\images\\container2.png"),
    m_BoxSpecular("D:\\Projects\\Github\\LearnOpenGl\\resources\\images\\container2_specular.png"),
    m_BoxProgram("D:\\Projects\\Github\\LearnOpenGl\\shaders\\chapter2\\box.vert",
                    "D:\\Projects\\Github\\LearnOpenGl\\shaders\\chapter2\\box.frag"),
    m_LightProgram("D:\\Projects\\Github\\LearnOpenGl\\shaders\\chapter2\\box.vert",
                     "D:\\Projects\\Github\\LearnOpenGl\\shaders\\chapter2\\light.frag"),
    m_Camera(glm::vec3(0.0, 0.0, 3.0))
{

    m_LightMaterial.Position = glm::vec3(1.2f, 1.0f, 2.0f);
    m_LightMaterial.Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    m_LightMaterial.Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    m_LightMaterial.Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    m_LightMaterial.Specular = glm::vec3(1.0f, 1.0f, 1.0f);

    glGenVertexArrays(1, &m_CubeVAO);
    glGenBuffers(1, &m_CubeVBO);

    glBindVertexArray(m_CubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_CubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNAndT), verticesNAndT, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

ChapterLayer::~ChapterLayer()
{
    glDeleteVertexArrays(1, &m_CubeVAO);
    glDeleteBuffers(1, &m_CubeVBO);
}

void ChapterLayer::Render(double time)
{
    static glm::vec3 s_BackGroundColor(0.200f, 0.200f, 0.200f);
    ProcessInput(m_Application->GetWindow(), &m_Camera);

    double xpos, ypos;
    glfwGetCursorPos(m_Application->GetWindow(), &xpos, &ypos);
    GlfwCursorPosCallback(xpos, ypos, &m_Camera);

    ImGui::Begin("Editor");

    ImGui::ColorEdit3("Bg", &s_BackGroundColor[0]);
    m_Application->SetClearColor(s_BackGroundColor);

    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Viewport");

    ImVec2 region =ImGui::GetContentRegionAvail();

    int width, height;
    glfwGetFramebufferSize(m_Application->GetWindow(), &width, &height);
    m_FrameBuffer.RescaleFramebuffer(width, height);

    glm::mat4 projection = glm::perspective(glm::radians(m_Camera.GetZoom()), (float)width / (float)height, 0.1f, 100.0f);
    m_FrameBuffer.BindFrameBuffer(true);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_BoxEmission.GetTextureID());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_BoxDiffuse.GetTextureID());

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_BoxSpecular.GetTextureID());

    m_BoxProgram.Use();
    m_BoxProgram.SetInt("BoxMaterial.diffuse", 1);
    m_BoxProgram.SetInt("BoxMaterial.emission", 0);
    m_BoxProgram.SetInt("BoxMaterial.specular", 2);
    m_BoxProgram.SetFloat("BoxMaterial.shininess", 32.0f);
    m_BoxProgram.SetVec3("BoxLight.position", m_Camera.GetPosition());
    m_BoxProgram.SetVec3("BoxLight.direction", m_Camera.GetFront());
    m_BoxProgram.SetFloat("BoxLight.cutOff", glm::cos(glm::radians(12.5f)));
    m_BoxProgram.SetFloat("BoxLight.outerCutOff", glm::cos(glm::radians(17.5f)));
    m_BoxProgram.SetVec3("BoxLight.ambient", m_LightMaterial.Ambient);
    m_BoxProgram.SetVec3("BoxLight.diffuse", m_LightMaterial.Diffuse);
    m_BoxProgram.SetVec3("BoxLight.specular", m_LightMaterial.Specular);
    m_BoxProgram.SetFloat("BoxLight.constant", 1.0f);
    m_BoxProgram.SetFloat("BoxLight.linear", 0.09f);
    m_BoxProgram.SetFloat("BoxLight.quadratic", 0.032f);
    m_BoxProgram.SetMat4("BoxProjection", projection);
    m_BoxProgram.SetMat4("BoxView", m_Camera.GetViewMatrix());

    glBindVertexArray(m_CubeVAO);
    for (int i = 1; i <= 10; ++i)
    {
        glm::mat4 boxModel = glm::mat4(1.0f);
        boxModel = glm::translate(boxModel, cubePositions[i - 1]);
        boxModel = glm::rotate(boxModel, glm::radians(static_cast<float>(20.0f * i)), glm::vec3(1.0f, 0.3f, 0.5f));
        m_BoxProgram.SetMat4("BoxModel", boxModel);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, m_LightMaterial.Position);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));

    m_LightProgram.Use();
    m_LightProgram.SetMat4("BoxProjection", projection);
    m_LightProgram.SetMat4("BoxView", m_Camera.GetViewMatrix());
    m_LightProgram.SetMat4("BoxModel", lightModel);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);



    m_FrameBuffer.UnbindFrameBuffer();


    ImGui::Image(reinterpret_cast<ImTextureID>(m_FrameBuffer.GetTextureID()), region, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::PopStyleVar(2);
    ImGui::End();
}
