#version 120

attribute vec3 a_position;
attribute vec3 a_normal;

uniform mat4 u_model_matrix;
uniform mat3 u_normal_matrix;
uniform mat4 u_PVM;

varying vec3 v_position;
varying vec3 v_normal;

void main()
{
    // 월드 좌표계로 변환된 위치와 노말
    vec4 position_wc = u_model_matrix * vec4(a_position, 1.0);
    v_position = position_wc.xyz;
    v_normal = normalize(u_normal_matrix * a_normal);

    gl_Position = u_PVM * vec4(a_position, 1.0);
}
