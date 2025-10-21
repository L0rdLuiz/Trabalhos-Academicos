const Service = require('../Models/Service');
const User = require('../Models/User');

// criar um novo serviço
exports.createService = async (req, res) => {
  const { servico, descricao, usuario } = req.body;
  try {
    const newService = new Service({
      servico,
      descricao,
      usuario
    });
    const savedService = await newService.save();
    res.status(201).json(savedService);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};

// obter todos os serviços
exports.getServices = async (req, res) => {
    try {
        const services = await Service.find().populate({
            path: 'usuario',
            select: 'name' // Seleciona apenas o campo 'name' da coleção 'User'
        });
        res.status(200).json(services);
    } catch (err) {
        console.error('Erro na função getServices:', err);
        res.status(500).json({ error: 'Erro ao carregar serviços.' });
    }
};

// funcao antiga
// exports.getServices = async (req, res) => {
//   try {
//     const services = await Service.find();
//     res.status(200).json(services);
//   } catch (err) {
//     res.status(500).json({ error: err.message });
//   }
// };

// obter um serviço por ID
exports.getServiceById = async (req, res) => {
  try {
    const serviceId = req.params.id;
    const service = await Service.findById(serviceId).populate('usuario', 'name');
    if (!service) {
      return res.status(404).json({ message: 'Serviço não encontrado' });
    }
    res.status(200).json(service);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};

// atualizar um serviço por ID
exports.updateService = async (req, res) => {
  try {
    const updatedService = await Service.findByIdAndUpdate(req.params.id, req.body, { new: true, runValidators: true });
    if (!updatedService) {
      return res.status(404).json({ message: 'Serviço não encontrado' });
    }
    res.status(200).json(updatedService);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};

// deletar um serviço por ID
exports.deleteService = async (req, res) => {
  try {
    const deletedService = await Service.findByIdAndDelete(req.params.id);
    if (!deletedService) {
      return res.status(404).json({ message: 'Serviço não encontrado' });
    }
    res.status(200).json({ message: 'Serviço deletado com sucesso' });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};