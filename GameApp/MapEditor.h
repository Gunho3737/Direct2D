#pragma once
#include <GameEngine/GameEngineGUI.h>

// 분류 : 
// 용도 : 
// 설명 : 
class MapEditor
{
private:	// member Var

public:
	MapEditor(); // default constructer 디폴트 생성자
	~MapEditor(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MapEditor(const MapEditor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MapEditor(MapEditor&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MapEditor& operator=(const MapEditor& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MapEditor& operator=(const MapEditor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

