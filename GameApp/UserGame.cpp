#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

#include "TitleLevel.h"
#include "PlayLevel.h"

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

	LevelCreate<TitleLevel>("Title");
	LevelCreate<PlayLevel>("Play");
	LevelChange("Play");

	return;
}

void UserGame::Release()
{

}


//
//void UserGame::GameLoop()
//{
//	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
//	{
//		Pos.x += 0.001f;
//		TransData.Position.Translation(Pos);
//		TransData.CalWorld();
//
//
//		// 랜더링 파이프라인이 하나가 돌고
//		// 이안에 세팅정보가 존재하겠죠?
//		GameEngineDevice::RenderStart();
//
//		// 매프레임마다 세팅해줘야 하는게 되죠?
//		// 
//		Pipe->Rendering();
//		GameEngineDevice::RenderEnd();
//	}
//}
//
//
