//
// Fragment Shader für 5x5 Gauss Tiefpass-Filter
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

uniform vec2 offsets[25] = vec2[](	vec2(-2,  2), vec2(-1,  2), vec2(0,  2), vec2(1,  2), vec2(2,  2),
									vec2(-2,  1), vec2(-1,  1), vec2(0,  1), vec2(1,  1), vec2(2,  1), 
									vec2(-2,  0), vec2(-1,  0), vec2(0,  0), vec2(1,  0), vec2(2,  0), 
									vec2(-2, -1), vec2(-1, -1), vec2(0, -1), vec2(1, -1), vec2(2, -1), 
									vec2(-2, -2), vec2(-1, -2), vec2(0, -2), vec2(1, -2), vec2(2, -2)	);



const float PI = 3.1415926535897932384626433832795;

void main()
{
float ent00 = 1/(2*PI*(param1.x/10));
 float ent10 = ent00*exp(-0.5/(param1.x/10)); 
 float ent11=  ent00*exp(-1/(param1.x/10));
float ent20=  ent00*exp(-2/(param1.x/10));
float ent12 = ent00*exp(-2.5/(param1.x/10));
float ent22= ent00*exp(-4/(param1.x/10));


   float factor[25] = float[](ent22,ent12,ent20,ent12,ent22,
                              ent12,ent11,ent10,ent11,ent12,
							  ent20,ent10,ent00,ent10,ent20,
							  ent12,ent11,ent10,ent11,ent12,
							  ent22,ent12,ent20,ent12,ent22);
    
	vec4 texel = vec4(0.0, 0.0, 0.0, 1.0);
   float sum= 0.0;

    for (int i = 0; i < 25; i++)
    {
        texel += factor[i]* texture(textureMap, texCoords + offsets[i]);
		sum += factor[i];
    }



    fragColor =		texel/ sum ;

}