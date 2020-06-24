#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char* filePath) {
	SetTexture(filePath); 
}

SpriteComponent::SpriteComponent(std::string id, uint32_t numFrames, uint32_t animationSpeed, bool hasDirections, bool isFixed)
: _numFrames(numFrames), _animationSpeed(animationSpeed), _isFixed(isFixed){

    _isAnimated = animationSpeed == 0;
    _srcRect.x = 0;
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

}

void SpriteComponent::Update(float deltaTime) {
    auto objectTransform = owner->GetComponent<TransformComponent>();
	// Todo: this is important for animation. Come back to this
	if(_isAnimated) {
		_srcRect.x = _srcRect.w * static_cast<int>((SDL_GetTicks() / _animationSpeed) % _numFrames);
	}
	_srcRect.w = objectTransform->width;
    _srcRect.h = objectTransform->height;
	_srcRect.y = animationIndex * objectTransform->scale;

	auto camera = Game::manager.GetEntityByName("camera").GetComponent<TransformComponent>()->position;

	_dstRect.x = static_cast<int>(objectTransform->position.x) - (_isFixed ? 0 : camera.x);
	_dstRect.y = static_cast<int>(objectTransform->position.y) - (_isFixed ? 0 : camera.y);
	_dstRect.w = objectTransform->width * objectTransform->scale;
	_dstRect.h = objectTransform->height * objectTransform->scale;
}

void SpriteComponent::Render() {
    if(owner->Name.compare("player") == 0){
        TextureManager::Draw(texture, _srcRect, _dstRect, SpriteFlip);
    }
}