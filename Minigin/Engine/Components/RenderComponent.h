#pragma once
#include "BaseComponent.h"
#include <glm/common.hpp>
#include <vector>

struct SDL_Rect;

namespace MyEngine
{
	class Texture2D;
	struct AnimatedTexture
	{
		Texture2D* Texture;
		float FrameTime, CurrentTime, Angle;
		int Rows, Columns, CurrentFrame, State, DrawWidth, DrawHeight;
		bool IsAnimated, IsReversed, IsMirrored;
		glm::fvec2 Pivot, SrcPos, SrcDim, Offset;
	};
	class RenderComponent final : public BaseComponent
	{
	public:
		//Inherited
		void Update(const float deltaTime) override;
		void FixedUpdate(const float fixedDeltaTime) override;
		void Render() const override;

		RenderComponent() = default;
		void AddTexture(Texture2D* texture, bool isAnimated = false, bool reverse = false, const int rows = 0, const int columns = 0, const float frameTime = 0.0f, const int drawWidth = 0, const int drawHeight = 0, const glm::fvec2& pivot = { 0.5f, 0.5f }, const int activeState = -1, const glm::fvec2 srcPos = { 0.0f, 0.0f }, const glm::fvec2 srcDim = { 1.0f, 1.0f }, const glm::fvec2 offSet = { 0.0f, 0.0f }, bool mirror = false, float angle = 0.0f);
		void AddTexture(const std::string& filePath, bool isAnimated = false, bool reverse = false, const int rows = 0, const int columns = 0, const float frameTime = 0.0f, const int drawWidth = 0, const int drawHeight = 0, const glm::fvec2& pivot = { 0.5f, 0.5f }, const int activeState = -1, const glm::fvec2 srcPos = { 0.0f, 0.0f }, const glm::fvec2 srcDim = { 1.0f, 1.0f }, const glm::fvec2 offSet = { 0.0f, 0.0f }, bool mirror = false, float angle = 0.0f);
	private:
		std::vector<AnimatedTexture> m_Textures;
	};
}

