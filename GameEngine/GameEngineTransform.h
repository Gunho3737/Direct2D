#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"

class TransformData
{
public:
	float4 vWorldPosition_;
	float4 vWorldRotation_;
	float4 vWorldScaling_;

	float4 vLocalPosition_;
	float4 vLocalRotation_;
	float4 vLocalScaling_;

	float4x4 LocalScaling_;
	float4x4 LocalRotation_;
	float4x4 LocalPosition_;
	float4x4 LocalWorld_;

	float4x4 Parent_;
	float4x4 WorldWorld_;

	float4x4 View_;
	float4x4 Projection_;

public:
	TransformData()
		: vWorldScaling_(float4::ONE)
		, vLocalScaling_(float4::ONE)
	{

	}

	void LocalCalculation()
	{
		LocalScaling_.Scaling(vLocalScaling_);
		LocalRotation_.RotationDeg(vLocalRotation_);
		LocalPosition_.Translation(vLocalPosition_);

		LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	}

	void ParentSetting(const float4x4& _Parent)
	{
		Parent_ = _Parent;
		WorldWorld_ = LocalWorld_;
		WorldWorld_ *= Parent_;
	}

	void RootCalculation()
	{
		WorldWorld_ = LocalWorld_;
	}
};

// 기능이란 
// 위치가 존재해야 한다. => 기능

// 어느 위치에 그려져야 한다. => 기능
// 어느 위치에서 다른 애들과 충돌해야 한다 => 기능

// 위치를 나타내는 기능이라 도저히 컴포넌트라고 부를수 없을정도로 중요하다.

// 충돌도 이녀석이 담당할것이기 때문에 어마어마하게 중요하고 잘만들어야 한다.
// 설명 :
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	void TransformUpdate();

	float4 GetLocalScaling() { return TransformData_.vLocalScaling_; }
	float4 GetWorldScaling() { return TransformData_.vWorldScaling_; }
	float4 GetLocalRotation() { return TransformData_.vLocalRotation_; }
	float4 GetWorldRotation() { return TransformData_.vWorldRotation_; }
	float4 GetLocalPosition() { return TransformData_.vLocalPosition_; }
	float4 GetWorldPosition() { return TransformData_.vWorldPosition_; }

	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0]
	// [0][0][0][1]

	float4 GetWorldForwardVector() { return TransformData_.WorldWorld_.vz.NormalizeReturn3D(); }
	float4 GetLocalForwardVector() { return TransformData_.LocalWorld_.vz.NormalizeReturn3D(); }
	float4 GetWorldRightVector() { return TransformData_.WorldWorld_.vx.NormalizeReturn3D(); }
	float4 GetLocalRightVector() { return TransformData_.LocalWorld_.vx.NormalizeReturn3D(); }
	float4 GetWorldUpVector() { return TransformData_.WorldWorld_.vy.NormalizeReturn3D(); }
	float4 GetLocalUpVector() { return TransformData_.LocalWorld_.vy.NormalizeReturn3D(); }



	void SetLocalScaling(const float4& _Value);
	void SetWorldScaling(const float4& _Value);

	// 무모건 디그리
	void SetLocalRotation(const float4& _Value);
	void SetWorldRotation(const float4& _Value);

	void SetLocalPosition(const float4& _Value);
	void SetWorldPosition(const float4& _Value);

	void DetachChildTransform(GameEngineTransform* _Child);
	void AttachTransform(GameEngineTransform* _Transform);

	TransformData& GetTransformData()
	{
		return TransformData_;
	}


protected:
	TransformData TransformData_;

	GameEngineTransform* Parent_;
	std::list<GameEngineTransform*> Childs_;

private:
	void AllChildCalculationScaling();
	void AllChildCalculationRotation();
	void AllChildCalculationPosition();

	void CalculationLocalScaling();
	void CalculationWorldScaling();

	void CalculationWorldRotation();
	void CalculationLocalRotation();

	void CalculationLocalPosition();
	void CalculationWorldPosition();



};

