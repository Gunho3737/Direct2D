#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine\EngineVertex.h>
#include "UserGame_Resources_Shader.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent("LGH_HollowKnight");
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
		TextureDir.MoveParent("LGH_HollowKnight");
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
		TextureDir.MoveParent("LGH_HollowKnight");
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
		TextureDir.MoveParent("LGH_HollowKnight");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("UI");

		
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("HealthIdle"));

	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("LGH_HollowKnight");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Knight");

		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Idle"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Run"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Slash"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("SlashEffect"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("UpSlash"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("UpSlashEffect"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("DownSlash"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("DownSlashEffect"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("IdleToRun"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("RunToIdle"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Jump"));
		GameEngineFolderTextureManager::GetInst().Load(TextureDir.PathToPlusFileName("Airborne"));
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("LGH_HollowKnight");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("Map");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}


		GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("fog.png");
		Texture->Cut(5, 4);
	}

	{
		GameEngineDirectory TextureDir;
		TextureDir.MoveParent("LGH_HollowKnight");
		TextureDir.MoveChild("Resources");
		TextureDir.MoveChild("Image");
		TextureDir.MoveChild("TitleScreen");

		std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}

	}





	AppShaderLoad();
}
