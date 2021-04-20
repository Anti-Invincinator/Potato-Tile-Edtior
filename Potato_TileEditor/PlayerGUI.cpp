#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/Karantina-Light.ttf");
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float pos_x = gui::p2pX(1.f, this->vm);
	float pos_y = gui::p2pY(1.9f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(55, 55, 55, 100));
	this->levelBarBack.setOutlineThickness(1.f);
	this->levelBarBack.setOutlineColor(sf::Color::White);
	this->levelBarBack.setPosition(pos_x, pos_y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::p2fontSize(this->vm, 80));
	this->levelBarText.setStyle(sf::Text::Style::Bold);
	this->levelBarText.setPosition(sf::Vector2f(pos_x + gui::p2pX(0.53f, this->vm), pos_y - gui::p2pY(0.5f, this->vm)));
}

void PlayerGUI::initHPBar()
{	
	this->hpBar = new gui::ProgressBar(1.f, 8.3f, 10.4f, 2.8f, this->player->getAttributeComponent()->hitpointsMax, sf::Color::Red, 100, this->vm, &this->font);
}

void PlayerGUI::initEXPBar()
{
	this->expBar = new gui::ProgressBar(1.f, 5.6f, 10.4f, 1.9f, this->player->getAttributeComponent()->expNext, sf::Color::Blue, 140, this->vm, &this->font);
}

//Constructor / Destructor
PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->initFont();
	this->initHPBar();
	this->initEXPBar();
	this->initLevelBar();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
	delete this->expBar;
}

//Functions
void PlayerGUI::updateHPBar()
{
	this->hpBar->Update(this->player->getAttributeComponent()->hitpoints);
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	this->hpBar->Render(target);
}

void PlayerGUI::updateEXPBar()
{
	this->expBar->Update(this->player->getAttributeComponent()->exp);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	this->expBar->Render(target);
}

void PlayerGUI::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::Update(const float& dt)
{
	this->updateEXPBar();
	this->updateHPBar();
	this->updateLevelBar();
}

void PlayerGUI::Render(sf::RenderTarget& target)
{
	this->renderEXPBar(target);
	this->renderHPBar(target);
	this->renderLevelBar(target);
}
