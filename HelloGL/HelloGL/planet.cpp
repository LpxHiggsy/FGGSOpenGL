#include "Planets.h"
#include <iostream>
#include <fstream>
using namespace std;


Planets::Planets(ObjMesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(nullptr), _objMesh(mesh)
{
	_rotation = 0.0f;
	_rotationSpeed = 0.5f;

	_position = new Vector3(x, y, z);

	_texture = texture;
}

Planets::~Planets()
{

}

void Planets::Update()
{
	_rotation += _rotationSpeed;

}

void Planets::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glPushMatrix();
	glTranslatef(_position->x, _position->y, _position->z);
	glRotatef(_rotation, 0.0f, 0.5f, 0.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	for (int i = 0; i < _objMesh->MeshIndices.size(); i++)
	{
		glVertexPointer(3, GL_FLOAT, 0, &_objMesh->Vertices[0]);
		glNormalPointer(GL_FLOAT, 0, &_objMesh->Normals[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &_objMesh->TexCoords[0]);

		glDrawElements(GL_TRIANGLES, _objMesh->MeshIndices[i].size(), GL_UNSIGNED_SHORT, &_objMesh->MeshIndices[i][0]);
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}