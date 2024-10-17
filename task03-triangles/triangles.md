### bearbeitet von Alp Eren Ünal

# OpenGL - Triangles

First I defined an array with coordinates of vertices on space as usual.
Also, I defined an another array which stores the indices of the vertices of the triangles.
These indices points to the positions at vertex array.
Vertices are stored into a VBO (Vertex Buffer Object), and indices are stored into a EBO (Element Buffer Object).
Later instead of using `glDrawArrays`, I use `glDrawElements` to render triangles.
