#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <clocale>
#include <vector>    // necessario para criar o struct, função do ranking
#include <algorithm> // necessario para utilizar sort() para ordenar as pontuações
using namespace std;

/////////////////////// FUNCAO GUARDAR RANKING //////////////////////////////
// função para a criação do ranking, assim, o struct permite guardar essas duas informações juntas.
struct Jogador
{
    string nome;
    int pontuacao;
};

void mostrarRanking()
{
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

    // O programa vai ler até encontrar ;
    while (getline(ficheiro, nome, ';')) // getline = ler uma sequência de caracteres e guardar essa informação numa string.
    {
        getline(ficheiro, dificuldade, ';');
        getline(ficheiro, palavra, ';');
        getline(ficheiro, pontosTexto, ';');
        getline(ficheiro, resultado);

        if (resultado == "Ganhou")
        {
            Jogador jogador;

            jogador.nome = nome;
            jogador.pontuacao = stoi(pontosTexto); // stoi (string to integer)= transformar texto num número inteiro.

            ranking.push_back(jogador); // colocar no final do vector
        }
    }

    ficheiro.close();

    // organizar do maior número de pontos para o menor
    sort(ranking.begin(), ranking.end(),
         [](const Jogador &a, const Jogador &b)
         {
             return a.pontuacao > b.pontuacao;
         });

    cout << "\n";
    cout << "              RANKING\n";
    cout << "=========================================\n\n";

    if (ranking.empty())
    {
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

        if (resposta == "s" || resposta == "S")
        {
            return true;
        }
        else if (resposta == "n" || resposta == "N")
        {
            cout << "Até a próxima!";
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
    cout << "Sua pontuacao é: " << pontos << "\n";

    while (true)
    {
        bool ganhou = true;

        ////////////////////// MOSTRAR PALAVRA //////////////////////////////

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

        ////////////////////// MOSTRAR FORCA ////////////////////////////////

        mostrarForca(erros);

        ////////////////////// MOSTRAR INFORMACOES //////////////////////////

        cout << "\nLetras certas: " << letrasCertas << "\n";
        cout << "Letras erradas: " << letrasErradas << "\n";
        cout << "Erros: " << erros << "/6\n";
        cout << "Pontuacao: " << pontos << "\n";
        cout << "\n";

        ////////////////////// VERIFICA VITORIA //////////////////////////////

        if (ganhou)
        {
            cout << "           PARABENS! GANHOU O JOGO!           \n";
            cout << "\n";
            cout << "A palavra era: " << *palavraSecreta << "\n";
            cout << "Sua pontuacao é: " << pontos << "\n";

            guardarPartida(nome, dificuldade, *palavraSecreta, pontos, "Ganhou");

            return perguntarContinuar();
        }

        ////////////////////// VERIFICA DERROTA //////////////////////////////

        if (erros >= 6)
        {
            cout << "          PERDEU O JOGO!            \n";
            cout << "\n";
            cout << "A palavra era: " << *palavraSecreta << "\n";
            cout << "Sua pontuacao é: " << pontos << "\n";

            guardarPartida(nome, dificuldade, *palavraSecreta, pontos, "Perdeu");

            return perguntarContinuar();
        }

        ////////////////////// PEDIR LETRA //////////////////////////////////

        cout << "\nDigite uma letra: ";
        cin >> letra;

        letra = toupper(letra);

        ////////////////////// VERIFICAR SE E LETRA //////////////////////////

        if (!isalpha(letra))
        {
            cout << "\nEntrada invalida! Digite apenas uma letra.\n";
            continue;
        }

        ////////////////////// VERIFICAR REPETICAO //////////////////////////

        if (letrasCertas.find(letra) != string::npos || letrasErradas.find(letra) != string::npos)
        {
            cout << "\nEssa letra ja foi usada!\n";
            continue;
        }

        ////////////////////// PROCURAR LETRA ////////////////////////////////

        bool encontrou = false;

        for (size_t i = 0; i < palavraSecreta->size(); i++)
        {
            if ((*palavraSecreta)[i] == letra)
            {
                encontrou = true;
            }
        }

        ////////////////////// ATUALIZAR JOGO ////////////////////////////////

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

        ////////////////////// LIMPAR ECRAN //////////////////////////////////

        limpa_Tela();

        cout << "A sua palavra é um " << categoria << " e tem " << palavraSecreta->size() << " letras\n";
    }
}

//////////////////////// FUNCAO MENU DIFICULDADE ////////////////////////////

void menu_Dificuldade(const string &nome) // assim ele recebe o nome do jogador
{
    const string facil[10] =
        {
            "GATO",
            "CAO",
            "LEAO",
            "PATO",
            "RATO",
            "LOBO",
            "URSO",
            "VACA",
            "SAPO",
            "AVES"};

    const string medio[10] =
        {
            "GUITARRA",
            "ESPELHO",
            "COMPUTADOR",
            "MOCHILA",
            "CADERNO",
            "TELEFONE",
            "CARTEIRA",
            "LANTERNA",
            "RELOGIO",
            "MARTELO"};

    const string dificil[10] =
        {
            "OTORRINOLARINGOLOGISTA",
            "PSICOLOGO",
            "ARQUEOLOGIA",
            "PROGRAMADOR",
            "ENGENHEIRO",
            "ASTRONAUTA",
            "NUTRICIONISTA",
            "NEUROCIENTISTA",
            "EMPREENDEDOR",
            "FARMACEUTICO"};

    bool continuarJogando = true;

    srand(time(0));

    while (continuarJogando)
    {
        cout << "          ESCOLHA A DIFICULDADE         \n";
        cout << "\n";
        cout << "1 - Facil\n";
        cout << "2 - Medio\n";
        cout << "3 - Dificil\n";

        int dificuldade;

        cout << "\nEscolha uma opcao: ";
        cin >> dificuldade;

        ////////////////////// DIFICULDADE FACIL ////////////////////////////

        if (dificuldade == 1)
        {
            int aleatorio = rand() % 10;

            continuarJogando =
                jogo(&facil[aleatorio], "animal", nome, "Facil");
        }

        ////////////////////// DIFICULDADE MEDIA ////////////////////////////

        else if (dificuldade == 2)
        {
            int aleatorio = rand() % 10;

            continuarJogando =
                jogo(&medio[aleatorio], "objeto", nome, "Medio");
        }

        ////////////////////// DIFICULDADE DIFICIL //////////////////////////

        else if (dificuldade == 3)
        {
            int aleatorio = rand() % 10;

            continuarJogando =
                jogo(&dificil[aleatorio], "profissao", nome, "Dificil");
        }

        ////////////////////// OPCAO INVALIDA ///////////////////////////////

        else
        {
            cout << "\nOpcao invalida!";
            cout << "\nPressione Enter para tentar novamente.";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n');

            cin.get();
        }
    }
}

////////////////////////// FUNCAO MENU INICIAL //////////////////////////////

void menu_Inicial()
{
    string nome;
    int escolha;

    ////////////////////// PEDIR NOME ///////////////////////////////////////

    cout << "Digite o seu nome: ";

    getline(cin, nome);
    inputNomes(nome);

    ////////////////////// MENU PRINCIPAL ///////////////////////////////////

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

        cout << "Escolha uma opcao!";
        cout << "\n";
        cout << "\n1 - Jogar";
        cout << "\n2 - Regras";
        cout << "\n3 - Ranking";
        cout << "\n4 - Sair";
        cout << "\n=========================================\n";

        cin >> escolha;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ////////////////////// SWITCH ///////////////////////////////////////

        switch (escolha)
        {

            ////////////////////// JOGAR ////////////////////////////////////////

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

            ////////////////////// REGRAS ///////////////////////////////////////

        case 2:

            limpa_Tela();
            cout << "\n";

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

                cin >> sub_Escolha;

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
                    escolha = 0;
                }
            } while (sub_Escolha < 1 || sub_Escolha > 2);

            break;

            ////////////////////// MOSTRAR RANKING ///////////////////////////////

        case 3:

            limpa_Tela();
            mostrarRanking();
            cout << "\nPressione Enter para voltar ao menu.";
            cin.get();
            limpa_Tela();
            escolha = 0;
            break;

            ////////////////////// SAIR //////////////////////////////////////////

        case 4:

            limpa_Tela();
            cout << "Ate logo!!\n";
            break;

            ////////////////////// OPCAO INVALIDA ////////////////////////////////

        default:

            limpa_Tela();
            cout << "Opcao invalida!\n";
            break;
        }

    } while (escolha < 1 || escolha > 4);
}

//////////////////////// MAIN ///////////////////////////////////////////////

int main()
{
    setlocale(LC_ALL, "Portuguese");

    menu_Inicial();

    return 0;
}
