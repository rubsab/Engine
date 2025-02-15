#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Font.h"
#include "../Graphics/Texture2D.h"
#include "../Scene/GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "../Managers/ResourceManager.h"
#include "glm/gtx/rotate_vector.hpp"

void MyEngine::TextComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void MyEngine::TextComponent::FixedUpdate(const float fixedDeltaTime)
{
	UNREFERENCED_PARAMETER(fixedDeltaTime);
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture->SetTexture(texture);
		m_NeedsUpdate = false;
	}
}

void MyEngine::TextComponent::Render() const
{
	glm::vec2 pos{ m_pGameObject->GetComponent<TransformComponent>()->GetPosition() };
	SDL_Rect dstRect{ static_cast<int>(pos.x), static_cast<int>(pos.y) };
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &dstRect.w, &dstRect.h);
	SDL_Point pivot = { int(m_Pivot.x * dstRect.w), int(m_Pivot.y * dstRect.h) };
	glm::fvec2 worldOffset = { m_Offset.x, m_Offset.y };
	worldOffset = glm::rotate(worldOffset, -m_pGameObject->GetComponent<TransformComponent>()->GetRotation() * float(M_PI) / 180.0f);
	dstRect.x += -pivot.x + int(worldOffset.x);
	dstRect.y += pivot.y + int(worldOffset.y);
	Renderer::GetInstance()->RenderTexture(*m_pTexture, &dstRect, nullptr, m_pGameObject->GetComponent<TransformComponent>()->GetRotation() + m_Angle, pivot, false);
}

MyEngine::TextComponent::TextComponent(const std::string& text, Font* font, SDL_Color color, const glm::fvec2& pivot, const float angle, const glm::fvec2& offSet)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr), m_Color{ color }, m_Pivot{ pivot }, m_Angle{ angle }, m_Offset{ offSet }
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = new Texture2D(texture);
		ResourceManager::GetInstance()->m_Textures.push_back(IndexedTexture{ m_pTexture, ""});
		m_NeedsUpdate = false;
	}
}

MyEngine::Texture2D* MyEngine::TextComponent::GetTexture() const
{
	return m_pTexture;
}

void MyEngine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
