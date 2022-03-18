#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class Map
{
private:	// member Var

public:
	Map(); // default constructer 디폴트 생성자
	~Map(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Map(const Map& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Map(Map&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Map& operator=(const Map& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Map& operator=(const Map&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

