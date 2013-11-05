#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <GL/glut.h>
#include "os.h"
#include "objreader.h"


objReader::objReader(){
  //Initialize Data
  m_maxX=m_minX=m_maxY=m_minY=m_maxZ=m_minZ=0;
  m_vertex_list=m_normal_list=m_texcoord_list=0;
  m_face_list=0;
  m_vertexCount=m_normalCount=m_texCoordCount=m_faceCount=0;	

  m_OBJerror= OBJ_NONE; //OBJ_NO_DATA;
}

objReader::~objReader() {	
}

int objReader::getTriangleCount() {
  if( m_OBJerror ) return 0;
  return m_faceCount;
}

int objReader::getVertexCount() {
  if( m_OBJerror ) return 0;
  return m_vertexCount;
} 

OBJerrorenum objReader::getError(){
  return m_OBJerror;
} 

void objReader::getBoundingVolume(float *minX,float *maxX,
				  float *minY,float *maxY,
				  float *minZ,float *maxZ) {
  if( m_OBJerror ) return;
  *minX = m_minX;
  *minY = m_minY;
  *minZ = m_minZ;
  *maxX = m_maxX;
  *maxY = m_maxY;
  *maxZ = m_maxZ;
} 

void objReader::loadObj(const char *filename) {
  int i=0,j=0,k=0,l=0,m=0; //loop variables
  m_maxZ=-3000;
  char token[80];
  int swapVertices=0;
  FILE *fp;
  fp = fopen(filename,"r");
  if( !fp ) { 
    m_OBJerror=OBJ_FILE_ERROR;
    return; 
  }
  rewind(fp);
  // Preprocess the Text File
  // Get the size number of vertices
  // Get the number of faces
  m_vertexCount=m_normalCount=m_texCoordCount=m_faceCount=0;
  while(	fgets(token,80,fp) != NULL){
    if(strlen(token)>2){
      if( token[0]=='v' && token[1]==' ' ) m_vertexCount++;
      else if( token[0]=='v' && token[1]=='n' ) m_normalCount++;
      else if( token[0]=='v' && token[1]=='t' ) m_texCoordCount++;
      else if( token[0]=='f' && token[1]==' ' ) m_faceCount++;
    }
  }	
  if(m_vertex_list)	{	
    free(m_vertex_list);
    free(m_normal_list);
    free(m_texcoord_list);
    free(m_face_list);
  }
  
  // Create Space for the object
  if( m_vertexCount ) m_vertex_list		= (coord *)malloc(m_vertexCount*sizeof(coord));
  else m_vertex_list=0;
  
  if( m_normalCount ) m_normal_list		= (coord *)malloc(m_normalCount*sizeof(coord));
  else m_normal_list=0;
  
  if( m_texCoordCount ) m_texcoord_list = (coord *)malloc(m_texCoordCount*sizeof(coord));
  else m_texcoord_list=0;
  
  if( m_faceCount ) m_face_list			= (face *)malloc(2*m_faceCount*sizeof(face));
  else m_face_list=0;
  
  /*	if( !(m_vertex_list && m_normal_list && m_texcoord_list && m_face_list) ){
	m_OBJerror = OBJ_LOW_MEMORY;
	return;
	}*/
  memset(m_vertex_list,0,m_vertexCount*sizeof(coord));
  memset(m_normal_list,0,m_normalCount*sizeof(coord));
  memset(m_texcoord_list,0,m_texCoordCount*sizeof(coord));
  memset(m_face_list,0,m_faceCount*2*sizeof(face));
  // Reset the filestream
  rewind(fp);
  // Read in the data
  while( fgets(token,80,fp)!=NULL ){
    if( token[1]==' ' ) token[1]='\0';
    else token[2]='\0';
    if(strcmp(token,"v") == 0 ){
      sscanf(&token[2],"%f%f%f",&m_vertex_list[i].x,&m_vertex_list[i].y,&m_vertex_list[i].z);
      if( i==0 ){
	m_maxX=m_vertex_list[i].x;
	m_maxY=m_vertex_list[i].y;
	m_maxZ=m_vertex_list[i].z;
	m_minX=m_vertex_list[i].x;
	m_minY=m_vertex_list[i].y;
	m_minZ=m_vertex_list[i].z;
      }
      else{
	if( m_vertex_list[i].x > m_maxX ) m_maxX=m_vertex_list[i].x;
	if( m_vertex_list[i].y > m_maxY ) m_maxY=m_vertex_list[i].y;
	if( m_vertex_list[i].z > m_maxZ ) m_maxZ=m_vertex_list[i].z;
	if( m_vertex_list[i].x < m_minX ) m_minX=m_vertex_list[i].x;
	if( m_vertex_list[i].y < m_minY ) m_minY=m_vertex_list[i].y;
	if( m_vertex_list[i].z < m_minZ ) m_minZ=m_vertex_list[i].z;
      }
      i++;
    }
    else if(strcmp(token,"vn") == 0 ){
      sscanf(&token[3],"%f%f%f",&m_normal_list[j].x,&m_normal_list[j].y,&m_normal_list[j].z);
      // FIXME: Normalize!
      j++;
    }
    else if(strcmp(token,"vt") == 0 ){
      sscanf(&token[3],"%f%f",&m_texcoord_list[k].x,&m_texcoord_list[k].y);
      m_texcoord_list[k].z=0;
      k++;
    }
    else if(strcmp(token,"f") == 0 ){
      int vnum,nnum,tnum;
      char *tempptr;
      tempptr= &token[2];
      m=0;
      while( tempptr && (3==sscanf(tempptr,"%i/%i/%i",&vnum,&tnum,&nnum)) ){
	vnum-=1;nnum-=1;tnum-=1;
	m_face_list[l].v[m]=vnum;
	m_face_list[l].n[m]=nnum;
	m_face_list[l].t[m]=tnum;
	m++;
	tempptr=strchr(tempptr,' ');
	if(tempptr) tempptr+=1;
      }
      while( tempptr && (2==sscanf(tempptr,"%i//%i",&vnum,&nnum)) ){
	vnum-=1;nnum-=1;tnum-=1;
	m_face_list[l].v[m]=vnum;
	m_face_list[l].n[m]=nnum;
	m_face_list[l].t[m]=0;
	m++;
	tempptr=strchr(tempptr,' ');
	if(tempptr) tempptr+=1;
      }
      while( tempptr && (2==sscanf(tempptr,"%i/%i",&vnum,&tnum)) ){
	vnum-=1;nnum-=1;tnum-=1;
	m_face_list[l].v[m]=vnum;
	m_face_list[l].n[m]=0;
	m_face_list[l].t[m]=tnum;
	m++;
	tempptr=strchr(tempptr,' ');
	if(tempptr) tempptr+=1;
      }
      while( tempptr && (1==sscanf(tempptr,"%i",&vnum)) ){
	vnum-=1;nnum-=1;tnum-=1;
	m_face_list[l].v[m]=vnum;
	m_face_list[l].n[m]=0;
	m_face_list[l].t[m]=0;
	m++;
	tempptr=strchr(tempptr,' ');
	if(tempptr) tempptr+=1;
      }
      if( m == 4) { //split into two 
	m_face_list[l+1].v[0]= m_face_list[l].v[0];
	m_face_list[l+1].n[0]= m_face_list[l].n[0];
	m_face_list[l+1].t[0]= m_face_list[l].t[0];
	m_face_list[l+1].v[1]= m_face_list[l].v[2];
	m_face_list[l+1].n[1]= m_face_list[l].n[2];
	m_face_list[l+1].t[1]= m_face_list[l].t[2];
	m_face_list[l+1].v[2]= m_face_list[l].v[3];
	m_face_list[l+1].n[2]= m_face_list[l].n[3];
	m_face_list[l+1].t[2]= m_face_list[l].t[3];
	l++;
      }
      if( swapVertices ){
	int ll;
	for( ll = ( m == 4? l-1 : l); ll <= l; ll++){
	  int temp;
	  temp=m_face_list[ll].v[0];
	  m_face_list[ll].v[0]=m_face_list[ll].v[1];
	  m_face_list[ll].v[1]=temp;
	  
	  temp=m_face_list[ll].n[0];
	  m_face_list[ll].n[0]=m_face_list[ll].n[1];
	  m_face_list[ll].n[1]=temp;
	  
	  temp=m_face_list[ll].t[0];
	  m_face_list[ll].t[0]=m_face_list[ll].t[1];
	  m_face_list[ll].t[1]=temp;
	}
	
      }
      l++;  //increase the number of faces
    }
    else if(strcmp(token,"g") == 0 ){
      swapVertices=0;
      if( strcmp(&token[2],"Facets_8\n")==0 )
	swapVertices=1;
      /*if( strcmp(&token[2],"Left_Leg2\n")==0 )
	swapVertices=1;
	if( strcmp(&token[2],"Left_Leg3\n")==0 )
	swapVertices=1;
	if( strcmp(&token[2],"Left_Arm1\n")==0 )
	swapVertices=1;
	if( strcmp(&token[2],"Left_Arm2\n")==0 )
	swapVertices=1;
	if( strcmp(&token[2],"Left_Arm3\n")==0 )
	swapVertices=1;*/
      
    }
  }/* end of while loop */
  fclose(fp);
  m_faceCount = l;
  if( i!=m_vertexCount || j!= m_normalCount || k!=m_texCoordCount || l!=m_faceCount ){
    m_OBJerror = OBJ_DATA_MISMATCH;
    return;
  }
  m_maxX += m_maxX * (m_maxX > 0 ? .1 : -0.1);
  m_maxY += m_maxY * (m_maxY > 0 ? .1 : -0.1);
  m_maxZ += m_maxZ * (m_maxZ > 0 ? .1 : -0.1);
  m_minX -= m_minX * (m_minX > 0 ? .1 : -0.1);
  m_minY -= m_minY * (m_minY > 0 ? .1 : -0.1);
  m_minZ -= m_minZ * (m_minZ > 0 ? .1 : -0.1);
};

void objReader::displayObj() {
  int i,j;
  if( m_OBJerror ) return;
  for(i=0; i<m_faceCount; i++){
    glBegin(GL_POLYGON);
    for(j=0; j<3; j++) {				    
      if (m_texcoord_list)
	glTexCoord3f(m_texcoord_list[m_face_list[i].t[j]].x,
		     m_texcoord_list[m_face_list[i].t[j]].y,
		     m_texcoord_list[m_face_list[i].t[j]].z);
      if (m_normal_list)
	glNormal3f(m_normal_list[m_face_list[i].n[j]].x, 
		   m_normal_list[m_face_list[i].n[j]].y, 
		   m_normal_list[m_face_list[i].n[j]].z);
      glVertex3f(m_vertex_list[m_face_list[i].v[j]].x, 
		 m_vertex_list[m_face_list[i].v[j]].y, 
		 m_vertex_list[m_face_list[i].v[j]].z);
    } // END: for j
    glEnd();
  } // END: for i
} 

void objReader::centerObject(){
  int i;
  if( m_OBJerror ) return;
  float cx = m_minX+(m_maxX-m_minX)/2.0f;
  float cy = m_minY+(m_maxY-m_minY)/2.0f;
  float cz = m_minZ+(m_maxZ-m_minZ)/2.0f;
  
  for( i=0; i< m_vertexCount; i++ ){
    m_vertex_list[i].x-=cx;
    m_vertex_list[i].y-=cy;
    m_vertex_list[i].z-=cz;
  } // END for i
  m_minX-=cx;
  m_maxX-=cx;
  m_minY-=cy;
  m_maxY-=cy;
  m_minZ-=cz;
  m_maxZ-=cz;
} 

void objReader::resizeObject() {
  float s = 0.0;
  
  if (-m_minX > s) s = -m_minX;
  if (-m_minY > s) s = -m_minY;
  if (-m_minZ > s) s = -m_minZ;
  if (m_maxX > s) s = m_maxX;
  if (m_maxY > s) s = m_maxY;
  if (m_maxZ > s) s = m_maxZ;
  
  s = 1.0/s;
  
  for (int i = 0; i < m_vertexCount; i++) {
    m_vertex_list[i].x *= s;
    m_vertex_list[i].y *= s;
    m_vertex_list[i].z *= s;
  }
  m_minX *= s;
  m_maxX *= s;
  m_minY *= s;
  m_maxY *= s;
  m_minZ *= s;
  m_maxZ *= s;
}
