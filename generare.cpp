#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <random>
#include <vector>
using namespace std;
void gen(string folder, int type)
{
    int ndata=1;
    vector<int> neg={0, 0, 0, 0, 0, 0, 1, 1, 1};
    vector<int> mx={100, 100, 10000, 10000, 100000, 100000, 1000000, 1000000000, 1000000000};
    for(int i=0; i<9; i++)
    {
        ndata*=10;
        mkdir(("./"+folder+to_string(i+1)).c_str());
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> dist(0 ,mx[i]+mx[i]*neg[i]);
        for(int j=1; j<10-i; j++)
        {
            ofstream o("./"+folder+to_string(i+1)+"/"+to_string(j)+".txt");
            o<<ndata<<' ';
            for(int k=0; k<ndata; k++)
            {
            if(type==0)
            {
                o<<(int)dist(rng)-neg[i]*mx[i]<<' ';
            }
            if(type==1)
            {
                if(k%100==0)
                {
                    o<<(int)dist(rng)-neg[i]*mx[i]<<' ';
                }
                else o<<k<<' ';
            }
            if(type==2)
            {
                o<<ndata-k<<' ';
            }
            }
            o.close();
        }
    }
}
int main()
{
    gen("random", 0);
    gen("almost", 1);
    gen("reverse", 2);
    return 0;
}
