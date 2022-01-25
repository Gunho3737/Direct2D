#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineReasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	float4x4 ViewPort;

public:
	void SetViewPort(float _ScreenX, float _ScreenY, float _StartX, float _StartY, float _MinZ, float _MaxZ)
	{
		ViewPort.ViewPortCenter(_ScreenX, _ScreenY, _StartX, _StartY, _MinZ, _MaxZ);
	}

public:
	void ReasterizerUpdate(float4& _Pos);


public:
	GameEngineReasterizer(); // default constructer 디폴트 생성자
	~GameEngineReasterizer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineReasterizer(const GameEngineReasterizer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineReasterizer(GameEngineReasterizer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineReasterizer& operator=(const GameEngineReasterizer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineReasterizer& operator=(const GameEngineReasterizer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

