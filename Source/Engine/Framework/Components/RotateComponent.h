#pragma once
#include "Component.h"
#include <glm/glm/glm.hpp>
#include "Renderer/Program.h"

namespace Jackster
{
    class RotateComponent : public Component
    {
    public:
        CLASS_DECLARATION(RotateComponent)

        bool Initialize() override;
        void Update(float dt) override;
        void ProcessGui();

    private:
        glm::vec3 euler{ 0 };
    };
}