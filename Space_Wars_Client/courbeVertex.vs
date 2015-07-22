attribute vec4 a_position;

uniform vec3 u_camPos;
uniform vec3 u_camDir;

uniform mat4 u_projection;
uniform mat4 u_modelView;
uniform mat4 u_world;
uniform vec3 u_color;

varying vec3 v_normal;
varying vec4 v_color;



varying vec3 v_lightPos;
varying vec3 v_lightDirection;

void main(void)
{
	gl_Position = u_projection * u_modelView * u_world * a_position;

	v_lightPos = u_camPos;
	v_lightDirection = u_camDir;

	vec3 normal = a_position.xyz;
	normal = normalize(normal);
	normal = mat3(u_world) * normal;
	v_normal = normal;

	vec3 L = normalize(-v_lightPos + v_lightDirection);
	float NdotL = max(dot(v_normal, L), 0.0);
	NdotL = 1.;
	v_color = vec4(u_color, 1.0) * NdotL;
}