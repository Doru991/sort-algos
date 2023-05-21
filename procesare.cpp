#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#define MAXLOG 5
#define SORTNAME "qsort"
#define FUNCTION quicksort
using namespace std;
void sortare(vector<int>&, int);
int main()
{
    vector<string> prefix= {"random", "almost", "reverse"};
    for(auto e:prefix)
    {
        ofstream o("./"+e+"_"+SORTNAME+".txt");
        o<<"input_size,t_avg,t_min,t_max\n";
        for(int i=1; i<=MAXLOG; i++)
        {
            cout<<endl<<i<<' ';
            vector<double> times;
            string folder=e+to_string(i);
            for(int j=1; j<=10-i; j++)
            {
                cout<<j<<' ';
                ifstream f("./"+folder+"/"+to_string(j)+".txt");
                int n;
                f>>n;
                vector<int> a(n);
                for(int i=0; i<n; i++)
                {
                    f>>a[i];
                }
                f.close();
                auto start = std::chrono::steady_clock::now();
                sortare(a, n);
                auto fin = std::chrono::steady_clock::now();
                auto diff = fin - start;
                times.push_back(std::chrono::duration<double, std::milli> (diff).count());
                for(int k=0; k<n; k++)
                {
                    if(k<n-1 && a[k]>a[k+1])
                    {
                        cout<<"Sortare incorecta"<<endl;
                        return 1;
                    }
                }
            }
                double s=0.0, mx=times[0], mn=times[0];
                for(auto f:times)
                {
                    s+=f;
                    mx=max(mx, f);
                    mn=min(mn, f);
                }
                o<<i<<','<<s/(double)(10-i)<<','<<mn<<','<<mx<<endl;
        }
        o.close();
    }
    return 0;
}
void selsort(vector<int> &a, int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(a[i]>a[j])
            {
                int x=a[i];
                a[i]=a[j];
                a[j]=x;
            }
        }
    }
    return;
}
void bubblesort(vector<int> &a, int n)
{
    bool sc=1;
    while(sc)
    {
        sc=0;
        for(int i=0; i<n-1; i++)
        {
            if(a[i]>a[i+1])
            {
                sc=1;
                int x=a[i];
                a[i]=a[i+1];
                a[i+1]=x;
            }
        }
    }
    return;
}
void inssort(vector<int> &a, int n)
{
    int i=1;
    while(i<n)
    {
        int x=a[i];
        int j=i-1;
        while(j>=0 && a[j]>x)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=x;
        i++;
    }
    return;
}
void countsort(vector<int> &a, int n)
{
    int mx=a[0], mn=a[0];
    for(int i=1; i<n; i++)
    {
        mx=max(mx, a[i]);
        mn=min(mn, a[i]);
    }
    int offset=0;
    if(mn<0) offset=mn*-1;
    vector<int> c(offset+mx+1, 0);
    for(int i=0; i<n; i++)
    {
        c[a[i]+offset]+=1;
    }
    int index=0;
    for(int i=0; i<(int)c.size(); i++)
    {
        for(int j=0; j<c[i]; j++)
        {
            a[index++]=i-offset;
        }
    }
    return;
}
void mer(vector<int> &a, vector<int> &b, int l, int r)
{
    int m=(l+r)/2;
    int i1=l, i2=m;
    for(int i=l; i<r; i++)
    {
        if(i1<m &&(i2>=r || a[i1]<=a[i2]))
        {
            b[i]=a[i1++];
        }
        else
        {
            b[i]=a[i2++];
        }
    }
    for(int i=l; i<r; i++)
    {
        a[i]=b[i];
    }
}
void mer2(vector<int> &a, vector<int> &b, int l, int r)
{
    int m=(l+r)/2;
    int i1=l, i2=m;
    for(int i=l; i<r; i++)
    {
        if(i1<m &&(i2>=r || a[i1]<=a[i2]))
        {
            b[i]=a[i1++];
        }
        else
        {
            b[i]=a[i2++];
        }
    }
}
void ms(vector<int> &a, vector<int> &b, int l, int r)
{
    if(l>=r-1) return;
    int m=(l+r)/2;
    ms(a, b, l, m);
    ms(a, b, m, r);
    mer(a, b, l, r);

}
void ms2(vector<int> &b, vector<int> &a, int l, int r)
{
    if(l>=r-1) return;
    int m=(l+r)/2;
    ms2(a, b, l, m);
    ms2(a, b, m, r);
    mer2(b, a, l, r);

}
void mergesort(vector<int> &a, int n)
{
    vector<int> b(n);
    ms(a, b, 0, n);
}
void altmergesort(vector<int> &a, int n)
{
    vector<int> b;
    b.reserve(n);
    for(int i=0; i<n; i++) b.push_back(a[i]);
    ms2(b, a, 0, n);
}
void gravsort(vector<int> &a, int n)
{
    int mx=a[0];
    for(int i=1; i<n; i++)
    {
        mx=max(mx, a[i]);
    }
    vector<vector<int>> beads(n, vector<int>(mx));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<a[i]; j++)
            beads[i][j]=1;
    }
    for(int j=0; j<mx; j++)
    {
        int sum=0;
        for(int i=0; i<n; i++)
        {
            sum+=beads[i][j];
            beads[i][j]=0;
        }
        for(int i=n-1; i>=n-sum; i--)
        {
            a[i]=j+1;
        }
    }
}
void inv(vector<int> &a, int n)
{
    for(int i=0; i<=n/2; i++)
    {
        int x=a[i];
        a[i]=a[n-i];
        a[n-i]=x;
    }
}
void pancakesort(vector<int> &a, int n)
{
    for(int s=n; s>1; s--)
    {
        //indexul maxim
        int i=0, mi=0;
        for(; i<s; ++i)
        {
            if(a[i]>a[mi])
            {
                mi=i;
            }
        }
        if(mi!=s-1)
        {
            inv(a, mi);
            inv(a, s-1);
        }
    }
}
int part(vector<int> &a, int l, int r)
{
    cout<<l<<' '<<r<<endl;
    int pivot=a[(l+r)/2];
    while(l<=r)
    {
        while(a[l]<pivot) l++;
        while(a[r]>pivot) r--;
        if(l<=r)
        {
            int x=a[l];
            a[l]=a[r];
            a[r]=x;
            l++;
            r--;
        }
    }
    return l;
}
void qs(vector<int> &a, int l, int r)
{
    int index=part(a, l, r);
    if(l<index-1)
    {
        qs(a, l, index-1);
    }
    if(index<r)
    {
        qs(a, index, r);
    }
}
void quicksort(vector<int> &a, int n)
{
    qs(a, 0, n);
}
void sortare(vector<int> &a, int n)
{
    FUNCTION(a, n);
}
