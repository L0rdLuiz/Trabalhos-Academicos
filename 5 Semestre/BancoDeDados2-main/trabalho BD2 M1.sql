-- =========================================
-- Tabelas
-- =========================================
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

-- Adicionei o campo status_item para o exercício 5
CREATE TABLE Itens_pedido (
	ID_item serial primary key,
	ID_pedido int,
	ID_livro int,
	quantidade int,
	preco_unitario numeric(6,2),
	status_item VARCHAR(50) DEFAULT 'Pendente'
);

CREATE TABLE Log_auditoria (
	ID_log serial primary key,
	tabela_afetada VARCHAR(100),
	ID_registro_afetado int,
	operacao VARCHAR(100)
);

-- =========================================
-- Inserts de teste
-- =========================================
INSERT INTO Livros (titulo, autor, preco, quant_estoque)
VALUES 
	('A Arte da Guerra', 'Sun Tzu', 12.49, 10),
	('Extraordinário', 'R. J. Palacio', 39.99, 25),
	('O cavaleiro preso na armadura', 'Robert Fischer', 32.77, 6),
	('Diário de um Banana I', 'Jeff Kinney', 48.90, 55);

INSERT INTO Clientes (nome, email)
VALUES 
	('Luiz', 'Luiz@gmail.com'),
	('Isabela', 'Isabela@gmail.com'),
	('Carlos', 'Carlos@gmail.com'),
	('Felype', 'Felype@gmail.com');

INSERT INTO Pedidos (ID_cliente) VALUES (1), (2), (3), (4);

INSERT INTO Itens_pedido (ID_pedido, ID_livro, quantidade, preco_unitario)
VALUES 
	(1, 3, 2, 32.77),
	(2, 1, 1, 12.49),
	(3, 4, 1, 48.90),
	(4, 2, 1, 39.99),
	(4, 1, 2, 12.49);

-- =========================================
-- Exercício 3: Atualizar estoque
-- =========================================
CREATE OR REPLACE FUNCTION atualizar_estoque()
RETURNS TRIGGER AS
$$
DECLARE
    v_status VARCHAR(50);
    v_estoque_atual INT;
BEGIN
    SELECT status INTO v_status
    FROM Pedidos
    WHERE ID_pedido = NEW.ID_pedido;

    IF v_status = 'pendente' THEN
        
        SELECT quant_estoque INTO v_estoque_atual
        FROM Livros
        WHERE ID_livro = NEW.ID_livro;

        IF v_estoque_atual < NEW.quantidade THEN
            RAISE EXCEPTION 'Estoque insuficiente para o livro inserido';
        END IF;

        UPDATE Livros
        SET quant_estoque = quant_estoque - NEW.quantidade
        WHERE ID_livro = NEW.ID_livro;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tgr_atualizar_estoque
AFTER INSERT ON Itens_pedido
FOR EACH ROW
EXECUTE FUNCTION atualizar_estoque();

-- =========================================
-- Exercício 4: Impedir exclusão de cliente com pedidos
-- =========================================
CREATE OR REPLACE FUNCTION cliente_verificar_delete()
RETURNS TRIGGER AS $$
BEGIN
	IF EXISTS (SELECT 1 FROM Pedidos WHERE ID_cliente = OLD.ID_cliente) THEN
		RAISE EXCEPTION 'Cliente não pode ser deletado pois efetuou pedido';
	END IF;

	RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER cliente_delete_pedido
BEFORE DELETE ON Clientes
FOR EACH ROW
EXECUTE FUNCTION cliente_verificar_delete();

-- Teste do exercício 4
DELETE FROM Clientes WHERE ID_cliente = 1;

-- =========================================
-- Exercício 5: Atualizar status do pedido quando itens forem enviados
-- =========================================
CREATE OR REPLACE FUNCTION att_status_enviado()
RETURNS TRIGGER AS $$
BEGIN
	-- Quando o status de um item for atualizado para 'Enviado',
	-- o pedido correspondente passa para 'Concluido'
	IF NEW.status_item = 'Enviado' THEN
		UPDATE Pedidos 
		SET status = 'Concluido' 
		WHERE ID_pedido = NEW.ID_pedido;
	END IF;

	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER att_status_pedido
AFTER UPDATE OF status_item ON Itens_pedido
FOR EACH ROW
EXECUTE FUNCTION att_status_enviado();

-- Teste do exercício 5
SELECT * FROM Itens_pedido;
SELECT * FROM Pedidos;

-- Atualizar um item para 'Enviado'
UPDATE Itens_pedido 
SET status_item = 'Enviado' 
WHERE ID_item = 4;

-- Conferir se o pedido foi atualizado
SELECT * FROM Pedidos WHERE ID_pedido = 4;
