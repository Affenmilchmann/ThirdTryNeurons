#pragma once

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>

#include <fstream>

#include "def_values.h"
class my_image
{
public:
	my_image();
	~my_image();

	bool is_image_loaded;

	void load_image(std::string file_path);
	int* get_array();

private:
	sf::Image img;
	int* values_array;
};

