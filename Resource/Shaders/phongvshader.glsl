#version 300 es


in vec3 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 vPosition;
out vec3 vN, vE;
out vec3 vL;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;

void main()
{
    vPosition = aPosition.xyz;

    vec3 pos = (modelViewMatrix * vec4(aPosition, 1.0)).xyz;
    vE = normalize(-pos);
    vN = normalize((modelViewMatrix * vec4(aNormal, 0.0)).xyz);

    vL = normalize(lightPosition - pos);

    gl_Position = projectionMatrix * vec4(pos, 1.0);
}
