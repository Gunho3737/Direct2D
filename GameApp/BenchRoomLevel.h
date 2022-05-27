#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Player;
class BitMap;
class ViewMap;
class JumpBug;
class BenchRoomLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BenchRoomLevel();
	~BenchRoomLevel();

	// delete Function
	BenchRoomLevel(const BenchRoomLevel& _Other) = delete;
	BenchRoomLevel(BenchRoomLevel&& _Other) noexcept = delete;
	BenchRoomLevel& operator=(const BenchRoomLevel& _Other) = delete;
	BenchRoomLevel& operator=(BenchRoomLevel&& _Other) noexcept = delete;

	class PostFade* FadeEffect;

	void FadeOn() override;
	void FadeOff() override;

	static GameEngineSoundPlayer* PlayLevelBackGroundSoundPlayer;

protected:
	Player* PlayerActor;
	BitMap* BitMapActor;
	ViewMap* VieMapActor;
	JumpBug* JumpActor;


	float4 PlayerPos;
	bool Reverse;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

};

