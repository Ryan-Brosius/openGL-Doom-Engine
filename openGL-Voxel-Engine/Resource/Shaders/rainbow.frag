#version 330 core
in vec2 uv;
out vec4 FragColor;

vec3 rainbow(float h)
{
    float r = clamp(1.0 - abs(h * 6.0 - 3.0), 0.0, 1.0);
    float g = clamp(2.0 - abs(h * 6.0 - 2.0), 0.0, 1.0);
    float b = clamp(2.0 - abs(h * 6.0 - 4.0), 0.0, 1.0);
    return vec3(r, g, b);
}

void main()
{
    float hue = mod(atan(uv.y, uv.x) / (2.0 * 3.14159), 1.0);
    vec3 color = rainbow(hue);
    
    FragColor = vec4(color, 1.0);
}
