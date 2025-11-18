#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int WIDTH = 800;
int HEIGHT = 800;

//Brauch das hier damit C++ compiler weiss das die functionen exestieren.
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f, 0.5f, 0.0f
};
const int indices[] = {
    0, 1, 3,
    1, 2, 3
};

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
    // GLFW Init
    glfwInit();
    // OpenGl Targeting
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window Create + Error
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "HELLO WORLD", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }


    // Macht einfach das jede nachfolgenen contexte auf dieses window rendert 
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to inizialize GLAD" << std::endl;
        return -1;
    }

    // Sagt OpenGL wo man rendern darf
    glViewport(0, 0, WIDTH, HEIGHT);

    // Setzt die function was passieren soll wenn das window das resiced wird.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Macht neunen Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Binded den VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Gibt die Daten rüber die wir and die GPU schicken wollen
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Einfach den cetexShader "id" machen
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
               
    // Shader zur "id" linken und Compilen
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Error
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error mit Vertex Shader: " << infoLog << std::endl;
    }

    // Gleiche wie bei vertex aber jetzt auch wie bei fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error mit Fragment Shader: " << infoLog << std::endl;
    }

    // Erstellt shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attached die Shader zum Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // Error handling wie beim Fragment/Vertexshader
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error mit dem Linken von den Shader: " << infoLog << std::endl;
    }

    // Macht es jetzt so das OpenGl  dieses Shader Program benutzt 
    glUseProgram(shaderProgram);

    // Deleted die Shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Beschrieben wo genau unser vertex data in der certex shader hin kommt? Aber besser noch mal nach lesen
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Macht ein neues Vertex Array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Bindet den VAO
    glBindVertexArray(VAO);
  
    // Kopiert die vertices array in einen buffer damit OpenGL es bentutzen kann
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Erstellen von den Vertex attributes ponters
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Erstellen vom EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {

        // Processes the input 
        processInput(window);

         

        // Cleared hintergrund
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Zeichnen vom 3Eck
        glUseProgram(shaderProgram);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swaped front and back buffer
        glfwSwapBuffers(window);

        // Nimmt die ganzen events
        glfwPollEvents();
    }
    
    //Terminates GLFW
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{

    // Schaut wenn esc gedrück ist und wenn ja schliesst es das window 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    // Veränder den Viewport on rezice
    glViewport(0, 0, width, height);
}