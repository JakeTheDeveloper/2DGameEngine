#pragma once
class Animation {
public:
	int index;
	int numFrames;
	int animationSpeed;
	Animation();
	Animation(int index, int numFrames, int animationSpeed);
};