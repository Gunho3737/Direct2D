#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "MapEditorLevel.h"

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
	//TransData.View.ViewToLH( { 0.0f, 0.0f, -10.0f }, {0.0f, 0.0f , 1.0f}, {0.0f, 1.0f , 0.0f});

	//TransData.Proj.OrthographicLH( 1280.f, 720.f, 0.1f, 1000.0f );


	//TransData.Scale.Scaling2D(200.0f);
	//TransData.Rotation.RotationDeg({ 0.0f, 0.0f, 45.0f });
	//TransData.Position.Translation({ 0.0f, 0.0f, 0.0f });
	//TransData.CalWorld();

	//GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	//Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);
	//GameEngineInput::GetInst().HideCursor();

	LevelCreate<TitleLevel>("Title");
	LevelCreate<MapEditorLevel>("MapEditor");
	LevelCreate<PlayLevel>("Play");
	LevelCreate<EndingLevel>("Ending");

	LevelChange("Play");

	return;
}

void UserGame::Release()
{

}
