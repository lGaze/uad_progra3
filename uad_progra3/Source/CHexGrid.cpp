#include "..\Include\CHexGrid.h"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

CHexGrid::CHexGrid() :
	First_CenterX(0),
	First_CenterY(0),
	WireframeID(0),
	m_ShaderProgramId(0),
	Vertex(0),
	VertexTexturas(0),
	ArrayID(0),
	m_textureId(0)

{

}

CHexGrid::~CHexGrid()
{
}

void CHexGrid::buildGrid(float cellsize)
{
	int vertIterator = 0;
	int vertIndexIterator = 0;
	float radio = sqrt(3)*(cellsize / 2);
	float Centro_X, Centro_Y;
	int singleHexIndices[] = 
	{
		2,1,0,
		3,5,4,
		3,0,5,
		2,0,3

		/*0,2,4,1,5,3,
		0,1,5,1,2,3,
		3,4,5*/  //el diablo

	};
	
	m_pCeldas[0][0] = new CHexCell(First_CenterX, First_CenterY);
	//m_pCeldasTex[0][0] = new CHexCell(First_CenterX, First_CenterY);

	Vertex = new float [GRID_SIZE * GRID_SIZE * 3 * 6]; //vraw
	//VertexTexturas =  new float[GRID_SIZE * GRID_SIZE * 3 * 6]; //vraw

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
	#ifdef POINTY
			Centro_X = First_CenterX + (i % 2)*radio + 2 * j*radio;
			Centro_Y = First_CenterY + i * ((3 * cellsize) / 2);
			
	#else
			Centro_X = First_CenterX + j*((3 * cellsize) / 2);
			Centro_Y = First_CenterY + (j % 2)*radio + 2 * i*radio;
			

	#endif
			m_pCeldas[i][j] = new CHexCell(Centro_X, Centro_Y);
			//m_pCeldasTex[i][j] = new CHexCell(Centro_X, Centro_Y);

			m_pCeldas[i][j]->CalculateVert(radio, cellsize);
			//m_pCeldasTex[i][j]->CalculateVerText(radio, cellsize);

			for (int k = 0; k < 6; k++)
			{
				Vertex[vertIterator++] = m_pCeldas[i][j]->Vert[k].getX();
				//VertexTexturas[vertIterator++] = m_pCeldasTex[i][j]->VertTex[k].getX();

				Vertex[vertIterator++] = m_pCeldas[i][j]->Vert[k].getY();
				//VertexTexturas[vertIterator++] = m_pCeldasTex[i][j]->VertTex[k].getY();

				Vertex[vertIterator++] = m_pCeldas[i][j]->Vert[k].getZ();
				//VertexTexturas[vertIterator++] = m_pCeldasTex[i][j]->VertTex[k].getZ();
				
			}

			for (int l = 0; l < 4*3; l++)
			{
				vindex[vertIndexIterator++] = 
					(i * GRID_SIZE * 6 + j * 6 + singleHexIndices[l]);
				/*vindexTex[vertIndexIterator++] =
					(i * GRID_SIZE * 6 + j * 6 + singleHexIndices[l]);*/
			}				
		}
	}
}

bool CHexGrid::initialize(COpenGLRenderer * render)
{
	buildGrid(5.0);
	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	std::wstring wresourceFilenameVStexture;
	std::wstring wresourceFilenameFStexture;
	std::string resourceFilenameVStexture;
	std::string resourceFilenameFStexture;
	
	
	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_WIREFRAME, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_WIREFRAME, wresourceFilenameFS, resourceFilenameFS))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << VERTEX_SHADER_WIREFRAME << endl;
		cout << "  " << FRAGMENT_SHADER_WIREFRAME << endl;
		return false;
	}

	/*if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_TEXTURED_3D_OBJECT, wresourceFilenameVStexture, resourceFilenameVStexture) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_TEXTURED_3D_OBJECT, wresourceFilenameFStexture, resourceFilenameFStexture))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << VERTEX_SHADER_TEXTURED_3D_OBJECT << endl;
		cout << "  " << FRAGMENT_SHADER_TEXTURED_3D_OBJECT << endl;
		return false;
	}*/

	render->createShaderProgram(&WireframeID, resourceFilenameVS.c_str(), resourceFilenameFS.c_str());
	//render->createShaderProgram(&m_ShaderProgramId,resourceFilenameVStexture.c_str(), resourceFilenameFStexture.c_str());

	//Allocate Memory
	render->allocateGraphicsMemoryForObject(&WireframeID, &ArrayID, Vertex, GRID_SIZE*GRID_SIZE * 6, vindex, GRID_SIZE*GRID_SIZE * 4 * 3);
	//render->allocateGraphicsMemoryForObject(&m_ShaderProgramId, &m_textureId, VertexTexturas, GRID_SIZE*GRID_SIZE * 6, vindexTex, GRID_SIZE*GRID_SIZE * 4 * 3);

	return true;
}

unsigned int* CHexGrid::getWireframeID()
{
	return &WireframeID;
}

unsigned int* CHexGrid::getArrayID()
{
	return &ArrayID;;
}

unsigned int * CHexGrid::getWireframeIDtex()
{
	return &m_ShaderProgramId;
}

unsigned int * CHexGrid::getArrayIDtex()
{
	return &m_textureId;									

}

void CHexGrid::reset()
{
}
