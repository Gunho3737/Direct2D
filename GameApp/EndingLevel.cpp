#include "PreCompile.h"
#include "EndingLevel.h"

EndingLevel::EndingLevel() // default constructer ����Ʈ ������
{

}

EndingLevel::~EndingLevel() // default destructer ����Ʈ �Ҹ���
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