#include "PreCompile.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"

GameEngineTransformComponent::GameEngineTransformComponent() 
{
	Transform_ = new GameEngineTransform();
}

GameEngineTransformComponent::~GameEngineTransformComponent() 
{
	if (nullptr != Transform_)
	{
		delete Transform_;
		Transform_ = nullptr;
	}
}




void GameEngineTransformComponent::AttachTransform(GameEngineTransform* _Parent)
{
	Transform_->AttachTransform(_Parent);
}