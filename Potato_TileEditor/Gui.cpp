#include "stdafx.h"
#include "Gui.h"

const float gui::p2pX(const float width_percent, const sf::VideoMode& vm)
{
	/*
	* Converts a percentage value to pixels relative to the current resolution in the x-axis.
	*
	* @param					float perc				the percentage value.
	* @param					sf::VideoMode& vm		the current videomode of the window (resolution).
	*
	* @return					float					the calculated pixel value.
	*/
	return std::floor(static_cast<float>(vm.width) * (width_percent / 100.f));
}

const float gui::p2pY(const float height_percent, const sf::VideoMode& vm)
{
	/*
	* Converts a percentage value to pixels relative to the current resolution in the y-axis.
	*
	* @param					float perc						the percentage value.
	* @param					sf::VideoMode& vm				the current videomode of the window (resolution).
	*
	* @return					float					the calculated pixel value.
	*/
	return std::floor(static_cast<float>(vm.height) * (height_percent / 100.f));
}

const unsigned gui::p2fontSize(const sf::VideoMode& vm, const unsigned font_size_modifier)
{
	/*
	* Converts the character size for text using the current resolution and a constant.
	*
	* @param					sf::VideoMode& vm				the current videomode of the window (resolution).
	* @param					unsigne font_size_modifier	    used to modify font size with respect to 1920 x 1080
	*
	* @return					unsigned						the calculated character size value.
	*/
	

	return static_cast<unsigned>((vm.width + vm.height) / font_size_modifier);
}


gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color pressed_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_pressed_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);
	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x  + this->shape.getGlobalBounds().width/2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textPressedColor = text_idle_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->pressedColor = pressed_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlinePressedColor = outline_pressed_color;

}

gui::Button::~Button()
{

}

//ACCESSORS
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}


//Modifers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//FUNCTIONS
void gui::Button::Update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_PRESSED:
		this->shape.setFillColor(this->pressedColor);
		this->text.setFillColor(this->textPressedColor);
		this->shape.setOutlineColor(this->outlinePressedColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Black);
		this->shape.setOutlineColor(sf::Color::Red);
		std::cout << "ERROR::BUTTON::BUTTON IS NOT PICKING IDLE COLOR" << "\n";
		break;
	}
}

void gui::Button::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//DROP DOWN LIST ======================================

gui::DropDownList::DropDownList(float x, float y, float width, float height, 
	sf::Font& font, std::string list[], 
	unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	this->activeElement = new gui::Button(
		x, y , width, height,
		&this->font, list[default_index], 14,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(120, 120, 120, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0)
	);

	for (unsigned i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i + 1) * height), width, height,		//i + 1 is done to prevent from duplication of buttons at top position						// posX, posY, sizeX, sizeY
				&this->font, list[i], 14,																													// font, text, font size
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),													// idle, hover, pressed Text Color
				sf::Color(70, 70, 70, 200), sf::Color(120, 120, 120, 200), sf::Color(20, 20, 20, 200),														// idle, hover, pressed Button Color  (0 in alpha to make it a transparent button)
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 100),
				i			
			)
		);
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;

	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

//Accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}


//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::DropDownList::Update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->Update(mousePosWindow);


	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;

		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->Update(mousePosWindow);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}

}

void gui::DropDownList::Render(sf::RenderTarget& target)
{
	this->activeElement->Render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->Render(target);
		}
	}
}

//Texture Selector============================================================================
#pragma region TextureSelector
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
	float gridSize, const sf::Texture* texture_sheet,
	sf::Font& font, std::string button_text) :
	keytimeMax(1.f), keytime(0.f)
{
	this->active = false;
	this->gridSize = gridSize;
	this->hidden = false;
	float offset = this->gridSize;                                                     //This is done to accomodate the Texture Selector Button

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineColor(sf::Color::Red);
	this->selector.setOutlineThickness(1.f);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->hide_btn = new gui::Button(
		x, y, 50.f, 50.f,
		&font, button_text, 24,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
		sf::Color(70, 70, 70, 200), sf::Color(120, 120, 120, 200), sf::Color(20, 20, 20, 200)
	);
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

//Accessors

const bool gui::TextureSelector::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const bool& gui::TextureSelector::getActive() const
{
	return active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

//Functions
void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::TextureSelector::Update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);
	this->hide_btn->Update(mousePosWindow);

	//Toggling the Texture Selector
	if (this->hide_btn->isPressed() && this->getKeytime())
	{
		this->hidden = !this->hidden;
	}

	if (!hidden)
	{
		this->active = false;
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))  //Checking if mouse is within the selection bounds
		{
			this->active = true;

			this->mousePosGrid.x = (mousePosWindow.x - static_cast<unsigned>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<unsigned>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);
		}

		//Update texture rectangle
		this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
		this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
	}
}

void gui::TextureSelector::Render(sf::RenderTarget& target)
{

	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}

	this->hide_btn->Render(target);
}

#pragma endregion