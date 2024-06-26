#include "PIG.h"
#include "flappy.c"

int main(int argc, char* args[])
{
    PIG_criarJanela("Janela", 1366, 768);
    int timerGeral = PIG_criarTimer();

    /// enfeites

    flappybird* flappy = new flappybird();

    while(PIG_jogoRodando() == SIM)
    {
        PIG_atualizarJanela();
        flappy->verificarPulo();

        if(PIG_tecla == TECLA_ENTER)
        {
            flappy->reiniciarPartida();
        }

        if(PIG_tempoDecorrido(timerGeral) > 0.01)
        {
            PIG_atualizarCamera();

            flappy->atualizar();

            PIG_iniciarDesenho();
            flappy->desenhar();
            PIG_encerrarDesenho();

            PIG_reiniciarTimer(timerGeral);
        }
    }

    delete flappy;

    PIG_destruirTimer(timerGeral);

    PIG_finalizarJanela();

    return 0;
}


