//This is the implementation file for the Vector3 and Mesh classes.

#include "mesh.h"

//The default constructor for the mesh class
//sets the number of vertices,  and faces to 0.
Mesh::Mesh() 			
{
	numVerts=0;
	numFaces=0;
	pt=NULL;
	face=NULL;
}

//The Mesh destructor releases all the space
//allocated to the mesh and sets the number
//of vertices, and faces back to 0.
Mesh::~Mesh()			
{
	delete[] pt;
	numVerts=0;
	
	delete[] face;
	numFaces=0;
}

//Draw the mesh.  Each face of the object is drawn
//using a different material property.
void Mesh:: draw() 
{
	//loop through the faces of the object
	for(int f = 0; f < numFaces; f++) 
	{ 
		//draw the face
		

		glBegin(GL_LINE_LOOP);
		  for(int v = 0; v < face[f].nVerts; v++) // for each one..
		  {
			  //find the next vertex
			  int iv =  face[f].vert[v].vertIndex ; // index of this vertex

			  //inform OpenGL of thevertex
			  glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		  }
		glEnd();
		
	}
}

//This function reads face information from a data file.
//The name of the file is passed to the function through 
//the argument list
int Mesh:: readmesh(char * fileName)
{
	//open the file and check for file failure
	fstream infile;
	infile.open(fileName, ios::in);
	if(infile.fail()) return -1; // error - can't open file
	if(infile.eof())  return -1; // error - empty file

	//the file is OK so read the 
	//number of vertices, and faces.
	infile >> numVerts >> numFaces;

	//create arrays to hold the vertices, nomrmals,
	//and faces.
	pt = new Point3[numVerts];
	face = new Face[numFaces];

	//check that enough memory was found:
	if( !pt || !face)return -1; 

	//read the vertices
	for(int p = 0; p < numVerts; p++) 
	{
		infile >> pt[p].x >> pt[p].y >> pt[p].z;
	}


	//read the faces
	for(int f = 0; f < numFaces; f++)
	{
		infile >> face[f].nVerts;
		face[f].vert = new VertexID[face[f].nVerts];
		for(int i = 0; i < face[f].nVerts; i++)
			infile >> face[f].vert[i].vertIndex;
	} 
	return 0; // success
} 




int Mesh:: generatemesh(char * basefileName, char * meshfileName, int H)
{
	int numBaseVertices, numBaseEdges;
	fstream basefile;
	basefile.open(basefileName, ios::in);
	if(basefile.fail()) return -1; // error - can't open file
	if(basefile.eof())  return -1; // error - empty file

	basefile >> numBaseVertices;

	numVerts = numBaseVertices*2;
	numFaces = numBaseVertices +2;

	//open the file 
	fstream meshfile;
	meshfile.open(meshfileName, ios::out);

	meshfile << numVerts << " " << numFaces << endl;
	
	// write the base vertices (x y 0)
	Point2* vertlist = new Point2[numBaseVertices];
	for(int i = 0; i<numBaseVertices; i++){
		basefile >> vertlist[i].x >> vertlist[i].y;
		meshfile << vertlist[i].x << "  " << vertlist[i].y << "  " << 0 << "     ";
	}

	meshfile << endl;

	// write the cap vertices (x y H)
	for(int i = 0; i<numBaseVertices; i++){
		meshfile << vertlist[i].x << "  " << vertlist[i].y << "  " << H << "     ";
	}

	meshfile << endl << endl;

	for(int i=0; i<numBaseVertices; i++){
		meshfile << 4 << endl;
		meshfile << i << " " << numBaseVertices+i << " " << (i+1)%numBaseVertices + numBaseVertices << " " << (i+1)%numBaseVertices << endl;
		meshfile << endl;
	}

	//base
	meshfile << numBaseVertices << endl;
	for(int i=0; i<numBaseVertices; i++){
		meshfile << i << " ";
	}

	meshfile << endl << endl;

	//cap face
	//meshfile << numBaseVertices << endl;
	meshfile << numBaseVertices <<" "<<endl;
	for(int i=numVerts-1; i>=numBaseVertices; i--){
		meshfile << i << " ";
	}

	return 0; // success
} 
