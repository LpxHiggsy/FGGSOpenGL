#include "Cube.h"
#include <iostream>
#include <fstream>
#include "Cube.txt"
using namespace std;



Vertex Cube::indexedVertices[] = nullptr;
//{ 1, 1, 1, -1, 1, 1,  // v0,v1,
//-1, -1, 1, 1, -1, 1,   // v2,v3
//1, -1, -1, 1, 1, -1,    // v4,v5
//-1, 1, -1, -1, -1, -1 }; // v6,v7

Color Cube::indexedColors[] = nullptr;
//{ 1, 1, 1, 1, 1, 0,   // v0,v1,
//1, 0, 0, 1, 0, 1,   // v2,v3
//0, 0, 1, 0, 1, 1,   // v4,v5
//0, 1, 0, 0, 0, 0 }; //v6,v7	

GLushort Cube::indices[] = nullptr;
//{ 0, 1, 2, 2, 3, 0,      // front
//0, 3, 4, 4, 5, 0,      // right
//0, 5, 6, 6, 1, 0,      // top
//1, 6, 7, 7, 2, 1,      // left
//7, 4, 3, 3, 2, 7,      // bottom
//4, 7, 6, 6, 5, 4 };    // back

int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;

Cube::Cube()
{
	_rotation = 0.0f;
	_rotationSpeed = rand() % 100;
	
	_position = new Vector3();
	_position->x = rand() % 400 - 200;
	_position->y = rand() % 400 - 200;
	_position->z = rand() % 400 - 200;
	
}

Cube::~Cube()
{

}

void Cube::Update()
{
	_rotation += _rotationSpeed;	

	_position->z -= 10.0f;

	if (_position->z < -300.0f)
	{
		_position->z = 200.0f;
	}

}

void Cube::Draw()
{

	glPushMatrix();
	glTranslatef(_position->x, _position->y, _position->z);
	glRotatef(_rotation, rand() % 10, rand() % 10, rand() % 10);
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < 36; i++)
	{
		glColor3f(indexedColors[indices[i]].r, indexedColors[indices[i]].g, indexedColors[indices[i]].b);
		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);
	}
	
	glEnd();
	glPopMatrix();
}
bool Cube::Load(char* path)
{
	ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}
	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		//TODO: Use inFile to populate the indexedVertices array
		(indexedVertices[i],inFile);
	}
	
	inFile >> numColours;
	indexedColors = new Vertex[numColours];
	for (int i = 0; i < numVertices; i++)
	{
		//TODO: Load the Colour information from file
		(indexedColors[i], inFile);
	}

	inFile >> numIndices;
	indices = new Vertex[numIndices];
	for (int i = 0; i < numVertices; i++)
	{	
		//TODO: Load the Index information from file
		(indices[i], inFile);
	}

	inFile.close();
	return true;
}