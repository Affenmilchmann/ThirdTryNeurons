#pragma once
#include "layer.h"
#include "my_image.h"

#include <iostream>

//// так сказали подключить
#include <boost/filesystem.hpp>
////
class network
{
public:
	network();
	~network();

	void teach();

	void guess(std::string file_path);

	void save_to_file(std::string file_path);

	void load_from_file(std::string file_path);

private:
	layer output_layer;
};

