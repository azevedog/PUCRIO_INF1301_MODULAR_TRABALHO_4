#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Módulo de definição: JOGO	Jogo de xadrez
*
*  Arquivo gerado:              JOGO.h
*  Letras identificadoras:      JOGO
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: fpf - Felipe Pessoa de Freitas
*			mmq - Matheus de Mello Queiroz
*			pf  - Pedro Ferreira
*			
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     2       mmq   16/nov/2016 correção de bugs
*     1       fpf   21/out/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa jogo de xadrez
*     Caso o Rei esteja em uma casa ameaçada e não possa se movimentar para qualquer outra casa,
*	  é emitida a mensagem “Cheque Mate”. Caso ele possa se movimentar
*	  para outra casa, é emitida a mensagem “Cheque”.
*	  A partida termina com o Cheque Mate ou a qualquer momento que um dos jogadores digite “FIM”.
*
*
***************************************************************************/

#include "TABULEIRO.H"

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Inteiro que indica se o jogo está rodando. 0 = PARADO; diferente de 0 = RODANDO  */

int jogoRodando;

/* string com o nome do jogador das peças brancas */

char * jogadorB;

/* string com o nome do jogador das peças pretas */

char * jogadorP;

/* char que indica o jogador corrente */

char jogCorr;


/***********************************************************************
*
*  $TC Tipo de dados: JOGO Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do jogo
*
***********************************************************************/

typedef enum {

	JOGO_CondRetOK,
	/* Concluiu corretamente */
	
	JOGO_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento do jogo */

	JOGO_CondRetTabuleiroInexistente,
	/* Tabuleiro não existe */

	JOGO_CondRetArquivoPecasNaoExiste,
	/* Arquivo de peças do tabuleiro não existe */

	JOGO_CondRetArquivoPecasForaPadrao,
	/* Arquivo de peças do tabuleiro não está no padrão */

	JOGO_CondRetJogoParado,
	/* O jogo ja terminou ou nao começou */

	JOGO_CondRetJogoEmAndamento,
	/* O jogo ja esta rodando */

	JOGO_CondRetMovimentoInvalido,
	/* Movimento Inválido */

	JOGO_CondRetJogoNaoPodeIniciar,
	/* Jogo nao pode ser iniciado */

	JOGO_CondRetCheque,
	/* Ocorreu cheque */

	JOGO_CondRetChequeMate,
	/* Ocorreu cheque mate */

	JOGO_CondRetNaoExisteRei
	/* Peca rei nao existe */

} JOGO_tpCondRet;


/***********************************************************************
*
*  $FC Função: JOGO  &Mostra tabuleiro
*
*  $ED Descrição da função
*     Mostra um tabuleiro de xadrez
*
*  $EP Parâmetros
*	 pTabuleiro - referencia para o tabuleiro a ser exibido
*
*  $FV Valor retornado
*     JOGO_CondRetOK				   - Executou corretamente
*	  JOGO_CondRetTabuleiroInexistente - Tabuleiro não existe
*	  JOGO_CondRetJogoParado		   - Jogo esta parado
*
***********************************************************************/

	JOGO_tpCondRet JOGO_MostraTabuleiro(TAB_tppTabuleiro pTabuleiro);

/***********************************************************************
*
*  $FC Função: JOGO  &Recebe jogada
*
*  $ED Descrição da função
*     Recebe a jogada de um jogador na partida
*
*  $EP Parâmetros
*	 pTabuleiro - referencia para o tabuleiro do jogo
*	 origem		- coordenada origem da jogada
*	 destino	- coordenada destino da jogada
*
*  $FV Valor retornado
*     JOGO_CondRetOK				   - Executou corretamente
*	  JOGO_CondRetTabuleiroInexistente - Tabuleiro não existe
*	  JOGO_CondRetJogoParado		   - Jogo esta parado
*	  JOGO_CondRetMovimentoInvalido	   - Movimento Inválido
*
***********************************************************************/

	JOGO_tpCondRet JOGO_RecebeJogada(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino);

/***********************************************************************
*
*  $FC Função: JOGO  &Recebe jogadores
*
*  $ED Descrição da função
*     Recebe os jogadores da partida
*
*  $EP Parâmetros
*	 jog1		- nome do jogador1
*	 jog2		- nome do jogador2
*
*  $FV Valor retornado
*     JOGO_CondRetOK				   - Executou corretamente
*	  JOGO_CondRetJogoEmAndamento	   - Jogo em andamento
*	  JOGO_CondRetFaltouMemoria		   - Faltou memoria
*
***********************************************************************/

	JOGO_tpCondRet JOGO_RecebeJogadores(char * jog1, char * jog2);


/***********************************************************************
*
*  $FC Função: JOGO  &Monta tabuleiro
*
*  $ED Descrição da função
*     Monta um tabuleiro de xadrez a partir de arquivo
*
*  $EP Parâmetros
*	 pTabuleiro - referencia para o tabuleiro a ser montado
*
*  $FV Valor retornado
*     JOGO_CondRetOK					 - Executou corretamente
*	  JOGO_CondRetTabuleiroInexistente	 - Tabuleiro não existe
*	  JOGO_CondRetArquivoPecasNaoExiste	 - Arquivo de pecas inexistente
*	  JOGO_CondRetArquivoPecasForaPadrao - Arquivo de pecas fora do padrao
*	  JOGO_CondRetJogoEmAndamento		 - Jogo em andamento
*
***********************************************************************/

	JOGO_tpCondRet JOGO_MontaTabuleiro(TAB_tppTabuleiro pTabuleiro, char * nomeArq);

/***********************************************************************
*
*  $FC Função: JOGO  &Inicia jogo
*
*  $ED Descrição da função
*     Inicia o jogo
*
*  $FV Valor retornado
*     JOGO_CondRetOK					 - Executou corretamente
*	  JOGO_CondRetJogoNaoPodeIniciar	 - Jogo nao pode ser iniciado
*	  JOGO_CondRetJogoEmAndamento		 - Jogo em andamento
*
***********************************************************************/

	JOGO_tpCondRet JOGO_IniciaJogo();
	
/***********************************************************************
*
*  $FC Função: JOGO  &Cheque mate
*
*  $ED Descrição da função
*     Confere o jogador está em cheque mate
*
*  $EP Parâmetros
*	 pTabuleiro - referencia para o tabuleiro do jogo
*    jogador    - nome do jogador que se deseja obter a informação
*
*  $FV Valor retornado
*     JOGO_CondRetOK					 - Não ocorreu cheque nem cheque mate
*     JOGO_CondRetChequeMate			 - Ocorreu cheque mate
*	  JOGO_CondRetCheque				 - Ocorreu cheque
*	  JOGO_CondRetNaoExisteRei			 - A peça rei não existe
*     JOGO_CondRetTabuleiroInexistente	 - Tabuleiro não existe
*	  JOGO_CondRetJogoParado			 - Jogo esta parado
*
***********************************************************************/

	JOGO_tpCondRet JOGO_ChequeMate( TAB_tppTabuleiro pTabuleiro, char* jogador );

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: JOGO  Jogo de xadrez **********/

#else
#endif
