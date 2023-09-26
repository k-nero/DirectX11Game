struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Color : COLOR;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Color : COLOR;
};

cbuffer constant: register(b0)
{
    float time;
    row_major matrix m_world;
    row_major matrix m_view;
    row_major matrix m_proj;
}

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = mul(input.Pos, m_world);
    output.Pos = mul(output.Pos, m_view);
    output.Pos = mul(output.Pos, m_proj);
    output.Color = input.Color;
    return output;
}