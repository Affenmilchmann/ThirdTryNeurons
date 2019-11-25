#include "network.h"

namespace fs = ::boost::filesystem;

void get_all(const fs::path& root, const std::string& ext, std::vector<fs::path>& ret);
std::string get_string(char x);

network::network()
{
	output_layer = layer(OUTPUT_NEURONS, PICTURE_SIZE * PICTURE_SIZE);
}

network::~network() {}

//-------------------------------

void network::teach() // main teaching func
{
	std::vector<fs::path>* retu = new std::vector<fs::path>[OUTPUT_NEURONS]; // vector that keeps all names of all training pics
	my_image img;
	int* input_image_array; // array with 1 and 0. black and white
	int* correct_answers = new int[OUTPUT_NEURONS]; // array with correct answers one 1 and 25 0
	//int iter_count = 0;

	for (int chr = 0; chr < OUTPUT_NEURONS; chr++) // getting all files with "BOOST" lib
	{
		get_all("lesson/" + get_string((char)(chr + (int)'A')), ".png", retu[chr]); //recording all files to retu
		//iter_count += retu[chr].size();
	}

	for (int img_num = 0; img_num < 1000; img_num++) // 1000 - amount of training files of each letter
	{
		std::cout << img_num << "/" << 1000 << "\n"; 

		for (int chr = 0; chr < OUTPUT_NEURONS; chr++)
		{
			img.load_image("lesson/" + get_string((char)(chr + (int)'A')) + "/" + retu[chr][img_num].string()); //loading pic from file
			if (img.is_image_loaded)
			{
				input_image_array = img.get_array(); // filling 1 è 0 black and white

				for (int i = 0; i < OUTPUT_NEURONS; i++) correct_answers[i] = 0; // filling 1 è 0 correct answers
				correct_answers[chr] = 1;

				output_layer.teach(correct_answers, input_image_array); // teaching the layer

				delete[] input_image_array; 
			}

			//save_to_file("loles.txt");
		}
		//save_to_file("loles.txt");
	}

	for (int chr = 0; chr < OUTPUT_NEURONS; chr++)
		retu[chr].clear();

	save_to_file(SAVE_PATH); // saving weights to file
	//img.load_image("lesson/A/" + retu[0].string());
	//output_layer.teach(correct_answers, input_values);
}

void network::guess(std::string file_path) // gives answer from pic
{
	std::ifstream input_stream;
	input_stream.open(file_path);// file existance check

	if (!input_stream)
	{
		input_stream.close();
		std::cout << "File does not exists\n";
		return;
	}
	else
	{
		my_image temp_img;
		temp_img.load_image(file_path);

		double* answers = output_layer.give_answer(temp_img.get_array()); // answers output to cmd
		for (int i = 0; i < OUTPUT_NEURONS; i++)
		{
			std::cout << (char)(i + (int)'A') << " is " << answers[i] << "\n";
		}
	}
}

void network::save_to_file(std::string file_path) // saving weights
{
	double** output_data = output_layer.weights();

	std::ofstream output_stream;
	output_stream.open(file_path); // file existance check

	if (!output_stream)
	{
		std::cout << "File does not exists.\n";
		output_stream.close();
		return;
	}

	for (int neu = 0; neu < OUTPUT_NEURONS; neu++)
	{
		output_stream << neu << "\n";
		for (int wght = 0; wght < PICTURE_SIZE * PICTURE_SIZE + 1; wght++) // recording
		{
			output_stream << output_data[neu][wght] << " ";
		}
	}
	output_stream.close();
	std::cout << "File have been saved. \n";
}

void network::load_from_file(std::string file_path) // loading 
{
	std::ifstream input_stream;
	input_stream.open(file_path); // file existance check

	if (!input_stream)
	{
		input_stream.close();
		std::cout << "File does not exists\n";
		return;
	}
	else
	{
		double** weights_temp = new double*[OUTPUT_NEURONS];
		double temp;
		for (int i = 0; i < OUTPUT_NEURONS; i++)
		{
			weights_temp[i] = new double[PICTURE_SIZE * PICTURE_SIZE + 1];
			input_stream >> temp;
			for (int j = 0; j < PICTURE_SIZE * PICTURE_SIZE + 1; j++)
			{
				input_stream >> temp;
				weights_temp[i][j] = temp;
			}
		}

		output_layer.set_weights(weights_temp);
		delete [] weights_temp;
		std::cout << "file has been loaded.\n";
	}

	input_stream.close();
}

//-------------------------------

// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories
void get_all(const fs::path& root, const std::string& ext, std::vector<fs::path>& ret) // i took it from stackoverflow. idk how it works
{
	if (!fs::exists(root) || !fs::is_directory(root)) return; // it gets all files from folder

	fs::recursive_directory_iterator it(root);
	fs::recursive_directory_iterator endit;

	while (it != endit)
	{
		if (fs::is_regular_file(*it) && it->path().extension() == ext) ret.push_back(it->path().filename());
		++it;

	}

}
