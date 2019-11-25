#pragma once
#include <string>
const int PICTURE_SIZE = 128; // input pic size

const double TRAIN_STEP = 0.00001; // jump steps

const std::string SAVE_PATH = "weights.txt"; // saving file name

const int OUTPUT_NEURONS = 26; // amount of letters

std::string get_string(char x);