#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "Structures.h"
#include "SceneObject.h"
#include "Texture2D.h"

class Player : public SceneObject
{
private:

	ObjMesh* _objMesh;
	Texture2D* _texture;
	GLfloat _rotation;
	Vector3* _position;

public:
	Player(ObjMesh* mesh, Texture2D* texture);
	~Player();

	void Draw();
	void Update();
};

