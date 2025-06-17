#version 120

attribute vec3 a_position;
attribute vec3 a_normal;

uniform mat4 u_PVM;
uniform mat4 u_model_matrix;
uniform mat3 u_normal_matrix;

varying vec3 v_position;   // fragment에서 사용할 position (world coord)
varying vec3 v_normal;     // fragment에서 사용할 normal (world coord)

void main()
{
    // 최종 좌표
    gl_Position = u_PVM * vec4(a_position, 1.0);

    // 조명 계산용 데이터 전달
    v_position = (u_model_matrix * vec4(a_position, 1.0)).xyz;
    v_normal = normalize(u_normal_matrix * a_normal);
}
