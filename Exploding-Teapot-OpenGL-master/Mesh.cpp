#include "Mesh.h"
  
#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <string>
   
using namespace std;
 
 
Mesh::Mesh()
{
    shape = new Shape();
 
}
 
 
Mesh::Mesh(Shape *shape2)
{
    shape = shape2;
}
 
 
 
Mesh::~Mesh()
{
 
}
 
 
 
// Make the mesh: vertex list, face list, normal list.
void Mesh::makeSurfaceMesh()
{

    readfile("cube.obj");
	
}
 
 
 
void Mesh::draw() // use openGL to draw this mesh
{
 
    for(unsigned int f = 0;f <face.size();f++) // for each face
    {
        glColor3f(1,1,1);
        if(!shape->getWire())  // draw in wireframe or solid mode?
        {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glBegin(GL_POLYGON);
        }
        else
        {
            glDisable(GL_LIGHTING);
            glBegin(GL_LINE_LOOP);
        }
        for(int v=0;v<face[f].nVerts;v++) // for each vertex in this face
        {   
            int in = face[f].vert[v].normIndex; // index of this normal
            int iv = face[f].vert[v].vertIndex; // index of this vertex
            if(shape->getSmooth())
                glNormal3f(norm[in].norm.x, norm[in].norm.y, norm[in].norm.z);
            else
                glNormal3f(face[f].faceNorm.norm.x, face[f].faceNorm.norm.y, face[f].faceNorm.norm.z);
 
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
         
        }
        glEnd();
 
    }

	//draw normals
	if(shape->getNormals())
	{
		glDisable(GL_LIGHTING);
		glColor3f(1,0,0);
		glBegin(GL_LINES);

		//if smooth shading we draw normals from vertex
		if(1)
		{
			for(unsigned int i =0; i<norm.size(); i++)
			{
				glVertex3d(pt.at(i).x, pt.at(i).y, pt.at(i).z); 

				glVertex3d(pt.at(i).x + norm.at(i).norm.x*.2/shape->getScale() , 
					pt.at(i).y + norm.at(i).norm.y*.2/shape->getScale(), 
					pt.at(i).z+ norm.at(i).norm.z*.2/shape->getScale());
				
				//cout<<"line from ("<<pt.at(i).x<<","<<pt.at(i).y<<","<<pt.at(i).z<<") to ("<<pt.at(i).x + norm.at(i).norm.x*.2/shape->getScale()<<","<<pt.at(i).y + norm.at(i).norm.y*.2/shape->getScale()<<","<<pt.at(i).z+ norm.at(i).norm.z*.2/shape->getScale()<<").\n";
			}
		}
		
		glEnd();
	}
	if (shape->getBoom())
	{
		glDisable(GL_LIGHTING);
		glColor3f(1, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();
	}
 
}
 
 
// Calculate Newell Face Normal 
void Mesh::calcNewell()
{
    for(unsigned int i = 0; i < face.size(); i++) {//every face
        face[i].faceNorm.norm.x = 0;
        face[i].faceNorm.norm.y = 0;
        face[i].faceNorm.norm.z = 0;
        for(int j = 0; j < face[i].nVerts; j++) { //loops x, y, z
            // store in face[i].facenorm.norm;
            // set current and next
            Vector3d current = pt[face[i].vert[j].vertIndex];
            Vector3d next;
            if(j == face[i].nVerts - 1) {
                next = pt[face[i].vert[0].vertIndex];
            } else {
                next = pt[face[i].vert[j + 1].vertIndex];
            }
            face[i].faceNorm.norm.x += (current.y - next.y * current.z + next.z);
            face[i].faceNorm.norm.y += (current.z - next.z * current.x + next.x);
            face[i].faceNorm.norm.z += (current.x - next.x * current.y + next.y);
        }
		//cout<<"face["<<i<<"]: Normal = "<<face[i].faceNorm.norm.x<<", "<<face[i].faceNorm.norm.y<<", "<<face[i].faceNorm.norm.z<<".\n";
    }

}
 
 
//Calculate Normal at Vertices
void Mesh::calcGourand()
{
     
    for(unsigned int i = 0; i < face.size(); i++) {
        for(int j = 0; j < face[i].nVerts; j++) {
            norm[face[i].vert[j].normIndex].norm.x = 0;
            norm[face[i].vert[j].normIndex].norm.y = 0;
            norm[face[i].vert[j].normIndex].norm.z = 0;
        }
    }
 
    for(unsigned int i = 0; i < face.size(); i++) {
        for(int j = 0; j < face[i].nVerts; j++) {
            norm[face[i].vert[j].normIndex].norm = face[i].faceNorm.norm;
        }
    }
 
    for(int i = 0; i < numNorms; i++) {
        norm[i].norm.normalize();
    }
}
 
 
void Mesh::readfile(string filename)
{
    // read a mesh from a Wavefront OBJ object model file.
    // fill in the content of the three lists
 
    ifstream in(filename.c_str());
    string s;
    double x,y,z;
    int vindex;
 
    Vector3d v;
    Face f;
    VertexID vid;
 
    norm.resize(0);
    face.resize(0);
    pt.resize(0);
 
    in >> s;
    while(1)
    {
        if(s=="v")//vertex
        {
            in >> x >> y >> z;
            v.set(x,y,z);
            pt.push_back(v);
            if(!(in >> s))
                break;
 
        }
        else if(s=="f")//face
        {
 
            while((in >> s) && s[0]>='0' && s[0]<='9')
            {
     
                vindex = atoi(s.c_str());
     
                vid.vertIndex = vid.normIndex = vindex-1;
                f.vert.push_back(vid);
                f.nVerts=f.vert.size();
            }
            face.push_back(f);
            f.vert.resize(0);
        }
        else
        {
            getline(in,s);
            if(!(in>>s))
                break;
        }
    } 
 
    norm.resize(pt.size());
 
    numVerts = pt.size();
    numFaces = face.size();
    numNorms = norm.size();
 
    // call the functions to calculate face normals and vertex normals
    calcNewell();
    calcGourand();
 
 
    in.close();
}
