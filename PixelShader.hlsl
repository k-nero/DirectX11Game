struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Color : COLOR;
};

cbuffer constant : register(b0)
{
    float time;
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	return float4(input.Color * time, 1.0f);
}