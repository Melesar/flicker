#include "LightingData.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include <sstream>
#include <cstring>

void Flicker::LightingData::buildLightingBuffer()
{
    createBuffer();
    setDirectionalLight();
    setPointLights();

    m_IsBuilt = true;
}

GLint Flicker::LightingData::getBufferSize() const
{
    GLint bufferSize;

    glGetActiveUniformBlockiv(m_ProgramID, BUFFER_BINDING, GL_UNIFORM_BLOCK_DATA_SIZE, &bufferSize);

    return bufferSize;
}

void Flicker::LightingData::createBuffer()
{
    int bufferSize = getBufferSize();
    glGenBuffers(1, &m_LightsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_LightsUBO);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, BUFFER_BINDING, m_LightsUBO);
}

void Flicker::LightingData::setDirectionalLight()
{
    const int baseOffset = 16;
    const int size = sizeof(glm::vec3);
    const int propsCount = 4;

    DirectionalLightData data = m_DirectionalLight != nullptr ? DirectionalLightData(*m_DirectionalLight) : DirectionalLightData();

    glm::vec3* ptr = reinterpret_cast<glm::vec3*>(&data);

    for(int i = 0; i < propsCount; i++)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, i * baseOffset, size, ptr);

        ptr++;
    }
}

void Flicker::LightingData::setPointLights()
{
    GLuint indices[POINT_LIGHT_UNIFORMS_COUNT];

    glGetUniformIndices(m_ProgramID, POINT_LIGHT_UNIFORMS_COUNT, m_PointLightUniformNames, indices);
    glGetActiveUniformsiv(m_ProgramID, POINT_LIGHT_UNIFORMS_COUNT, indices, GL_UNIFORM_OFFSET, m_PointLightUniformOffsets);

    size_t numLights = m_PointLights.size();
    for(size_t light = 0; light < NUM_POINT_LIGHTS; ++light)
    {
        PointLightData pointLightData = light < numLights 
        ? PointLightData {m_PointLights[light]}
        : PointLightData {};

        setPointLightData(light, POINT_LIGHT_POSITION, pointLightData.position);
        setPointLightData(light, POINT_LIGHT_AMBIENT, pointLightData.ambient);
        setPointLightData(light, POINT_LIGHT_DIFFUSE, pointLightData.diffuse);
        setPointLightData(light, POINT_LIGHT_SPECULAR, pointLightData.specular);
        setPointLightData(light, POINT_LIGHT_CONSTANT, pointLightData.constant);
        setPointLightData(light, POINT_LIGHT_LINEAR, pointLightData.linear);
        setPointLightData(light, POINT_LIGHT_QUADRANT, pointLightData.quadrant);
    }
}

Flicker::PointLight* Flicker::LightingData::addPointLight(glm::vec3 position)
{
    if (pointLightsCount() >= NUM_POINT_LIGHTS)
    {
        return nullptr;
    }

    PointLight& light = m_PointLights.emplace_back();
    light.setWorldPosition(position);

    return &light;
}

Flicker::DirectionalLight* Flicker::LightingData::createDirectionalLight(glm::vec3 direction)
{
    m_DirectionalLight = std::make_unique<DirectionalLight>();
    m_DirectionalLight->direction = direction;

    return m_DirectionalLight.get();
}

void Flicker::LightingData::setPointLightPosition(size_t lightIndex, glm::vec3 position)
{
    assert(lightIndex < NUM_POINT_LIGHTS);

    Flicker::PointLight& lightObject = m_PointLights[lightIndex];
    lightObject.setWorldPosition(position);

    setPointLightData(lightIndex, POINT_LIGHT_POSITION, position, true);
}

glm::vec3 Flicker::LightingData::getPointLightPosition(size_t lightIndex)
{
    assert(lightIndex < NUM_POINT_LIGHTS);

    return m_PointLights[lightIndex].worldPosition();
}

int Flicker::LightingData::pointLightsCount() const
{
    return m_PointLights.size();
}

Flicker::LightingData::LightingData()
{
    m_PointLights.reserve(NUM_POINT_LIGHTS);

    std::shared_ptr<Flicker::Shader> program = Flicker::Assets::loadShader("lit");

    m_ProgramID = program->getID();
}