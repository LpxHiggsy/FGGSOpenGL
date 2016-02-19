#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "Structures.h"
#include "SceneObject.h"
#include "Texture2D.h"

class Rocks : public SceneObject
{
private:
	
	ObjMesh* _objMesh;
	Texture2D* _texture;
	GLfloat _rotation;
	GLfloat _rotationSpeed;
	Vector3* _position;

public:
	Rocks(ObjMesh* mesh, Texture2D* texture, float x, float y, float z);
	~Rocks();


	void Draw();
	void Update();
};

