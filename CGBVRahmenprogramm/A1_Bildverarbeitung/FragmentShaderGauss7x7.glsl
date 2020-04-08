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

uniform vec2 offsets[49] = vec2[](		vec2(-3,  3), vec2(-2,  3), vec2(-1,  3), vec2(0,  3), vec2(1,  3), vec2(2,  3), vec2(3,  3), 
										vec2(-3,  2), vec2(-2,  2), vec2(-1,  2), vec2(0,  2), vec2(1,  2), vec2(2,  2), vec2(3,  2),
										vec2(-3,  1), vec2(-2,  1), vec2(-1,  1), vec2(0,  1), vec2(1,  1), vec2(2,  1), vec2(3,  1),
										vec2(-3,  0), vec2(-2,  0), vec2(-1,  0), vec2(0,  0), vec2(1,  0), vec2(2,  0), vec2(3,  0),
										vec2(-3, -1), vec2(-2, -1), vec2(-1, -1), vec2(0, -1), vec2(1, -1), vec2(2, -1), vec2(3, -1),
										vec2(-3, -2), vec2(-2, -2), vec2(-1, -2), vec2(0, -2), vec2(1, -2), vec2(2, -2), vec2(3, -2),
										vec2(-3, -3), vec2(-2, -3), vec2(-1, -3), vec2(0, -3), vec2(1, -3), vec2(2, -3), vec2(3, -3)	);

void main()
{

    fragColor =	texture(textureMap, texCoords);

}