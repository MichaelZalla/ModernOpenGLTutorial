#version 120

// Uniform variable is accessible to both GPU and CPU;

varying vec2 texCoord0;

// varying vec4 diffuseOut;

uniform sampler2D diffuse;

void main()
{
	//diffuseOut = texture2D(diffuse, texCoord0);
	gl_FragColor = texture2D(diffuse, texCoord0);
}
