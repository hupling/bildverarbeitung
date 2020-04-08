//
// The gouraud vertex shader.
// ---------------------------------
// Angepasst f�r Core Profile
//
// @author: Link Alexis Constantin, Andreas Klein
// @lecturer: Prof. Dr. Alfred Nischwitz
//
// (c)2010 Hochschule M�nchen, HM
//
// ---------------------------------
#version 330
//Attribute 
in vec4 vVertex;
in vec2 vTexCoord;

uniform mat4 mvpMatrix;
//Texturkoordinaten an Fragmentshader �bergeben
smooth out vec2 texCoords;

void main()
{	
	
	gl_Position = mvpMatrix * vVertex ;
	// texcoords �bergeben.
	texCoords = vTexCoord;
}