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



UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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