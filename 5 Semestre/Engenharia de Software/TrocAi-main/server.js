const express = require('express');
const mongoose = require('mongoose');
const dotenv = require('dotenv');
const cors = require('cors');

dotenv.config();

const serviceRoutes = require('./Routes/ServiceRoutes');

const authRoutes = require('./Routes/auth/AuthRoutes');

const app = express();
const PORT = process.env.PORT || 3000;

// middleware
app.use(cors());
app.use(express.json());

// conexão MongoDB
mongoose.connect(process.env.MONGO_URI)
  .then(() => console.log('Conectado ao MongoDB!'))
  .catch(err => console.error('Erro ao conectar ao MongoDB:', err));

// rotas da API
app.use('/api/services', serviceRoutes);

app.use('/api/auth', authRoutes);

// inicia o servidor
app.listen(PORT, () => {
  console.log(`Servidor rodando na porta ${PORT}`);
});