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

bool ColisaoCobra(const vector<Snake>& Cobra, bool especialAtivoCobra) {        ///COLISAO DO CORPO
    if (especialAtivoCobra == false){
        for(int i =1;i<Cobra.size();i++){                       ///FOR DO PESCOÇO PRA FRENTE, POIS NÃO PRECISA DA CABEÇÇA
            if(Cobra[0].x==Cobra[i].x&&Cobra[0].y==Cobra[i].y){ ///VERIFICA SE A CABEÇA ESTA ENCOSTADA EM ALGUMA PARTE DO CORPO TODO
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

bool ColisaoCobra(const vector<Snake>& Cobra, int m[15][17], bool especialAtivoParede) {
    if (m[Cobra[0].x][Cobra[0].y] == 1 || m[Cobra[0].x][Cobra[0].y] == 5 && especialAtivoParede == false) {
        return true;
    } else if (m[Cobra[0].x][Cobra[0].y] == 5 && especialAtivoParede == true) {
        return false;
    } else {
        return false;
    }
}

void geraMaca(int m[15][17], bool& macaNoJogo, const vector<Snake>& Cobra, int& mx, int& my) {
    if (!macaNoJogo) {
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
        } while (m[mx][my] != 0 || !posicaoValida);

        m[mx][my] = 2;
        macaNoJogo = true;
    }
}

void IncrementoDaCobra (vector <Snake>&Cobra) { ///AUMENTA O TAMANHO DO CORPO QUANDO PEGA A MAÇA
    Snake Cauda = Cobra.back();                 ///STRUCT CALDA RECEBE A ULTIMA POSIÇÃO
    Cobra.push_back(Cauda);                     ///VECTOR COBRA RECEBE A POSIÇÃO DO STRUCT CAUDA
}

void GerarMatrix (int m[15][17], int dificuldade, int FaseJogo){
    for(int i=0;i<15;i++){
        for(int j=0;j<17;j++){
            if(i==0||i==14||j==0||j==16){
                m[i][j]=1;
            } else {
                m[i][j]=0;
            }
            if(FaseJogo==2&&i>2&&i<12&&j==8){
                m[i][j]=5;
            }
            if(FaseJogo==2&&i==8&&j>3&&j<14){
                m[i][j]=5;
            }
            if(FaseJogo==3&&i>1&&i<13&&i%2==0&&j>3&&j<14){
                m[i][j]=5;
            }
        }
    }
}

void GerarMapa(int m[15][17], vector <Snake> Cobra, bool& especialColocadoPontos, bool& especialColocadoParede, bool& especialColocadoCobra){
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
                    case 3: cout<<char(36); break;      ///Poder de Dobra a pontuação por um tempo
                    case 4: cout<<char(209); break;    ///Poder de atravessar parede
                    case 5: cout<<char(35); break;    ///Parede quebravel
                    case 6: cout<<char(244); break;    ///Poder de atravessar o próprio corpo
                                                        ///default: cout << "-"; //erro
                    }
                }                                       ///fim switch
            }

            if (especialColocadoPontos == false) {
                int ex, ey;
                bool posicaoPontosValida;
                do {
                    ex = rand() % 15;
                    ey = rand() % 17;

                    // Verificar se a posição está ocupada pelo corpo da cobra
                    posicaoPontosValida = true;
                    for (int i = 0; i < Cobra.size(); i++) {
                        if (Cobra[i].x == ex && Cobra[i].y == ey) {
                            posicaoPontosValida = false;
                            break;
                        }
                    }
                } while (m[ex][ey] != 0 || !posicaoPontosValida);
                m[ex][ey] = 3;
                especialColocadoPontos = true;
            }

            if (especialColocadoParede == false) {
                int epx, epy;
                bool posicaoParedeValida;
                do {
                    epx = rand() % 15;
                    epy = rand() % 17;

                    // Verificar se a posição está ocupada pelo corpo da cobra
                    posicaoParedeValida = true;
                    for (int i = 0; i < Cobra.size(); i++) {
                        if (Cobra[i].x == epx && Cobra[i].y == epy) {
                            posicaoParedeValida = false;
                            break;
                        }
                    }
                } while (m[epx][epy] != 0 || !posicaoParedeValida);
                m[epx][epy] = 4;
                especialColocadoParede = true;
            }

            if (especialColocadoCobra == false) {
                int ecx, ecy;
                bool posicaoCobraValida;
                do {
                    ecx = rand() % 15;
                    ecy = rand() % 17;

                    // Verificar se a posição está ocupada pelo corpo da cobra
                    posicaoCobraValida = true;
                    for (int i = 0; i < Cobra.size(); i++) {
                        if (Cobra[i].x == ecx && Cobra[i].y == ecy) {
                            posicaoCobraValida = false;
                            break;
                        }
                    }
                } while (m[ecx][ecy] != 0 || !posicaoCobraValida);
                m[ecx][ecy] = 6;
                especialColocadoCobra = true;
            }
        }
    cout << "\n";
    }
}

void ModoEspecial(vector<Snake>&Cobra){
    Cobra.clear();
    Cobra.push_back({13,9});
    for(int i=14;i>0;i--){
        if(i%2!=0){
            for(int j=9;j>0;j--){
                if(i>0&&i<14&&j>0&&j<9){
                Cobra.push_back({i,j});
                }
            }
        } else {
                for(int j=0;j<9;j++){
                    if(i>0&&i<14&&j>0&&j<9){
                    Cobra.push_back({i,j});
                    }
                }
            }
     }
}

void pontosMovimentosGastos(int movimentos, int dificuldade, int& pontuacao, bool JogoComTimer, bool JogoEspecial, bool& diminuiuPontos) {
    if (!JogoComTimer && !JogoEspecial) {
        switch(dificuldade) {
            case 1: // Fácil
                if (movimentos % 50 == 0 && movimentos != 0 && !diminuiuPontos && pontuacao < 0) {
                    pontuacao -= 20;
                    diminuiuPontos = true;
                } else if (movimentos % 50 != 0) {
                    diminuiuPontos = false;
                }
                break;
            case 2: // Médio
                if (movimentos % 40 == 0 && movimentos != 0 && !diminuiuPontos && pontuacao < 0) {
                    pontuacao -= 20;
                    diminuiuPontos = true;
                } else if (movimentos % 40 != 0) {
                    diminuiuPontos = false;
                }
                break;
            case 3: // Difícil
                if (movimentos % 30 == 0 && movimentos != 0 && !diminuiuPontos && pontuacao < 0) {
                    pontuacao -= 20;
                    diminuiuPontos = true;
                } else if (movimentos % 30 != 0) {
                    diminuiuPontos = false;
                }
                break;
        }
    }
}

void salvarRanking(const string& nome, int &pontuacao,  int tempoEmSegundos, int dificuldade, int movimentos) {  ///salva a pontuacao no arquivo
    ofstream arquivoS;
    arquivoS.open("ranking.txt", std::ios_base::app);
    if (arquivoS.is_open()){
        time_t tempoAtual = time(nullptr); ///tempo atual em segundos
        char dataFormatada[80];
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y %H:%M:%S", localtime(&tempoAtual)); ///ajeitando a data
        arquivoS << "Nome: " << nome <<  endl;
        arquivoS << "Pontuacao: " << pontuacao <<  endl;
        arquivoS << "Tempo de Jogo: " << tempoEmSegundos << " segundos" << endl;
        arquivoS << "Movimentos:" << movimentos << endl;
        if(dificuldade==1){
             arquivoS << "Dificuldade: " << "Facil" << endl;
        }else if(dificuldade==2){
            arquivoS << "Dificuldade: " << "Medio" << endl;
        }else if(dificuldade==3){
            arquivoS << "Dificuldade: " << "Dificil"<< endl;
        }
        arquivoS << "Data: " << dataFormatada << endl << endl;
        arquivoS << endl;
        arquivoS.close();}


}


void salvarRankingDesafio(const string& nome, int &pontuacao,  int tempoEmSegundos,int movimentos, int &escolha){  ///ranking separado para o desafio

   ofstream arquivoS;
    arquivoS.open("rankingDesafio.txt", std::ios_base::app);
    if (arquivoS.is_open()){
        time_t tempoAtual = time(nullptr); // tempo atual em segundos
        char dataFormatada[80];
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y %H:%M:%S", localtime(&tempoAtual));
        arquivoS << "Nome: " << nome <<  endl;
        arquivoS << "Pontuacao: " << pontuacao <<  endl;
        arquivoS << "Tempo de Jogo: " << tempoEmSegundos << " segundos" << endl;
        arquivoS << "Data: " << dataFormatada << endl;
        arquivoS << "Movimentos:" << movimentos << endl;
        if(escolha==1){
            arquivoS << "MODO: jogo com tempo." << endl;
        }else if(escolha==2){
            arquivoS << "MODO: jogo especial." << endl;
        }

        arquivoS << endl;
        arquivoS.close();}

}

///recursividade ordenando rank pares
///realiza trocas para posicionar os elementos em ordem decrescente com base no primeiro elemento

void exibirRankingRecursivo(vector<pair<int, string>>& ranking, int esquerda, int direita) {
    if (esquerda < direita)
    {
        int pivo = ranking[direita].first; ///pivo selecionado como ultimo elemento, usado para a base da comparacao
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
        exibirRankingRecursivo(ranking, esquerda, indice - 1); ///ordenando esquerda
        exibirRankingRecursivo(ranking, indice + 1, direita); ///ordenando direita
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



void exibirRankingDesafio(){
    ifstream arquivoS;
    string linha;
    vector<pair<int, string>> ranking;
    arquivoS.open("rankingDesafio.txt");
    if (arquivoS.is_open())
    {
        int pontos;
        string nome;
        int escolha;
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

//// Função para verificar se a posição é segura (não é uma parede)
//bool posicaoSegura(int x, int y) {
//    return m[y][x] != 1; // Assumindo que 'm' é a matriz do jogo e 1 representa uma parede
//}

int main()
{
    hide_cursor();

    int menu;
    int escolha;
    string nome;
    int dificuldade;
    int FaseJogo = 1;
    int m[15][17];
    int pontuacao;
    int pontuacaoAnterior;
    int repetir = 0;
    int TamanhoCobra = 3;
    int movimentos;
    int movimentosAnterior;
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
    int mx, my;
    //Cobra viva
    Snake CobraViva;
    milliseconds diminuirVelocidade(45);
    //Modos Especiais
    bool JogoComTimer = false;
    bool JogoEspecial = false;
    bool IAJogo = false;
    //Jogo Com Timer
    seconds tempoLimite(180);
    //Especial ativo
    milliseconds intervaloEspecial(5000);

    do {
        PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC);
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
            if (JogoComTimer == false && JogoEspecial == false) {
                cout<<"Selecione a dificuldade: [1] facil [2] medio [3] dificil."<<endl;
                cin>>dificuldade;
                while(dificuldade<1||dificuldade>3){
                   cout<<"Opcao invalida! tente novamente:"<<endl;
                   cin>>dificuldade;
                }
            }
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
                ///Botar coisas para repetir aqui
                PlaySound(TEXT("trilha.wav"), NULL, SND_ASYNC);
                ///Modo especial e Modo normal
                if(JogoEspecial==true){
                    Cobra.clear();
                    ModoEspecial(Cobra);
                } else {
                    Cobra.clear();
                    Cobra.push_back({5,5});
                    Cobra.push_back({5,4});
                    Cobra.push_back({5,3});
                }
                CabecaDireita= true;
                CobraHorizontal = true;
                CabecaBaixo = CabecaEsquerda = CabecaCima = false;
                CobraViva.vivo = true;
                CobraViva.comeu = 0;
                bool macaNoJogo = false;
                bool aumentoVelocidade = false;
                auto inicio = steady_clock::now();
                milliseconds velocidade;
                if (dificuldade == 1 && IAJogo == false) {
                    velocidade = milliseconds(750);
                } else if (dificuldade == 2 && IAJogo == false) {
                    velocidade = milliseconds(600);
                } else if (dificuldade == 3 && IAJogo == false) {
                    velocidade = milliseconds(450);
                }
                if (IAJogo == true) {
                    velocidade = milliseconds(200);
                }
                if (JogoComTimer == true) {
                    velocidade = milliseconds(600);
                }
                if (JogoEspecial == true) {
                    velocidade = milliseconds(600);
                }
                ///Reseta pontos e movimentos
                if (FaseJogo == 1) {
                    pontuacao = 0;
                    movimentos = 0;
                } else {
                    pontuacao = pontuacaoAnterior;
                    movimentos = movimentosAnterior;
                }
                milliseconds velocidadeTecla(250);
                auto inicioCobra = high_resolution_clock::now();
                auto inicioCobraMovimento = high_resolution_clock::now(); //Bloqueio de tecla
                bool jogo = true;
                bool diminuiuPontos = false;
                ///Poderes especiais
                bool especialAtivoPontos = false;
                bool especialColocadoPontos = false;
                auto inicioEspecial = high_resolution_clock::now();
                bool especialAtivoParede = false;
                bool especialColocadoParede = false;
                bool especialAtivoCobra = false;
                bool especialColocadoCobra = false;

                GerarMatrix(m, dificuldade, FaseJogo);
                while (jogo == true) {
                    ///Posiciona a escrita no inicio do console
                    set_cursor();
                    ///Imprime o jogo: mapa e personagem.
                    GerarMapa(m,Cobra, especialColocadoPontos, especialColocadoParede, especialColocadoCobra);
                    //fim for mapa
                    auto agoraCobra = high_resolution_clock::now();
                    auto passouCobra = duration_cast<milliseconds>(agoraCobra - inicioCobra);
                    if (passouCobra >= velocidade) {
                        if (CabecaCima == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].x--;
                            movimentos++;
                        }
                        if (CabecaBaixo == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].x++;
                            movimentos++;
                        }
                        if (CabecaDireita == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].y++;
                            movimentos++;
                        }
                        if (CabecaEsquerda == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].y--;
                            movimentos++;
                        }
                        inicioCobra = agoraCobra;
                    }

                    auto agoraCobraMovimento = high_resolution_clock::now();
                    auto passouCobraMovimento = duration_cast<milliseconds>(agoraCobraMovimento - inicioCobraMovimento);

                    ///executa os movimentos
//                    if (IAJogo == false) {
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
                                jogo = false;
                                FaseJogo++;
                                pontuacaoAnterior = pontuacao;
                                movimentosAnterior = movimentos;
                                ///Cobra.pop_back();
                                break;
                            }
                        }
//                    } else if (IAJogo == true) {
//                        int movDir;
//
//                        // Decidindo a direção de movimento
//                        if (abs(mx - Cobra[0].x) > abs(my - Cobra[0].y)) {
//                            if (mx > Cobra[0].x && movDir != 4 && posicaoSegura(Cobra[0].x + 1, Cobra[0].y)) {
//                                movDir = 3; // Mover para a direita
//                            } else if (mx < Cobra[0].x && movDir != 3 && posicaoSegura(Cobra[0].x - 1, Cobra[0].y)) {
//                                movDir = 4; // Mover para a esquerda
//                            } else if (my > Cobra[0].y && movDir != 1 && posicaoSegura(Cobra[0].x, Cobra[0].y + 1)) {
//                                movDir = 2; // Mover para baixo
//                            } else if (my < Cobra[0].y && movDir != 2 && posicaoSegura(Cobra[0].x, Cobra[0].y - 1)) {
//                                movDir = 1; // Mover para cima
//                            } else {
//                                // Caso a direção escolhida não seja segura, escolher uma direção alternativa
//                                if (CobraHorizontal) {
//                                    if (posicaoSegura(Cobra[0].x, Cobra[0].y + 1)) {
//                                        movDir = 2; // Mover para baixo
//                                    } else if (posicaoSegura(Cobra[0].x, Cobra[0].y - 1)) {
//                                        movDir = 1; // Mover para cima
//                                    }
//                                } else if (CobraVertical) {
//                                    if (posicaoSegura(Cobra[0].x + 1, Cobra[0].y)) {
//                                        movDir = 3; // Mover para a direita
//                                    } else if (posicaoSegura(Cobra[0].x - 1, Cobra[0].y)) {
//                                        movDir = 4; // Mover para a esquerda
//                                    }
//                                }
//                            }
//                        } else {
//                            if (my > Cobra[0].y && movDir != 1 && posicaoSegura(Cobra[0].x, Cobra[0].y + 1)) {
//                                movDir = 2; // Mover para baixo
//                            } else if (my < Cobra[0].y && movDir != 2 && posicaoSegura(Cobra[0].x, Cobra[0].y - 1)) {
//                                movDir = 1; // Mover para cima
//                            } else if (mx > Cobra[0].x && movDir != 4 && posicaoSegura(Cobra[0].x + 1, Cobra[0].y)) {
//                                movDir = 3; // Mover para a direita
//                            } else if (mx < Cobra[0].x && movDir != 3 && posicaoSegura(Cobra[0].x - 1, Cobra[0].y)) {
//                                movDir = 4; // Mover para a esquerda
//                            } else {
//                                // Caso a direção escolhida não seja segura, escolher uma direção alternativa
//                                if (CobraHorizontal) {
//                                    if (posicaoSegura(Cobra[0].x, Cobra[0].y + 1)) {
//                                        movDir = 2; // Mover para baixo
//                                    } else if (posicaoSegura(Cobra[0].x, Cobra[0].y - 1)) {
//                                        movDir = 1; // Mover para cima
//                                    }
//                                } else if (CobraVertical) {
//                                    if (posicaoSegura(Cobra[0].x + 1, Cobra[0].y)) {
//                                        movDir = 3; // Mover para a direita
//                                    } else if (posicaoSegura(Cobra[0].x - 1, Cobra[0].y)) {
//                                        movDir = 4; // Mover para a esquerda
//                                    }
//                                }
//                            }
//                        }
//
//                        // Executando o movimento
//                        switch (movDir) {
//                            case 1: // Para cima
//                                if (CobraHorizontal && posicaoSegura(Cobra[0].x, Cobra[0].y - 1)) {
//                                    MovimentoCobra(Cobra);
//                                    Cobra[0].y--; // Movendo para cima (diminuindo y)
//                                    CobraVertical = true;
//                                    CobraHorizontal = false;
//                                    CabecaCima = true;
//                                    CabecaBaixo = CabecaDireita = CabecaEsquerda = false;
//                                }
//                                break;
//                            case 2: // Para baixo
//                                if (CobraHorizontal && posicaoSegura(Cobra[0].x, Cobra[0].y + 1)) {
//                                    MovimentoCobra(Cobra);
//                                    Cobra[0].y++; // Movendo para baixo (aumentando y)
//                                    CobraVertical = true;
//                                    CobraHorizontal = false;
//                                    CabecaBaixo = true;
//                                    CabecaCima = CabecaDireita = CabecaEsquerda = false;
//                                }
//                                break;
//                            case 3: // Para a direita
//                                if (CobraVertical && posicaoSegura(Cobra[0].x + 1, Cobra[0].y)) {
//                                    MovimentoCobra(Cobra);
//                                    Cobra[0].x++; // Movendo para a direita (aumentando x)
//                                    CobraVertical = false;
//                                    CobraHorizontal = true;
//                                    CabecaDireita = true;
//                                    CabecaCima = CabecaBaixo = CabecaEsquerda = false;
//                                }
//                                break;
//                            case 4: // Para a esquerda
//                                if (CobraVertical && posicaoSegura(Cobra[0].x - 1, Cobra[0].y)) {
//                                    MovimentoCobra(Cobra);
//                                    Cobra[0].x--; // Movendo para a esquerda (diminuindo x)
//                                    CobraVertical = false;
//                                    CobraHorizontal = true;
//                                    CabecaEsquerda = true;
//                                    CabecaCima = CabecaBaixo = CabecaDireita = false;
//                                }
//                                break;
//                        }
//                    }

                    //tempo em tela
                    final = steady_clock::now();
                    auto tempo = final - inicio;

                    ///coisas em tela

                    cout << "   TEMPO: " << duration_cast<seconds>(tempo).count() << endl;
                    cout << " PONTUACAO: " << pontuacao << endl; //pontuacao em tela
                    cout << "   FASE:    " << FaseJogo << endl; //Fase do jogo
                    cout << "MOVIMENTOS: " << movimentos << endl;

                    geraMaca(m, macaNoJogo, Cobra, mx, my);
                    pontosMovimentosGastos(movimentos, dificuldade, pontuacao, JogoComTimer, JogoEspecial, diminuiuPontos);

                    if (m[Cobra[0].x][Cobra[0].y] == 2) {
                        m[Cobra[0].x][Cobra[0].y] = 0;
                        if(JogoEspecial==true){
                            Cobra.pop_back();
                        }else {
                            IncrementoDaCobra(Cobra);
                        }
                        macaNoJogo = false;
                        switch (dificuldade)
                        {
                        case 1:
                            pontuacao+=10; //somando 10 à pontuacao
                            CobraViva.comeu += 1; //Contador de maçãs comidas
                            if (especialAtivoPontos == true) {
                                pontuacao+=10;
                            }
                            break;
                        case 2:
                            pontuacao+=20; //somando 10 à pontuacao
                            CobraViva.comeu += 1; //Contador de maçãs comidas
                            if (especialAtivoPontos == true) {
                                pontuacao+=10;
                            }
                            break;
                        case 3:
                            pontuacao+=30; //somando 10 à pontuacao
                            CobraViva.comeu += 1; //Contador de maçãs comidas
                            if (especialAtivoPontos == true) {
                                pontuacao+=10;
                            }
                            break;
                        }

                        if (JogoComTimer == true || JogoEspecial == true) {
                            pontuacao+=10;
                            CobraViva.comeu += 1; //Contador de maçãs comidas
                        }
                    }

                    ///verificações de vitoria e derrota

                    if (ColisaoCobra(Cobra, m, especialAtivoParede) || ColisaoCobra(Cobra, especialAtivoCobra)) { ///colisões normais
                        CobraViva.vivo = false;
                    }

                    if (tempo >= tempoLimite && JogoComTimer == true) { ///modo de timer
                        CobraViva.vivo = false;
                    }

                    if(JogoEspecial== true && Cobra.size()==3){                                ///modo especial
                        jogo = false;
                    }

                    if(!CobraViva.vivo) {                               ///jogo quebra aqui
                        jogo = false;
                    }

                    ///pontuação de acordo com a dificuldade

                    if(dificuldade==1){
                        switch (FaseJogo){
                        case 1:
                            if (CobraViva.comeu == 20) {
                                jogo = false;
                                FaseJogo++;
                                pontuacaoAnterior = pontuacao;
                                movimentosAnterior = movimentos;
                            }
                            break;
                        case 2:
                             if (CobraViva.comeu == 50) {
                                jogo = false;
                                FaseJogo++;
                                pontuacaoAnterior = pontuacao;
                                movimentosAnterior = movimentos;
                            }
                            break;
                        case 3:
                            if (CobraViva.comeu == 100) {
                               jogo = false;
                               FaseJogo++;
                               pontuacaoAnterior = pontuacao;
                               movimentosAnterior = movimentos;
                            }
                            break;
                        }
                    }
                    if(dificuldade==2 || JogoComTimer == false && JogoEspecial == false){
                        switch (FaseJogo){
                        case 1:
                            if (CobraViva.comeu == 40) {
                                jogo = false;
                                FaseJogo++;
                                pontuacaoAnterior = pontuacao;
                                movimentosAnterior = movimentos;
                            }
                            break;
                        case 2:
                             if (CobraViva.comeu == 70) {
                                jogo = false;
                                FaseJogo++;
                                pontuacaoAnterior = pontuacao;
                                movimentosAnterior = movimentos;
                            }
                            break;
                        case 3:
                            if (CobraViva.comeu == 100) {
                               jogo = false;
                               FaseJogo++;
                               pontuacaoAnterior = pontuacao;
                               movimentosAnterior = movimentos;
                            }
                            break;
                        }
                    }
                    if(dificuldade==3){
                        switch (FaseJogo){
                        case 1:
                            if (CobraViva.comeu == 50) {
                                jogo = false;
                                FaseJogo++;
                                pontuacaoAnterior = pontuacao;
                                movimentosAnterior = movimentos;
                            }
                            break;
                        case 2:
                             if (CobraViva.comeu == 100) {
                                jogo = false;
                                FaseJogo++;
                                pontuacaoAnterior = pontuacao;
                                movimentosAnterior = movimentos;
                            }
                            break;
                        case 3:
                            if (CobraViva.comeu == 120) {
                               jogo = false;
                               FaseJogo++;
                               pontuacaoAnterior = pontuacao;
                               movimentosAnterior = movimentos;
                            }
                            break;
                        }
                    }

                    ///aumento de velocidade da cobra quando come a maça
                    if (CobraViva.comeu % 5 == 0 && CobraViva.comeu != 0 && aumentoVelocidade == false) {
                        velocidade -= diminuirVelocidade;
                        aumentoVelocidade = true;
                    } else if (CobraViva.comeu % 5 != 0 && aumentoVelocidade == true) {
                        aumentoVelocidade = false;
                    }

                    //Pegar o poder
                    if (m[Cobra[0].x][Cobra[0].y] == 3) {
                        m[Cobra[0].x][Cobra[0].y] = 0;
                        pontuacao+=10;
                        especialColocadoPontos = false;
                        especialAtivoPontos = true;
                        velocidade -= diminuirVelocidade;
                        inicioEspecial = high_resolution_clock::now(); // Inicializa o tempo de início aqui
                    }

                    if (especialAtivoPontos == true) {
                        auto agoraEspecial = high_resolution_clock::now();
                        auto passouEspecial = duration_cast<milliseconds>(agoraEspecial - inicioEspecial);
                        if (passouEspecial >= intervaloEspecial) {
                            inicioEspecial = agoraEspecial;
                            especialAtivoPontos = false;
                        }
                    }

                    if (m[Cobra[0].x][Cobra[0].y] == 4) {
                        m[Cobra[0].x][Cobra[0].y] = 0;
                        pontuacao+=10;
                        especialColocadoParede = false;
                        especialAtivoParede = true;
                    }

                    if (m[Cobra[0].x][Cobra[0].y] == 6) {
                        m[Cobra[0].x][Cobra[0].y] = 0;
                        pontuacao+=10;
                        especialColocadoCobra = false;
                        especialAtivoCobra = true;
                    }

                }; //fim do laco do jogo

                if(JogoComTimer==true || JogoEspecial==true){
                    salvarRankingDesafio(nome,pontuacao,tempoEmSegundos,movimentos,escolha);
                }

                if(CobraViva.vivo == false){
                    PlaySound(TEXT("morreu.wav"), NULL, SND_ASYNC); //som morte cobra
                }

                if(FaseJogo>1 && FaseJogo<4 && CobraViva.vivo == true){ ///Verificação pra passar de fase
                    system("cls");
                    cout<<"Voce passou de fase!"<<endl;
                    repetir=1;
                    system("pause");
                    system("cls");
                }

                if(FaseJogo==4){
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    salvarRanking(nome,pontuacao, tempoEmSegundos,dificuldade,movimentos);
                    FaseJogo=1;
                    cout<<nome<<" Voce fez: "<<pontuacao<<" pontos.";
                    cout<< endl << "Voce ganhou o jogo"<<endl;
                    cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                    cout<<"Professor: Alex Luciano"<<endl;
                    cout<<"Quer jogar novamente?"<<endl;
                    cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                    cin>>repetir;
                    system ("cls");
                }

                if (CobraViva.vivo == false && JogoComTimer == false && JogoEspecial == false) {
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    salvarRanking(nome,pontuacao, tempoEmSegundos,dificuldade,movimentos);
                    FaseJogo=1;
                    cout<<nome<<" Voce fez: "<<pontuacao<<" pontos.";
                    cout<< endl << "Voce perdeu o jogo"<<endl;
                    cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                    cout<<"Professor: Alex Luciano"<<endl;
                    cout<<"Quer jogar novamente?"<<endl;
                    cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                    cin>>repetir;
                    system ("cls");
                }

                if (CobraViva.vivo == false && JogoComTimer == true || CobraViva.vivo == false && JogoEspecial == true) {  ///ranking modo desafio
                    if(escolha==1 || escolha ==2 || escolha ==3){
                        salvarRankingDesafio(nome,pontuacao,tempoEmSegundos,movimentos,escolha);
                        system ("cls");
                        auto tempo = final - inicio;
                        int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                        cout<<nome<<" Voce fez: "<<pontuacao<<" pontos.";
                        cout<< endl << "Voce perdeu o jogo"<<endl;
                        cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                        cout<<"Professor: Alex Luciano"<<endl;
                        cout<<"Quer jogar novamente?"<<endl;
                        cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                        cin>>repetir;
                        system ("cls");
                    }
                }

                if (CobraViva.comeu == 100) {
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    salvarRanking(nome,pontuacao, tempoEmSegundos,dificuldade,movimentos);
                    cout<<nome<<" Voce fez: "<<pontuacao<<" pontos.";
                    cout<< endl << "Voce ganhou o jogo"<<endl;
                    cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                    cout<<"Professor: Alex Luciano"<<endl;
                    cout<<"Quer jogar novamente?"<<endl;
                    cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                    cin>>repetir;
                    system ("cls");
                }

                if (CobraViva.comeu == 100 || JogoEspecial==true && Cobra.size()==3) { //jogador ganha
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    if(JogoComTimer==true||JogoEspecial==true){
                        salvarRankingDesafio(nome,pontuacao,tempoEmSegundos,movimentos,escolha);
                    } else {
                        salvarRanking(nome,pontuacao, tempoEmSegundos,dificuldade,movimentos);
                    }
                    cout<<nome<<" Voce fez: "<<pontuacao<<" pontos.";
                    cout<< endl << "Voce ganhou o jogo"<<endl;
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
        case 2: ///Sobre o jogo
            system ("cls");
            cout<<endl<<endl<<endl<<endl;
            cout << "MOVIMENTO: Use W, A, S e D para mover a cobra que se move sempre para frente" << endl;
            cout << "MACAS: Mova-se em direcao as macas para come-las e crescer." << endl;
            cout << "EVITAR COLISOES: Evite colidir com a parede ou com o corpo da cobra." << endl;
            cout << "ITENS ESPECIAIS:" << endl;
            cout << "- ganhe pontos a mais" << endl;
            cout << "- passe atraves de paredes " << endl;
            cout << "- esbarre em seu corpo sem morrer" << endl;
            cout << "PONTUACAO POR DIFICULDADE" << endl;
            cout << "FACIL:" <<endl;
            cout << "A cada maca coletada o jogador recebe 10 pontos." << endl;
            cout << "MEDIO: " << endl;
            cout << "A cada maca coletada o jogador recebe 20 pontos"<<endl;
            cout << "DIFICIL:" << endl;
            cout << "A cada maca coletada o jogador recebe 30 pontos" << endl;
            cout << "MODO DESAFIO: " << endl;
            cout << "Jogo com tempo: faca o maximo de pontos em 3 minutos" << endl << endl;
            cout << "Jogo Especial: Voce começa com 100 de espaço e a cada maca seu corpo diminui, seu objetivo e chegar em 0" << endl << endl;
            cout << "BOA SORTE!" << endl << endl;
            system("pause");
            system ("cls");
            break;
        case 3: ///Acessar rank no menu
            system("cls");
            cout << "1-Rank" << endl;
            cout << "2- Rank modo desafio" << endl;
            int escolhaRank;
            cin >> escolhaRank;
            if(escolhaRank==1){
                exibirRanking();
                system("pause");
                main();
            }else if(escolhaRank==2){
                 exibirRankingDesafio();
                 system("pause");
                 main();
            }

        case 4: /// Modos Especiais
            system("cls");
            cout << "Escolha entre um dos modos especiais:" << endl << endl;
            cout << "Escolha uma opcao (1, 2, 3): " << endl << endl;
            cout << "1 - Jogo com Tempo: O jogador possui apenas 3 minutos para completar o jogo" << endl;
            cout << "2 - Jogo Especial: Voce começa com 100 de espaco e a cada maca seu corpo diminui, seu objetivo e chegar em 0" << endl;
            cout << "3 - Ativar IA: IA joga o jogo por voce" << endl;
            cout << "4 - sem modo especial" << endl;
            cin >> escolha;
            switch (escolha) {
            case 1:
                JogoComTimer = true;
                JogoEspecial = false;
                IAJogo = false;
                break;
            case 2:
                JogoEspecial = true;
                IAJogo = false;
                JogoComTimer = false;
                break;
            case 3:
                IAJogo = true;
                JogoComTimer = false;
                JogoEspecial = false;
                break;
            case 4:
                break;
            default:
                cout << "Opcao invalida." << endl;
                return 0;
            }
        break;
        case 5: ///Obrigado por jogar
            cout << endl << "Obrigado por jogar" << endl;
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
