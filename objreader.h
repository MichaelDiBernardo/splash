#ifndef OBJREADER
#define OBJREADER

// NOTE(mddibern): This is not my code: It was supplied by CS314 course staff.

enum OBJerrorenum { OBJ_NONE,
                    OBJ_NO_DATA,
                    OBJ_DATA_MISMATCH, 
		    OBJ_LOW_MEMORY, 
		    OBJ_FILE_ERROR  };

struct coord {
	float x;
	float y;
	float z;
};

struct edge {
	int v[2];
	int f[2];
	int faceCount;
};

struct face {
	int v[4]; // vertices
	int n[4]; // normals
	int t[4]; // texture coords
	int fn[4]; // face neighbors
	int neighborCount;
	float area; // triangle area
	coord normal; // normal for triangle
	int visited;
	float visibility;
};

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	class objReader	      			  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

class objReader{
public:
  objReader();
  ~objReader();
  
  void		displayObj();
  void		loadObj(const char *filename);
  
  OBJerrorenum		getError();
  
  void getBoundingVolume(float *minX,float *maxX,
			 float *minY,float *maxY,
			 float *minZ,float *maxZ);
  
  int			getVertexCount();
  int			getTriangleCount();
  
  face* getFaceList() { return m_face_list; }
  
  void	centerObject();
  void	resizeObject();
  
private:
  coord		*m_vertex_list;			// loaded vertex data
  coord		*m_normal_list;			// loaded normal data
  coord		*m_texcoord_list;		// loaded texture coordinate data	
  face		*m_face_list;			// loaded face data
  edge		*m_edge_list;			// loaded edge data

  int		m_vertexCount;			// number of vertices in loaded object
  int		m_normalCount;			// number of normals
  int		m_texCoordCount;		// number of texture coordinates
  int		m_faceCount;			// number of faces in loaded object
    
  float		m_maxX;				// maximum and mininum x, y and z values
  float		m_minX;				// for loaded object
  float		m_maxY;				//
  float		m_minY;				//
  float		m_maxZ;				//
  float		m_minZ;				//
  
  OBJerrorenum m_OBJerror;
};

#endif
