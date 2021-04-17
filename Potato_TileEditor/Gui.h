#ifndef GUI_H
#define GUI_H

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

namespace gui
{
	//Functions
	const float p2pX(const float width_percent, const sf::VideoMode& vm);
	const float p2pY(const float height_percent, const sf::VideoMode& vm);
	const unsigned p2fontSize(const sf::VideoMode& vm, const unsigned font_size_modifier = 60);

	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textPressedColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color pressedColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlinePressedColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_pressed_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color pressed_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_pressed_color = sf::Color::Transparent,
			short unsigned id = 0);

		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void Update(const sf::Vector2i& mousePos);
		void Render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keytime;
		const float keytimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector <gui::Button*> list;
		bool showList;

	public:
		//Constructors/Destructors
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const bool getKeytime();
		const unsigned short& getActiveElementId() const;

		//Functions
		void updateKeytime(const float& dt);
		void Update(const sf::Vector2i& mousePosWindow, const float& dt);
		void Render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;
		gui::Button* hide_btn;

		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		TextureSelector(float x, float y, float width, float height, 
			float gridsize, const sf::Texture* texture_sheet,
			sf::Font& font, std::string button_text );

		~TextureSelector();

		//Accessors]
		const bool getKeytime();
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//Functions
		void updateKeytime(const float& dt);
		void Update(const sf::Vector2i& mousePosWindow, const float& dt);
		void Render(sf::RenderTarget& target);
	};
}

#endif // !GUI_H