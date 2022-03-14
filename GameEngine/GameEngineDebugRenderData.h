#pragma once
#include "GameEngineTransform.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// Ό³Έν :
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineDebugRenderData
{
	friend class CameraComponent;

public:
	// constrcuter destructer
	GameEngineDebugRenderData();
	~GameEngineDebugRenderData();

	// delete Function
	GameEngineDebugRenderData(const GameEngineDebugRenderData& _Other)
		: Data(_Other.Data)
		, ShaderHelper(_Other.ShaderHelper)
		, PipeLine_(_Other.PipeLine_)
	{

	}
	// GameEngineDebugRenderData(GameEngineDebugRenderData&& _Other) noexcept = delete;
	// GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData& _Other) = delete;
	// GameEngineDebugRenderData& operator=(GameEngineDebugRenderData&& _Other) noexcept = delete;

protected:

private:
	TransformData Data;
	GameEngineShaderResHelper ShaderHelper;
	GameEngineRenderingPipeLine* PipeLine_;

};

