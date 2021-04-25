#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H

enum TagTypes { DEFAULT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXPERIENCE_TAG};

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
		float acceleration;
		sf::Vector2f velocity;
		int fadeValue;

	public:
		TextTag(sf::Font& font, std::string text,
			float pos_x, float pos_y,
			float dir_x, float dir_y,
			sf::Color color, unsigned char_size,
			float life_time,
			float speed, float acceleration,
			int fade_value
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
			this->acceleration = acceleration;
			this->fadeValue = fade_value;
			
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
			this->acceleration = tag->acceleration;
			this->fadeValue = tag->fadeValue;
			
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
				this->lifeTime -= 500.f * dt;

				//Accelerate
				if (this->acceleration > 0.f)
				{
					this->velocity.x += this->dirX * this->acceleration * dt;
					this->velocity.y += this->dirY * this->acceleration * dt;

					if (abs(this->velocity.x) > this->speed)
						this->velocity.x = this->dirX * this->speed;

					if (abs(this->velocity.y) > this->speed)
						this->velocity.y = this->dirY * this->speed;

					this->text.move(this->velocity * dt);
				}

				//Move the tag
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
			}

			if (this->fadeValue > 0 && this->text.getFillColor().a >= this->fadeValue)
			{
				this->text.setFillColor(
					sf::Color(
						this->text.getFillColor().r,
						this->text.getFillColor().g,
						this->text.getFillColor().b,
						this->text.getFillColor().a - this->fadeValue
					)
				);
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
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string string, const std::string prefix = "", const std::string postfix = "");
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const std::string prefix = "", const std::string postfix = "");
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const std::string prefix = "", const std::string postfix = "");

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};


#endif // !TEXTTAGSYSTEM_H


