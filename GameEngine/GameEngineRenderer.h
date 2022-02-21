#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// ���� : �ϳ��� ���� ������ ǥ���մϴ�.
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
private:
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetRenderingPipeLine(const std::string& _Value);

	GameEngineShaderResHelper ShaderHelper;

protected:
	GameEngineRenderingPipeLine* PipeLine_;


private:
	void Start() override;
	void Update() override;

	virtual void Render();

};

