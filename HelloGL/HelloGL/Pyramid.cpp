#include "Pyramid.h"
#include <iostream>
#include <fstream>
using namespace std;



Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh)
{
	_position = new Vector3();
	_position->x = x;
	_position->y = y;
	_position->z = z;

	_mesh = mesh;
}


Pyramid::~Pyramid()
{
}

void Pyramid::Update()
{

}

void Pyramid::Draw()
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
	glTranslatef(_position->x, _position->y, _position->z);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < _mesh->IndexCount; i++)
	{	
		glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
	}

	glEnd();
	glPopMatrix();
}
