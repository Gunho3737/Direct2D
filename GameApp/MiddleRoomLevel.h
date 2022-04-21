#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Player;
class BitMap;
class MiddleRoomLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MiddleRoomLevel();
	~MiddleRoomLevel();

	// delete Function
	MiddleRoomLevel(const MiddleRoomLevel& _Other) = delete;
	MiddleRoomLevel(MiddleRoomLevel&& _Other) noexcept = delete;
	MiddleRoomLevel& operator=(const MiddleRoomLevel& _Other) = delete;
	MiddleRoomLevel& operator=(MiddleRoomLevel&& _Other) noexcept = delete;

	class PostFade* FadeEffect;

	void FadeOn() override;
	void FadeOff() override;

	static std::string PrevLevel;

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

