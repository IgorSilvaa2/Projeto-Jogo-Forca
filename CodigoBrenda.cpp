#include <iostream>
#include <fstream> // necessario para abrir os ficheiros
#include <string>
#include <vector> // necessario para ler a lista de palavras
using namespace std;

// estrutura para carregar palavras
struct palavraItem{
    string categoria;
    string palavra;
};

// função para carregar o ficheiro 'palavras.txt'
void carregarPalavras(const string$ nomeFicheiro, //O const é a abreviatura da palavra inglesa "constant" (que significa constante ou imutável).
    vector<palavraItem>& palavras)
{
    ifstream arquivo(nomeFicheiro); //função para abrir o ficheiro 'nomeFicheiro'

    if(!arquivo.is_open()) //O uso de ! é para confirmar se o ficheiro está aberto ou não, assim, se não abrir o ficheiro, irá mostrar a mensagem.
    {
        cout << "Erro ao abrir o ficheiro.\n";
        return;
    }

    string linha;

    while (getline(arquivo, linha)) //utilizar o while para continuar enquanto existirem linhas para ler
    {
        size_t pos = linha.find(','); //size_t guarda tamanhos, contagens ou posições de texto. Garante que o numero é sempre zero ou positivo. (size - tamanho, t - type/ tipo)
        // size_t é só uma "gaveta" de guardar numeros int +, usada pelo C++ para indicar posições e tamanhos de coisas.
        // size_t pos: cria uma "gaveta" chamada 'pos' preparada para guardar um numero positivo.

        if (pos != string::npos)
        { // string::npos é um valor do C++ que significa "não foi encontrado" (no position)
          //pos != string::npos lê-se: "Se a posição guardada em 'pos' for diferente de 'não encontrado".
            palavraItem item;

            item.categora = linha.substr(0, pos); //substr(): pega uma parte da string e pega a parte depois da virgula.
            item.palavra = linha.substr(pos + 1);
            //O substr é a abreviatura de substring (que significa "subfrase" ou "pedaço de texto"). É uma função do C++ usada para cortar e extrair um pedaço de uma palavra ou frase (string).

            palavras.push_back(item);// push_back() "Apanha estes dados (item) e acrescenta-os ao fim da minha lista (lista)".
        } // no array é necessario informar no inicio a quantidade, assim, o push_back ajusta o tamanho sozinho, vai aumentando o tamanho da lista automaticamente à medida que encontra novas palavras.
    }
    arquivo.close();
}

--

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
