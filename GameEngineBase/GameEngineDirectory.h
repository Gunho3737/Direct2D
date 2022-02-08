#pragma once
#include "GameEnginePath.h"
// �з� :
// �뵵 :
// ���� :

class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	GameEngineDirectory(); // default constructer ����Ʈ ������
	~GameEngineDirectory(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineDirectory(const GameEngineDirectory& _other); // default Copy constructer ����Ʈ ���������
	GameEngineDirectory(GameEngineDirectory&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineDirectory& operator=(const GameEngineDirectory& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDirectory& operator=(const GameEngineDirectory&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	std::string DirectroyName();

public:		//member Func
	//C:\ �� D:\ �� ���� ���� �⺻ ���͸����� Ȯ��
	bool IsRoot();

	//���� ������ �̵�
	void MoveParent();

	//���� ������ _DirName��� �̸��� ���� ������ �̵�
	bool MoveParent(const std::string& _DirName);

	//���� ������ _DirName��� �̸��� ���� ������ �̵�
	bool MoveChild(const std::string& _DirName);

public:
	std::string PathToPlusFileName(const std::string& _DirName);


	std::vector<GameEngineFile> GetAllFile(const std::string& _filter = "*");
};

