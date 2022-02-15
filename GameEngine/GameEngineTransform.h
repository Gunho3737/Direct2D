#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"

class TransformData 
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
};

// 기능이란 
// 위치가 존재해야 한다. => 기능

// 어느 위치에 그려져야 한다. => 기능
// 어느 위치에서 다른 애들과 충돌해야 한다 => 기능

// 위치를 나타내는 기능이라 도저히 컴포넌트라고 부를수 없을정도로 중요하다.

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

protected:
	TransformData TransData_;

	GameEngineTransform* Parent_;
	std::list<GameEngineTransform*> Childs_;

private:
	void SetParent(GameEngineTransform* _Parent);

	void DetachChild(GameEngineTransform* _Child);

};

