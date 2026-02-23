#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[]){
    if(argc==1){
        cout << "Please input numbers to find average.";
        return 0;
    }
    double sum = 0;
    int n = argc-1;
    for(int i = 1; i<argc; i++){
        sum += stod(argv[i]);
    }
    double avg = sum/n;
    cout << "---------------------------------\n";
    cout << "Average of " << n << " numbers = " << avg << "\n";
    cout << "---------------------------------";
}