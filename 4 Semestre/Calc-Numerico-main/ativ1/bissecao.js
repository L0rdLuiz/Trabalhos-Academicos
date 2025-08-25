function bisectionMethod(f, a, b, toler, iterMax) {
    let fa = f(a);
    let fb = f(b);
    let iter = 0;
    let condErro = 1;
    let raiz = null;
    
    if (fa * fb > 0) {
        console.log("Função não muda de sinal nos extremos do intervalo dado");
        return { raiz, iter, condErro };
    }
    
    let deltaX = Math.abs(b - a) / 2;
    
    while (true) {
        let x = (a + b) / 2;
        let fx = f(x);
        console.log(`Iter: ${iter}, a: ${a}, Fa: ${fa}, b: ${b}, Fb: ${fb}, x: ${x}, Fx: ${fx}, DeltaX: ${deltaX}`);
        
        if ((deltaX <= toler && Math.abs(fx) <= toler) || iter >= iterMax) {
            raiz = x;
            break;
        }
        
        if (fa * fx > 0) {
            a = x;
            fa = fx;
        } else {
            b = x;
        }
        
        deltaX /= 2;
        iter++;
    }
    
    if (deltaX <= toler && Math.abs(f(raiz)) <= toler) {
        condErro = 0;
    }
    
    return { raiz, iter, condErro };
}

function exemploFuncao(x) {
    return (x * x * x) - (4 * x) + 1;
}

let resultado = bisectionMethod(exemploFuncao, 0, 1, 0.01, 10);
console.log(resultado);