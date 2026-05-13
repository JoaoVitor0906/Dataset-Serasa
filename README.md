# Quick Sort - Método de Hoare - Dataset Serasa

## Descrição
Este projeto implementa o algoritmo **Quick Sort** utilizando o **método de particionamento de Hoare** para ordenar um dataset fictício de 50.000 registros de inadimplentes do Serasa, conforme solicitado no trabalho de Tópicos em Algoritmos.

## Estrutura do Projeto

- `serasa_dataset_generator.cpp` - Gera o dataset CSV com 50.000 registros
- `quicksort_serasa.cpp` - Implementação do Quick Sort com Hoare para ordenar o dataset

## Como Usar

### 1. Compilar o Gerador de Dataset
```bash
g++ -std=c++17 -O2 serasa_dataset_generator.cpp -o dataset_generator
```

### 2. Executar o Gerador
```bash
./dataset_generator
```
Isso criará o arquivo `serasa_dataset.csv` com 50.000 registros.

### 3. Compilar o Quick Sort
```bash
g++ -std=c++17 -O2 quicksort_serasa.cpp -o quicksort
```

### 4. Executar o Quick Sort
```bash
./quicksort
```

## Método de Hoare Explicado

O particionamento de Hoare funciona da seguinte forma:

1. **Escolhe um pivô** (primeiro elemento)
2. **Dois ponteiros** (i e j) movem-se em direções opostas
3. **i** avança enquanto elemento < pivô
4. **j** recua enquanto elemento > pivô
5. Quando i >= j, o particionamento termina
6. Retorna j como ponto de divisão

### Vantagens do Método de Hoare
- **Menos trocas** comparado ao método de Lomuto
- **Mais eficiente** em prática
- **Melhor cache locality**

## Saída do Programa

O programa exibe:
- ✓ Status de carregamento do dataset
- Número de comparações realizadas
- Número de trocas realizadas
- Tempo total de execução em milissegundos
- Tempo por registro
- Amostra dos dados ordenados

## Exemplo de Saída

```
╔════════════════════════════════════════════════════════════╗
║  QUICK SORT - MÉTODO DE HOARE - DATASET SERASA           ║
╚════════════════════════════════════════════════════════════╝

Carregando dataset...
✓ Dataset carregado com sucesso!
  Total de registros: 50000

Executando Quick Sort com particionamento de Hoare...
✓ Ordenação concluída!

=== ESTATÍSTICAS DA ORDENAÇÃO ===
Total de registros: 50000
Comparações realizadas: 1234567
Trocas realizadas: 567890
Tempo total: 234.5670 ms
Tempo por registro: 0.004691 ms

=== AMOSTRA DOS DADOS ORDENADOS ===
```

## Estrutura do Registro

Cada registro no CSV contém:
- **ID**: Identificador único
- **Nome**: Nome completo
- **CPF**: CPF válido (gerado)
- **Email**: Endereço de email
- **Telefone**: Número de telefone
- **Data de Nascimento**: DD/MM/AAAA
- **Renda**: Renda anual em R$
- **Score Creditício**: 300-900 (critério de ordenação)
- **Contas Pendentes**: Número de contas pendentes
- **Dias de Atraso**: Dias de atraso em pagamentos
- **Montante de Dívida**: Valor total devido
- **Status**: Ativo, Inativo ou Bloqueado

## Compilação Alternativa (Windows)

```bash
g++ -std=c++17 -O2 quicksort_serasa.cpp -o quicksort.exe
quicksort.exe
```

## Notas Importantes

- O dataset é ordenado por **Score Creditício** em ordem crescente
- Comparações e trocas são contabilizadas para análise de performance
- O tempo é medido em milissegundos com precisão de 4 casas decimais
- Use `-O2` na compilação para otimização de release

## Requisitos

- Compilador C++17 ou superior
- 500MB de RAM (para 50.000 registros)
- Arquivo `serasa_dataset.csv` no mesmo diretório

## Autor

Desenvolvimento para trabalho de Tópicos em Algoritmos - UTFPR
