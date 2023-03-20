#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;

uniform float L;
uniform float Q;
uniform float A;
uniform float S;
uniform float t;
uniform vec2 D;

uniform mat4 view, projection;

out vec3 worldSpace_pos;
out vec3 worldSpace_norm;

vec3 gerstnerWavePos(vec2 xz, float Q, float A, vec2 D, float w, float phi, float t){
    float x = xz.x + Q * A * D.x * cos(w * dot(D, xz) + phi * t);
    float z = xz.y + Q * A * D.y * cos(w * dot(D, xz) + phi * t);
    float y = A * sin(w * dot(D, xz) + phi * t);
    return vec3(x, y, z);
}

vec3 gerstnerWaveNorm(vec2 xz, float A, vec2 D, float w, float phi, float t){
    float WA = w * A;
    float C = cos(w * dot(D, xz) + phi * t);
    float S = sin(w * dot(D, xz) + phi * t);
    
    float x = -D.x * WA * C;
    float z = -D.y * WA * C;
    float y = 1 - Q * WA * S;

    return vec3(x, y, z);
}

void main() {
    vec2 Dn = normalize(D);
    float w = 2/L;
    float phi = S * 2/L;
    float Qp = Q/(w * A);

    vec2 xz = vec2(pos.x, pos.z);
    worldSpace_pos = gerstnerWavePos(xz, Qp, A, Dn, w, phi, t);
    xz = vec2(worldSpace_pos.x, worldSpace_pos.z);
    worldSpace_norm = gerstnerWaveNorm(xz, A, Dn, w, xz, phi, t);

    gl_Position = projection * view * vec4(worldSpace_pos, 1);
}
