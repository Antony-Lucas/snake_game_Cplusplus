#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>

int main(){

    //variáveis gerais
    int i, gp=0, gd, gm, d = 2;
    char buffer[16] = {0};
    //variáveis do cenário
    int s=16, gs=700, xs = 1350;

    //variáveis da cobra
    int x[100], y[100], l;

    //variáveis da comida;
    int rx, ry;

    srand(time(NULL));//usado pra gerar números aleatórios.
    detectgraph(&gd,&gm);//detecta o adaptador grafico do sistema.
    initgraph(&gd,&gm,NULL);//inicializa o sistema grafico para renderizar os elementos na tela.
    initwindow(1540, 720, "snake_game_by_AntonyLucas");//iniciar e definir a largura e altura da tela

    outtextxy(1360, 50, "use as setas direcionais");
    outtextxy(1360, 70, "para mover");

    setfillstyle(1, 10); //define o tipo de linha e a cor (tipo, cor).

    /*cenário - cada barra utiliza quatro parâmetros.
    O conjunto das variáveis é usado para calcular a largura e altura que as barras irão ter
    em relação ao tamanho da viewpor, usando bar(int,int,int,int)). */
    //
    bar(s-s/2,s-s/2,(s/2)+s*(xs/s), s+s/2); //barra superior
    bar(s-s/2,(-s/2)+s*(gs/s),(s/2)+s*(xs/s),(s/2)+s*(gs/s)); //barra inferior
    bar(s-s/2,s-s/2,s+s/2,(s/2)+s*(s*2.68)); //barra esquerda
    bar((-s/2)+s*(xs/s),s-s/2,(s/2)+s*(xs/s),(s/2)+s*(gs/s)); //barra direita
    //

    //cobra
    x[0] = s*(xs/(2*s));//eixos x
    y[0] = s*(gs/(2*s));//eixo y

    setfillstyle(1, 14);//cor e tipo da cobra(barra amarela).
    bar(x[0]-s/2,y[0]-s/2,x[0]+s/2,y[0]+s/2);//renderização da cobra.

    l = 5; //tamanho incial da cobra
    for(i = 1; i < l; i++){
        x[i] = x[0]-(i*s);
        y[i] = y[0];

        bar(x[i]-s/2,y[i]-s/2,x[i]+s/2,y[i]+s/2);
    }
    //

    //comida
    rx = s;
    ry = s;

    setfillstyle(1, 12); //cor e tipo da comida(ponto vermelho).
    while(getpixel(rx, ry)!= 0){
        rx = s*(1+rand()%(xs/s-1));
        ry = s*(1+rand()%(gs/s-1));
    }//renderiza a comida de forma aleatória a cada inicialização usando a funcao rand.
    bar(rx-s/2,ry-s/2,rx+s/2,ry+s/2);
    delay(2000);//faz com que a barra seja atualizada a cada 2000 milisegundos
    //
    //movimentação
    while(1){
        setfillstyle(1,0);
        bar(x[l-1]-s/2,y[l-1]-s/2,x[l-1]+s/2,y[l-1]+s/2);
        for(i = l; i > 0; i--){
            x[i] = x[i-1];
            y[i] = y[i-1];
        }//ataualização da cobra a cada vez que ela pegar a comida

        if(d == 0){
            x[0] = x[0]-s;
        } else if(d == 1){
            y[0] = y[0]-s;
        } else if( d == 2){
            x[0] = x[0]+s;
        } else if(d == 3){
            y[0] = y[0]+s;
        } //atualiza o tamanho da cobra

        if(getpixel(x[0], y[0])== 10){
            outtextxy(600, 350, "voce morreu ");
            delay(100000);
        } //se a cobra colidir com alguma barra ela morre

        if(GetAsyncKeyState(VK_RIGHT)&&d != 0){
            d = 2;
        }else if(GetAsyncKeyState(VK_UP)&&d != 3){
            d = 1;
        }else if(GetAsyncKeyState(VK_LEFT)&&d != 2){
            d = 0;
        }else if(GetAsyncKeyState(VK_DOWN)&&d != 1){
            d = 3;
        }//movimentação da cobra pelo teclado

        if(getpixel(x[0],y[0])== 12){//pegou a comida?
            rx = s;
            ry = s;
            gp = gp + 1;
            setfillstyle(1, 12);
            while(getpixel(rx, ry)!= 0){
                rx = s*(1+rand()%(xs/s-1));
                ry = s*(1+rand()%(gs/s-1));
            }
            bar(rx-s/2,ry-s/2,rx+s/2,ry+s/2);
            l = l+1;
        }

        itoa(gp, buffer, 10); // converter int pra char
        outtextxy(1360, 250, "pontuacao: ");
        outtextxy(1460, 250, buffer);

        setfillstyle(1,14);
        for(i = 0; i < l; i++){
            bar(x[i]-s/2, y[i]-s/2, x[i]+s/2,y[i]+s/2);
        }
        delay(100);// velocidade da cobra
    }
    while(!GetAsyncKeyState(VK_RETURN))
    closegraph();
    //
    getch();//funcao parar ler um caractere do teclado da lib graphics.h.
    return 0;
}

/*
Desenvolvido por Antony Lucas
fontes:
https://stackoverflow.com/questions/20313534/how-to-use-graphics-h-in-codeblocks
https://jmeubank.github.io/tdm-gcc/
https://blog.csdn.net/F_hawk189/article/details/80681819 C语言graphics.h的使用
https://blog.csdn.net/CSUstudent007/article/details/79162449
https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
https://home.cs.colorado.edu/~main/bgi/doc/

*/
