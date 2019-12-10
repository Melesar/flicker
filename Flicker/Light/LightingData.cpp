#include "LightingData.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include <sstream>
#include <cstring>

void Flicker::LightingData::buildLightingBuffer()
{
    int bufferSize = getBufferSize();
    glGenBuffers(1, &m_LightsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_LightsUBO);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, BUFFER_BINDING, m_LightsUBO);

    const int uniformCount = NUM_VARS * NUM_POINT_LIGHTS;
    GLuint indices[uniformCount];
    GLint offsets[uniformCount];

    glGetUniformIndices(m_ProgramID, uniformCount, m_UniformNames, indices);
    glGetActiveUniformsiv(m_ProgramID, uniformCount, indices, GL_UNIFORM_OFFSET, offsets);

    size_t numLights = m_PointLights.size();
    for(size_t light = 0; light < NUM_POINT_LIGHTS; ++light)
    {
        PointLightData pointLightData = light < numLights 
        ? PointLightData {m_PointLights[light]}
        : PointLightData {};

        int var = 0;
        glBufferSubData(GL_UNIFORM_BUFFER, offsets[light * NUM_VARS + var++], sizeof(glm::vec3), &pointLightData.position);
        glBufferSubData(GL_UNIFORM_BUFFER, offsets[light * NUM_VARS + var++], sizeof(glm::vec3), &pointLightData.ambient);
        glBufferSubData(GL_UNIFORM_BUFFER, offsets[light * NUM_VARS + var++], sizeof(glm::vec3), &pointLightData.diffuse);
        glBufferSubData(GL_UNIFORM_BUFFER, offsets[light * NUM_VARS + var++], sizeof(glm::vec3), &pointLightData.specular);

        glBufferSubData(GL_UNIFORM_BUFFER, offsets[light * NUM_VARS + var++], sizeof(float), &pointLightData.constant);
        glBufferSubData(GL_UNIFORM_BUFFER, offsets[light * NUM_VARS + var++], sizeof(float), &pointLightData.linear);
        glBufferSubData(GL_UNIFORM_BUFFER, offsets[light * NUM_VARS + var++], sizeof(float), &pointLightData.quadrant);
    }
}

GLint Flicker::LightingData::getBufferSize() const
{
    GLint bufferSize;

    glGetActiveUniformBlockiv(m_ProgramID, BUFFER_BINDING, GL_UNIFORM_BLOCK_DATA_SIZE, &bufferSize);

    return bufferSize;
}

Flicker::PointLight* Flicker::LightingData::addPointLight(glm::vec3 position)
{
    if (pointLightsCount() >= NUM_POINT_LIGHTS)
    {
        return nullptr;
    }

    PointLight& light = m_PointLights.emplace_back();
    light.setPosition(position);

    return &light;
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