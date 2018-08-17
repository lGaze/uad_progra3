#include "..\Include\CWorld.h"
#include "..\Include\Globals.h"
#include "..\Include\LoadTGA.h"

CWorld::CWorld()
{
	Grid = new CHexGrid();
}

CWorld::~CWorld()
{
}

bool CWorld::initialize(COpenGLRenderer* renderer)
{
	this->renderer = renderer;
	initializeTexture();
	GLfloat vertexPositions[] =
	{
		2.5f,0.0f,-4.3f,
		5.0f,0.0f,0.0f,
		2.5f,0.0f,4.3f,
	  - 2.5f,0.0f,4.3f,
	  - 5.0f,0.0f,0.0f,
	  - 2.5f,0.0f,-4.3f
	};

	GLfloat vertexUVs[] =
	{
		2.5,-4.3,
		5,0,
		2.5,4.3,
	  - 2.5,4.3,
	  - 5,0,
	  - 2.5,-4.3
	};

	GLfloat normals[] =
	{
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f
	};

	unsigned short indices[] =
	{
		2,1,0,
		3,5,4,
		3,0,5,
		2,0,3
	};

	unsigned short normlindices[] =
	{
		0,0,0,0,0,0,0,0,0,0,0,0
	};

	unsigned short UVcoords[] =
	{
		2,1,0,
		3,5,4,
		3,0,5,
		2,0,3
	};
		

	renderer->allocateGraphicsMemoryForObject(&ShaderProgramID, 
		                                      Grid->getVaoIDtex(),
		                                      vertexPositions, 
		                                      6, 
											  normals,
											  1,
		                                      vertexUVs, 
											  6,
											  indices,
											  12,
											  normlindices,
											  12,
											  UVcoords,
											  12);

	return Grid->initialize(renderer);
	
}
	


void CWorld::render(CVector3 CamPosition)
{
	float c[3] = { 1.0f, 1.0f, 1.0f };
	float b[3] = { 0.0f, 0.0f, 0.0f };
	
	
	CVector3 CamPosition2 = CamPosition;
	CamPosition2.Y -= 0.4f;

	MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CamPosition);
	MathHelper::Matrix4 modelMatrix2 = MathHelper::ModelMatrix((float)0, CamPosition2);


	//renderer->renderWireframeObject(
	//	Grid->getWireframeID(),
	//	Grid->getArrayID(),
	//	4 * GRID_SIZE*GRID_SIZE,
	//	c,
	//	&modelMatrix
	//);


	renderer->renderObject(
		&ShaderProgramID,
		Grid->getVaoIDtex(),
		&m_TextureID,
		4 * GRID_SIZE*GRID_SIZE,
		b,
		&modelMatrix2,
		COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
		true
	);
	
}


bool CWorld::initializeTexture()
{
	m_TextureID = 0;
	std::wstring wresourceFilenameTexture;
	std::string resourceFilenameTexture;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(PASTO_TEXTURE, wresourceFilenameTexture, resourceFilenameTexture))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << PASTO_TEXTURE << endl;
		return false;
	}

	// Initialize the texture
	if (!loadTexture(resourceFilenameTexture.c_str(), &m_TextureID))
	{
		return false;
	}

	// Initialize a Minecraft cube
	initializeHexTexture();

	return true;
}

/* Read texture file and generate an OpenGL texture object */
bool CWorld::loadTexture(const char *filename, unsigned int *newTextureID)
{
	TGAFILE tgaFile;
	tgaFile.imageData = nullptr;

	if (filename == nullptr || newTextureID == nullptr)
	{
		return false;
	}

	*newTextureID = 0;

	if (LoadTGAFile(filename, &tgaFile))
	{
		if (tgaFile.imageData == nullptr ||
			tgaFile.imageHeight < 0 ||
			tgaFile.imageWidth < 0)
		{
			if (tgaFile.imageData != nullptr)
			{
				delete[] tgaFile.imageData;
			}

			return false;
		}

		// Create a texture object for the menu, and copy the texture data to graphics memory
		if (!renderer->createTextureObject(
			newTextureID,
			tgaFile.imageData,
			tgaFile.imageWidth,
			tgaFile.imageHeight
		))
		{
			return false;
		}

		// Texture data is stored in graphics memory now, we don't need this copy anymore
		if (tgaFile.imageData != nullptr)
		{
			delete[] tgaFile.imageData;
		}
	}
	else
	{
		// Free texture data
		if (tgaFile.imageData != nullptr)
		{
			delete[] tgaFile.imageData;
		}

		return false;
	}

	return true;
}

void CWorld::initializeHexTexture()
{
	ShaderProgramID = 0;
	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_TEXTURED_3D_OBJECT, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_TEXTURED_3D_OBJECT, wresourceFilenameFS, resourceFilenameFS))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << VERTEX_SHADER_TEXTURED_3D_OBJECT << endl;
		cout << "  " << FRAGMENT_SHADER_TEXTURED_3D_OBJECT << endl;
		return;
	}
	if (renderer->createShaderProgram(
		&ShaderProgramID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str()
	))
	{

		

		
		
	}

}



