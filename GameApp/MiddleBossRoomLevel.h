#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Player;
class BitMap;
class MiddleBossRoomLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MiddleBossRoomLevel();
	~MiddleBossRoomLevel();

	// delete Function
	MiddleBossRoomLevel(const MiddleBossRoomLevel& _Other) = delete;
	MiddleBossRoomLevel(MiddleBossRoomLevel&& _Other) noexcept = delete;
	MiddleBossRoomLevel& operator=(const MiddleBossRoomLevel& _Other) = delete;
	MiddleBossRoomLevel& operator=(MiddleBossRoomLevel&& _Other) noexcept = delete;

	class PostFade* FadeEffect;

	void FadeOn() override;
	void FadeOff() override;

protected:
	Player* PlayerActor;
	BitMap* BitMapActor;
	float4 PlayerPos;

	bool Reverse;
private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;



};

