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
 * 	  Compilation:  g++ main.cpp
 *
 * =====================================================================================
 */

// TODO
// zakończenie algorytmy (połowa możlwiych iteracji bruteforce i BEST nie zmienia się)

#include <iostream>
#include <stdio.h>	/* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>	/* time */
#include <ctime>
#include <tuple>
#include <math.h>
#include <chrono>

using namespace std;

unsigned int OCENA_ITERACJA;
int WEIGHT_BULL;
int WEIGHT_COW;
int MAX_SCORE;
int SIZE;
int MAX_ITERATIONS;


class Number
{
	public:
	int size;
	int * array;

	Number()
    {
		this->size = 4;
        this->array = new int[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->array[i] = 0;
		}
    }

	Number(int size)
    {
		this->size = size;
        this->array = new int[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->array[i] = 0;
		}
    }

	~Number()
    {
        delete[] this->array;
    }

	void print()
	{
		for (int i = this->size - 1; i >= 0; i--)
		{
			cout << this->array[i];
		}
		//cout << endl;
	}

	void random()
	{
		for (int i = 0; i < this->size; i++)
		{
			/* generate secret number between 0 and 9: */
			this->array[i] = rand() % 10;
		}

	}

	void set_new_value(Number* number)
	{
		for (int i = 0; i < this->size; i++)
		{
			this->array[i] = number->array[i];
		}
	}

};

int CountScore(Number *a, Number *b)
{
	int bull = 0;
	int cow = 0;
	int a_count[10] = {0};
	int b_count[10] = {0};
    OCENA_ITERACJA++;
	// COUNT BULL; find bull or increse, we count all number to find which reapet
	for (int i = 0; i < SIZE; i++)
	{
		if (a->array[i] == b->array[i])
			bull++;
		else
		{
			a_count[a->array[i]]++;
			b_count[b->array[i]]++;
		}
	}
	//cout << "!!!" << endl;
	//print_array(a_count, 10);
	//print_array(b_count, 10);

	// COUNT COW;
	for (int j = 0; j < 10; j++)
	{
		// get smaller number and add to cow, smaller means reapetad the same number
		if (a_count[j] <= b_count[j])
			cow += a_count[j];
		else
			cow += b_count[j];
	}

	//cout << "BULL" << bull << "COW" << cow << endl;

	return WEIGHT_BULL * bull + WEIGHT_COW * cow;
}

// -------- Algorithms -----

void bruteforce(Number *secret)
{
	Number *x = new Number(SIZE);

	int iterations = 0;
	while (1)
	{
		//Increment x by one
		for (int i = 0; i < SIZE; i++)
		{
			//iterations++;
			if (x->array[i] < 9)
			{
				x->array[i]++;
				break;
			}
			else
			{
				x->array[i] = 0;
			}

		}
//Show that it's actually working
//        cout << "Checking " << testval++<<" comparing to ";
//        secret->print();
//        cout << endl;
        iterations++;
		if (CountScore(x, secret) == MAX_SCORE)
			break;
	}

	cout << "Bruteforce: \t";
	x->print();
	cout << "\t" << CountScore(secret, x);
	cout << "\t" << iterations;
	cout << endl;
}

void wspinaczokwy_random(Number *secret)
{

	Number* x = new Number(SIZE);
	x->random();
	Number *Best = new Number(SIZE);
	Number *anktualna = new Number(SIZE);

	int iterations = 0;
	for ( ; iterations < MAX_ITERATIONS; iterations++)
	{
		anktualna->set_new_value(x);

		int value = rand() % 10;
		int position = rand() % SIZE;
		anktualna->array[position] = value;

		if (CountScore(secret, anktualna) >= CountScore(secret, x))
		{
			x->set_new_value(anktualna);
		}

		if (CountScore(secret, x) == MAX_SCORE)
			break;

	}

	cout << "Wspinaczokwy: \t";
	x->print();
	cout << "\t" << CountScore(secret, x);
	cout << "\t" << iterations;
	cout << "\t" << (double)CountScore(secret,x)/iterations << " solution quality";
	cout << endl;

	delete x, anktualna, Best;
}

void wspinaczokwy_all_neighbor(Number *secret)
{

	Number* x = new Number(SIZE);
	x->random();
	Number *Best = new Number(SIZE);
	Number *anktualna = new Number(SIZE);

	int iterations = 0;
	int number_ask_score = 0;
	for ( ; iterations < MAX_ITERATIONS; iterations++)
	{
		// Po wszystkich sasiadach
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				anktualna->set_new_value(x);
				anktualna->array[i] = j;

				number_ask_score++;
				if (CountScore(secret, anktualna) >= CountScore(secret, x))
				{
					x->set_new_value(anktualna);
				}
			}
		}

		if (CountScore(secret, x) == MAX_SCORE)
			break;

	}

	cout << "Wspinaczokwy: \t";
	x->print();
	cout << "\t" << CountScore(secret, x);
	cout << "\t" << number_ask_score;
	cout << "\t" << (double)CountScore(secret,x)/number_ask_score << " solution quality";
	cout << endl;

	delete x, anktualna, Best;
}

void wspinaczokwy(Number *secret)
{

	Number* x = new Number(SIZE);
	x->random();
	Number *Best = new Number(SIZE);
	Number *anktualna = new Number(SIZE);

	int iterations = 0;
	for ( ; iterations < MAX_ITERATIONS; iterations++)
	{
		// Po wszystkich sasiadach
		for (int i = 0; i < SIZE; i++)
		{

			anktualna->set_new_value(x);

			// dodaj -1 i +1 do kazdje liczby pokolei
			if (x->array[i] < 9)
			{
				anktualna->array[i] = x->array[i] + 1;
				if (CountScore(secret, anktualna) >= CountScore(secret, x))
				{
					x->set_new_value(anktualna);
				}
			}

			anktualna->set_new_value(x);

			if (x->array[i] > 0)
			{
				anktualna->array[i] = x->array[i] - 1;
				if (CountScore(secret, anktualna) >= CountScore(secret, x))
				{
					x->set_new_value(anktualna);
				}
			}
		}

		if (CountScore(secret, x) == MAX_SCORE)
			break;

	}

	cout << "Wspinaczokwy: \t";
	x->print();
	cout << "\t" << CountScore(secret, x);
	cout << "\t" << iterations;
	cout << "\t" << (double)CountScore(secret,x)/iterations << " solution quality";
	cout << endl;

	delete x, anktualna, Best;
}


bool juz_odwiedzony(int ** tabu, Number * x, int size_tabu) {

	int j = 0;
	// po całej tablicy tabu
	for(int i = 0; i < size_tabu; i++) {
		// porównanie elementów
		j = 0;
		for( ; j < SIZE; j++) {
			if(tabu[i][j] != x->array[j]) {
				break;
			}
		}
		// jest identyczny w tablicy
		if(j == SIZE) {
			return true;
		}
	}

	return false;
}


void przeszukiwanie_tabu(Number *secret)
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

	int w = 100;
	int liczba_w_tabu = 0;

	int **tab2 = new int *[w];
	for (int i = 0; i < w; ++i)
	{
		tab2[i] = new int[SIZE];
		for (int j = 0; j < SIZE; ++j)
			tab2[i][j] = 0;
	}

	Number* x = new Number(SIZE);
	x->random();
	Number *Best = new Number(SIZE);
	Number *anktualna = new Number(SIZE);

	int iterations = 0;
	for ( ; iterations < MAX_ITERATIONS; iterations++)
	{
		// Po wszystkich sasiadach
		for (int i = 0; i < SIZE; i++)
		{
			anktualna->set_new_value(x);

			if (x->array[i] < 9)
			{
				anktualna->array[i] = x->array[i] + 1;
				int a = CountScore(secret, anktualna);
				int b = CountScore(secret, x);
				// cout << "Aktualna1 " << a << " ";
				// anktualna->print();
				// cout << "Max1 " << b << " ";
				// x->print();
				if (a >= b)
				{
					if(!juz_odwiedzony(tab2, anktualna, w)) {
						x->set_new_value(anktualna);
						//dodaj do tabu x
						for (int j = 0; j < SIZE; j++)
						{
							tab2[liczba_w_tabu%w][j] = x->array[j];
						}
						liczba_w_tabu++;
					}
				}
			}

			anktualna->set_new_value(x);

			if (x->array[i] > 0)
			{
				anktualna->array[i] = x->array[i] - 1;
				int a = CountScore(secret, anktualna);
				int b = CountScore(secret, x);
				if (a >= b)
				{
					if(!juz_odwiedzony(tab2, anktualna, w)) {
						x->set_new_value(anktualna);
						//dodaj do tabu x
						for (int j = 0; j < SIZE; j++)
						{
							tab2[liczba_w_tabu%w][j] = x->array[j];
						}
						liczba_w_tabu++;
					}
				}
			}

		}

		if (CountScore(secret, x) >= CountScore(secret, Best))
		{
			Best->set_new_value(x);
		}

	}

	cout << "Lista Tabu: \t";
	Best->print();
	cout << "\t" << CountScore(secret, x);
	cout << "\t" << iterations;
	cout << "\t" << (double)CountScore(secret,x)/iterations << " solution quality";
	cout << endl;

	//wypisz tab2[w][k]
	// for (int i = 0; i < w; ++i, cout << endl)
	// 	for (int j = 0; j < count_number_to_find; ++j)
	// 		cout << tab2[i][j] << '\t';

	//zniszcz tab2
	for (int i(0); i < w; ++i)
		delete[] tab2[i];
	delete[] tab2;
	tab2 = NULL;

	delete tab2;

	delete Best, x, anktualna;
}

void symulowane_wyzarzanie(Number* secret) {

	// https://nowosad.github.io/ahod/11-simulated-annealing.html#13
	// 1. Wybierz losowe rozwiązanie startowe i. Ustal paramter T = T_max
	// 2. Wylicz f(i), czyli koszt rozwiązania i.
	// 3. Wyznacz propozycję nowego rozwiązania j (np. losowy sąsiad).
	// 4. Wylicz f(j), czyli koszt rozwiązania j.
	// 5. Zaakceptuj nowe rozwiązanie, jeżeli obniża one całkowity koszt. Jeżeli jednak ta zmiana podwyższa całkowity koszt to nowe rozwiązanie może być przyjęte z pewnym prawdopodobieństwem.
	// 6. Zmniejsz wartość parametru T.
	// 7. Zakończ algorytm lub wróć do kroku 3.

	double T_MAX = 100.0;
	double T = T_MAX;

	// 1. Random number
	Number* x = new Number(SIZE);
	x->random();
	Number* sasiad = new Number(SIZE);

	int iterations = 0;
	for ( ; iterations < MAX_ITERATIONS; iterations++) {

		sasiad->set_new_value(x);

		// 3. generate position 0-max and number between 0 and 9: */
		int value = rand() % 10;
		int position = rand() % SIZE;
		sasiad->array[position] = value;

		// 2.
		int a = CountScore(secret, x);
		// 4.
		int b = CountScore(secret, sasiad);

		// 5.
		if (b >= a)
		{
			// nowe rozwizanie lepsze, to zawsze nadpisz
			x->set_new_value(sasiad);
		} else {
			// nowe rozwiazanie gorsze, zobaczy czy nadpisac
			double result;
			result = exp ((b-a)/T);

			double randd = (rand() % 100) / 100;

			if ( result > randd ) {
				x->set_new_value(sasiad);
			}
            //Stygnięcie przy stałej temperaturze otoczenia
			if (T > 0)
				T = T -2.0;

		}

		if (CountScore(x, secret) == MAX_SCORE)
			break;

	}

	cout << "Wyzarzanie: \t";
	x->print();
	cout << "\t" << CountScore(secret, x);
	cout << "\t" << iterations;
	cout << "\t" << (double)CountScore(secret,x)/iterations << " solution quality";
	cout << endl;

	delete x, sasiad;

}

int main()
{

	srand(time(NULL));

	WEIGHT_BULL = 5;
	WEIGHT_COW = 2;
	SIZE = 9;
	MAX_SCORE = SIZE * WEIGHT_BULL;
	double max_iteration = (int)((pow(10 ,SIZE / 2.0) ));
	MAX_ITERATIONS = (int)max_iteration;
	cout << "MAX_ITERATIONS\t" << MAX_ITERATIONS << endl;
	cout << "MAX_SCORE\t" << MAX_SCORE << endl;

	Number* secret = new Number(SIZE);
	secret->random();
	cout << "Secret number: \t";
	secret->print();
	cout << "\tScore  \tIterations";
	cout << endl;

	OCENA_ITERACJA=0;

    auto start = std::chrono::high_resolution_clock::now();
	bruteforce(secret);
	auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    auto start2 = std::chrono::high_resolution_clock::now();
	wspinaczokwy(secret);
	auto finish2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = finish2 - start2;
    std::cout << "Elapsed time: " << elapsed2.count() << " s\n";

    auto start3 = std::chrono::high_resolution_clock::now();
	wspinaczokwy_all_neighbor(secret);
	auto finish3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed3 = finish3 - start3;
    std::cout << "Elapsed time: " << elapsed3.count() << " s\n";

    auto start4 = std::chrono::high_resolution_clock::now();
	wspinaczokwy_random(secret);
	auto finish4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed4 = finish4 - start4;
    std::cout << "Elapsed time: " << elapsed4.count() << " s\n";

    auto start5 = std::chrono::high_resolution_clock::now();
	przeszukiwanie_tabu(secret);
	auto finish5 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed5 = finish5 - start5;
    std::cout << "Elapsed time: " << elapsed5.count() << " s\n";

    auto start6 = std::chrono::high_resolution_clock::now();
	symulowane_wyzarzanie(secret);
	auto finish6 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed6 = finish6 - start6;
    std::cout << "Elapsed time: " << elapsed6.count() << " s\n";

	cout << "Calls to CountScore: " << OCENA_ITERACJA;

	delete secret ;
	return 0;
}
