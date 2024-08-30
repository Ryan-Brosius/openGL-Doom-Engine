#version 300 es
precision mediump float;

uniform vec3 ambientProduct;
uniform vec3 diffuseProduct;
uniform vec3 specularProduct;
uniform float shininess;

in vec3 vPosition;
in vec3 vN, vE;
in vec3 vL;
out vec4 fColor;

void main()
{
    vec3 N = normalize(vN);
    vec3 E = normalize(vE);

    vec3 L = normalize(vL);
    vec3 H = normalize( L + E );

    vec3 ambient = ambientProduct;
    if (dot(E,N) < 0.0) N = vec3(-1,-1,-1) * N;
    float diffuseTerm = max( dot(L, N), 0.0 );
    vec3 diffuse = diffuseTerm*diffuseProduct;
    float specularTerm = pow( max(dot(N, H), 0.0), shininess );
    vec3 specular = specularTerm * specularProduct;

    if ( dot(L, N) < 0.0 ) specular = vec3(0.0, 0.0, 0.0);

    vec3 normalizedPos = vPosition + vec3(0.5, 0.5, 0.5);
    vec3 scaledPos = normalizedPos * 150.0;
    float red = 0.5 * sin(scaledPos.x + scaledPos.y + scaledPos.z) + 0.5;
    float green = 0.5 * sin(scaledPos.x - scaledPos.y + scaledPos.z) + 0.5;
    float blue  = 0.5 * sin(scaledPos.x + scaledPos.y - scaledPos.z) + 0.5;
    vec3 LSD = vec3(red, green, blue) * 2.0;
    LSD = smoothstep(0.1, 0.9, LSD);
    vec3 newColor = clamp(LSD, 0.0, 1.0);

    vec3 color = ambient + newColor + specular;

    fColor = vec4(min(color,1.0), 1.0);
}
