#ifndef OPENGLEXERCISE_SQUARE_HPP
#define OPENGLEXERCISE_SQUARE_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include<vector>
#include<cmath>

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

    Square(float x,float y, float length);

    glm::vec3 getPosition();
    glm::vec4 getColor();
    void move();
    void setDirection(DIRECTION direction);
    const void* getVertices();
    const void* getIndices();
    int getSizeOfVertices();
    int getSizeOfIndices();
    int getCountOfIndices();

private:
   glm::vec3 m_Position;
   glm::vec4 m_Color;
   float m_length;

   std::vector<glm::vec3> m_vertices;
   std::vector<unsigned int> m_indices;
   DIRECTION m_Direction;
};


#endif //OPENGLEXERCISE_SQUARE_HPP
