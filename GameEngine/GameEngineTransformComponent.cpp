#include "PreCompile.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"

GameEngineTransformComponent::GameEngineTransformComponent()
{
}

GameEngineTransformComponent::~GameEngineTransformComponent()
{
}

void GameEngineTransformComponent::InitComponent(GameEngineActor* Actor_)
{
	GameEngineComponent::InitComponent(Actor_);

	Transform = new GameEngineTransform();

}