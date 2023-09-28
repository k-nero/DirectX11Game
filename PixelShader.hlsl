Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Texcoord : TEXCOORD0;
};

cbuffer constant : register(b0)
{
    row_major matrix m_world;
    row_major matrix m_view;
    row_major matrix m_proj;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    return Texture.Sample(TextureSampler, input.Texcoord);
}