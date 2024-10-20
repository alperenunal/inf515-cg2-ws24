// ToDo: adapt the shaders so that
// - the colormode can be changed
// - the triangle resizes

#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
out vec3 our_color;
uniform float scale;
void main(){
  gl_Position = vec4(pos.x * scale, pos.y * scale, pos.z * scale, 1.0);
  our_color = color;
}