#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Definição da estrutura para os bens
struct Bem {
    string nome;
    string categoria;
    string dataAquisicao;
    float peso;
    string enderecoAlocacao; // Apenas para imóveis
};

// Função para adicionar um bem ao arquivo
void adicionarBem(const Bem& bem) {
    ofstream arquivo("bens.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << bem.nome << " " << bem.categoria << " " << bem.dataAquisicao << " " << bem.peso;
        if (bem.categoria == "Imovel") {
            arquivo << " " << bem.enderecoAlocacao;
        }
        arquivo << endl;
        cout << "Bem adicionado com sucesso!" << endl;
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

// Função para listar todos os bens
void listarBens(const vector<Bem>& bens) {
    cout << "Lista de bens:" << endl;
    for (int i = 0; i < bens.size(); ++i)  {
    	const Bem& bem = bens[i];
        cout << "Nome: " << bem.nome << ", Categoria: " << bem.categoria << ", Data de aquisicao: " << bem.dataAquisicao << ", Peso: " << bem.peso;
        if (bem.categoria == "Imovel") {
            cout << ", Endereco de alocacao: " << bem.enderecoAlocacao;
        }
        cout << endl;
    }
}

// Função para ler os bens do arquivo
vector<Bem> lerBensDoArquivo() {
    vector<Bem> bens;
    ifstream arquivo("bens.txt");
    if (arquivo.is_open()) {
        while (!arquivo.eof()) {
            Bem bem;
            getline(arquivo, bem.nome);
            if (!arquivo.eof()) {
                arquivo >> bem.categoria >> bem.dataAquisicao >> bem.peso;
                arquivo.ignore();
                if (bem.categoria == "Imovel") {
                    getline(arquivo, bem.enderecoAlocacao);
                }
                bens.push_back(bem);
            }
        }
        arquivo.close();
    } else {
        cout << "Arquivo de bens nao encontrado." << endl;
    }
    return bens;
}

int main() {
    vector<Bem> bens = lerBensDoArquivo();

    int opcao;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Adicionar bem" << endl;
        cout << "2. Listar bens" << endl;
        cout << "3. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); // Limpar o buffer de entrada

        switch (opcao) {
            case 1: {
                Bem novoBem;
                cout << "Nome do bem: ";
                getline(cin, novoBem.nome);
                cout << "Categoria do bem: ";
                cin >> novoBem.categoria;
                cout << "Data de aquisicao do bem: ";
                cin >> novoBem.dataAquisicao;
                cout << "Peso do bem: ";
                cin >> novoBem.peso;

                if (novoBem.categoria == "Imovel") {
                    cin.ignore(); // Limpar o buffer de entrada
                    cout << "Endereco de alocacao: ";
                    getline(cin, novoBem.enderecoAlocacao);
                }

                adicionarBem(novoBem);
                bens.push_back(novoBem);
                break;
            }
            case 2:
                listarBens(bens);
                break;
            case 3:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    } while (opcao != 3);

    return 0;
}

