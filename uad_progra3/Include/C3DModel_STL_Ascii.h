#pragma once
#include "C3DModel.h"
#include "CVector3.h"

class C3DModel_STL_Ascii : public C3DModel
{
public:

	C3DModel_STL_Ascii();
	~C3DModel_STL_Ascii();

	
private:
	
	bool openFile(const char * const filename);
	CVector3 * m_Vertex;
	CVector3 * m_Normals;
	CVector3 * m_UVcoords;
	
protected:
	void reset();
	bool loadFromFile(const char * const filename);
};

