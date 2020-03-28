#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "../Graphics/Renderer.h"

void MyEngine::TransformComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void MyEngine::TransformComponent::Render() const
{

}

MyEngine::TransformComponent::TransformComponent(const Vector2 pos)
	:m_Position{ pos }
{
}

const Vector2& MyEngine::TransformComponent::GetPosition() const
{
	return m_Position;
}

void MyEngine::TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}
