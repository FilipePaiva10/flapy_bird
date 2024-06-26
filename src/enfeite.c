
class enfeite
{
    private:

        int sprite;
        double posicaoX, posicaoY;
        double velocidadeX, velocidadeY;
        double larguraSprite, alturaSprite;

    public:

        enfeite(double px, double py, double largura, double altura,
                double vx, double vy, char* caminhoSprite)
        {
            sprite          = PIG_criarSprite(caminhoSprite, 0);

            posicaoX        = px;
            posicaoY        = py;
            velocidadeX     = vx;
            velocidadeY     = vy;
            larguraSprite   = largura;
            alturaSprite    = altura;
        }

        ~enfeite()
        {
            PIG_destruirSprite(sprite);
        }

        void movimentar()
        {
            posicaoX = posicaoX + velocidadeX;
        }

        void verificarReset(double valor)
        {
            if(posicaoX + larguraSprite < 0)
            {
                posicaoX = posicaoX + valor;
            }
        }

        void desenhar()
        {
            PIG_desenharSprite(sprite, posicaoX, posicaoY, larguraSprite, alturaSprite,
                               0, NAO, BRANCO, 255, SIM);
        }

        void setVelocidadeX(double valor)
        {
            velocidadeX = valor;
        }

};
