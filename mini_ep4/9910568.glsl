// NUSP: 9910568

// Digite aqui seu código GLSL para gerar uma imagem
// O GLSL é muito próximo do C, mas não é idêntico.

// Essa linha vai definir a precisão do float,
// e mediump é bom o bastante no momento.
precision mediump float;

// Aqui não tem conversão automática entre int e float
// Então coloque .0 quando precisar de floats

// As janelas tem um tamanho fixo de 3000x3000
#define WIDTH (3000.0)
#define HEIGHT (3000.0)

// Constantes do limite do plano cartesiano
#define Xi (-1.0)
#define Xj (+1.0)
#define Yi (-1.0)
#define Yj (+1.0)

#define Xd (Xj - Xi)
#define Yd (Yj - Yi)


// diferente do código em JS
// a GPU roda essa função main para cada pixel
void main() {
    // Aqui o pixel é guardado num vetor de 4 floats
    // Também segue o formato RGBA, mas dessa vez
    // os campos variam de 0.0 a 1.0

    // vamos obter as coordenadas do plano a partir da
    // variável gl_FragCoord que é pré definida para cada pixel
    vec2 xy = (gl_FragCoord.xy / vec2(WIDTH, HEIGHT) * vec2(Xd, Yd)) + vec2(Xi, Yi);

    // Para acessa o x ou o y individualmente é só usar
    // xy.x e xy.y respectivamente
    float x = xy.x;
    float y = xy.y;

    //****************************
    //compute a cor do pixel aqui


    float zx, zy;
    float zx_novo, zy_novo;
    int steps = 255;
    for(int i = 0; i < 255; i++) {
        zx_novo = zx*zx - zy*zy + x;
        zy_novo = 2.0*zx*zy + y;
        zx = zx_novo;
        zy = zy_novo;
    
        if(zx*zx+zy*zy > 4.0) {
            steps = i;
            break;
        }
    }

    // define cor com base no steps
    float max_b, max_g, max_r;
    float min_b, min_g, min_r;
    float min_steps, max_steps;
    if( steps < 10 ) {
        // porcentagem
        min_steps = 0.0;
        max_steps = 10.0;
        max_r = 32.0;
        min_r = 0.0;
        max_g = 107.0;
        min_g = 7.0;
        max_b = 203.0;
        min_b = 100.0;

    }
    else if(steps < 80 ) {
        min_steps = 10.0;
        max_steps = 80.0;
        max_r = 237.0;
        min_r = 32.0;
        max_g = 255.0;
        min_g = 107.0;
        max_b = 255.0;
        min_b = 203.0;
    }
    else if(steps < 150) {
        min_steps = 80.0;
        max_steps = 150.0;
        max_r = 255.0;
        min_r = 237.0;
        max_g = 170.0;
        min_g = 255.0;
        max_b = 0.0;
        min_b = 255.0;
    }
    else if(steps < 200) {
        min_steps = 150.0;
        max_steps = 200.0;
        max_r = 100.0;
        min_r = 255.0;
        max_g = 120.0;
        min_g = 170.0;
        max_b = 0.0;
        min_b = 0.0;
    }
    else if(steps <= 255) {
        min_steps = 200.0;
        max_steps = 255.0;
        max_r = 0.0;
        min_r = 100.0;
        max_g = 0.0;
        min_g = 120.0;
        max_b = 0.0;
        min_b = 0.0;
    }

    float p = (float(steps)-min_steps)/(max_steps-min_steps);
    float red = (sqrt(min_r*min_r*(1.0 - p) + max_r*max_r*p))/255.0;
    float green = (sqrt(min_g*min_g*(1.0 - p) + max_g*max_g*p))/255.0;
    float blue = (sqrt(min_b*min_b*(1.0 - p) + max_b*max_b*p))/255.0;

    //*****************************
    // Aplica a cor
    gl_FragColor = vec4(red, green, blue, 1.0);
}

// Clique em Run GLSL para rodar o código ;)