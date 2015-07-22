
varying vec3 v_normal;
varying vec4 v_color;

varying vec3 v_lightPos;
varying vec3 v_lightDirection;

void main(void)
{
    vec3 N = normalize(v_normal);
	vec3 L = normalize(-v_lightPos + v_lightDirection);
	float NdotL = max(dot(N, L), 0.0);
    NdotL = 1.;
  	gl_FragColor = v_color * NdotL;
}