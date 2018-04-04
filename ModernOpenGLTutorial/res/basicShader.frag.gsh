#version 120

// 'varying' same as 'in' for fragment shader

varying vec2 texCoord0;
varying vec3 normal0;

// Uniform variable is accessible to both GPU and CPU;

uniform sampler2D diffuse;

void main()
{

	gl_FragColor = texture2D(diffuse, texCoord0)
		* clamp(dot(-/*lightDirection*/vec3(0, 0, 1), normal0), 0.0, 1.0);

}
