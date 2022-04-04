#include "PreCompile.h"
#include "PostFade.h"

PostFade::PostFade(float _Dir,// 1
	float _Speed, // 
	int _Clip /*= 0*/)
{
	Data.Dir = _Dir;
	Data.Speed = _Speed;
	Data.Clip = _Clip;
}

PostFade::~PostFade()
{
}



void PostFade::Effect()
{

}