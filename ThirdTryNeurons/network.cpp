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

void network::teach() // главная функция для обучения
{
	std::vector<fs::path>* retu = new std::vector<fs::path>[OUTPUT_NEURONS]; // вектор для хранения имен всех файлов. Ест много памяти
	my_image img;
	int* input_image_array; // массив из 1 и 0, черный и белый соотвественно
	int* correct_answers = new int[OUTPUT_NEURONS]; // массив из 1 и 0, где одна единица на верном ответе
	//int iter_count = 0;

	for (int chr = 0; chr < OUTPUT_NEURONS; chr++) // получаем все файлы из папок с помощью библиотеки BOOST
	{
		get_all("lesson/" + get_string((char)(chr + (int)'A')), ".png", retu[chr]); //смотрим все файлы в папке и записываем в retu
		//iter_count += retu[chr].size();
	}

	for (int img_num = 0; img_num < 1000; img_num++) // проходим по каждой буквеfor (int img_num = 0; img_num < /*retu.size()*/100; img_num++)
	{
		std::cout << img_num << "/" << 1000 << "\n"; 

		for (int chr = 0; chr < OUTPUT_NEURONS; chr++)
		{
			img.load_image("lesson/" + get_string((char)(chr + (int)'A')) + "/" + retu[chr][img_num].string()); //загружаем каритнку из файла
			if (img.is_image_loaded)
			{
				input_image_array = img.get_array(); // заполняем 1 и 0

				for (int i = 0; i < OUTPUT_NEURONS; i++) correct_answers[i] = 0; // заполняем 1 и 0 верный ответ
				correct_answers[chr] = 1;

				output_layer.teach(correct_answers, input_image_array); // учим слой

				delete[] input_image_array; 
			}

			//save_to_file("loles.txt");
		}
		//save_to_file("loles.txt");
	}

	for (int chr = 0; chr < OUTPUT_NEURONS; chr++)
		retu[chr].clear();

	save_to_file(SAVE_PATH); // сохранение файла с весами
	//img.load_image("lesson/A/" + retu[0].string());
	//output_layer.teach(correct_answers, input_values);
}

void network::guess(std::string file_path) // просто считает ответ сети
{
	std::ifstream input_stream;
	input_stream.open(file_path);// тут проверка на существование файла 

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

		double* answers = output_layer.give_answer(temp_img.get_array()); // а тут вывод ответов
		for (int i = 0; i < OUTPUT_NEURONS; i++)
		{
			std::cout << (char)(i + (int)'A') << " is " << answers[i] << "\n";
		}
	}
}

void network::save_to_file(std::string file_path) // сохранение а файл весов
{
	double** output_data = output_layer.weights();

	std::ofstream output_stream;
	output_stream.open(file_path); // проверка на существование

	if (!output_stream)
	{
		std::cout << "File does not exists.\n";
		output_stream.close();
		return;
	}

	for (int neu = 0; neu < OUTPUT_NEURONS; neu++)
	{
		output_stream << neu << "\n";
		for (int wght = 0; wght < PICTURE_SIZE * PICTURE_SIZE + 1; wght++) // запись
		{
			output_stream << output_data[neu][wght] << " ";
		}
	}
	output_stream.close();
	std::cout << "File have been saved. \n";
}

void network::load_from_file(std::string file_path) // загрузка из файла
{
	std::ifstream input_stream;
	input_stream.open(file_path); // проверка на существование

	if (!input_stream)
	{
		input_stream.close();
		std::cout << "File does not exists\n";
		return;
	}
	else
	{
		double** weights_temp = new double*[OUTPUT_NEURONS]; // ну, загрузка
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
void get_all(const fs::path& root, const std::string& ext, std::vector<fs::path>& ret) // скопировал из интернета. Не понимаю, как она работает
{
	if (!fs::exists(root) || !fs::is_directory(root)) return; // она получает все файлы из папки

	fs::recursive_directory_iterator it(root);
	fs::recursive_directory_iterator endit;

	while (it != endit)
	{
		if (fs::is_regular_file(*it) && it->path().extension() == ext) ret.push_back(it->path().filename());
		++it;

	}

}
