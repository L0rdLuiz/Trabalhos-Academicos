# TrocAi - Backend

Este é o **back-end** do projeto **TrocAi**, uma plataforma para troca de serviços.  
A API é construída em **Node.js** e segue o padrão arquitetural **MVC (Model-View-Controller)** para manter o código organizado e escalável.

---

## Funcionalidades

- **Autenticação de Usuário**: Sistema de registro e login seguro usando criptografia de senhas e **JWT (JSON Web Tokens)** para controle de sessão.  
- **CRUD de Serviços**: Gerencia a criação, leitura, atualização e exclusão de serviços oferecidos pelos usuários.  

---

## Tecnologias Utilizadas

- **Node.js**: Ambiente de execução.  
- **Express.js**: Framework para criação da API REST.  
- **MongoDB**: Banco de dados NoSQL.  
- **Mongoose**: ODM (Object Data Modeling) para interação com o MongoDB.  
- **bcryptjs**: Para criptografia de senhas.  
- **jsonwebtoken**: Para geração e verificação de tokens de autenticação.  

---

## Configuração e Instalação

1. Clone este repositório:
   ```bash
   git clone <url-do-repositorio>
   ```

2. Navegue até a pasta do projeto:
   ```bash
   cd TrocAi
   ```

3. Instale as dependências:
   ```bash
   npm install
   ```

4. Crie um arquivo `.env` na raiz do projeto com as seguintes variáveis:
   ```env
   MONGO_URI=sua_string_de_conexao_do_mongodb_aqui
   JWT_SECRET=sua_chave_secreta_jwt_aqui
   ```

5. Inicie o servidor:
   ```bash
   node server.js
   ```

➡️ O servidor estará rodando em: **http://localhost:3000**

---

## Endpoints da API

### Autenticação (`/api/auth`)

| Método | Endpoint   | Descrição                          |
|--------|-----------|------------------------------------|
| POST   | `/register` | Registra um novo usuário.          |
| POST   | `/login`    | Autentica um usuário e retorna JWT |

---

### Serviços (`/api/services`)

| Método | Endpoint | Descrição                           |
|--------|----------|-------------------------------------|
| POST   | `/`      | Cria um novo serviço.               |
| GET    | `/`      | Lista todos os serviços disponíveis.|
| GET    | `/:id`   | Obtém um serviço específico pelo ID. |
| PUT    | `/:id`   | Atualiza um serviço pelo ID.        |
| DELETE | `/:id`   | Exclui um serviço pelo ID.          |

---