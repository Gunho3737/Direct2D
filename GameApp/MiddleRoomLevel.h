#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class MiddleRoomLevel
{
private:	// member Var

public:
	MiddleRoomLevel(); // default constructer ����Ʈ ������
	~MiddleRoomLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MiddleRoomLevel(const MiddleRoomLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	MiddleRoomLevel(MiddleRoomLevel&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MiddleRoomLevel& operator=(const MiddleRoomLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MiddleRoomLevel& operator=(const MiddleRoomLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

