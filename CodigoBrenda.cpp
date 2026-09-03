#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

    cout << "==============================\n";
    cout << "=========JOGO DA FORCA========\n";
    cout << "==============================\n";

    string nomeJogador;

    cout << "Digite o seu nome: ";
    getline(cin, nomeJogador);

    int opcao;

    cout << "\n ------------ MENU ------------\n";
    cout << "1 - Jogar\n";
    cout << "2 - Ver ranking\n";
    cout << "3 - Sair\n";

    cout << "\nEscolha uma opção: ";
    cin >> opcao;

    if(opcao == 1){
        cout << "\nVocê escolheu JOGAR!";
    }
    else if(opcao == 2){
        cout << "\nO ranking será criado na próxima etapa.\n";
    }
    else if(opcao == 3){
        cout << "\nAté a próxima, " << nomeJogador << "!\n";
    }
    else{
        cout << "\nOpção inválida!\n";
    }
    

    return 0;
}
