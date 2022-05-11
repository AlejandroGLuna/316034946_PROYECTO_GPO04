// Std. Includes
#include <string>
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Otras bibliotecas
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

//Cargar modelos
#include "SOIL2/SOIL2.h"

// Propiedades
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Prototipos de funciones
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camara
Camera camera( glm::vec3( 60.0f, 30.0f, 40.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Tiempo entre el frame actual y el ultimo
GLfloat lastFrame = 0.0f;  	// Tiempo del ultimo frame 

// Animacion Sencilla Puerta Principal
bool anim_PP = false;
float rot_PP = 0.0f;
short regreso_PP = 0;

// Animacion Sencilla Puerta Pasillo
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

// Atributos de la luz
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

// Posiciones de las point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(37.5, 7.1f, 2.0f),
    glm::vec3(15.0f, 32.0f, 50.0f)
};

// Colores de iluminacion de las point lights
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

int main( )
{
    // Inicializar GLFW
    glfwInit( );
    
    //Se crea una ventana con las medidas especificadas
    //Argumentos: Anchura, altura, nombre encabezado, direcciones de memorias a las que apunta (2)
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr );
    
    //Verificaci�n de errores de creacion  ventana
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    //Empieza a dibujar la ventana en el contexto actual
    glfwMakeContextCurrent( window );
    
    // Define las dimensiones de la ventana
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Se de finen las funciones de callback apropiadas
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // Se deshabilita el cursor
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Se pone esta opcion en veradero para que GLEW use una aproximacion moderna para obtener punteros de funciones
    // y exteneiones
    glewExperimental = GL_TRUE;

    // Inicializar GLEW para los punteros de funciones en OpenGL. Asimismo, se comprueba que se pueda inicializar
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Definir las dimensiones del viewport
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // Configurar y compilar todos los shaders que estaremos utilizando
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
    Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

    // Cargar los modelos
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

    // Variables para poder trabajar con los apuntadores
    GLuint VBO, VAO;
    // Primero se genera el VAO con glGenVertexArrays, asignangole una localidad de memoria
    glGenVertexArrays(1, &VAO);
    // Posteriormente se genera el buffer, que trabajara en conjunto con el VAO.
    glGenBuffers(1, &VBO);
    // Enlazar el VAO
    glBindVertexArray(VAO);
    // Se especifica con el buffer que se estara trabajando
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Se especifica el tamaño(2) e informacion(3), asi como el modo de dibujo (4), que en este caso es estatico solamente
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Apunta a la localidad (0), tomando 3 elementos (1), de tipo flotante (2) con un modo de dibujo estatico (3)
    // el numero de elementos por el tamaño de cada uno (4) y a partir de donde se comienza (5)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    // Se habilita la localidad 0 de memoria
    glEnableVertexAttribArray(0);
    // Se ajustan los atributos de las normales
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // Se habilita la localidad 1 de memoria
    glEnableVertexAttribArray(1);

    // Habilitar el lightning shader
    lightingShader.Use();
    //Alojar la textura difusa en la localidad 0
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
    //Alojar la textura especular en la localidad 1
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

    // SkyBox
    // Se sigue el mismo proceso descrito con anteiroridad, solo que en este caso es para poder dibujar el skybox
    GLuint skyboxVBO, skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Cargar las texturas que van a conformar al skybox, adicionandolos a un vector llamado faces
    vector<const GLchar*> faces;
    faces.push_back("SkyBox/right.png");
    faces.push_back("SkyBox/left.png");
    faces.push_back("SkyBox/top.png");
    faces.push_back("SkyBox/bottom.png");
    faces.push_back("SkyBox/back.png");
    faces.push_back("SkyBox/front.png");

    // Se carga la textura completa del cubo que conforma al skybox
    GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

    // Se define el FOV, luego el aspecto dependiendo del ancho y alto de la ventana
	//	Finalmente se modifica la altura de la piramide de vision
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Se ejecuta mientras no se cierre la ventana
    while (!glfwWindowShouldClose(window))
    {
        // Ajustar el tiempo entre los frames
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Revisar y llamar a los eventos correspondientes
        glfwPollEvents();
        DoMovement();

        // Define el color del fondo de la ventana. Recibe valores normalizados de RGB, siendo
        // Rojo (1), Verde(2), Azul(3). Para normalizar se tiene que dividir el valor en octal del color entre 255.
        // El ultimo valor es de transparencia
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Opciones de OpenGL
        glEnable(GL_DEPTH_TEST);

        // Se indica que estaremos trabajando con el lightning shader, el cual es el que utilizaremos para poder
        // lograr todos los efectos de iluminacion
        lightingShader.Use();
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        //Uso de camara sintetica
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Se define una luz direccional para que los objetos se puedan iluminar conforme a la direccion de esta luz
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f); //Direccion de la luz
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.1f, 0.1f, 0.1f); //Componente ambiental
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.15f, 0.15f, 0.15f); //Componente difusa
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f); //Componente especular

        // Se define una primer pointlight, que estara ubicada en el sotano. Alcanza una distancia de iluminacion de hasta 65 unidades
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), Light1.x, Light1.y, Light1.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), Light1.x, Light1.y, Light1.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.07f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.017f);

        // Se define una segunda pointlight, que estara ubicada en la facahda principal. Alcanza una distancia de iluminacion de hasta 160 unidades 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), Light2.x, Light2.y, Light2.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), Light2.x, Light2.y, Light2.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.027f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0028f);

        // Configurar la brillantez del material que se usara en general para los objetos
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

        // Definir la matriz de vista respecto a la camara
        glm::mat4 view = camera.GetViewMatrix();

        // Obtener las localizaciones uniformes de las matrices de modelo, vista y proyeccion
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pasarle las matrices a nuestro shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Definir la variable de modelo que ocuparemos para dibujar los objetos en escena
        glm::mat4 model(1);

        // Habilitamos todos los colores para mostar correctamente las texturas, ademas de dejar el canal alpha con el valor por 
        // defecto de 1.0 para los objetos que estaremos dibujando posteriormente. 
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

        //Escritorio
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos el escritorio a la posicion de 26.0f en X, -6.9 en Y y 0.0 en Z
        model = glm::translate(model, glm::vec3(26.0f, -6.9f, 0.0f));
        // Modificamos la matriz de modeloLoc para reflejar los cambios que acabamos de realizar
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Dibujamos el escritorio haciendo uso del lightning shader.
        escritorio.Draw(lightingShader);

        //Copa
        // Trasladamos la copa a la posicion relativa que nos indicen las variables de los ejes X y Y. Z se queda estatico en -2.0
        // Posicion relativa respecto al escritorio,
        model = glm::translate(model, glm::vec3(puntoX, puntoY, -2.0f));
        // Rotamos la copa respecto al eje Z segun la variable giroZ, en sentido contrario
        model = glm::rotate(model, glm::radians(-giroZ), glm::vec3(0.0f, 0.0f, 1.0f));
        // Rotamos la copa respecto al eje X segun la variable giroX, en sentido contrario.
        model = glm::rotate(model, glm::radians(-giroX), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        escritorio_copa.Draw(lightingShader);

        // Primer Cajon del Escritorio
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos el cajon a la posicion absoluta de 27.48 en X, -3.195 en Y y 4.544 en Z
        // En el eje X tendremos movimiento, dependiendo de la variable tras_caj1
        model = glm::translate(model, glm::vec3(27.48f + tras_caj1, -3.195f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        escritorio_cajonChico.Draw(lightingShader);

        // Segundo Cajon del Escritorio
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos el cajon a la posicion absoluta de 27.48 en X, -4.288 en Y y 4.544 en Z
        // En el eje X tendremos movimiento, dependiendo de la variable tras_caj2
        model = glm::translate(model, glm::vec3(27.48f + tras_caj2, -4.288f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        escritorio_cajonGrande.Draw(lightingShader);

        // Tercer Cajon del Escritorio
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos el cajon a la posicion absoluta de 27.48 en X, -5.399 en Y y 4.544 en Z
        // En el eje X tendremos movimiento, dependiendo de la variable tras_caj3
        model = glm::translate(model, glm::vec3(27.48f + tras_caj3, -5.399f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        escritorio_cajonGrande.Draw(lightingShader);

        // Cuarto Cajon del Escritorio
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos el cajon a la posicion absoluta de 27.48 en X, -6.518 en Y y 4.544 en Z
        // En el eje X tendremos movimiento, dependiendo de la variable tras_caj4
        model = glm::translate(model, glm::vec3(27.48f + tras_caj4, -6.518f, 4.544f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        escritorio_cajonGrande.Draw(lightingShader);

        //Silla
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos la silla a la posicion absoulta de 22.5 en X, -6.6 en Y y 0.0 en Z
        model = glm::translate(model, glm::vec3(22.5f, -6.6f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        silla.Draw(lightingShader);

        //Repisas
        // Trasladamos las repisas a la posicion relativa de 5.5 en X, 0.25 en Y y -16.0 en Z respecto a la silla
        model = glm::translate(model, glm::vec3(5.5f, 0.25f, -16.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        repisas.Draw(lightingShader);

        //Primer Alacen
        // Trasladamos el primer alacen a la posicion relativa de -10.0 en X, 0.0 en Y y 0.0 en Z respecto a la silla
        model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
        // Rotamos el mueble respecto al eje Y en 90 grados.
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        alacen.Draw(lightingShader);

        //Segundo Alacen
        // Trasladamos el segundo alacen a la posicion relativa de 0.0 en X, 0.0 en Y y -9.1 en Z respecto a la silla
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -9.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        alacen.Draw(lightingShader);

        //Escalerita
        // Trasladamos la escalerita a la posicion relativa de 7.0 en X, 0.0 en Y y 0.0 en Z respecto a la silla
        model = glm::translate(model, glm::vec3(7.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        escalera.Draw(lightingShader);

        //Cajas con pergaminos
        // Trasladamos la caja con perhaminos a la posicion relativa de 12.0 en X, 0.0 en Y y 0.0 en Z respecto a la silla
        model = glm::translate(model, glm::vec3(12.0f, 0.0f, 0.0f));
        // Rotamos el mueble respecto al eje Y en -30 grados debido a la rotacion anterior de 90 grados
        model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cajas.Draw(lightingShader);

        //Lampara 
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos la lampara  a la posicion absoluta marcada por las variables posX y posZ para los ejes X y Z respectivamente
        // En el eje Y mantenemos el valor base de 5.0f
        model = glm::translate(model, glm::vec3(posX, 5.0f, posZ));
        // Dependiendo de si esta activada la animacion de la lampara que se encuentra moviendose en espiral habilitaremos al objeto
        // de la lampara normal o la lampara inclinada, las cuales varian en la posicion de su pivote para poder hacer la animacion
        // mas dinamica.
        if (espiral)
        {
            // Trasladaremos a la lampara inclinada en el eje Y segun lo indique la variable posY2
            model = glm::translate(model, glm::vec3(0.0f, posY2, 0.0f));
            // Rotaremos a la lampara inclinada en el eje Y de su pivote segun lo indique la variable rotY en sentido contrario
            model = glm::rotate(model, glm::radians(-rotY), glm::vec3(0.0, 1.0f, 0.0f));
            // Rotaremos a la lampara inclinada en el eje X de su pivote segun lo indique la variable rotX2 en sentido contrario
            model = glm::rotate(model, glm::radians(-rotX2), glm::vec3(1.0, 0.0f, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            lampara_inclinada.Draw(lightingShader);

            glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // Cristal de la lampara inclinada
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            // Usamos la variable activaTransparencia para que se habilite la transparencia en este objeto
            glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
            // Añadimos una transparencia del 60% en el objeto.
            glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.6);
            lampara_cristal_inclinada.Draw(lightingShader);

            glDisable(GL_BLEND);  //Desactiva el canal alfa 
        }
        else
        {
            // Trasladaremos a la lampara en el eje Y segun lo indique la variable posY
            model = glm::translate(model, glm::vec3(0.0f, posY, 0.0f));
            // Rotaremos a la lampara en el eje X segun lo indique la variable rotX en sentido contrario
            model = glm::rotate(model, glm::radians(-rotX), glm::vec3(1.0, 0.0f, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            lampara.Draw(lightingShader);


            glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //Cristal de la lampara
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            // Usamos la variable activaTransparencia para que se habilite la transparencia en este objeto
            glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
            // Añadimos una transparencia del 60% en el objeto.
            glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.6);
            lampara_cristal.Draw(lightingShader);

            glDisable(GL_BLEND);  //Desactiva el canal alfa 
        }

        // Reinicializar los valores definidos al inicio
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

        //Fachada
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos la fachada  a la posicion absoluta de 15.0 en X, 12.8 en Y y 50.0 en Z
        model = glm::translate(model, glm::vec3(15.0f, 12.8f, 50.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        fachada.Draw(lightingShader);

        glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Ventanas de la Fachada
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
        // Añadimos una transparencia del 150% en el objeto.
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 0.0, 1.5);
        fachada_ventanas.Draw(lightingShader);

        glDisable(GL_BLEND);  //Desactiva el canal alfa 

        // Volvemos a reinicializar los valores definidos al inicio
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

        // Puerta Principal de la Fachada
        // Trasladamos la puerta principal de la fachada a la posicion relativa de 16.632 en X, 0.79 en Y y 3.876 en Z respecto a la fachada
        model = glm::translate(model, glm::vec3(16.632f, 0.79f, 3.876f));
        // Rotaremos a la puerta principal de la fachada respecto al eje Y segun lo indique la variable rot_PP
        model = glm::rotate(model, glm::radians(rot_PP), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        fachada_puertaPrincipal.Draw(lightingShader);

        // Puerta Pasillo de la Fachada
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos la puerta del pasillo a la posicion 50.0f de 29.082 en X, 12.8 en Y y 37.68 en Z
        model = glm::translate(model, glm::vec3(29.082f, 12.8f, 37.668f));
        // Rotaremos a la puerta del pasillo respecto al eje Z segun lo indique la variable rot_PC
        model = glm::rotate(model, glm::radians(rot_PC), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        fachada_puertaSotano.Draw(lightingShader);

        //Pasto
        //Reinicializamos la variable model
        model = glm::mat4(1);
        // Trasladamos el pasto a la posicion absoluta de 15.0 en X, 12.3 en Y y 50.0 en Z
        model = glm::translate(model, glm::vec3(15.0f, 12.3f, 50.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        pasto.Draw(lightingShader);

        //Pasillo
        // Trasladamos el pasillo entre la facahda y el sotano a la posicion relativa de 10.0 en X, -18.75 en Y y -16.7 en Z respecto al pasto
        model = glm::translate(model, glm::vec3(10.0f, -18.75f, -16.7f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        pasillo.Draw(lightingShader);

        //Sotano
        // Trasladamos el sotano a la posicion relativa de 00.0 en X, -0.15 en Y y -38.6 en Z respecto al pasto
        model = glm::translate(model, glm::vec3(0.0f, -0.15f, -38.6f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        sotano.Draw(lightingShader);

        // Puerta del Sotano
        // Trasladamos la puerta sotano a la posicion relativa de 3.057 en X, 0.0 en Y y 19.0111 en Z respecto al pasto
        model = glm::translate(model, glm::vec3(3.057f, 0.0f, 19.0111f));
        // Rotaremos a la puerta del sotano respecto al eje Y segun lo indique la variable rot_PS
        model = glm::rotate(model, glm::radians(rot_PS), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        sotano_puerta.Draw(lightingShader);

        // Desenlazar de memoria
        glBindVertexArray(0);

        // Dibujar los objetos de iluminacion, por lo tanto ahora se usa el lamp shader
        lampShader.Use();

        // Obtener la localizaciones de las matrices de modelo, vista y proyeccion del lamp shader
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");

        // Configurar las matrices de vista y proyeccion 
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Reinicializamos la variable de model
        model = glm::mat4(1);
        // Trasladamos hacia la posicion de la luz, que en este caso empieza en el origen
        model = glm::translate(model, lightPos);
        // Esacalamos a 1.0 para mantener las proporciones
        model = glm::scale(model, glm::vec3(1.0f));
        // Modificamos la matriz modelLoc con los cambios realizados
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Se dibujan las dos pointlights
        for (GLuint i = 0; i < 2; i++)
        {
            // Reinicializamos la variable de model
            model = glm::mat4(1);
            // Trasladamos hacia la posicion de la pointlight
            model = glm::translate(model, pointLightPositions[i]);
            // Escalamos a 0.2 para hacer un cubo mas pequeño
            model = glm::scale(model, glm::vec3(0.2f)); 
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(VAO);
            // En caso de que no este la animacion de la lampara activa, entonces dibujamos al pequeño cubo que representa a la pointlight
            if(!anim_L)
                glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Finalmente se dibuja el SkyBox
        // Funcion de profundidad
        glDepthFunc(GL_LEQUAL); 
        // Se utiliza el skybox shader
        SkyBoxshader.Use();
        // Se reinicializa la matriz de vista
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Se liga el VAO del skybox para dibujar el cubo con sus respectivas texturas y posiciones definidas al inicio del codigo
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Se vuelve a poner la funcion de profundidad por defecto
        glDepthFunc(GL_LESS); 

        // Intercambiar los bufers
        glfwSwapBuffers( window );
    }

    // Limpiar los recursos de memoria utilizados
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    // Terminar GLFW para que se limpie la memoria que utilizo
    glfwTerminate();
    // Terminar la funcion
    return 0;
}


// Funcion para poder realizar el movimiento de la camara y de las animaciones
void DoMovement( )
{
    // Controles de camara
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

    // Animacion sencilla de la puerta principal de la fachada
    if (anim_PP)
    {
        // Primera parte de la animacion, en donde la puerta gira en sentido antihorario hasta 90 grados
        if (regreso_PP == 0)
        {
            if (rot_PP < 90.0f)
                rot_PP += 1.0f;
            else
                regreso_PP = 1;
        }
        // Segunda parte de la animacion, en donde la puerta gira en sentido horario hasta -90 grados
        else if (regreso_PP == 1)
        {
            if (rot_PP > -90.0f)
                rot_PP -= 1.0f;
            else
                regreso_PP = 2;
        }
        // Ultima parte de la animacion, en donde la puerta gira en sentido antihorario hasta su posicion inicial
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
    
    // Animacion sencilla de la puerta del pasillo 
    if (anim_PC)
    {
        // Primera parte de la animacion, en donde se abre la puerta del pasillo en sentido horario
        if (!regreso_PC)
        {
            if (rot_PC > -110.0f)
                rot_PC -= 1.0f;
            else
                regreso_PC = true;
        }
        // Ultima parte de la animacion, en donde se cierra la puerta del pasillo en sentido antihorario
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

    // Animacion sencilla de la puerta del sotano
    if (anim_PS)
    {
        // Primera parte de la animacion, en donde la puerta gira en sentido antihorario hasta 90 grados
        if (regreso_PS == 0)
        {
            if (rot_PS < 90.0f)
                rot_PS += 1.0f;
            else
                regreso_PS = 1;
        }
        // Segunda parte de la animacion, en donde la puerta gira en sentido horario hasta -90 grados
        else if (regreso_PS == 1)
        {
            if (rot_PS > -90.0f)
                rot_PS -= 1.0f;
            else
                regreso_PS = 2;
        }
        // Ultima parte de la animacion, en donde la puerta gira en sentido antihorario hasta su posicion inicial
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

    // Animacion sencilla de los cajones del escritorio
    if (anim_C)
    {
        // Primera parte de la animacion, en donde se abre el ultimo cajon al primero, uno por uno
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
        // Ultima parte de la animacion, en donde se cierra el primero al ultimo cajon, uno por uno
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

    // Animacion compleja del movimiento de la lampara del techo que se compone de tres recorridos
    // El primero va desde el origen hasta la posicion inicial del espiral
    // El segundo es la movimiento que describe un movimiento en espiral 
    if (anim_L)
    {
        // Segunda parte de la animacion, en donde la lampara va moveindose en Z y X describiendo una trayectoria en espiral
        // a la par que se encuentra rotando sobre el eje Y
        // Asimismo se mueve la pointlight dentro de la lampara describiendo una trayectoria circular
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
            // Ultima parte de la animacion, en donde la lampara regresa a su posicion inicial, rotando en X en sentido contrario
            // al inicial, y moviendose en Z igualmente.
            // Asimismo se mueve la pointlight dentro de la lampara
            if (regreso_L)
            {
                rotX2 -= 0.5f;
                posZ += 0.075f;
                posY2 += 0.01438f;
                if (rotX2 <= -40.0f)
                {
                    // Volviendo a inicializar todas las variables para poder volver a reproducir la animacion
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
                    pointLightPositions[0].z = posZ - 3.0f;
            }
            else
            {
                // Primera parte de la animacion, en donde la lampara va rotando en X y moviendose en Z hasta la posicion inicial 
                // del movimiento en espiral
                // Asimismo se mueve la pointlight dentro de la lampara
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

    // Animacion compleja del movimiento de la copa, la cual se desliza por el escritorio y describe un tiro parabolico
    // hasta que llega al piso y rota un poco.
    if (anim_T)
    {
        // Ultima parte de la animacion, en donde la copa retorna a su posicion inicial
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
            // Primera parte de la animacion, en donde primero se desliza la copa al borde del escritorio para posteriormente
            // describir un tiro parabolico a la par que rota respecto al eje Z hasta que la copa toca el piso
            // Una vez que llega al piso la copa gira respecto a su eje X hasta que se detenga
            if (puntoX <= 2.0f)
                puntoX += 0.1f;
            else
            {
                if (puntoY >= 0.4f)
                {
                    puntoX = 2.0f + 3.0f * t;
                    puntoY = 4.8f - (0.96f * t * t) / 2;
                    t += 0.05f;
                    giroZ += 1.487f;
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

// Esta funcion siempre se llama cuando se presiona una tecla
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    // Se cierra la ventana cuando se preciona la tecla de escape
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    // Se utiliza para verificar que solo se accione una vez la tecla aun cuando se deje presionada
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

    // Cuando se presiona la tecla C se acciona la animacion de la puerta principal de la fachada
    if (keys[GLFW_KEY_C])
        anim_PP = !anim_PP;

    // Cuando se presiona la tecla V se acciona la animacion de la puerta del pasillo para el pasillo
    if (keys[GLFW_KEY_V])
        anim_PC = !anim_PC;

    // Cuando se presiona la tecla B se acciona la animacion de la puerta del sotano
    if (keys[GLFW_KEY_B])
        anim_PS = !anim_PS;

    // Cuando se presiona la tecla N se acciona la animacion de los cajones del escritorio
    if (keys[GLFW_KEY_N])
        anim_C = !anim_C;

    // Cuando se presiona la tecla M se acciona la animacion de la lampara colgante
    if (keys[GLFW_KEY_M])
        anim_L = !anim_L;

    // Cuando se presiona la tecla L se acciona la animacion de la copa
    if (keys[GLFW_KEY_L])
        anim_T = !anim_T;
}

// Funcion que se llama cuando se mueve el mouse 
void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Se invierte ya que las coordenadas en Y van desde el fondo a la izquierda
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

