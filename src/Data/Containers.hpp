#pragma once

#include "Components.hpp"
#include "Data.hpp"

namespace Flicker
{
    // class Material;
    struct Shader;

    template<int SIZE>
    struct DataContainer
    {
        template<typename T>
        using DataArray = std::array<T, SIZE>;

        uint16_t Count;
        DataArray<uint16_t> Generations;
    };

    struct SceneHierarchy : public DataContainer<512>
    {
        DataArray<uint16_t> Parents;
        DataArray<glm::mat4> Local;
        DataArray<glm::mat4> Global;
    };

    struct MeshesStorage : public DataContainer<512>
    {
        DataArray<GLuint> VertexBuffers;
        DataArray<GLuint> IndexBuffers;
        // DataArray<Material> Materials;
        DataArray<uint32_t> TrisCounts;
    };

    struct ShadersStorage : public DataContainer<4>
    {
        DataArray<Shader> Shaders;
    };

    struct ModelsStorage : public DataContainer<8>
    {
        DataArray<ModelEntity> Models;
    };

    template<int SIZE>
    void clear (DataContainer<SIZE>& container)
    {
        container.Count = 0;
        memset(&container.Generations, 0, SIZE);
    }

    ShaderHandle add_shader(ShadersStorage& container, Shader shader);

    template<typename T>
    T* create_container()
    {
        T* container = new T();
        clear(*container);
        return container;
    }

    template<typename T>
    void free_container(T* container)
    {
        delete container;
    }

    struct RenderingWorld
    {
        MeshesStorage MeshesStorage;
        ShadersStorage ShadersStorage;

        RenderingWorld()
        {
            clear(MeshesStorage);
            clear(ShadersStorage);
        }
    };
}