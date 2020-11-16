// Copyright 2020 Kolesin Andrey
#include <mpi.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include "../../../modules/task_2/kolesin_a_bubblesort/bubblesort.h"

std::vector<int> getRandomArray() {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> res;
    int size = 10000;
    for (int  i = 0; i < size; i++) {
        res.push_back(gen()%100);
    }
    return res;
}

void SortMass(int* m, int n)
{
     for(int i = n - 1; i >= 1; i--)
       for(int j = 0; j < i; j++)
       {
               if(m[j] > m[j+1])
               {
                       int foo = m[j];
                       m[j] = m[j+1];
                       m[j+1] = foo;
               }
       }  
}

void initialScatter(int *arr, int *mypart, int n, int rank, int size, int *mycount, bool* left, bool* right, int* sendcounts, int *displs) {
    mypart+=1;
    
    int base_count = 2*(n/2/size); 
    int remainder = n - size*base_count;
    for (int i = 0; i < size; i++) {
        sendcounts[i] = base_count;
    }
    sendcounts[size-1] += remainder;
    int x = 0;
    for (int i = 0; i < size; i++) {
        displs[i] = x;
        x += sendcounts[i];
    }

    *mycount = sendcounts[rank];
    
    if (base_count == 0) {
        *left=false;
        *right=false;
    } else {
        *left = true;
        *right = true;
        if (rank == 0) {
            *left = false;
        }
        if (rank == size - 1) {
            *right = false;
        }
    }

    MPI_Scatterv(arr, sendcounts, displs,MPI_INT, mypart, sendcounts[rank], MPI_INT, 0, MPI_COMM_WORLD);
    delete[] displs;

}
void SyncronizeLR(int* mypart, int mycount, int rank, int size, bool left, bool right) {
    // left to right
    MPI_Request sendrequest;
    MPI_Request recvrequest;
    MPI_Status status;

    if (right) {
        MPI_Isend(&mypart[mycount], 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD, &sendrequest);
    }
    if (left) {
        MPI_Irecv(mypart, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD,  &recvrequest);
        //MPI_Wait(&recvrequest, &status);
    }
    MPI_Barrier(MPI_COMM_WORLD);
}
void SyncronizeRL(int* mypart, int mycount, int rank, int size, bool left, bool right) {
    // right to left
    MPI_Request sendrequest;
    MPI_Request recvrequest;
    MPI_Status status;

    if (left) {
        MPI_Isend(mypart, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &sendrequest);
    }
    if (right) {
        MPI_Irecv(&mypart[mycount], 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD,  &recvrequest);
        //MPI_Wait(&recvrequest, &status);
    }
    MPI_Barrier(MPI_COMM_WORLD);
}
void SortIteration(int* arr, int mycount) {
    for(int i=0;i<mycount;i+=2){
        if(arr[i]>arr[i+1]){
            int tmp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = tmp;
        }
    }
}
void parallelSort(std::vector<int> *Arr) {
    std::vector<int> &arr = *Arr;
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n;
    if (rank == 0) {
        n = arr.size();
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int* mypart = new int[n+1];
    mypart[0]=-333;
    int mycount;
    bool left, right;
    int* sendcounts  = new int[size];
    int* displs = new int[size];
    initialScatter(&arr[0], mypart, n, rank, size, &mycount, &left, &right,sendcounts,displs);
    // std::cout<< rank <<"   %%%  "; 

    // for(int i=0;i<mycount+1;i++) {
    //     std::cout<<mypart[i]<<" ";
    // }
    // std::cout <<"##"<<std::endl;

    for (int i = 0; i < n; i++) {
        int* buff = mypart;
        int count = mycount;
        if (i%2==0){
            buff+=1;
            count-=1;
        }
        else{
            if(!left){
                buff+=2;
                count-=2;
            }
        }
        
        //std::cout<<buff-mypart<<"   "<<count<<"      ";



        SortIteration(buff,count);
        if (i%2==0) {
            SyncronizeLR(mypart,mycount, rank, size, left, right);
        } else {
            SyncronizeRL(mypart,mycount, rank, size, left, right);
        }


        
        // std::cout<< rank << " ;; "<< mycount<<"   %%%  "; 

        // for(int i=0;i<mycount+1;i++) {
        //     std::cout<<mypart[i]<<" ";
        // }
        // std::cout<<std::endl;
        // MPI_Barrier(MPI_COMM_WORLD);
        // if(rank==0) std::cout<<"+++="<<i<<std::endl;
    }
    if(n%2==1){
        SyncronizeRL(mypart,mycount, rank, size, left, right);
    }
    if(rank==0){
        int x = 0;
        for(int i = 0;i<size;i++){
            displs[i]=x;
            x+=sendcounts[i];
            //std::cout<<sendcounts[i]<<" "<<displs[i]<<std::endl;
        }
    }
    MPI_Gatherv(mypart+1,sendcounts[rank],MPI_INT,&arr[0],sendcounts,displs,MPI_INT,0,MPI_COMM_WORLD);
    
    
    delete[] mypart;
 }
/*
int shareStrings(int rank, int size, std::string str, char** buff_out) {
    int n;
    if (rank == 0) {
        n = str.size();
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n <= size*2) {
        return -1;
    }
    int delta = n/size;
    int remainder = n - delta*size;
    int buffsize =   delta + remainder;

    char* buff = new char[buffsize+1];
    MPI_Scatter(str.c_str(), delta, MPI_CHAR, buff, delta, MPI_CHAR, 0, MPI_COMM_WORLD);
    if (remainder != 0) {
        if (rank == 0) {
            MPI_Send(str.c_str()+size*delta, remainder, MPI_CHAR, size-1, 0, MPI_COMM_WORLD);
        } else if (rank == size-1) {
            MPI_Status status;
            MPI_Recv(buff+delta, remainder, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        }
    }
    if (rank == size-1) {
        buff[buffsize] = 0;
    } else {
        buff[delta] = 0;
    }
    *buff_out = buff;
    return 0;
}

int countWords(std::string str) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char* buff;
        if (shareStrings(rank, size, str, &buff) == -1) {
        if (rank == 0) {
            return count(str.c_str());
        }
        return 0;
    }
    int local_sum = count(buff);
    int* result_array = new int[size];
    MPI_Gather(&local_sum, 1, MPI_INT, result_array, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += result_array[i];
    }
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int p1 = str.size()/size*i;
            int p2 = p1 - 1;
            if (str[p2] != ' ' &&  str[p1] != ' ') {
                result--;
            }
        }
    }
    delete[] buff;
    delete[] result_array;
    return result;
}
*/
