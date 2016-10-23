attribute vec4 position;

uniform mat4 modelViewMatrix;
void main() {

	gl_Position = modelViewMatrix * position;
}