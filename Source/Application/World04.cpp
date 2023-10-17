#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>

namespace Jackster
{
    bool World04::Initialize()
    {

        auto material = GET_RESOURCE(Material, "Materials/grid.mtrl");
        m_model = std::make_shared<Model>();
        m_model->SetMaterial(material);
        m_model->Load("Models/cube.obj");

        return true;
    }

    void World04::Shutdown()
    {

    }

    void World04::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0]);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0]);
        ImGui::End();

        auto material = m_model->GetMaterial();
        material->ProcessGui();
        material->Bind();

        //model matrix
        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());
        //view matrix
        material->GetProgram()->SetUniform("view", m_transform.GetMatrix());
        //projection matrix
        material->GetProgram()->SetUniform("projection", m_transform.GetMatrix());

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World04::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();
        // render
        ENGINE.GetSystem<Gui>()->Draw();
        m_model->Draw(GL_TRIANGLES);
        // post-render
        renderer.EndFrame();
    }
}