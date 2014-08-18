//This is the header file for the Point3, Vector3, VertexID, Face, 
//and Mesh classes.

#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;
#include <gl/glut.h>

//This is the definition of the point class
class Point2
{
public:
	//the x, and y coordinates of the 2D point
	float x, y;

	//constructors for the Point3 class
	Point2 (float xx, float yy){x = xx; y = yy;}
	Point2() {x = y = 0;}

	//set the point either by passing x, y, & z or by passing a point
	void set (float dx, float dy){x = dx; y = dy;}
	void set (Point2& p){x = p.x; y = p.y;}

	
};

class Point3
{
public:
	//the x, y, and z coordinates of the point
	float x, y, z;

	//constructors for the Point3 class
	Point3 (float xx, float yy, float zz){x = xx; y = yy; z = zz;}
	Point3() {x = y = z = 0;}

	//set the point either by passing x, y, & z or by passing a point
	void set (float dx, float dy, float dz){x = dx; y = dy; z = dz;}
	void set (Point3& p){x = p.x; y = p.y; z = p.z;}

	
};

//################# VertexID ###################
class VertexID{
	public:
		int vertIndex;		// index of this vert in the vertex list
};


//#################### Face ##################
class Face{
  public:
		int nVerts;			// number of vertices in this face

		VertexID * vert;	// the list of vertex
		
		Face(){nVerts = 0; vert = NULL;}	// constructor
		~Face(){delete[] vert; nVerts = 0;} // destructor
};

//###################### Mesh #######################
class Mesh{
   private:
		int numVerts;		// number of vertices in the mesh
		Point3* pt;			// array of 3D vertices
		int numFaces; 		// number of faces in the mesh
		Face* face;			// array of face data
		// ... others to be added later
   public:
		Mesh(); 			// constructor
		~Mesh();			// destructor

		// to read in a filed mesh
		int readmesh(char * fileName);
		int generatemesh(char * basefileName, char * meshfileName, int H);
		void draw();		// use OpenGL to draw this mesh
		
		//.. others ..
};	
