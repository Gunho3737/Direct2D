#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine\EngineVertex.h>
#include "UserGame_Resources_Shader.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent("Direct2D");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().Load(AllFile[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("Direct2D");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Monster");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}

		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("FlyBug.png");
		Texture->Cut(5, 5);
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("Direct2D");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("UI");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}

	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("Direct2D");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("UI");

		
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("HealthIdle"));

	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("Direct2D");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Knight");

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Idle"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Run"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Slash"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("SlashEffect"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("IdleToRun"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("RunToIdle"));
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("Direct2D");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Map");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}

	}





	AppShaderLoad();
}
