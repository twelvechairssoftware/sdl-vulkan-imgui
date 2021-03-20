#include "main.h"
#define numVAOs 1

GLuint renderingProgram;
GLuint vertexArrayObjects[numVAOs];

static std::string glsl_version;

void selectGLVersion(){
#ifdef __APPLE__
    glsl_version = "#version 330 \n";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    glsl_version = "#version 420 \n";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
}

GLuint createShaderProgram(){
    std::string vertexShaderString =
            "void main(void) \n"
            "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";
    vertexShaderString.insert(0, glsl_version);
    const char* vertexShaderSource = vertexShaderString.c_str();

    std::string fragmentShaderString =
            "out vec4 color; \n"
            "void main(void) \n"
            "{ if(gl_FragCoord.x < 295) color = vec4(1.0, 0.0, 0.0, 1.0); else color = vec4(0.0, 0.0, 1.0, 1.0);}";
    fragmentShaderString.insert(0, glsl_version);
    const char* fragmentShaderSource = fragmentShaderString.c_str();

    GLuint shaderProgram = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);\
    glCompileShader(fragmentShader);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    return shaderProgram;
}

void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vertexArrayObjects);
    glBindVertexArray(vertexArrayObjects[0]);
}

void display(GLFWwindow* window, double currentTime){
//    glClearColor(1.0, 0.0, 0.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);
    glPointSize(60);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main(int, char**){
    if (!glfwInit()) {
        spdlog::error("Error initializing GLFW!");
        return 1;
    }

    selectGLVersion();

    GLFWwindow* window = glfwCreateWindow(300, 300, "GLFW+ImGui+OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        spdlog::error("Failed to create GLFW window!\n");
        return 1;
    }

    glfwMakeContextCurrent(window);

    // Initialize OpenGL loader
    if (glewInit() != GLEW_OK){
        spdlog::error("Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Enable vsync
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)){
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}