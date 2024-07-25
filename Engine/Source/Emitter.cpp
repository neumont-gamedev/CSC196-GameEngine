#include "Emitter.h"
#include "Particle.h"
#include "Random.h"
#include "Engine.h"

void Emitter::Update(float dt)
{
	// create burst particles
	if (m_data.burst)
	{
		m_data.burst = false;
		for (int i = 0; i < m_data.burstCount; i++)
		{
			Emit();
		}
	}

	// create particles based on rate
	if (m_data.spawnRate > 0.0f)
	{
		m_data.spawnRateTimer += dt;
		while (m_data.spawnRateTimer >= 0)
		{
			Emit();
			m_data.spawnRateTimer -= (1 / m_data.spawnRate);
		}
	}

	Actor::Update(dt);
}

void Emitter::Emit()
{
	// find free particle in paricle system
	Particle* particle = g_engine.GetPS().GetFreeParticle();

	if (particle)
	{
		// set particle data from emitter data
		Particle::Data data;
		data.lifespan = randomf(m_data.lifetimeMin, m_data.lifetimeMax);
		data.position = m_transform.position;
		data.color = m_data.color;

		float angle = m_transform.rotation + m_data.angle + randomf(-m_data.angleRange, m_data.angleRange);
		Vector2 direction = Vector2{ 1, 0 }.Rotate(angle);
		data.velocity = direction * randomf(m_data.speedMin, m_data.speedMax);
		data.damping = m_data.damping;
		data.size = m_data.size;

		particle->Initialize(data);
	}
}

