#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hh"

/*
    Color mode is a single byte that represents the color mode of the shader.
    It is encoded as 00RRBBGG. Two bits for each color channel.
    Bits 00 indicates the default color of that color channel.
    Bits 01 -> red, 10 -> green, 11 -> blue.
*/
enum ColorMode {
    RRR = 0b00010101,
    RRG = 0b00010110,
    RRB = 0b00010111,
    RGR = 0b00011001,
    RGG = 0b00011010,
    RGB = 0b00011011,
    RBR = 0b00011101,
    RBG = 0b00011110,
    RBB = 0b00011111,
    GRR = 0b00100101,
    GRG = 0b00100110,
    GRB = 0b00100111,
    GGR = 0b00101001,
    GGG = 0b00101010,
    GGB = 0b00101011,
    GBR = 0b00101101,
    GBG = 0b00101110,
    GBB = 0b00101111,
    BRR = 0b00110101,
    BRG = 0b00110110,
    BRB = 0b00110111,
    BGR = 0b00111001,
    BGG = 0b00111010,
    BGB = 0b00111011,
    BBR = 0b00111101,
    BBG = 0b00111110,
    BBB = 0b00111111,
};

void setColorMode(const Shader &shader, const ColorMode mode) {
    shader.setInt("color_mode", mode);
}

// ------------------------------------------------------------------------ //
/* Settings keeps global app information. */
struct Settings {
    std::string const title = "INF515 - Uniforms";
    int window_width = 800;
    int window_height = 600;
    GLFWwindow *window = nullptr;
    int buffer_width = -1;
    int buffer_height = -1;
};

// ------------------------------------------------------------------------ //
/** Initialize the GL framework. */
bool initGLFW() {
    if (!glfwInit()) {
        std::cout << "GLFW initilization failed!";
        glfwTerminate();
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL min version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL max version
    // core profile -> do not allow backward compatability
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // core profile -> do allow foward compatability
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return true;
}

// ------------------------------------------------------------------------ //
bool initGLFWWindow(Settings &s) {
    // --- create window
    s.window = glfwCreateWindow(s.window_width, s.window_height,
                                s.title.c_str(), NULL, NULL);
    if (!s.window) {
        std::cout << "Window creation failed!" << std::endl;
        return false;
    }
    // --- read frame buffer size
    glfwGetFramebufferSize(s.window, &s.buffer_width, &s.buffer_height);
    // --- set context for GLFW to use
    glfwMakeContextCurrent(s.window);
    std::cout << "window created" << std::endl;
    return true;
}

// ------------------------------------------------------------------------ //
bool initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!" << std::endl;
        return false;
    }
    std::cout << "GLEW initialized" << std::endl;
    return true;
}

// ------------------------------------------------------------------------ //
void renderLoop(Settings &s) {
    Shader our_shader = Shader{"vertex_shader.vs", "fragment_shader.fs"};

    struct Color {
        Color(int ri, int gi, int bi)
            : r{ri / 255.f}, g{gi / 255.f}, b{bi / 255.f} {};
        float r = 0;
        float g = 0;
        float b = 0;
    };
    Color c0{27, 158, 119};
    Color c1{55, 126, 184};
    Color c2{255, 127, 0};
    Color c3{152, 78, 163};

    // --- set up vertex data (and buffers) and configure vertex attributes
    // clang-format off
  float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  c1.r, c1.g, c1.b,  // bottom right
    -0.5f, -0.5f, 0.0f,  c2.r, c2.g, c2.b,  // bottom left
     0.0f,  0.5f, 0.0f,  c3.r, c3.g, c3.b   // top
  };
    // clang-format on

    unsigned int VBO = 0;
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ColorMode modes[] = {RRR, RRG, RRB, RGR, RGB, RGG, RBR, RBG, RBB,
                         GRR, GRG, GRB, GGR, GGG, GGB, GBR, GBG, GBB,
                         BRR, BRG, BRB, BGR, BGG, BGB, BBR, BBG, BBB};
    int mode_index = -1;

    // --- render loop
    while (!glfwWindowShouldClose(s.window)) {
        //--- poll for and process events like mouse input
        glfwPollEvents();

        // ToDo: Close the window, when ESC is pressed.
        if (glfwGetKey(s.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(s.window, true);
        }
        // ToDo: Reload the shader, when key 1 is pressed.
        if (glfwGetKey(s.window, GLFW_KEY_1) == GLFW_PRESS) {
            mode_index = -1;
            our_shader.reload();
        }
        // ToDo: Switch color mode, when key 2 is pressed.
        if (glfwGetKey(s.window, GLFW_KEY_2) == GLFW_PRESS) {
            mode_index = (mode_index + 1) % 27;
            setColorMode(our_shader, modes[mode_index]);
        }
        // ToDo: Scale the triangle over time.
        float time = glfwGetTime();
        float scale = std::sin(time) / 2 + 0.5;
        our_shader.setFloat("scale", scale);

        // --- clear the window
        glClearColor(c0.r, c0.g, c0.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        our_shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // --- swap front and back buffers (we use double buffering) ---//
        glfwSwapBuffers(s.window);
    }
}

// ------------------------------------------------------------------------ //
int main(void) {
    Settings settings;
    // --- setup GLFW
    if (!initGLFW() || !initGLFWWindow(settings)) {
        glfwTerminate();
        return -1;
    };

    // --- setup GLEW
    if (!initGLEW()) {
        glfwDestroyWindow(settings.window);
        glfwTerminate();
        return -1;
    }

    // --- setup viewport size
    glViewport(0, 0, settings.buffer_width, settings.buffer_height);
    // --- render
    renderLoop(settings);
    //--- clean up before close
    glfwTerminate();
    return 0;
}