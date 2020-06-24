#pragma once
#include "TextureManager.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "Animation.h"
#include <SDL.h>

struct SpriteComponent: public Component {
    SDL_Texture* texture;

    std::string currentAnimationName;
    uint32_t animationIndex = 0;

    SDL_RendererFlip SpriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char* filepath);
    SpriteComponent(std::string id, uint32_t numFrames, uint32_t animationSpeed, bool hasDirections, bool isFixed);
    void SetTexture(std::string assetTextureId);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    TransformComponent* _attachedObjectTransform = NULL;
    std::map<std::string, Animation> _animations;
    SDL_Rect _srcRect;
    SDL_Rect _dstRect;
    bool _isAnimated;
    uint32_t _numFrames;
    uint32_t _animationSpeed;
    bool _isFixed;
    void Play();
};