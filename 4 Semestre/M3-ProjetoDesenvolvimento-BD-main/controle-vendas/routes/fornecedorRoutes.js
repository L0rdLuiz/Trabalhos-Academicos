import express from 'express';
import { db } from '../db.js';

const router = express.Router();

// CREATE
router.post('/', (req, res) => {
  const { nome, telefone, cnpj } = req.body;
  const sql = 'INSERT INTO Fornecedor (nome, telefone, cnpj) VALUES (?, ?, ?)';
  db.query(sql, [nome, telefone, cnpj], (err, result) => {
    if (err) return res.status(500).json(err);
    res.status(201).json({ id: result.insertId, nome, telefone, cnpj });
  });
});

// READ
router.get('/', (req, res) => {
  db.query('SELECT * FROM Fornecedor', (err, results) => {
    if (err) return res.status(500).json(err);
    res.json(results);
  });
});

// UPDATE
router.put('/:id', (req, res) => {
  const { id } = req.params;
  const { nome, telefone, cnpj } = req.body;
  const sql = 'UPDATE Fornecedor SET nome = ?, telefone = ?, cnpj = ? WHERE id_fornecedor = ?';
  db.query(sql, [nome, telefone, cnpj, id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Fornecedor atualizado!' });
  });
});

// DELETE
router.delete('/:id', (req, res) => {
  const { id } = req.params;
  const sql = 'DELETE FROM Fornecedor WHERE id_fornecedor = ?';
  db.query(sql, [id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Fornecedor deletado!' });
  });
});

export default router;
