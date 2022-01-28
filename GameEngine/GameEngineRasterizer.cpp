#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() // default constructer 디폴트 생성자
{

}

GameEngineRasterizer::~GameEngineRasterizer() // default destructer 디폴트 소멸자
{

}

GameEngineRasterizer::GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



void GameEngineRasterizer::ReasterizerUpdate(float4& _Pos)
{
	// 실제 복사 받은 녀석들이 들어오는데 저는 보여주기 위해서 그냥 여기서 하겠습니다.
	_Pos.x /= _Pos.w;
	_Pos.y /= _Pos.w;
	_Pos.z /= _Pos.w;
	_Pos.w = 1.0f;


	// 여기서 2차원이 되는 겁니다.
	_Pos *= ViewPort;

	// _Pos * ViewPort;
}