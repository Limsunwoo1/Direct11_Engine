#include "globals.hlsli"

//cbuffer Transform : register(b0)
//{
//    row_major matrix world;
//    row_major matrix view;
//    row_major matrix projection;
//}
VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.f;
    
    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);
    
    Out.Pos = ProjPosition;
    Out.Color = In.Color;
    Out.UV = In.UV;
    
    return Out;
}