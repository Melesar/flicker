namespace glm
{
    glm::mat4 rotation_matrix(glm::mat4 m, glm::vec3 rotation)
    {
        quat q = quat(rotation);
        return glm::toMat4(q) * m;
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

