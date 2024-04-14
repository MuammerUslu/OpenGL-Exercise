#ifndef OPENGLEXERCISE_CUBE_HPP
#define OPENGLEXERCISE_CUBE_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <cmath>
#include<glm/gtx/matrix_transform_2d.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec4 color;
    glm::vec2 texCoord;
};

struct Transform{
    float rotation;
    glm::vec3 position;
    float scale;
};

class cube {
public:
    cube(float length);
    void move();
    void scale();
    void rotate();
    const void* getVertices();
    const void* getIndices();
    const glm::mat4* getTransformMatrix();
    int getSizeOfVertices();
    int getSizeOfIndices();
    int getCountOfIndices();

private:
   float m_length;
   Transform m_transform;
   glm::mat4 m_transformMatrix; // pointer ile gönderiliyor. O yüzden belirli bir adrese sahip olması gerekiyor.
   std::vector<Vertex> m_vertices;
   std::vector<unsigned int> m_indices;
};



#endif //OPENGLEXERCISE_CUBE_HPP
