#version 330 core
out vec4      frag_color;
uniform float time;

const vec4 clr0 = vec4(228.0 / 255.0, 26.0 / 255.0, 28.0 / 255.0, 1.0);
const vec4 clr1 = vec4(55.0 / 255.0, 126.0 / 255.0, 184.0 / 255.0, 1.0);
const vec4 clr2 = vec4(77.0 / 255.0, 175.0 / 255.0, 74.0 / 255.0, 1.0);
const vec4 clr3 = vec4(152.0 / 255.0, 78.0 / 255.0, 163.0 / 255.0, 1.0);
const vec4 clr4 = vec4(255.0 / 255.0, 127.0 / 255.0, 0.0 / 255.0, 1.0);

vec2 p1 = vec2(350, 250);
vec2 p2 = vec2(450, 250); 
vec2 p3 = vec2(450, 350);
vec2 p4 = vec2(350, 350);
vec2 p5 = vec2(400, 400);

float line(vec2 p, vec2 a, vec2 b, float t, float d) {
  vec2 pa = p - a;
  vec2 ba = b - a;
  float time_scale = clamp((time - t) / d, 0, 1);
  ba = ba * time_scale;
  float h = clamp(dot(pa, ba) / dot(ba, ba), 0, 1);
  return length(h * ba - pa);
}

// ---
void
main() {
  vec4 color = vec4(1);
  vec2 uv = gl_FragCoord.xy;
  
  if (line(uv, p1, p4, 1, 1) < 5) {
    color = clr0;
  }
  
  if (line(uv, p4, p5, 2, 1) < 5) {
    color = clr0;
  }

  if (line(uv, p5, p3, 3, 1) < 5) {
    color = clr0;
  }

  if (line(uv, p3, p2, 4, 1) < 5) {
    color = clr0;
  }

  if (line(uv, p2, p1, 5, 1) < 5) {
    color = clr0;
  }

  if (line(uv, p1, p3, 6, 1) < 5) {
    color = clr0;
  }
  
  if (line(uv, p3, p4, 7, 1) < 5) {
    color = clr0;
  }

  if (line(uv, p4, p2, 8, 1) < 5) {
    color = clr0;
  }

  frag_color = color;
}
