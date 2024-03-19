#include <iostream>
#include <glad/glad.h> //glfw'dan önce include edilmesi gerekiyor
#include <GLFW/glfw3.h>

//vertex shader kaynak kodu
const char* vssource =
"#version 330 core\n                                    \
 layout (location = 0) in vec3 inPosition;              \
 void main(){                                           \
    gl_Position = vec4(inPosition, 1.0);                \
}";
//fragment shader kaynak kodu
const char* fssource =
"#version 330 core\n                                    \
 out vec4 fragColor;                                    \
 void main(){                                           \
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);           \
 }";

//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.6f, -0.6f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

unsigned int programId;
unsigned int fragmentShader;
unsigned int vertexShader;
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

    //Vertex Shader
    vertexShader =glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vssource,NULL); //vertexShaderId'ye,1 adet char* (char* array de olabilirdi) ve bu char* vssource
    glCompileShader(vertexShader); // belirttiğimiz shader'ı derle. Bu derleme grafik kartında yapılır.

    //Fragment Shader
    fragmentShader =glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fssource,NULL); 
    glCompileShader(fragmentShader);

    //Create Program
    programId = glCreateProgram();
    glAttachShader(programId,vertexShader);  //Attach Shaders --shader compile edilmiş olmalı
    glAttachShader(programId,fragmentShader);
    glLinkProgram(programId);

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO); // aktif olacak vertex array
    glBindBuffer(GL_ARRAY_BUFFER,VBO); //aktif olacak buffer'ı belirliyoruz. id ile kullanılmıyor. kullanmadan önce buffer aktif ediliyor.

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //buffer'ımızı grafik karttakiyle bağladık. (aktif olan VBO)
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0); //0 nolu slota,3 elemanlı,türü GL_FlOAT,normalized etme,bir vertex'in boyutu,attribute'un vertex byte dizisi içerisinde hangi adresten başladığı

    glEnableVertexAttribArray(0); //0 nolu slotu aktive et

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.5f,0.5f,1.0f);//ekranı temizleyip rengini veriyoruz
        glClear(GL_COLOR_BUFFER_BIT);

        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        glUseProgram(programId);
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}