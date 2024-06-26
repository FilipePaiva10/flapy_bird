

class cano
{
    private:

        int sprite;
        double posicaoX, posicaoY;
        double velocidadeX;
        double larguraSprite, alturaSprite;

    public:

    cano(double px, double py, double largura, double altura,
         double vx, char* caminhoSprite)
    {
        sprite          = PIG_criarSprite(caminhoSprite, 0);

        posicaoX        = px;
        posicaoY        = py;
        velocidadeX     = vx;
        larguraSprite   = largura;
        alturaSprite    = altura;
    }

    ~cano()
    {
        PIG_destruirSprite(sprite);
    }

    void movimentar()
    {
        posicaoX = posicaoX + velocidadeX;
    }

    void verificarReset(double valor, double valorAbertura)
    {
        if(posicaoX + larguraSprite < 0)
        {
            posicaoX = posicaoX + valor;
            posicaoY = ALT_TELA/2.0 + valorAbertura;
        }
    }

    void desenhar(double angulo)
    {
        PIG_desenharSprite(sprite, posicaoX, posicaoY, larguraSprite, alturaSprite,
                           angulo, NAO, BRANCO, 255, SIM);
    }

    void setVelocidadeX(double valor)
    {
        velocidadeX = valor;
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
        return larguraSprite;
    }

    double getAltura()
    {
        return alturaSprite;
    }
};
