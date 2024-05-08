
varying vec3 v_position;
varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;
varying vec4 v_color;

uniform vec4 u_color;
uniform vec3 u_Kd;
uniform float u_time;

void main()
{
	vec2 uv = v_uv;
	gl_FragColor = u_color * vec4(u_Kd, 1.0);
}
