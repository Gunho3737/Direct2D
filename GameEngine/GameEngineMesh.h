#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineMesh
{
private:	// member Var

public:
	GameEngineMesh(); // default constructer ����Ʈ ������
	~GameEngineMesh(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineMesh(const GameEngineMesh& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineMesh(GameEngineMesh&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

