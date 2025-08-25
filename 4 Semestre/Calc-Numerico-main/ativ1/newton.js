function newtonMethod(f, df, x0, toler, iterMax) {
    let x = x0;
    let iter = 0;
    let condErro = 1;
    
    console.log(`Iteração: ${iter}, x: ${x}, f(x): ${f(x)}, f'(x): ${df(x)}`);
    
    while (iter < iterMax) {
        let fx = f(x);
        let dfx = df(x);
        
        if (dfx === 0) {
            console.log("Derivada zero, método não pode continuar.");
            break;
        }
        
        let deltaX = -fx / dfx;
        x += deltaX;
        iter++;
        
        console.log(`Iteração: ${iter}, x: ${x}, f(x): ${f(x)}, f'(x): ${df(x)}, DeltaX: ${deltaX}`);
        
        if (Math.abs(deltaX) <= toler && Math.abs(fx) <= toler) {
            condErro = 0;
            break;
        }
    }
    
    return { raiz: x, iter, condErro };
}

function f(x) {
    return x ** 3 - 4 * x - 9; // Exemplo: encontrar raiz de x^2 - 4 = 0
}

function df(x) {
    return 3 * x ** 2 - 4; // Derivada da função acima
}

let resultado = newtonMethod(f, df, 2, 0.0001, 5);
console.log("Resultado:", resultado);
