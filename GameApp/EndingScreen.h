#pragma once
#include <GameEngine/GameEngineActor.h>


// �з� : 
// �뵵 : 
// ���� : 
class GameEngineSoundPlayer;
class EndingScreen : public GameEngineActor
{
private:	// member Var

public:
	EndingScreen(); // default constructer ����Ʈ ������
	~EndingScreen(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;

	static GameEngineSoundPlayer* EndingBackGroundPlayer;

protected:		// delete constructer
	EndingScreen(const EndingScreen& _other) = delete; // default Copy constructer ����Ʈ ���������
	EndingScreen(EndingScreen&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	EndingScreen& operator=(const EndingScreen& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EndingScreen& operator=(const EndingScreen&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

