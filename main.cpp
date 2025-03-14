#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 2000;
const unsigned int SCR_HEIGHT = 1200;

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"precision highp float;\n"
"uniform vec2 u_resolution;\n"
"uniform float u_time;\n"
"uniform float u_rotationx;\n"
"uniform float u_rotationy;\n"
"uniform float u_rotationz;\n"
"#define PI 3.1415925359\n"
"#define TWO_PI 6.2831852\n"
"out vec4 FragColor;\n"   // 自定义输出变量
"void main()\n"
"{\n"
"    vec2 uv = gl_FragCoord.xy / u_resolution * 2.0 - 1.0;\n"
"    uv.x *= u_resolution.x / u_resolution.y;\n"
"    vec2 uv0 = uv;\n"
"    vec3 final_color = vec3(0.0);\n"
"    for (float i = 0.0; i < 4.0; i++) {\n"
"        uv = fract(uv * 1.6) - 0.5;\n"
"        float d = length(uv) * exp(-length(uv0));\n"
"        float d0 = length(uv0);\n"
"        vec3 col = vec3(1.0 + sin(d0 * 8.0 + u_time) * 0.5 - i * 0.2,\n"
"                          0.5 + cos(d0 * 5.0 + u_time) * 0.3 - i * 0.2,\n"
"                          1.5 + sin(d0 * 10.0 + u_time)) * 0.8 - i * 0.2;\n"
"        d = sin(d * 8.0 + u_time) / 8.0;\n"
"        d = abs(d);\n"
"        d = pow(0.01 / d, 1.4);\n"
"        final_color += col * d;\n"
"    }\n"
"    FragColor = vec4(final_color, 1.0);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW 初始化失败！" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Render Factory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Center the window
    int workAreaX, workAreaY, workAreaWidth, workAreaHeight;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &workAreaX, &workAreaY, &workAreaWidth, &workAreaHeight);
    int windowPosX = workAreaX + (workAreaWidth - SCR_WIDTH) / 2;
    int windowPosY = workAreaY + (workAreaHeight - SCR_HEIGHT) / 2;
    glfwSetWindowPos(window, windowPosX, windowPosY);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::VERTEX_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders into shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data (rectangular shape, two triangles)
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Use shader program
    glUseProgram(shaderProgram);

    // Get uniform locations
    GLint resLocation = glGetUniformLocation(shaderProgram, "u_resolution");
    GLint timeLocation = glGetUniformLocation(shaderProgram, "u_time");
    GLint rotationXLocation = glGetUniformLocation(shaderProgram, "u_rotationx");
    GLint rotationYLocation = glGetUniformLocation(shaderProgram, "u_rotationy");
    GLint rotationZLocation = glGetUniformLocation(shaderProgram, "u_rotationz");

    // Set initial rotation parameters (set to 0 if not used)
    glUniform1f(rotationXLocation, 0.0f);
    glUniform1f(rotationYLocation, 0.0f);
    glUniform1f(rotationZLocation, 0.0f);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Clear screen with white background for visibility
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Update uniforms
        float timeValue = glfwGetTime();
        glUniform1f(timeLocation, timeValue);
        glUniform2f(resLocation, (float)SCR_WIDTH, (float)SCR_HEIGHT);

        // Render rectangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
