struct VS_INPUT
{
    float4 Pos : POSITION0;
    float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Texcoord : TEXCOORD0;

};



VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    return output;
}