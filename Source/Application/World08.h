#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace Jackster
{
	class World08 : public World
	{
	public:
		const uint32_t INVERT_MASK	  = (1 << 0);
		const uint32_t GRAYSCALE_MASK = (1 << 1);
		const uint32_t COLORTINT_MASK = (1 << 2);
		const uint32_t GRAIN_MASK     = (1 << 3);
		const uint32_t SCANLINE_MASK  = (1 << 4);
		const uint32_t BLUR_MASK	  =	(1 << 5);

	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;
		float m_blend = 1;
		float m_refraction = 1;
		glm::vec3 m_ambientColor{ 0.4, 0.4, 0.4 };
		glm::vec3 m_tint{ 1 };

		uint32_t m_params{ 0 };
	};
}