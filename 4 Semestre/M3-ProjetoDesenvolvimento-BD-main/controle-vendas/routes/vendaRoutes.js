import express from 'express';
import { db } from '../db.js';

const router = express.Router();

// CREATE
router.post('/', (req, res) => {
  const { data, id_cliente } = req.body;
  const sql = 'INSERT INTO Venda (data, id_cliente) VALUES (?, ?)';
  db.query(sql, [data, id_cliente], (err, result) => {
    if (err) return res.status(500).json(err);
    res.status(201).json({ id: result.insertId, data, id_cliente });
  });
});

// READ
router.get('/', (req, res) => {
  db.query('SELECT * FROM Venda', (err, results) => {
    if (err) return res.status(500).json(err);
    res.json(results);
  });
});

// UPDATE
router.put('/:id', (req, res) => {
  const { id } = req.params;
  const { data, id_cliente } = req.body;
  const sql = 'UPDATE Venda SET data = ?, id_cliente = ? WHERE id_venda = ?';
  db.query(sql, [data, id_cliente, id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Venda atualizada!' });
  });
});

// DELETE
router.delete('/:id', (req, res) => {
  const { id } = req.params;
  const sql = 'DELETE FROM Venda WHERE id_venda = ?';
  db.query(sql, [id], (err) => {
    if (err) return res.status(500).json(err);
    res.json({ message: 'Venda deletada!' });
  });
});

export default router;
