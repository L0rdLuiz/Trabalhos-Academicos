CREATE TABLE Livros (
	ID_livro serial primary key, 
	titulo text, 
	autor text, 
	preco numeric(6,2), 
	quant_estoque int
);

CREATE TABLE Clientes (
	ID_cliente serial primary key,
	nome text,
	email varchar(255)
);

CREATE TABLE Pedidos (
	ID_pedido serial primary key,
	ID_cliente int,
	data_pedido TIMESTAMPTZ NOT NULL DEFAULT now(),
	status VARCHAR(50) NOT NULL DEFAULT 'pendente'
);

CREATE TABLE Itens_pedido (
	ID_item serial primary key,
	ID_pedido int,
	ID_livro int,
	quantidade int,
	preco_unitario numeric(6,2)
);

CREATE TABLE Log_auditoria (
	ID_log serial primary key,
	tabela_afetada VARCHAR(100),
	ID_registro_afetado int,
	operacao VARCHAR(100)
);

INSERT INTO Livros (titulo, autor, preco, quant_estoque)
values ('A Arte da Guerra', 'Sun Tzu', 12.49, 10),
	   ('Extraordinário', 'R. J. Palacio', 39.99, 25),
	   ('O cavaleiro preso na armadura', 'Robert Fischer', 32.77, 6),
	   ('Diário de um Banana I', 'Jeff Kinney', 48.90, 55)
	   
INSERT INTO Clientes (nome, email)
values ('Luiz', 'Luiz@gmail.com'),
	   ('Isabela', 'Isabela@gmail.com'),
	   ('Carlos', 'Carlos@gmail.com'),
	   ('Felype', 'Felype@gmail.com')
	   
INSERT INTO Pedidos (ID_cliente)
values (1)
INSERT INTO Pedidos (ID_cliente)
values (2)
INSERT INTO Pedidos (ID_cliente)
values (3)
INSERT INTO Pedidos (ID_cliente)
values (4)

INSERT INTO Itens_pedido (ID_pedido, ID_livro, quantidade, preco_unitario)
values (1, 3, 2, 32.77),
	   (2, 1, 1, 12.49),
	   (3, 4, 1, 48.90),
	   (4, 2, 1, 39.99),
	   (5, 1, 2, 12.49)
	   
select * from Livros;
select * from Clientes;
select * from Pedidos;
select * from Itens_pedido;
