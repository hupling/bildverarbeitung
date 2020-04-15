//
// Fragment Shader f�r Sharpen Operator
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

uniform vec2 offsets[9] = vec2[](	vec2(-1,  1),
									vec2(-1,  0),
									vec2(-1, -1),
									vec2( 0,  1),
									vec2( 0,  0),
									vec2( 0, -1),
									vec2( 1,  1),
									vec2( 1,  0),
									vec2( 1, -1)	);

void main()
{ float factor[9] = float[](0,1,0,
                             1,-4,1,
							 0,1,0);
    
	vec4 texel = vec4(0.0, 0.0, 0.0, 1.0);

    for (int i = 0; i < 9; i++)
    {
        texel += factor[i]* texture(textureMap, texCoords + offsets[i]);
    }



	(	texel+param1.x/10+0.5)*(param1.y+1);


    fragColor =	texture(textureMap, texCoords)+param1.x/10*(texel);

}