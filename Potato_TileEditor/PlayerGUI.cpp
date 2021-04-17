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
	float width = gui::p2pX(10.4f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float pos_x = gui::p2pX(1.f, this->vm);
	float pos_y = gui::p2pY(8.3f, this->vm);

	this->hpBarWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(this->hpBarWidth, height));
	this->hpBarBack.setFillColor(sf::Color(52, 52, 52, 100));
	this->hpBarBack.setOutlineThickness(1.f);
	this->hpBarBack.setOutlineColor(sf::Color::White);
	this->hpBarBack.setPosition(pos_x, pos_y);

	this->hpBar.setSize(sf::Vector2f(width, height));
	this->hpBar.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBar.setPosition(pos_x, pos_y);

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::p2fontSize(this->vm, 100));
	this->hpBarText.setPosition(sf::Vector2f(pos_x + gui::p2pX(0.53f, this->vm), pos_y - gui::p2pY(0.5f, this->vm)));
}

void PlayerGUI::initEXPBar()
{
	float width = gui::p2pX(10.4f, this->vm);
	float height = gui::p2pY(1.9f, this->vm);
	float pos_x = gui::p2pX(1.f, this->vm);
	float pos_y = gui::p2pY(5.6f, this->vm);

	this->expBarWidth = width;

	this->expBarBack.setSize(sf::Vector2f(this->expBarWidth, height));
	this->expBarBack.setFillColor(sf::Color(52, 52, 52, 100));
	this->expBarBack.setOutlineThickness(1.f);
	this->expBarBack.setOutlineColor(sf::Color::White);
	this->expBarBack.setPosition(pos_x, pos_y);

	this->expBar.setSize(sf::Vector2f(width, height));
	this->expBar.setFillColor(sf::Color(20, 20, 250, 200));
	this->expBar.setPosition(pos_x, pos_y);

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(20);
	this->expBarText.setPosition(sf::Vector2f(pos_x + gui::p2pX(0.53f, this->vm), pos_y - gui::p2pY(0.5f, this->vm)));
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

}

//Functions
void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hitpoints) / static_cast<float>(this->player->getAttributeComponent()->hitpointsMax);

	this->hpBar.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarWidth * percent)),
			this->hpBar.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hitpoints) + " / " + std::to_string(this->player->getAttributeComponent()->hitpointsMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBar);
	target.draw(this->hpBarText);
}

void PlayerGUI::updateEXPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBar.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarWidth * percent)),
			this->expBar.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBar);
	target.draw(this->expBarText);
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
