#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"

GameEngineCore* GameEngineCore::MainCore_ = nullptr;

GameEngineCore::GameEngineCore() // default constructer ����Ʈ ������
{

}

GameEngineCore::~GameEngineCore() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineCore::GameEngineCore(GameEngineCore&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void GameEngineCore::MainLoop()
{
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