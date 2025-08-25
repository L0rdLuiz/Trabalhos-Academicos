# 📦 Projeto: Controle de Vendas

Este projeto foi desenvolvido como parte da disciplina de Banco de Dados (M3).  
Consiste em um sistema backend com Node.js e MySQL que realiza operações CRUD para controle de clientes, fornecedores, produtos e vendas.

GET

http://localhost:3000/clientes
http://localhost:3000/fornecedores
http://localhost:3000/produtos
http://localhost:3000/vendas

POST


PUT
DELETE

---

## ⚙️ Tecnologias Utilizadas

- Node.js
- Express
- MySQL
- dotenv
- Postman (para testes)

---

## 🧱 Estrutura do Projeto

- `server.js` → Arquivo principal do servidor
- `db.js` → Conexão com banco de dados MySQL
- `routes/` → Contém as rotas CRUD para cada entidade:
  - `clienteRoutes.js`
  - `fornecedorRoutes.js`
  - `produtoRoutes.js`
  - `vendaRoutes.js`

---

## 🗃️ Banco de Dados

Crie o banco e tabelas com o seguinte script SQL:

```sql
CREATE DATABASE controle_vendas;
USE controle_vendas;

CREATE TABLE Cliente (
  id_cliente INT PRIMARY KEY AUTO_INCREMENT,
  nome VARCHAR(100),
  telefone VARCHAR(15),
  email VARCHAR(100)
);

CREATE TABLE Fornecedor (
  id_fornecedor INT PRIMARY KEY AUTO_INCREMENT,
  nome VARCHAR(100),
  telefone VARCHAR(15),
  cnpj VARCHAR(20)
);

CREATE TABLE Produto (
  id_produto INT PRIMARY KEY AUTO_INCREMENT,
  nome VARCHAR(100),
  preco DECIMAL(10,2),
  estoque INT,
  id_fornecedor INT,
  FOREIGN KEY (id_fornecedor) REFERENCES Fornecedor(id_fornecedor)
);

CREATE TABLE Venda (
  id_venda INT PRIMARY KEY AUTO_INCREMENT,
  data DATE,
  id_cliente INT,
  FOREIGN KEY (id_cliente) REFERENCES Cliente(id_cliente)
);

CREATE TABLE ItemVenda (
  id_itemVenda INT PRIMARY KEY AUTO_INCREMENT,
  id_venda INT,
  id_produto INT,
  quantidade INT,
  preco_unitario DECIMAL(10,2),
  FOREIGN KEY (id_venda) REFERENCES Venda(id_venda),
  FOREIGN KEY (id_produto) REFERENCES Produto(id_produto)
);
