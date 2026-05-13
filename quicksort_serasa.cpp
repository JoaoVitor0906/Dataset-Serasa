#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Registro {
    int id;
    string nome;
    string cpf;
    string email;
    string telefone;
    string dataNascimento;
    int renda;
    int scoreCrediticio;
    int contasPendentes;
    int diasAtraso;
    double montantaDivida;
    string status;
};

class QuickSortHoare {
private:
    long long comparacoes = 0;
    long long trocas = 0;

    int particionamentoHoare(vector<Registro>& registros, int esquerda, int direita) {
        int pivo = registros[esquerda].scoreCrediticio;
        int i = esquerda - 1;
        int j = direita + 1;

        while (true) {
            do {
                i++;
                comparacoes++;
            } while (registros[i].scoreCrediticio < pivo);

            do {
                j--;
                comparacoes++;
            } while (registros[j].scoreCrediticio > pivo);

            if (i >= j) {
                return j;
            }

            swap(registros[i], registros[j]);
            trocas++;
        }
    }

    void quickSortRecursivo(vector<Registro>& registros, int esquerda, int direita) {
        if (esquerda < direita) {
            int pi = particionamentoHoare(registros, esquerda, direita);

            quickSortRecursivo(registros, esquerda, pi);
            quickSortRecursivo(registros, pi + 1, direita);
        }
    }

public:
    void ordenar(vector<Registro>& registros) {
        if (!registros.empty()) {
            comparacoes = 0;
            trocas = 0;
            quickSortRecursivo(registros, 0, registros.size() - 1);
        }
    }

    long long getComparacoes() const {
        return comparacoes;
    }

    long long getTrocas() const {
        return trocas;
    }
};

bool carregarDataset(const string& nomeArquivo, vector<Registro>& registros) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro: Não foi possível abrir o arquivo " << nomeArquivo << endl;
        return false;
    }

    string linha;
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string campo;

        Registro reg;

        getline(ss, campo, ',');
        reg.id = stoi(campo);

        getline(ss, reg.nome, ',');
        getline(ss, reg.cpf, ',');
        getline(ss, reg.email, ',');
        getline(ss, reg.telefone, ',');
        getline(ss, reg.dataNascimento, ',');

        getline(ss, campo, ',');
        reg.renda = stoi(campo);

        getline(ss, campo, ',');
        reg.scoreCrediticio = stoi(campo);

        getline(ss, campo, ',');
        reg.contasPendentes = stoi(campo);

        getline(ss, campo, ',');
        reg.diasAtraso = stoi(campo);

        getline(ss, campo, ',');
        reg.montantaDivida = stod(campo);

        getline(ss, reg.status, '\n');

        registros.push_back(reg);
    }

    arquivo.close();
    return true;
}

void exibirEstatisticas(const vector<Registro>& registros, long long comparacoes, long long trocas, double tempoMs) {
    cout << "\n=== ESTATÍSTICAS DA ORDENAÇÃO ===" << endl;
    cout << "Total de registros: " << registros.size() << endl;
    cout << "Comparações realizadas: " << comparacoes << endl;
    cout << "Trocas realizadas: " << trocas << endl;
    cout << "Tempo total: " << fixed << setprecision(4) << tempoMs << " ms" << endl;
    cout << "Tempo por registro: " << fixed << setprecision(6) << (tempoMs / registros.size()) << " ms" << endl;
}

void exibirAmostra(const vector<Registro>& registros, int quantidade = 5) {
    cout << "\n=== AMOSTRA DOS DADOS ORDENADOS ===" << endl;
    cout << left << setw(6) << "ID" << setw(20) << "Nome" << setw(15) << "Score" << setw(15) << "Status" << endl;
    cout << string(56, '-') << endl;

    int fim = min(quantidade, (int)registros.size());
    for (int i = 0; i < fim; i++) {
        cout << left << setw(6) << registros[i].id
             << setw(20) << registros[i].nome.substr(0, 19)
             << setw(15) << registros[i].scoreCrediticio
             << setw(15) << registros[i].status << endl;
    }

    cout << "\n... (últimos 5 registros) ..." << endl;
    int inicio = max(0, (int)registros.size() - 5);
    for (int i = inicio; i < (int)registros.size(); i++) {
        cout << left << setw(6) << registros[i].id
             << setw(20) << registros[i].nome.substr(0, 19)
             << setw(15) << registros[i].scoreCrediticio
             << setw(15) << registros[i].status << endl;
    }
}

int main() {
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  QUICK SORT - MÉTODO DE HOARE - DATASET SERASA           ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;

    vector<Registro> registros;

    cout << "\nCarregando dataset..." << endl;
    if (!carregarDataset("serasa_dataset.csv", registros)) {
        cerr << "Falha ao carregar o dataset. Verifique se 'serasa_dataset.csv' existe." << endl;
        cout << "\nPrimeiro, execute 'serasa_dataset_generator.cpp' para gerar o dataset." << endl;
        return 1;
    }

    cout << "✓ Dataset carregado com sucesso!" << endl;
    cout << "  Total de registros: " << registros.size() << endl;

    cout << "\nExecutando Quick Sort com particionamento de Hoare..." << endl;

    QuickSortHoare sorter;

    auto inicio = chrono::high_resolution_clock::now();
    sorter.ordenar(registros);
    auto fim = chrono::high_resolution_clock::now();

    double tempoMs = chrono::duration<double, milli>(fim - inicio).count();

    cout << "✓ Ordenação concluída!" << endl;

    exibirEstatisticas(registros, sorter.getComparacoes(), sorter.getTrocas(), tempoMs);
    exibirAmostra(registros);

    cout << "\n✓ Processo finalizado com sucesso!" << endl;

    system("pause");
    return 0;
}
