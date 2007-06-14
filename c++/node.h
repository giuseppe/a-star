#include <iostream>


using namespace std;


class node
{
   friend ostream &operator<<(ostream &, const node &);

   public:
      int x;
      int y;
      double F; // heuristik F = G+H (bewegungskosten+luftlinie)
      double G;
      double H;
      int px; //eltern
      int py;
      bool used;

      node();
      node(const node &);
      ~node(){};
      node &operator=(const node &rhs);
      int operator==(const node &rhs) const;
      int operator<(const node &rhs) const;
};
