Texture2D Texture : register(t0);
SamplerState TextureSampler : register(ps_5_0, s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Texcoord : TEXCOORD0;
    float3 Normal : NORMAL0;
    float3 direction_to_camera : TEXCOORD1;
};

cbuffer constant : register(b0)
{
    row_major matrix m_world;
    row_major matrix m_view;
    row_major matrix m_proj;
    float4 light_direction;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    //Ambient Light
    float ka = 0.1;
    float3 ia = float3(1.0, 1.0, 1.0);
    float3 ambient_light = ka * ia;

	//DIFFUSE LIGHT
    float kd = 0.7;
    float3 id = float3(1.0, 1.0, 1.0);
    float amount_diffuse_light = max(0.0, dot(light_direction.xyz, input.Normal));
    float3 diffuse_light = kd * amount_diffuse_light * id;

	//SPECULAR LIGHT
    float ks = 1.0;
    float3 is = float3(1.0, 1.0, 1.0);
    float3 reflected_light = reflect(light_direction.xyz, input.Normal);
    float shininess = 30.0;
    float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);
    float3 specular_light = ks * amount_specular_light * is;

    float3 light = ambient_light + diffuse_light + specular_light;

    
    //return Texture.Sample(TextureSampler, input.Texcoord) * float4(light, 1.0);
    return float4(light, 1.0);
}