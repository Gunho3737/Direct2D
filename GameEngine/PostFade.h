#pragma once
#include "GameEnginePostProcessRender.h"

struct FadeData
{
	float Dir;// 1
	float Speed; // 
	int Clip; // 1 투명도가 0인 애들은 안한다.
			  // 0 투명도가 0인 애들은 한다.

	int Temp;

	FadeData()
		: Dir(1),
		Speed(10.0f),
		Clip(0)

	{

	}
};

// 설명 :
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

