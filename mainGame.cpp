//*******************************************/
// DEVELOPER: GILVAN L. ABREU               *
// PROJETO DESENVOLVIDO PURAMENTE           *
// COM O OBJETIVO DE COLOCAR O COMHECIMENTO *
// EM PRÁTICA E ME DESAFIAR CADA VEZ MAIS.  *
//*******************************************/

#include<iostream>
#include<clocale>
#include<cstdlib>
#include<time.h>
#include<limits>
#include<cmath> 
#include<iomanip>
#include<fstream>

using namespace std;

#define VERMELHO     "\x1b[31m"
#define VERDE        "\x1b[32m"
#define AZUL         "\x1b[34m"
#define RESET        "\x1b[0m"

enum { JOGAR = 1, SCORE, SAIR };
enum { FACIL = 20, MEDIO = 50, DIFICIL = 100 };

void mainGame();
void jogo();
void atualizarScore();
int numeroAleatorio();
void dica2();
void dica3();

int objetivo;
int dificuldade;
int melhorScore;

int main() {
    setlocale(LC_ALL, "portuguese");
    atualizarScore();
    mainGame();
    return 0;
}

void atualizarScore() {
    int* const ptr2 = &melhorScore;
    ifstream fin;
    fin.open("score.bin",ios_base::in|ios_base::binary);
    if (fin.is_open()) {
        fin.read((char*)&melhorScore, sizeof(melhorScore));
        fin.close();
    }
    if(!fin.good())
        *ptr2 = 0;
    fin.close();
}

void newScore() {
    ofstream fout;
    fout.open("score.bin", ios_base::out | ios_base::binary);
    if (fout.is_open()) {
        fout.write((char*)&melhorScore, sizeof(melhorScore));
        fout.close();
    }
    else
        fout.close();
}

void mainGame() {
    int escolha;
    while (true) {
    cout << "**********************************************" << endl;
    cout << "*                 MENU                       *" << endl;
    cout << "* #######  1- JOGAR   ###########            *" << endl;
    cout << "* #######  2- EXIBIR SCORE  #####            *" << endl;
    cout << "* #######  3- SAIR    ###########            *" << endl;
    cout << "* ESCOLHA [ ]\b\b";
    cin >> escolha;
        system("cls");
        switch (escolha) {
            case JOGAR:
            {
                int escolhaDificuldade;
                int* const difi = &dificuldade;
                cout << "SELECIONE O NIVEL DE DIFICULDADE :" << endl;
                cout << "1-FACIL\n2-MEDIO\n3-DIFICIL" << endl;
                cout << "ESCOLHA [ ]\b\b"; 
                cin >> escolhaDificuldade;
                switch (escolhaDificuldade) {
                    case 1:
                     {
                         *difi = FACIL;
                         system("cls");
                         jogo();
                         break;
                     }
                    case 2:
                     {
                         *difi = MEDIO;
                         system("cls");
                         jogo();
                         break;
                     }
                    case 3: 
                     {
                         *difi = DIFICIL;
                         system("cls");
                         jogo();
                         break;
                     }
                    default:
                         continue;
                    }
            break;
            }
            case SCORE:
            {
                system("cls");
                cout << "********************************************"<< endl;
                cout << "*  SEU MAIOR SCORE É DE " << melhorScore;
                cout << "                  *" << endl;
                cout << "*  CONTINUE JOGANDO NO NIVEL HARD E EVOLUA *"<< endl;
                cout << "*  CADA VEZ MAIS.                          *"<< endl;
                cout << "********************************************"<< endl;
                system("pause");
                break;
            }
            case SAIR:
            {
                exit(NULL);
                break;
            }
            default:
                continue;
        }
    }
}

void jogo() {
    int num1, num2, num3;
    int score = 0;
    int* const ptr_score = &melhorScore;
    bool desejo = true;
    while (desejo) {
        objetivo = numeroAleatorio();
        cout << VERMELHO <<"melhor score: "<< melhorScore << setw(10) << VERDE << "score atual: " << score << endl;
        cout << AZUL << "------JOGO DA ADIVINHAÇÃO-------" << endl;
        cout << "NUMEROS DE 0 A "<< dificuldade << endl;
        cout << "DICA 1: " << endl;
        if (objetivo % 2 == 0) {
            cout << "SOU UM NÚMERO PAR" << endl;
        }
        else {
            cout << "SOU UM NÚMERO IMPAR" << endl;
        }
        cout<< "NÚMERO: [ ]\b\b";
        while (!(cin >> num1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        if (num1 == objetivo) {
            cout << VERDE << "VOCÊ GANHOU !!" << endl;
            score++;
            if (num1 == objetivo) {
                cout << "DESEJA CONTINUAR JOGANDO?\n";
                cout << "DIGITE 1 PARA SIM E 0 PARA NÃO" << endl;
                while (!(cin >> desejo)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (desejo) continue;
                else {
                    if (score > melhorScore) {
                        *ptr_score = score;
                        newScore();
                        cout << RESET << endl;
                        break;
                    }
                }
            }
        }
        else if (num1 != objetivo) {
            cout << "ERRO TENTE NOVAMENTE:\n";
            cout << "DICA 2:" << endl;
        }
        dica2();
        cout << "NÚMERO: [ ]\b\b";
        while (!(cin >> num2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (num2 == objetivo) {
            cout << VERDE << "VOCÊ GANHOU !!" << endl;
            score++;
            if (num2 == objetivo) {
                cout << "DESEJA CONTINUAR JOGANDO?\n";
                cout << "DIGITE 1 PARA SIM E 0 PARA NÃO" << endl;
                while (!(cin >> desejo)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (desejo) continue;
                else {
                    if (score > melhorScore) {
                        *ptr_score = score;
                        newScore();
                        cout << RESET << endl;
                        break;
                    }
                }
            }
        }
        else if (num2 != objetivo) {
            cout << "VOCÊ ERROU" << endl;
            cout << "DICA 3:" << endl;
            dica3();
            cout << "NÚMERO: [ ]\b\b";
            while (!(cin >> num3)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (num3 == objetivo) {
            cout << VERDE << "VOCÊ GANHOU !!" << endl;
            score++;
            if (num3 == objetivo) {
                cout << "DESEJA CONTINUAR JOGANDO?\n";
                cout << "DIGITE 1 PARA SIM E 0 PARA NÃO" << endl;
                while (!(cin >> desejo)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (desejo) continue;
                else {
                    if (score > melhorScore) {
                        *ptr_score = score;
                        newScore();
                        cout << RESET << endl;
                        break;
                    }
                }
            }
        }
        else if (num3 != objetivo) {
            cout << VERMELHO << "VOCÊ PERDEU !!" << endl;
            cout << "O NUMERO ERA: " << objetivo << endl;
            cout << "DESEJA CONTINUAR JOGANDO?\n";
            cout << "DIGITE 1 PARA SIM E 0 PARA NÃO" << endl;
            cin >> desejo;
            if(desejo)
                score = 0;
            if (!desejo) {
                if (score > melhorScore) {
                    *ptr_score = score;
                     newScore();
                }
            }
            cout << RESET << endl;
        }
    }   
}

int numeroAleatorio() {
    srand(time(NULL));
    int objetivo = (rand() % dificuldade+1);
    return objetivo;
}

void dica2() {
    int  raiz = sqrt(objetivo);
    float valorRaiz = raiz * raiz;

    if (valorRaiz == objetivo) {
        cout << "—————————————————————————————--" << endl;
        cout << "SOU UM NÚMERO COM RAIZ EXATA" << endl;
    }
    else if (valorRaiz != objetivo) {
        cout << "SOU UM NÚMERO SEM RAIZ EXATA" << endl;
    }
}

void dica3() {
    float numeroPi = objetivo * 3.14f;
    cout << "—————————————————————————————" << endl;
    cout << "QUANDO EU FOR MULTIPLICADO POR PI";
    cout << " MEU RESULTADO SERÁ: " << numeroPi << endl;
}
