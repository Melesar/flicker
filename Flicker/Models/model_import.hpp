#pragma once

namespace Flicker
{
    class Node;

    std::shared_ptr<Node> parse_scene(const aiScene* scene, const std::string& filePath);
}
