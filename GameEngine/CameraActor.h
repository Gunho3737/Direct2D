#pragma once
#include "GameEngineActor.h"

class CameraComponent;
// Ό³Έν :
class CameraActor : public GameEngineActor
{
public:
	// constrcuter destructer
	CameraActor();
	~CameraActor();

	// delete Function
	CameraActor(const CameraActor& _Other) = delete;
	CameraActor(CameraActor&& _Other) noexcept = delete;
	CameraActor& operator=(const CameraActor& _Other) = delete;
	CameraActor& operator=(CameraActor&& _Other) noexcept = delete;

	CameraComponent* GetCamera()
	{
		return Camera_;
	}

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);

private:
	CameraComponent* Camera_;

};

