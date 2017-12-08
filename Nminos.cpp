// Nminos.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <climits>
#include "Entity.h"

//#define MY_DEBUG_DEF
#define LOG_TIME 3


using namespace std;
using namespace Entities;


void drawArr(int** arr, int m, int n);


bool isRowEmpty(int**arr, int m, int n, int k);

bool isColEmpty(int**arr, int m, int n, int k);

Figure* removeZeros(int** arr, int m, int n);

void recDandy(int** arr, int m, int n, int x, int y);

bool isDandy(int** arr, int m, int n);

int** manualFigureInput(int m, int n);

bool isValid(int**arr, int m, int n, vector<Figure*> figures);

Figure* findByID(vector<Figure*> figures, int id);

int** init_arr(int m, int n);

void insertNum(int**arr, int x, int y, int num);

vector<int**> combinations(int m, int n, std::vector<Figure*> figures);

int** copyArr(int** arr, int m, int n);

void swap(int**arr, int x, int y, int x2, int y2);

void algorithm(vector<Figure*> figures, int m, int n);

int loadBuff(int max);

void saveToFile(vector<Figure*>figures, int m, int n);

void readFromFile(vector<Figure*>*figures, int*m, int*n, char* name);

void deallocArr(int** arr, int m, int n);

void logAllocs();


int main(int argc, char** argv)
{
	std::vector<Figure*> figures;

	int m = 4, n = 6;

	if (argc==2) readFromFile(&figures, &m, &n, argv[1]);

	int a;
	cout << "0. Manual" << endl;
	cout << "1. Auto" << endl;
	a = loadBuff(1);
	if (a == 0)//manual test
	{


		while (true)
		{
			cout << "0. Add figure" << endl;
			cout << "1. Change m, n" << endl;
			cout << "2. Save to file" << endl;
			cout << "3. Load from file" << endl;
			cout << "4. Run algorithm" << endl;
			cout << "5. Draw figures" << endl;
			cout << "6. Exit" << endl;
			cout << "7. Destroy all figures" << endl;
			cout << "8. Show created/destroyed int** status" << endl;
			a = loadBuff(8);

			if (a == 0)
			{
				int** arr;
				while (true)
				{
					arr = manualFigureInput(m, n);

					drawArr(arr, m, n);
					if (isDandy(arr, m, n) == 0)
					{
						cout << "This data is not nice! I want all ones neary eachother and [0][0] must be = 1! Try again ;-)" << endl;
						deallocArr(arr, m, n);
					}
					else
					{
						cout << "This data is correct" << endl;
						break;
					}
				}
				figures.push_back(removeZeros(arr, m, n));
			}
			else if (a == 1)
			{
				m = loadBuff(1000);
				n = loadBuff(1000);
			}
			else if (a == 2)
			{
				saveToFile(figures, m, n);
			}
			else if (a == 3)
			{
				readFromFile(&figures, &m, &n, "MJ.txt");
			}
			else if (a == 4)
			{
				algorithm(figures, m, n);
			}
			else if (a == 5)
			{
				for (int i = 0; i < figures.size(); i++)
					figures[i]->LogMatrix();
			}
			else if (a == 6)
			{
				for (int i = 0; i < figures.size(); i++)
					deallocArr(figures[i]->Matrix(), figures[i]->M(), figures[i]->N());
				return 0;
			}
			else if (a == 7)
			{
				for (int i = 0; i < figures.size(); i++)
					deallocArr(figures[i]->Matrix(), figures[i]->M(), figures[i]->N());
				figures.clear();
			}
			else if (a == 8)
			{
				logAllocs();
			}
		}
	}
	else if (a == 1)
	{

		int** d = new int*[2];
		d[0] = new int[1];
		d[0][0] = 1;
		d[1] = new int[1];
		d[1][0] = 1;

		int** dd = new int*[1];
		dd[0] = new int[2];
		dd[0][0] = 1;
		dd[0][1] = 1;

		int**t1 = new int*[2];
		t1[0] = new int[2];
		t1[1] = new int[2];
		t1[0][0] = 1;
		t1[1][0] = 0;
		t1[0][1] = 1;
		t1[1][1] = 1;

		int**t2 = new int*[2];
		t2[0] = new int[2];
		t2[1] = new int[2];
		t2[0][0] = 1;
		t2[1][0] = 1;
		t2[0][1] = 0;
		t2[1][1] = 1;

		//drawArr(t1, 2, 2);
		//drawArr(t2, 2, 2);

		int**q1 = new int*[3];
		q1[0] = new int[2];
		q1[1] = new int[2];
		q1[2] = new int[2];
		q1[0][0] = 1;
		q1[0][1] = 0;
		q1[1][0] = 1;
		q1[1][1] = 1;
		q1[2][0] = 0;
		q1[2][1] = 1;

		int**q2 = new int*[4];
		q2[0] = new int[2];
		q2[1] = new int[2];
		q2[2] = new int[2];
		q2[3] = new int[2];
		q2[0][0] = 1;
		q2[0][1] = 1;
		q2[1][0] = 1;
		q2[1][1] = 1;
		q2[2][0] = 1;
		q2[2][1] = 1;
		q2[3][0] = 1;
		q2[3][1] = 1;

		//figures.push_back(new Figure(d, 2, 1));
		//figures.push_back(new Figure(copyArr(d, 2, 1), 2, 1));
		////figures.push_back(new Figure(copyArr(d, 2, 1), 2, 1));
		//figures.push_back(new Figure(copyArr(d, 2, 1), 2, 1));
		//figures.push_back(new Figure(copyArr(d, 2, 1), 2, 1));
		//figures.push_back(new Figure(copyArr(d, 2, 1), 2, 1));
		//figures.push_back(new Figure(copyArr(t, 2, 2), 2, 2));
		//figures.push_back(new Figure(copyArr(t, 2, 2), 2, 2));

		for (int i = 0; i<1; i++)
			figures.push_back(new Figure(copyArr(q1, 3, 2), 3, 2));

		for (int i = 0; i<1; i++)
			figures.push_back(new Figure(copyArr(d, 2, 1), 2, 1));

		for (int i = 0; i<1; i++)
			figures.push_back(new Figure(copyArr(t1, 2, 2), 2, 2));

		for (int i = 0; i<1; i++)
			figures.push_back(new Figure(copyArr(t2, 2, 2), 2, 2));

		for (int i = 0; i<0; i++)
			figures.push_back(new Figure(copyArr(dd, 1, 2), 1, 2));

		for (int i = 0; i<1; i++)
			figures.push_back(new Figure(copyArr(q2, 4, 2), 4, 2));

		cout << "Objects have been created:" << endl;
		for (int i = 0; i < figures.size(); i++)
		{
			cout << "Figure number " << i + 1 << ":" << endl;
			figures[i]->LogMatrix();
			cout << endl;
		}

		cout << "Starting algorithm with objects above for map size: m = " << m << ", n = " << n << endl;

		algorithm(figures, m, n);



		for (int i = 0; i < figures.size(); i++)
			deallocArr(figures[i]->Matrix(), figures[i]->M(), figures[i]->N());

		logAllocs();
	}


	return 0;
}

bool isRowEmpty(int**arr, int m, int n, int k)
{
	for (int i = 0; i < m; i++)
	{
		if (arr[i][k] != 0)
			return false;
	}
	return true;
}

bool isColEmpty(int**arr, int m, int n, int k)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[k][i] != 0)
			return false;
	}
	return true;
}

Figure* removeZeros(int** arr, int m, int n)
{
	int ms = 0, me = m - 1, ns = 0, ne = n - 1;

	//check last, first coordinates on x and y to minimise vectors of all 0
#ifdef MY_DEBUG_DEF
	cout << "Before: " << ms << " " << me << " " << ns << " " << ne << endl;
#endif // MY_DEBUG_DEF

	for (int i = 0; i < m; i++)
	{
		if (isColEmpty(arr, m, n, i))
		{
			ms++;
#ifdef MY_DEBUG_DEF
			cout << "ms++, ms: " << ms << endl;
#endif // MY_DEBUG_DEF
		}
		else
			break;
	}
	for (int i = me; i > ms; i--)
	{
		if (isColEmpty(arr, m, n, i))
		{
			me--;
#ifdef MY_DEBUG_DEF
			cout << "me--, me: " << me << endl;
#endif
		}
		else
			break;
	}
	for (int i = 0; i < n; i++)
	{
		if (isRowEmpty(arr, m, n, i))
		{
			ns++;
#ifdef MY_DEBUG_DEF
			cout << "ns++, ns: " << ns << endl;
#endif
		}
		else
			break;
	}
	for (int i = ne; i > ns; i--)
	{
		if (isRowEmpty(arr, m, n, i))
		{
			ne--;
#ifdef MY_DEBUG_DEF
			cout << "ne--, ne: " << ne << endl;
#endif
		}
		else
			break;
	}

	//figure out the new size of array
	int newM = me - ms + 1;
	int newN = ne - ns + 1;

#ifdef MY_DEBUG_DEF
	cout << "DATA: " << ms << " " << me << " " << ns << " " << ne << endl;
#endif
	int**ret = init_arr(newM, n);

	for (int i = 0; i < newM; i++)
	{
		for (int j = 0; j < newN; j++)
		{
			ret[i][j] = arr[i + ms][j + ns];
		}
	}

	deallocArr(arr, m, n);

	return new Figure(ret, newM, newN);
}

void recDandy(int** arr, int m, int n, int x, int y)
{
	if (arr[x][y] == 1)
	{
		arr[x][y] = 2;
		if (x + 1 < m)
			recDandy(arr, m, n, x + 1, y);
		if (y + 1 < n)
			recDandy(arr, m, n, x, y + 1);
	}
}

bool isDandy(int** arr, int m, int n)
{
	if (m > 0 && n > 0 && arr[0][0]==0)
		return false;


	//checks if there are no unconnected groups of ones
	int** copy = copyArr(arr, m, n);
	recDandy(copy, m, n, 0, 0);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (copy[i][j] == 1)
			{
				deallocArr(copy, m, n);
				return false;
			}
		}
	}
	deallocArr(copy, m, n);
	return true;
}

int** manualFigureInput(int m, int n)
{
	int**ret = init_arr(m, n);
	int x, y;
	drawArr(ret, m, n);

	int a;
	do
	{
		std::cout << "0. Accept current matrix as new figure" << endl;
		std::cout << "1. Swap x-th,y-th digit" << endl;

		a = loadBuff(1);
		if (a == 0)
			break;

		std::cout << "Give me x:"<<endl;
		x = loadBuff(m);
		std::cout << "Give me y:"<<endl;
		y = loadBuff(n);

		ret[x][y] = (ret[x][y] == 0) ? 1 : 0;
		drawArr(ret, m, n);
	} while (a != 2);
	return ret;
}

bool isValid(int**arr, int m, int n, vector<Figure*> figures)
{
#ifdef MY_DEBUG_DEF
	cout << "Before Validation:" << endl;
	drawArr(arr, m, n);
#endif
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] > 0)
			{
				//replace with -1s
				Figure *temp = findByID(figures, arr[i][j]);
#ifdef MY_DEBUG_DEF
				cout << "Checking figure: id" << arr[i][j] << endl;
				temp->LogMatrix();
#endif

				arr[i][j] = 0;
				if (temp->fits(arr, m, n, i, j))
				{
					temp->write(arr, m, n, i, j);
				}
				else
				{
					return false;
				}
			}
		}
	}


	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] != -1)
				return false;
		}
	}
	return true;
}

Figure* findByID(vector<Figure*> figures, int id)
{
	//cout << "searching by ID" << endl;
	for (int i = 0; i < figures.size(); i++)
	{
		if (figures[i]->Id() == id)
		{
			//cout << "found by ID" << endl;
			return figures[i];
		}
	}
}

void drawArr(int** arr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int** init_arr(int m, int n)
{
	int**arr = new int*[m];
	for (int i = 0; i < m; i++)
	{
		arr[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = 0;
		}
	}
	return arr;
}

void insertNum(int**arr, int x, int y, int num)
{
	arr[x][y] = num;
}

vector<int**> combinations(int m, int n, std::vector<Figure*> figures)
{
	clock_t start, end;
	start = clock();
	int Daszczu = m*n;
	int all = 1;
	if (figures.size() > 1)
	{
		for (int i = 0; i < figures.size(); i++)
			all *= Daszczu - i;
		cout << "Estimated return array size: " << all << endl;
	}


	cout << "starting combinations creation. M: " << m << ", N: " << n << ", figures size: " << figures.size() << endl;
	vector<int**> ret;
	vector<int**> temp;
	ret.push_back(init_arr(m, n));


	for (int i = 1; i < figures.size() + 1; i++)
	{
		for (int j = 0; j < ret.size(); j++)
		{
			for (int k = 0; k < m; k++)
			{
				for (int d = 0; d < n; d++)
				{
					clock_t end = clock();
					double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;

					if (elapsed_secs > LOG_TIME)
					{
						start = clock();
						cout << "Progress: " << ret.size() << "/" << all << "(" << 100.*ret.size() / all << "%)" << endl;
					}

					if (ret[j][k][d] == 0)
					{
						int**buf = copyArr(ret[j], m, n);
						insertNum(buf, k, d, i);
						temp.push_back(buf);
					}
				}
			}
		}
		cout << "Switching vectors. Temp size: " << temp.size() << endl;

		for (int j = 0; j < ret.size(); j++)
			deallocArr(ret[j], m, n);
		ret.clear();

		for (int j = 0; j < temp.size(); j++)
			ret.push_back(temp[j]);

		temp.clear();
	}
	return ret;
}

int** copyArr(int** arr, int m, int n)
{
	int**ret = new int*[m];
	for (int i = 0; i < m; i++)
	{
		ret[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			ret[i][j] = arr[i][j];
		}
	}
	return ret;
}

void swap(int**arr, int x, int y, int x2, int y2)
{
	int buf = arr[x][y];
	arr[x][y] = arr[x2][y2];
	arr[x2][y2] = buf;
}

void algorithm(vector<Figure*> figures, int m, int n)
{
	clock_t begin = clock();
	clock_t aStart = clock();

	vector<int**>combs = combinations(m, n, figures);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "done in " << elapsed_secs << endl;
	cout << "Elements: " << combs.size() << endl;
	cout << "Searching for valid combinations..." << endl;


	begin = clock();

	vector<int**>initialValues;
	cout << "copying combinations started" << endl;
	for (int i = 0; i < combs.size(); i++)
	{
		initialValues.push_back(copyArr(combs[i], m, n));
	}
	cout << "copying combinations over" << endl;

	for (int i = 0; i < combs.size(); i++)
	{
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		if (elapsed_secs > LOG_TIME)
		{
			begin = clock();
			cout << "Progress: " << i << "/" << combs.size() << "(" << 100.*i / combs.size() << "%)" << endl;
		}


		if (isValid(combs[i], m, n, figures))
		{
			cout << i << " is valid: " << endl;
			drawArr(initialValues[i], m, n);
		}
	}
	clock_t aEnd = clock();
	double total_elapsed_secs = double(aEnd - aStart) / CLOCKS_PER_SEC;

	for (int i = 0; i < combs.size(); i++)
	{
		deallocArr(combs[i], m, n);
		deallocArr(initialValues[i], m, n);
	}

	cout << "Algorithm done! Entire calculation time: " << total_elapsed_secs <<"s"<< endl;
}

int loadBuff(int max)
{
	int a;
	cout << "Input from 0 to " << max << endl;
	while (cin>>a &&(a<0 || a>max))
	{
		cout << "Wrong Input! Input from 0 to " << max << endl;
		std::cin.ignore(INT_MAX, '\n');
		cin.clear();
		//DUSNT WORK, NEED THE HELP OF A LOVELY EXPERT

		//LOVELY EXPERT PLIS HELP
	}

	//CHECKS
	return a;
}

void saveToFile(vector<Figure*> figures, int m, int n)
{
	//File structure:
	//1. m
	//2. n
	//3. num of figures
	//4. figure m
	//5. figure n
	//6. zeros, ones

	ofstream file;
	file.open("MJ.txt");
	file << m << "\n";
	//cout << m << endl;
	file << n << "\n";
	//cout << n << endl;
	file << figures.size() << "\n";
	for (int i = 0; i < figures.size(); i++)
	{
		file << figures[i]->M() << "\n";
		//cout << figures[i]->M() << endl;
		file << figures[i]->N() << "\n";
		//cout << figures[i]->N() << endl;
		for (int a = 0; a < figures[i]->M(); a++)
		{
			for (int b = 0; b < figures[i]->N(); b++)
			{
				file << figures[i]->Matrix()[a][b] << "\n";
				//cout << figures[i]->Matrix()[a][b] << endl;
			}
		}
	}
	file.close();
	cout << "file saved" << endl;
}

void readFromFile(vector<Figure*>*figures, int*m, int*n, char* name)
{
	figures->clear();
	ifstream file;

	file.open(name);
	if (!file.good())
	{
		cout<<"File does not exist"<<endl;
		file.close();
		return;
	}

	string line;
	vector<int> a;
	while (getline(file, line))
	{
		a.push_back(atoi(line.c_str()));
		//cout << stoi(line) << endl;
	}
	*m = a[0];
	*n = a[1];
	int g = 2;
	for (int i = 0; i < a[2]; i++)
	{
		int fm = a[++g];
		int fn = a[++g];
		//cout << fm << " " << fn << endl;
		int** arr = init_arr(fm, fn);
		for (int j = 0; j < fm; j++)
		{
			for (int k = 0; k < fn; k++)
			{
				arr[j][k] = a[++g];
				//cout << arr[j][k] << endl;
			}
		}
		figures->push_back(new Figure(arr, fm, fn));
	}
	file.close();
	cout << "file read" << endl;
#ifdef MY_DEBUG_DEF
	cout << figures->size() << endl;
	cout << *m << endl;
	cout << *n << endl;
#endif // MY_DEBUG_DEF


}

void deallocArr(int** arr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

void logAllocs()
{
	//cout << "Created: " << CREATED << endl;
	//cout << "Destroyed: " << DESTROYED << endl;
	//cout << "Live: " << CREATED - DESTROYED << endl;

	//cout << "Created rows: " << CREATED_ROWS << endl;
	//cout << "Destroyed rows: " << DESTROYED_ROWS << endl;
	//cout << "Live rows: " << CREATED_ROWS -DESTROYED_ROWS << endl;
}
