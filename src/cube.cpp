//
// Created by Muammer Uslu on 24.03.2024.
//

#include "cube.hpp"
#include <cstdlib>

cube::cube(float length)
{
    m_length = length;

    m_transform.rotation=0.0f;
    m_transform.position = glm::vec3(0.0f,0.0f,0.0f);
    m_transform.scale = 1.0f;

    glm::vec3 v[8];
    v[0] = glm::vec3(-length/2,-length/2,-length/2);
    v[1] = glm::vec3(length/2,-length/2,-length/2);
    v[2] = glm::vec3(length/2,-length/2,length/2);
    v[3] = glm::vec3(-length/2,-length/2,length/2);

    v[4] = glm::vec3(-length/2,length/2,-length/2);
    v[5] = glm::vec3(length/2,length/2,-length/2);
    v[6] = glm::vec3(length/2,length/2,length/2);
    v[7] = glm::vec3(-length/2,length/2,length/2);
    //Ust Yuzey

    Vertex tempVertices[24];
    tempVertices[0].pos = v[7];
    tempVertices[1].pos = v[3];
    tempVertices[2].pos = v[2];
    tempVertices[3].pos = v[6];
    tempVertices[0].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[1].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[2].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[3].texCoord = glm::vec2(1.0f,1.0f);
    //Sag Yuzey
    tempVertices[4].pos = v[6];
    tempVertices[5].pos = v[2];
    tempVertices[6].pos = v[1];
    tempVertices[7].pos = v[5];
    tempVertices[4].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[5].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[6].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[7].texCoord = glm::vec2(1.0f,1.0f);
//    //Ust Yuzey
    tempVertices[8 ].pos = v[4];
    tempVertices[9 ].pos = v[7];
    tempVertices[10].pos = v[6];
    tempVertices[11].pos = v[5];
    tempVertices[8 ].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[9 ].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[10].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[11].texCoord = glm::vec2(1.0f,1.0f);

    //Sol Yüzey
    tempVertices[12].pos = v[0];
    tempVertices[13].pos = v[3];
    tempVertices[14].pos = v[2];
    tempVertices[15].pos = v[1];
    tempVertices[12].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[13].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[14].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[15].texCoord = glm::vec2(1.0f,1.0f);
    //Sag Yuzey
    tempVertices[16].pos = v[4];
    tempVertices[17].pos = v[0];
    tempVertices[18].pos = v[1];
    tempVertices[19].pos = v[5];
    tempVertices[16].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[17].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[18].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[19].texCoord = glm::vec2(1.0f,1.0f);
//    //Alt Yuzey
    tempVertices[20].pos = v[7];
    tempVertices[21].pos = v[3];
    tempVertices[22].pos = v[0];
    tempVertices[23].pos = v[4];
    tempVertices[20].texCoord = glm::vec2(0.0f,1.0f);
    tempVertices[21].texCoord = glm::vec2(0.0f,0.0f);
    tempVertices[22].texCoord = glm::vec2(1.0f,0.0f);
    tempVertices[23].texCoord = glm::vec2(1.0f,1.0f);


    for(int i=0;i<24;i++)
        m_vertices.push_back(tempVertices[i]);

    for(int i=0;i<6;i++)
    {
        int startIndex = 4*i;
        m_indices.push_back(startIndex);
        m_indices.push_back(startIndex+1);
        m_indices.push_back(startIndex+2);

        m_indices.push_back(startIndex);
        m_indices.push_back(startIndex+2);
        m_indices.push_back(startIndex+3);
    }
}

void cube::rotate()
{
    m_transform.rotation += 1.0;
}

const glm::mat4* cube::getTransformMatrix()
{
    glm::mat4 mtxRotation = glm::rotate(glm::mat3(1), glm::radians(m_transform.rotation));
    glm::mat4 mtxTranslation = glm::translate(glm::mat3(1), glm::vec2(m_transform.position.x, m_transform.position.y));
    glm::mat4 mtxScale =glm::scale(glm::mat3(1),glm::vec2(m_transform.scale,m_transform.scale));
    m_transformMatrix = mtxTranslation * mtxRotation * mtxScale;

    return &m_transformMatrix;
}

const void *cube::getVertices() {
    return &m_vertices[0];
}

const void *cube::getIndices() {
    return &m_indices[0];
}

int cube::getSizeOfVertices() {
    return sizeof(Vertex)*m_vertices.size();
}

int cube::getSizeOfIndices() {
    return sizeof(unsigned int)*getCountOfIndices();
}

int cube::getCountOfIndices() {
    return m_indices.size();
}




