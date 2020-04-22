//
// Fragment Shader für den morphologischen Operator 
// Erosion
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



void main()
{

		vec4 texel = vec4(1.0, 1.0, 1.0, 1.0);

		float dist= param1.x;
    for (float i = -dist; i <= dist; i++)   {
	for(float j = -dist; j <= dist; j++){
<<<<<<< HEAD

        texel = min(texel, texture(textureMap, texCoords + vec2(i,j)));
=======
if(i!=0 && j!=0){
        texel = min(texel, texture(textureMap, texCoords +vec2(i,j)));
>>>>>>> d7ffcf4c0695ae110415613debfe8d62db718004

   } }
	}



    fragColor =		texel;
}
