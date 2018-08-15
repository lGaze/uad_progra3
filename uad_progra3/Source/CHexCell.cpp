#include "..\Include\CHexCell.h"
#include <iostream>
using namespace std;

CHexCell::CHexCell(float Centro_X, float Centro_Y)
{
	centro_X = Centro_X;
	centro_Y = Centro_Y;
}

CHexCell::~CHexCell()
{
}

void CHexCell::CalculateVert(float radio,float cellsize)
{

#ifdef POINTY

	//Point1
	float Point1_x = centro_X;
	float Point1_y = centro_Y - cellsize;
	Vert[0].setValues(Point1_x, 0.1, Point1_y);
	//cout << Point1_x << "," << Point1_y << endl;
	//Point2
	float Point2_x = centro_X + radio;
	float Point2_y = centro_Y - (cellsize / 2);
	Vert[1].setValues(Point2_x, 0.1, Point2_y);
	//cout << Point2_x << "," << Point2_y << endl;
	//Point3
	float Point3_x = centro_X + radio;
	float Point3_y = centro_Y + (cellsize / 2);
	Vert[2].setValues(Point3_x, 0.1, Point3_y);
	//cout << Point3_x << "," << Point3_y << endl;
	//Point4
	float Point4_x = centro_X;
	float Point4_y = centro_Y + cellsize;
	Vert[3].setValues(Point4_x, 0.1, Point4_y);
	//cout << Point4_x << "," << Point4_y << endl;
	//Point5
	float Point5_x = centro_X - radio;
	float Point5_y = centro_Y + (cellsize/2);
	Vert[4].setValues(Point5_x, 0.1, Point5_y);
	//cout << Point5_x << "," << Point5_y << endl;
	//Point6
	float Point6_x = centro_X - radio;
	float Point6_y = centro_Y - (cellsize/2);
	Vert[5].setValues(Point6_x, 0.1, Point6_y);
	//cout << Point6_x << "," << Point6_y << endl;
#else

 //Point1
	float Point1_x = centro_X +(cellsize/2);
	float Point1_y = centro_Y - radio;
	Vert[0].setValues(Point1_x, 0.1, Point1_y);
	//cout << Point1_x << "," << Point1_y << endl;
	//Point2
	float Point2_x = centro_X + cellsize;
	float Point2_y = centro_Y;
	Vert[1].setValues(Point2_x, 0.1, Point2_y);
	//cout << Point2_x << "," << Point2_y << endl;
	//Point3
	float Point3_x = centro_X + (cellsize / 2);
	float Point3_y = centro_Y + radio;
	Vert[2].setValues(Point3_x, 0.1, Point3_y);
	//cout << Point3_x << "," << Point3_y << endl;
	//Point4
	float Point4_x = centro_X - (cellsize / 2);
	float Point4_y = centro_Y + radio;
	Vert[3].setValues(Point4_x, 0.1, Point4_y);
	//cout << Point4_x << "," << Point4_y << endl;
	//Point5
	float Point5_x = centro_X - cellsize;
	float Point5_y = centro_Y;
	Vert[4].setValues(Point5_x, 0.1, Point5_y);
	//cout << Point5_x << "," << Point5_y << endl;
	//Point6
	float Point6_x = centro_X - (cellsize / 2);
	float Point6_y = centro_Y - radio;
	Vert[5].setValues(Point6_x, 0.1, Point6_y);
	//cout << Point6_x << "," << Point6_y << endl;

#endif

}

/*void CHexCell::CalculateVerText(float radio, float cellsize)
{


#ifdef POINTY

	//Point1
	float Point1_x = centro_X;
	float Point1_y = centro_Y - cellsize;
	VertTex[0].setValues(Point1_x, 0, Point1_y);
	//cout << Point1_x << "," << Point1_y << endl;
	//Point2
	float Point2_x = centro_X + radio;
	float Point2_y = centro_Y - (cellsize / 2);
	VertTex[1].setValues(Point2_x, 0, Point2_y);
	//cout << Point2_x << "," << Point2_y << endl;
	//Point3
	float Point3_x = centro_X + radio;
	float Point3_y = centro_Y + (cellsize / 2);
	VertTex[2].setValues(Point3_x, 0, Point3_y);
	//cout << Point3_x << "," << Point3_y << endl;
	//Point4
	float Point4_x = centro_X;
	float Point4_y = centro_Y + cellsize;
	VertTex[3].setValues(Point4_x, 0, Point4_y);
	//cout << Point4_x << "," << Point4_y << endl;
	//Point5
	float Point5_x = centro_X - radio;
	float Point5_y = centro_Y + (cellsize / 2);
	VertTex[4].setValues(Point5_x, 0, Point5_y);
	//cout << Point5_x << "," << Point5_y << endl;
	//Point6
	float Point6_x = centro_X - radio;
	float Point6_y = centro_Y - (cellsize / 2);
	VertTex[5].setValues(Point6_x, 0, Point6_y);
	//cout << Point6_x << "," << Point6_y << endl;
#else

	//Point1
	float Point1_x = centro_X + (cellsize / 2);
	float Point1_y = centro_Y - radio;
	VertTex[0].setValues(Point1_x, 0, Point1_y);
	//cout << Point1_x << "," << Point1_y << endl;
	//Point2
	float Point2_x = centro_X + cellsize;
	float Point2_y = centro_Y;
	VertTex[1].setValues(Point2_x, 0, Point2_y);
	//cout << Point2_x << "," << Point2_y << endl;
	//Point3
	float Point3_x = centro_X + (cellsize / 2);
	float Point3_y = centro_Y + radio;
	VertTex[2].setValues(Point3_x, 0, Point3_y);
	//cout << Point3_x << "," << Point3_y << endl;
	//Point4
	float Point4_x = centro_X - (cellsize / 2);
	float Point4_y = centro_Y + radio;
	VertTex[3].setValues(Point4_x, 0, Point4_y);
	//cout << Point4_x << "," << Point4_y << endl;
	//Point5
	float Point5_x = centro_X - cellsize;
	float Point5_y = centro_Y;
	VertTex[4].setValues(Point5_x, 0, Point5_y);
	//cout << Point5_x << "," << Point5_y << endl;
	//Point6
	float Point6_x = centro_X - (cellsize / 2);
	float Point6_y = centro_Y - radio;
	VertTex[5].setValues(Point6_x, 0, Point6_y);
	//cout << Point6_x << "," << Point6_y << endl;

#endif

}*/



