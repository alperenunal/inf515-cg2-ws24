#include <cmath>
#include <iostream> // used for console output

// ToDo: include necessary headers for OpenGL (GLEW, GLFW)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define COLOR(c) (((float)c) / 255.0f)

float lerp(float a, float b, float f) { return a + f * (b - a); }

int main(void) {
    std::cout << "Task02 - Change Clear Color" << std::endl;

    // ToDo step 1 - 6
    // - repeat steps from task01-window
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window =
        glfwCreateWindow(800, 600, "Task01 - Render Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    int buffer_width;
    int buffer_height;
    glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
    std::cout << "Buffer size: " << buffer_width << " x " << buffer_height
              << std::endl;
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, buffer_width, buffer_height);

    // ToDo step 7
    // - perform a smooth color change of the clear color in the render loop
    // - e.g. select a nice color palette from ColorBrewer and perform a linear
    //   interpolation between the colors

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    float colors[3][3] = {{COLOR(229), COLOR(245), COLOR(249)},
                          {COLOR(153), COLOR(216), COLOR(201)},
                          {COLOR(44), COLOR(162), COLOR(95)}};
    float red = colors[0][0];
    float green = colors[0][1];
    float blue = colors[0][2];
    float alpha = 1.0f;

    while ((!glfwWindowShouldClose(window))) {
        int target_idx = 0;
        int curr_idx = 0;
        if (red < COLOR(44)) {
            target_idx = 0;
            curr_idx = 2;
        } else if (red < COLOR(153)) {
            target_idx = 2;
            curr_idx = 1;
        } else {
            target_idx = 1;
            curr_idx = 0;
        }

        float begin[] = {colors[curr_idx][0], colors[curr_idx][1],
                         colors[curr_idx][2]};
        float *end = colors[target_idx];
        double time = glfwGetTime();
        double f = (std::sin(time) + 1) / 2;
        std::cout << f << std::endl;

        red = lerp(begin[0], end[0], f);
        green = lerp(begin[1], end[1], f);
        blue = lerp(begin[2], end[2], f);

        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ToDo step 8
    // - repeat step from task01-window
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Task02 - Shutdown" << std::endl;

    return 0;
}
