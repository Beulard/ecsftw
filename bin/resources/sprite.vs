#version 120

attribute vec3 vertex;
attribute vec2 uv;

varying vec2 UV;

uniform vec2 camPos;
uniform mat3 projMat;

void main(){
	vec4 pos = vec4( projMat * (vertex - vec3(200, 300, 0) - vec3(camPos, 0)), 1 );
	UV = uv;
	gl_Position = pos;
}
