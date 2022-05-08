#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>
#include <GameEngine\GameEngineLevelControlWindow.h>
#include <GameEngine\GameEngineRenderWindow.h>

#include "TitleLevel.h"
#include "BenchRoomLevel.h"
#include "MiddleRoomLevel.h"
#include "MiddleBossRoomLevel.h"
#include "FinalBossRoomLevel.h"
#include "EndingLevel.h"

std::atomic<int> UserGame::LoadingFolder = 0;



UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}


void UserGame::Initialize()
{

	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineLevelControlWindow>("LevelControlWindow");
	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineRenderWindow>("RenderWindow");

	LevelCreate<TitleLevel>("Title");
	LevelCreate<BenchRoomLevel>("BenchRoom");
	LevelCreate<MiddleRoomLevel>("MiddleRoom");
	LevelCreate<MiddleBossRoomLevel>("MiddleBossRoom");
	LevelCreate<FinalBossRoomLevel>("FinalBossRoom");
	LevelCreate<EndingLevel>("Ending");

	LevelChange("Title");

	return;
}

void UserGame::Release()
{

}