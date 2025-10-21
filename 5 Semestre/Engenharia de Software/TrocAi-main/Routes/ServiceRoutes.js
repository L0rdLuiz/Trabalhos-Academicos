const express = require('express');
const router = express.Router();
const serviceController = require('../Controllers/ServiceController');

// rota para criar um novo serviço
router.post('/', serviceController.createService);

// rota para obter todos os serviços
router.get('/', serviceController.getServices);

// rota para obter um serviço específico por ID
router.get('/:id', serviceController.getServiceById);

// rota para atualizar um serviço por ID
router.put('/:id', serviceController.updateService);

// rota para deletar um serviço por ID
router.delete('/:id', serviceController.deleteService);

module.exports = router;