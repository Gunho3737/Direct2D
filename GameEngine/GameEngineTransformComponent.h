#pragma once
#include "GameEngineComponent.h"

// Ό³Έν :
class GameEngineTransform;
class GameEngineTransformComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineTransformComponent();
	~GameEngineTransformComponent();

	// delete Function
	GameEngineTransformComponent(const GameEngineTransformComponent& _Other) = delete;
	GameEngineTransformComponent(GameEngineTransformComponent&& _Other) noexcept = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _Other) = delete;
	GameEngineTransformComponent& operator=(GameEngineTransformComponent&& _Other) noexcept = delete;

protected:

private:
	GameEngineTransform* Transform;

	virtual void InitComponent(GameEngineActor* Actor_);
};

