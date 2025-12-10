# Sistema de Análise Hemodinâmica - Projeto Final APC

**Aluna:** Maria Luisa Oliveira Lima  
**Matrícula:** 252015113  
**Universidade:** Universidade de Brasília (UnB)  
**Disciplina:** Algoritmos e Programação de Computadores (APC)

---

## 📋 Sobre o Projeto

Este projeto consiste em um software desenvolvido em **Linguagem C** para monitoramento e análise de dados hemodinâmicos de pacientes. O sistema permite o registro de pressões arteriais, realiza cálculos fisiológicos automáticos e gera relatórios estatísticos e arquivos de saída.

O foco principal é auxiliar na classificação da pressão arterial e no cálculo de indicadores de risco cardiovascular, como a Pressão de Pulso (PP) e a Pressão Arterial Média (PAM).

## ⚙️ Funcionalidades

O sistema opera através de um menu interativo no console com as seguintes opções:

1.  **Inserção Manual:** Cadastro de pacientes com Nome, PAS (Sistólica) e PAD (Diastólica).
    * *Nota: Suporta nomes compostos.*
2.  **Importação de Dados:** Leitura automática de arquivos de texto (`dados.txt`) para processamento em lote.
3.  **Histórico:** Visualização tabular de todos os registros armazenados na memória.
4.  **Análise Estatística:**
    * Cálculo da média da PAM do grupo.
    * Contagem de pacientes por categoria de risco.
    * Identificação do paciente com a maior pressão sistólica.
5.  **Relatório Externo:** Exportação de todos os dados e estatísticas para um arquivo de texto personalizado (ex: `relatorio.txt`).

## 🏥 Lógica de Classificação e Fórmulas

O software utiliza diretrizes médicas internacionais e fórmulas fisiológicas padrão:

### 1. Fórmulas Hemodinâmicas
* **Pressão de Pulso (PP):** $$PP = PAS - PAD$$
    *Indicador de rigidez arterial.*
* **Pressão Arterial Média (PAM):** $$PAM = \frac{PAS + (2 \times PAD)}{3}$$
    *Indicador da perfusão tecidual.*

### 2. Diretriz de Classificação
O código implementa a classificação baseada na **AHA/ACC 2017 (American Heart Association)**:

| Classificação | Sistólica (mmHg) | E/OU | Diastólica (mmHg) |
| :--- | :--- | :--- | :--- |
| **Normal** | < 120 | E | < 80 |
| **Elevada** | 120 – 129 | E | < 80 |
| **Hipertensão Estágio 1** | 130 – 139 | OU | 80 – 89 |
| **Hipertensão Estágio 2** | ≥ 140 | OU | ≥ 90 |

---

## 🛠️ Tecnologias e Estruturas Utilizadas

* **Linguagem:** C (Padrão C99)
* **Armazenamento:** `structs` para organização dos dados do paciente.
* **Persistência:** Manipulação de arquivos (`FILE *`) para leitura e escrita.
* **Algoritmos:** Busca de maior valor, contadores condicionais e acumuladores para médias.

## 🚀 Como Compilar e Executar

Para rodar este projeto em sua máquina, você precisará de um compilador C (como GCC).

1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/mahluoliveira/projeto-final-apc.git](https://github.com/mahluoliveira/projeto-final-apc.git)
    ```
2.  **Compile o código:**
    ```bash
    gcc projetofinal/projetofinal.c -o sistema
    ```
3.  **Execute:**
    * **Windows:** `sistema.exe`
    * **Linux/Mac:** `./sistema`

---

## 📄 Estrutura de Arquivos

* `projetofinal.c`: Código fonte principal.
* `dados.txt`: Arquivo modelo para importação de dados (Formato: `Nome PAS PAD`).
* `README.md`: Documentação do projeto.

---
*Desenvolvido como requisito de avaliação final da disciplina de APC - 2025.*
