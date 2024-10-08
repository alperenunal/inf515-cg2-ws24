#include <iostream> // used for console output

// ToDo: include necessary headers for OpenGL (GLEW, GLFW)
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) {
    std::cout << "Task01 - Initialize a Render Window" << std::endl;

    // ToDo step 1
    // - initialize GLFW
    // - exit if initialization fails
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // ToDo step 2
    // - set the properties of GLFW
    // - us OpenGL version
    // - use the core profile, i.e. no backwards compatibility
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // ToDo step 3
    // - create a window
    // - 800 x 600 pixels
    // - exit if window creation fails
    GLFWwindow *window =
        glfwCreateWindow(800, 600, "Task01 - Render Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ToDo step 4
    // - read the buffer size (window dimensions)
    // - set the render context to the current window
    int buffer_width;
    int buffer_height;
    glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
    std::cout << "Buffer size: " << buffer_width << " x " << buffer_height
              << std::endl;
    glfwMakeContextCurrent(window);

    // ToDo step 5
    // - setup GLEW
    // - allow GLEW to use experimental functions
    // - clean up and exit if this fails
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // ToDo step 6
    // - set up the viewport with the buffer size
    glViewport(0, 0, buffer_width, buffer_height);

    // ToDo step 7
    // - run a loop in which you clear the viewport
    // - set the clear color to a value of your choice
    // - swap front an back buffer to show the result
    while ((!glfwWindowShouldClose(window))) {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ToDo step 8
    // - clean everything up
    // - exit the program
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Task01 - Shutdown" << std::endl;

    return 0;
}
