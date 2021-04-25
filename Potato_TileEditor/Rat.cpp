#include "stdafx.h"
#include "Rat.h"

//Initializer functions
void Rat::initVariables()
{

}

void Rat::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);
}

void Rat::initAI()
{

}

void Rat::initGui()
{
	this->hpbar.setFillColor(sf::Color::Red);
	this->hpbar.setSize(sf::Vector2f(100.f, 20.f));
	this->hpbar.setPosition(sf::Vector2f(this->sprite.getPosition()));
}

//Constructor / Destructor

Rat::Rat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	:Enemy(enemy_spawner_tile)
{
	this->initVariables();
	this->initGui();

	this->createHitboxComponent(this->sprite, 13.f, 39.f, 30.f, 30.f);
	this->createMovementComponent(50.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->generateAttributes(this->attributeComponent->level);

	this->setPosition(x, y);
	this->initAnimations();

	this->follow = new AIFollow(*this, player);
}

Rat::~Rat()
{
	delete this->follow;
}

void Rat::takeDamage(const int damage)
{
	this->attributeComponent->loseHP(damage);
}

//Functions
void Rat::updateAnimation(const float& dt)
{
	//Attack Animation
	//Animate and Check for animation end

	//Movement Animations
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->Play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->Play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->Play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->Play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->Play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);
}
void Rat::Update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	//UpdateGUI REMOVE
	this->hpbar.setSize(sf::Vector2f(100.f * (static_cast<float>(this->attributeComponent->hitpoints) / this->attributeComponent->hitpointsMax), 20.f));
	this->hpbar.setPosition(this->sprite.getPosition());

	this->movementComponent->Update(dt);

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->Update();

	this->follow->Update(dt);

}

void Rat::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	target.draw(this->hpbar);

	if (show_hitbox)
		this->hitboxComponent->Render(target);
}
