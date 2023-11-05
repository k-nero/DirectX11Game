struct VS_INPUT
{
    float4 Pos : POSITION0;
    float2 Texcoord : TEXCOORD0;
    float3 Normal : NORMAL0;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Texcoord : TEXCOORD0;
    float3 Normal : NORMAL0;
    float3 direction_to_camera : TEXCOORD1;
};

cbuffer constant: register(b0)
{
    row_major matrix m_world;
    row_major matrix m_view;
    row_major matrix m_proj;
    float4 light_direction;
    float4 camera_position;
}

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.Pos = mul(input.Pos, m_world);
    output.direction_to_camera = normalize(output.Pos.xyz - camera_position.xyz);
    output.Pos = mul(output.Pos, m_view);
    output.Pos = mul(output.Pos, m_proj);
    output.Texcoord = input.Texcoord;
    output.Normal = input.Normal;
    return output;
}