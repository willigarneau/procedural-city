/*	
	Procedural city generator
	Infography 2018
	Cégep Lévis-Lauzon

	OpenGL 3.42,
	FreeGlut 3.7,
	Glew 2.1,
	GLM 0.9.3,
	SOIL 1.16,

	Copyright (c) 2018, William Garneau and the respective contributors
	All rights reserved.
*/

#include <iostream>

/******APIs*****/
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\gtc\matrix_transform.hpp"
#include "Dependencies\soil\src\SOIL.h"
/*****Classes personnalisées*******/
#include "ShaderLoader\Shader_Loader.h"
#include "HouseMaker\House_Maker.h"
#include "TextureLoader\Texture_Loader.h"


/**********namespaces**************/
using namespace Core;
using namespace House;
using namespace texCore;


/****Handlers globaux*****/
GLuint textureProgram;
GLuint skyboxProgram;
GLuint vaoBase;
GLuint vaoToit;
GLuint vaoSol;
GLuint vaoNuage[2];
GLuint vaoHorizon[4];
GLuint vaoGrass;
GLuint vaoSkybox;
GLuint gProjection;
GLuint gVue;
GLuint gModele;
GLuint texMaison;
GLuint texBuilding1;
GLuint texBuilding2;
GLuint texBuilding3;
GLuint texBuilding4;
GLuint texBuilding5;
GLuint texBuilding6;
GLuint texBuilding7;
GLuint texBuilding8;
GLuint texBuilding9;
GLuint texBuilding10;
GLuint texBuilding11;
GLuint texSol;
GLuint texToit;
GLuint texNuage;
GLuint texHorizon;
GLuint texGrass;
GLuint texSkybox;

/******variables globales*******/
glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 7.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.25f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float multipleCouleur[4] = { 1.0,1.0,1.0,1.0 };
bool firstMouse = true;
bool firstKey = false;
GLfloat yaw = -90.0f;	
GLfloat pitch = 0.0f;
GLfloat lastX = 0;
GLfloat lastY = 0;
bool boutons[5] = { false,false,false,false,false };
bool warpsouris=false;
int nbBuildings = 40;
bool hasStarted = false;
// Scaling
std::vector<float> _x;
std::vector<float> _y;
std::vector<float> _z;
std::vector<GLuint> _texture;

void getUniforms(GLuint *program)
{
	glUseProgram(*program);
	gProjection = glGetUniformLocation(*program, "gProjection");
	assert(gProjection != 0xFFFFFFFF);

	gVue = glGetUniformLocation(*program, "gVue");
	assert(gVue != 0xFFFFFFFF);
}

GLuint getRandomTexture(int random) {
	switch (random) {
		case 0:
			return texMaison;
		case 1:
			return texBuilding1;
		case 2:
			return texBuilding2;
		case 3:
			return texBuilding3;
		case 4:
			return texBuilding4;
		case 5:
			return texBuilding5;
		case 6:
			return texBuilding6;
		case 7:
			return texBuilding7;
		case 8:
			return texBuilding8;
		case 9:
			return texBuilding9;
		case 10:
			return texBuilding10;
		case 12:
			return texBuilding11;
		default:
			return 0;
	}
}

void Limites()
{
	if (cameraPos.z <= -200.0)
	{
		cameraPos.z = -200.0;
	}
	if (cameraPos.z >= 200.0)
	{
		cameraPos.z = 200.0;
	}
	if (cameraPos.x <= -200.0)
	{
		cameraPos.x = -200.0;
	}
	if (cameraPos.x >= 200.0)
	{
		cameraPos.x = 200.0;
	}
}

void deplacement()
{
	GLfloat cameraSpeed = 0.8f;
	glm::vec3 camDevant;
	camDevant.x = cameraFront.x;
	camDevant.z = cameraFront.z;

	if (boutons[0] == true) {
		cameraPos -= glm::normalize(glm::cross(camDevant, cameraUp)) * cameraSpeed;
	}
	if (boutons[1] == true) {
		cameraPos += cameraSpeed * camDevant;
	}
	if (boutons[2] == true) {
		cameraPos -= cameraSpeed * camDevant;
	}
	if (boutons[3] == true) {
		cameraPos += glm::normalize(glm::cross(camDevant, cameraUp)) * cameraSpeed;
	}
	if (boutons[4] == true) {
		_x.clear();
		_y.clear();
		_z.clear();
		_texture.clear();
		hasStarted = false;
	}
	Limites();
}

void drawBuilding()
{	
	House_Maker maMaison;

	glBindVertexArray(vaoBase);
	maMaison.creeBase(10, 50, 5.0f, glm::vec3(rand() % 2, rand() % 2, rand() % 2));
	glBindVertexArray(0);

	glBindVertexArray(vaoToit);
	maMaison.creeToit(0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glBindVertexArray(0);

	glBindVertexArray(vaoSol);
	maMaison.creeSurface(500.0, -1.01, 500.0, 100.0, true, false);
	glBindVertexArray(0);

	glBindVertexArray(vaoNuage[0]);
	maMaison.creeSurface(600.0,350.0,700.0, 1.0, true, false);
	glBindVertexArray(0);

	glBindVertexArray(vaoNuage[1]);
	maMaison.creeSurface(600.0, 150.0, 700.0, 2.0, true, false);
	glBindVertexArray(0);

	glBindVertexArray(vaoHorizon[0]);
	maMaison.creeSurface(500.0,500.0,-500.0,3.0, false, false);
	glBindVertexArray(0);

	glBindVertexArray(vaoHorizon[1]);
	maMaison.creeSurface(500.0, 500.0, 500.0, 3.0, false, false);
	glBindVertexArray(0);

	glBindVertexArray(vaoHorizon[2]);
	maMaison.creeSurface(500.0, 500.0, 500.0, 3.0, false, true);
	glBindVertexArray(0);

	glBindVertexArray(vaoHorizon[3]);
	maMaison.creeSurface(-500.0, 500.0, 500.0, 3.0, false, true);
	glBindVertexArray(0);


	glBindVertexArray(vaoGrass);
	maMaison.creeSurface(3.0, 0.5, 4.01, 1.0, false, false);
	glBindVertexArray(0);

	glBindVertexArray(vaoSkybox);
	maMaison.creeBase(1.0, 1.0, 1.0, glm::vec3(1.0, 0.0, 0.0));
	glBindVertexArray(0);
}

void renduMaison()
{
	float randY = 1.0;
	if (!hasStarted) {
		for (int i = 0; i < nbBuildings * nbBuildings; i++) {
			float randomX = ((2.0f - 0.25f) * ((float)rand() / RAND_MAX)) + 0.25f;
			float randomY = ((4.5f - 0.25f) * ((float)rand() / RAND_MAX)) + 0.25f;
			float randomZ = ((2.0f - 0.75f) * ((float)rand() / RAND_MAX)) + 0.75f;
			float randomTex = rand() % 11;
			_x.push_back(randomX);
			_y.push_back(randomY);
			_z.push_back(randomZ);
			_texture.push_back(randomTex);
		}
		hasStarted = true;
	}
	glm::mat4 modele=glm::mat4(1.0);
	for (int y = 1; y < nbBuildings / 2; y++) {
		for (int x = 1; x < nbBuildings / 2; x++)
		{
			glUniformMatrix4fv(glGetUniformLocation(textureProgram, "gModele"), 1, GL_FALSE, &modele[0][0]);
			glBindVertexArray(vaoBase);
			glBindTexture(GL_TEXTURE_2D, getRandomTexture(_texture[x * y]));
			glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
			glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glBindVertexArray(vaoToit);
			glBindTexture(GL_TEXTURE_2D, texToit);
			glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
			glDrawElements(GL_TRIANGLES, 6 * 3, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			modele = glm::mat4(1.0f);
			randY *= -1;
			modele = glm::translate(modele, glm::vec3(10.0*x, 0.0, -10.0*randY*y));
			modele = glm::scale(modele, glm::vec3(_x[x * y], _y[x * y], _z[x * y]));
			//modele = glm::rotate(modele, glm::radians(1.0f*x), glm::vec3(0.0, 1.0, 0.0));
		}
		randY *= -1;
	}

}

void drawSkybox()
{
	// skybox cube
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxProgram, "Skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texSkybox);
	glBindVertexArray(vaoSkybox);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//Fonction de rappel du rendu graphique
void renduScene()
{
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 modele;

	deplacement();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	projection = glm::perspective(glm::radians(45.0f), glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)*1.0f, 0.1f, 800.0f);
	
	getUniforms(&skyboxProgram);
	view = glm::mat4(glm::mat3(glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)));
	glUniformMatrix4fv(gProjection, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(gVue, 1, GL_FALSE, &view[0][0]);
	drawSkybox();
	
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	gModele = glGetUniformLocation(textureProgram, "gModele");
	assert(gModele != 0xFFFFFFFF);

	getUniforms(&textureProgram);
	glUniformMatrix4fv(gProjection, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(gVue, 1, GL_FALSE, &view[0][0]);
	glUniform4fv(glGetUniformLocation(textureProgram, "color"), 1, multipleCouleur);

	glActiveTexture(GL_TEXTURE0);

	renduMaison();

	modele = glm::mat4(1.0);
	glUniformMatrix4fv(gModele, 1, GL_FALSE, &modele[0][0]);

	glBindVertexArray(vaoSol);
	glBindTexture(GL_TEXTURE_2D, texSol);
	glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	for (int i = 0; i < 2; i++)
	{
		glBindVertexArray(vaoNuage[i]);
		glBindTexture(GL_TEXTURE_2D, texNuage);
		glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		
	}
	for (int i = 0; i < 4; i++)
	{
		glBindVertexArray(vaoHorizon[i]);
		glBindTexture(GL_TEXTURE_2D, texHorizon);
		glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	glBindVertexArray(vaoGrass);
	glBindTexture(GL_TEXTURE_2D, texGrass);
	glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	
	glutSwapBuffers();
}

void clavier(unsigned char bouton, int x, int y)
{
	switch (bouton)
	{
	case 'a':
		boutons[0] = true;
		break;
	case 'w':
		boutons[1] = true;
		break;
	case 's':
		boutons[2] = true;
		break;
	case 'd':
		boutons[3] = true;
		break;
	case 'r':
		boutons[4] = true;
		break;
	case 27:
		glutLeaveMainLoop();
		break;

	}
}

void releaseClavier(unsigned char bouton, int x, int y)
{

	switch (bouton)
	{
	case 'a':
		boutons[0] = false;
		break;
	case 'w':
		boutons[1] = false;
		break;
	case 's':
		boutons[2] = false;
		break;
	case 'd':
		boutons[3] = false;
		break;
	case 'r':
		boutons[4] = false;
		break;
	}
}

void souris(int x, int y)
{

	if (warpsouris)
	{
		warpsouris = false;
		lastX = x;
		lastY = y;
	}
	else
	{
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		GLfloat xoffset = x - lastX;
		GLfloat yoffset = lastY - y;
		lastX = x;
		lastY = y;

		GLfloat sensitivity = 0.3;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);

		warpsouris = true;
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
}

/*****************************************/
//Fonction d'initialisation des textures
void initTextures()
{
	Texture_Loader textureLoader;
	texMaison = textureLoader.CreateTexture2D("textures/woodenhouse.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texSol = textureLoader.CreateTexture2D("textures/grass.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);
	texToit = textureLoader.CreateTexture2D("textures/toit2.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding1 = textureLoader.CreateTexture2D("textures/building1.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding2 = textureLoader.CreateTexture2D("textures/building2.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding3 = textureLoader.CreateTexture2D("textures/building3.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding4 = textureLoader.CreateTexture2D("textures/building4.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding5 = textureLoader.CreateTexture2D("textures/building5.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding6 = textureLoader.CreateTexture2D("textures/building6.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding7 = textureLoader.CreateTexture2D("textures/building7.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding8 = textureLoader.CreateTexture2D("textures/building8.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding9 = textureLoader.CreateTexture2D("textures/building9.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding10 = textureLoader.CreateTexture2D("textures/building10.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texBuilding11 = textureLoader.CreateTexture2D("textures/building11.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	
	texNuage = textureLoader.CreateTexture2D("textures/cloud.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGBA);
	texHorizon = textureLoader.CreateTexture2D("textures/city.png", GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGBA);
	texGrass = textureLoader.CreateTexture2D("textures/grass.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGBA);

	std::vector<char*> faces;
	faces.push_back("textures/right.jpg");
	faces.push_back("textures/left.jpg");
	faces.push_back("textures/top.jpg");
	faces.push_back("textures/bottom.jpg");
	faces.push_back("textures/back.jpg");
	faces.push_back("textures/front.jpg");
	texSkybox = textureLoader.CreateSkyboxTexture(faces);
}

/*****************************************/
//Fonction d'initialisation des shaders
void initShaders()
{
	Core::Shader_Loader shaderLoader;
	textureProgram = shaderLoader.CreateProgram("vertexShader.glsl", "fragmentShader.glsl");
	skyboxProgram = shaderLoader.CreateProgram("vertSkybox.glsl", "fragSkybox.glsl");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//glUseProgram(textureProgram);

	/*gProjection = glGetUniformLocation(textureProgram, "gProjection");
	assert(gProjection != 0xFFFFFFFF);

	gVue = glGetUniformLocation(textureProgram, "gVue");
	assert(gVue != 0xFFFFFFFF);

	gModele = glGetUniformLocation(textureProgram, "gModele");
	assert(gModele != 0xFFFFFFFF);*/

	glGenVertexArrays(1, &vaoBase);
	glGenVertexArrays(1, &vaoToit);
	glGenVertexArrays(1, &vaoSol);
	glGenVertexArrays(2, vaoNuage);
	glGenVertexArrays(4, vaoHorizon);
	glGenVertexArrays(1, &vaoGrass);
	glGenVertexArrays(1, &vaoSkybox);

}
void passeTemps(int temps)
{
	multipleCouleur[temps] -= 0.5;
	temps++;

	if(temps == 4)
	{
		multipleCouleur[0] = 1.0;
		multipleCouleur[1] = 1.0;
		multipleCouleur[2] = 1.0;
		multipleCouleur[3] = 1.0;
		temps = 0;
	}
	
	glutTimerFunc(5000, passeTemps, temps);
}
/******************************************/
void fermeture()
{
	glutLeaveMainLoop();
}
//Fonction principale d'initialisation et d'exécution
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutCreateWindow("Travail Pratique 3, par William Garneau");
	glutFullScreen();
	/*******************/
	glewInit();
	initShaders();
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 2);
	/******************/
	glutDisplayFunc(renduScene);
	glutCloseFunc(fermeture);
	glutKeyboardFunc(clavier);
	glutPassiveMotionFunc(souris);
	glutKeyboardUpFunc(releaseClavier);
	glutIdleFunc(renduScene);
	//glutTimerFunc(5000,passeTemps,0);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glClearColor(0.0f, 0.4f, 0.5f, 0.0f);

	glutSetCursor(GLUT_CURSOR_NONE);

	/***Initialisation de la maison****/
	initTextures();
	drawBuilding();
	/**********************************/
	glutMainLoop();
	/***************/
	glDeleteVertexArrays(1, &vaoBase);
	glDeleteVertexArrays(1, &vaoToit);
	glDeleteVertexArrays(1, &vaoSol);
	glDeleteVertexArrays(2, vaoNuage);
	glDeleteVertexArrays(4, vaoHorizon);
	glDeleteVertexArrays(1, &vaoGrass);
	glDeleteProgram(skyboxProgram);
	glDeleteProgram(textureProgram);
	/**************/

	return 0;
}

