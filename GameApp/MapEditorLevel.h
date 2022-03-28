#pragma once
#include <GameEngine/GameEngineLevel.h>

// �з� : 
// �뵵 : 
// ���� : 
class MapEditorLevel : public GameEngineLevel
{
private:	// member Var

public:
	MapEditorLevel(); // default constructer ����Ʈ ������
	~MapEditorLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MapEditorLevel(const MapEditorLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	MapEditorLevel(MapEditorLevel&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MapEditorLevel& operator=(const MapEditorLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MapEditorLevel& operator=(const MapEditorLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

};

