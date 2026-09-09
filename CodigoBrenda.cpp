#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
using namespace std;

struct palavraItem{
    string categoria;
    string palavra;
};
struct Jogador
{
    string nome;
    int pontuacao;
};

void carregarPalavras(const string& nomeFicheiro, 
    vector<palavraItem>& palavras)
{
    ifstream arquivo(nomeFicheiro); 

    if(!arquivo.is_open()) 
    {
        cout << "Erro ao abrir o ficheiro.\n";
        return;
    }

    string linha;

    while (getline(arquivo, linha)) 
    {
        size_t pos = linha.find(','); 
        if (pos != string::npos){ 
            palavraItem item;

            item.categoria = linha.substr(0, pos); 
            item.palavra = linha.substr(pos + 1); 

            palavras.push_back(item); 
        } 
    }
    arquivo.close();
}
void criarFicheiroPalavras()
{
    ifstream teste("palavras.txt");

    if (!teste.is_open())
    {
        ofstream arquivo("palavras.txt");

        arquivo << "Animais,gato\n";
        arquivo << "Animais,cachorro\n";
        arquivo << "Animais,elefante\n";
        arquivo << "Animais,leao\n";
        arquivo << "Animais,tigre\n";

        arquivo << "Frutas,banana\n";
        arquivo << "Frutas,laranja\n";
        arquivo << "Frutas,maca\n";
        arquivo << "Frutas,morango\n";
        arquivo << "Frutas,abacaxi\n";

        arquivo << "Paises,portugal\n";
        arquivo << "Paises,brasil\n";
        arquivo << "Paises,espanha\n";
        arquivo << "Paises,franca\n";
        arquivo << "Paises,italia\n";

        arquivo.close();

        cout << "\nFicheiro palavras.txt criado com sucesso!\n";
    }

    teste.close();
}

void guardarPartida(
    const string& nomeJogador, 
    const string& categoriaEscolhida, 
    const string& nomeDificuldade, 
    const string& palavraSecreta, 
    int erros, 
    int pontuacao, 
    const string& resultado) 
{
    ofstream arquivo("historico.txt", ios::app);

    if (!arquivo.is_open()){
        cout << "Erro ao abrir o ficheiro de histórico.\n";
        return;
    }

    arquivo << nomeJogador << ";"
            << categoriaEscolhida << ";"
            << nomeDificuldade << ";"
            << palavraSecreta << ";"
            << erros << ";"
            << pontuacao << ";"
            << resultado << "\n";

    arquivo.close();
}

//criação do boneco
void desenharForca(int erros) {
    cout << "\n  +---+\n";
    cout << "  |   |\n";
    cout << "  " << (erros >= 1 ? "O" : " ") << "   |\n";
    cout << " " << (erros >= 3 ? "/" : " ") << (erros >= 2 ? "|" : " ") << (erros >= 4 ? "\\" : " ") << "  |\n";
    cout << " " << (erros >= 5 ? "/" : " ") << " " << (erros >= 6 ? "\\" : " ") << "  |\n";
    cout << "=========\n";
}

void mostrarRanking(){
    ifstream arquivo("historico.txt");

    if(!arquivo.is_open()){
        cout << "\nErro ao abrir o ficheiro de histórico.\n";
        return;
    }

    vector<Jogador> jogadores;
    string linha;

    while (getline(arquivo, linha))
    {
        size_t pos = linha.find(';');

        if (pos != string::npos)
        {
            Jogador jogador;

            jogador.nome = linha.substr(0, pos);

            size_t posPontuacao = linha.find(';', pos + 1);
            posPontuacao = linha.find(';', posPontuacao + 1);
            posPontuacao = linha.find(';', posPontuacao + 1);
            posPontuacao = linha.find(';', posPontuacao + 1);

            size_t posFinal = linha.find(';', posPontuacao + 1);

            jogador.pontuacao = stoi(
                linha.substr(
                    posPontuacao + 1,
                    posFinal - posPontuacao - 1
                )
            );

            jogadores.push_back(jogador);
        }
    }

    arquivo.close();

    cout << "\n-------------- RANKING -------------- \n";

    for (int i = 0; i < jogadores.size() - 1; i++){
        for (int j = i + 1; j < jogadores.size(); j++){
            if (jogadores[j].pontuacao > jogadores[i].pontuacao){
                Jogador temp = jogadores[i];
                jogadores[i] = jogadores[j];
                jogadores[j] = temp;
            }
        }
    }

    for (int i = 0; i < jogadores.size(); i++){
        cout << i + 1
            << "º "
            << jogadores[i].nome
            << " - "
            << jogadores[i].pontuacao
            << " pontos\n";
    }
}

void jogar(const string& nomejogador, vector<palavraItem>& listaPalavras){
    int dificuldade;
    int maxErros;
    string nomeDificuldade;
    int pontuacao;

    int opcao;
    cout << "\n--------------- MENU ---------------\n";
    cout << "1 - Iniciar Jogo\n";
    cout << "2 - Ver  Ranking\n";
    cout << "3 - Sair.\n";

    cout << "\nEscolha uma opção: ";
    cin >> opcao;

    if (opcao == 1){
        cout << "\nVocê escolheu JOGAR!\n";
    }
    else if (opcao == 2){
        mostrarRanking();

        char jogarAgora;

        cout << "\nDeseja jogar? (s/n): ";
        cin >> jogarAgora;

        if (jogarAgora == 'n' || jogarAgora == 'N'){
            cout << "\nAté à próxima, " << nomejogador << "!\n";
            return;
        }
    }
    else if (opcao == 3){
        cout << "\nAté à próxima, " << nomejogador << "!\n";
    }
    else{
        cout << "\nOpção inválida!\n";
    }

    cout << "\nEscolha a dificuldade:\n";
    cout << "1 - Fácil\n";
    cout << "2 - Médio\n";
    cout << "3 - Difícil\n";

    cout << "Escolha uma opção: ";
    cin >> dificuldade;

    if (dificuldade == 1){
        maxErros = 8;
        nomeDificuldade = "Fácil";
        pontuacao = 80;
    }
    else if (dificuldade == 2){
        maxErros = 6;
        nomeDificuldade = "Médio";
        pontuacao = 100;
    }
    else if (dificuldade == 3){
        maxErros = 4;
        nomeDificuldade = "Difícil";
        pontuacao = 120;
    }
    else{
        cout << "Dificuldade inválida!\n";
        return;
    }

    cout << "\nEscolha uma categoria:\n";
    cout << "1 - Animais\n";
    cout << "2 - Frutas\n";
    cout << "3 - Paises\n";

    int opcaoCategoria;

    cout << "Escolha uma opção: ";
    cin >> opcaoCategoria;

    string categoriaEscolhida;

    if (opcaoCategoria == 1){
        categoriaEscolhida = "Animais";
    }
    else if (opcaoCategoria == 2){
        categoriaEscolhida = "Frutas";
    }
    else if (opcaoCategoria == 3){
        categoriaEscolhida = "Paises";
    }
    else{
        cout << "Categoria inválida!\n";
        return;
    }

vector<string> palavrasFiltradas;
for(const auto& item : listaPalavras){
    if(item.categoria == categoriaEscolhida){
        palavrasFiltradas.push_back(item.palavra);
    }
}

int numero;

cout << "\nEscolha um número de 1 a " << palavrasFiltradas.size() << ": ";
cin >> numero;

if (numero < 1 || numero > palavrasFiltradas.size()){
    cout << "Número inválido!\n";
    return;
}
string palavraSecreta =
    palavrasFiltradas[numero -1];

string letrasUsadas = "";
int erros = 0;
string resultado;

string palavraEscondida = "";

    for (size_t i = 0; i < palavraSecreta.length(); i++){
        palavraEscondida += "_";
    }

while (palavraEscondida != palavraSecreta && erros < maxErros){
    char letra;

    cout << "\nPalavra: " << palavraEscondida << endl;
    cout << "Letras usadas: " << letrasUsadas << endl;
    cout << "Erros: " << erros << endl;
    cout << "Pontuação: " << pontuacao << endl;

    desenharForca(erros);

    cout << "\nDigite uma letra: ";
    cin >> letra;

    if (letrasUsadas.find(letra) != string::npos){
        cout << "Essa letra já foi utilizada!\n";
        continue;
    }

    letrasUsadas += letra;
    bool acertou = false;

    for (size_t i = 0; i < palavraSecreta.length(); i++){
        if (palavraSecreta[i] == letra){
            palavraEscondida[i] = letra;
            acertou = true;
        }
    }

    if (acertou){
        cout << "Acertou!\n";
        if(erros > 0){ 
            pontuacao += 5;
            cout << "+5 pontos!\n"; 
        }
    }
    else{
        erros++;
        pontuacao -= 10;

        if (pontuacao < 0){
            pontuacao = 0;
        }

        cout << "Errou!\n";
    }
}

if (palavraEscondida == palavraSecreta){
    resultado = "Ganhou";

    cout << "\nPARABENS! Você descobriu a palavra!\n";
    cout << "A palavra era: " << palavraSecreta << endl;
}
else{
    resultado = "Perdeu";

    cout << "\nVocê perdeu!\n";
    cout << "A palavra era: " << palavraSecreta << endl;
}
cout << "\nPontuação final: " << pontuacao << " pontos\n";


guardarPartida(nomejogador, categoriaEscolhida, nomeDificuldade, palavraSecreta, erros, pontuacao, resultado);

}

int main()
{
    string nomejogador;
    vector<palavraItem> listaPalavras;
    char novamente; 

    cout << "================================\n";
    cout << "          JOGO DA FORCA         \n";
    cout << "================================\n";

    cout << "\nDigite o seu nome: ";
    cin >> nomejogador;

    criarFicheiroPalavras();
    carregarPalavras("palavras.txt", listaPalavras);

    if (listaPalavras.empty()){
        cout << "Erro: não foi possível carregar as palavras.\n";
        return 1;
    }
    do{
        jogar(nomejogador, listaPalavras);

        cout << "\nDeseja jogar novamente? (s/n): ";
        cin >> novamente;

    } 
    while (novamente == 's' || novamente == 'S');
    cout << "\nObrigado por jogar, "
         << nomejogador
         << "!\n";

    cout << "Até à próxima!\n";

    return 0;
}
