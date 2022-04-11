#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Player;
class BitMap;
class FinalBossRoomLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	FinalBossRoomLevel();
	~FinalBossRoomLevel();

	// delete Function
	FinalBossRoomLevel(const FinalBossRoomLevel& _Other) = delete;
	FinalBossRoomLevel(FinalBossRoomLevel&& _Other) noexcept = delete;
	FinalBossRoomLevel& operator=(const FinalBossRoomLevel& _Other) = delete;
	FinalBossRoomLevel& operator=(FinalBossRoomLevel&& _Other) noexcept = delete;

	class PostFade* FadeEffect;

	void FadeOn() override;
	void FadeOff() override;

protected:
	Player* PlayerActor;
	BitMap* BitMapActor;
	float4 PlayerPos;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;



};

