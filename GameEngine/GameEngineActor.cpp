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

}

void GameEngineActor::SetLevel(GameEngineLevel* _Level) 
{
	Level = _Level;
}

void GameEngineActor::Update(float _DeltaTime)
{

}