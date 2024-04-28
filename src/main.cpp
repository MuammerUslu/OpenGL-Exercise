#include <iostream>
#include <glad/glad.h> //glfw'dan önce include edilmesi gerekiyor
#include <GLFW/glfw3.h>
#include "shaderprogram.hpp"

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

static void GLClearError() {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

static bool GLLogCall(const char* function, const char* file, int line) {
    GLenum error;
    bool hasError = false;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        hasError = true;
    }
    return !hasError;
}

//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.5f, -0.5f, 0.0f,1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, 0.0f,0.0f, 0.0f, 1.0f,
     -0.5f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f,
};

unsigned int indices[] = {
        0,1,2,
        2,3,0
};

//vertex array object
unsigned int VAO;
//vertex buffer object
unsigned int VBO;
//index buffer object
unsigned int IBO;

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
    glGenBuffers(1,&IBO);


    glBindVertexArray(VAO); // aktif olacak vertex array
    glBindBuffer(GL_ARRAY_BUFFER,VBO); //aktif olacak buffer'ı belirliyoruz. id ile kullanılmıyor. kullanmadan önce buffer aktif ediliyor.
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //buffer'ımızı grafik karttakiyle bağladık. (aktif olan VBO)

    glBindVertexArray(IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0); //0 nolu slota,3 elemanlı,türü GL_FlOAT,normalized etme,bir vertex'in boyutu,attribute'un vertex byte dizisi içerisinde hangi adresten başladığı
    glEnableVertexAttribArray(0); //0 nolu slotu aktive et

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float))); //0 nolu slota,3 elemanlı,türü GL_FlOAT,normalized etme,bir vertex'in boyutu,attribute'un vertex byte dizisi içerisinde hangi adresten başladığı
    glEnableVertexAttribArray(1);

    program.addUniform("windowHeight");

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.25f,0.5f,1.0f);//ekranı temizleyip rengini veriyoruz
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;
        // Pencere boyutunu al
        glfwGetFramebufferSize(window, &width, &height);

        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();

        //program.setFloat("windowHeight", 800.0f);
        program.setFloat("windowHeight", (float)height*0.5f);

        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
        //glDrawArrays(GL_TRIANGLES, 0, 6);

       glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr); // GL_INT yerine GL_UNSIGNED_INT olmalıydı. 1280 error kodu


        //GLCall(glDrawElements(GL_TRIANGLES,6,GL_INT,nullptr)); // GL_INT yerine GL_UNSIGNED_INT olmalıydı. 1280 error kodu


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}