
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "../Include/C3DModel_STL_Ascii.h"
using namespace std;


C3DModel_STL_Ascii::C3DModel_STL_Ascii()
	:m_Vertex(nullptr),
	m_Normals(nullptr),
	m_UVcoords(nullptr)
{

}


C3DModel_STL_Ascii::~C3DModel_STL_Ascii()
{
	reset();
}

bool C3DModel_STL_Ascii::loadFromFile(const char * const filename)
{
	bool readFileOk = false;

	// Free any previous resources
	reset();

	// First pass is to count the number of vertices, normals, UVs, faces
	readFileOk = openFile(filename);

	// Display count
	cout << "Finished reading 3D model" << endl;
	cout << "Vertices: " << m_numVertices << endl;
	cout << "Normals: " << m_numNormals << endl;
	cout << "UVCoords: " << m_numUVCoords << endl;
	cout << "Faces: " << m_numFaces << endl;

	if (readFileOk)
	{
		// Check for MAX number of faces
		if (m_numVertices >= 65535 || m_numNormals >= 65535 || m_numUVCoords >= 65535)
		{
			cout << "Error: object cannot have more than 65535 vertices" << endl;
			cout << "Object attempted to load has: " << m_numVertices << " vertices" << endl;
			return false;
		}

		if (readFileOk)
		{
			m_Initialized = true;
		}
	}
	else
	{
		cout << "Error ocurred while reading 3D model." << endl;
	}

	return readFileOk;
}
void C3DModel_STL_Ascii::reset()
{
	if (m_vertexIndices != NULL)
	{
		cout << "deleting vertex indices" << endl;
		delete[] m_vertexIndices;
		m_vertexIndices = NULL;
	}
	if (m_normalIndices != NULL)
	{
		cout << "deleting normal indices" << endl;
		delete[] m_normalIndices;
		m_normalIndices = NULL;
	}
	if (m_UVindices != NULL)
	{
		cout << "deleting UV indices" << endl;
		delete[] m_UVindices;
		m_UVindices = NULL;
	}
	if (m_Vertex != NULL)
	{
		cout << "deleting vertices" << endl;
		delete[] m_Vertex;
		m_Vertex = NULL;
	}
	if (m_verticesRaw != NULL)
	{
		cout << "deleting vertices (float)" << endl;
		delete[] m_verticesRaw;
		m_verticesRaw = NULL;
	}
	if (m_Normals != NULL)
	{
		cout << "deleting normals" << endl;
		delete[] m_Normals;
		m_Normals = NULL;
	}
	if (m_normalsRaw != NULL)
	{
		cout << "deleting normals (float)" << endl;
		delete[] m_normalsRaw;
		m_normalsRaw = NULL;
	}
	if (m_UVcoords != NULL)
	{
		cout << "deleting UV coords" << endl;
		delete[] m_UVcoords;
		m_UVcoords = NULL;
	}
	if (m_uvCoordsRaw != NULL)
	{
		cout << "deleting uvCoords (float)" << endl;
		delete[] m_uvCoordsRaw;
		m_uvCoordsRaw = NULL;
	}

	m_numVertices = 0;
	m_numNormals = 0;
	m_numUVCoords = 0;
	m_numFaces = 0;

	m_Initialized = false;

	m_graphicsMemoryObjectId = 0;
	m_shaderProgramId = 0;
}

bool C3DModel_STL_Ascii::openFile(const char * const filename)
{
	ifstream file;
	string textLine;
	string token;
	char normalDelim = 'l';
	char vertexDelim = 'x';
	int faces = 0;
	
	//Open the file 
	file.open(filename, ios::in);            


	if (file.fail())
	{
		cout << "no se pudo cargar el archivo" << endl;
		return false;

	}
	
	//First pass to count the faces
	while (!file.eof())
	{
		std::getline(file, textLine);
		if (textLine[0] == 'f')
		{
			faces++;
		}
	}
	
	//Allocate memory 
	m_numFaces = faces;
	m_numNormals = m_numFaces;
	m_numVertices = m_numFaces * 3;
	m_numUVCoords = m_numFaces * 3;

	m_Vertex = new CVector3[m_numVertices];
	m_Normals = new CVector3[m_numNormals];
	m_UVcoords = new CVector3[m_numUVCoords];

	//Raw
	m_verticesRaw = new float[m_numVertices * 3]; 
	m_normalsRaw = new float[m_numFaces * 3];
	m_uvCoordsRaw = new float[m_numUVCoords * 2];

	//Index
	m_vertexIndices = new unsigned short[m_numVertices];
	m_normalIndices = new unsigned short[m_numVertices];
	m_UVindices = new unsigned short[m_numVertices];

	

	file.clear();
	file.seekg(0, ios::beg);

	int indiceNormals = 0;
	int indiceVertex = 0;
	int indiceUVs = 0;
	int vertCount = 0;
	int faceCount = 0;

	//Second pass, Parser.
	while (!file.eof())
	{
		std::getline(file, textLine);

		//Normals
		if (textLine[0] == 'f')
		{
			istringstream ss(textLine);
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');
			float x = stof(token);
			m_normalsRaw[indiceNormals] = x;
			m_normalIndices[indiceNormals++] = faceCount;

			std::getline(ss, token, ' ');
			float y = stof(token);
			m_normalsRaw[indiceNormals] = y;
			m_normalIndices[indiceNormals++] = faceCount;

			std::getline(ss, token, ' ');
			float z = stof(token);
			m_normalsRaw[indiceNormals] = z;
			m_normalIndices[indiceNormals++] = faceCount;

			m_Normals[faceCount++].setValues(x, y, z);
		}

		//Vertex
		else if (textLine[4] == 'v')
		{
			istringstream ss(textLine);
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');
			std::getline(ss, token, ' ');

			float x = stof(token);
			m_verticesRaw[indiceVertex++] = x;

			std::getline(ss, token, ' ');
			float y = stof(token);
			m_verticesRaw[indiceVertex++] = y;

			std::getline(ss, token, ' ');
			float z = stof(token);
			m_verticesRaw[indiceVertex++] = z;

			m_uvCoordsRaw[indiceUVs++] = 0.0;
			m_uvCoordsRaw[indiceUVs++] = 0.0;

			m_UVindices[vertCount] = vertCount;
			m_vertexIndices[vertCount] = vertCount;

			m_UVcoords[vertCount].setValues(0.0, 0.0, 0.0);
			m_Vertex[vertCount++].setValues(x, y, z);
		}
	}


	//memcpy(m_uvCoordsRaw, m_verticesRaw, sizeof(float) * m_numVertices * 3);
	//memcpy(m_UVcoords, m_Vertex, sizeof(CVector3) * m_numVertices);
	//memcpy(m_UVindices, m_vertexIndices, sizeof(unsigned short) * m_numVertices);

	return true;
}
