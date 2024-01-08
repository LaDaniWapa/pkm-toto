#version 330 core

uniform sampler2D texture0;
in vec2 fragTexcoord;

out vec4 fragColor;

void main()
{
    vec2 texSize = vec2(textureSize(texture0, 0));

    vec2 uv = fragTexcoord * texSize;
    vec2 st = uv / texSize;

    vec2 scale = 1.0 / texSize;

    vec4 color = texture(texture0, st);
    vec4 up = texture(texture0, st + vec2(0.0, scale.y));
    vec4 down = texture(texture0, st - vec2(0.0, scale.y));
    vec4 left = texture(texture0, st - vec2(scale.x, 0.0));
    vec4 right = texture(texture0, st + vec2(scale.x, 0.0));

    vec4 result = (color + up + down + left + right) / 5.0;

    fragColor = result;
}
