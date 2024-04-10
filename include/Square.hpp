#ifndef OPENGLEXERCISE_SQUARE_HPP
#define OPENGLEXERCISE_SQUARE_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Square {
public:

    enum DIRECTION
    {
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
    int getSizeOfVertices();

private:
   glm::vec3 m_Position;
   glm::vec4 m_Color;
   float m_length;

   float m_vertices[18];
   DIRECTION m_Direction;
};


#endif //OPENGLEXERCISE_SQUARE_HPP
