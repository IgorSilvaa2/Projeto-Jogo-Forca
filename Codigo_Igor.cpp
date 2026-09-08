#include <iostream>
#include <string>
#include <fstream>
#include <clocale>

using namespace std;

/////////////////////// FUNCAO LIMPA TELA ///////////////////////////////////
void limpa_Tela()
{
    system("CLS");
}
/////////////////////// FUNCAO INPUT STRING ///////////////////////////////////
void input_String(string a)
{
    ofstream ficheiro("Input_String.txt", ios::app);
    if(ficheiro.is_open())
    {
        ficheiro << a << "\n";
    }
    ficheiro.close();
}
////////////////////////// FUNCAO MENU ////////////////////////////////
void menu_Inicial()
{
    string nome;
    int escolha;

    do
    {
        cout << "============================================================================================\n"
     << "   _  ___   ____  ___    ____   _      _____ ___  ____   ____   _         +---+\n"
     << "  | |/ _ \\ / ___|/ _ \\  |  _ \\ / \\    |  ___/ _ \\|  _ \\ / ___| / \\        |   |\n"
     << "  | | | | | |  _| | | | | | | / _ \\   | |_ | | | | |_) | |    / _ \\       O   |\n"
     << "  | | |_| | |_| | |_| | | |_/ / ___ \\  |  _|| |_| |  _ <| |___/ ___ \\    /|\\  |\n"
     << " _/ |\\___/ \\____|\\___/  |____/_/   \\_\\ |_|   \\___/|_| \\_\\\\____/_/   \\_\\  / \\  |\n"
     << "|__/                                                                          |\n"
     << "============================================================================================\n" << endl;

        cout << "Escolha uma opcao !";
        cout << "\n 1 - Jogar";
        cout << "\n 2 - Regras";
        cout << "\n 3 - Sair";
        cout << "\n =========================================\n";
        cin >> escolha;

        switch(escolha)
        {
        case 1 :
            limpa_Tela();
            cout << "=========================================================================\n"
                 << "  ____  _____ __  __     __     ___ _   _ ____   ___  _ _ _ \n"
                 << " | __ )| ____|  \\/  |    \\ \\   / / | \\ | |  _ \\ / _ \\| | | |\n"
                 << " |  _ \\|  _| | |\\/| |     \\ \\ / /| |  \\| | | | | | | | | | |\n"
                 << " | |_) | |___| |  | |      \\ V / | | |\\  | |_| | |_| |_|_|_|\n"
                 << " |____/|_____|_|  |_|       \\_/  |_|_| \\_|____/ \\___/(_|_|_)\n"
                 << "=========================================================================\n" << endl;

            cout << "Digite o seu nome : ";
            cin >> nome;
            input_String(nome);
            break;
        case 2 :
            limpa_Tela();
            cout << "\n";
            cout << "=========================================\n"
                 << "         REGRA DO JOGO DA FORCA          \n"
                 << "=========================================\n\n"
                 << "1. OBJETIVO:\n"
                 << "   Adivinhar a palavra secreta antes que o\n"
                 << "   boneco seja totalmente desenhado.\n\n"
                 << "2. COMO JOGAR:\n"
                 << "   - Introduza uma letra de cada vez.\n"
                 << "   - Se a letra existir, ela sera revelada.\n"
                 << "   - Se errar, uma parte do corpo vai para a forca.\n\n"
                 << "3. FIM DE JOGO:\n"
                 << "   - VITORIA: Se descobrir todas as letras.\n"
                 << "   - DERROTA: Se atingir o limite de 6 erros.\n\n"
                 << "=========================================\n" << endl;
            int sub_Escolha;

            do
            {
                cout << "Escolha uma das opcoes. 1 - Voltar  2 - sair : ";
                cin >> sub_Escolha;
                if(sub_Escolha == 1)
                {
                    limpa_Tela();
                    escolha = 0;
                }
                else if(sub_Escolha == 2)
                {
                    limpa_Tela();
                    cout << "Ate logo !!";
                    escolha = 3;
                }
                else
                {
                    cout << "Invalido " << endl;
                    escolha = 0;
                }
            }
            while (sub_Escolha < 1 || sub_Escolha > 2 );


            break;
        case 3 :
            limpa_Tela();
            cout << "Ate logo !!";
            break;
        }
    }
    while(escolha < 1 || escolha > 3);
}
//////////////////////// MAIN //////////////////////////////////

int main()
{
    setlocale(LC_ALL, "Portuguese");

    menu_Inicial();

    return 0;
}
