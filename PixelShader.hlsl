struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Color : COLOR;
};

cbuffer constant : register(b0)
{
    float time;
    row_major matrix m_world;
    row_major matrix m_view;
    row_major matrix m_proj;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	return float4(input.Color * time, 1.0f);
}