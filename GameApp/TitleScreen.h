#pragma once
#include <GameEngine/GameEngineActor.h>


// �з� : 
// �뵵 : 
// ���� : 
class TitleScreen : public GameEngineActor
{
private:	// member Var

public:
	TitleScreen(); // default constructer ����Ʈ ������
	~TitleScreen(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* BackGroundImageRenderer;
	GameEngineImageRenderer* LogoImageRenderer;

protected:		// delete constructer
	TitleScreen(const TitleScreen& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleScreen(TitleScreen&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TitleScreen& operator=(const TitleScreen& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleScreen& operator=(const TitleScreen&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

