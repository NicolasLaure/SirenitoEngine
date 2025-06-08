#version 330 core  
out vec4 FragColor;

in vec4 ourColor;
in vec2 ourTextureCoordinates;
in vec3 Normal;
in vec3 FragPos;


uniform sampler2D u_Texture;
uniform float u_ObjectGlossiness;

uniform vec3 u_AmbientLightColor;

uniform vec4 u_SpotLightColor;
uniform vec3 u_SpotLightDir;
uniform vec3 u_SpotLightPos;

uniform vec3 u_ViewPos;

struct PointLight
{
	vec3 color;
	vec3 position;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};

uniform PointLight u_PointLight;
uniform DirectionalLight u_DirectionalLight;

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

void main()
{
	vec4 tintedColor = texture(u_Texture,  ourTextureCoordinates) * ourColor;
	
	vec3 output = u_AmbientLightColor;
	output += CalculateDirectionalLight(u_DirectionalLight, Normal, FragPos, u_ViewPos);
	output += CalculatePointLight(u_PointLight, Normal, FragPos, u_ViewPos);

	FragColor = vec4(output, 1.0) * tintedColor;
};