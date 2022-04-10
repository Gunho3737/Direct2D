#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineImageRenderer;
class BitMap : public GameEngineActor
{
public:
	// constrcuter destructer
	BitMap();
	~BitMap();

	// delete Function
	BitMap(const BitMap& _Other) = delete;
	BitMap(BitMap&& _Other) noexcept = delete;
	BitMap& operator=(const BitMap& _Other) = delete;
	BitMap& operator=(BitMap&& _Other) noexcept = delete;

	GameEngineImageRenderer* ImageRenderer;

	static float4 GetColor(GameEngineTransform* _Ptr, bool YRevers = true);
	static float4 GetColor(float4 _Postion, bool YReverse = true);

	MapProgress Progress;

protected:
	//std::vector<GameEngineCollision> MapJumpCollision;
	GameEngineCollision* BenchNextCollision;
	GameEngineCollision* MiddleRoomNextCollision;
	GameEngineCollision* MiddleBossNextCollision;
	GameEngineCollision* FinalBossNextCollision;
			
	GameEngineCollision* MiddleRoomPrevCollision;
	GameEngineCollision* MiddleBossPrevCollision;
	GameEngineCollision* FinalBossPrevCollision;


	void Start() override;
	void LevelChangeStartEvent() override;
	void Update(float DeltaTime_) override;


private:
	static BitMap* CurrentMap;
	float4 RoomSkipCollsionSize;
};