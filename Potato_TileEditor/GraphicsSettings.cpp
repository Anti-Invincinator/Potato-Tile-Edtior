#include "stdafx.h"
#include "GraphicsSettings.h"

//Constructor
GraphicsSettings::GraphicsSettings()
{
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->vertical_sync = false;
	this->framerate_limit = 120;
	this->context_settings.antialiasingLevel = 0;
	this->video_modes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	/* Values
	*  - window width and height
	*  - fullscreen mode (0 or 1)
	*  - framrate limit
	*  - vertical sync
	*  - antialiasing level
	*/

	if (ofs.is_open())
	{
		ofs << title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->framerate_limit;
		ofs << this->vertical_sync;
		ofs << this->context_settings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	/* Assigning Values
	*  - window width and height
	*  - fullscreen mode (0 or 1)
	*  - framrate limit
	*  - vertical sync
	*  - antialiasing level
	*/

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->framerate_limit;
		ifs >> this->vertical_sync;
		ifs >> this->context_settings.antialiasingLevel;
	}

	ifs.close();
}