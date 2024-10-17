### bearbeitet von Alp Eren Ünal

# OpenGL - Two Colors

In order to render triangles with different colors, I first changed the vertex shader. Instead of just giving the position of a vertex, I defined an input to receive color input. The given color is passed to fragment shader, and the fragment shader keeps it as is. With this change we change the our program to include the desired color with position, i.e. a stride of the input given to VBO looks like this: [position.x, position.y, position.z, color.red, color.blue, color.green]. Also, we inform VAO with `glVertexAttribPointer` to pass the given color input, so in our vertex shader when `location` is 0, the input is position, and when it's 1, the input is color.
