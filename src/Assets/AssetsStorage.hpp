#pragma once
#include <ecs/mpl.hpp>
#include <Data/Data.hpp>

namespace Flicker
{
    class AssetsStorage
    {
    private:
        template<typename T>
        using Storage = std::vector<T>;
        
    public:
       
        Handle addShader(const std::string& shaderName);
        Handle createMaterial(Handle shaderHandle);
        Handle createMesh(const std::vector<Vertex>& verices, const std::vector<size_t>& indices);

        template<typename T>
        T& getAsset(Handle handle) { return std::get<std::vector<T>>(m_Storage)[handle.Index]; }

    private:

        template<typename T>
        Storage<T>& getStorage() { return std::get<Storage<T>>(m_Storage); }
        
    private:
        mpl::TupleOfVectors<Shader, Material, Mesh, Texture> m_Storage;
    };
}
