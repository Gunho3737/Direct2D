#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11RasterizerState* State;
	D3D11_VIEWPORT ViewPort;

public:
	void SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth)
	{
		ViewPort.Height = _Height;
		ViewPort.Width = _Width;
		ViewPort.TopLeftX = _TopLeftX;
		ViewPort.TopLeftY = _TopLeftY;
		ViewPort.MinDepth = _MinDepth;
		ViewPort.MaxDepth = _MaxDepth;
	}

public:
	void Create(const D3D11_RASTERIZER_DESC& _Value);

public:
	GameEngineRasterizer(); // default constructer 디폴트 생성자
	~GameEngineRasterizer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SettingViewPort();

	void Setting();
};

