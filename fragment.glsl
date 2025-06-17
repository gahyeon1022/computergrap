#version 120

varying vec3 v_normal;
varying vec3 v_position;

uniform vec3 u_camera_position;
uniform vec3 u_light_position;

uniform vec3 u_light_ambient;
uniform vec3 u_light_diffuse;
uniform vec3 u_light_specular;

uniform vec3 u_obj_ambient;
uniform vec3 u_obj_diffuse;
uniform vec3 u_obj_specular;
uniform float u_obj_shininess;

void main()
{
    vec3 N = normalize(v_normal);
    vec3 L = normalize(u_light_position - v_position);
    vec3 V = normalize(u_camera_position - v_position);
    vec3 R = reflect(-L, N);

    vec3 ambient = u_light_ambient * u_obj_ambient;

    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = u_light_diffuse * u_obj_diffuse * diff;

    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(R, V), 0.0), u_obj_shininess);
    vec3 specular = u_light_specular * u_obj_specular * spec;

    vec3 final_color = ambient + diffuse + specular;
    gl_FragColor = vec4(final_color, 1.0);
}
