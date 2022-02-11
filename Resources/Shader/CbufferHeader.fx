//cbuffer-> CPU에 있는 데이터를 GPU로 보내기 위한 것
//바이트 단위로 보내는 것이다


cbuffer TransformData : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};

