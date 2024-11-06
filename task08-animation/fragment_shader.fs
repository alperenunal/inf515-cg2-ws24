#version 330 core
out vec4      frag_color;
uniform float time;

const vec4 clr0 = vec4(228.0 / 255.0, 26.0 / 255.0, 28.0 / 255.0, 1.0);
const vec4 clr1 = vec4(55.0 / 255.0, 126.0 / 255.0, 184.0 / 255.0, 1.0);
const vec4 clr2 = vec4(77.0 / 255.0, 175.0 / 255.0, 74.0 / 255.0, 1.0);
const vec4 clr3 = vec4(152.0 / 255.0, 78.0 / 255.0, 163.0 / 255.0, 1.0);
const vec4 clr4 = vec4(255.0 / 255.0, 127.0 / 255.0, 0.0 / 255.0, 1.0);

vec2 p1 = vec2(300, 225); // bottom left
vec2 p2 = vec2(500, 225); // bottom right 
vec2 p3 = vec2(500, 375); // top right
vec2 p4 = vec2(300, 375); // top left
vec2 p5 = vec2(400, 450); // top center

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
  vec4 white = vec4(1);
  vec4 color = vec4(1);
  vec2 uv = gl_FragCoord.xy;

  if (time > 1) {
    float dist = line(uv, p1, p4, 1, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  }

  if (time > 2) {
    float dist = line(uv, p4, p5, 2, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  }

  if (time > 3) {
    float dist = line(uv, p5, p3, 3, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  }

  if (time > 4) {
    float dist = line(uv, p3, p2, 4, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  }

  if (time > 5) {
    float dist = line(uv, p2, p1, 5, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  }

  if (time > 6) {
    float dist = line(uv, p1, p3, 6, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  } 

  if (time > 7) {
    float dist = line(uv, p3, p4, 7, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  }

  if (time > 8) {
    float dist = line(uv, p4, p2, 8, 1);
    if (dist < 5) {
      dist = smoothstep(0.025, 0.03, dist);
      color = mix(white, clr0, dist);
      frag_color = color;
    }
  }

  frag_color = color;
}
