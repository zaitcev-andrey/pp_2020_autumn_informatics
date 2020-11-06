#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<map>
#include<mpi.h>

using namespace std;
 
const double EPS = 1e-12;

bool converge(const vector<double> &x, const vector<double> last, double eps){
    double ans = 0;
    for(int i = 0;i < (int)x.size();++i) {
        double tmp = x[i] - last[i];
        ans += tmp * tmp;
    }
    return sqrtl(ans) < eps;
}

void swap(vector<double> &a, int n, int x, int y){
    for(int i = 0;i < n;++i){
        swap(a[x * n + i], a[y * n + i]);
    }    
}

double calcParallel(const vector<double> & a, const vector<double> &x, int row, int n){
    
    int procNum, procRank;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    

    int offset = n / procNum;
    int rem = n % procNum;
    double localRes = 0, globalRes = 0;
    vector<double> localA(offset), localX(offset);

    if (procRank == 0) {
        for(int i = 1;i < procNum;++i){
            MPI_Send(&a[0] + n * (row - 1) + rem + offset * i, offset, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&x[0] + rem + offset * i, offset, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
        }
    }
    if (procRank == 0){
        localA = vector<double>(a.begin() + (row - 1) * n, a.begin() + (row - 1) * n + rem + offset);
        localX = vector<double>(x.begin(), x.begin() + rem + offset);
    } else {
        MPI_Status status;
        MPI_Recv(&localA[0], offset, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&localX[0], offset, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);            
    }
    for(int i = 0;i < (int)localA.size();++i){
        localRes += localA[i] * localX[i];
    }
    MPI_Reduce(&localRes, &globalRes, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    return globalRes;
}

int main(int argc, char** argv) {   
    MPI_Init(&argc, &argv);    
    int n = 2;
    vector<double> a = {1, 2, 3, 4};
    vector<double> b = {5, 6};
    for(int j = 0;j < n;++j){
        double ma = fabs(a[j * n + j]);
        int ind = j;
        for(int i = j + 1;i < n;++i) {
            if (ma < fabs(a[i * n + j]) - EPS) {
                ma = fabs(a[i * n + j]);
                ind = i;                           
            }
        }
        swap(a, n, ind, j);
        swap(b[ind], b[j]);
    }
    double eps = 0.00001;
    vector<double> x(n, 0), last(n, 0);
    map<vector<double>, int> was;
    int cnt = 20;
    
    do{
        was[x]++;
        last = x;
        for(int i = 0;i < n;++i){
            x[i] = 0;
            double gg = calcParallel(a, x, i, n);
            x[i] = (b[i] - gg) / a[i * n + i];
        }
        
    }while(!converge(x, last, eps) && !was.count(x) && cnt--);
    
    if (procRank == 0){
        for(auto &i : x) cout << i << ' ';
        cout << '\n';            
    }    
    
    MPI_Finalize();    
    return 0;
}