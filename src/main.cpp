#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <glad/glad.h> //glfw'dan önce include edilmesi gerekiyor
#include <GLFW/glfw3.h>
#include "shaderprogram.hpp"
#include <glm/glm.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>
#include "Square.hpp"

float length=0.08f;

Square square(0.0f,0.0f,length);

float angle;
glm::vec2 position;
float scale;

//vertex array object
unsigned int VAO;
//vertex buffer object
unsigned int VBO;
//index buffer
unsigned int EBO;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();

    if(action==GLFW_PRESS)
    {
        if(key==GLFW_KEY_LEFT)
        {
            position.x-=0.01;
        }
        if(key==GLFW_KEY_RIGHT)
        {
            position.x+=0.01;
        }
        if(key==GLFW_KEY_UP)
        {
            position.y+=0.01;
        }
        if(key==GLFW_KEY_DOWN)
        {
            position.y-=0.01;
        }


        if(key==GLFW_KEY_Q)
        {
            scale-=0.1;
        }

        if(key==GLFW_KEY_W)
        {
            scale+=0.1;
        }
    }

}

int main(int argc , char** argv)
{
    if(!glfwInit())
        return-1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(800,800,"First Program",NULL,NULL);

    if(window==NULL)
    {
        std::cout<< "Window could not be created"<<std::endl;

        glfwTerminate();

        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad." << std::endl;
        return -1;
    }

    glm::mat3 mtxTransform(1);

    angle=0.0f;
    position = glm::vec2(0.0f,0.0f);
    scale = 1.0f;

    ShaderProgram program;

    program.attachShader("../shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("../shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");
    program.addUniform("uMtxTransform");

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO); // aktif olacak vertex array
    glBindBuffer(GL_ARRAY_BUFFER,VBO); //aktif olacak buffer'ı belirliyoruz. id ile kullanılmıyor. kullanmadan önce buffer aktif ediliyor.

    glBufferData(GL_ARRAY_BUFFER,square.getSizeOfVertices(),square.getVertices(),GL_STATIC_DRAW); //buffer'ımızı grafik karttakiyle bağladık. (aktif olan VBO)
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0); //0 nolu slota,3 elemanlı,türü GL_FlOAT,normalized etme,bir vertex'in boyutu,attribute'un vertex byte dizisi içerisinde hangi adresten başladığı

    glEnableVertexAttribArray(0); //0 nolu slotu aktive et

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, square.getSizeOfIndices(), square.getIndices(), GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.25f,0.5f,1.0f);//ekranı temizleyip rengini veriyoruz
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat3 mtxRotation = glm::rotate(glm::mat3(1), glm::radians(angle));
        glm::mat3 mtxTranslation = glm::translate(glm::mat3(1),position);
        glm::mat3 mtxScale =glm::scale(glm::mat3(1),glm::vec2(scale,scale));
        mtxTransform = mtxTranslation * mtxRotation * mtxScale;

        angle+=1.0f;

        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();

        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        //glBindVertexArray(VAO);

        program.setVec3("uMove", square.getPosition());
        program.setVec4("uColor", square.getColor());
        program.setMat3("uMtxTransform",&mtxTransform);

        //glDrawArrays(GL_TRIANGLES, 0, 6);

        square.move();

        glDrawElements(GL_TRIANGLES, square.getCountOfIndices(), GL_UNSIGNED_INT, 0);

        std::this_thread::sleep_for (std::chrono::milliseconds(50));
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}