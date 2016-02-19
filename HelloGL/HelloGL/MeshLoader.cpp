#include "MeshLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	
	void LoadVertex(vector<Vertex>& vertices, string& LastLine);
	void LoadNormal(vector<Vector3>& normals, string& LastLine);
	void LoadTexCoord(vector<TexCoord>& texCoords, string& LastLine);
	void LoadIndex(vector<GLushort>& indices, string& LastLine);
	void ConvertToMesh(ObjMesh& mesh, vector<Vertex>& vertices, vector<Vector3>& normals, vector<TexCoord>& texCoords, vector<vector<GLushort>>& indices);


	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		//TODO: LOAD COLOURS
		inFile >> mesh.NormalCount;
		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		//TODO: Load Indices
		inFile >> mesh.IndexCount;
		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE
		LoadVertices(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}
	void LoadTexCoords(ifstream& inFile, TexturedMesh& mesh)
	{
		//TODO: LOAD COLOURS
		inFile >> mesh.TexCoordCount;
		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}
	TexturedMesh* MeshLoader::LoadTextured(char* path)
	{
		TexturedMesh* mesh = new TexturedMesh();
		mesh->Mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE
		LoadVertices(inFile, *mesh->Mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh->Mesh);
		LoadIndices(inFile, *mesh->Mesh);
		

		return mesh;
	}

	void ConvertToMesh(ObjMesh& mesh, vector<Vertex>& vertices, vector<Vector3>& normals, vector<TexCoord>& texCoords, vector<vector<GLushort>>& indices)
	{
		int indexCount = 0;

		for (int i = 0; i < indices.size(); i++)
		{
			vector<GLushort> currentIndices;

			for (int j = 0; j < indices[i].size(); j = j + 3)
			{
				currentIndices.push_back(indexCount);

				mesh.Vertices.push_back(vertices[indices[i][j]]);
				mesh.TexCoords.push_back(texCoords[indices[i][j + 1]]);
				mesh.Normals.push_back(normals[indices[i][j + 2]]);

				indexCount++;
			}

			mesh.MeshIndices.push_back(currentIndices);
		}
	}

	void LoadVertex(vector<Vertex>& vertices, string& LastLine)
	{
		stringstream strstm;
		string tempString;

		Vertex v;

		strstm.str("");
		strstm.clear();
		strstm << LastLine;

		strstm >> tempString;
		strstm >> v.x;
		strstm >> v.y;
		strstm >> v.z;

		vertices.push_back(v);

	}
	void LoadNormal(vector<Vector3>& normals, string& LastLine)
	{
		stringstream strstm;
		string tempString;

		Vector3 v;

		strstm.str("");
		strstm.clear();
		strstm << LastLine;

		strstm >> tempString;
		strstm >> v.x;
		strstm >> v.y;
		strstm >> v.z;

		normals.push_back(v);

	
	}

	void LoadTexCoord(vector<TexCoord>& texCoord, string& LastLine)
	{
		stringstream strstm;
		string tempString;

		float tempFloat;
		TexCoord tc;

		strstm.str("");
		strstm.clear();
		strstm << LastLine;

		strstm >> tempString;
		strstm >> tc.u;
		strstm >> tc.v;
		strstm >> tempFloat;

		texCoord.push_back(tc);

	}

	void LoadIndex(vector<GLushort>& indices, string& LastLine)
	{
		stringstream strstm;
		string tempString;

		string faces[3];

		strstm.str("");
		strstm.clear();
		strstm << LastLine;

		strstm >> tempString;
		strstm >> faces[0];
		strstm >> faces[1];
		strstm >> faces[2];

		for (int i = 0; i < 3; i++)
		{
			strstm.str("");
			strstm.clear();
			strstm << faces[i];
			getline(strstm, LastLine, '/');
			indices.push_back(stoi(LastLine) - 1);
			getline(strstm, LastLine, '/');
			indices.push_back(stoi(LastLine) - 1);
			getline(strstm, LastLine, '/');
			indices.push_back(stoi(LastLine) - 1);

		}

	}

	ObjMesh* MeshLoader::LoadObj(char* path)
	{
		vector<Vertex> vertices;
		vector<Vector3> normals;
		vector<TexCoord> texCoords;
		vector<vector<GLushort>> currentIndices;

		string line;
		stringstream strstm;
		string tempString;

		ObjMesh* mesh = new ObjMesh();

		ifstream inFile;

		inFile.open(path);
		if (!inFile.good())
		{
			cerr << "Can't open texture file" << path << endl;
		}

		while (!inFile.eof())
		{
			getline(inFile, line);

			if (line.length() > 2)
			{
				switch (line.at(0))
				{
				case 'v':
					switch (line.at(1))
					{
					case' ':
						LoadVertex(vertices, line);
						break;
					case 'n':
						LoadNormal(normals, line);
						break;
					case't':
						LoadTexCoord(texCoords, line);
						break;
					}
					break;
				case 'f':
					LoadIndex(currentIndices.back(), line);
					break;
				case'#':
					strstm.str("");
					strstm.clear();
					strstm << line;

					strstm >> tempString;
					strstm >> tempString;

					if (tempString == "object")
					{
						strstm >> tempString;

						mesh->MeshNames.push_back(tempString);

						vector<GLushort> indices;
						currentIndices.push_back(indices);
					}
					break;
				}
			}
		}

		ConvertToMesh(*mesh, vertices, normals, texCoords, currentIndices);

		return mesh;
	}
}