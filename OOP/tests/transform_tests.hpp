#include "Scene/Node.hpp"

void test_local_values()
{
    Flicker::Node t;
    t.setLocal({1, 2, 0}, {45, 142, 12});

    glm::mat4 locToWorld = t.localToWorldMatrix();
    assert(glm::abs(locToWorld[0][0] + 0.6802) < 0.001f);
    assert(glm::abs(locToWorld[0][1] - 0.5896) < 0.001f);
    assert(glm::abs(locToWorld[0][2] - 0.4353) < 0.001f);
    assert(glm::abs(locToWorld[0][3] - 1) < 0.001f);

}

void run_transform_tests()
{
    test_local_values();
}
