#pragma once
#include "GameEngineBase\GameEngineObjectNameBase.h"
#include <vector>
#include "imgui.h"

// Ό³Έν :
class GameEngineGUIWindow;
class GameEngineGUI
{
	friend class GameEngineCore;
	friend class GameEngineLevel;
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
	template<typename WindowType>
	WindowType* CreateGUIWindow(const std::string& _Name)
	{
		WindowType* NewWindow = new WindowType();

		NewWindow->SetName(_Name);

		Windows_.insert(std::map<std::string, GameEngineGUIWindow*>::value_type(_Name, NewWindow));

		return NewWindow;
	}

	GameEngineGUIWindow* FindGUIWindow(const std::string& _Name)
	{
		std::map<std::string, GameEngineGUIWindow*>::iterator FindIter = Windows_.find(_Name);

		if (FindIter == Windows_.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

protected:


private:
	std::map<std::string, GameEngineGUIWindow*> Windows_;

	void Initialize();
	void GUIRenderStart();
	void GUIRenderEnd();

	// constrcuter destructer
	GameEngineGUI();
	~GameEngineGUI();

	// delete Function
	GameEngineGUI(const GameEngineGUI& _Other) = delete;
	GameEngineGUI(GameEngineGUI&& _Other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _Other) = delete;
	GameEngineGUI& operator=(GameEngineGUI&& _Other) noexcept = delete;

};



class GameEngineGUIWindow : public GameEngineObjectNameBase
{
	friend GameEngineGUI;

public:


	void Begin()
	{
		ImGui::Begin(GetName().c_str(), &GetIsUpdateRef());
	}

	virtual void OnGUI() = 0;

	void End()
	{
		ImGui::End();
	}


	// constrcuter destructer
	GameEngineGUIWindow();
	~GameEngineGUIWindow();
private:

	// delete Function
	GameEngineGUIWindow(const GameEngineGUIWindow& _Other) = delete;
	GameEngineGUIWindow(GameEngineGUIWindow&& _Other) noexcept = delete;
	GameEngineGUIWindow& operator=(const GameEngineGUIWindow& _Other) = delete;
	GameEngineGUIWindow& operator=(GameEngineGUIWindow&& _Other) noexcept = delete;

};