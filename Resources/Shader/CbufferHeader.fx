//cbuffer-> CPU에 있는 데이터를 GPU로 보내기 위한 것
//바이트 단위로 보내는 것이다


cbuffer TransformData : register(b0)
{
    float4 vWorldTranslation;
    float4 vWorldRotation;
    float4 vWorldScaling;

    float4 vLocalTranslation;
    float4 vLocalRotation;
    float4 vLocalScaling;

    float4x4 Scaling;
    float4x4 Rotation;
    float4x4 Translation;
    float4x4 Revolve;
    float4x4 Parent;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};

