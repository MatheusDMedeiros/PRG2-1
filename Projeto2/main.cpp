#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <list>
#include <time.h>

using namespace std;

struct Passageiro
{
    string nome;
    string sobrenome;
    string nomeCompleto;
    int nAssento;
};

struct Viagem
{
    string nomeMotorista;
    string horaSaida;
    string horaChegada;
    string origem;
    string destino;
    unordered_map<int, Passageiro> passageiros;
    unordered_map<int, bool> lugares;
};

unordered_map<int, Viagem> viagens;

string transformaParaMinusculas(string p) {
    string p1;
    int i = 0;
    char c;
    while(p[i]) {
        c = p[i];
        p1[i] = putchar(tolower(c));
        i++;
    }
    return p1;
}

float criaIdPassageiro()
{
    return (random() % 100) + 1;
}

float criaIdViagem()
{
    return (random() % 10000) + 4000;
}

unordered_map<int, bool> criaLugares(unordered_map<int, bool> &lugares)
{
    int lug = 0;
    while (lug < 43)
    {
        lugares[lug] = true;
        lug++;
    }

    return lugares;
}

string criaNomeCompleto(string nome, string sobrenome)
{
    string nomeCompleto = nome + " " + sobrenome;
    return nomeCompleto;
}

void mostrarViagens(Viagem bus)
{
    cout << "Partindo de " << bus.origem << " com destino " << bus.destino << " sai às " << bus.horaSaida << " e chega " << bus.horaChegada << endl;
}

void mostrarPassageiro(unordered_map<int, Passageiro> &passageiros, int id_passageiro)
{
    for (auto &p : passageiros)
    {
        if (p.first == id_passageiro)
        {
            auto po = p.second;
            cout << "ID: " << p.first << endl;
            cout << "Nome completo: " << po.nomeCompleto << endl;
            cout << "N° do assento: " << po.nAssento << endl;
        }
    }
}

void mostrarPassageiros(Passageiro passageiro)
{
    cout << passageiro.nomeCompleto << " ";
}

void mostrarAssentos(unordered_map<int, Passageiro> &passageiros)
{
    for (auto &par : passageiros)
    {
        mostrarPassageiros(par.second);
        cout << endl;
    }
}

void mostrarLugares(unordered_map<int, bool> &lugares, unordered_map<int, Passageiro> &passageiros)
{
    for (auto &par : lugares)
    {
        if (!par.second)
        {
            cout << par.first << ". ";
            mostrarAssentos(passageiros);
        }
        else
        {
            cout << par.first << ". LIVRE" << endl;
        }
    }
}

void criarViagens()
{
    Viagem bus;
    fstream arq("data/viagens1.txt");
    string linha;

    while (getline(arq, linha))
    {
        int pos = 0, pos1;
        pos1 = linha.find(",");
        bus.nomeMotorista = linha.substr(pos, pos1);
        pos = pos1 + 1;
        pos1 = linha.find(",", pos);
        bus.origem = linha.substr(pos, (pos1 - pos));
        pos = pos1 + 1;
        pos1 = linha.find(",", pos);
        bus.destino = linha.substr(pos, (pos1 - pos));
        pos = pos1 + 1;
        pos1 = linha.find(",", pos);
        bus.horaSaida = linha.substr(pos, (pos1 - pos));
        pos = pos1 + 1;
        pos1 = linha.find(",", pos);
        bus.horaChegada = linha.substr(pos, (pos1 - pos));
        criaLugares(bus.lugares);

        viagens[criaIdViagem()] = bus;
    }

    for (auto &par : viagens)
    {
        cout << "Ônibus de número " << par.first << ": ";
        mostrarViagens(par.second);
        cout << endl;
    }
}

void reservar()
{
    Passageiro viajante;
    Viagem *trecho;
    int lugar;
    float nOnibus;

    cout << "Digite o número do ônibus que realizará sua viagem: ";
    cin >> nOnibus;

    for (auto &viagem : viagens)
    {
        if (nOnibus == viagem.first)
        {
            trecho = &viagem.second;
            cout << "Escolha seu assento de 0 a 42: ";
            cin >> lugar;

            if (lugar >= 42)
            {
                cout << "Nossos ônibus possuem apenas 43 lugares, favor escolher uma poltrona de 0 a 42" << endl;
            }
            else
            {
                if (trecho->lugares[lugar])
                {
                    viajante.nAssento = lugar;
                    trecho->lugares[lugar] = false;
                    cout << "Certo, agora preciso do seu nome e sobrenome para reservar seu assento na viagem." << endl;
                    cout << "Nome: ";
                    cin >> viajante.nome;
                    cout << "Sobrenome: ";
                    cin >> viajante.sobrenome;
                    viajante.nomeCompleto = criaNomeCompleto(viajante.nome, viajante.sobrenome);
                    int id_passageiro = criaIdPassageiro();
                    trecho->passageiros[id_passageiro] = viajante;
                    cout << "Seu ID é: " << id_passageiro << ". Salve-o para consultar sua reserva quando quiser." << endl;
                }
                else
                {
                    cout << "Esse lugar já está ocupado ou está indisponível nessa viagem." << endl;
                }
            }
        }
    }
    // cout << "Não encontrei a viagem com ônibus que possua o número " << nOnibus << ". Você pode consultar o número dos ônibus selecionando a opção 4: Viagens disponíveis." << endl;
}

void infoViagem()
{
    Viagem trecho;
    float nOnibus;

    cout << "Digite o número do ônibus que realizará sua viagem: ";
    cin >> nOnibus;

    for (auto &viagem : viagens)
    {
        if (nOnibus == viagem.first)
        {
            trecho = viagem.second;
            break;
        }
    }

    cout << endl;
    mostrarViagens(trecho);
    cout << endl;
    mostrarLugares(trecho.lugares, trecho.passageiros);

    // cout << "Não encontrei a viagem com ônibus que possua o número " << nOnibus << ". Você pode consultar o número dos ônibus selecionando a opção 4: Viagens disponíveis." << endl;
}

void infoReserva()
{

    Viagem trecho;
    int idPassageiro;
    float nOnibus;

    cout << "Digite o número do ônibus que realizará sua viagem: ";
    cin >> nOnibus;
    cout << "Digite o seu ID de passageiro: ";
    cin >> idPassageiro;

    for (auto &viagem : viagens)
    {
        if (nOnibus == viagem.first)
        {
            trecho = viagem.second;
            break;
        }
    }

    mostrarPassageiro(trecho.passageiros, idPassageiro);
}

void viagensDisponiveis()
{

    cout << "Mostrando viagens disponíveis.." << endl;

    for (auto &par : viagens)
    {
        cout << "Ônibus de número " << par.first << ": ";
        mostrarViagens(par.second);
        cout << endl;
    }
}

void buscarViagensOrigem() {

    string cidOrigem;
    list<Viagem> trechos;

    cout << "Digite a cidade de origem que você deseja consultar as viagens disponíveis: ";
    cin >> cidOrigem;
    // getline(cin,cidOrigem);

    for(auto &par: viagens) {

        if(cidOrigem == par.second.origem) {
            trechos.push_back(par.second);
        }
    }

    for(auto &l: trechos) {
        mostrarViagens(l);
    }
}

void buscarViagensDestino() {

    string cidDestino;
    list<Viagem> trechos;

    cout << "Digite a cidade de destino que você deseja consultar as viagens disponíveis: ";
    cin >> cidDestino;
    // getline(cin,cidDestino);

    for(auto &par: viagens) {
        if(cidDestino == par.second.destino) {
            trechos.push_back(par.second);
        }
    }

    for(auto &l: trechos) {
        mostrarViagens(l);
    }
}

void menu()
{
    while (true)
    {
        int escolha;
        cout << " \t\t\t 1. Reservar assento\n\t\t\t 2. Informações de viagem\n\t\t\t 3. Viagens disponíveis\n\t\t\t 4. Informações da sua reserva\n\t\t\t 5. Buscar viagens pela origem\n\t\t\t 6. Buscar viagens pelo destino\n\t\t\t 7. Sair\n\t\t\t" << endl;
        cout << "Escolha uma opção:\n>> ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            reservar();
            break;
        case 2:
            infoViagem();
            break;
        case 3:
            viagensDisponiveis();
            break;
        case 4:
            infoReserva();
            break;
        case 5:
            buscarViagensOrigem();
            break;
        case 6:
            buscarViagensDestino();
            break;
        case 7:
            break;
        default:
            cout << "Você não escolheu nenhuma das opções listadas" << endl;
            break;
        }
    }
}

int main()
{
    cout << transformaParaMinusculas("GaBRiEl") << endl;
    criarViagens();
    menu();
    return 0;
}