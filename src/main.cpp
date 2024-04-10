#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <glad/glad.h> //glfw'dan önce include edilmesi gerekiyor
#include <GLFW/glfw3.h>
#include "shaderprogram.hpp"
#include <glm/glm.hpp>
#include "Square.hpp"

float length=0.08f;

Square square(0.0f,0.0f,length);

//vertex array object
unsigned int VAO;
//vertex buffer object
unsigned int VBO;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();

    if(action==GLFW_PRESS)
    {
        if(key==GLFW_KEY_LEFT)
        {
            square.setDirection(Square::DIR_LEFT);
        }
        if(key==GLFW_KEY_RIGHT)
        {
            square.setDirection(Square::DIR_RIGHT);
        }
        if(key==GLFW_KEY_UP)
        {
            square.setDirection(Square::DIR_UP);
        }
        if(key==GLFW_KEY_DOWN)
        {
            square.setDirection(Square::DIR_DOWN);
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

    ShaderProgram program;

    program.attachShader("../shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("../shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO); // aktif olacak vertex array
    glBindBuffer(GL_ARRAY_BUFFER,VBO); //aktif olacak buffer'ı belirliyoruz. id ile kullanılmıyor. kullanmadan önce buffer aktif ediliyor.

    glBufferData(GL_ARRAY_BUFFER,square.getSizeOfVertices(),square.getVertices(),GL_STATIC_DRAW); //buffer'ımızı grafik karttakiyle bağladık. (aktif olan VBO)
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0); //0 nolu slota,3 elemanlı,türü GL_FlOAT,normalized etme,bir vertex'in boyutu,attribute'un vertex byte dizisi içerisinde hangi adresten başladığı

    glEnableVertexAttribArray(0); //0 nolu slotu aktive et

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.25f,0.5f,1.0f);//ekranı temizleyip rengini veriyoruz
        glClear(GL_COLOR_BUFFER_BIT);

        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();

        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        //glBindVertexArray(VAO);

        program.setVec3("uMove", square.getPosition());
        program.setVec4("uColor", square.getColor());
        glDrawArrays(GL_TRIANGLES, 0, 6);

        square.move();

        std::this_thread::sleep_for (std::chrono::milliseconds(50));
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}