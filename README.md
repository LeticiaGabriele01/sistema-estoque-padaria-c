# 🥖 Sistema de Gerenciamento de Padaria

Projeto desenvolvido para a disciplina de **Laboratório de Programação**. O sistema é uma aplicação de console em **Linguagem C** focada no controle de estoque de produtos de uma padaria, utilizando persistência de dados em arquivos binários.

## ✨ Funcionalidades

- **Cadastro de Produtos**: Registro de código único, nome, preço e quantidade.
- **Validação Inteligente**: 
    - Verificação de códigos duplicados para evitar erros de estoque.
    - Bloqueio de valores negativos para preço e quantidade.
    - Validação de campos obrigatórios (nome).
- **Consulta de Estoque**: Listagem completa de todos os itens registrados.
- **Busca por Código**: Localização rápida de produtos através do identificador único.
- **Persistência de Dados**: Armazenamento em arquivo binário (`.dat`), garantindo que os dados permaneçam salvos após o fechamento do programa.

## 🛠️ Tecnologias e Conceitos

- **Linguagem C**: Utilização de funções padrão de I/O e manipulação de memória.
- **Structs**: Modelagem organizada dos dados do produto.
- **Manipulação de Arquivos**: Uso de `fopen`, `fwrite` e `fread` para gerenciar o banco de dados binário.
- **Tratamento de Buffer**: Implementação de rotinas para evitar erros de leitura de teclado.

## 📂 Estrutura de Arquivos

- `main.c`: Contém toda a lógica de negócio e interface de usuário.
- `produtos.dat`: Arquivo gerado automaticamente para salvar os registros (não deve ser editado manualmente).

## 🚀 Como testar

1. Certifique-se de ter um compilador C (como o GCC) instalado.
2. Clone o repositório:
   ```bash
   git clone [https://github.com/SeuUsuario/sistema-estoque-padaria-c.git](https://github.com/SeuUsuario/sistema-estoque-padaria-c.git)
