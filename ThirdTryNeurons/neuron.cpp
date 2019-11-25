#include "neuron.h"
#include <iostream>
double sg(double x);

neuron::neuron() {}

neuron::neuron(int input_amount)
{
	this->input_amount = input_amount; // there is w0 in the last array element(w1*x1 + ... wn*xn + w0) <- w0
	weights = new double[this->input_amount + 1];
	for (int i = 0; i < this->input_amount + 1; i++) weights[i] = 0;
}

neuron::~neuron() { }

//-------------------------Class functions

double neuron::give_answer(int* input_values) // neuron answer
{
	double sum = 0;

	for (int i = 0; i < input_amount; i++)
	{
		sum += input_values[i] * weights[i];
	}

	sum += weights[input_amount];
	return sg(sum);
}

double neuron::train_sum(int* input_values) // summ before sending to sg()
{
	double sum = 0;
	for (int i = 0; i < input_amount; i++)
	{
		sum += input_values[i] * weights[i];
	}
	sum += weights[input_amount];
	return sum;
}

void neuron::teach(double correct_answer, int* input_values) // teaching
{
	double prev_error = abs(correct_answer - give_answer(input_values)), error = 0;
	double prev_sum = neuron::train_sum(input_values), cur_sum = prev_sum; // for optimisaion im not calculating error every time from beginning
	                                                                      // without this training takes ~60 times longer. With every "jump"
	for (int i = 0; i < input_amount; i++)                                // i`m just adding delta to the summ
	{
		/*if (weights[i] > 0 & input_values[i] > 0)
		{
			i = i;
		}*/
		weights[i] += TRAIN_STEP; // jumping forward

		cur_sum += TRAIN_STEP * input_values[i]; // here it is. i`m adding delta to the summ instead of calling give_answer()
		error = abs(correct_answer - sg(cur_sum));

		if (error >= prev_error) 
		{
			weights[i] -= 2 * TRAIN_STEP;

			cur_sum -= 2 * TRAIN_STEP * input_values[i];
			error = abs(correct_answer - sg(cur_sum));

			if (error >= prev_error) 
			{
				weights[i] += TRAIN_STEP;

				cur_sum += TRAIN_STEP * input_values[i];
			}
			else
			{
				prev_error = error; // all is good. saving the results
				prev_sum = cur_sum;
			}
		}
		else
		{
			prev_error = error; // all is good. saving the results
			prev_sum = cur_sum;
		}

		for (int l = 0; (l < 26); l++) // its "kostyl", bad move. I`m trying to make all answers average to avoid all answers equal 1 or 0
		{
			if (abs(correct_answer - prev_error) > 0.5)
			{
				weights[input_amount] -= TRAIN_STEP;
			}
			else
			{
				weights[input_amount] += TRAIN_STEP;
			}
		}
	}
}

double* neuron::get_weights() 
{
	return weights;
}

void neuron::set_weights(double* weights) 
{
	delete[] this->weights;
	this->weights = weights;
}

double neuron::get_w0() 
{
	return weights[input_amount];
}

void neuron::set_w0(double value) 
{
	weights[input_amount] = value;
}

//--------------------------Additional funcs

double sg(double x) // sigmoid. idk why i moved it by 5
{
	return 1 / (1 + exp(-x + 5));
}