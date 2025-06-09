#version 330 core  
out vec4 FragColor;

in vec4 ourColor;
in vec3 Normal;
in vec3 FragPos;

uniform float u_ObjectGlossiness;

uniform vec3 u_AmbientLightColor;

uniform vec3 u_ViewPos;

struct PointLight
{
	vec3 color;
	vec3 position;

	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
};

struct SpotLight
{
	vec3 color;
	vec3 position;
	vec3 direction;
	float innerAngle;
	float outerAngle;
};

uniform PointLight u_PointLight;
uniform DirectionalLight u_DirectionalLight;
uniform SpotLight u_SpotLight;

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewPos)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.color;
	
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = u_ObjectGlossiness * spec * light.color;
	
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	diffuse *= attenuation;
	specular *= attenuation;
	
	return (diffuse + specular);
};

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewPos)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.color;
	
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = u_ObjectGlossiness * spec * light.color;
	
	return (diffuse + specular);
};

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewPos)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerAngle - light.outerAngle;
	float intensity = clamp((theta - light.outerAngle) / epsilon, 0.0, 1.0);

	if(theta > light.outerAngle)
	{
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * light.color;
	
		vec3 viewDir = normalize(viewPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);	
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = u_ObjectGlossiness * spec * light.color;
	
		diffuse *= intensity;
		specular *= intensity;

		return (diffuse + specular);
	}
	
	return vec3(0.0, 0.0, 0.0);
};

void main()
{
  	vec3 output = u_AmbientLightColor;
	output += CalculateDirectionalLight(u_DirectionalLight, Normal, FragPos, u_ViewPos);
	output += CalculatePointLight(u_PointLight, Normal, FragPos, u_ViewPos);
	output += CalculateSpotLight(u_SpotLight, Normal, FragPos, u_ViewPos);

	FragColor = vec4(output, 1.0) * ourColor;
};