#include "Renderer.hpp"
#include "Assets/Assets.hpp"
#include "Transform/Camera.hpp"
#include "Models/Model.hpp"
#include "Material/LitMaterial.hpp"
#include "Transform/Transform.hpp"
// #include "Light/PointLight.hpp"
#include "Light/LightUniformData.hpp"

void Flicker::Renderer::render(Camera* camera)
{
    glClearColor(0.14f, 0.43f, 0.85f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderScene(camera);
}

void Flicker::Renderer::onWindowResize(GLFWwindow* window, int width, int height)
{
    m_Width = width;
    m_Height = height;
    
    glViewport(0, 0, m_Width, m_Height);
}

void Flicker::Renderer::setupUniformBuffers()
{
    glGenBuffers(1, &m_CameraUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_CameraUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4) + sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_CameraUBO);

    Flicker::LightUniformData lightData;
    for(int i = 0; i < m_Lights.size(); i++)
    {
        PointLightUniformData& data = lightData.pointLights[i];
        
        data = PointLightUniformData(m_Lights[i]);
    }

    glGenBuffers(1, &m_LightsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_LightsUBO);
    glBufferData(GL_UNIFORM_BUFFER, 320, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_LightsUBO);

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), &lightData.pointLights[0].position);
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::vec4), sizeof(glm::vec3), &lightData.pointLights[0].ambient);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec3), &lightData.pointLights[0].diffuse);
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4), sizeof(glm::vec3), &lightData.pointLights[0].specular);
    glBufferSubData(GL_UNIFORM_BUFFER, 60, sizeof(float), &lightData.pointLights[0].constant);
    glBufferSubData(GL_UNIFORM_BUFFER, 64, sizeof(float), &lightData.pointLights[0].linear);
    glBufferSubData(GL_UNIFORM_BUFFER, 68, sizeof(float), &lightData.pointLights[0].quadrant);

    std::cout << "alignment" << '\t' << "offset" << std::endl;
    for(int i = 0; i < 4; ++i)
    {
        std::cout << sizeof(glm::vec4) << '\t' << i * sizeof(glm::vec4) << std::endl;
    }

    for(int i = 0; i < 3; ++i)
    {
        std::cout << sizeof(float) << '\t' << 4 * sizeof(glm::vec4) + i * sizeof(float) << std::endl;
    }
}

Flicker::Renderer::Renderer(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glfwGetWindowSize(window, &m_Width, &m_Height);

    glViewport(0, 0, m_Width, m_Height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  

    m_Lights.emplace_back();
    Flicker::PointLight& light = m_Lights[0];
    Flicker::Transform& lightTransform = light.transform;
    lightTransform.position = {-3, 2, -3};


    m_Model = Flicker::Assets::loadModel("teapot.fbx");
    m_Model->getMaterial<LitMaterial>(0)->setColor({1, 0.534, 0.874, 1});
    Flicker::Transform& modelTransform = m_Model->transform;
    modelTransform.position = {0, -1, -3};

    setupUniformBuffers();

    // glfwSetFramebufferSizeCallback(window, &onWindowResize);
}

