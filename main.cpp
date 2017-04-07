#include <iostream>
#include <vector>

#define beta 1;

using namespace std;

class lattice {
 public:
  lattice(int length)
    {
    plane.resize(length);
    for(int i = 0; i < length; ++i)
        plane[i].resize(length);

    for(int i = 0; i < length; ++i)
    for(int j = 0; j < length; ++j)
        plane[i][j] = true;

    p4 = exp(-4 * beta);
    p2 = exp(-2 * beta);
    p0 = 1;
    m2 = exp(2 * beta);
    m4 = exp(4 * beta);
    }

  void display()
    {
    for(int i = 0; i < plane.size(); ++i)
        {for(int j = 0; j < plane.size(); ++j)
            {cout << plane[i][j] ? 1 : 0;}
        cout << endl;
        }
    }

  void metropolis_update()
    {

    }


 protected:
  vector<vector<bool> > plane;

  double p4, p2, p0, m2, m4;

};


int main()
{
    cout << "Hello world!" << endl;
    lattice mylat(10);

    mylat.display();

    return 0;
}
