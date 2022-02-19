#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineTransformComponent.h"

enum class ProjectionMode
{
	Perspective,
	Orthographic
};

// Ό³Έν :
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;

public:
	// constrcuter destructer
	CameraComponent();
	~CameraComponent();
	CameraComponent(const CameraComponent& _Other) = delete;
	CameraComponent(CameraComponent&& _Other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _Other) = delete;
	CameraComponent& operator=(CameraComponent&& _Other) noexcept = delete;

	void SetProjectionMode(ProjectionMode _ProjectionMode)
	{
		ProjectionMode_ = _ProjectionMode;
	}

protected:
	void Start() override;
	void Update() override;

private:
	ProjectionMode ProjectionMode_;
	float FovAngleY_;
	float4 CamSize_;
	float NearZ_;
	float FarZ_;



	void CameraTransformUpdate();
};

