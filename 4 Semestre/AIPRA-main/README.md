<h1>🧠 AIPRA</h1>

<p>Este é o repositório do projeto <strong>AIPRA</strong>, uma aplicação web com formulário e integração a banco de dados via Prisma.</p>

<p><strong>Acesse o site hospedado aqui:</strong><br />
➡ <a href="https://aipra-front.onrender.com/index.html" target="_blank">https://aipra-front.onrender.com/index.html</a></p>

<p><strong>Repositório no GitHub:</strong><br />
➡ <a href="https://github.com/L0rdLuiz/AIPRA" target="_blank">https://github.com/L0rdLuiz/AIPRA</a></p>

<hr />

<h2>⚙️ Como rodar localmente</h2>

<p>Siga os passos abaixo para rodar o projeto em sua máquina local:</p>

<h3>1. Clone o repositório</h3>

<pre><code>git clone https://github.com/L0rdLuiz/AIPRA
cd AIPRA
</code></pre>

<h3>2. Instale as dependências</h3>

<p>Certifique-se de ter o <strong>Node.js</strong> instalado.</p>

<pre><code>npm install
</code></pre>

<h3>3. Configure o .env</h3>

<p>Crie um arquivo <code>.env</code> na raiz do projeto com o seguinte conteúdo (preencha com suas informações reais):</p>

<pre><code>DATABASE_URL=coloque_sua_url_do_banco_aqui

EMAIL_ADMIN=seu_email_de_envio@gmail.com
EMAIL_SENHA=senha_do_email

PORT=3000
</code></pre>

<p><strong>Lembre-se:</strong> o e-mail e a senha são usados para envio de formulários. Ative o acesso a apps menos seguros no provedor de e-mail, se necessário.</p>

<h3>4. Configure o Prisma</h3>

<pre><code>npx prisma generate
npx prisma migrate dev --name init
</code></pre>

<p>(Ou apenas <code>npx prisma migrate dev</code> se o projeto já tiver migrations definidas)</p>

<h3>5. Inicie o servidor</h3>

<pre><code>npm run dev
</code></pre>

<p>O servidor estará disponível em <code>http://localhost:3000</code> (ou na porta definida no <code>.env</code>).</p>

<hr />

<h2>🛠️ Tecnologias utilizadas</h2>

<ul>
  <li>HTML, CSS e JavaScript</li>
  <li>Node.js</li>
  <li>Express</li>
  <li>Prisma (ORM)</li>
  <li>Nodemailer</li>
  <li>Render (para hospedagem)</li>
</ul>

<hr />
