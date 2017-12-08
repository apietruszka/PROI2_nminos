#ifndef ENTITY_H
#define ENTITY_H

namespace Entities
{
  class Entity
  {
  	int id;
  public:
  	int Id();

  	Entity();
  	void LogMatrix();
  };

  class Figure : public Entity
  {
  	int m, n;
  	int** matrix;

  public:
  	Figure(int**_matrix, int _m, int _n);

  	int M();

  	int N();

  	int**Matrix();

  	void LogMatrix();

  	bool fits(int**arr, int N, int M, int x, int y);

  	void write(int**arr, int N, int M, int x, int y);

  	bool isInRange(int x, int max);
  };

}



#endif
