#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
	, Transform_(nullptr)
{
	Transform_ = new GameEngineTransform();
}

GameEngineActor::~GameEngineActor()
{
	if (nullptr != Transform_)
	{
		delete Transform_;
		Transform_ = nullptr;
	}
}

void GameEngineActor::SetLevel(GameEngineLevel* _Level)
{
	Level_ = _Level;
}

void GameEngineActor::Update(float _DeltaTime)
{

}