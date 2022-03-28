#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 
// 용도 : 
// 설명 : 
class MapEditorLevel : public GameEngineLevel
{
private:	// member Var

public:
	MapEditorLevel(); // default constructer 디폴트 생성자
	~MapEditorLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MapEditorLevel(const MapEditorLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MapEditorLevel(MapEditorLevel&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MapEditorLevel& operator=(const MapEditorLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MapEditorLevel& operator=(const MapEditorLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

};

