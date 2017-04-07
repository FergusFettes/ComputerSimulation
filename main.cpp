#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

const int B = 1;
const int L = 10;
const int D = 2;

inline short int pp(short int in) { short int out = (in + 1) % L;  return out;}
inline short int pm(short int in) { short int out = (in + L - 1) % L;  return out;}

using namespace std;

class lattice {
 public:
  lattice(int length)
    {
    dimension = D;

    plane.resize(length);
    for(int i = 0; i < length; ++i)
        plane[i].resize(length);

    for(int i = 0; i < length; ++i)
    for(int j = 0; j < length; ++j)
        plane[i][j] = true;

    p4 = exp(-4 * B);
    p2 = exp(-2 * B);
    p0 = 1;
    m2 = exp(2 * B);
    m4 = exp(4 * B);

    }

  void display()
    {
    for(int i = 0; i < plane.size(); ++i)
        {for(int j = 0; j < plane.size(); ++j)
            {cout << plane[i][j];}
        cout << endl;
        }
    }

  void metropolis_update(int multi=1)
    {
    double l = length; double d = dimension;
    double num = pow(l, d); int n = num;
    int choice = rand() % n;   //choose spin
    int r = (int)choice/length;                     //get row
    int c = choice % length;                        //and col


    int nnsum += plane[r][c]==plane[r][pp(c)] ? 1 : -1;

    }


 protected:
  vector<vector<bool> > plane;

  double p4, p2, p0, m2, m4;

  int dimension, length;

};


int main()
{
    cout << "Hello world!" << endl;
    lattice mylat(L);

    mylat.display();

    return 0;
}
