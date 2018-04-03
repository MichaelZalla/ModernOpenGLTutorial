#version 120

// 'attribute' same as 'in' for vert shader;
// 'varying' same as 'out' for vert shader;

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

void main()
{
	gl_Position = vec4(position, 1.0);
	//.xyz = position;
	//gl_Position.w = 1;

	texCoord0 = texCoord;
}
