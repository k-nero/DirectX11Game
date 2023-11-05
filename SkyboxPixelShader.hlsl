Texture2D Texture : register(t0);
SamplerState TextureSampler : register(ps_5_0, s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Texcoord : TEXCOORD0;
    float3 Normal : NORMAL0;
    float3 direction_to_camera : TEXCOORD1;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return Texture.Sample(TextureSampler, input.Texcoord);
}