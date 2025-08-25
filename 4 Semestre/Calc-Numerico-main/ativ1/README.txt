Medidas:
Altura 17,25 cm
Raio 3,5 cm
Diametro 7 cm
200 ml de água
2,9 cm de água

Bisseção

1. Inicialização

A função bisectionMethod(f, a, b, toler, iterMax) recebe:

f: a função a ser analisada.

a e b: extremos do intervalo inicial.

toler: tolerância para o critério de parada.

iterMax: número máximo de iterações.

Calcula fa = f(a) e fb = f(b).

Se fa * fb > 0, significa que não há mudança de sinal → não há raiz garantida no intervalo, e a função retorna um erro.

--

2. Laço principal (método da bisseção)

O ponto médio 𝑥 do intervalo é calculado:

x = (a+b) / 2

Calcula fx = f(x).

Exibe no console os valores atuais dos limites, x, fx e deltaX.

--

3. Critérios de Parada

Se deltaX e |fx| forem menores ou iguais à tolerância OU se o número máximo de iterações for atingido, o laço para e raiz recebe x.

--

4. Atualização do intervalo

Se fa * fx > 0, significa que fa e fx têm o mesmo sinal → a raiz não está no intervalo [a,x], então atualiza a = x e fa = fx.

Caso contrário, a raiz está em [x,b], então apenas b = x.

deltaX é atualizado (deltaX /= 2).

Incrementa o contador de iterações.

--

5. Verificação final

Se a precisão foi alcançada, condErro recebe 0 (indica sucesso), caso contrário, mantém 1 (indica erro ou parada por iteração máxima)

-----

Newton Raphson

1. A Função newtonMethod

Essa função recebe os seguintes parâmetros:

f: a função cuja raiz queremos encontrar.

df: a derivada de f, usada para calcular o próximo valor de x.

x0: a estimativa inicial para a raiz.

toler: a tolerância para a precisão da raiz.

iterMax: o número máximo de iterações permitidas.

O algoritmo funciona assim: 

1-Inicializa x com o valor inicial x0.
2-Entra em um loop até atingir o número máximo de iterações (iterMax).
3- Calcula o valor da função f(x) e sua derivada df(x).
4-Se a derivada for zero (df(x) == 0), o método para, pois dividir por zero não é possível.
5-Calcula o próximo valor de x com a fórmula do método de Newton.
6-Se o deslocamento Δx e f(x) forem menores que a tolerância, o algoritmo para.
7-Retorna o valor final de x, o número de iterações e uma variável de controle de erro.

--
2. A Função f(x)
A função que queremos encontrar a raiz:

f(x)=x³−4x−9
--
3. A Função df(x)
A derivada de f(x), necessária para o cálculo do método de Newton:

f′(x)=3x²−4
--
4. Execução do Algoritmo

O código executa o método de Newton-Raphson com:
Estimativa inicial x0 = 2

Tolerância 0.0001

Máximo de 5 iterações.

O resultado final é exibido no console.
