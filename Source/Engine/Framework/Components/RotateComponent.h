#pragma once
#include "Component.h"

namespace Jackster
{
	class RotateComponent : public Component
	{
	public:
		CLASS_DECLARATION(RotateComponent)

		bool Initialize() override;
		void Update(float dt) override;
		
	private:

	};
}