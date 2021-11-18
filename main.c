#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

float vertices[] =
{
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

int indices[] = {
    1, 2, 3
};



void compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1000];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1000, NULL, infoLog);
			printf("SHADER_COMPILATION_ERROR for: %s\n", type);
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1000, NULL, infoLog);
			printf("SHADER_LINKING_ERROR for: %s\n", type);
		}
	}
}

int main(void)
{
    GLFWwindow* window;



    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL();

    GLuint SP; //Shader Program

    {
        const char* vertShaderSrc;
        const char* fragShaderSrc;
        /* 
    
        TODO: Fix file reading
    
        */

        /*char vertShaderBuffer[1000];
        FILE* vertShaderFile = fopen("shader.vert", "r");
        fread(vertShaderBuffer, 1, 1000, vertShaderFile);
        fclose(vertShaderFile);*/
        vertShaderSrc = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main() {\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";

        /*char fragShaderBuffer[1000];
        FILE* fragShaderFile = fopen("shader.frag", "r");
        fread(fragShaderBuffer, 1, 1000, fragShaderFile);
        fclose(fragShaderFile);*/
        fragShaderSrc = "#version 330 core\nout vec4 FragColor;\nvoid main() {\nFragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n}";


        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
        glCompileShader(vertShader);
        compileErrors(vertShader, "VERTEX");

        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
        glCompileShader(fragShader);
        compileErrors(fragShader, "FRAGMENT");


        SP = glCreateProgram();
        glAttachShader(SP, vertShader);
        glAttachShader(SP, fragShader);
        glLinkProgram(SP);
        compileErrors(SP, "PROGRAM");

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
    }

    GLuint VAO;
    GLuint VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    


    glViewport(0, 0, 800, 800);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(SP);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteProgram(SP);

    glfwTerminate();
    return 0;
}