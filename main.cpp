#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const float B = 0.3;
const int L = 10;
const int D = 2;

inline int pp(int in) { int out = (in + 1) % L;  return out;}
inline int pm(int in) { int out = (in + L - 1) % L;  return out;}

using namespace std;

class lattice {
 public:
  lattice(int x) :length(x), dimension(D), p8(exp(-8 * B)), p4(exp(-4 * B))
    {
    this->reset();
    }

  void reset()
    {
    plane.resize(length);
    for(int i = 0; i < length; ++i)
        plane[i].resize(length);

    for(int i = 0; i < length; ++i)
    for(int j = 0; j < length; ++j)
        plane[i][j] = true;
    }

  void display()
    {
    for(unsigned int i = 0; i < plane.size(); ++i)
        {for(unsigned int j = 0; j < plane.size(); ++j)
            {cout << plane[i][j];}
        cout << endl;
        }
    }

  void metropolis_update(int mlty = 1)
    {
    srand (time(NULL));

    while(mlty>0)
        {
        --mlty;
        double l = length; double d = dimension;
        double num = pow(l, d); int n = num;

        int choice = rand() % n;   //choose spin
        int nnsum1 = this->neighbors(choice);

        int r = (int)choice/length;                     //get row
        int c = choice % length;                        //and col
        plane[r][c] = !plane[r][c];                      //flip!

        int nnsum2 = this->neighbors(choice);

        if (nnsum1 >= nnsum2)
         continue;

        double rnd = rand() % 100; rnd /= rnd;
        switch(nnsum2 - nnsum1)
         {
         case 8:
          if (rnd < p8)
           continue;
         case 4:
          if (rnd < p4)
           continue;
         }

        plane[r][c] = !plane[r][c];                      //flip!
        }
    }

  int neighbors(int spin)
    {
    int r = (int)spin/length;                     //get row
    int c = spin % length;                        //and col

    int temp = 0;
    temp += plane[r][c]==plane[ r     ][ pp(c) ] ? 1 : -1;
    temp += plane[r][c]==plane[ r     ][ pm(c) ] ? 1 : -1;
    temp += plane[r][c]==plane[ pp(r) ][ c     ] ? 1 : -1;
    temp += plane[r][c]==plane[ pm(r) ][ c     ] ? 1 : -1;
    return temp;
    }


  int energy()
    {
    int temp = 0;

    for(int i = 0; i < plane.size(); ++i)
    for(int j = 0; j < plane.size(); ++j)
        {
        temp += plane[i][j]==plane[ i     ][ pp(j) ] ? 1 : -1;
        temp += plane[i][j]==plane[ pp(i) ][ j     ] ? 1 : -1;
        }

    erg = temp;
    return erg;
    }
  int energy_saved() {return erg;}

  int magnetism()
    {
    int temp = 0;

    for(int i = 0; i < plane.size(); ++i)
    for(int j = 0; j < plane.size(); ++j)
        {
        temp += plane[i][j] ? 1 : -1;
        }

    mag = temp;
    return mag;
    }
  int magnetism_saved() {return mag;}


 protected:
  vector<vector<bool> > plane;

  const double p8, p4;
  const int dimension, length;

  int erg, mag;

};


int main()
{
    cout << "Hello world!" << endl;

    lattice lll(23);
    cout << lll.energy() << endl;
    cout << lll.magnetism() << endl;
    lll.metropolis_update(10000);
    cout << lll.energy() << endl;
    cout << lll.magnetism() << endl;
    lll.display();
    lll.reset();
    lll.display();

    return 0;
}
