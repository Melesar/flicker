#include "model_import.hpp"
#include "Model.hpp"


std::shared_ptr<Flicker::Node> Flicker::parse_scene(const aiScene* scene)
{
    return std::make_shared<Node>();
}