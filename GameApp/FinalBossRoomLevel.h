#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Player;
class BitMap;
class FinalBoss;
class Door;
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

public:
	void CameraUp();
	void CameraDown();

	static bool BossBattleOn;

protected:
	Player* PlayerActor;
	BitMap* BitMapActor;
	FinalBoss* FinalBossActor;
	float4 PlayerPos;
	Door* BossBlockDoor;
	Door* EndingBlockDoor;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;



};

