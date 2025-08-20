#include <iostream>
#include "console.h"
#include <vector>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;
using namespace std::chrono;

struct Snake { ///STRUC COBRA
    int x, y;
    bool vivo;
    int comeu;
};

bool contemApenasLetras(const std::string& str) {
    if (str.length() != 4) {
        return false;
    }
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

void MovimentoCobra(vector <Snake> &Cobra) { ///MOVIMENTO DO CORPO
    for(int i = Cobra.size()-1;i>0;i--){     ///FOR DO TAMANHO DA COBRA SE MOVIMENTO ATÉ A CABEÇA
        Cobra[i]=Cobra[i-1];                 ///POSIÇÃO FINAL RECEBE A ANTERIOR
        }
}

bool ColisaoCobra(const vector<Snake>& Cobra) {        ///COLISAO DO CORPO
    for(int i =1;i<Cobra.size();i++){                       ///FOR DO PESCOÇO PRA FRENTE, POIS NÃO PRECISA DA CABEÇÇA
        if(Cobra[0].x==Cobra[i].x&&Cobra[0].y==Cobra[i].y){ ///VERIFICA SE A CABEÇA ESTA ENCOSTADA EM ALGUMA PARTE DO CORPO TODO
            return true;
        }
    }
    return false;
}

bool ColisaoCobra(const vector<Snake>& Cobra, int m[15][17]) {
    if (m[Cobra[0].x][Cobra[0].y] == 1) {
        return true;
    } else {
        return false;
    }
}

void geraMaca(int m[15][17], bool& macaNoJogo, const vector<Snake>& Cobra) {
    if (!macaNoJogo) {
        int mx, my;
        bool posicaoValida;
        do {
            mx = rand() % 15;
            my = rand() % 17;

            // Verificar se a posição está ocupada pelo corpo da cobra
            posicaoValida = true;
            for (int i = 0; i < Cobra.size(); i++) {
                if (Cobra[i].x == mx && Cobra[i].y == my) {
                    posicaoValida = false;
                    break;
                }
            }
        } while (m[mx][my] == 1 || !posicaoValida);

        m[mx][my] = 2;
        macaNoJogo = true;
    }
}

void IncrementoDaCobra (vector <Snake>&Cobra) { ///AUMENTA O TAMANHO DO CORPO QUANDO PEGA A MAÇA
    Snake Cauda = Cobra.back();                 ///STRUCT CALDA RECEBE A ULTIMA POSIÇÃO
    Cobra.push_back(Cauda);                     ///VECTOR COBRA RECEBE A POSIÇÃO DO STRUCT CAUDA
}

void GerarMatrix (int m[15][17], int dificuldade){
    for(int i=0;i<15;i++){
        for(int j=0;j<17;j++){
            if(i==0||i==14||j==0||j==16){
                m[i][j]=1;
            } else {
                m[i][j]=0;
            }
        }
    }
}

void GerarMapa(int m[15][17], vector <Snake> Cobra){
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 17; j++) {
            bool CobraOn = false;                               ///UMA VARIAVEL BOOLEANA PARA QUEBRAR A IMPRESÃO DA COBRA
                if(i==Cobra[0].x&&j==Cobra[0].y){
                    cout<<char (79);
                    }else{
                        for(auto const &Snake:Cobra){           ///LOOP PARA IMPRIMIR A COBRA NO JOGO
                            if(i==Snake.x&&j==Snake.y){
                                cout << char(111);              ///personagem
                                CobraOn = true;                 ///QUANDO RECEBE TRUE ELE CONTINUA O CODIGO E VOLTA A SER FALSE NO PROXIMO CICLO
                                break;                          ///QUEBRA O LOOP
                            }
                        }
                        if(!CobraOn){                           ///QUANDO FOR FALSE A VARIAVEL BOOLEANA SEGUE O CODIGO
                            switch (m[i][j]) {
                            case 0: cout << " "; break;         ///caminho
                            case 1: cout << char(219); break;   ///parede
                            case 2: cout<<char(162); break;     ///maçã
                                                                ///default: cout << "-"; //erro
                            }
                        }                                       ///fim switch
                    }
                }
            cout << "\n";
        }
}

void salvarRanking(const string& nome, int &pontuacao,  int tempoEmSegundos) {  //salva a pontuacao no arquivo
    ofstream arquivoS;
    arquivoS.open("ranking.txt", std::ios_base::app);
    if (arquivoS.is_open()){
        time_t tempoAtual = time(nullptr); // tempo atual em segundos
        char dataFormatada[80];
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y %H:%M:%S", localtime(&tempoAtual));
        arquivoS << "Nome: " << nome <<  endl;
        arquivoS << "Pontuacao: " << pontuacao <<  endl;
        arquivoS << "Tempo de Jogo: " << tempoEmSegundos << " segundos" << endl;
        arquivoS << "Data: " << dataFormatada << endl << endl;
        arquivoS << endl;
        arquivoS.close();}


}

///recursividade (ordenando rank)

void exibirRankingRecursivo(vector<pair<int, string>>& ranking, int esquerda, int direita) {
    if (esquerda < direita)
    {
        int pivo = ranking[direita].first;
        int i = esquerda - 1;
        for (int j = esquerda; j <= direita - 1; j++)
        {
            if (ranking[j].first > pivo)
            {
                i++;
                swap(ranking[i], ranking[j]);
            }
        }
        swap(ranking[i + 1], ranking[direita]);
        int indice = i + 1;
        exibirRankingRecursivo(ranking, esquerda, indice - 1);
        exibirRankingRecursivo(ranking, indice + 1, direita);
    }
}

void exibirRanking() { ///exibi rank ordenado em tela
    ifstream arquivoS;
    string linha;
    vector<pair<int, string>> ranking;
    arquivoS.open("ranking.txt");
    if (arquivoS.is_open())
    {
        int pontos;
        string nome;
        while (arquivoS >> linha)
        {
            if (linha == "Pontuacao:")
            {
                arquivoS >> pontos;
                ranking.push_back(make_pair(pontos, nome));
            }
            else if (linha == "Nome:")
            {
                arquivoS >> nome;
            }
        }
        arquivoS.close();

        exibirRankingRecursivo(ranking, 0, ranking.size() - 1);

        cout << "Ranking:" << endl;
        for (const auto& pair : ranking)
        {
            cout << pair.second << " - " << pair.first << endl;
        }
    }
    else
    {
        cout << "Erro ao abrir o arquivo de ranking." << endl;
    }
}

int main()
{
    hide_cursor();

    int menu;
    string nome;
    int dificuldade;
    int m[15][17];
    int pontuacao = 0;
    int repetir = 0;
    int TamanhoCobra = 3;
    vector <Snake> Cobra;
    //Posicao inicial do personagem no console
    Cobra.push_back({5,5});
    Cobra.push_back({5,4});
    Cobra.push_back({5,3});
    ///VERIFICAÇÃO COBRA NA HORIZONTAL OU VERTICAL
    bool CobraHorizontal = false;
    bool CobraVertical   = false;
    ///ONDE A COBRA ESTA OLHANDO
    bool CabecaCima = false;
    bool CabecaBaixo = false;
    bool CabecaDireita = false;
    bool CabecaEsquerda = false;
    //Variavel para tecla pressionada
    char tecla;
    //Variavel para contagem de tempo em tela
    auto inicio = steady_clock::now();
    auto final = steady_clock::now();
    int tempoEmSegundos;
    //Gerador de Maçã
    srand (time(NULL));
    bool macaNoJogo = false;
    //Cobra viva
    Snake CobraViva;
    milliseconds diminuirVelocidade(45);
    //Modos Especiais
    bool JogoComTimer = false;
    bool JogoEspecial = false;
    bool IAJogo = false;
    //Jogo Com Timer
    seconds tempoLimite(180);

    do {
        clear_console();

        cout << "                           _____             _        " << endl;
        cout << "                          /  ___|           | |       " << endl;
        cout << "                          \\ `--. _ __   __ _| | _____ " << endl;
        cout << "                           `--. \\ '_ \\ / _` | |/ / _ \\" << endl;
        cout << "                          /\\__/ / | | | (_| |   <  __/" << endl;
        cout << "                          \\____/|_| |_|\\__,_|_|\\_\\___|" << endl;
        cout << "                                                      " << endl<<endl;
        cout <<"                          ______________________________ " << endl;
        cout << "                         |                              |" << endl;
        cout << "                         |         1 - COMECAR          |" << endl;
        cout << "                         |         2 - TUTORIAL         |" << endl;
        cout << "                         |         3 - RANKING          |" << endl;
        cout << "                         |         4 - MODOS ESPECIAIS  |" << endl;
        cout << "                         |         5 - SAIR             |" << endl;
        cout << "                         |______________________________|" << endl;
        cin >> menu;
        switch (menu) {
        case 1:{
            //Jogo
            cout<<"Selecione a dificuldade: [1] facil [2] medio [3] dificil."<<endl;
            cin>>dificuldade;
            while(dificuldade<1||dificuldade>3){
               cout<<"Opcao invalida! tente novamente:"<<endl;
               cin>>dificuldade;
            };
            cout << "digite seu nome: " << endl; //nome do jogador para o rank
            cin >> nome;
            while (!contemApenasLetras(nome)){
                cout << "Erro: O nome deve conter apenas 4 letras." << endl;
                cout << "digite seu nome:" << endl;
                cin >> nome;
            };

            system("cls");
            auto inicio = steady_clock::now();

            do {
                //Botar coisas para repetir aqui
                bool jogo = true;
                CobraViva.vivo = true;
                CobraViva.comeu = 0;
                bool macaNoJogo = false;
                bool aumentoVelocidade = false;
                auto inicio = steady_clock::now();
                milliseconds velocidade(750);
                milliseconds velocidadeTecla(500);
                auto inicioCobra = high_resolution_clock::now();
                auto inicioCobraMovimento = high_resolution_clock::now(); //Bloqueio de tecla
                CobraHorizontal = true;
                Cobra.clear();
                Cobra.push_back({5,5});
                Cobra.push_back({5,4});
                Cobra.push_back({5,3});
                CabecaDireita= true;
                CabecaBaixo = CabecaBaixo = CabecaCima = false;
                pontuacao = 0;

                GerarMatrix(m, dificuldade);
                while (jogo == true) {
                    ///Posiciona a escrita no inicio do console
                    set_cursor();

                    ///Imprime o jogo: mapa e personagem.
                    GerarMapa(m,Cobra);
                    //fim for mapa

                    auto agoraCobra = high_resolution_clock::now();
                    auto passouCobra = duration_cast<milliseconds>(agoraCobra - inicioCobra);
                    if (passouCobra >= velocidade) {
                        if (CabecaCima == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].x--;
                        }
                        if (CabecaBaixo == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].x++;
                        }
                        if (CabecaDireita == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].y++;
                        }
                        if (CabecaEsquerda == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].y--;
                        }
                        inicioCobra = agoraCobra;
                    }

                    auto agoraCobraMovimento = high_resolution_clock::now();
                    auto passouCobraMovimento = duration_cast<milliseconds>(agoraCobraMovimento - inicioCobraMovimento);

                    ///executa os movimentos
                    if (_kbhit()) {
                        tecla = get_input_without_enter();
                        switch (tecla) {
                        case 72:
                        case 'w': ///cima
                            if(CobraHorizontal==true && passouCobraMovimento >= velocidadeTecla) {
                                MovimentoCobra(Cobra);
                                Cobra[0].x--;
                                CobraVertical=true;
                                CobraHorizontal=false;
                                CabecaCima = true;
                                CabecaBaixo = CabecaDireita = CabecaEsquerda = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                        case 80:
                        case 's': ///baixo
                            if(CobraHorizontal==true && passouCobraMovimento >= velocidadeTecla) {
                                MovimentoCobra(Cobra);
                                Cobra[0].x++;
                                CobraVertical=true;
                                CobraHorizontal=false;
                                CabecaBaixo = true;
                                CabecaCima = CabecaDireita = CabecaEsquerda = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                        case 75:
                        case 'a': ///esquerda
                            if(CobraVertical==true && passouCobraMovimento >= velocidadeTecla) {
                                MovimentoCobra(Cobra);
                                Cobra[0].y--;
                                CobraVertical=false;
                                CobraHorizontal=true;
                                CabecaEsquerda = true;
                                CabecaCima = CabecaBaixo = CabecaDireita = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                        case 77:
                        case 'd': ///direita
                            if(CobraVertical==true && passouCobraMovimento >= velocidadeTecla) {
                                MovimentoCobra(Cobra);
                                Cobra[0].y++;
                                CobraVertical=false;
                                CobraHorizontal=true;
                                CabecaDireita = true;
                                CabecaCima = CabecaBaixo = CabecaEsquerda = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                            case 'o':
                            IncrementoDaCobra(Cobra);
                            break;
                        }
                    }
                    //tempo em tela
                    final = steady_clock::now();
                    auto tempo = final - inicio;


                    cout << "   TEMPO: " << duration_cast<seconds>(tempo).count() << endl;
                    cout << " PONTUACAO: " << pontuacao << endl; //pontuacao em tela

                    geraMaca(m, macaNoJogo, Cobra);

                    if (m[Cobra[0].x][Cobra[0].y] == 2) {
                        m[Cobra[0].x][Cobra[0].y] = 0;
                        IncrementoDaCobra(Cobra);
                        macaNoJogo = false;
                        pontuacao+=10; //somando 10 à pontuacao
                        CobraViva.comeu += 1; //Contador de maçãs comidas
                    }

                    if (ColisaoCobra(Cobra, m)) {
                        CobraViva.vivo = false;
                    }

                    if(ColisaoCobra(Cobra)){
                        CobraViva.vivo = false;
                    }

                    if(!CobraViva.vivo) {
                        jogo = false;
                    }

                    if (CobraViva.comeu == 10) {
                        jogo = false;
                    }

                    if (CobraViva.comeu % 5 == 0 && CobraViva.comeu != 0 && aumentoVelocidade == false) {
                        velocidade -= diminuirVelocidade;
                        aumentoVelocidade = true;
                    } else if (CobraViva.comeu % 5 != 0 && aumentoVelocidade == true) {
                        aumentoVelocidade = false;
                    }

                    if (tempo >= tempoLimite && JogoComTimer == true) {
                        jogo = false;
                    }

                }; //fim do laco do jogo
                if(CobraViva.vivo == false){
                    ///musica fica aqui
                }
                if (CobraViva.vivo == false) {
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    salvarRanking(nome,pontuacao, tempoEmSegundos);
                    cout<<nome<<" Voce fez: "<<pontuacao<<" pontos.";
                    cout<< endl << "Voce perdeu o jogo"<<endl;
                    cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                    cout<<"Professor: Alex Luciano"<<endl;
                    cout<<"Quer jogar novamente?"<<endl;
                    cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                    cin>>repetir;

                    system ("cls");
                }
                if (CobraViva.comeu == 100) {
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    salvarRanking(nome,pontuacao, tempoEmSegundos);
                    cout<<nome<<" Voce fez: "<<pontuacao<<" pontos.";
                    cout<< endl << "Voce ganhou o jogo"<<endl;
                    cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                    cout<<"Professor: Alex Luciano"<<endl;
                    cout<<"Quer jogar novamente?"<<endl;
                    cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                    cin>>repetir;

                    system ("cls");
                }
                if (jogo == false && JogoComTimer == true) {
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    salvarRanking(nome,pontuacao, tempoEmSegundos);
                    cout<<nome<<" Voce fez: "<<pontuacao<<" pontos."<<endl;
                    cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                    cout<<"Professor: Alex Luciano"<<endl;
                    cout<<"Quer jogar novamente?"<<endl;
                    cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                    cin>>repetir;

                    system ("cls");
                }
            } while (repetir == 1);
            break;
        }
        case 2: //Sobre o jogo
            system ("cls");
            cout<<endl<<endl<<endl<<endl;
            cout << "OBJETIVO: Coma 100 macas sem colidir com a parede ou com a cobra." << endl;
            cout << "MOVIMENTO: Use W, A, S e D para mover a cobra que se move sempre para frente" << endl;
            cout << "MACAS: Mova-se em direcao as macas para come-las e crescer." << endl;
            cout << "EVITAR COLISOES: Evite colidir com a parede ou com o corpo da cobra." << endl;
            cout << "PONTUACAO: A cada maca coletada o jogador recebe 10 pontos." << endl;
            cout << "VITORIA: Ao comer 100 macas sem colisoes, voce vence o jogo!" << endl<< endl;
            cout << "BOA SORTE!" << endl << endl;
            system("pause");
            system ("cls");
            break;
        case 3: //Rank
            system("cls");
            exibirRanking();
            system("pause");
            break;
        case 4: // Modos Especiais
            system ("cls");
            cout<<"Modos Especiais:"<<endl<<endl;
            cout<<"Jogo com Tempo: Jogo normal com tempo de 3 minutos para completar"<<endl<<endl;
            cout<<"Sim (1)"<<endl;
            cout<<"Nao (0)"<<endl;
            cin>>JogoComTimer;
            cout<<endl<<endl<<"Jogo Especial: Voce comeca com 100 macas e seu objetivo e chegar ate 0"<<endl<<endl;
            cout<<"Sim (1)"<<endl;
            cout<<"Nao (0)"<<endl;
            cin>>JogoEspecial;
            cout<<endl<<endl<<"Ativar IA: IA joga o jogo por voce"<<endl<<endl;
            cout<<"Sim (1)"<<endl;
            cout<<"Nao (0)"<<endl;
            cin>>IAJogo;
            break;
        case 5: //Obrigado por jogar
            break;
        default:
            cout << "Esta opcao nao e aceita digite outro numero"<<endl;
            system("pause");
            break;
        }
    }
    while (menu != 5);

    return 0;
} //fim main
