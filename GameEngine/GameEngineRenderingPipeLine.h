#pragma once
#include <GameEngine/GameEngineDevice.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineShaderResHelper.h"



// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineBlend;
class GameEngineShader;
class GameEngineConstantBuffer;
class GameEngineIndexBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEnginePixelShader;
class GameEngineRasterizer;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
private:	// member Var
	// IA1
	GameEngineVertexBuffer* VertexBuffer_;
	// IA1
	GameEngineVertexShader* InputLayOutVertexShader_;
	// VS
	GameEngineVertexShader* VertexShader_;
	// IA2
	GameEngineIndexBuffer* IndexBuffer_;
	// IA2
	D3D11_PRIMITIVE_TOPOLOGY Topology_;
	// RS
	GameEngineRasterizer* Rasterizer_;
	// PS
	GameEnginePixelShader* PixelShader_;
	// Blend
	GameEngineBlend* Blend_;
	// OM
	GameEngineRenderTarget* RenderTarget_;

public:
	inline GameEnginePixelShader* GetPixelShader() const
	{
		return PixelShader_;
	}

	inline GameEngineVertexShader* GetVertexShader() const
	{
		return VertexShader_;
	}

	void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);

	void SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY Topology_);

	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void RenderingPipeLineSetting();

	void Rendering();

	void Reset();

public:
	GameEngineRenderingPipeLine(); // default constructer 디폴트 생성자
	~GameEngineRenderingPipeLine(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

	void InputAssembler1();
	void InputAssembler2();
	void VertexShader();
	void Rasterizer();
	void PixelShader();
	void OutPutMerger();


};

