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

// ����̶� 
// ��ġ�� �����ؾ� �Ѵ�. => ���

// ��� ��ġ�� �׷����� �Ѵ�. => ���
// ��� ��ġ���� �ٸ� �ֵ�� �浹�ؾ� �Ѵ� => ���

// ��ġ�� ��Ÿ���� ����̶� ������ ������Ʈ��� �θ��� ���������� �߿��ϴ�.

// ���� :
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

	void SetLocalScaling(const float4& _Value);
	void SetWorldScaling(const float4& _Value);

	// ����� ��׸�
	void SetLocalRotation(const float4& _Value);
	void SetWorldRotation(const float4& _Value);

	void SetLocalPosition(const float4& _Value);
	void SetWorldPosition(const float4& _Value);

protected:
	TransformData TransData_;

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


	void SetParent(GameEngineTransform* _Parent);
	void DetachChild(GameEngineTransform* _Child);

};

