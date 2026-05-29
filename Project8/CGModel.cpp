#include "CGModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CGCamera.h"
#include "CGScene.h"
#include "resource.h"

//
// FUNCIÓN: CGModel::initialize(int, int)
//
// PROPÓSITO: Initializa el modelo 3D
//
void CGModel::initialize(int w, int h)
{
    // Crea el programa
    program = new CGShaderProgram(IDR_SHADER1, IDR_SHADER2, -1, -1, -1);
    // program = new CGShaderProgram("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl", NULL, NULL, NULL);
    if (program->IsLinked() == GL_FALSE) return;
    program->Use();

    // Crea la cámara
    camera = new CGCamera();
    camera->SetPosition(0.0f, 5.0f, 30.0f);

    // Crea la escena
    scene = new CGScene();

    // Asigna el viewport y el clipping volume
    resize(w, h);

    // Opciones de dibujo
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//
// FUNCIÓN: CGModel::finalize()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
void CGModel::finalize()
{
    delete camera;
    delete scene;
    delete program;
}

//
// FUNCIÓN: CGModel::resize(int w, int h)
//
// PROPÓSITO: Asigna el viewport y el clipping volume
//
void CGModel::resize(int w, int h)
{
    double fov = glm::radians(15.0);
    double sin_fov = sin(fov);
    double cos_fov = cos(fov);
    if (h == 0) h = 1;
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    GLfloat wHeight = (GLfloat)(sin_fov * 0.2 / cos_fov);
    GLfloat wWidth = wHeight * aspectRatio;

    glViewport(0, 0, w, h);
    projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 400.0f);
}

//
// FUNCIÓN: CGModel::render()
//
// PROPÓSITO: Genera la imagen
//
void CGModel::render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera->ViewMatrix();
    scene->Draw(program, projection, view);
}

//
// FUNCIÓN: CGModel::update()
//
// PROPÓSITO: Anima la escena
//
void CGModel::update()
{
    camera->MoveFront();
//    CameraConstraints();
}

//
// FUNCIÓN: CGModel::key_pressed(int)
//
// PROPÓSITO: Respuesta a acciones de teclado
//
void CGModel::key_pressed(int key)
{
    switch (key)
    {
    case GLFW_KEY_UP:
        camera->TurnDown();
        break;
    case GLFW_KEY_DOWN:
        camera->TurnUp();
        break;
    case GLFW_KEY_LEFT:
        camera->TurnCCW();
        break;
    case GLFW_KEY_RIGHT:
        camera->TurnCW();
        break;
    case GLFW_KEY_S:
        camera->SetMoveStep(0.0f);
        break;
    case GLFW_KEY_RIGHT_BRACKET:
    case GLFW_KEY_KP_ADD:
        camera->SetMoveStep(camera->GetMoveStep() + 0.1f);
        break;
    case GLFW_KEY_LEFT_BRACKET:
    case GLFW_KEY_MINUS:
    case GLFW_KEY_KP_SUBTRACT:
        camera->SetMoveStep(camera->GetMoveStep() - 0.1f);
        break;
    case GLFW_KEY_Q:
        camera->SetMoveStep(0.1f);
        camera->MoveUp();
        camera->SetMoveStep(0.0f);
        break;
    case GLFW_KEY_A:
        camera->SetMoveStep(0.1f);
        camera->MoveDown();
        camera->SetMoveStep(0.0f);
        break;
    case GLFW_KEY_O:
        camera->SetMoveStep(0.1f);
        camera->MoveLeft();
        camera->SetMoveStep(0.0f);
        break;
    case GLFW_KEY_P:
        camera->SetMoveStep(0.1f);
        camera->MoveRight();
        camera->SetMoveStep(0.0f);
        break;
    case GLFW_KEY_K:
        camera->TurnLeft();
        break;
    case GLFW_KEY_L:
        camera->TurnRight();
        break;
    }
}

//
//  FUNCIÓN: CGModel:::mouse_button(int button, int action)
//
//  PROPÓSITO: Respuesta del modelo a un click del ratón.
//
void CGModel::mouse_button(int button, int action)
{
}

//
//  FUNCIÓN: CGModel::mouse_move(double xpos, double ypos)
//
//  PROPÓSITO: Respuesta del modelo a un movimiento del ratón.
//
void CGModel::mouse_move(double xpos, double ypos)
{
}

//
//  FUNCIÓN: CGModel::CameraConstraints()
//
//  PROPÓSITO: Limita el movimiento de la cámara a una cierta zona
//
void CGModel::CameraConstraints()
{
    glm::vec3 pos = camera->GetPosition();
    int constraint = 0;
    if (pos.y < 1.0f) { pos.y = 1.0f; constraint = 1; }
    if (pos.y > 40.0f) { pos.y = 40.0f; constraint = 1; }
    if (pos.x > 100.0f) { pos.x = 100.0f; constraint = 1; }
    if (pos.x < -100.0f) { pos.x = -100.0f; constraint = 1; }
    if (pos.z > 100.0f) { pos.z = 100.0f; constraint = 1; }
    if (pos.z < -100.0f) { pos.z = -100.0f; constraint = 1; }
    if (constraint == 1)
    {
        camera->SetPosition(pos.x, pos.y, pos.z);
        camera->SetMoveStep(0.0f);
    }
}