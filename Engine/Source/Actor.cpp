#include "Actor.h"
#include "Model.h"

void Actor::Update(float dt)
{
	// check for lifespan
	if (m_lifespan != 0)
	{
		m_lifespan -= dt;
		if (m_lifespan <= 0)
		{
			m_destroyed = true;
		}
	}
	
	// acceleration = F + F + F
	// velocity += acceleration * dt
	// position += velocity * dt

	m_transform.position += (m_velocity * dt);
	m_velocity *= 1.0f / (1.0f + m_damping * dt);
}

void Actor::Draw(Renderer& renderer)
{
	if (m_destroyed) return;

	if (m_model) // 0000000000 <- nullptr <- false
	{
		m_model->Draw(renderer, m_transform);
	}
}
