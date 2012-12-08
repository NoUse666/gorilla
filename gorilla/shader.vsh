#version 150

in vec4 aPosition;
in vec3 aNormal;

uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;

out vec4 vPosition;
out vec3 vNormal;

void main() {

    vNormal = normalize( vec3( transpose( inverse( mat3( uModelViewMatrix ) ) ) * aNormal ) );
    vPosition = uModelViewMatrix * aPosition;

    gl_Position = uProjectionMatrix * uModelViewMatrix * aPosition;

}
