// NUSP: 9910568

// Digite aqui seu código JS para gerar uma imagem

// As janelas tem um tamanho fixo de 3000x3000
const WIDTH = 3000;
const HEIGHT = 3000;

// Constantes do limite o plano cartesiano
const Xi = -1.0;
const Xj = +1.0;
const Yi = -1.0;
const Yj = +1.0;

const Xd = Xj - Xi;
const Yd = Yj - Yi;

const main = (data) => {
    //Data é um array de bytes que representa a imagem
    //O valor mínimo é 0 e o máximo é 255
    //A cada 4 bytes temos um pixel
    //Red Green Blue Alpha

    //Vamos usar o for para percorrer cada pixel
    for(let i = 0; i < data.length; i += 4) {
        const _x = Math.floor((i/4) % 3000);
        const _y = Math.floor((i/4) / 3000);

        //converte para um plano cartesiano indo de Xi-Xj e Yi-Yj.
        const x = Xi + (_x/WIDTH) * Xd;
        const y = Yj - (_y/HEIGHT) * Yd;

        //****************************
        //compute a cor do pixel aqui

        let zx = 0, zy = 0;
        let steps = 0;
        for(steps = 0; steps < 255; steps++) {
            let zx_novo = zx*zx - zy*zy + x;
            let zy_novo = 2*zx*zy + y;
            zx = zx_novo;
            zy = zy_novo;
        
            if((zx*zx + zy*zy )> 4) {
                break;
            }
        }
        // define cor com base no steps
        let max_b, max_g, max_r;
        let min_b, min_g, min_r;
        let min_steps, max_steps;
        if( steps < 10 ) {
            // porcentagem
            min_steps = 0;
            max_steps = 10;
            max_r = 32;
            min_r = 0;
            max_g = 107;
            min_g = 7;
            max_b = 203;
            min_b = 100;

        }
        else if(steps < 80 ) {
            min_steps = 10;
            max_steps = 80;
            max_r = 237;
            min_r = 32;
            max_g = 255;
            min_g = 107;
            max_b = 255;
            min_b = 203;
        }
        else if(steps < 150) {
            min_steps = 80;
            max_steps = 150;
            max_r = 255;
            min_r = 237;
            max_g = 170;
            min_g = 255;
            max_b = 0;
            min_b = 255;
        }
        else if(steps < 200) {
            min_steps = 150;
            max_steps = 200;
            max_r = 100;
            min_r = 255;
            max_g = 120;
            min_g = 170;
            max_b = 0;
            min_b = 0;
        }
        else if(steps <= 255) {
            min_steps = 200;
            max_steps = 255;
            max_r = 0;
            min_r = 100;
            max_g = 0;
            min_g = 120;
            max_b = 0;
            min_b = 0;
        }

        let p = (steps-min_steps)/(max_steps-min_steps);
        const red = Math.sqrt(min_r*min_r*(1 - p) + max_r*max_r*p);
        const green = Math.sqrt(min_g*min_g*(1 - p) + max_g*max_g*p);
        const blue = Math.sqrt(min_b*min_b*(1 - p) + max_b*max_b*p);

        //*****************************
        
        //define a cor do pixel
        data[i]   = red;
        data[i+1] = green;
        data[i+2] = blue;
        data[i+3] = 255;
    }
};

// O nome da função a ser executada retornada deve aparecer no final
// clique em Run JS e aguarde um pouco para o seu código executar
main