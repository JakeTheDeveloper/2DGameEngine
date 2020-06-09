#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char* filePath) {
	SetTexture(filePath); 
}

SpriteComponent::SpriteComponent(std::string id, uint32_t numFrames, uint32_t animationSpeed, bool hasDirections, bool isFixed)
: _numFrames(numFrames), _animationSpeed(animationSpeed), _isFixed(isFixed){
	_isAnimated = true;

	if(hasDirections) {
		auto downAnimation = Animation(0, numFrames, animationSpeed);
		auto rightAnimation = Animation(1, numFrames, animationSpeed);
		auto leftAnimation = Animation(2, numFrames, animationSpeed);
		auto upAnimation = Animation(3, numFrames, animationSpeed);

		_animations.emplace("DownAnimation", downAnimation);
		_animations.emplace("RightAnimation", rightAnimation);
		_animations.emplace("LeftAnimation", leftAnimation);
		_animations.emplace("UpAnimation", upAnimation);

        animationIndex = 0;
        currentAnimationName = "DownAnimation";
	} else {
		auto singleAnimation = Animation(0, numFrames, animationSpeed);
		_animations.emplace("Single Animation", singleAnimation);
        animationIndex = 0;
        currentAnimationName = "Single Animation";
	}
	
	Play();
	SetTexture(id);
}

void SpriteComponent::Play() {
	_numFrames = _animations[currentAnimationName].numFrames;
	_animationSpeed = _animations[currentAnimationName].animationSpeed;
    animationIndex = _animations[currentAnimationName].index;
    currentAnimationName = currentAnimationName;
}

void SpriteComponent::SetTexture(std::string assetTextureId) {
	texture = Game::assetManager->GetTexture(assetTextureId);
}

void SpriteComponent::Initialize() {
	_attachedObjectTransform = owner->GetComponent<TransformComponent>();
	_srcRect.x = 0;
	_srcRect.y = 0;
	_srcRect.w = _attachedObjectTransform->width;
	_srcRect.h = _attachedObjectTransform->height;
}

void SpriteComponent::Update(float deltaTime) {
	// Todo: this is important for animation. Come back to this
	if(_isAnimated) {
		_srcRect.x = _srcRect.w * static_cast<int>((SDL_GetTicks() / _animationSpeed) % _numFrames);
	}
	_srcRect.y = animationIndex * _attachedObjectTransform->scale;

	_dstRect.x = static_cast<int>(_attachedObjectTransform->position.x) - (_isFixed ? 0 : Game::camera.x);
	_dstRect.y = static_cast<int>(_attachedObjectTransform->position.y) - (_isFixed ? 0 : Game::camera.y);
	_dstRect.w = _attachedObjectTransform->width * _attachedObjectTransform->scale;
	_dstRect.h = _attachedObjectTransform->height * _attachedObjectTransform->scale;
}

void SpriteComponent::Render() {
	TextureManager::Draw(texture, _srcRect, _dstRect, SpriteFlip);
}