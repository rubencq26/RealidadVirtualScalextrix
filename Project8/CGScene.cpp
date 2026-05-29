#include "CGScene.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGShaderProgram.h"
#include "CGObject.h"
#include "CGLight.h"
#include "F18_Hornet.h"


//
// FUNCIÓN: CGScene::CGScene()
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CGScene::CGScene()
{
    glm::vec3 Ldir = glm::vec3(1.0f, -0.8f, -1.0f);
    Ldir = glm::normalize(Ldir);
    light = new CGLight();
    light->SetLightDirection(Ldir);
    light->SetAmbientLight(glm::vec3(0.3f, 0.3f, 0.3f));
    light->SetDifusseLight(glm::vec3(0.7f, 0.7f, 0.7f));
    light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

    object = new F18_Hornet(); // Introducir aquí el constructor del objeto

}

//
// FUNCIÓN: CGScene3:~CGScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CGScene::~CGScene()
{
    delete light;
    delete object;
}

//
// FUNCIÓN: CGScene::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void CGScene::Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
    light->SetUniforms(program);
    object->Draw(program, proj, view);
}
