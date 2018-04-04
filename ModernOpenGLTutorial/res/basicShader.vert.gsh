#version 120

// 'attribute' same as 'in' for vertex shader;

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

// 'varying' same as 'out' for vertex shader;

varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
	// Note that the fourth component of the vec4 acts as
	// a scalar coefficient for the translation 
	// transformation;
	
	gl_Position = transform * vec4(position, 1.0);
	
	texCoord0 = texCoord;

	normal0 = vec3(transform * vec4(normal, 0.0)).xyz;
}
