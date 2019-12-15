#include "Application/Application.hpp"
#include "tests/tests.hpp"

int main(int argc, char** argv)
{
    //run_tests();

    Flicker::Application app;
    app.run();

    return 0;
}
