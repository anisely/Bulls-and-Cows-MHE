/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23.05.2020 18:20:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdio.h>	/* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>	/* time */
#include <tuple>
#include <math.h>

using namespace std;

// ------ tool

class Number
{
	public:
	int size;
	int * array;

	Number() 
    { 
		size = 4;
        int * array = new int[size];
    } 

	~Number() 
    { 
        delete[] array;
    } 

	void print()
	{
		for (int i = size - 1; i >= 0; i--)
		{
			cout << array[i];
		}
		cout << endl;
	}

};

void print_array(int *array, int count_number_to_find)
{
	for (int a = count_number_to_find - 1; a >= 0; a--)
	{
		cout << array[a];
	}
	cout << endl;
}

void print_array2(int *array, int count_number_to_find)
{
	for (int a = count_number_to_find - 1; a >= 0; a--)
	{
		cout << array[a];
	}
	cout << endl;
}

// -------------------------

tuple<int, int> CompareArrays2(int *a, int *b, int size)
{

	int bull = 0;
	int cow = 0;
	int a_count[10] = {0};
	int b_count[10] = {0};

	//print_array(a, size);
	//print_array(b, size);

	// find bull or increse, we count all number to find which reapet
	for (int i = 0; i < size; i++)
	{
		if (a[i] == b[i])
			bull++;
		else
		{
			a_count[a[i]]++;
			b_count[b[i]]++;
		}
	}
	//cout << "DUPA!" << endl;
	//print_array(a_count, 10);
	//print_array(b_count, 10);

	// count cow
	for (int j = 0; j < 10; j++)
	{
		// get smaller number and add to cow, smaller means reapetad the same number
		if (a_count[j] <= b_count[j])
			cow += a_count[j];
		else
			cow += b_count[j];
	}

	//cout << "BULL" << bull << "COW" << cow << endl;

	return make_tuple(bull, cow);
}

int goal(int *a, int *b, int size)
{

	tuple<int, int> res = CompareArrays2(a, b, size);
	int bull = get<0>(res);
	int cow = get<1>(res);
	//cout << bull << "," << cow << endl;
	if (bull == size)
		return 1;
	else
		return 0;
}

int goal2(int *a, int *b, int size)
{

	tuple<int, int> res = CompareArrays2(a, b, size);
	int bull = get<0>(res);
	int cow = get<1>(res);

	return 4 * bull + 3 * cow;
}

bool CompareArrays(int *a, int *b, int size)
{

	for (int i = 0; i < size; i++)
	{
		if (a[i] == b[i])
			continue;
		else
			return false;
	}

	return true;
}

void FillSecretNumbers(int *secret_numbers, int count_number_to_find)
{
	int secret;

	/* initialize random seed: */

	for (int i = 0; i < count_number_to_find; i++)
	{
		/* generate secret number between 0 and 9: */
		secret = rand() % 10;
		secret_numbers[i] = secret;
	}
}

// -------- Algorithms -----

void bruteforce(int *secret_numbers, int count_number_to_find)
{

	int iteration = 0;

	// wyzeruj
	int *to_find_numbers = new int[count_number_to_find];
	for (int a = 0; a < count_number_to_find; a++)
	{
		to_find_numbers[a] = 0;
	}

	// Loop untill goal is not achived
	while (1)
	{
		iteration++;

		// Alghoritm
		// Incrementcount_number_to_find
		for (int i = 0; i < count_number_to_find; i++)
		{
			if (to_find_numbers[i] < 9)
			{
				to_find_numbers[i]++;
				break;
			}
			else
			{
				to_find_numbers[i] = 0;
			}
		}

		// Check goal
		if (goal(to_find_numbers, secret_numbers, count_number_to_find))
			break;
	}

	// Print results
	cout << "WIN!" << endl;
	cout << "Find number: ";
	print_array(to_find_numbers, count_number_to_find);
	cout << "Iterations: " << iteration << endl;
}

void wspinaczokwy(int *secret_numbers, int count_number_to_find)
{

	// Random number
	int *x = new int[count_number_to_find];
	FillSecretNumbers(x, count_number_to_find);

	int *max = new int[count_number_to_find];
	int *anktualna = new int[count_number_to_find];

	int tmp;

	for (int j = 0; j < count_number_to_find; j++)
	{
		tmp = x[j];
		anktualna[j] = tmp;
	}

	for (int k = 1; k < 20; k++)
	{
		// Po wszystkich sasiadach
		// for(int l= 0; l < 2; l++) {
		for (int i = 0; i < count_number_to_find; i++)
		{

			for (int j = 0; j < count_number_to_find; j++)
			{
				tmp = x[j];
				anktualna[j] = tmp;
			}

			// dodaj -1 i +1 do kazdje liczby pokolei
			if (x[i] < 9)
			{
				anktualna[i] = x[i] + 1;

				int a = goal2(secret_numbers, anktualna, count_number_to_find);
				int b = goal2(secret_numbers, x, count_number_to_find);
				cout << "Aktualna1 " << a << " ";
				print_array2(anktualna, count_number_to_find);
				cout << "Max1 " << b << " ";
				print_array2(x, count_number_to_find);
				if (a >= b)
				{
					for (int j = 0; j < count_number_to_find; j++)
					{
						tmp = anktualna[j];
						x[j] = tmp;
					}
				}
			}

			// dodaj -1 i +1 do kazdje liczby pokolei
			if (x[i] > 1)
			{
				anktualna[i] = x[i] - 2;

				int a = goal2(secret_numbers, anktualna, count_number_to_find);
				int b = goal2(secret_numbers, x, count_number_to_find);
				cout << "Aktualna2 " << a << " ";
				print_array2(anktualna, count_number_to_find);
				cout << "Max2 " << b << " ";
				print_array2(x, count_number_to_find);
				if (a >= b)
				{
					for (int j = 0; j < count_number_to_find; j++)
					{
						tmp = anktualna[j];
						x[j] = tmp;
					}
				}
			}
		}
		cout << "MAX ";
		print_array(x, count_number_to_find);

		if (goal(secret_numbers, anktualna, count_number_to_find))
			break;
		// }
	}

	delete[] x, max, anktualna;
}

int f() {
	
}


void somsiad(int * secret_numbers, int * x, int * anktualna, int count_number_to_find) {
	int tmp;

	int a = goal2(secret_numbers, anktualna, count_number_to_find);
	int b = goal2(secret_numbers, x, count_number_to_find);
	cout << "Aktualna " << a << " ";
	print_array2(anktualna, count_number_to_find);
	cout << "Max " << b << " ";
	print_array2(x, count_number_to_find);
	if (a >= b)
	{
		for (int j = 0; j < count_number_to_find; j++)
		{
			tmp = anktualna[j];
			x[j] = tmp;
		}
	}

}

bool juz_odwiedzony(int ** tabu, int * x, int count_number_to_find, int size_tabu) {

	int j = 0;
	// po całej tablicy tabu
	for(int i = 0; i < size_tabu; i++) {
		// porównanie elementów
		j = 0;
		for( ; j < count_number_to_find; j++) {
			if(tabu[i][j] != x[j]) {
				break;
			}
		}
		// jest identyczny w tablicy
		if(j == count_number_to_find) {
			return true;
		}
	}

	return false;
}


void przeszukiwanie_tabu(int *secret_numbers, int count_number_to_find)
{
	int w = 100;
	int liczba_w_tabu = 0;

	int **tab2 = new int *[w];
	for (int i = 0; i < w; ++i)
	{
		tab2[i] = new int[count_number_to_find];
		for (int j = 0; j < count_number_to_find; ++j) 
			tab2[i][j] = 0;
	}

	// Random number
	int *x = new int[count_number_to_find];
	FillSecretNumbers(x, count_number_to_find);

	int *Best = new int[count_number_to_find];

	int *anktualna = new int[count_number_to_find];

	int tmp;

	for (int j = 0; j < count_number_to_find; j++)
	{
		tmp = x[j];
		anktualna[j] = tmp;
	}

	
	for (int k = 1; k < 900; k++)
	{
		// Po wszystkich sasiadach
		// for(int l= 0; l < 2; l++) {
		for (int i = 0; i < count_number_to_find; i++)
		{

			
		//wykonanie kroku
		// s = SELECT(NEIGHBORS(s),t))
		// //aktualizowanie listy tabu
		// t = UPDATE TABU(s,t)
		// //najlepsze rozwiązanie zapamiętujemy
		// if (f(best) < f(s))
		// {
		// 	best = s
		// }

			for (int j = 0; j < count_number_to_find; j++) {
				tmp = x[j];
				anktualna[j] = tmp;
			}


			if (x[i] < 9)
			{
				anktualna[i] = x[i] + 1;
				int a = goal2(secret_numbers, anktualna, count_number_to_find);
				int b = goal2(secret_numbers, x, count_number_to_find);
				cout << "Aktualna1 " << a << " ";
				print_array2(anktualna, count_number_to_find);
				cout << "Max1 " << b << " ";
				print_array2(x, count_number_to_find);
				if (a >= b)
				{
					// nie ma w tablicy już odwiedzonych
					if(!juz_odwiedzony(tab2, anktualna, count_number_to_find, w)) {
						for (int j = 0; j < count_number_to_find; j++)
						{
							tmp = anktualna[j];
							x[j] = tmp;
						}
						//dodaj do tabu x						
						for (int j = 0; j < count_number_to_find; j++)
						{
							tmp = x[j];
							tab2[liczba_w_tabu%w][j] = tmp;
						}
						liczba_w_tabu++;	
					}
				}
			}

			for (int j = 0; j < count_number_to_find; j++) {
				tmp = x[j];
				anktualna[j] = tmp;
			}

			if (x[i] > 0)
			{
				anktualna[i] = x[i] - 1;
				int a = goal2(secret_numbers, anktualna, count_number_to_find);
				int b = goal2(secret_numbers, x, count_number_to_find);
				cout << "Aktualna2 " << a << " ";
				print_array2(anktualna, count_number_to_find);
				cout << "Max2 " << b << " ";
				print_array2(x, count_number_to_find);
				if (a >= b)
				{
					// nie ma w tablicy już odwiedzonych
					if(!juz_odwiedzony(tab2, anktualna, count_number_to_find, w)) {
						for (int j = 0; j < count_number_to_find; j++)
						{
							tmp = anktualna[j];
							x[j] = tmp;
						}
						//dodaj do tabu x						
						for (int j = 0; j < count_number_to_find; j++)
						{
							tmp = x[j];
							tab2[liczba_w_tabu%w][j] = tmp;
						}
						liczba_w_tabu++;	
					}
				}
			}

		}

		// Podmień jesli najlepszy
		int a = goal2(secret_numbers, x, count_number_to_find);
		int b = goal2(secret_numbers, Best, count_number_to_find);
		if (a >= b)
		{
			for (int j = 0; j < count_number_to_find; j++)
			{
				tmp = x[j];
				Best[j] = tmp;
			}
		}


	}

	cout << "TABU:";
	print_array(Best, count_number_to_find);

	//wypisz tab2[w][k]
	// for (int i = 0; i < w; ++i, cout << endl)
	// 	for (int j = 0; j < count_number_to_find; ++j)
	// 		cout << tab2[i][j] << '\t';

	//zniszcz tab2
	for (int i(0); i < w; ++i)
		delete[] tab2[i]; 
	delete[] tab2;		  
	tab2 = NULL;
}

void symulowane_wyzarzanie(int *secret_numbers, int count_number_to_find) {

	// Random number
	int *x = new int[count_number_to_find];
	FillSecretNumbers(x, count_number_to_find);
	int *Best = new int[count_number_to_find];
	int *sasiad = new int[count_number_to_find];

	for (int j = 0; j < count_number_to_find; j++)
	{
		sasiad[j] = x[j];
		Best[j] = x[j];
	}

	/* generate position 0-max and number between 0 and 9: */
	int value = rand() % 10;
	int position = rand() % count_number_to_find;
	sasiad[position] = value;

	int a = goal2(secret_numbers, x, count_number_to_find);
	int b = goal2(secret_numbers, sasiad, count_number_to_find);



	if (a >= b)
	{
		for (int j = 0; j < count_number_to_find; j++)
		{
			Best[j] =  x[j];
		}
	} else {


	}


	for(int i = 0; i < 300; i++) {
		double param, result;
  		param = 5.0;
  		result = exp (-abs(param));





	}
}

int main()
{

	srand(time(NULL));

	int count_number_to_find = 4;

	// Inicjalize secret number
	int *secret_numbers = new int[count_number_to_find];
	FillSecretNumbers(secret_numbers, count_number_to_find);
	cout << "Secret number: ";
	print_array(secret_numbers, count_number_to_find);

	// bruteforce(secret_numbers, count_number_to_find);

	cout << "Secret number: ";
	print_array(secret_numbers, count_number_to_find);

	// wspinaczokwy(secret_numbers, count_number_to_find);

	cout << "Secret number: ";
	print_array(secret_numbers, count_number_to_find);

	// przeszukiwanie_tabu(secret_numbers, count_number_to_find);

	cout << "Secret number: ";
	print_array(secret_numbers, count_number_to_find);

	symulowane_wyzarzanie(secret_numbers, count_number_to_find);

	cout << "Secret number: ";
	print_array(secret_numbers, count_number_to_find);

	delete[] secret_numbers;

	return 0;
}
