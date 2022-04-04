#pragma once
#include "GameEnginePostProcessRender.h"

struct FadeData
{
	float Dir;// 1
	float Speed; // 
	int Clip; // 1 ������ 0�� �ֵ��� ���Ѵ�.
			  // 0 ������ 0�� �ֵ��� �Ѵ�.

	int Temp;

	FadeData()
		: Dir(1),
		Speed(10.0f),
		Clip(0)

	{

	}
};

// ���� :
class PostFade : public GameEnginePostProcessRender
{
public:
	// constrcuter destructer
	PostFade(float _Dir,// 1
		float Speed, // 
		int Clip = 0);
	~PostFade();

	// delete Function
	PostFade(const PostFade& _Other) = delete;
	PostFade(PostFade&& _Other) noexcept = delete;
	PostFade& operator=(const PostFade& _Other) = delete;
	PostFade& operator=(PostFade&& _Other) noexcept = delete;

protected:
	void Effect() override;


private:

	FadeData Data;

};

