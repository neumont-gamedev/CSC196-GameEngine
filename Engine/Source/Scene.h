#pragma once
#include <list>

class Renderer;
class Actor;

class Scene
{
public:
	Scene() = default;

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(Actor* actor);

protected:
	std::list<Actor* > m_actors;
};