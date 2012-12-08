#version 150

in vec4 vPosition;
in vec3 vNormal;

uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;

uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform float uLightSpotLightFactor;

uniform mat3 uAmbientMaterial;
uniform mat3 uDiffuseMaterial;
uniform mat3 uSpecularMaterial;
uniform float uSpecularityExponent;

out vec4 oFragColor;

void main() {

    vec3 l = normalize( uLightPosition - vec3( vPosition ) );
    vec3 v = normalize( vec3( -vPosition ) );
    vec3 h = normalize ( l + v );
    vec3 d = normalize( vec3( uModelViewMatrix * vec4( 0,0,0,1 ) )- uLightPosition );
    float spot = pow ( clamp( dot( d, normalize( vec3( vPosition ) - uLightPosition ) ), 0, 1 ), uLightSpotLightFactor );

    vec3 ca = uAmbientMaterial * uLightColor;
    vec3 cd = uDiffuseMaterial * uLightColor * ( clamp( dot( vNormal, l ), 0, 1 ) );
    vec3 cs = uSpecularMaterial * uLightColor * pow( clamp( dot( vNormal , h ), 0, 1 ) , uSpecularityExponent );

    oFragColor = vec4( ca + spot * ( cd + cs ), 1 );

}
