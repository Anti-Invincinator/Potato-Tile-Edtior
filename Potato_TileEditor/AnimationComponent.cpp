#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	//Deleting the Animations
	for (auto &i : this->animations)
	{
		delete i.second;          //second because that's the second value which is animation
	}
}


//Accessor
const bool& AnimationComponent::isDone(const std::string key) 
{
	return this->animations[key]->isDone();
}

//Functions
void AnimationComponent::addAnimation(
	const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation (
		this->sprite, this->textureSheet, 
		animation_timer, 
		start_frame_x, start_frame_y, frames_x, frames_y, width, height
	);
}

const bool& AnimationComponent::Play(const std::string key, const float& dt, const bool priority)
{
	if (priority)
	{
		this->priorityAnimation = this->animations[key];
	}
	if (this->priorityAnimation)  //if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//if the primary animation is done remove it
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = nullptr;
			}
		}
		
	}
	else //Play animation if no other priority animation is set
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}
	
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::Play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{

	if (this->priorityAnimation)  //if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//if the primary animation is done, remove it
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = nullptr;
			}
		}

	}
	else //Play animation if no other priority animation is set
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}

