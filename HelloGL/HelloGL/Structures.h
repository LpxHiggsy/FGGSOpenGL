#pragma once
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include <vector>
using namespace std;

class SceneObject;

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};
struct Color
{
	GLfloat r, g, b;
};
struct Vertex
{
	GLfloat x, y, z;
};
struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	int VertexCount, NormalCount, IndexCount;
};
struct TexCoord
{
	GLfloat u, v;
};
struct TexturedMesh
{
	Mesh* Mesh;
	TexCoord* TexCoords;

	int TexCoordCount;
};
struct Vector4
{
	float x, y, z, w;
};
struct Lighting
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
};
struct Material
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
	GLfloat shininess;
};
struct listnode
{
	SceneObject* data;
	listnode* next;
};
struct ObjMesh
{
	vector<string> MeshNames;
	vector<vector<GLushort>> MeshIndices;
	vector<Vertex> Vertices;
	vector<Vector3> Normals;
	vector<TexCoord> TexCoords;
};

