#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

class GraphicsSettings
{

public:
	GraphicsSettings();

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool vertical_sync;
	unsigned framerate_limit;
	sf::ContextSettings context_settings;
	std::vector<sf::VideoMode> video_modes;

	//Functions
	void saveToFile(const std::string path);

	void loadFromFile(const std::string path);
};

#endif  //!GRAPHICSSETTINGS_H