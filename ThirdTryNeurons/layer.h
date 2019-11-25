#pragma once
#include "neuron.h"

class layer
{
public:
	layer();
	layer(int neurons_amount, int inputs_amount);
	~layer();

	void teach(int* correct_answers, int* input_values);
	double** weights();
	double* give_answer(int* input_values);
	void set_weights(double** weights);

private:
	int neurons_amount;
	neuron* neurons;
};

