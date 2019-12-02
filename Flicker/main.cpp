#include "Application/Application.hpp"

int main(int argc, char** argv)
{
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    Flicker::Application app;
    app.run();
    return 0;
}
