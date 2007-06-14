#include <vector>
#include <list>
#include <iostream>

using namespace std;

#include "node.h"

class pathplan2
{
	private:
	  int dif(int w1, int w2);
      bool enter(int sx, int sy, int tx, int ty);
      double prune(int sx, int sy, int tx, int ty);
      int w;
      int h;
      int *tmap;
      node expand(int sx, int sy, int x, int y, double cost);
      int targetx;
      int targety;

	public:
      vector<node> get_graph(int *map, int w, int h, int sx, int sy, int tx, int ty);
      int counter;

};
