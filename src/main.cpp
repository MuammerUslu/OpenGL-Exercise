#include <iostream>
#include <glad/glad.h> //glfw'dan önce include edilmesi gerekiyor
#include <GLFW/glfw3.h>
#include "shaderprogram.hpp"

//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.6f, -0.6f, 0.0f,
     0.6f, -0.6f, 0.0f,
     0.0f,  0.0f, 0.0f,
     -0.6f, 0.6f, 0.0f,
    0.6f, 0.6f, 0.0f,
    0.0f,  0.0f, 0.0f
};

//vertex array object
unsigned int VAO;
//vertex buffer object
unsigned int VBO;

int main(int argc , char** argv)
{
    if(!glfwInit())
        return-1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(800,600,"First Program",NULL,NULL);

    if(window==NULL)
    {
        std::cout<< "Window could not be created"<<std::endl;

        glfwTerminate();

        return -1;
    }

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

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO); // aktif olacak vertex array
    glBindBuffer(GL_ARRAY_BUFFER,VBO); //aktif olacak buffer'ı belirliyoruz. id ile kullanılmıyor. kullanmadan önce buffer aktif ediliyor.

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //buffer'ımızı grafik karttakiyle bağladık. (aktif olan VBO)
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0); //0 nolu slota,3 elemanlı,türü GL_FlOAT,normalized etme,bir vertex'in boyutu,attribute'un vertex byte dizisi içerisinde hangi adresten başladığı

    glEnableVertexAttribArray(0); //0 nolu slotu aktive et

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.25f,0.5f,1.0f);//ekranı temizleyip rengini veriyoruz
        glClear(GL_COLOR_BUFFER_BIT);

        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();

        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
        glDrawArrays(GL_TRIANGLES, 0, 6);


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}