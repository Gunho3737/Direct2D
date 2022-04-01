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

	MapProgress Progress;

	static float4 GetColor(GameEngineTransform* _Ptr, bool YRevers = true);

	static float4 GetColor(float4 _Postion, bool YReverse = true);

protected:

	void Start() override;
	void LevelChangeStartEvent() override;



private:
	static BitMap* CurrentMap;
};