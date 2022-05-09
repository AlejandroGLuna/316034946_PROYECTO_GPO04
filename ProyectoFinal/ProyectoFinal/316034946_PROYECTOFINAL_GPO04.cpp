// Std. Includes
#include <string>
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera camera( glm::vec3( 60.0f, 30.0f, 40.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Animacion Sencilla Puerta Principal
bool anim_PP = false;
float rot_PP = 0.0f;
short regreso_PP = 0;

// Animacion Sencilla Puerta Cobertizo
bool anim_PC = false;
bool regreso_PC = false;
float rot_PC = 0.0f;

// Animacion Sencilla Puerta Sotano
bool anim_PS = false;
float rot_PS = 0.0f;
short regreso_PS = 0;

// Animacion Sencilla Cajones Escritorio
bool anim_C = false;
bool regreso_C = false;
float tras_caj1 = 0.0f;
float tras_caj2 = 0.0f;
float tras_caj3 = 0.0f;
float tras_caj4 = 0.0f;

// Animacion Compleja Lampara
bool anim_L = false;
bool espiral = false;
bool regreso_L = false;
float posX = 37.5f;
float posY = 0.0f;
float posY2 = 0.0f;
float posZ = 2.0f;
float rotX = 0.0f;
float rotX2 = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;
float theta = -15.7f;

// Animacion Compleja Copa
bool anim_T = false;
bool regreso_T = false;
float puntoX = 0.0f;
float puntoY = 4.8f;
float giroX = 0.0f;
float giroZ = 0.0f;
float desA = 0.0f;
float t = 0.0f;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(37.5, 7.1f, 2.0f),
    glm::vec3(15.0f, 32.0f, 50.0f)
};

glm::vec3 Light1 = glm::vec3(1.0f, 0.7686f, 0.0f);
glm::vec3 Light2 = glm::vec3(1.0f, 1.0f, 1.0f);

//Es importante considerar el sentido de dibujo, debido a la normal de la imagen
float vertices[] = {
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// Cubo para skybox
GLfloat skyboxVertices[] = {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

// Positions all containers
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    /*glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );*/
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // Setup and compile our shaders
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
    Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

    // Load models
    Model alacen((char*)"Models/Mueble_Derecho/Alacen.obj");
    Model cajas((char*)"Models/Cajas/Cajas_Pergaminos.obj");
    Model escritorio((char*)"Models/Escritorio/Escritorio.obj");
    Model escritorio_cajonChico((char*)"Models/Escritorio/Cajon.obj");
    Model escritorio_cajonGrande((char*)"Models/Escritorio/CajonGrande.obj");
    Model escritorio_copa((char*)"Models/Copa/Copa.obj");
    Model escalera((char*)"Models/Escalera/Escalera.obj");
    Model fachada((char*)"Models/Fachada/Fachada.obj");
    Model fachada_puertaPrincipal((char*)"Models/Fachada/Puerta_Principal.obj");
    Model fachada_puertaSotano((char*)"Models/Fachada/Puerta_Sotano.obj");
    Model fachada_ventanas((char*)"Models/Fachada/Ventanas.obj");
    Model lampara((char*)"Models/Lampara/lampara.obj");
    Model lampara_inclinada((char*)"Models/Lampara/lampara_techo_inclinada.obj");
    Model lampara_cristal((char*)"Models/Lampara/cristal.obj");
    Model lampara_cristal_inclinada((char*)"Models/Lampara/cristal_inclinado.obj");
    Model pasillo((char*)"Models/Pasadizo/Corredor.obj");
    Model pasto((char*)"Models/Pasto/Pasto.obj");
    Model repisas((char*)"Models/Mueble_Izquierdo/Repisas.obj");
    Model silla((char*)"Models/Silla/silla.obj");
    Model sotano((char*)"Models/Sotano/Sotano.obj");
    Model sotano_puerta((char*)"Models/Sotano/Puerta_Sotano.obj");
    Model cobweb((char*)"Models/Sotano/Cobweb.obj");

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set texture units
    lightingShader.Use();
    //Alojar la textura difusa en la localidad 0
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
    //Alojar la textura especular en la localidad 1
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

    //SkyBox
    GLuint skyboxVBO, skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Load textures
    vector<const GLchar*> faces;
    faces.push_back("SkyBox/right.png");
    faces.push_back("SkyBox/left.png");
    faces.push_back("SkyBox/top.png");
    faces.push_back("SkyBox/bottom.png");
    faces.push_back("SkyBox/back.png");
    faces.push_back("SkyBox/front.png");

    GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // OpenGL options
        glEnable(GL_DEPTH_TEST);

        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use();
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        //Uso de camara sintetica
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f); //Direccion de la luz
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.15f, 0.15f, 0.15f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);

        glm::vec3 lightColor1, lightColor2, lightColor3, lightColor4;

        // Point light 1
        /*lightColor1.x = abs(sin(glfwGetTime() * Light1.x));
        lightColor1.y = abs(sin(glfwGetTime() * Light1.y));
        lightColor1.z = sin(glfwGetTime() * Light1.z);*/

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), Light1.x, Light1.y, Light1.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), Light1.x, Light1.y, Light1.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.07f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.017f);

        // Point light 2
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), Light2.x, Light2.y, Light2.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), Light2.x, Light2.y, Light2.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.027f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0028f);

        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

        glm::mat4 view = camera.GetViewMatrix();

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the loaded model
        glm::mat4 model(1);

        view = camera.GetViewMatrix();

        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

        //Escritorio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(26.0f, -6.9f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        escritorio.Draw(lightingShader);

        //Copa
        model = glm::translate(model, glm::vec3(puntoX, puntoY, -2.0f));
        model = glm::rotate(model, glm::radians(-giroZ), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(-giroX), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        escritorio_copa.Draw(lightingShader);

        // Primer Cajon del Escritorio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(27.48f+tras_caj1, -3.195f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        escritorio_cajonChico.Draw(lightingShader);

        // Segundo Cajon del Escritorio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(27.48f + tras_caj2, -4.288f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        escritorio_cajonGrande.Draw(lightingShader);

        // Tercer Cajon del Escritorio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(27.48f + tras_caj3, -5.399f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        escritorio_cajonGrande.Draw(lightingShader);
        
        // Cuarto Cajon del Escritorio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(27.48f + tras_caj4, -6.518f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        escritorio_cajonGrande.Draw(lightingShader);

        //Silla
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(22.5f, -6.6f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        silla.Draw(lightingShader);

        //Repisas
        model = glm::translate(model, glm::vec3(5.5f, 0.25f, -16.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        repisas.Draw(lightingShader);

        //Primer Alacen
        model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        alacen.Draw(lightingShader);

        //Segundo Alacen
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -9.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        alacen.Draw(lightingShader);

        //Escalerita
        model = glm::translate(model, glm::vec3(7.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        escalera.Draw(lightingShader);

        //Cajas con pergaminos
        model = glm::translate(model, glm::vec3(12.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        cajas.Draw(lightingShader);

        //Lampara 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(posX, 5.0f, posZ));
        if (espiral) 
        {
            model = glm::translate(model, glm::vec3(0.0f, posY2, 0.0f));
            model = glm::rotate(model, glm::radians(-rotY), glm::vec3(0.0, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-rotX2), glm::vec3(1.0, 0.0f, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
            lampara_inclinada.Draw(lightingShader);

            glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //Cristal de la lampara
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
            glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.6);
            lampara_cristal_inclinada.Draw(lightingShader);

            glDisable(GL_BLEND);  //Desactiva el canal alfa 
        }
        else
        {
            model = glm::translate(model, glm::vec3(0.0f, posY, 0.0f));
            model = glm::rotate(model, glm::radians(-rotX), glm::vec3(1.0, 0.0f, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
            lampara.Draw(lightingShader);


            glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //Cristal de la lampara
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
            glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.6);
            lampara_cristal.Draw(lightingShader);

            glDisable(GL_BLEND);  //Desactiva el canal alfa 
        }

        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

        //Fachada
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.0f, 12.8f, 50.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        fachada.Draw(lightingShader);

        glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Ventanas de la Fachada
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 0.0, 1.5);
        fachada_ventanas.Draw(lightingShader);

        glDisable(GL_BLEND);  //Desactiva el canal alfa 

        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

        // Puerta Principal de la Fachada
        model = glm::translate(model, glm::vec3(16.632f, 0.79f, 3.876f));
        model = glm::rotate(model, glm::radians(rot_PP), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        fachada_puertaPrincipal.Draw(lightingShader);

        // Puerta Cobertizo de la Fachada
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(29.082f, 12.8f, 37.668f));
        model = glm::rotate(model, glm::radians(rot_PC), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        fachada_puertaSotano.Draw(lightingShader);

        //Pasto
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.0f, 12.3f, 50.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        pasto.Draw(lightingShader);

        //Pasillo
        model = glm::translate(model, glm::vec3(10.0f, -18.75f, -16.7f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        pasillo.Draw(lightingShader);

        //Sotano
        model = glm::translate(model, glm::vec3(0.0f, -0.15f, -38.6f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        sotano.Draw(lightingShader);


        glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Telarañas
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 4.0);
        cobweb.Draw(lightingShader);

        glDisable(GL_BLEND);  //Desactiva el canal alfa 


        // Puerta del Sotano
        model = glm::translate(model, glm::vec3(3.057f, 0.0f, 19.0111f));
        model = glm::rotate(model, glm::radians(rot_PS), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        sotano_puerta.Draw(lightingShader);

        

        glBindVertexArray(0);

        // Also draw the lamp object, again binding the appropriate shader
        lampShader.Use();

        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");

        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4(1);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(1.0f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Draw the light object (using light's vertex attributes)
        for (GLuint i = 0; i < 2; i++)
        {
            model = glm::mat4(1);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(VAO);
            if(!anim_L)
                glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Draw skybox as last
        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
        SkyBoxshader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // Set depth function back to default

        // Swap the buffers
        glfwSwapBuffers( window );
    }

    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

    if (anim_PP)
    {
        if (regreso_PP == 0)
        {
            if (rot_PP < 90.0f)
                rot_PP += 1.0f;
            else
                regreso_PP = 1;
        }
        else if (regreso_PP == 1)
        {
            if (rot_PP > -90.0f)
                rot_PP -= 1.0f;
            else
                regreso_PP = 2;
        }
        else
        {
            if (rot_PP < 0.0f)
                rot_PP += 1.0f;
            else
            {
                anim_PP = false;
                regreso_PP = 0;
            }
        }
    }

    if (anim_PC)
    {
        if (!regreso_PC)
        {
            if (rot_PC > -110.0f)
                rot_PC -= 1.0f;
            else
                regreso_PC = true;
        }
        else
        {
            if (rot_PC < 0.0f)
                rot_PC += 1.0f;
            else
            {
                regreso_PC = false;
                anim_PC = false;
            }
        }
    }

    if (anim_PS)
    {
        if (regreso_PS == 0)
        {
            if (rot_PS < 90.0f)
                rot_PS += 1.0f;
            else
                regreso_PS = 1;
        }
        else if (regreso_PS == 1)
        {
            if (rot_PS > -90.0f)
                rot_PS -= 1.0f;
            else
                regreso_PS = 2;
        }
        else
        {
            if (rot_PS < 0.0f)
                rot_PS += 1.0f;
            else
            {
                anim_PS = false;
                regreso_PS = 0;
            }
        }
    }

    if (anim_C)
    {
        if (!regreso_C) {
            if (tras_caj4 > -4.0f)
                tras_caj4 -= 0.04f;
            else if (tras_caj3 > -4.0f)
                tras_caj3 -= 0.04f;
            else if (tras_caj2 > -4.0f)
                tras_caj2 -= 0.04f;
            else if (tras_caj1 > -4.0f)
                tras_caj1 -= 0.04f;
            else
                regreso_C = true;
        }
        else 
        {
            if (tras_caj1 < 0.0f)
                tras_caj1 += 0.04f;
            else if (tras_caj2 < 0.0f)
                tras_caj2 += 0.04f;
            else if (tras_caj3 < 0.0f)
                tras_caj3 += 0.04f;
            else if (tras_caj4 < 0.0f)
                tras_caj4 += 0.04f;
            else {
                regreso_C = false;
                anim_C = false;
            }
                
        }
    }

    if (anim_L)
    {
        if (espiral && !regreso_L)
        {
            posZ = (0.1 * theta * cos(theta)) + 0.4f;
            posX = (0.1 * theta * sin(theta)) + 37.5f;
            theta += 0.02f;
            rotY += 1.1428f;

            if (theta >= 0.0f)
            {
                regreso_L = true;
                posZ = 0.0f;
            }

            pointLightPositions[0].z = posZ*4;
            pointLightPositions[0].x = posX;
        }
        else
        {
            if (regreso_L)
            {
                rotX2 -= 0.5f;
                posZ += 0.075f;
                posY2 += 0.01438f;
                if (rotX2 <= -40.0f)
                {
                    // Volviendo a inicializar las variables
                    anim_L = false;
                    espiral = false;
                    regreso_L = false;
                    posX = 37.5f;
                    posY = 0.0f;
                    posY2 = 0.0f;
                    posZ = 2.0f;
                    rotX = 0.0f;
                    rotX2 = 0.0f;
                    rotY = 0.0f;
                    theta += -15.7;
                    pointLightPositions[0].x = 37.5f;
                    pointLightPositions[0].y = 7.1f;
                    pointLightPositions[0].z = 2.0f;
                }
                else
                    pointLightPositions[0].z = posZ - 4.0f;
            }
            else
            {
                rotX += 0.5f;
                posY += 0.0125f;
                posZ += 0.05f;
                if (posZ >= 6.0f)
                {
                    espiral = true;
                    posZ = 2.0f;
                }
                pointLightPositions[0].z = posZ - 1.0f;
            }
        }
    }

    if (anim_T)
    {
        if (regreso_T)
        {
            puntoY += 0.1f;
            puntoX -= 0.2309f;
            giroZ += 1.875f;
            if (puntoY >= 4.8f)
            {
                anim_T = false;
                regreso_T = false;
                puntoX = 0.0f;
                puntoY = 4.8f;
                giroX = 0.0f;
                giroZ = 0.0f;
                desA = 0.0f;
                t = 0.0f;
            }
        }
        else
        {
            if (puntoX <= 2.0f)
                puntoX += 0.1f;
            else
            {
                if (puntoY >= 0.4f)
                {
                    puntoX = 2.0f + 3.0f * t;
                    puntoY = 4.8f - (0.96f * t * t) / 2;
                    t += 0.05f;
                    giroZ += 1.423f;
                }
                else
                {
                    if (giroX <= 180.0f)
                    {
                        if (desA <= 2.0f)
                            desA += 0.02f;

                        giroX += 2.5f - desA;
                    }
                    else
                        regreso_T = true;
                }
            }
        }
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_C])
        anim_PP = !anim_PP;

    if (keys[GLFW_KEY_V])
        anim_PC = !anim_PC;

    if (keys[GLFW_KEY_B])
        anim_PS = !anim_PS;

    if (keys[GLFW_KEY_N])
        anim_C = !anim_C;

    if (keys[GLFW_KEY_M])
        anim_L = !anim_L;

    if (keys[GLFW_KEY_L])
        anim_T = !anim_T;
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

