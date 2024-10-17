#include <array>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ------------------------------------------------------------------------ //
/* forward declarations*/
// clang-format off
struct Scene;
void createShaderProgram(Scene&);
void createTriangleScene(Scene&);
void renderLoop(Scene const&);
// clang-format on

// ------------------------------------------------------------------------ //
/* Scene keeps global app information. An instance of Scene is sent to
   initialziation functions and to the render loop.*/
struct Scene {
    // --- window stuff
    std::string const title = "INF515 - Two Shaders";
    GLFWwindow *window = nullptr;
    int width = 800;  // window width
    int height = 600; // window height
    // --- scene stuff
    GLuint shader_program = -1; // shader program object
    GLuint VAO = -1;            // shader array object
    GLuint VBO = -1;            // vertex buffer object
};

// ------------------------------------------------------------------------ //
/** Initialize the GL framework. */
bool initGLFW() {
    if (!glfwInit()) {
        std::cout << "GLFW initilization failed!" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL min version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL max version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return true;
}

// ------------------------------------------------------------------------ //
bool initGLFWWindow(Scene &s) {
    // --- create window
    s.window = glfwCreateWindow(s.width, s.width, s.title.c_str(), NULL, NULL);
    if (!s.window) {
        std::cout << "Window creation failed!" << std::endl;
        return false;
    }
    glfwGetFramebufferSize(s.window, &s.width, &s.height);
    glfwMakeContextCurrent(s.window);
    return true;
}

// ------------------------------------------------------------------------ //
bool initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!";
        return false;
    }
    return true;
}

// ------------------------------------------------------------------------ //
int main(void) {
    Scene scene;
    // --- Scene GLFW & GLEW
    if (!initGLFW() || !initGLFWWindow(scene) || !initGLEW()) {
        glfwDestroyWindow(scene.window);
        glfwTerminate();
        return -1;
    };
    glViewport(0, 0, scene.width, scene.height);
    // --- prepare scene
    createShaderProgram(scene);
    createTriangleScene(scene);
    // --- start render loop
    renderLoop(scene);
    //--- clean up before close
    glfwTerminate();
    return 0;
}

// ************************************************************************* //
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ToDo: Add code to draw a triangle image with at least two colors.
// ToDo: Describe your approach in more detail! How does your solution work?
// ToDo: Create a creative image!
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ************************************************************************* //

const char *vertex_shader_src =
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 vertex_color;\n"
    "void main() {\n"
    "    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "    vertex_color = color;\n"
    "}";

const char *fragment_shader_src = "#version 330 core\n"
                                  "in vec3 vertex_color;\n"
                                  "out vec4 frag_color;\n"
                                  "void main() {\n"
                                  "    frag_color = vec4(vertex_color.x, "
                                  "vertex_color.y, vertex_color.z, 1.0f);\n"
                                  "}";

// ------------------------------------------------------------------------ //
void createShaderProgram(Scene &scene) {
    GLint status;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::cerr << "Could not compile vertex shader" << std::endl;
        exit(-1);
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::cerr << "Could not compile fragment shader" << std::endl;
        exit(-1);
    }

    GLuint program = glCreateProgram();
    scene.shader_program = program;

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        char log[512];
        glGetProgramInfoLog(scene.shader_program, 512, NULL, log);
        std::cerr << "Program could not linked" << std::endl;
        std::cerr << log << std::endl;
        exit(-1);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

// ------------------------------------------------------------------------ //
void createTriangleScene(Scene &scene) {
    float vertices[][2][3] = {
        {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        {{-0.5f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, 0.25f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.25f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}},
        {{0.5f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}},
        {{0.5f, -0.25f, 0.0f}, {0.0f, 1.0f, 1.0f}},
        {{0.0f, -0.5f, 0.0f}, {0.5f, 0.5f, 0.5f}},
        {{-0.25f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    };

    int indices[][3] = {
        {0, 1, 2}, {0, 3, 4}, {0, 5, 6}, {0, 7, 8},
        {0, 2, 3}, {0, 4, 5}, {0, 6, 7}, {0, 8, 1},
    };

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    scene.VAO = VAO;
    scene.VBO = VBO;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ------------------------------------------------------------------------
void renderLoop(Scene const &scene) {
    while (!glfwWindowShouldClose(scene.window)) {
        glfwPollEvents();
        glClearColor(0.192f, 0.510f, 0.741f, 1.000f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(scene.shader_program);
        glBindVertexArray(scene.VAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(scene.window);
    }
}