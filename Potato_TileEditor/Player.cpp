#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->sword = new Sword(1,20, "Resources/Images/Sprites/Player/sword.png", 2, 5, 60);	
	this->sword->generate(1, 3);
}

void Player::initComponents()
{

}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

void Player::initAttributes()
{
	this->attributeComponent->vitality 	=  2;
	this->attributeComponent->strength	=  4;
	this->attributeComponent->dexterity	=  1;
	this->attributeComponent->agility	=  1;
	this->attributeComponent->intelligence	=  1;
	this->attributeComponent->luck	=  1;
}

void Player::initInventory()
{
	this->inventory = new Inventory(10);
}

//Constructor/Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(160.f, 1300.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->setPosition(x, y);
	this->initAnimations();
	this->initAttributes();

	this->initInventory();
}

Player::~Player()
{
	delete this->sword;
	delete this->inventory;
}

//Accessors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

Weapon* Player::getWeapon() const
{
	return this->sword;
}

const bool& Player::getInitAttack() const
{
	return this->initAttack;
}

const std::string Player::toStringCharacterTab() const
{
	std::stringstream ss;

	AttributeComponent* ac = this->attributeComponent;

	ss << "Vitality : " << ac->vitality << "\n"
		<< "Strength : " << ac->strength << "\n"
		<< "Dexterity : " << ac->dexterity << "\n"
		<< "Agility : " << ac->agility << "\n"
		<< "Intelligence : " << ac->intelligence << "\n"
		<< "Luck: " << ac->luck << "\n";

	return ss.str();
}

void Player::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAnimation(const float& dt)
{
	//Attack Animation
	//Animate and Check for animation end
	if (this->attacking)
	{

	}

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
}


/*
	Updating Player
	1.updating movement Component (called from Entity Class)
	2.checking for attack input
	3.updating player animations
	4.updating hitox component (called from Entity Class)
*/
void Player::Update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->Update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->Update();

	this->sword->Update(mouse_pos_view, this->getCenter());

}

void Player::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		this->sword->Render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->sword->Render(target);
	}

	if(show_hitbox)
	this->hitboxComponent->Render(target);
}