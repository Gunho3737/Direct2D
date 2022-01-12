#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"

GameEngineCore* GameEngineCore::MainCore_ = nullptr;

GameEngineCore::GameEngineCore() // default constructer 디폴트 생성자
{

}

GameEngineCore::~GameEngineCore() // default destructer 디폴트 소멸자
{

}

GameEngineCore::GameEngineCore(GameEngineCore&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineCore::MainLoop()
{
	GameEngineTime::GetInst().TimeCheck();
	GameEngineSoundManager::GetInst().SoundUpdate();
	MainCore_->GameLoop();

}

void GameEngineCore::WindowCreate()
{
	GameEngineWindow::GetInst().CreateMainWindow("MyWindow", { 800, 600 }, { 0, 0 });
}

void GameEngineCore::Loop()
{
	GameEngineWindow::GetInst().Loop(&GameEngineCore::MainLoop);
}



void GameEngineCore::EngineDestroy()
{
	Death();
}