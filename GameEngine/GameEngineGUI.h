#pragma once

// Ό³Έν :
class GameEngineGUI
{
private:
	static GameEngineGUI* Inst_;

public:
	inline static GameEngineGUI* GetInst() 
	{
		return Inst_;
	}

	static void Destroy() 
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}


public:
	void Initialize();

	void GUIRenderStart();


	void GUIRenderEnd();

protected:

private:
	// constrcuter destructer
	GameEngineGUI();
	~GameEngineGUI();

	// delete Function
	GameEngineGUI(const GameEngineGUI& _Other) = delete;
	GameEngineGUI(GameEngineGUI&& _Other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _Other) = delete;
	GameEngineGUI& operator=(GameEngineGUI&& _Other) noexcept = delete;

};

