#ifndef MESH_H
#define MESH_H
  
  
#include "Face.h"
#include "Vector3d.h"
#include <vector>
 
 
class Shape;
 
#include "Shape.h"
#include "Normal.h"
 
using namespace std;
 
#define PI 3.1415
// ############### Mesh ######################
class Mesh{
   public:
    int numVerts;       // number of vertices in the mesh
    int numNorms;       // number of normal vertices for the mesh
    int numFaces;       // number of faces in the mesh
 
//  Vector3d *pt;       
//  Vector3d *norm;     
//  Face *face;         
    vector <Vector3d> pt;      // list of 3D vertices
    vector <Normal> norm;    // list of normals
    vector <Face> face;       // list of faces
 
    Shape *shape;
                        // others to be added later
   
    Mesh();         // constructor
    Mesh(Shape *shape); // constructor
    ~Mesh();            // destructor
    void draw();
    void makeSurfaceMesh();
    void calcNewell();
    void calcGourand();
 
    void readfile(string filename);
};
 
#endif