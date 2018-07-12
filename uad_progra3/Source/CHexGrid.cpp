#include "..\Include\CHexGrid.h"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

CHexGrid::CHexGrid():
	First_CenterX(0),
	First_CenterY(0),
	WireframeID(0), 
	Vertex(0),
	ArrayID(0)
{
}

CHexGrid::~CHexGrid()
{
}

void CHexGrid::buildGrid(float cellsize)
{
	int k = -1;
	float radio = sqrt(3)*(cellsize / 2);
	float Centro_X, Centro_Y;
	
	m_pCeldas[0][0] = new CHexCell(First_CenterX, First_CenterY);

	Vertex = new float [GRID_SIZE * GRID_SIZE * 3 * 6]; //vraw

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{

			Centro_X = First_CenterX + (i % 2)*radio + 2 * j*radio;
			Centro_Y = First_CenterY + i * ((3 * cellsize) / 2);
			m_pCeldas[i][j] = new CHexCell(Centro_X, Centro_Y);
			m_pCeldas[i][j]->CalculateVert(radio,cellsize);

			Vertex[++k] = m_pCeldas[i][j]->Vert[0].getX();
			cout << Vertex[k] <<" , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[0].getY();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[0].getZ();
			cout << Vertex[k] << " ,, ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[1].getX();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[1].getY();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[1].getZ();
			cout << Vertex[k] << " ,,";
			Vertex[++k] = m_pCeldas[i][j]->Vert[2].getX();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[2].getY();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[2].getZ();
			cout << Vertex[k] << " ,, ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[3].getX();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[3].getY();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[3].getZ();
			cout << Vertex[k] << " ,, ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[4].getX();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[4].getY();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[4].getZ();
			cout << Vertex[k] << " ,, ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[5].getX();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[5].getY();
			cout << Vertex[k] << " , ";
			Vertex[++k] = m_pCeldas[i][j]->Vert[5].getZ();
			cout << Vertex[k] << " ,, ";
			
			for (int l = 0; l < 4*3; l++)
			{
				vindex[l++] = (i * GRID_SIZE * 6 + j * 6);
				vindex[l++] = (i * GRID_SIZE * 6 + j * 6 + l + 1);
				vindex[l++] = (i * GRID_SIZE * 6 + j * 6 + l + 2);
			}
							
		}
		
	}
}

void CHexGrid::initialize(COpenGLRenderer * render)
{
	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	
	
	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_WIREFRAME, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_WIREFRAME, wresourceFilenameFS, resourceFilenameFS))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << VERTEX_SHADER_WIREFRAME << endl;
		cout << "  " << FRAGMENT_SHADER_WIREFRAME << endl;
		return;
	}

	render->createShaderProgram(&WireframeID, resourceFilenameVS.c_str(), resourceFilenameFS.c_str());

	//Allocate Memory
	render->allocateGraphicsMemoryForObject(WireframeID, &ArrayID, Vertex, GRID_SIZE*GRID_SIZE * 6, &vindex, GRID_SIZE*GRID_SIZE * 4);
	
}
