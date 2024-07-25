#include "Scene.h"
#include "Actor.h"
#include "Model.h"
#include <algorithm>

void Scene::Update(float dt)
{
	// update
	for (auto& actor : m_actors)
	{
		actor->Update(dt);
	}

	// destroy
	//auto iter = m_actors.begin();
	//while (iter != m_actors.end())
	//{
	//	iter = ((*iter)->m_destroyed) ? m_actors.erase(iter) : ++iter;
	//}

	// The std::remove_if algorithm reorders the elements in the range [m_actors.begin(), m_actors.end()]
	// such that the elements that satisfy the predicate (i.e., those that should be removed) are moved
	// to the end of the range. The algorithm returns an iterator to the beginning of the "removed" range,
	// which is the new logical end of the container.
	//m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [](Actor* actor) { return actor->m_destroyed; }), m_actors.end());
	std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });

	// collision
	for (auto& actor1 : m_actors)
	{
		for (auto& actor2 : m_actors)
		{
			if (actor1 == actor2 || (actor1->m_destroyed || actor2->m_destroyed)) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();
			float radius = actor1->GetRadius() + actor2->GetRadius();

			if (distance <= radius)
			{
				actor1->OnCollision(actor2.get());
				actor2->OnCollision(actor1.get());
			}
		}
	}
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : m_actors)
	{
		actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->m_scene = this;
	m_actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	m_actors.clear();
}
