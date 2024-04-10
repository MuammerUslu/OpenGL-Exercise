//
// Created by Muammer Uslu on 24.03.2024.
//

#include "Square.hpp"
#include <cstdlib>

Square::Square(float x, float y, float length)
{
    m_Color.r = ((10+std::rand()) % 25) * 0.04f;
    m_Color.g = ((10+std::rand()) % 25) * 0.04f;
    m_Color.b = ((10+std::rand()) % 25) * 0.04f;

    m_length = length;

    m_transform.rotation=0.0f;
    m_transform.position = glm::vec2(0.0f,0.0f);
    m_transform.scale = 1.0f;


    glm::vec3 pos0;
    pos0.x = -m_length * 0.5f;
    pos0.y = m_length * 0.5f;
    pos0.z = 1.0f;

    glm::vec3 pos1;
    pos1.x = -m_length * 0.5f;
    pos1.y = -m_length * 0.5f;
    pos1.z = 1.0f;

    glm::vec3 pos2;
    pos2.x = m_length * 0.5f;
    pos2.y = -m_length * 0.5f;
    pos2.z = 1.0f;

    glm::vec3 pos3;
    pos3.x = m_length * 0.5f;
    pos3.y = m_length * 0.5f;
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

glm::vec4 Square::getColor()
{
    return m_Color;
}

void Square::move(Square::DIRECTION direction) {

    switch (direction)
    {
        case DIR_RIGHT:
            m_transform.position.x += 0.1f;
            break;
        case DIR_LEFT:
            m_transform.position.x -= 0.1f;
            break;
        case DIR_UP:
            m_transform.position.y += 0.1f;
            break;
        case DIR_DOWN:
            m_transform.position.y -= 0.1f;
            break;
        case NONE:
            break;

    }
}

void Square::scale(Square::SCALE direction)
{
    switch (direction)
    {
        case UP:
            m_transform.scale += 0.1f;
            break;
        case DOWN:
            m_transform.scale -= 0.1f;
            break;
    }
}

void Square::rotate(Square::ROTATE rotate)
{

    switch (rotate)
    {
        case CLOCKWISE:
            m_transform.rotation += 10;
            break;
        case COUNTER_CLOCKWISE:
            m_transform.rotation -= 10;
            break;
    }
}

const glm::mat3* Square::getTransformMatrix()
{

    glm::mat3 mtxRotation = glm::rotate(glm::mat3(1), glm::radians(m_transform.rotation));
    glm::mat3 mtxTranslation = glm::translate(glm::mat3(1),m_transform.position);
    glm::mat3 mtxScale =glm::scale(glm::mat3(1),glm::vec2(m_transform.scale,m_transform.scale));
    m_transform.transformMatrix = mtxTranslation * mtxRotation * mtxScale;

    return &m_transform.transformMatrix;
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
    return sizeof(unsigned int)*getCountOfIndices();
}

int Square::getCountOfIndices() {
    return m_indices.size();
}




