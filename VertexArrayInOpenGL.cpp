#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

//by Alexander

////The lasson of vertex Array Buffer is needed when drawing multiple geomitries.
//// It releases the vertex attribute buffer/pointer, which are the specifications of the vertex buffer
////below the vbinding of vertex buffer, and then rebind them in the while-loop, making it possible for 
////binding multiple geomitries in every rendering. We also call specification as "layout".

//// The way we draw things was: (1)Bind shader --->(2)Bind vertex buffer --->(3)Set up vertex layout --->(4)Bind index buffer
//// The way of drawing is now: (1)Bind shader --->(2)Bind vertex array --->(3)Bind index buffer 

////https://www.khronos.org/opengl/wiki/ is a good OpenGL related web
////Try to see its effectiveness on your device to choose whether using Compat(use unique globle vao in each geomitry) 
////or Core(seperate vao on each of the geomitry) profile

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Lesson of error handling ability in OpenGL.

//Optimization
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

/////////////////////////////////////////////////////
static void GLClearError() {
	while (glGetError() != GL_NO_ERROR) {}; // Just clear the error history while there is no error.

}

//// Before seting an Assert() function and witout optimization.
//static void GLCheckError(){
//	while (GLenum error = glGetError()) // Log error info  while there is the errors.
//	{
//		cout << "[OpenGL Error] (" << error << ")" << endl;
//	}
//}

//// 1st and 2nd stage of Optimization through the C++ Assert() method
//static bool GLLogCall(){
//	while (GLenum error = glGetError()) // Log error info  while there is the errors.
//	{
//		cout << "[OpenGL Error] (" << error << ")" << endl;
//		return false;
//	}
//	return true;
//}

//// 3rd stage of Optimization
static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) // Log error info  while there is the errors.
	{
		cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << endl;
		return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ShaderProgramSource
{
	string VertexSource;
	string FragmentSource;
};

static ShaderProgramSource ParseShader(const string filePath) {

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ifstream stream(filePath);
	ShaderType type = ShaderType::NONE;
	string line;
	stringstream ss[2]; // One for vertex shader while the other is for the fragment shader
	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				//set vertex mode
				type = ShaderType::VERTEX;
			}
			else {
				//set fragment mode
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n'; // Add line to the stream string
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static int CompilerShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int programe = glCreateProgram();  // "unsigned int" equals to "GLuint"
	unsigned int vShder = CompilerShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fShder = CompilerShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(programe, vShder);
	glAttachShader(programe, fShder);
	glLinkProgram(programe);
	GLCall(glValidateProgram(programe));

	glDeleteShader(vShder);
	glDeleteShader(fShder);

	return programe;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);//Can be rendered because it is compact
	//Because the vao is defaultly boud with buffer, with the default index 0.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// Must bind object below because it's Core and no defaultly bound

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error(Don't worry for this is just a test!)" << std::endl;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(480, 480, "Shaders in OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // Set the interval time among each rendering time

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error Again!!!" << std::endl;  // Will not an Error printing 
	}
	std::cout << "Your current GL version is : " << glGetString(GL_VERSION) << std::endl;

	float position[] = {
		-0.5f,-0.5f,//0
		0.5f, -0.5f,//1
		0.5f,  0.5f,//2
	   -0.5f,  0.5f//3
	};

	unsigned int indecies[] = {
		0,1,2,
		0,2,3
	};

	////VAO must be bound in the "Core" profile
	unsigned int vao; // vao ----> vertex array object: which will hold vertex array object ID
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	unsigned int buffer;
	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), position, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0)); //The index must be the same with the code below
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
	//The one-line code above is linking vertex array object with vertex buffer!!!
	//The first number "0", which is the index,is making sure the link between vertex buffer and vertex array object
	//If a different vertex buffer should also be rendered, the index may be 1 or furthur.


	unsigned int ibo; // ibo ---> index buffer object
	GLCall(glGenBuffers(1, &ibo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indecies, GL_STATIC_DRAW));

	ShaderProgramSource source = ParseShader("Basics.shader");

	cout << "Vertex Shader Code Below" << endl;
	cout << source.VertexSource << endl;
	cout << "Fragment Shader Code Below" << endl;
	cout << source.FragmentSource << endl;

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1); // Assert the location in case it was ruined or fragiled！*********Very Important*********

	//glUniform4f(location, 0.9f, 0.3f, 0.5f, 1.0); //Used below!

	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	//// Lesson of vertex array buffer ////
	// Unbind all of the buffers
	GLCall(glBindVertexArray(0)); // Bind vertex array object below in the while-loop
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));


	float red = 0.0f;
	//float green = 0.0f;
	//float blue = 0.0f;
	float increment = 0.05f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		GLCall(glUseProgram(shader)); // Reloading the shader to the GPU ----> (1) Bind shader
		GLCall(glUniform4f(location, red, 0.9f, 0.0f, 1.0f)); // Only the Grayscale will change when RGB is equally distributed
															  // ----> (2) Set up shaders' uniform
		////The first way of doing with compat profile mode
	//	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); // Rebinding the vertex array buffer ----> (1) Bind vertex buffer
	//	glEnableVertexAttribArray(0); // Again
	//	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0)); // Again
		// [layout ----> vertex specification]						// ----> (2) Set up the layout of vertex buffer
		// The two/(or 3) ways above in the while-loop is called 'Binding the vertex array object'!!!
		// Because 'while-loop' contains all the states that we need.

		////The second way of doing by vao in core profile:
		GLCall(glBindVertexArray(vao)); //Rebinding vao

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));// Rebinding the index buffer

		/*Draw here*/
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (red > 1.0f)
		{
			increment = -0.05f; // Make the increment go back to initial state
		}
		else if (red < 0.0f)
		{
			increment = 0.05f; // Make the increment go back to initial state
		}
		red += increment; // Add the increment in each loop
		//green += increment + 0.25f;
		 //Only the grayscale will change when RGB is equally distributed, so the increment shouldn't be the same.
		 //Only the lightness will change when the increment is the same, so the increment should change in random type. 
		//blue += increment - 0.35f;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}