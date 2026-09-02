#include <iostream>
#include <string>
using namespace std;

void New(int a[], int b)
{
    for (int i = 0; i < b; i++)
    {
        cout << a[i] << " ";
    }
}

int main()
{
    int tamanho;

    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    int *vetor = new int[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        cout << "Digite o " << (i + 1) << "º numero: ";
        cin >> vetor[i];
    }

    New(vetor, tamanho);

    delete[] vetor;
}
