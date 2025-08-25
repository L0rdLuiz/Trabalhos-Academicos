import express from 'express';
import { db } from '../db.js';

const router = express.Router();

// CREATE
router.post('/', (req, res) => {
  const { nome, telefone, email } = req.body;
  const sql = 'INSERT INTO Cliente (nome, telefone, email) VALUES (?, ?, ?)';
  db.query(sql, [nome, telefone, email], (err, result) => {
    if (err) return res.status(500).json(err);
    res.status(201).json({ id: result.insertId, nome, telefone, email });
  });
});

// READ
router.get('/', (req, res) => {
  db.query('SELECT * FROM Cliente', (err, results) => {
    if (err) return res.status(500).json(err);
    res.json(results);
  });
});

// UPDATE
router.put('/:id', (req, res) => {
  const { id } = req.params;
  const { nome, telefone, email } = req.body;
  const sql = 'UPDATE Cliente SET nome = ?, telefone = ?, email = ? WHERE id_cliente = ?';
  db.query(sql, [nome, telefone, email, id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Cliente atualizado!' });
  });
});

// DELETE
router.delete('/:id', (req, res) => {
  const { id } = req.params;
  const sql = 'DELETE FROM Cliente WHERE id_cliente = ?';
  db.query(sql, [id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Cliente deletado!' });
  });
});

export default router;
