#include "Actor.h"
#include "Model.h"

void Actor::Update(float dt)
{
	m_transform.position += (m_velocity * dt);
	m_velocity *= 1.0f / (1.0f + m_damping * dt);
}

void Actor::Draw(Renderer& renderer)
{
	if (m_model) // 0000000000 <- nullptr <- false
	{
		m_model->Draw(renderer, m_transform);
	}
}
