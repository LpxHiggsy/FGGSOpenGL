#include "objectcube.h"
#include <iostream>
#include <fstream>
using namespace std;



objectcube::objectcube(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture) : SceneObject(mesh->Mesh)
{
	_rotation = 0.0f;

	_position = new Vector3(x,y,z);

	_material = new Material();
	_material->ambient.x = 0.0;
	_material->ambient.y = 0.00;
	_material->ambient.z = 0.00;
	_material->ambient.w = 0.0;
	_material->diffuse.x = 0.8;
	_material->diffuse.y = 0.05;
	_material->diffuse.z = 0.05;
	_material->diffuse.w = 0.0;
	_material->specular.x = 0.0;
	_material->specular.y = 0.0;
	_material->specular.z = 0.0;
	_material->specular.w = 0.0;
	_material->shininess = 100.0f;

	_mesh = mesh;
	_texture = texture;
}


objectcube::~objectcube()
{
}

void objectcube::Update()
{

}

void objectcube::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);*/

	glPushMatrix();
	glTranslatef(_position->x, _position->y, _position->z);
	glRotatef(_rotation, 2.0f, 2.0f, 2.0f);
	
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _mesh->Mesh->IndexCount; i++)
	{
		glNormal3fv(&_mesh->Mesh->Normals[_mesh->Mesh->Indices[i]].x);
		glTexCoord2fv(&_mesh->TexCoords[_mesh->Mesh->Indices[i]].u);
		glVertex3fv(&_mesh->Mesh->Vertices[_mesh->Mesh->Indices[i]].x);
	}

	glEnd();

	glEnd();
	glPopMatrix();
}
