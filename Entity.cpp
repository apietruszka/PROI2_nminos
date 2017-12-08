#include "Entity.h"
#include <iostream>

using namespace std;

namespace Entities
{

  int GLOBAL_ID = 0;

  int Entity::Id() {return id;}

  Entity::Entity() : id(++GLOBAL_ID)
  {
  #ifdef MY_DEBUG_DEF
    cout << "constructing Entity!" << endl;
  #endif
  }
  void Entity::LogMatrix()
  {
    cout << "Sorry, I don't have any Matrix that i could log!" << endl;
  }

  Figure::Figure(int**_matrix, int _m, int _n) : matrix(_matrix), m(_m), n(_n)
  {
#ifdef MY_DEBUG_DEF
    cout << "constructing Figure!" << endl;
#endif
  }

  int Figure::M()
  {
    return m;
  }

  int Figure::N()
  {
    return n;
  }

  int** Figure::Matrix() { return matrix; }

  void Figure::LogMatrix()
  {
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
  }

  bool Figure::fits(int**arr, int N, int M, int x, int y)
  {
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (matrix[i][j] == 1)
        {
#ifdef MY_DEBUG_DEF
          cout << "checking" << endl;
#endif

          if (!isInRange(x + i, N) || !isInRange(y + j, M))
          {
#ifdef MY_DEBUG_DEF
            cout << "doesnt fit: out of range" << endl;
#endif
            return false;
          }
          if ((arr[x + i][y + j] != 0))
          {
#ifdef MY_DEBUG_DEF
            cout << "doesnt fit: occupied" << endl;
#endif
            return false;
          }
#ifdef MY_DEBUG_DEF
          cout << "might fit" << endl;
#endif
        }
      }
    }
#ifdef MY_DEBUG_DEF
    cout << "fits" << endl;
#endif
    return true;
  }

  void Figure::write(int**arr, int N, int M, int x, int y)
  {
#ifdef MY_DEBUG_DEF
    cout << "Before writing:" << endl;
    drawArr(arr, N, M);
#endif
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (matrix[i][j] == 1)
          arr[x + i][y + j] = -1;
      }
    }
#ifdef MY_DEBUG_DEF
    cout << "After writing:" << endl;
    drawArr(arr, N, M);
#endif
  }
  bool Figure::isInRange(int x, int max)
  {
    if (x < max) return true;
    return false;
  }
}
