#include "neuron.h"
#include <iostream>
double sg(double x);

neuron::neuron() {}

neuron::neuron(int input_amount)
{
	this->input_amount = input_amount; // в последнем элементе лежит вес смещения активационной функции
	weights = new double[this->input_amount + 1];
	for (int i = 0; i < this->input_amount + 1; i++) weights[i] = 0;
}

neuron::~neuron() { }

//-------------------------Описание функций

double neuron::give_answer(int* input_values)
{
	double sum = 0;

	for (int i = 0; i < input_amount; i++)
	{
		sum += input_values[i] * weights[i];
	}

	sum += weights[input_amount];
	return sg(sum);
}

double neuron::train_sum(int* input_values)
{
	double sum = 0;
	for (int i = 0; i < input_amount; i++)
	{
		sum += input_values[i] * weights[i];
	}
	sum += weights[input_amount];
	return sum;
}

void neuron::teach(double correct_answer, int* input_values)
{
	double prev_error = abs(correct_answer - give_answer(input_values)), error = 0;
	double prev_sum = neuron::train_sum(input_values), cur_sum = prev_sum;

	for (int i = 0; i < input_amount; i++)
	{
		if (weights[i] > 0 & input_values[i] > 0)
		{
			i = i;
		}
		weights[i] += TRAIN_STEP; //прыгаем вперед

		cur_sum += TRAIN_STEP * input_values[i];
		error = abs(correct_answer - sg(cur_sum));

		if (error >= prev_error) // если ухудшилось, возвращаемся в исходное значение и прыгаем назад
		{
			weights[i] -= 2 * TRAIN_STEP;

			cur_sum -= 2 * TRAIN_STEP * input_values[i];
			error = abs(correct_answer - sg(cur_sum));

			if (error >= prev_error) //если ухудшилось, возвращаемся в исходное значение
			{
				weights[i] += TRAIN_STEP;

				cur_sum += TRAIN_STEP * input_values[i];
			}
			else
			{
				prev_error = error;
				prev_sum = cur_sum;
			}
		}
		else
		{
			prev_error = error;
			prev_sum = cur_sum;
		}

		for (int l = 0; (l < 26); l++)
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

	/*for (int l = 0; l < ; l++)
	{
		if (prev_error > 0.5)
		weights[input_amount] += TRAIN_STEP;

		cur_sum += TRAIN_STEP;
		error = abs(correct_answer - sg(cur_sum));
	}*/


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

//--------------------------Доп функции

double sg(double x)
{
	return 1 / (1 + exp(-x + 5));
}