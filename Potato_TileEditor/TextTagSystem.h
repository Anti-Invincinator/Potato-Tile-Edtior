#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H

enum TagTypes { DEFAULT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXP_TAG};

class TextTagSystem
{
private:
	class TextTag
	{
	private:
		sf::Text text;
		float dirY;
		float dirX;
		float lifeTime;
		float speed;

	public:
		TextTag(sf::Font& font, std::string text,
			float pos_x, float pos_y,
			float dir_x, float dir_y,
			sf::Color color, unsigned char_size,
			float life_time, float speed
		)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pos_y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->text.setString(text);

			this->dirX = dir_x;
			this->dirY = dir_y;
			this->lifeTime = life_time;
			this->speed = speed;
		}

		TextTag(TextTag* tag, float pos_x, float pos_y, std::string str)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(pos_x, pos_y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifeTime = tag->lifeTime;
			this->speed = tag->speed;
		}

		~TextTag()
		{

		}

		//Accessor
		inline const bool isExpired() const { return this->lifeTime <= 0.f; }

		//Function
		void Update(const float& dt) 
		{
			if (this->lifeTime > 0.f)
			{
				//Update the lifetime
				this->lifeTime -= 100.f * dt;

				//Move the tag
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);

			}
			
		}

		void Render(sf::RenderTarget& target)
		{
			target.draw(this->text);
		}
	};

	sf::Font font;
	std::map<unsigned, TextTag*> tagTemplates;
	std::vector<TextTag*> tags;

	//Private Functions
	void initFont(std::string  font_file);
	void initVariables();
	void initTagTemplates();

public:

	//Constructor/Destructor
	TextTagSystem(std::string font_file);
	virtual ~TextTagSystem();

	//Functions
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string string);
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i);
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f);

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};


#endif // !TEXTTAGSYSTEM_H


