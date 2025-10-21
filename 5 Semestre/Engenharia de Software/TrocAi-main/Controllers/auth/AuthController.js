const User = require('../../Models/User');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

// a senha do token
const JWT_SECRET = process.env.JWT_SECRET;

// registrar novo usuário
exports.registerUser = async (req, res) => {
  const { name, email, password } = req.body;
  try {
    const existingUser = await User.findOne({ email });
    if (existingUser) {
      return res.status(400).json({ message: 'E-mail já cadastrado.' });
    }

    const hashedPassword = await bcrypt.hash(password, 10);
    const newUser = new User({
      name,
      email,
      password: hashedPassword
    });

    await newUser.save();
    res.status(201).json({ message: 'Usuário registrado com sucesso!' });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};

// login do usuário
exports.loginUser = async (req, res) => {
  const { email, password } = req.body;
  try {
    const user = await User.findOne({ email });
    if (!user) {
      return res.status(400).json({ message: 'Credenciais inválidas.' });
    }

    const isMatch = await bcrypt.compare(password, user.password);
    if (!isMatch) {
      return res.status(400).json({ message: 'Credenciais inválidas.' });
    }

    const token = jwt.sign({ userId: user._id }, JWT_SECRET, { expiresIn: '1h' });
    res.status(200).json({
      message: 'Login bem-sucedido!',
      token,
      userId: user._id
    });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};