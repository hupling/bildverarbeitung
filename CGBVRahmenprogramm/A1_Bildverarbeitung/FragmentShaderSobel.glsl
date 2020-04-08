//
// Fragment Shader f�r Sobel Operator
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

uniform vec2 offsets[9] = vec2[](	vec2(-1,  1),vec2(-1,  0),vec2(-1, -1),
									vec2( 0,  1),vec2( 0,  0),vec2( 0, -1),
									vec2( 1,  1),vec2( 1,  0),vec2( 1, -1)	);

 uniform  float factorx[9] = float[](1,2,1,
                                    0,0,0,
							       -1,-2,-1);
							 
uniform  float factory[9] = float[](1,0,-1,
                                    2,0,-2,
							        1,0,-1);
void main()
{
   
      vec4 texelx = vec4(0.0 , 0.0, 0.0, 1.0);
	  vec4 texely = vec4(0.0, 0.0, 0.0, 1.0);


    for (int i = 0; i < 9; i++)
    {
        texelx += factorx[i] *texture(textureMap, texCoords + offsets[i]);
        texely += factory[i]*texture(textureMap, texCoords + offsets[i]);
	}
   
  
fragColor =	(sqrt(texelx*texelx+texely+texely)+param1.x/10)*(param1.y+1);


}