#include "Engine\Core\MiniginPCH.h"
#include "LevelManager.h"
#include "Factory.h"

void LevelManager::Notify(const MyEngine::Event event, const int value, const MyEngine::GameObject* object)
{
	switch (event)
	{
	case(IncreaseLevel):
		if (m_CurrentLevel == 99)
		{
			Notify(MyEngine::Event(GoBackToMenu), value, object);
			break;
		}
		DataHolder::GetInstance()->RemoveAllEnemies();
		CreateLevel(m_CurrentLevel + 1, DataHolder::GetInstance()->GetLevel(m_CurrentLevel).WindowHeight, 4.0f);
		break;
	case(GoBackToMenu):
		DataHolder::GetInstance()->RemoveAllEnemies();
		SceneManager::GetInstance()->SetSceneActive("MenuScene");
		m_CurrentLevel = 0;
		break;
	case(ReloadLevel):
		DataHolder::GetInstance()->RemoveAllEnemies();
		SceneManager::GetInstance()->SetSceneActive("BufferScene");
		SceneManager::GetInstance()->GetActiveScene()->Invoke([this]() { CreateLevel(m_CurrentLevel, DataHolder::GetInstance()->GetLevel(m_CurrentLevel).WindowHeight, 0.0f); m_CurrentLevel--; }, 0.0f);
		break;
	}
}
