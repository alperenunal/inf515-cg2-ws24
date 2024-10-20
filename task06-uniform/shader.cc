#include "shader.hh"

// ------------------------------------------------------------------------
Shader::Shader(const char *vertex_filepath, const char *fragment_filepath)
    : vertex_filepath(vertex_filepath), fragment_filepath(fragment_filepath) {
    load();
}

// ------------------------------------------------------------------------
void Shader::reload() {
    glDeleteProgram(program_ID);
    load();
}

// ------------------------------------------------------------------------
void Shader::use() { glUseProgram(program_ID); }

// ************************************************************************* //
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ToDo: Add code for the shader class below.
// *`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`*`* //
// ************************************************************************* //

// ------------------------------------------------------------------------
void Shader::load() {
    // ToDo step 1: read the source code from the given filepaths.
    GLint status;
    std::ifstream vertex_file("./vertex_shader.vs");
    std::ifstream fragment_file("./fragment_shader.fs");

    if (!vertex_file.is_open() || !fragment_file.is_open()) {
        std::cerr << "Failed to open shader files!" << std::endl;
        return;
    }

    std::stringstream vertex_stream;
    std::stringstream fragment_stream;

    vertex_stream << vertex_file.rdbuf();
    fragment_stream << fragment_file.rdbuf();

    std::string vertex_code = vertex_stream.str();
    const char *vertex_shader_src = vertex_code.c_str();

    std::string fragment_code = fragment_stream.str();
    const char *fragment_shader_src = fragment_code.c_str();

    // ToDo step 2: create and compile the shaders
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char log[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, log);
        std::cerr << "Could not compile fragment shader" << std::endl;
        std::cerr << log << std::endl;
        exit(-1);
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char log[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, log);
        std::cerr << "Could not compile fragment shader" << std::endl;
        std::cerr << log << std::endl;
        exit(-1);
    }

    // ToDo step 3: create and link the shader program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        std::cerr << "Program could not linked: " << std::endl;
        std::cerr << log << std::endl;
        exit(-1);
    }
    program_ID = program;

    // ToDo step 4: clean up unnecessary stuff
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    vertex_file.close();
    fragment_file.close();
}

// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const {
    GLint index = glGetUniformLocation(program_ID, name.c_str());
    if (index == -1) {
        std::cerr << "Could not find uniform: " << name << std::endl;
        return;
    }
    glUniform1i(index, (GLint)value);
}

// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const {
    GLint index = glGetUniformLocation(program_ID, name.c_str());
    if (index == -1) {
        std::cerr << "Could not find uniform: " << name << std::endl;
        return;
    }
    glUniform1i(index, value);
}

// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const {
    GLint index = glGetUniformLocation(program_ID, name.c_str());
    if (index == -1) {
        std::cerr << "Could not find uniform: " << name << std::endl;
        return;
    }
    glUniform1f(index, value);
}
