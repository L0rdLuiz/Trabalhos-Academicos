import express from 'express';
import nodemailer from 'nodemailer';
import cors from 'cors';
import path from 'path';
import { fileURLToPath } from 'url';
import { PrismaClient } from '@prisma/client';
import dotenv from 'dotenv';

dotenv.config();
const prisma = new PrismaClient();
const app = express();

app.use(cors());
app.use(express.json());

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

app.use(express.static(path.join(__dirname, '../pages')));
app.use('/css', express.static(path.join(__dirname, '../pages/css')));
app.use('/scripts', express.static(path.join(__dirname, '../scripts')));
app.use('/img', express.static(path.join(__dirname, '../img')));

app.post('/api/enviar-formulario', async (req, res) => {
  const { nome, nascimento, contato, email, cep } = req.body;
  if (!nome || nome.length < 3) return res.status(400).json({ erro: 'Nome inválido' });
  if (!nascimento) return res.status(400).json({ erro: 'Data de nascimento inválida' });
  if (!contato || !/^\d{10,11}$/.test(contato)) return res.status(400).json({ erro: 'Contato inválido' });
  if (!email || !/\S+@\S+\.\S+/.test(email)) return res.status(400).json({ erro: 'Email inválido' });
  if (!cep || !/^\d{8}$/.test(cep)) return res.status(400).json({ erro: 'CEP inválido' });
  const transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
      user: process.env.EMAIL_ADMIN,
      pass: process.env.EMAIL_SENHA
    }
  });

  const mailOptions = {
    from: `"Formulário AIPRA" <${process.env.EMAIL_ADMIN}>`,
    to: process.env.EMAIL_ADMIN,
    replyTo: email,
    subject: 'Formulário de Voluntário',
    html: `
      <h2>Dados do formulário:</h2>
      <p><strong>Nome:</strong> ${nome}</p>
      <p><strong>Nascimento:</strong> ${nascimento}</p>
      <p><strong>Telefone:</strong> ${contato}</p>
      <p><strong>Email:</strong> ${email}</p>
      <p><strong>CEP:</strong> ${cep}</p>
    `
  };

  try {
    await prisma.voluntario.create({
      data: { nome, nascimento, contato, email, cep }
    });
    console.log('✅ Dados salvos no banco');

    // Envia o e-mail
    await transporter.sendMail(mailOptions);
    console.log('✅ Email enviado');

    res.status(200).json({ mensagem: 'Formulário salvo e email enviado com sucesso!' });
  } catch (error) {
    console.error('❌ Erro no envio ou salvamento:', error);
    res.status(500).json({ erro: 'Erro ao enviar ou salvar' });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Servidor rodando na porta ${PORT}`));
