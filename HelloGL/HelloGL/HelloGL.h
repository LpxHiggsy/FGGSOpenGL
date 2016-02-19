#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "Structures.h"
#include "Object.h"
#include "MeshLoader.h"
#include "objectcube.h"
#include "Texture2D.h"
#include "Linkedlist.h"
#include "Rocks.h"
#include "RocketObj.h"
#include "Player.h"
#include "Planets.h"
#include "EnemyShip.h"
#define REFRESHRATE 16
#define BANANACOUNT 40
#define CUBECOUNT 500
#define ROCKS 40
#define ROCKETCOUNT 40
#define ENEMYCOUNT 50

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL();

	Camera* camera;

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void DrawString(const char* text, const Vector3* position, const Color* color);
	void Reshape(int width, int height);

private:

	GLfloat _rotation;
	Vector4* _lightPosition; 
	Lighting* _lightData;
	Linkedlist* cubeList;
	Linkedlist* bananaList;
	Linkedlist* rockList;
	Linkedlist* rocketList;
	Linkedlist* enemyList;
	SceneObject* playerObj;
	SceneObject* planetObj;
	SceneObject* planetObj2;
	SceneObject* planetObj3;
	SceneObject* planetObj4;
	SceneObject* planetObj5;

};

