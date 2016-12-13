/***************************************************************************
*  $MCI Módulo de implementação: TJOGO Teste jogo de xadrez
*
*  Arquivo gerado:              TestJOGO.c
*  Letras identificadoras:      TJOGO
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data     Observações
*     1        fpf   21/out/2016  início do desenvolvimento
*
***************************************************************************/

#include    <stdio.h>

#include <string.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include "TABULEIRO.H"
#include "JOGO.H"

static const char MOSTRA_TABULEIRO_CMD            [ ] = "=mostraTab"	;
static const char RECEBE_JOGADA_CMD			      [ ] = "=recJogada" 	;
static const char RECEBE_JOGADORES_CMD            [ ] = "=recJogador" 	;
static const char MONTA_TABULEIRO_CMD             [ ] = "=montaTab" 	;
static const char INICIA_JOGO_CMD	              [ ] = "=iniciaJogo" 	;
static const char CHEQUE_MATE_CMD	              [ ] = "=chequeMate" 	;


TAB_tppTabuleiro pTabuleiro = NULL;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TJOGO &Testar jogo
*
*  $ED Descrição da função
*     Testa a execução de um jogo de xadrez
*
*     Comandos disponíveis:
*
*     =mostraTab					CondRetEsp
*     =recJogada	orig	dest	CondRetEsp
*     =recJogador	jog1	jog2	CondRetEsp
*     =montaTab						CondRetEsp
*     =iniciaJogo					CondRetEsp
*     =chequeMate   jog				CondRetEsp
*
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int numLidos   = -1 ,
		CondRetEsp = -1  ;

	char jog1[20];
	char jog2[20];
	char jog[20];

	char pCoordOrigem[4];
	char pCoordDestino[4];

	char nomeArq[50];

	TST_tpCondRet CondRet = TST_CondRetOK;
	
	if (pTabuleiro == NULL)
	{
		TAB_CriarTabuleiro(&pTabuleiro);
	}
		
	/* JOGO  &Mostra tabuleiro */

		if (strcmp(ComandoTeste, MOSTRA_TABULEIRO_CMD) == 0)
		{
			numLidos = LER_LerParametros("i", &CondRetEsp);

			if (numLidos != 1)
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = JOGO_MostraTabuleiro(pTabuleiro);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao mostrar tabuleiro.");

		} /* fim ativa: JOGO  &Mostra tabuleiro */

	/* JOGO  &Recebe jogada */

		if (strcmp(ComandoTeste, RECEBE_JOGADA_CMD) == 0)
		{
			numLidos = LER_LerParametros("ssi", pCoordOrigem, pCoordDestino, &CondRetEsp);

			if (numLidos != 3)
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = JOGO_RecebeJogada(pTabuleiro,pCoordOrigem,pCoordDestino);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao receber jogada.");

		} /* fim ativa: JOGO  &Recebe jogada */

	/* JOGO  &Recebe jogadores */

		if (strcmp(ComandoTeste, RECEBE_JOGADORES_CMD) == 0)
		{
			numLidos = LER_LerParametros("ssi", jog1, jog2, &CondRetEsp);

			if (numLidos != 3)
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = JOGO_RecebeJogadores(jog1,jog2);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao receber jogadores.");

		} /* fim ativa: JOGO  &Recebe jogadores */

	/* JOGO  &Monta tabuleiro */

		if (strcmp(ComandoTeste, MONTA_TABULEIRO_CMD) == 0)
		{
			numLidos = LER_LerParametros("si", nomeArq, &CondRetEsp);

			if (numLidos != 2)
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = JOGO_MontaTabuleiro(pTabuleiro, nomeArq);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao montar tabuleiro.");

		} /* fim ativa: JOGO  &Monta tabuleiro */

	/* JOGO  &Inicia jogo */

		if (strcmp(ComandoTeste, INICIA_JOGO_CMD) == 0)
		{
			numLidos = LER_LerParametros("i", &CondRetEsp);

			if (numLidos != 1)
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = JOGO_IniciaJogo();

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao iniciar jogo.");

		} /* fim ativa: JOGO  &Inicia jogo */

	/* JOGO  &Cheque mate*/

		if (strcmp(ComandoTeste, CHEQUE_MATE_CMD) == 0)
		{
			numLidos = LER_LerParametros("si", jog, &CondRetEsp);

			if (numLidos != 2)
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = JOGO_ChequeMate( pTabuleiro, jog );

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao testar cheque mate.");

		} /* fim ativa: JOGO  &Cheque mate */

	return TST_CondRetNaoConhec ;
} /* Fim função: TJOGO &Testar jogo */



/********** Fim do módulo de implementação: TJOGO Teste jogo de xadrez **********/

