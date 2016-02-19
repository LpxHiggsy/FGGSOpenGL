#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include "Structures.h"
#include "SceneObject.h"
#include "Texture2D.h"

class objectcube : public SceneObject
{
private:
	
	TexturedMesh* _mesh;
	Texture2D* _texture;
	Material* _material;
	GLfloat _rotation;
	Vector3* _position;

public:
	objectcube(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture);
	~objectcube();

	void Draw();
	void Update();
};

