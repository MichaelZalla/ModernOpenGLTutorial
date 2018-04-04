#version 120

// 'attribute' same as 'in' for vert shader;
// 'varying' same as 'out' for vert shader;

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
	// Note that the fourth component of the vec4 acts as
	// a scalar coefficient for the translation 
	// transformation;
	
	gl_Position = transform * vec4(position, 1.0);
	
	texCoord0 = texCoord;
}
