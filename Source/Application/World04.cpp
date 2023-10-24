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
        m_model->Load("Models/plane.obj");
        m_transform.position.y = -1;
        //m_model->Load("Models/Buddha.obj", glm::vec3{ 0 }, glm::vec3{-90, 0, 0,});

        m_light.type = light_t::eType::Point;
        m_light.position = glm::vec3{ 0, 5, 0 };
        m_light.direction = glm::vec3{ 0, -1, 0 };
        m_light.color = glm::vec3{ 1, 1, 1 };
        m_light.intensity = 1;
        m_light.innerAngle = 10.0f;
        m_light.outerAngle = 30.0f;

        return true;
    }

    void World04::Shutdown()
    {

    }

    void World04::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0], 0.1f);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0], 0.1f);
        ImGui::DragFloat3("Scale", &m_transform.scale[0], 0.1f);
        ImGui::End();

        ImGui::Begin("Light");
        const char* types[] = { "Point", "Directional", "Spot" };
        ImGui::Combo("Type", (int*)(&m_light.type), types, 3);

        if (m_light.type != light_t::Directional) ImGui::DragFloat3("Position", glm::value_ptr(m_light.position), 0.1f);
        if (m_light.type != light_t::Point) ImGui::DragFloat3("Direction", glm::value_ptr(m_light.direction), 0.1f);
        if (m_light.type == light_t::Spot)
        {
            ImGui::DragFloat("Inner Angle", &m_light.innerAngle, 1, 0, m_light.outerAngle);
            ImGui::DragFloat("Outer Angle", &m_light.outerAngle, 1, m_light.innerAngle, 90);
        }

        ImGui::ColorEdit3("Color", glm::value_ptr(m_light.color));
        ImGui::DragFloat("Intensity", &m_light.intensity, 0.1f, 0 , 10);

        ImGui::ColorEdit3("AmbientColor", &m_ambientColor[0]);
        ImGui::End();

        auto material = m_model->GetMaterial();
        material->ProcessGui();
        material->Bind();
        
        material->GetProgram()->SetUniform("light.type", m_light.type);
        material->GetProgram()->SetUniform("light.position", m_light.position);
        material->GetProgram()->SetUniform("light.direction", m_light.direction);
        material->GetProgram()->SetUniform("light.color", m_light.color);
        material->GetProgram()->SetUniform("light.intensity", m_light.intensity);
        material->GetProgram()->SetUniform("light.innerAngle", glm::radians(m_light.innerAngle));
        material->GetProgram()->SetUniform("light.outerAngle", glm::radians(m_light.outerAngle));

        material->GetProgram()->SetUniform("light.ambientColor", m_ambientColor);

        //model matrix
        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());
        //view 
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        material->GetProgram()->SetUniform("view", view);
        //projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)ENGINE.GetSystem<Renderer>()->GetWidth()/(float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.1f, 100.0f);
        material->GetProgram()->SetUniform("projection", projection);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World04::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();
        // render
        m_model->Draw(GL_TRIANGLES);
        ENGINE.GetSystem<Gui>()->Draw();
        // post-render
        renderer.EndFrame();
    }
}