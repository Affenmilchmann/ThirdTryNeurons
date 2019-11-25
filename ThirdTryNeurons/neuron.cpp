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

double neuron::give_answer(int* input_values) // ответ нейрона
{
	double sum = 0;

	for (int i = 0; i < input_amount; i++)
	{
		sum += input_values[i] * weights[i];
	}

	sum += weights[input_amount];
	return sg(sum);
}

double neuron::train_sum(int* input_values) // дает сумму до преобразования через сигмоиду
{
	double sum = 0;
	for (int i = 0; i < input_amount; i++)
	{
		sum += input_values[i] * weights[i];
	}
	sum += weights[input_amount];
	return sum;
}

void neuron::teach(double correct_answer, int* input_values) // обучение
{
	double prev_error = abs(correct_answer - give_answer(input_values)), error = 0;
	double prev_sum = neuron::train_sum(input_values), cur_sum = prev_sum; // для оптимизации я не считаю ошибку каждый раз с нуля.
	                                                                      // иначе она тренируется раз в 60 дольше. Я с каждым "прыжком"
	for (int i = 0; i < input_amount; i++)                                // прибавляю изменение к сумме до пропуска через sg()
	{
		/*if (weights[i] > 0 & input_values[i] > 0)
		{
			i = i;
		}*/
		weights[i] += TRAIN_STEP; //прыгаем вперед

		cur_sum += TRAIN_STEP * input_values[i]; // вот прибавление изменения к сумме
		error = abs(correct_answer - sg(cur_sum));

		if (error >= prev_error) // если ухудшилось, возвращаемся в исходное значение и прыгаем назад, на -TRAIN_STEP
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
				prev_error = error; // значит все хорошо и запоминаем результаты
				prev_sum = cur_sum;
			}
		}
		else
		{
			prev_error = error; // значит все хорошо и запоминаем результаты
			prev_sum = cur_sum;
		}

		for (int l = 0; (l < 26); l++) // костыль с усреднением веса смещения. пытаюсь, чтоб он не уходил в крайности 0 и 1
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

double* neuron::get_weights() //дать веса
{
	return weights;
}

void neuron::set_weights(double* weights) // задать веса
{
	delete[] this->weights;
	this->weights = weights;
}

double neuron::get_w0() // дать вес смещения
{
	return weights[input_amount];
}

void neuron::set_w0(double value) //задать вес смещения
{
	weights[input_amount] = value;
}

//--------------------------Доп функции

double sg(double x) // сигмоида. Я её зачм-то сместил на 5
{
	return 1 / (1 + exp(-x + 5));
}