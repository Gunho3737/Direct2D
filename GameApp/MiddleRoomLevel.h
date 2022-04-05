#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class MiddleRoomLevel
{
private:	// member Var

public:
	MiddleRoomLevel(); // default constructer 디폴트 생성자
	~MiddleRoomLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MiddleRoomLevel(const MiddleRoomLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MiddleRoomLevel(MiddleRoomLevel&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MiddleRoomLevel& operator=(const MiddleRoomLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MiddleRoomLevel& operator=(const MiddleRoomLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

