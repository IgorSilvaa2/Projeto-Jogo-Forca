#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <clocale>
#include <vector>    
#include <algorithm> 
using namespace std;

/////////////////////// FUNCAO LIMPAR BUFFER ////////////////////////////////

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/////////////////////// FUNCAO GUARDAR RANKING //////////////////////////////

struct Jogador{
    string nome;
    int pontuacao;
};

void mostrarRanking(){
    ifstream ficheiro("historico.txt");
    if (!ficheiro.is_open())
    {
        cout << "\nNao foi possivel abrir o historico.\n";
        return;
    }

    vector<Jogador> ranking;

    string nome;
    string dificuldade;
    string palavra;
    string pontosTexto;
    string resultado;

    while (getline(ficheiro, nome, ';')) 
    {
        getline(ficheiro, dificuldade, ';');
        getline(ficheiro, palavra, ';');
        getline(ficheiro, pontosTexto, ';');
        getline(ficheiro, resultado);

        if (resultado == "Ganhou"){
            Jogador jogador;
            jogador.nome = nome;
            jogador.pontuacao = stoi(pontosTexto); 
            ranking.push_back(jogador); 
        }
    }

    ficheiro.close();

    sort(ranking.begin(), ranking.end(),
         [](const Jogador &a, const Jogador &b)
         {
             return a.pontuacao > b.pontuacao;
         });

    cout << "\n";
    cout << "              RANKING\n";
    cout << "=========================================\n\n";

    if (ranking.empty()){
        cout << "Ainda nao existem partidas ganhas.\n";
        return;
    }

    for (size_t i = 0; i < ranking.size(); i++)
    {
        cout << i + 1 << " - "
             << ranking[i].nome
             << " | "
             << ranking[i].pontuacao
             << " pontos\n";
    }

    cout << "\n=========================================\n";
}

/////////////////////// FUNCAO GUARDAR PARTIDA //////////////////////////////

void guardarPartida(
    const string &nome,
    const string &dificuldade,
    const string &palavra,
    int pontos,
    const string &resultado)
{
    ofstream ficheiro("historico.txt", ios::app);

    if (ficheiro.is_open())
    {
        ficheiro << nome << ";"
                 << dificuldade << ";"
                 << palavra << ";"
                 << pontos << ";"
                 << resultado << "\n";
    }

    ficheiro.close();
}

/////////////////////// FUNCAO LIMPA TELA ///////////////////////////////////

void limpa_Tela()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

/////////////////////// FUNCAO INPUT NOME ///////////////////////////////////

void inputNomes(const string &a)
{
    ofstream ficheiro("inputNomes.txt", ios::app);

    if (ficheiro.is_open())
    {
        ficheiro << a << "\n";
    }

    ficheiro.close();
}

/////////////////////// FUNCAO CONTINUAR ///////////////////////////////////

bool perguntarContinuar()
{
    string resposta;

    while (true)
    {
        cout << "\nDeseja continuar a jogar? (s/n): ";
        cin >> resposta;
        limparBuffer();

        if (resposta == "s" || resposta == "S")
        {
            return true;
        }
        else if (resposta == "n" || resposta == "N")
        {
            cout << "Ate a proxima!\n";
            return false;
        }
        else
        {
            cout << "Opcao invalida! Digite apenas s ou n.\n";
        }
    }
}

/////////////////////// FUNCAO DESENHO FORCA ////////////////////////////////

void mostrarForca(int erros)
{
    cout << "\n";
    cout << " +---+\n";
    cout << " |   |\n";

    if (erros >= 1)
        cout << " O   |\n";
    else
        cout << "     |\n";

    if (erros == 2)
        cout << " |   |\n";
    else if (erros == 3)
        cout << "/|   |\n";
    else if (erros >= 4)
        cout << "/|\\  |\n";
    else
        cout << "     |\n";

    if (erros >= 5)
        cout << "/    |\n";
    else
        cout << "     |\n";

    if (erros >= 6)
        cout << "/ \\  |\n";
    else
        cout << "     |\n";

    cout << "     |\n";
    cout << "=========\n";
}

//////////////////////// FUNCAO JOGO ////////////////////////////////////////

bool jogo(const string *palavraSecreta, string categoria, const string &nome, string dificuldade)
{
    string letrasCertas = "";
    string letrasErradas = "";

    int pontos = 6;
    int erros = 0;

    char letra;

    limpa_Tela();

    cout << "A sua palavra e um " << categoria << " e tem " << palavraSecreta->size() << " letras\n";
    cout << "Sua pontuacao e: " << pontos << "\n";

    while (true)
    {
        bool ganhou = true;

        cout << "\nPalavra: ";

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

        mostrarForca(erros);

        cout << "\nLetras certas: " << letrasCertas << "\n";
        cout << "Letras erradas: " << letrasErradas << "\n";
        cout << "Erros: " << erros << "/6\n";
        cout << "Pontuacao: " << pontos << "\n";
        cout << "\n";

        if (ganhou)
        {
            cout << "           PARABENS! GANHOU O JOGO!           \n";
            cout << "\n";
            cout << "A palavra era: " << *palavraSecreta << "\n";
            cout << "Sua pontuacao e: " << pontos << "\n";

            guardarPartida(nome, dificuldade, *palavraSecreta, pontos, "Ganhou");

            return perguntarContinuar();
        }

        if (erros >= 6)
        {
            cout << "          PERDEU O JOGO!            \n";
            cout << "\n";
            cout << "A palavra era: " << *palavraSecreta << "\n";
            cout << "Sua pontuacao e: " << pontos << "\n";

            guardarPartida(nome, dificuldade, *palavraSecreta, pontos, "Perdeu");

            return perguntarContinuar();
        }

        cout << "\nDigite uma letra: ";
        cin >> letra;
        limparBuffer(); 

        letra = toupper(letra);

        if (!isalpha(letra))
        {
            cout << "\nEntrada invalida! Digite apenas uma letra.\n";
            continue;
        }

        if (letrasCertas.find(letra) != string::npos || letrasErradas.find(letra) != string::npos)
        {
            cout << "\nEssa letra ja foi usada!\n";
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

            cout << "\nAcertou!\n";
        }
        else
        {
            letrasErradas += letra;
            pontos -= 1;
            erros++;

            cout << "\nErrou!\n";
        }

        limpa_Tela();

        cout << "A sua palavra e um " << categoria << " e tem " << palavraSecreta->size() << " letras\n";
    }
}

//////////////////////// FUNCAO MENU DIFICULDADE ////////////////////////////

void menu_Dificuldade(const string &nome)
{
    const string facil[10] = {"GATO","CAO","LEAO","PATO","RATO","LOBO","URSO","VACA","SAPO","AVES"};
    const string medio[10] = {"GUITARRA","ESPELHO","COMPUTADOR","MOCHILA","CADERNO","TELEFONE","CARTEIRA","LANTERNA","RELOGIO","MARTELO"};
    const string dificil[10] = {"OTORRINOLARINGOLOGISTA","PSICOLOGO","ARQUEOLOGIA","PROGRAMADOR","ENGENHEIRO","ASTRONAUTA","NUTRICIONISTA","NEUROCIENTISTA","EMPREENDEDOR","FARMACEUTICO"};

    bool continuarJogando = true;
    srand(time(0));

    while (continuarJogando)
    {
        cout << "          ESCOLHA A DIFICULDADE         \n\n";
        cout << "1 - Facil\n";
        cout << "2 - Medio\n";
        cout << "3 - Dificil\n";

        int dificuldade;

        cout << "\nEscolha uma opcao: ";
        if (!(cin >> dificuldade))
        {
            limparBuffer();
            limpa_Tela();
            cout << "\nOpcao invalida! Digite apenas numeros.\n\n";
            continue;
        }
        limparBuffer();

        if (dificuldade == 1)
        {
            int aleatorio = rand() % 10;
            continuarJogando = jogo(&facil[aleatorio], "animal", nome, "Facil");
        }
        else if (dificuldade == 2)
        {
            int aleatorio = rand() % 10;
            continuarJogando = jogo(&medio[aleatorio], "objeto", nome, "Medio");
        }
        else if (dificuldade == 3)
        {
            int aleatorio = rand() % 10;
            continuarJogando = jogo(&dificil[aleatorio], "profissao", nome, "Dificil");
        }
        else
        {
            limpa_Tela();
            cout << "\nOpcao invalida! Escolha entre 1 e 3.\n\n";
        }
    }
}

////////////////////////// FUNCAO MENU INICIAL //////////////////////////////

void menu_Inicial()
{
    string nome;
    int escolha;

    cout << "Digite o seu nome: ";
    getline(cin, nome);
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
             << "============================================================================================\n\n";

        cout << "Escolha uma opcao!\n\n";
        cout << "1 - Jogar\n";
        cout << "2 - Regras\n";
        cout << "3 - Ranking\n";
        cout << "4 - Sair\n";
        cout << "=========================================\n";
        cout << "Opcao: ";

        if (!(cin >> escolha))
        {
            limparBuffer();
            limpa_Tela();
            cout << "Opcao invalida! Digite apenas um numero.\n\n";
            escolha = 0;
            continue;
        }
        limparBuffer();

        switch (escolha)
        {
        case 1:
            limpa_Tela();
            cout << "=========================================================================\n"
                 << "  ____  _____ __  __     __     ___ _   _ ____   ___  _ _ _ \n"
                 << " | __ )| ____|  \\/  |    \\ \\   / / | \\ | |  _ \\ / _ \\| | | |\n"
                 << " |  _ \\|  _| | |\\/| |     \\ \\ / /| |  \\| | | | | | | | | | |\n"
                 << " | |_) | |___| |  | |      \\ V / | | |\\  | |_| | |_| |_|_|_|\n"
                 << " |____/|_____|_|  |_|       \\_/  |_|_| \\_|____/ \\___/(_|_|_)\n"
                 << "=========================================================================\n\n";

            menu_Dificuldade(nome);
            break;

        case 2:
            limpa_Tela();
            cout << "=========================================\n"
                 << "         REGRAS DO JOGO DA FORCA\n"
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
                 << "=========================================\n\n";

            int sub_Escolha;

            do
            {
                cout << "Escolha uma das opcoes.\n";
                cout << "1 - Voltar\n";
                cout << "2 - Sair\n";
                cout << "Opcao: ";

                if (!(cin >> sub_Escolha))
                {
                    limparBuffer();
                    cout << "Invalido!\n";
                    sub_Escolha = 0;
                    continue;
                }
                limparBuffer();

                if (sub_Escolha == 1)
                {
                    limpa_Tela();
                    escolha = 0;
                }
                else if (sub_Escolha == 2)
                {
                    limpa_Tela();
                    cout << "Ate logo!!\n";
                    escolha = 4;
                }
                else
                {
                    cout << "Invalido!\n";
                }
            } while (sub_Escolha < 1 || sub_Escolha > 2);

            break;

        case 3:
            limpa_Tela();
            mostrarRanking();
            cout << "\nPressione Enter para voltar ao menu.";
            cin.get();
            limpa_Tela();
            escolha = 0;
            break;

        case 4:
            limpa_Tela();
            cout << "Ate logo!!\n";
            break;

        default:
            limpa_Tela();
            cout << "Opcao invalida!\n";
            break;
        }

    } while (escolha != 4);
}

//////////////////////// MAIN ///////////////////////////////////////////////

int main(){
    setlocale(LC_ALL, "Portuguese");

    menu_Inicial();

    return 0;
}
