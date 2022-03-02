#pragma once
#include "GameEngineRenderer.h"


// 설명 :
class GameEngineTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
private:
	struct Animation2D
	{
		GameEngineTexture* Textrue_;
		float InterTime_;
		float CurTime_;

		bool IsEnd;
		bool Loop_;
		int CurFrame_;
		int StartFrame_;
		int EndFrame_;

		GameEngineImageRenderer* Renderer;

		std::map<int, std::vector<std::function<void()>>> FrameCallBack_;
		std::vector<std::function<void()>> EndCallBack_;
		std::vector<std::function<void()>> StartCallBack_;

	public:
		void Reset();
		void CallStart();
		void CallEnd();
		void CallFrame();
		void Update(float _DeltaTime);
	};

public:
	// constrcuter destructer
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

	// delete Function
	GameEngineImageRenderer(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer(GameEngineImageRenderer&& _Other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer& operator=(GameEngineImageRenderer&& _Other) noexcept = delete;

	void SetImage(const std::string& _ImageName);
	void SetImage(const std::string& _ImageName, GameEngineTransform* _transform);


	void SetIndex(const int Index);

	void CreateAnimation(const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);

	// _IsForce 같은 애니메이션 인데도 바꿀거냐? true 바꾼다.
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);

	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);


protected:
	void Update(float _DeltaTime) override;


private:
	std::map<std::string, Animation2D*> AllAnimations_;
	Animation2D* CurAnimation_;

	float4 CutData;
	GameEngineTexture* CurTexture;
	void Start() override;

};



