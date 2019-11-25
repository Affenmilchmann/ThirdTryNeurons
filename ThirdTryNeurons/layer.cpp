#include "layer.h"

layer::layer() {}

layer::layer(int neurons_amount, int inputs_amount)
{
	this->neurons_amount = neurons_amount;
	neurons = new neuron[neurons_amount];
	for (int i = 0; i < neurons_amount; i++) neurons[i] = neuron(inputs_amount);
}

void layer::teach(int* correct_answers, int* input_values)
{
	for (int i = 0; i < OUTPUT_NEURONS; i++)
	{
		neurons[i].teach(correct_answers[i], input_values);

		double avrg = 0;
		for (int i = 0; i < 26; i++) avrg += neurons[i].get_w0();

		avrg /= 26;

		for (int i = 0; i < 26; i++) neurons[i].set_w0(avrg);
	}
	//neurons[correct_answers].teach(1.0f, input_values);
}

double** layer::weights()
{
	double** output = new double*[OUTPUT_NEURONS];

	for (int i = 0; i < OUTPUT_NEURONS; i++)
	{
		output[i] = neurons[i].get_weights();
	}

	return output;
}

double* layer::give_answer(int* input_values)
{
	double* output = new double[OUTPUT_NEURONS];

	for (int i = 0; i < OUTPUT_NEURONS; i++) output[i] = neurons[i].give_answer(input_values);

	return output;
}

void layer::set_weights(double** weights)
{
	for (int i = 0; i < OUTPUT_NEURONS; i++) neurons[i].set_weights(weights[i]);
}

layer::~layer() {}

//----------------------