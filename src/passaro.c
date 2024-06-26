

class passaro
{
    private:

        int sprite[3];

        int contadorAnimacao;
        int indiceFrameAtual;

        double posicaoX, posicaoY;
        double largura, altura;
        double velocidadeY;
        double angulo;

        void atualizarAnimacao()
        {
            contadorAnimacao = contadorAnimacao + 1;
            if(contadorAnimacao > 10)
            {
                contadorAnimacao = 0;
                indiceFrameAtual = indiceFrameAtual + 1;
                if(indiceFrameAtual >= 3)
                {
                    indiceFrameAtual = 0;
                }
            }
        }

        void aplicarGravidade()
        {
            double aceleracaoGravidade = -0.2;

            velocidadeY = velocidadeY   + aceleracaoGravidade;
            posicaoY    = posicaoY      + velocidadeY;
        }

        void atualizarAngulo()
        {
            if(angulo >= -90)
            {
                angulo = angulo - 0.8;
            }
        }

    public:

    passaro(double px, double py,
            double larguraSprite, double alturaSprite,
            double vy, double anguloRosto,
            char* animacaoFrame1, char* animacaoFrame2, char* animacaoFrame3)
    {
        posicaoX        = px;
        posicaoY        = py;
        velocidadeY     = vy;
        angulo          = anguloRosto;
        largura         = larguraSprite;
        altura          = alturaSprite;

        contadorAnimacao = 0;
        indiceFrameAtual = 0;

        sprite[0]       = PIG_criarSprite(animacaoFrame1, 0);
        sprite[1]       = PIG_criarSprite(animacaoFrame2, 0);
        sprite[2]       = PIG_criarSprite(animacaoFrame3, 0);
    }

    ~passaro()
    {
        PIG_destruirSprite(sprite[0]);
        PIG_destruirSprite(sprite[1]);
        PIG_destruirSprite(sprite[2]);
    }

    void aplicarPulo()
    {
        angulo = 20;
        velocidadeY = 6;
        //velocidadeY = velocidadeY + 10;
    }

    void atualizar()
    {
        atualizarAnimacao();
        atualizarAngulo();
        aplicarGravidade();
    }

    void desenhar()
    {
        PIG_desenharSprite(sprite[indiceFrameAtual], posicaoX, posicaoY, largura, altura, angulo, NAO, BRANCO, 255, SIM);
    }

    double getPosicaoX()
    {
        return posicaoX;
    }

    double getPosicaoY()
    {
        return posicaoY;
    }

    double getLargura()
    {
        return largura;
    }

    double getAltura()
    {
        return altura;
    }

    void setVelocidadeY(double valor)
    {
        velocidadeY = valor;
    }

};
