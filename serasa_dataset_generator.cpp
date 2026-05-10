#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

// 巴西常见姓名数据
vector<string> firstNames = {
    "João", "Maria", "José", "Ana", "Carlos", "Paulo", "Francisco", "Antônio",
    "Marcos", "Pedro", "Lucas", "Felipe", "André", "Rafael", "Gustavo", "Bruno",
    "Isabella", "Juliana", "Fernanda", "Gabriela", "Beatriz", "Camila", "Patricia",
    "Mariana", "Larissa", "Amanda", "Carolina", "Vanessa", "Thais", "Monica"
};

vector<string> lastNames = {
    "Silva", "Santos", "Oliveira", "Souza", "Costa", "Ferreira", "Rodrigues",
    "Martins", "Gomes", "Alves", "Rocha", "Carvalho", "Ribeiro", "Pereira",
    "Teixeira", "Barbosa", "Monteiro", "Machado", "Dias", "Gonçalves", "Medeiros",
    "Tavares", "Moreira", "Neves", "Cavalcante", "Aguiar", "Pinto", "Mendes",
    "Lopes", "Campos", "Araújo", "Vieira", "Borges", "Nascimento"
};

// 生成有效的巴西CPF号码
string generateCPF() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    
    string cpf = "";
    
    // 生成前9位
    for (int i = 0; i < 9; i++) {
        cpf += to_string(dis(gen));
    }
    
    // 计算第一个校验位
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += (cpf[i] - '0') * (10 - i);
    }
    int remainder = sum % 11;
    int digit1 = (remainder < 2) ? 0 : 11 - remainder;
    cpf += to_string(digit1);
    
    // 计算第二个校验位
    sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += (cpf[i] - '0') * (11 - i);
    }
    remainder = sum % 11;
    int digit2 = (remainder < 2) ? 0 : 11 - remainder;
    cpf += to_string(digit2);
    
    return cpf;
}

// 生成邮箱
string generateEmail(const string& name) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 3);
    
    vector<string> domains = {"gmail.com", "outlook.com", "yahoo.com.br", "hotmail.com"};
    return name + to_string(dis(gen)) + "@" + domains[dis(gen) % 4];
}

// 生成电话号码
string generatePhone() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis1(11, 99);  // 区号
    uniform_int_distribution<> dis2(90000000, 99999999);  // 号码
    
    return "(" + to_string(dis1(gen)) + ") 9" + to_string(dis2(gen));
}

// 生成信用评分
int generateCreditScore() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(300, 900);
    return dis(gen);
}

// 生成出生日期
string generateBirthDate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> yearDis(1950, 2005);
    uniform_int_distribution<> monthDis(1, 12);
    uniform_int_distribution<> dayDis(1, 28);
    
    int year = yearDis(gen);
    int month = monthDis(gen);
    int day = dayDis(gen);
    
    stringstream ss;
    ss << setfill('0') << setw(2) << day << "/"
       << setw(2) << month << "/"
       << year;
    return ss.str();
}

// 生成年收入
int generateIncome() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(15000, 500000);
    return dis(gen);
}

// 生成待支付账户数
int generatePendingAccounts() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 5);
    return dis(gen);
}

// 生成拖欠天数
int generateDaysOverdue() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1000);
    return dis(gen);
}

// 生成债务金额
double generateDebtAmount() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 100000.0);
    return dis(gen);
}

int main() {
    const int RECORDS = 50000;  // 50,000 条记录
    
    // 打开输出文件
    ofstream file("serasa_dataset.csv");
    
    if (!file.is_open()) {
        cerr << "Não foi possível criar o arquivo de saída!" << endl;
        return 1;
    }
    
    // 写入CSV标题
    file << "ID,Nome,CPF,Email,Telefone,DataNascimento,Renda,ScoreCrediticio,"
         << "ContasPendentes,DiasAtraso,MontantaDivida,Status\n";
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> statusDis(0, 2);
    vector<string> statuses = {"Ativo", "Inativo", "Bloqueado"};
    
    // Gerar 50.000 registros
    cout << "Gerando " << RECORDS << " registros de dados..." << endl;
    
    for (int i = 1; i <= RECORDS; i++) {
        // 生成随机名字
        uniform_int_distribution<> firstNameDis(0, firstNames.size() - 1);
        uniform_int_distribution<> lastNameDis(0, lastNames.size() - 1);
        
        string firstName = firstNames[firstNameDis(gen)];
        string lastName = lastNames[lastNameDis(gen)];
        string fullName = firstName + " " + lastName;
        
        // 生成所有数据字段
        string cpf = generateCPF();
        string email = generateEmail(firstName);
        string phone = generatePhone();
        string birthDate = generateBirthDate();
        int income = generateIncome();
        int creditScore = generateCreditScore();
        int pendingAccounts = generatePendingAccounts();
        int daysOverdue = generateDaysOverdue();
        double debtAmount = generateDebtAmount();
        string status = statuses[statusDis(gen)];
        
        // 写入CSV行
        file << i << ","
             << fullName << ","
             << cpf << ","
             << email << ","
             << phone << ","
             << birthDate << ","
             << income << ","
             << creditScore << ","
             << pendingAccounts << ","
             << daysOverdue << ","
             << fixed << setprecision(2) << debtAmount << ","
             << status << "\n";
        
        // Exibir progresso a cada 10.000 registros
        if (i % 10000 == 0) {
            cout << "Registros gerados: " << i << "..." << endl;
        }
    }
    
    file.close();
    
    cout << "\n✓ Conjunto de dados gerado com sucesso!" << endl;
    cout << "Arquivo salvo como: serasa_dataset.csv" << endl;
    cout << "Total de registros: " << RECORDS << endl;

    // Exibir os primeiros 5 registros em uma tabela formatada
    cout << "\n--- Amostra dos Dados Gerados (5 primeiros registros) ---\n";
    cout << left << setw(5) << "ID" << setw(20) << "Nome" << setw(15) << "CPF" << setw(15) << "Score" << setw(10) << "Status" << endl;
    cout << string(65, '-') << endl;

    ifstream readFile("serasa_dataset.csv");
    string line;
    getline(readFile, line); // Pular cabeçalho

    for (int i = 0; i < 5; ++i) {
        getline(readFile, line);
        stringstream ss(line);
        string id, nome, cpf, email, telefone, dataNascimento, renda, score, contas, dias, divida, status;
        
        getline(ss, id, ',');
        getline(ss, nome, ',');
        getline(ss, cpf, ',');
        getline(ss, email, ',');
        getline(ss, telefone, ',');
        getline(ss, dataNascimento, ',');
        getline(ss, renda, ',');
        getline(ss, score, ',');
        getline(ss, contas, ',');
        getline(ss, dias, ',');
        getline(ss, divida, ',');
        getline(ss, status, '\n');

        cout << left << setw(5) << id << setw(20) << nome << setw(15) << cpf << setw(15) << score << setw(10) << status << endl;
    }
    readFile.close();
    
    return 0;
}
