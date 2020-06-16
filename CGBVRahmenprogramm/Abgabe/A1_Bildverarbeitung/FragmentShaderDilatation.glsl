//
// Fragment Shader f�r den morphologischen Operator 
// Dilatation
// Angepasst f�r Core Profile
// ---------------------------------
//
// @author: Prof. Dr. Alfred Nischwitz
// @lecturer: Prof. Dr. Alfred Nischwitz
//
// (c)2017 Hochschule M�nchen, HM
//
// ---------------------------------
#version 330


smooth in vec2 texCoords;				// pixelbezogene Texturkoordinate
out vec4 fragColor;					// Ausgabewert mit 4 Komponenten zwischen 0.0 und 1.0
uniform sampler2DRect textureMap;		// Sampler f�r die Texture Map
uniform vec4 param1;					// Param1 X,Y,Z,W in GUI


void main()
{

		vec4 texel = texture(textureMap, texCoords);

		float dist= param1.x;
    for (float i = -dist; i <= dist; i++)   {
	for(float j = -dist; j <= dist; j++){

        texel = max(texel, texture(textureMap, texCoords +vec2(i,j)));

    }
	}



    fragColor =		texel;
}