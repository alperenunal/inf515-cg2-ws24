// ToDo: adapt the shaders so that
// - the colormode can be changed
// - the triangle resizes

#version 330 core
out vec4 frag_color;
in vec3 our_color;
uniform int color_mode;
void main(){
  frag_color = vec4(0.0, 0.0, 0.0, 1.0);
  int r = (color_mode&0x30) >> 4;
  int g = (color_mode&0x0c) >> 2;
  int b = (color_mode&0x03);
  
  if (r == 2) {
    frag_color.x = our_color.y;
  } else if (r == 3) {
    frag_color.x = our_color.z;
  } else {
    frag_color.x = our_color.x;
  }
  
  if (g == 1){
    frag_color.y = our_color.x;
  } else if (g == 3) {
    frag_color.y = our_color.z;
  } else {
    frag_color.y = our_color.y;
  }
  
  if (b == 1) {
    frag_color.z = our_color.x;
  } else if (b == 2) {
    frag_color.z = our_color.y;
  } else {
    frag_color.z = our_color.z;
  }
}