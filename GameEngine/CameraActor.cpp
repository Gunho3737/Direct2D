#include "PreCompile.h"
#include "CameraActor.h"
#include "CameraComponent.h"
#include "GameEngineTransform.h"

CameraActor::CameraActor()
	: Camera_(nullptr)
{
}

CameraActor::~CameraActor()
{
}



void CameraActor::Start()
{
	Camera_ = CreateTransformComponent<CameraComponent>(GetTransform());
}

float4x4 CameraActor::GetViewMatrix()
{
	return Camera_->GetTransform()->GetTransformData().View_;
}

float4x4 CameraActor::GetProjectionMatrix()
{
	return Camera_->GetTransform()->GetTransformData().Projection_;
}

void CameraActor::TransformUpdate()
{
	GameEngineActor::TransformUpdate();
	Camera_->CameraTransformUpdate();
}
void CameraActor::Update(float _DeltaTime)
{

}