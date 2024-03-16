#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc , char** argv)
{
    if(!glfwInit())
        return-1;

    GLFWwindow* window = glfwCreateWindow(800,600,"First Program",NULL,NULL);

    if(window==NULL)
    {
        std::cout<< "Window could not be created"<<std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}