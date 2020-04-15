//
// Fragment Shader für 7x7 Gauss Tiefpassfilter
// Angepasst für Core Profile
// ---------------------------------
//
// @author: Prof. Dr. Alfred Nischwitz
// @lecturer: Prof. Dr. Alfred Nischwitz
//
// (c)2017 Hochschule München, HM
//
// ---------------------------------
#version 330

smooth in vec2 texCoords;				// pixelbezogene Texturkoordinate
out vec4 fragColor;					// Ausgabewert mit 4 Komponenten zwischen 0.0 und 1.0
uniform sampler2DRect textureMap;		// Sampler für die Texture Map
uniform vec4 param1;					// Param1 X,Y,Z,W in GUI

uniform vec2 offsets[7] = vec2[](   vec2(0,  3), 
									 vec2(0,  2),
									 vec2(0,  1),
									 vec2(0,  0),
								     vec2(0, -1), 
									 vec2(0, -2), 
									 vec2(0, -3)	);

const float PI = 3.1415926535897932384626433832795;

void main()
{
float powerx =pow(param1.x/10,2);
float ent00 = sqrt(1/(2*PI*powerx));
 float ent10 = ent00*exp(-1/(2*powerx)); 
 float ent20=  ent00*exp(-4/(2*powerx));
 float ent30 = ent00*exp(-9/(2*powerx));


   float factor[7] = float[](ent30,ent20,ent10,ent00,ent10,ent20,ent30);
    
	vec4 texel = vec4(0.0, 0.0, 0.0, 1.0);
   float sum= 0.0;

    for (int i = 0; i < 7; i++)
    {
        texel += factor[i]* texture(textureMap, texCoords + offsets[i]);
		sum += factor[i];
    }



    fragColor =		texel/ sum ;


}
