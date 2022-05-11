#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
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

	int HP;

protected:

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* HPBarRenderer;
	GameEngineUIRenderer* HPIconRenderer1;
	GameEngineUIRenderer* HPIconRenderer2;
	GameEngineUIRenderer* HPIconRenderer3;
	GameEngineUIRenderer* HPIconRenderer4;
	GameEngineUIRenderer* HPIconRenderer5;
};

