#ifndef OPENGLEXERCISE_SQUARE_HPP
#define OPENGLEXERCISE_SQUARE_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <cmath>
#include<glm/gtx/matrix_transform_2d.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 tex;
};

struct Transform{
    float rotation;
    glm::vec3 position;
    float scale;
};

class Square {
public:

    enum DIRECTION
    {
        NONE,
        DIR_RIGHT = 1,
        DIR_LEFT =-1,
        DIR_UP = 2,
        DIR_DOWN = -2
    };

    enum SCALE
    {
        UP,
        DOWN
    };


    enum ROTATE
    {
        CLOCKWISE,
        COUNTER_CLOCKWISE
    };

    Square(float x,float y, float length);

    glm::vec4 getColor();
    void move(DIRECTION direction);
    void scale(SCALE scale);
    void rotate(ROTATE rotate);
    const void* getVertices();
    const void* getIndices();
    const glm::mat3* getTransformMatrix();
    int getSizeOfVertices();
    int getSizeOfIndices();
    int getCountOfIndices();

private:
   glm::vec4 m_Color;
   float m_length;
   Transform m_transform;
   glm::mat3 m_transformMatrix; // pointer ile gönderiliyor. O yüzden belirli bir adrese sahip olması gerekiyor.
   std::vector<Vertex> m_vertices;
   std::vector<unsigned int> m_indices;
};



#endif //OPENGLEXERCISE_SQUARE_HPP
