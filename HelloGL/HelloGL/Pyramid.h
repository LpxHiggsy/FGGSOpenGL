#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "Structures.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:
	
	Mesh* _mesh;
public:
	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid();

	Vector3* _position;

	void Draw();
	void Update();
};

