CREATE TABLE Livros (
	ID serial primary key, 
	id_livro int, 
	titulo text, 
	autor text, 
	preco numeric(6,2), 
	quant_estoque int
);

CREATE TABLE Clientes (
	ID serial primary key,
	id_cliente int,
	nome text,
	email varchar(255)
);

CREATE TABLE Pedidos (
	ID serial primary key,
	id_pedido int,
	id_cliente int,
	data_pedido TIMESTAMPTZ NOT NULL DEFAULT now(),
	status VARCHAR(50) NOT NULL DEFAULT 'pendente'
);

CREATE TABLE Itens_pedido (
	ID serial primary key,
	id_item int,
	id_pedido int,
	id_livro int,
	quantidade int,
	preco_unitario numeric(6,2)
);

CREATE TABLE Log_auditoria (
	ID serial primary key,
	id_log int,
	tabela_afetada VARCHAR(100),
	id_registro_afetado int,
	operacao VARCHAR(100)
);

