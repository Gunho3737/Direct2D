#pragma once
#include "GameEngineRenderer.h"

// 설명 : 하나의 랜더 단위를 표현합니다.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineRenderer
{
private:
	friend GameEngineLevel;
	friend CameraComponent;

public:
	// constrcuter destructer
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

	// delete Function
	GameEngineUIRenderer(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer(GameEngineUIRenderer&& _Other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer& operator=(GameEngineUIRenderer&& _Other) noexcept = delete;

protected:


private:
	void Start() override;
};

