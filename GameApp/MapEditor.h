#pragma once
#include <GameEngine/GameEngineGUI.h>

// �з� : 
// �뵵 : 
// ���� : 
class MapEditor
{
private:	// member Var

public:
	MapEditor(); // default constructer ����Ʈ ������
	~MapEditor(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MapEditor(const MapEditor& _other) = delete; // default Copy constructer ����Ʈ ���������
	MapEditor(MapEditor&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MapEditor& operator=(const MapEditor& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MapEditor& operator=(const MapEditor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

