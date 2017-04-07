#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int B = 0.5;
const int L = 32;
const int D = 2;

using namespace std;

inline int pp(int in) { int out = (in + 1) % L;  return out;}
inline int pm(int in) { int out = (in + L - 1) % L;  return out;}

void write_out(vector<double> *h);

class lattice {
 public:
  lattice(int x, float y) :length(x), beta(y), dimension(D), p8(exp(-8 * beta)), p4(exp(-4 * beta))
    {
    srand (time(NULL));
    this->reset();
    }

  void reset(){
    plane.resize(length);
    for(int i = 0; i < length; ++i)
        plane[i].resize(length);

    for(int i = 0; i < length; ++i)
    for(int j = 0; j < length; ++j)
        plane[i][j] = true;
    }

  void display(){
    for(unsigned int i = 0; i < plane.size(); ++i){
        for(unsigned int j = 0; j < plane.size(); ++j)
            cout << plane[i][j];
        cout << endl;
        }
    }

  void metropolis_update(int mlty = 1){
    while(mlty>0){
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

        double rnd = rand() % 100; rnd /= 100;
        switch(nnsum2 - nnsum1){
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

  int neighbors(int spin){
    int r = (int)spin/length;                     //get row
    int c = spin % length;                        //and col

    int temp = 0;
    temp += plane[r][c]==plane[ r     ][ pp(c) ] ? 1 : -1;
    temp += plane[r][c]==plane[ r     ][ pm(c) ] ? 1 : -1;
    temp += plane[r][c]==plane[ pp(r) ][ c     ] ? 1 : -1;
    temp += plane[r][c]==plane[ pm(r) ][ c     ] ? 1 : -1;
    return temp;
    }

  int energy(){
    int temp = 0;

    for(int i = 0; i < plane.size(); ++i)
    for(int j = 0; j < plane.size(); ++j){
        temp += plane[i][j]==plane[ i     ][ pp(j) ] ? 1 : -1;
        temp += plane[i][j]==plane[ pp(i) ][ j     ] ? 1 : -1;
        }

    erg = temp;
    return erg;
    }
  int energy_saved() {return erg;}

  int magnetism(){
    int temp = 0;

    for(int i = 0; i < plane.size(); ++i)
    for(int j = 0; j < plane.size(); ++j){
        temp += plane[i][j] ? 1 : -1;
        }

    mag = temp;
    return mag;
    }
  int magnetism_saved() {return mag;}

  void repetition(int rep, int l, bool m, bool e){
    if (e){energys.clear(); energys.resize(l);}
    if (m){magnets.clear(); magnets.resize(l);}

    for (int j = 0; j < rep; j++){
        this->reset();
        for (int i = 0; i < l; i++){
            this->metropolis_update();
            if (e) {energys[i] += energy();}
            if (m) {energys[i] += magnetism();}
            }
        }

    if (e){
    for (int i = 0; i < l; i++)
        energys[i] /= rep;
        }

    if (m){
    for (int i = 0; i < l; i++)
        magnets[i] /= rep;
        }

    }

  void jacknife(int skip, int seg, int n, bool m, bool e){
    if (e){energys.clear(); energys.resize(seg);}
    if (m){magnets.clear(); magnets.resize(seg);}
    this->reset();
    this->metropolis_update(skip);

    for(int j = 0; j < n; j++)
    for(int i = 0; i < seg; i++){
        this->metropolis_update();
        if (e) {energys[i] += energy();}
        if (m) {energys[i] += magnetism();}
        }

    if (e){
    for (int i = 0; i < seg; i++)
        energys[i] /= n;
        }

    if (m){
    for (int i = 0; i < seg; i++)
        magnets[i] /= n;
        }

    }

  vector<double> *energys_out(){
    return &energys;
    }

  vector<double> *magnets_out(){
    return &magnets;
    }


 protected:
  vector<vector<bool> > plane;

  const double p8, p4;
  const int dimension, length;
  const double beta;

  int erg, mag;
  vector<double> energys;
  vector<double> magnets;

};


int main()
{
    cout << "Hello world!" << endl;

    lattice l(L,B);
    l.jacknife(2000, 5000, 50, 0, 1);
//    l.repetition(50, 10000, 0, 1);
    vector<double> *h = l.energys_out();
    l.display();

    write_out(h);

    return 0;
}


void write_out(vector<double> *h)
{
    fstream mystream;
    mystream.open ("/home/fergus/Data/data.txt", fstream::out | fstream::trunc );
    for (int i = 0; i < (*h).size(); i++)
        mystream << (*h)[i] << endl;
    mystream.close();
}
