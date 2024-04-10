//
// Created by Muammer Uslu on 24.03.2024.
//

#include "Square.hpp"
#include <cstdlib>

Square::Square(float x, float y, float length)
{
    m_Position = glm::vec3 (x,y,0.0);

    m_Color.r = ((10+std::rand()) % 25) * 0.04f;
    m_Color.g = ((10+std::rand()) % 25) * 0.04f;
    m_Color.b = ((10+std::rand()) % 25) * 0.04f;

    m_length = length;

    m_Direction = NONE;


    glm::vec3 pos0;
    pos0.x = -length * 0.5f;
    pos0.y = length * 0.5f;
    pos0.z = 1.0f;

    glm::vec3 pos1;
    pos1.x = -length * 0.5f;
    pos1.y = -length * 0.5f;
    pos1.z = 1.0f;

    glm::vec3 pos2;
    pos2.x = length * 0.5f;
    pos2.y = -length * 0.5f;
    pos2.z = 1.0f;

    glm::vec3 pos3;
    pos3.x = length * 0.5f;
    pos3.y = length * 0.5f;
    pos3.z = 1.0f;

    m_vertices.push_back(pos0);
    m_vertices.push_back(pos1);
    m_vertices.push_back(pos2);
    m_vertices.push_back(pos3);

    m_indices.push_back(0);
    m_indices.push_back(1);
    m_indices.push_back(2);
    m_indices.push_back(0);
    m_indices.push_back(2);
    m_indices.push_back(3);
}


void Square::setDirection(Square::DIRECTION direction)
{
    m_Direction = direction;
}


glm::vec3 Square::getPosition()
{
    return m_Position;
}

glm::vec4 Square::getColor()
{
    return m_Color;
}

void Square::move() {

    switch (m_Direction)
    {
        case DIR_RIGHT:
            m_Position+= glm::vec3(m_length,0.0f,0.0f);
            break;
        case DIR_LEFT:
            m_Position+= glm::vec3(-m_length,0.0f,0.0f);
            break;
        case DIR_UP:
            m_Position+= glm::vec3(0.0f,m_length,0.0f);
            break;
        case DIR_DOWN:
            m_Position+= glm::vec3(0.0f,-m_length,0.0f);
            break;
        case NONE:
            break;
    }
}

const void *Square::getVertices() {
    return &m_vertices[0];
}

const void *Square::getIndices() {
    return &m_indices[0];
}

int Square::getSizeOfVertices() {
    return sizeof(glm::vec3)*m_vertices.size();
}

int Square::getSizeOfIndices() {
    return sizeof(long)*getCountOfIndices();
}

int Square::getCountOfIndices() {
    return m_indices.size();
}