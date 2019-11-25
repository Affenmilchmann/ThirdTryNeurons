#pragma once
#include <string>
const int PICTURE_SIZE = 128; // размер входного изобращения

const double TRAIN_STEP = 0.00001; // дальность прыжков

const std::string SAVE_PATH = "weights.txt"; // имя сохраненного файла

const int OUTPUT_NEURONS = 26; // кол-во букв

std::string get_string(char x);