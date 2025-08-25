import express from 'express';
import cors from 'cors';
import { db } from './db.js';
import clienteRoutes from './routes/clienteRoutes.js';
import fornecedorRoutes from './routes/fornecedorRoutes.js';
import produtoRoutes from './routes/produtoRoutes.js';
import vendaRoutes from './routes/vendaRoutes.js';

const app = express();
app.use(cors());
app.use(express.json());

app.use('/clientes', clienteRoutes);
app.use('/fornecedores', fornecedorRoutes);
app.use('/produtos', produtoRoutes);
app.use('/vendas', vendaRoutes);

app.listen(3000, () => {
  console.log('Servidor rodando na porta 3000');
});
