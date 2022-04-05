#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Player;
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

protected:
	Player* PlayerActor;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

};

