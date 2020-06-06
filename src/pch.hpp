#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <unordered_map>

const int NUM_POINT_LIGHTS = 4;
const float POINT_LIGHT_CONSTANT_ATTENUATION = 1.0f;
const float POINT_LIGHT_LINEAR_ATTENUATION = 0.09f;
const float POINT_LIGHT_QUADRATIC_ATTENUATION = 0.032f;