#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class Map
{
private:	// member Var

public:
	Map(); // default constructer ����Ʈ ������
	~Map(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Map(const Map& _other) = delete; // default Copy constructer ����Ʈ ���������
	Map(Map&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Map& operator=(const Map& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Map& operator=(const Map&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

