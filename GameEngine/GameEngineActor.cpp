#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor()
	: Level(nullptr)
{
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