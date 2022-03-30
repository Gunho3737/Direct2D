#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class GameEngineImageRenderer;
class ViewMap : public GameEngineActor
{
public:
	// constrcuter destructer
	ViewMap();
	~ViewMap();
	

	// delete Function
	ViewMap(const ViewMap& _Other) = delete;
	ViewMap(ViewMap&& _Other) noexcept = delete;
	ViewMap& operator=(const ViewMap& _Other) = delete;
	ViewMap& operator=(ViewMap&& _Other) noexcept = delete;

	GameEngineImageRenderer* ImageRenderer;


protected:

	void Start() override;
	void LevelChangeStartEvent() override;



private:

};