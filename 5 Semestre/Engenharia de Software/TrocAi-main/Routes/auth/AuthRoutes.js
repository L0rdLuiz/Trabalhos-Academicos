const express = require('express');
const router = express.Router();
const authController = require('../../Controllers/auth/AuthController');

// rota para registrar um novo usuário
router.post('/register', authController.registerUser);

// rota para login de usuário
router.post('/login', authController.loginUser);

module.exports = router;