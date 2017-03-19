#include "Shape.h"

 
 
Shape::Shape()
{
	//values customized to teapot
	tx = -.98;
	ty = -.18;
	tz = -0.5;
	rx = 0.2;
	ry = 19;
	rz = 0.4;
	scale = .1;
	smooth = false;  
	normals = false;  
	wire =  true;	
	
	
	
	mesh = new Mesh(this);
	mesh->makeSurfaceMesh();  // read in a mesh, make a tesselated mesh, etc.
}


Shape::~Shape(){

	delete mesh;
}

Shape& Shape::operator=(const Shape& rhs)
{
	tx = rhs.tx;
	ty = rhs.ty;
	tz = rhs.tz;
	rx = rhs.rx;
	ry = rhs.ry;
	rz = rhs.rz;
	scale = rhs.scale;
	smooth = rhs.smooth;
	normals = rhs.normals;
	boom = rhs.boom;
	wire = rhs.wire;
	return * this;
}


void Shape::draw()
{
	mesh->draw();

}

void Shape::readfile(string filename)
{
	mesh->readfile(filename);
}

