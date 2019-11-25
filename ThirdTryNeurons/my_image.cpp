#include "my_image.h"

my_image::my_image() { is_image_loaded = false; }

my_image::~my_image() { }

//-----------------------

void my_image::load_image(std::string file_path) // loading img using "SFML"
{
	std::ifstream exist_test;
	exist_test.open(file_path);

	if (!exist_test) is_image_loaded = false; //file existance check
	else
	{
		is_image_loaded = true;

		img.loadFromFile(file_path);

		values_array = new int[PICTURE_SIZE * PICTURE_SIZE];

		for (int i = 0; i < img.getSize().x; i++)
			for (int j = 0; j < img.getSize().y; j++)
				if (img.getPixel(i, j).r > 100) values_array[i * PICTURE_SIZE + j] = 0; // black = 1 white = 0
				else							values_array[i * PICTURE_SIZE + j] = 1;
	}

	exist_test.close();
}

int* my_image::get_array() // return 1 and 0
{
	return values_array;
}