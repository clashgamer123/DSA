#include "ropes.cpp"



int main()
{
    int T;
    cin >> T;
    int arr[100000];
    for (int i = 0; i < T;i++)
    {
        int size;
        cin >> size;
        for (int j = 0;j<size;j++) cin >> arr[j];
        auto start = std :: chrono :: high_resolution_clock :: now() ;
        cout << minCost(arr, size) << std::endl; // Write a function mincost which takes the array and size as parameters and returns the integer solution
        auto stop = std :: chrono :: high_resolution_clock :: now() ;
        auto duration = std :: chrono :: duration_cast<std :: chrono :: microseconds>(stop-start) ;
        std :: cout<<duration.count()<<endl ;
    }
	return 0;
}

