#pragma once
#include "TextureManager.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "Animation.h"
#include <SDL.h>

class SpriteComponent: public Component {
private:
	TransformComponent* _attachedObjectTransform;
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_Rect _dstRect;
	bool _isAnimated;
	uint32_t _numFrames;
	uint32_t _animationSpeed;
	bool _isFixed;
	std::map<std::string, Animation> _animations;
	std::string _currentAnimationName;
	uint32_t _animationIndex = 0;
	void Play();

public:
	SDL_RendererFlip SpriteFlip = SDL_FLIP_NONE;

	SpriteComponent(const char* filepath);
	SpriteComponent(std::string id, uint32_t numFrames, uint32_t animationSpeed, bool hasDirections, bool isFixed);
	void SetTexture(std::string assetTextureId);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
};