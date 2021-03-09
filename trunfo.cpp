#include <iostream>
#include <vector>
#include <fstream> // trabalhar com arquivos
#include <ctime>
#include <string>
using namespace std;

struct Carta
{
    string id; // no futuro serah string
    string nome;
    int    velocidadeMaxima;
    int    cilindradas;
    double zeroCem;
    int    potencia;
    double comprimento;
    int    peso;
};

struct Jogador
{
    string nome;    
    vector<Carta> mao;
    int nJogadas = 0;
    bool bot = false;
};

struct ranking
{
    string nome;
    int nVitorias;
    int menorNumJogadas;
};


vector <Carta> baralho; // definiçao do vetor que vai armazenar todas as cartas
vector <Jogador> jogadores; //vetor para controlar cada jogador
vector <ranking> rankingLog;


void ImprimeBaralho()
{
    for (int i = 0; i < baralho.size(); i++)
    {
        cout << baralho[i].id << " - " << baralho[i].nome << " - " << baralho[i].velocidadeMaxima << " - " << baralho[i].cilindradas << " - " << baralho[i].zeroCem << " - " << baralho[i].potencia << " - " << baralho[i].comprimento << " - " << baralho[i].peso << endl;
    }
}

string ajustaEspaco(string palavra)
{
    for (int i = 0; i < palavra.size(); i++)
    {
        if (palavra[i] == '_')
            palavra[i] = ' ';
    }
    return palavra;
}

void LoadCartas()
{
    ifstream arquivo;

    arquivo.open("cartas.txt");

    if (arquivo.is_open())
    {
        cout << "Arquivo aberto para leitura\n";
        while (!arquivo.eof()) // enquanto nao for o final do arquivo
        {
            Carta temp;

            arquivo >> temp.id;
            arquivo >> temp.nome;
            arquivo >> temp.velocidadeMaxima;
            arquivo >> temp.cilindradas;
            arquivo >> temp.zeroCem;
            arquivo >> temp.potencia;
            arquivo >> temp.comprimento;
            arquivo >> temp.peso;

            temp.nome = ajustaEspaco(temp.nome); // troca '_' por ' '

            baralho.push_back(temp);

            //cout << temp.id << endl;
        }
        arquivo.close();

    }
    else
        cout << "Erro ao abrir arquivo\n";

    cout << baralho.size() << " cartas carregadas!\n";
}

void Embaralhar()
{

    //random_shuffle(baralho.begin(), baralho.end());
    //Trocar as cartas de posição de forma aletoria no mesmo vetor

    for (int i = 0; i < baralho.size(); i++)
    {
        int pos = rand() % baralho.size();

        Carta temp = baralho[i];
        baralho[i] = baralho[pos];
        baralho[pos] = temp;
    }

    //Trocar as cartas de posição de forma aletoria usando um vector temporario
   /* vector<Carta> temporario;

    while (baralho.size()>0) {

        int pos = rand() % baralho.size();
        temporario.push_back(baralho[pos]); // copia para o vector temporario
        baralho.erase(baralho.begin()+pos); // apaga o elemento copiado
    }

    baralho = temporario;*/
}

void Distribuir()
{

    int j = 0; //jogador atual

    for (int i = 0; i < baralho.size(); i++) // percorrer o baralho e dividir as cartas
    {
        jogadores[j].mao.push_back(baralho[i]);
        j++;

        if (j == jogadores.size())
            j = 0;
    }

}

void MostraStatus()
{

    for (int i = 0; i < jogadores.size(); i++)
        cout << "Num Cartas: " << jogadores[i].nome << ": " << jogadores[i].mao.size() << endl;
}

void ImprimeCartaPlayer(int v)
{
    cout << "=========== SUA CARTA: " << jogadores[v].mao[0].id << " - " << jogadores[v].mao[0].nome << " ===========" <<endl;
    cout << "Atributos: \n";
    cout << "1. Vel Maxima: " << jogadores[v].mao[0].velocidadeMaxima << endl;
    cout << "2. Cilindradas: " << jogadores[v].mao[0].cilindradas << endl;
    cout << "3. Zero a 100: " << jogadores[v].mao[0].zeroCem << endl;
    cout << "4. Potencia: " << jogadores[v].mao[0].potencia << endl;
    cout << "5. Comprimento: " << jogadores[v].mao[0].comprimento << endl;
    cout << "6. Peso: " << jogadores[v].mao[0].peso << endl;

}

void Jogada(int vez)
{
    int atr;
    bool empate = false;


    do 
    {
        if (empate)
        {
            cout << "Aconteceu um Empate! Jogue novamente" << endl;
            empate = false;
        }
    if (jogadores[vez].mao.size() > 0)
    {
        if (jogadores[vez].bot == true)
        {
            atr = rand() % 6;
            cout << "======== " << jogadores[vez].nome << " Esta jogando" << " ========" << endl;
            jogadores[vez].nJogadas++;
        }
        else
        {
            cout << "Jogador " << jogadores[vez].nome << ", informe o numero do atributo escolhido: ";
            cin >> atr;
            jogadores[vez].nJogadas++;
        }

        int maiorVel = 0;
        int maiorCil = 0;
        int maiorZC = 0;
        int maiorPot = 0;
        int maiorCom = 0;
        int maiorPeso = 0;
        int jVencedor = vez;

            switch (atr)
            {

            case 1:
                cout << "Atributo escolhido: VELOCIDADE\n";
                maiorVel = jogadores[vez].mao[0].velocidadeMaxima;

                for (int i = 0; i < jogadores.size(); i++)
                {
                    if (jogadores[i].mao.size() > 0)
                    {

                        cout << "Carta Jogador " << jogadores[i].nome << ": " << jogadores[i].mao[0].id << " - Vel: " << jogadores[i].mao[0].velocidadeMaxima << endl;
                        if (i != vez && jogadores[vez].mao.size() > 0) //não compara consigo mesmo e só compara se estiver vivo
                        {
                            if (jogadores[i].mao[0].velocidadeMaxima == maiorVel)
                            {
                                empate = true;
                            }
                            if (jogadores[i].mao[0].velocidadeMaxima > maiorVel)
                            {
                                maiorVel = jogadores[i].mao[0].velocidadeMaxima;
                                jVencedor = i;
                            }                         
                        }
                    }
                }
                if (!empate)
                {
                    cout << "Vencedor: Jogador " << jogadores[jVencedor].nome << endl;

                    for (int i = 0; i < jogadores.size(); i++)
                    {
                        if (jogadores[i].mao.size() > 0)
                        {
                            jogadores[jVencedor].mao.push_back(jogadores[i].mao[0]);
                            jogadores[i].mao.erase(jogadores[i].mao.begin()); // apaga a posicao zero
                        }
                    }
                }
                break;

            case 2:
                cout << "Atributo escolhido: CILINDRADAS" << endl;
                maiorCil = jogadores[vez].mao[0].cilindradas;

                for (int i = 0; i < jogadores.size(); i++)
                {
                    if (jogadores[i].mao.size() > 0)
                    {

                        cout << "Carta Jogador " << jogadores[i].nome << ": " << jogadores[i].mao[0].id << " - Cil: " << jogadores[i].mao[0].cilindradas << endl;

                        if (i != vez && jogadores[vez].mao.size() > 0) //não compara consigo mesmo e só compara se estiver vivo) //não compara consigo mesmo
                        {
                            if (jogadores[i].mao[0].cilindradas == maiorCil)
                            {
                                empate = true;
                            }
                            if (jogadores[i].mao[0].cilindradas > maiorCil)
                            {
                                maiorCil = jogadores[i].mao[0].cilindradas;
                                jVencedor = i;
                            }
                         
                        }
                    }
                }
                if (!empate)
                {
                    cout << "Vencedor: Jogador " << jogadores[jVencedor].nome << endl;

                    for (int i = 0; i < jogadores.size(); i++)
                    {
                        if (jogadores[i].mao.size() > 0)
                        {
                            jogadores[jVencedor].mao.push_back(jogadores[i].mao[0]);
                            jogadores[i].mao.erase(jogadores[i].mao.begin()); // apaga a posicao zero
                        }
                    }
                }
                break;
            case 3:
                cout << "Atributo escolhido: ZERO A 100" << endl;
                maiorZC = jogadores[vez].mao[0].zeroCem;

                for (int i = 0; i < jogadores.size(); i++)
                {
                    if (jogadores[i].mao.size() > 0)
                    {
                        cout << "Carta Jogador " << jogadores[i].nome << ": " << jogadores[i].mao[0].id << " - Zero a Cem: " << jogadores[i].mao[0].zeroCem << endl;

                        if (i != vez && jogadores[vez].mao.size() > 0) //não compara consigo mesmo e só compara se estiver vivo) //não compara consigo mesmo
                        {
                            if (jogadores[i].mao[0].zeroCem == maiorZC)
                            {
                                empate = true;
                            }
                            if (jogadores[i].mao[0].zeroCem > maiorZC)
                            {
                                maiorCil = jogadores[i].mao[0].zeroCem;
                                jVencedor = i;
                            }
                          
                        }
                    }
                }
                if (!empate)
                {
                    cout << "Vencedor: Jogador " << jogadores[jVencedor].nome << endl;

                    for (int i = 0; i < jogadores.size(); i++)
                    {
                        if (jogadores[i].mao.size() > 0)
                        {
                            jogadores[jVencedor].mao.push_back(jogadores[i].mao[0]);
                            jogadores[i].mao.erase(jogadores[i].mao.begin()); // apaga a posicao zero
                        }
                    }
                }
                break;

            case 4:
                cout << "Atributo escolhido: POTENCIA" << endl;

                maiorPot = jogadores[vez].mao[0].potencia;

                for (int i = 0; i < jogadores.size(); i++)
                {
                    if (jogadores[i].mao.size() > 0)
                    {
                        cout << "Carta Jogador " << jogadores[i].nome << ": " << jogadores[i].mao[0].id << " - Potencia: " << jogadores[i].mao[0].potencia << endl;

                        if (i != vez && jogadores[vez].mao.size() > 0) //não compara consigo mesmo e só compara se estiver vivo) //não compara consigo mesmo
                        {
                            if (jogadores[i].mao[0].potencia == maiorPot)
                            {
                                empate = true;
                            }
                            if (jogadores[i].mao[0].potencia > maiorPot)
                            {
                                maiorPot = jogadores[i].mao[0].potencia;
                                jVencedor = i;
                            }
                         
                        }
                    }
                }
                if (!empate)
                {
                    cout << "Vencedor: Jogador " << jogadores[jVencedor].nome << endl;

                    for (int i = 0; i < jogadores.size(); i++)
                    {
                        if (jogadores[i].mao.size() > 0)
                        {
                            jogadores[jVencedor].mao.push_back(jogadores[i].mao[0]);
                            jogadores[i].mao.erase(jogadores[i].mao.begin()); // apaga a posicao zero
                        }
                    }
                }
                break;

            case 5:
                cout << "Atributo escolhido: COMPRIMENTO" << endl;

                maiorCom = jogadores[vez].mao[0].comprimento;

                for (int i = 0; i < jogadores.size(); i++)
                {
                    if (jogadores[i].mao.size() > 0)
                    {
                        cout << "Carta Jogador " << jogadores[i].nome << ": " << jogadores[i].mao[0].id << " - Comprimento: " << jogadores[i].mao[0].comprimento << endl;

                        if (i != vez && jogadores[vez].mao.size() > 0) //não compara consigo mesmo e só compara se estiver vivo) //não compara consigo mesmo
                        {
                            if (jogadores[i].mao[0].comprimento == maiorCom)
                            {
                                empate = true;
                            }
                            if (jogadores[i].mao[0].comprimento > maiorCom)
                            {
                                maiorCom = jogadores[i].mao[0].comprimento;
                                jVencedor = i;
                            }
                        
                        }
                    }
                }
                if (!empate)
                {
                    cout << "Vencedor: Jogador " << jogadores[jVencedor].nome << endl;

                    for (int i = 0; i < jogadores.size(); i++)
                    {
                        if (jogadores[i].mao.size() > 0)
                        {
                            jogadores[jVencedor].mao.push_back(jogadores[i].mao[0]);
                            jogadores[i].mao.erase(jogadores[i].mao.begin()); // apaga a posicao zero
                        }
                    }
                }
                break;

            case 6:
                cout << "Atributo escolhido: PESO" << endl;

                maiorPeso = jogadores[vez].mao[0].peso;

                for (int i = 0; i < jogadores.size(); i++)
                {
                    if (jogadores[i].mao.size() > 0)
                    {
                        cout << "Carta Jogador " << jogadores[i].nome << ": " << jogadores[i].mao[0].id << " - Peso: " << jogadores[i].mao[0].peso << endl;

                        if (i != vez && jogadores[vez].mao.size() > 0) //não compara consigo mesmo e só compara se estiver vivo) //não compara consigo mesmo
                        {
                            if (jogadores[i].mao[0].peso == maiorPeso)
                            {
                                empate = true;
                            }
                            if (jogadores[i].mao[0].peso > maiorPeso)
                            {
                                maiorPeso = jogadores[i].mao[0].peso;
                                jVencedor = i;
                            }                       
                        }
                    }
                }
                if (!empate)
                {
                    cout << "Vencedor: Jogador " << jogadores[jVencedor].nome << endl;

                    for (int i = 0; i < jogadores.size(); i++)
                    {
                        if (jogadores[i].mao.size() > 0)
                        {
                            jogadores[jVencedor].mao.push_back(jogadores[i].mao[0]);
                            jogadores[i].mao.erase(jogadores[i].mao.begin()); // apaga a posicao zero
                        }
                    }
                }
                break;
            }
        }
    else
    {
        cout << "===== Jogador " << jogadores[vez].nome << " esta eliminado eliminado =========" << endl;

    }
    }while (empate);
}

void ImprimeMaos()
{
    for (int i = 0; i < jogadores.size(); i++)
    {
        cout << "======= CARTAS DO JOGADOR " << i << "=========\n";
        cout << jogadores[i].mao.size() << "\n";

       

        for (int j = 0; j < jogadores[i].mao.size(); j++)
        {
            cout << jogadores[i].mao[j].id << " - " << jogadores[i].mao[j].nome << " - " << jogadores[i].mao[j].velocidadeMaxima << " - " << jogadores[i].mao[j].cilindradas << " - " << jogadores[i].mao[j].zeroCem << " - " << jogadores[i].mao[j].potencia << " - " << jogadores[i].mao[j].comprimento << " - " << jogadores[i].mao[j].peso << endl;
        }
        
    }
}

void LoadRanking()
{

    rankingLog.clear();

    ifstream arquivo;

    arquivo.open("ranking.txt");

    if (arquivo.is_open())
    {   
        cout << "Arquivo aberto para leitura\n";
        while (!arquivo.eof()) // enquanto nao for o final do arquivo
        {
            ranking temp;
            arquivo >> temp.nome;            
            arquivo >> temp.nVitorias;
            arquivo >> temp.menorNumJogadas;
            rankingLog.push_back(temp);      
        }
     arquivo.close();
    }      
   
}

void RegistraRanking(int vez)
{
    bool existe = false;

    for (int i = 0; i < rankingLog.size(); i++)
    {
        if (rankingLog[i].nome == jogadores[vez].nome)
        {
            rankingLog[i].nVitorias++;
            if (jogadores[vez].nJogadas < rankingLog[i].menorNumJogadas)
                rankingLog[i].menorNumJogadas = jogadores[vez].nJogadas;
            existe = true;
        }    
    }
    if (!existe) {
        ranking temp;
        temp.nome = jogadores[vez].nome;
        temp.nVitorias = 1;
        temp.menorNumJogadas = jogadores[vez].nJogadas;
        rankingLog.push_back(temp);
    }
    ifstream arquivo;
    arquivo.open("ranking.txt");
    ofstream rankingTemp;
    rankingTemp.open("temp.txt");
    
    if (arquivo.is_open())
    {
        cout << "Arquivo aberto para escritura\n";

        for (int i = 0; i < rankingLog.size(); i++)
        {
            
            rankingTemp << " " << rankingLog[i].nome << " ";
            rankingTemp << rankingLog[i].nVitorias << " ";
            rankingTemp << rankingLog[i].menorNumJogadas;
            
        }
        arquivo.close();
    }
    else
    {
        cout << "erro ao abrir o arquivo";
    }
            
    rankingTemp.close();
    arquivo.close();
    remove("ranking.txt");
    rename("temp.txt", "ranking.txt");
        
    
}

void ImprimeRanking()
{
    for (int i = 0; i < rankingLog.size(); i++)
    {
        cout <<"nome: " << rankingLog[i].nome << " ";
        cout << "vitorias: " << rankingLog[i].nVitorias << " ";
        cout << "vitoria com menor numero de jogadas: " << rankingLog[i].menorNumJogadas << " ";
        cout << endl;
    }
}





void GamePlay(int numJogadores)
{
    // O player da vez sempre visualiza a sua primeira carta
    // O player da vez escolhe o atributo para comparar
    // Os valores sao comparados
    // O jogador com maior valor do atributo leva as cartas dos coleguinhas
    // As cartas que foram embora são "removidas" da mão do coleguinha e adicionadas na mão do player da vez

    //TODO:
    // Empate: Nova pergunta com as mesmas cartas
    // Jogadores com zero cartas devem ser eliminados
    // O jogo acaba quando um dos jogadores estiver com todas as cartas

    bool isRunning = true;
    int  vez = 0;
    
           
        while (isRunning)
        {
            if (jogadores[vez].bot == false && jogadores[vez].mao.size() > 0)
                ImprimeCartaPlayer(vez);            
            Jogada(vez);
            if (jogadores[vez].mao.size() > 0)
                MostraStatus();
            vez++;
            if (vez == jogadores.size())
            {
                vez = 0;
            }
            if (jogadores[vez].mao.size() >= 32)
            {
                cout << "================= " << jogadores[vez].nome << "VENCEU!!!!";
                isRunning = false;
                RegistraRanking(vez);
            }
            
        }
    

    //fimDeJogo

}

int main()
{
    srand(time(0)); // numeros pseudo-aleatorios

    //TODO: Menu
    //
    // perguntar numeros de jogadores... humanos ou bots?
    // Salvar o nome dos jogadores, criar nomes para bots (atualizar struct jogador)
    // implementar jogabilidade completa
    // ranking -> jogador e numero de jogadas.... o jogador que vence mais rapido

    int numJogadores;
    int numBots;
    int k = 1;
    int menu;
    

    
        do {
            
            cout << "opcao 1: jogar" << endl << "opcao 2: ranking" << endl << "opcao 3: sair" << endl;
            cin >> menu;
            switch (menu)
            {
            case 1:



                do
                {
                    cout << "A quantiade de jogadores e bots nao deve passar de 8 " << endl;
                    cout << "informe a quantidade de jogadores humanos: ";
                    cin >> numJogadores;
                    cout << "informe a quantidade de bots: ";
                    cin >> numBots;
                } while (numJogadores + numBots > 8);

                jogadores.resize(numJogadores + numBots); // Definir o numero de jogadores;

                for (int j = 0; j < numJogadores; j++)
                {
                    cout << "informe o nome do jogador: " << endl;
                    cin >> jogadores[j].nome;
                }
                if (numBots != 0)
                {
                    for (int j = numJogadores; j < numJogadores + numBots; j++)
                    {

                        jogadores[j].bot = true;
                        jogadores[j].nome = "bot" + to_string(k);
                        k++;

                    }
                }
                k = 0;

                LoadCartas();
                Embaralhar();
                Distribuir();



                GamePlay(numJogadores);
                

                break;

            case 2:
                LoadRanking();
                ImprimeRanking();
                break;
            default:
                break;
            }
        } 
        while(menu != 3);
}

    // ImprimeBaralho();