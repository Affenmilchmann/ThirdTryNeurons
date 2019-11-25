#pragma once
#include <vector>
#include "def_values.h"

class neuron
{
public:
	neuron(int input_amount);
	neuron();
	~neuron();

	double give_answer(int* input_values);
	void teach(double correct_answer, int* input_values);
	double* get_weights();
	double train_sum(int* input_values);
	void set_weights(double* weights);

	double get_w0(); //kostyl
	void set_w0(double value); //sec kostyl

private:
	int input_amount;
	double* weights;
};

