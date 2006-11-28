#include "pathplan2.h"
#include <math.h>

using namespace std;

vector<node> pathplan2::get_graph(int *map, int width, int height, int sx, int sy, int tx, int ty)
{
    counter = 0;

    w = width;
    h = height;
    targetx=tx;
    targety=ty;

    int beginx = sx;
    int beginy = sy;

	vector<node>graph;
	list<node>act;
	list<node>pass;

	tmap = new int[w*h];
	for(int i=0; i<w*h; i++) tmap[i] = map[i];

    if(map[tx+ty*w]==0) { cout << "ziel gibt es nicht." << endl; return graph; }
    if(map[sx+sy*w]==0) { cout << "quelle gibt es nicht." << endl; return graph; }

    list<node>::iterator ci;

    node A;
    A.x = sx;
    A.y = sy;
    A.F = prune(sx,sy,tx,tx)+tmap[sx+sy*w];
    A.G = tmap[sx+sy*w];
    A.H = prune(sx,sy,tx,tx);
    A.px = sx;
    A.py = sy;
    act.push_back(A);

    bool found = false;

    while(!found && !act.empty())
    {
        if(counter!=0)
        {
            act.sort();
            A = act.front();
            sx= A.x;
            sy= A.y;
        }

        node B;
        B = expand(sx,sy,sx+1,sy, A.G);
        if(B.used) act.push_back(B);

        node C;
        C = expand(sx,sy,sx-1,sy, A.G);
        if(C.used) act.push_back(C);

        node D;
        D = expand(sx,sy,sx,sy+1, A.G);
        if(D.used) act.push_back(D);

        node F;
        F = expand(sx,sy,sx,sy-1, A.G);
        if(F.used) act.push_back(F);


        pass.push_back(A);
        act.remove(A);
        tmap[sx+sy*w] = 0;

        //if(counter>30)break;

        if(A.x==tx && A.y==ty) found=true;

        counter++;
    }

    if(!found) cout << "kein Weg..\n";

    /*
        Pfad rekonstruieren.
    */
    list<node> togo;
    bool wayok = false;
    while(!wayok && found)
    {
        node A;
        for(ci=pass.begin(); ci!=pass.end(); ci++)
        {
            A = *ci;
            //cout << A << sx <<endl;
            if(A.x==sx && A.y==sy)
            {
                togo.push_front(A);
                sx = A.px;
                sy = A.py;
                break;
            }


        }
        //Anfang gefunden. Knoten verweist auf sich selbst.
        if(beginx==A.x && beginy==A.y) { wayok = true;  }
    }

    if(found)
    {
        for(ci=togo.begin(); ci!=togo.end(); ci++)
        {
            graph.push_back(*ci);
        }
    }

    delete tmap;
    return graph;
}


double pathplan2::prune(int sx, int sy, int tx, int ty)
{
    if(sx>=0 && sx<w && tx>=0 && tx<w && sy>=0 && sy<h && ty>=0 && ty<h )
    {
        double a;
        double b;
        a = (double)sx - (double)tx;
        b = (double)sy - (double)ty;
        return (int(sqrt(a*a + b*b)));
    }
    else return w*h;
}



bool pathplan2::enter(int sx, int sy, int tx, int ty)
{

    if(sx>=0 && sx<w && tx>=0 && tx<w && sy>=0 && sy<h && ty>=0 && ty<h)
    {
        if(tmap[tx+ty*w]>0 && tmap[sx+sy*w]>0)
        {
            if( dif(sx,tx)<=1 && dif(sy, ty)<=1 )
            {
                  return true;
            }
        }
    }
	return false;
}

int pathplan2::dif(int w1, int w2)
{
	int temp = w1 - w2;
	if(temp<0) temp *= -1;
	return temp;
}

node pathplan2::expand(int sx, int sy, int x, int y, double cost)
{
    node B;
    if(enter(sx,sy,x,y))
    {
        B.x = x;
        B.y = y;
        B.G = tmap[x+(y)*w]+cost*0.5;
        B.H = prune(x,y,targetx,targety);
        B.F = B.H+B.G;
        B.px = sx;
        B.py = sy;
        B.used = true;


/*
        for(ci=act.begin(); ci!=act.end(); ci++)
        {
            node x = *ci;
            if(x==B)
            {
                cout << "found\n";
                if(x.G<B.G)
                {
                    //cout << "found better\n";
                    act.remove(x);
                    x.px = sx;
                    x.py = sy;
                    x.G = tmap[x.x+x.y*w];
                    x.H = prune(x.x,x.y,tx,ty);
                    x.F = x.G+x.H;
                    act.push_back(x);
                }

                break;
            }
        }
*/


    }
    return B;
}
