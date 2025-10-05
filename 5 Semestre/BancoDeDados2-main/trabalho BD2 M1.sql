-- CRIAÇÃO DAS TABELAS BASE

DROP TABLE IF EXISTS Itens_pedido CASCADE;
DROP TABLE IF EXISTS Pedidos CASCADE;
DROP TABLE IF EXISTS Clientes CASCADE;
DROP TABLE IF EXISTS Livros CASCADE;
DROP TABLE IF EXISTS Log_auditoria CASCADE;

CREATE TABLE Livros (
    id_livro SERIAL PRIMARY KEY, 
    titulo TEXT, 
    autor TEXT, 
    preco NUMERIC(6,2), 
    quant_estoque INT
);

CREATE TABLE Clientes (
    id_cliente SERIAL PRIMARY KEY,
    nome TEXT,
    email VARCHAR(255)
);

CREATE TABLE Pedidos (
    id_pedido SERIAL PRIMARY KEY,
    id_cliente INT,
    data_pedido TIMESTAMPTZ NOT NULL DEFAULT now(),
    status VARCHAR(50) NOT NULL DEFAULT 'pendente'
);

CREATE TABLE Itens_pedido (
    id_item SERIAL PRIMARY KEY,
    id_pedido INT,
    id_livro INT,
    quantidade INT,
    preco_unitario NUMERIC(6,2),
    status_item VARCHAR(50) DEFAULT 'Pendente'
);

CREATE TABLE Log_auditoria (
    id_log SERIAL PRIMARY KEY,
    tabela_afetada VARCHAR(100),
    id_registro_afetado INT,
    operacao VARCHAR(100),
    data_hora TIMESTAMPTZ DEFAULT now(),
    detalhes TEXT
);

-- DADOS INICIAIS

INSERT INTO Livros (titulo, autor, preco, quant_estoque) VALUES
('A Arte da Guerra', 'Sun Tzu', 12.49, 10),
('Extraordinário', 'R. J. Palacio', 39.99, 25),
('O cavaleiro preso na armadura', 'Robert Fischer', 32.77, 6),
('Diário de um Banana I', 'Jeff Kinney', 48.90, 55);

INSERT INTO Clientes (nome, email) VALUES
('Luiz', 'Luiz@gmail.com'),
('Isabela', 'Isabela@gmail.com'),
('Carlos', 'Carlos@gmail.com'),
('Felype', 'Felype@gmail.com');

INSERT INTO Pedidos (id_cliente) VALUES (1), (2), (3), (4);

INSERT INTO Itens_pedido (id_pedido, id_livro, quantidade, preco_unitario) VALUES
(1, 3, 2, 32.77),
(2, 1, 1, 12.49),
(3, 4, 1, 48.90),
(4, 2, 1, 39.99),
(1, 1, 2, 12.49);

-- EXERCÍCIO 1 - AUDITORIA DE PREÇOS

CREATE OR REPLACE FUNCTION auditar_preco_livro()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.preco <> NEW.preco THEN
        INSERT INTO log_auditoria (tabela_afetada, id_registro_afetado, operacao, data_hora, detalhes)
        VALUES ('livros', OLD.id_livro, 'UPDATE', NOW(),
                'Preço alterado de ' || OLD.preco || ' para ' || NEW.preco);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_auditar_preco_livro
AFTER UPDATE ON Livros
FOR EACH ROW
EXECUTE FUNCTION auditar_preco_livro();

-- EXERCÍCIO 2 - EMAIL EM MINÚSCULO

CREATE OR REPLACE FUNCTION cliente_email_minusculo()
RETURNS TRIGGER AS $$
BEGIN
    NEW.email := LOWER(NEW.email);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_cliente_email_minusculo
BEFORE INSERT OR UPDATE ON Clientes
FOR EACH ROW
EXECUTE FUNCTION cliente_email_minusculo();

-- EXERCÍCIO 3 - ESTOQUE NEGATIVO

CREATE OR REPLACE FUNCTION atualizar_estoque()
RETURNS TRIGGER AS $$
DECLARE
    v_status VARCHAR(50);
    v_estoque_atual INT;
BEGIN
    SELECT status INTO v_status
    FROM Pedidos
    WHERE id_pedido = NEW.id_pedido;

    IF v_status = 'pendente' THEN
        SELECT quant_estoque INTO v_estoque_atual
        FROM Livros
        WHERE id_livro = NEW.id_livro;

        IF v_estoque_atual < NEW.quantidade THEN
            RAISE EXCEPTION 'Estoque insuficiente para o livro %', NEW.id_livro;
        END IF;

        UPDATE Livros
        SET quant_estoque = quant_estoque - NEW.quantidade
        WHERE id_livro = NEW.id_livro;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_atualizar_estoque
AFTER INSERT ON Itens_pedido
FOR EACH ROW
EXECUTE FUNCTION atualizar_estoque();

-- EXERCÍCIO 4 - IMPEDIR EXCLUSÃO DE CLIENTES COM PEDIDOS

CREATE OR REPLACE FUNCTION cliente_verificar_delete()
RETURNS TRIGGER AS $$
BEGIN
    IF EXISTS (SELECT 1 FROM Pedidos WHERE id_cliente = OLD.id_cliente) THEN
        RAISE EXCEPTION 'Cliente não pode ser deletado pois já efetuou pedido';
    END IF;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_cliente_delete_pedido
BEFORE DELETE ON Clientes
FOR EACH ROW
EXECUTE FUNCTION cliente_verificar_delete();

-- EXERCÍCIO 5 - ATUALIZAR STATUS DO PEDIDO QUANDO TODOS ITENS FOREM ENVIADOS

CREATE OR REPLACE FUNCTION att_status_enviado()
RETURNS TRIGGER AS $$
DECLARE
    v_restantes INT;
BEGIN
    IF NEW.status_item = 'Enviado' THEN
        SELECT COUNT(*) INTO v_restantes
        FROM Itens_pedido
        WHERE id_pedido = NEW.id_pedido
          AND status_item <> 'Enviado';

        IF v_restantes = 0 THEN
            UPDATE Pedidos
            SET status = 'Concluido'
            WHERE id_pedido = NEW.id_pedido;
        END IF;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_att_status_pedido
AFTER UPDATE OF status_item ON Itens_pedido
FOR EACH ROW
EXECUTE FUNCTION att_status_enviado();

-- EXERCÍCIO 6 - RELATÓRIO DE VENDAS POR CLIENTE

CREATE OR REPLACE PROCEDURE relatorio_vendas_cliente(p_id_cliente INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_nome_cliente TEXT;
    v_total_pedidos INT;
    v_total_gasto NUMERIC(10,2);
BEGIN
    SELECT nome INTO v_nome_cliente
    FROM Clientes
    WHERE id_cliente = p_id_cliente;

    IF v_nome_cliente IS NULL THEN
        RAISE NOTICE 'Cliente com ID % não encontrado.', p_id_cliente;
        RETURN;
    END IF;

    SELECT COUNT(*) INTO v_total_pedidos
    FROM Pedidos
    WHERE id_cliente = p_id_cliente;

    SELECT COALESCE(SUM(ip.quantidade * ip.preco_unitario), 0)
    INTO v_total_gasto
    FROM Itens_pedido ip
    JOIN Pedidos p ON p.id_pedido = ip.id_pedido
    WHERE p.id_cliente = p_id_cliente;

    RAISE NOTICE 'Cliente: %', v_nome_cliente;
    RAISE NOTICE 'Total de pedidos: %', v_total_pedidos;
    RAISE NOTICE 'Valor total gasto: R$ %', v_total_gasto;
END;
$$;

-- Exemplo de uso:
CALL relatorio_vendas_cliente(1);

-- EXERCÍCIO 7 - REPOSIÇÃO DE ESTOQUE

CREATE OR REPLACE PROCEDURE repor_estoque(p_id_livro INT, p_quantidade INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_estoque_anterior INT;
BEGIN
    SELECT quant_estoque INTO v_estoque_anterior
    FROM Livros
    WHERE id_livro = p_id_livro;

    IF v_estoque_anterior IS NULL THEN
        RAISE NOTICE 'Livro com ID % não encontrado.', p_id_livro;
        RETURN;
    END IF;

    UPDATE Livros
    SET quant_estoque = quant_estoque + p_quantidade
    WHERE id_livro = p_id_livro;

    INSERT INTO Log_auditoria (tabela_afetada, id_registro_afetado, operacao, detalhes)
    VALUES (
        'Livros',
        p_id_livro,
        'REPOSICAO_ESTOQUE',
        'Estoque aumentado de ' || v_estoque_anterior || ' para ' || (v_estoque_anterior + p_quantidade)
    );

    RAISE NOTICE 'Reposição concluída com sucesso. Livro ID: %, Estoque atual: %',
                 p_id_livro, (v_estoque_anterior + p_quantidade);
END;
$$;

-- Exemplo de uso:
CALL repor_estoque(3, 10);

-- EXERCÍCIO 8 - CANCELAMENTO DE PEDIDO

CREATE OR REPLACE PROCEDURE cancelar_pedido(p_id_pedido INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_id_livro INT;
    v_quantidade INT;
    v_data_atual TIMESTAMP := NOW();
BEGIN
    UPDATE Pedidos
    SET status = 'Cancelado'
    WHERE id_pedido = p_id_pedido;

    IF NOT FOUND THEN
        RAISE NOTICE 'Pedido com ID % não encontrado.', p_id_pedido;
        RETURN;
    END IF;

    FOR v_id_livro, v_quantidade IN
        SELECT id_livro, quantidade
        FROM Itens_pedido
        WHERE id_pedido = p_id_pedido
    LOOP
        UPDATE Livros
        SET quant_estoque = quant_estoque + v_quantidade
        WHERE id_livro = v_id_livro;
    END LOOP;

    INSERT INTO Log_auditoria (tabela_afetada, id_registro_afetado, operacao, data_hora, detalhes)
    VALUES ('Pedidos', p_id_pedido, 'CANCELAMENTO_PEDIDO', v_data_atual, 'Pedido cancelado e estoque reposto.');

    RAISE NOTICE 'Pedido % cancel

-- EXERCÍCIO 9 - RANKING DE LIVROS MAIS VENDIDOS

CREATE OR REPLACE PROCEDURE ranking_livros_vendidos(p_mes INT, p_ano INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_livro RECORD;
BEGIN
    RAISE NOTICE 'Ranking de Livros Mais Vendidos - Mês: % / Ano: %', p_mes, p_ano;
    RAISE NOTICE '----------------------------------------------------';

    FOR v_livro IN
        SELECT
            l.titulo,
            l.autor,
            SUM(ip.quantidade) AS total_vendido
        FROM
            Pedidos p
        JOIN
            Itens_pedido ip ON p.id_pedido = ip.id_pedido
        JOIN
            Livros l ON ip.id_livro = l.id_livro
        WHERE
            EXTRACT(MONTH FROM p.data_pedido) = p_mes
            AND EXTRACT(YEAR FROM p.data_pedido) = p_ano
            AND p.status = 'Concluido'
        GROUP BY
            l.titulo, l.autor
        ORDER BY
            total_vendido DESC
        LIMIT 5
    LOOP
        RAISE NOTICE 'Título: %, Autor: %, Quantidade Vendida: %',
            v_livro.titulo, v_livro.autor, v_livro.total_vendido;
    END LOOP;
END;
$$;

-- Exemplo de uso:
-- CALL ranking_livros_vendidos(10, 2025);

-- CONSULTAS DE TESTE
SELECT * FROM Livros;
SELECT * FROM Clientes;
SELECT * FROM Pedidos;
SELECT * FROM Itens_pedido;
