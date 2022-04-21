#include "PreCompile.h"
#include "EndingLevel.h"

EndingLevel::EndingLevel() // default constructer 디폴트 생성자
{

}

EndingLevel::~EndingLevel() // default destructer 디폴트 소멸자
{

}

void EndingLevel::LevelStart()
{}

void EndingLevel::LevelUpdate(float _DeltaTime)
{}

void EndingLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{}

void EndingLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{}

void EndingLevel::FadeOn()
{}

void EndingLevel::FadeOff()
{}