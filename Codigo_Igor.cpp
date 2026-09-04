#include <iostream>
#include <string>
#include <fstream>
#include <clocale>

using namespace std;

void Nome_usuario(string a)
{

}
void Salva_nome(string a){
    ofstream ficheiro("Nome_jogadores.txt", ios::app);
    if(ficheiro.is_open()){
        ficheiro << a << "\n";
    }
    ficheiro.close();
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    string Nome;
    int Escolha;

    do{
    cout << "***************************" << endl;
    cout << "*      JOGO DA FORCA      *" << endl;
    cout << "***************************" << endl;

    cout << "digite o seu nome : ";
    cin >> Nome;

    Salva_nome(Nome);

    cout << "Dezeja continuar ? 1 = Sim - 0 = Não : ";
    cin >> Escolha;
    }while(Escolha != 0);





    return 0;
}
