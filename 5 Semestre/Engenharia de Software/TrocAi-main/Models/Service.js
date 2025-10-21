const mongoose = require('mongoose');

const serviceSchema = new mongoose.Schema({
    servico: {
        type: String,
        required: true,
        trim: true
    },
    descricao: {
        type: String,
        required: true
    },
    usuario: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'User', // 'User' é o nome do seu modelo
        required: true
    }
}, {
    timestamps: true
});

const Service = mongoose.model('Service', serviceSchema);

module.exports = Service;