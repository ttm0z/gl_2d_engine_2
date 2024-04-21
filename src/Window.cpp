#include "Window.h"
#include <iostream>
#include <iomanip> // For std::setw
#include <algorithm> // For std::find

//constructor, initialze
Window::Window(int width, int height, const char* title) : width(width), height(height), title(title)
{
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
        //delete window ~Window();
	}
	glfwMakeContextCurrent(window);

    // Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
        //delete window
	}
    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

}

//descructor - cleanup
Window::~Window(){

}