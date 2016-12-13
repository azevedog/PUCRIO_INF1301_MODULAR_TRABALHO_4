/***************************************************************************
*  $MCI Módulo de implementação: MAIN	modulo para jogar jogo de xadrez
*
*  Arquivo gerado:              MAIN.c
*  Letras identificadoras:      MAIN
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data       Observações
*     2       mmq     16/nov/2016  correcao de bugs
*     1       fpf     08/nov/2016  início da implementação
*
***************************************************************************/

#include <stdio.h>
#include <string.h>

#include "TABULEIRO.H"
#include "JOGO.H"

int main(int argc, char *argv[])
{
	char coordOrigem[4];
	char coordDestino[4];

	char jogBrancas[20];
	char jogPretas[20];

	TAB_tppTabuleiro pTabuleiro = NULL;

	TAB_CriarTabuleiro(&pTabuleiro);

	JOGO_MontaTabuleiro(pTabuleiro, argv[1]);

	printf("Nome do jogador das pecas brancas:\n");
	scanf("%s", jogBrancas);

	printf("Nome do jogador das pecas pretas:\n");
	scanf("%s", jogPretas);

	JOGO_RecebeJogadores(jogBrancas, jogPretas);

	JOGO_IniciaJogo();

	if( jogoRodando )
	{
		JOGO_MostraTabuleiro( pTabuleiro );
	}
	
	while( jogoRodando )
	{
		printf( "Jogador %s, realize sua jogada (coord origem, coord destino) ou FIM para terminar:\n", ( jogCorr=='B' ) ? jogadorB : jogadorP );
		scanf( "%s", coordOrigem );
		if (strcmp(coordOrigem, "FIM") == 0)
		{
			strcpy(coordDestino, coordOrigem);
		}
		else
		{
			scanf("%s", coordDestino);
		}		

		JOGO_RecebeJogada( pTabuleiro, coordOrigem, coordDestino );
		JOGO_MostraTabuleiro( pTabuleiro );

		JOGO_ChequeMate(pTabuleiro, (jogCorr == 'B') ? jogadorP : jogadorB);
		JOGO_ChequeMate(pTabuleiro, (jogCorr == 'B') ? jogadorB : jogadorP);
	}

	system("PAUSE");

	return 0;
}

/********** Fim do módulo de implementação: MAIN  modulo para jogar jogo de xadrez **********/