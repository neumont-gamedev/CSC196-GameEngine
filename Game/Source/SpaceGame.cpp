#include "SpaceGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

bool SpaceGame::Initialize()
{
    m_scene = new Scene();

    return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
    switch (m_state)
    {
    case eState::Title:
        if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StartGame;
        }
        break;
    case eState::StartGame:
        m_score = 0;
        m_state = eState::StartLevel;
        break;
    case eState::StartLevel:
        {
            Transform transform{ Vector2{ 400, 300 }, 0, 3 };
            Model* model = new Model{ GameData::shipPoints, Color{ 1, 0, 0 } };
            Player* player = new Player(800, transform, model);
            player->SetDamping(2.0f);
            player->SetTag("Player");
            m_scene->AddActor(player);
        }

        m_spawnTime = 3;
        m_spawnTimer = m_spawnTime;

        m_state = eState::Game;
        break;
    case eState::Game:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            m_spawnTime -= 0.2f;
            m_spawnTimer = m_spawnTime;

            auto* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 0, 1 } };
            auto* enemy = new Enemy(400, Transform{ { g_engine.GetRenderer().GetWidth(),  g_engine.GetRenderer().GetHeight() }, 0, 2 }, enemyModel);
            enemy->SetDamping(1.0f);
            enemy->SetTag("Enemy");
            m_scene->AddActor(enemy);
        }

        break;
    case eState::PlayerDead:
        break;
    case eState::GameOver:
        break;
    default:
        break;
    }


    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    switch (m_state)
    {
    case SpaceGame::eState::Title:
        // draw text "Game Title"
        break;
    case SpaceGame::eState::GameOver:
        // draw text "Game Over"
        break;
    default:
        break;
    }

    // draw score
    // draw lives

    m_scene->Draw(renderer);
}
