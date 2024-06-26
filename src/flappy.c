
#include "enfeite.c"
#include "cano.c"
#include "passaro.c"

#define  QUANTIDADE_CHAO        8
#define  QUANTIDADE_ARVORES     3
#define  QUANTIDADE_PREDIOS     3
#define  QUANTIDADE_NUVENS      3

#define  QUANTIDADE_CANOS       6

class flappybird
{
    private:

        double  velocidadeJogo = -2.5;
        double  DISTANCIA_ENTRE_CANOS = 200;
        int     partidaEncerrada;
        int     contadorFimPartida;

        enfeite*    fundo;
        enfeite*    chao[QUANTIDADE_CHAO];
        enfeite*    arvores[QUANTIDADE_ARVORES];
        enfeite*    predios[QUANTIDADE_PREDIOS];
        enfeite*    nuvens[QUANTIDADE_NUVENS];
        cano*       canoSuperior[QUANTIDADE_CANOS];
        cano*       canoInferior[QUANTIDADE_CANOS];
        passaro*    passarinho;

        void encerrarPartida()
        {
            partidaEncerrada = SIM;
            contadorFimPartida = 200;
            passarinho->setVelocidadeY(0);

            for(int i=0; i<QUANTIDADE_CHAO; i++)
            {
                chao[i]->setVelocidadeX(0);
            }
            for(int i=0; i<QUANTIDADE_ARVORES; i++)
            {
                arvores[i]->setVelocidadeX(0);
            }
            for(int i=0; i<QUANTIDADE_PREDIOS; i++)
            {
                predios[i]->setVelocidadeX(0);
            }
            for(int i=0; i<QUANTIDADE_NUVENS; i++)
            {
                nuvens[i]->setVelocidadeX(0);
            }
            for(int i=0; i<QUANTIDADE_CANOS; i++)
            {
                canoSuperior[i]->setVelocidadeX(0);
                canoInferior[i]->setVelocidadeX(0);
            }
        }

        int verificarColisao(double x1, double y1, double largura1, double altura1,
                             double x2, double y2, double largura2, double altura2)
        {
            if(x1 + largura1 < x2)
            {
                return NAO;
            }
            if(x1 > x2 + largura2)
            {
                return NAO;
            }
            if(y1 + altura1 < y2)
            {
                return NAO;
            }
            if(y1 > y2 + altura2)
            {
                return NAO;
            }
            return SIM;
        }

        void aplicarColisao()
        {
            if(partidaEncerrada == NAO)
            {
                double xPassaro         = passarinho->getPosicaoX()+10;
                double yPassaro         = passarinho->getPosicaoY()+5;
                double larguraPassaro   = passarinho->getLargura()-20;
                double alturaPassaro    = passarinho->getAltura()-10;

                int colisaoSuperior     = NAO;
                int colisaoInferior     = NAO;

                for(int i=0; i<QUANTIDADE_CANOS; i++)
                {
                    /// cano superior
                    double xCanoSup         = canoSuperior[i]->getPosicaoX();
                    double yCanoSup         = canoSuperior[i]->getPosicaoY();
                    double larguraCanoSup   = canoSuperior[i]->getLargura();
                    double alturaCanoSup    = canoSuperior[i]->getAltura();
                    colisaoSuperior         = verificarColisao(xPassaro, yPassaro, larguraPassaro, alturaPassaro,
                                                               xCanoSup, yCanoSup, larguraCanoSup, alturaCanoSup);

                    /// cano inferior
                    double xCanoInf         = canoInferior[i]->getPosicaoX();
                    double yCanoInf         = canoInferior[i]->getPosicaoY();
                    double larguraCanoInf   = canoInferior[i]->getLargura();
                    double alturaCanoInf    = canoInferior[i]->getAltura();
                    colisaoInferior         = verificarColisao(xPassaro, yPassaro, larguraPassaro, alturaPassaro,
                                                               xCanoInf, yCanoInf, larguraCanoInf, alturaCanoInf);

                    if(colisaoSuperior == SIM || colisaoInferior == SIM)
                    {
                        encerrarPartida();

                        /// encerrar partida

                        break;
                    }
                }

                if(yPassaro < 75 || yPassaro + alturaPassaro > ALT_TELA)
                {
                    encerrarPartida();
                }
            }
        }

        void alocarPassaroCanos()
        {
            for(int i=0; i<QUANTIDADE_CANOS; i++)
            {
                int variacao = (rand()%401) - 200;

                canoSuperior[i] = new cano(0.8*LARG_TELA + (DISTANCIA_ENTRE_CANOS+86)*i, ALT_TELA/2.0 + 100 + variacao,
                                           86, 836,
                                           velocidadeJogo, "imagens//cano.png");

                canoInferior[i] = new cano(0.8*LARG_TELA + (DISTANCIA_ENTRE_CANOS+86)*i, ALT_TELA/2.0 - 836 - 100 + variacao,
                                           86, 836,
                                           velocidadeJogo, "imagens//cano.png");
            }
            passarinho = new passaro(300,300,54,46,0,0,"imagens\\flap1.png","imagens\\flap2.png","imagens\\flap3.png");
        }

    public:

        flappybird()
        {
            partidaEncerrada = NAO;

            fundo = new enfeite(0,0,LARG_TELA,ALT_TELA,0,0,"imagens//fundo.png");
            for(int i=0; i<QUANTIDADE_CHAO; i++)
            {
                chao[i] = new enfeite(209*i,0,209,75,velocidadeJogo,0,"imagens//chao.png");
            }
            for(int i=0; i<QUANTIDADE_ARVORES; i++)
            {
                arvores[i] = new enfeite(959*i,75,959,52,0.5*velocidadeJogo,0,"imagens//arvores.png");
            }
            for(int i=0; i<QUANTIDADE_PREDIOS; i++)
            {
                predios[i] = new enfeite(960*i,105,960,54,0.15*velocidadeJogo,0,"imagens//predios.png");
            }
            for(int i=0; i<QUANTIDADE_NUVENS; i++)
            {
                nuvens[i] = new enfeite(959*i,105,960,114,0.1*velocidadeJogo,0,"imagens//nuvens.png");
            }
            alocarPassaroCanos();
        }

        ~flappybird()
        {
            delete passarinho;

            for(int i=0; i<QUANTIDADE_CANOS; i++)
            {
                delete canoSuperior[i];
                delete canoInferior[i];
            }

            delete fundo;
            for(int i=0; i<QUANTIDADE_NUVENS; i++)
            {
                delete nuvens[i];
            }

            for(int i=0; i<QUANTIDADE_PREDIOS; i++)
            {
                delete predios[i];
            }

            for(int i=0; i<QUANTIDADE_CHAO; i++)
            {
                delete chao[i];
            }

            for(int i=0; i<QUANTIDADE_ARVORES; i++)
            {
                delete arvores[i];
            }
        }

        void atualizar()
        {
            if(partidaEncerrada == SIM)
            {
                contadorFimPartida = contadorFimPartida - 1;
                if(contadorFimPartida == 0)
                {
                    reiniciarPartida();
                }
            }

            double yPassaro = passarinho->getPosicaoY();
            if(yPassaro > 60)
            {
                passarinho->atualizar();
            }

            for(int i=0; i<QUANTIDADE_CANOS; i++)
            {
                canoSuperior[i]->movimentar();
                canoInferior[i]->movimentar();

                int variacao = (rand()%401) - 200;

                canoSuperior[i]->verificarReset(QUANTIDADE_CANOS*(86+DISTANCIA_ENTRE_CANOS),
                                                100+variacao);


                canoInferior[i]->verificarReset(QUANTIDADE_CANOS*(86+DISTANCIA_ENTRE_CANOS),
                                                -100-836+variacao);
            }

            aplicarColisao();

            for(int i=0; i<QUANTIDADE_CHAO; i++)
            {
                chao[i]->movimentar();
                chao[i]->verificarReset(QUANTIDADE_CHAO*209);
            }

            for(int i=0; i<QUANTIDADE_ARVORES; i++)
            {
                arvores[i]->movimentar();
                arvores[i]->verificarReset(QUANTIDADE_ARVORES*959);
            }

            for(int i=0; i<QUANTIDADE_PREDIOS; i++)
            {
                predios[i]->movimentar();
                predios[i]->verificarReset(QUANTIDADE_PREDIOS*960);
            }

            for(int i=0; i<QUANTIDADE_NUVENS; i++)
            {
                nuvens[i]->movimentar();
                nuvens[i]->verificarReset(QUANTIDADE_NUVENS*959);
            }
        }

        void desenhar()
        {
            fundo->desenhar();

            for(int i=0; i<QUANTIDADE_NUVENS; i++)
            {
                nuvens[i]->desenhar();
            }

            for(int i=0; i<QUANTIDADE_PREDIOS; i++)
            {
                predios[i]->desenhar();
            }

            for(int i=0; i<QUANTIDADE_ARVORES; i++)
            {
                arvores[i]->desenhar();
            }

//            double xPassaro         = passarinho->getPosicaoX()+10;
//            double yPassaro         = passarinho->getPosicaoY()+5;
//            double larguraPassaro   = passarinho->getLargura()-20;
//            double alturaPassaro    = passarinho->getAltura()-10;
//            PIG_desenharRetangulo(xPassaro, yPassaro, larguraPassaro, alturaPassaro, VERMELHO, NAO, SIM);
            passarinho->desenhar();

            for(int i=0; i<QUANTIDADE_CANOS; i++)
            {
                canoSuperior[i]->desenhar(0);
                canoInferior[i]->desenhar(180);
            }

            for(int i=0; i<QUANTIDADE_CHAO; i++)
            {
                chao[i]->desenhar();
            }
        }

        void verificarPulo()
        {
            if(PIG_tecla == TECLA_BARRAESPACO)
            {
                if(partidaEncerrada == NAO)
                {
                    passarinho->aplicarPulo();
                }
            }
        }

        void reiniciarPartida()
        {
            partidaEncerrada = NAO;

            delete passarinho;
            for(int i=0; i<QUANTIDADE_CANOS; i++)
            {
                delete canoSuperior[i];
                delete canoInferior[i];
            }

            alocarPassaroCanos();

            for(int i=0; i<QUANTIDADE_CHAO; i++)
            {
                chao[i]->setVelocidadeX(velocidadeJogo);
            }
            for(int i=0; i<QUANTIDADE_ARVORES; i++)
            {
                arvores[i]->setVelocidadeX(velocidadeJogo);
            }
            for(int i=0; i<QUANTIDADE_PREDIOS; i++)
            {
                predios[i]->setVelocidadeX(velocidadeJogo);
            }
            for(int i=0; i<QUANTIDADE_NUVENS; i++)
            {
                nuvens[i]->setVelocidadeX(velocidadeJogo);
            }
            for(int i=0; i<QUANTIDADE_CANOS; i++)
            {
                canoSuperior[i]->setVelocidadeX(velocidadeJogo);
                canoInferior[i]->setVelocidadeX(velocidadeJogo);
            }
        }
};












