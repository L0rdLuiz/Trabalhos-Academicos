import express from 'express';
import { db } from '../db.js';

const router = express.Router();

// CREATE
router.post('/', (req, res) => {
  const { nome, preco, estoque, id_fornecedor } = req.body;
  const sql = 'INSERT INTO Produto (nome, preco, estoque, id_fornecedor) VALUES (?, ?, ?, ?)';
  db.query(sql, [nome, preco, estoque, id_fornecedor], (err, result) => {
    if (err) return res.status(500).json(err);
    res.status(201).json({ id: result.insertId, nome, preco, estoque, id_fornecedor });
  });
});

// READ
router.get('/', (req, res) => {
  db.query('SELECT * FROM Produto', (err, results) => {
    if (err) return res.status(500).json(err);
    res.json(results);
  });
});

// UPDATE
router.put('/:id', (req, res) => {
  const { id } = req.params;
  const { nome, preco, estoque, id_fornecedor } = req.body;
  const sql = 'UPDATE Produto SET nome = ?, preco = ?, estoque = ?, id_fornecedor = ? WHERE id_produto = ?';
  db.query(sql, [nome, preco, estoque, id_fornecedor, id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Produto atualizado!' });
  });
});

// DELETE
router.delete('/:id', (req, res) => {
  const { id } = req.params;
  const sql = 'DELETE FROM Produto WHERE id_produto = ?';
  db.query(sql, [id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Produto deletado!' });
  });
});

export default router;
