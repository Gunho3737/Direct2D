#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class GameEngineImageRenderer;
class UI_HpBar : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_HpBar();
	~UI_HpBar();

	// delete Function
	UI_HpBar(const UI_HpBar& _Other) = delete;
	UI_HpBar(UI_HpBar&& _Other) noexcept = delete;
	UI_HpBar& operator=(const UI_HpBar& _Other) = delete;
	UI_HpBar& operator=(UI_HpBar&& _Other) noexcept = delete;

protected:
	GameEngineImageRenderer* UIRenderer;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

};

