#include <iostream>
#include "pathplan2.h"

using namespace std;

int main()
{
	int w=10;
	int h=10;

	int maze[]={ 	0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,1,1,0,
			0,0,0,0,0,0,1,0,1,0,
			0,0,0,0,0,0,1,1,1,0,
			0,0,0,0,0,0,0,0,1,0,
			0,0,0,0,0,1,1,1,1,0,
			0,0,0,0,1,1,1,1,1,0,
			0,1,1,1,1,1,1,1,1,1,
			0,1,1,1,1,1,1,1,1,1,
			0,1,1,1,1,1,1,1,0,0
		   };


	for(int x=0; x<w; x++)
	{
		for(int y=0;y<h; y++)
		{
			cout << maze[x+y*w] << " ";
		}
		cout << "\n";
	}


	pathplan2 plan;

	vector<node> gothisway;

	gothisway = plan.get_graph(maze,w,h,1,1,8,8);
	
	for(int i=0; i<gothisway.size(); i++)
	{
		cout << gothisway[i];
	}


	cout << "OK"<< endl;

	return 0;
}

