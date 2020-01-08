namespace glm
{
    glm::mat4 rotation_matrix(glm::mat4 m, glm::vec3 rotation)
    {
        quat q = quat(rotation);
        m = glm::toMat4(q) * m;
        // m = glm::rotate(m, glm::radians(rotation.z), {0, 0, 1});
        // m = glm::rotate(m, glm::radians(rotation.x), {1, 0, 0});
        // m = glm::rotate(m, glm::radiaŃns(rotation.y), {0, 1, 0});

        return m;
    }

    glm::vec3 quat_to_euler(glm::quat q)
    {
        return glm::degrees(glm::eulerAngles(q));
    }

    glm::mat4 trs(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    {
        glm::mat4 trs = glm::mat4x4(1.f);
        trs = glm::translate(trs, position);
        trs = glm::rotation_matrix(trs, rotation);
        trs = glm::scale(trs, scale);

        return trs;
    }
}

