CREATE TABLE Funcionario (ID serial primary key, nome text, salario numeric (10,2));

CREATE TABLE Funcionario_log (ID serial primary key,id_funcionario int, novo_salario numeric (10,2), data_alteracao TIMESTAMPTZ NOT NULL DEFAULT now());

CREATE TABLE Funcionario_mail (id serial primary key,id_funcionario int, nome text, data_inclusao TIMESTAMPTZ NOT NULL DEFAULT now(), enviado boolean NOT NULL DEFAULT false);

insert into Funcionario (nome, salario)
values ('saldanha', 1000)
	   ,('maria', 10000)
	   ,('jorge', 5000)
	   
insert into Funcionario (nome, salario)
values ('luiz', 3000)

insert into Funcionario (nome, salario)
values ('isa', 4500)

insert into Funcionario (nome, salario)
values ('carlos', 0)

CREATE OR REPLACE FUNCTION f_log_func() 
RETURNS TRIGGER AS $$ 
BEGIN 
  INSERT INTO Funcionario_log      (id_funcionario, novo_salario, data_alteracao, antigo_salario) 
  VALUES (new.id, new.salario, now(), old.salario); 
RETURN NEW; 
END; $$ LANGUAGE plpgsql;


CREATE TRIGGER g_logfunc
AFTER UPDATE
ON Funcionario
FOR EACH ROW
WHEN (old.salario<>new.salario)
EXECUTE FUNCTION f_log_func();

alter table Funcionario_log add column antigo_salario numeric

-- Exercicio 2
CREATE OR REPLACE FUNCTION f_log_func_email() 
RETURNS TRIGGER AS $$ 
BEGIN 
  INSERT INTO Funcionario_mail     (id_funcionario, nome, data_inclusao, enviado) 
  VALUES (new.id, new.nome, now(), false); 
RETURN NEW; 
END; $$ LANGUAGE plpgsql;

CREATE TRIGGER trg_func_email
AFTER INSERT ON Funcionario
FOR EACH ROW
EXECUTE FUNCTION f_log_func_email();
-- Fim exercicio 2

-- Exercicio 3
CREATE OR REPLACE FUNCTION f_log_func_delete() 
RETURNS TRIGGER AS $$ 
BEGIN 
  IF EXISTS (SELECT 1 FROM Funcionario_log where id_funcionario = OLD.id)
  then RAISE EXCEPTION 'Não é permitido excluir funcionário com alterações de salário registradas no log.';
  END IF;
RETURN OLD; 
END; $$ LANGUAGE plpgsql;

CREATE TRIGGER trg_bloqueia_delete_func
BEFORE DELETE ON Funcionario
FOR EACH ROW
EXECUTE FUNCTION f_log_func_delete();

DELETE FROM Funcionario WHERE id = 1;
-- Fim exercicio 3

-- Exércicio 4

-- Fim exércicio 4

-- Exércicio 5
CREATE OR REPLACE FUNCTION f_log_func_insert_null()
RETURNS TRIGGER AS $$
BEGIN
  IF NEW.salario IS NULL OR NEW.salario = 0 THEN
    RAISE EXCEPTION 'Não é permitido inserir salário nulo ou 0.';
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_bloqueia_insert_func
BEFORE INSERT ON Funcionario
FOR EACH ROW
EXECUTE FUNCTION f_log_func_insert_null();
--

CREATE OR REPLACE FUNCTION f_log_func_delete_3()
RETURNS TRIGGER AS $$
DECLARE
  qtd_atualizacoes INTEGER;
BEGIN
  SELECT COUNT(*) INTO qtd_atualizacoes
  FROM Funcionario_log
  WHERE id_funcionario = OLD.id;

  IF qtd_atualizacoes >= 3 THEN
    RAISE EXCEPTION 'Não é permitido excluir funcionário com 3 ou mais alterações de salário registradas no log.';
  END IF;

  RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_bloqueia_delete_func_3
BEFORE DELETE ON Funcionario
FOR EACH ROW
EXECUTE FUNCTION f_log_func_delete_3();
-- Fim exércicio 5

-- Exércicio 6

-- Fim exércicio 6
update Funcionario set salario = 3500 where id = 1

select fl.id, f.nome, fl.novo_salario, fl.data_alteracao
from funcionario_log fl inner join funcionario f on (f.id = fl.id_funcionario)

select * from funcionario

select * from funcionario_log

select * from funcionario_mail
