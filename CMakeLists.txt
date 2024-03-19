cmake_minimum_required(VERSION 3.8)

project(OpenGLExercise)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set( PROJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/math.cpp 
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/glad.c) #glad kütüphanesi de projemizle beraber derlenecek.

set(PROJECT_HEADERS
        $(PROJECT_INCLUDE_DIR)/math.hpp)

include_directories(${PROJECT_INCLUDE_DIR})

#Required yazdığımızda bulma işlemi başarısız olursa hata alırız işlem sonlanır. min v3.2 required
#glfw3 dosyasını arar
#cmake arama işlemlerini usr/local/ib/cmake içerisini tarar
#glfw zaten derlenmiş bir proje. derleme esansında değil linking esnasında bağlanacak
find_package(glfw3 3.2 REQUIRED) 

find_package(glm REQUIRED) 
find_package (OpenGL REQUIRED)
find_library(COCOA_LIBRARY Cocoa REQUIRED)
find_library(IOKIT_LIBRARY IOKit REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

#OpenGlExercise projesini glfw kütüphanesiyle bağla
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        glfw
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
)