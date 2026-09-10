#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <ios>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

/////////////////////// FUNCAO LIMPA TELA ///////////////////////////////////
void limpa_Tela()
{
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}
/////////////////////// FUNCAO INPUT STRING ///////////////////////////////////
void inputNomes(const string& a)
{
    ofstream ficheiro("inputNomes.txt", ios::app);
    if(ficheiro.is_open())
    {
        ficheiro << a << "\n";
    }
    ficheiro.close();
}
/////////////////////FUNÇAO JOGO//////////////////////////////////
bool jogo (const string *palavraSecreta, string categoria)
{
    string letrasCertas = "";
    string letrasErradas = "";
    int pontos = 10;
    char letra;

    limpa_Tela();
    cout << "A sua palavra e um " << categoria << " e tem " << palavraSecreta->size() << " letras\n";
    cout << "Sua pontuacao e : " << pontos << "\n";

    while (true)
    {
        bool ganhou = true;
        for (size_t i = 0; i < palavraSecreta->size(); i++)
        {
            if (letrasCertas.find((*palavraSecreta)[i]) != string::npos)
            {
                cout << (*palavraSecreta)[i] << " ";
            }
            else
            {
                cout << "_ ";
                ganhou = false;
            }
        }
        cout << "\n";

        // VERIFICA ViTORIA
        if(ganhou){
            cout << "\nParabens! Ganhou o jogo! A palavra era: " << *palavraSecreta << "\n";
            cout << "Quer recomeçar ? 1- (sim) 2- (nao) : ";
            int escolha;
            cin >> escolha;
            if(escolha == 1){
                return true;
            } else {
                cout << "Ate logo ! \n";
                return false;
            }
        }

        // VERIFICA DERROTA
        if (pontos <= 0){
            cout << "\nPerdedor !! A palavra era: " << *palavraSecreta << "\n";
            cout << "Quer recomeçar ? 1- (sim) 2- (nao) : ";
            int escolha;
            cin >> escolha;
            if(escolha == 1){
                return true;
            } else {
                cout << "Ate logo ! \n";
                return false;
            }
        }

        cout << "Digite uma letra: ";
        cin >> letra;
        letra = toupper(letra);

        if (letrasCertas.find(letra) != string::npos ||
            letrasErradas.find(letra) != string::npos)
        {
            cout << "\n Essa letra ja foi usada!\n";
            continue;
        }

        bool encontrou = false;
        for (size_t i = 0; i < palavraSecreta->size(); i++)
        {
            if ((*palavraSecreta)[i] == letra)
            {
                encontrou = true;
            }
        }

        if (encontrou)
        {
            letrasCertas += letra;
            pontos += 1;
        }
        else
        {
            letrasErradas += letra;
            pontos -= 1;
        }

        limpa_Tela();
        cout << "A sua palavra e um " << categoria << " e tem " << palavraSecreta->size() << " letras\n";
        cout << "Letras Certas: " << letrasCertas << " \n";
        cout << "Letras Erradas: " << letrasErradas << " \n";
        cout << "Sua pontuacao e : " << pontos << "\n";
    }
}

//////////////////////// FUNCAO MENU DIFICULDADDE //////////////////////////////////
void menu_Dificuldade()
{
    const string facil [10] = {"GATO", "CAO", "LEAO", "PATO", "RATO", "LOBO", "URSO", "VACA", "SAPO", "AVES"};
    const string medio[10]= {"GUITARRA", "ESPELHO", "COMPUTADOR", "MOCHILA", "CADERNO", "TELEFONE", "CARTEIRA", "LANTERNA", "RELOGIO", "MARTELO"};
    const string dificil [10]= {"OTORRINOLARINGOLOGISTA", "PSICOLOGO", "ARQUEOLOGIA", "PROGRAMADOR", "ENGENHEIRO", "ASTRONAUTA", "NUTRICIONISTA", "NEUROCIENTISTA", "EMPREENDEDOR", "FARMACEUTICO"};

    bool continuarJogando = true;
    srand(time(0));

    while(continuarJogando)
    {

        cout << "\n 1 - Facil";
        cout << "\n 2 - Medio";
        cout << "\n 3 - Dificil \n";

        int dificuldade;
        cout << "Escolha uma opcao : ";
        cin >> dificuldade;

        if(dificuldade == 1)
        {
            int aleatorio = rand() % 10;
            continuarJogando = jogo(&facil[aleatorio], "animal");
        }
        else if (dificuldade == 2)
        {
            int aleatorio = rand() % 10;
            continuarJogando = jogo(&medio[aleatorio], "objeto");
        }
        else if(dificuldade == 3)
        {
            int aleatorio = rand() % 10;
            continuarJogando = jogo(&dificil[aleatorio], "profissao");
        }
        else
        {
            cout << "Opcao invalida ! Pressione Enter para tentar novamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}
////////////////////////// FUNCAO MENU ////////////////////////////////
void menu_Inicial()
{
    string nome;
    int escolha;
    cout << "Digite o seu nome : ";
    getline (cin,nome);
    inputNomes(nome);

    do
    {
        cout << "============================================================================================\n"

             << "   _  ___   ____  ___    ____   _      _____ ___  ____   ____   _         +---+\n"
             << "  | |/ _ \\ / ___|/ _ \\  |  _ \\ / \\    |  ___/ _ \\|  _ \\ / ___| / \\        |   |\n"
             << "  | | | | | |  _| | | | | | | / _ \\   | |_ | | | | |_) | |    / _ \\       O   |\n"
             << "  | | |_| | |_| | |_| | | |_/ / ___ \\  |  _|| |_| |  _ <| |___/ ___ \\    /|\\  |\n"
             << " _/ |\\___/ \\____|\\___/  |____/_/   \\_\\ |_|   \\___/|_| \\_\\\\____/_/   \\_\\  / \\  |\n"
             << "|__/                                                                          |\n"
             << "============================================================================================\n" << "\n";


        cout << "Escolha uma opcao !";
        cout << "\n 1 - Jogar";
        cout << "\n 2 - Regras";
        cout << "\n 3 - Sair";
        cout << "\n =========================================\n";
        cin >> escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                 << "=========================================================================\n" << "\n";
            menu_Dificuldade();
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
                 << "=========================================\n" << "\n";
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
                    cout << "Invalido " << "\n";
                    escolha = 0;
                }
            }
            while (sub_Escolha < 1 || sub_Escolha > 2 );


            break;
        case 3 :
            limpa_Tela();
            cout << "Ate logo !!";
            break;
        default:
            limpa_Tela();
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
