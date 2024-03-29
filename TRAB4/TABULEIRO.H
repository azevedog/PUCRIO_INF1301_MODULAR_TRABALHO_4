#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAB	Tabuleiro de xadrez
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: fpf - Felipe Pessoa de Freitas
*			mmq - Matheus de Mello Queiroz
*			pf  - Pedro Ferreira
*			mcs - Maria Carolina Santos
*			gbha - Gustavo Azevedo
*			
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  4		  mcs	10/dez/2016	mudan�as para t4
*     3       mmq   04/out/2016 revisao e corre��es
*     2       fpf   02/out/2016 incluindo defini��o de fun��es implementadas
*     1       fpf   01/out/2016 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa tabuleiro de xadrez
*     O tabuleiro possui uma cabe�a encapsulando o seu estado.
*
*
***************************************************************************/

#include "LISTA.H"

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um tabuleiro */

typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK,
	/* Concluiu corretamente */

	TAB_CondRetEntradaInvalida,
	/* Erro ao abrir o arquivo de entrada */

	TAB_CondRetNaoExiste,
	/* O tabuleiro n�o existe */

	TAB_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento de tabuleiro */

	TAB_CondRetCasaInexistente,
	/* Coordenada para casa inv�lida */

	TAB_CondRetPecaInexistente,
	/* Pe�a inexistente */

	TAB_CondRetCorInexistente,
	/* Cor inexistente */

	TAB_CondRetMovimentoInvalido,
	/* Movimento invalido */

	TAB_CondRetCasaVazia
	/* N�o existe pe�a na casa especificada */

} TAB_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: TAB  &Criar tabuleiro
*
*  $AE Assertivas de entrada
*  - pTabuleiro n�o deve ter memoria alocada
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria um tabuleiro de xadrez
*    
*  $EP Par�metros
*	 pTabuleiro - referencia para o tabuleiro a ser criado
*
*  $FV Valor retornado
*     TAB_CondRetOK            - Executou corretamente.
*	  TAB_CondRetFaltouMemoria - Ocorreu algum erro de falta de mem�ria
*
***********************************************************************/

	TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTabuleiro);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Inserir peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pNome n�o deve estar NULL e deve possuir no m�ximo 4 caracteres
*  - cor dever� ser o char 'p', 'P', 'b' ou 'B'
*  - pCoordenada tem apenas 2 caracteres e s�o referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  com um novo elemento na casa referente a coordenada
*
*  $ED Descri��o da fun��o
*     Insere pe�a em um tabuleiro de xadrez
*    
*  $EP Par�metros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser inserido
*	 pNome			- ponteiro para o nome da pe�a
*	 cor			- cor da pe�a
*	 pCoordenada	- ponteiro para coordenada da casa
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro n�o existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inv�lida
*	  TAB_CondRetPecaInexistente - Pe�a a ser inserida n�o existe
*	  TAB_CondRetCorInexistente  - Cor n�o existe
*
***********************************************************************/

	TAB_tpCondRet TAB_InserirPeca(TAB_tppTabuleiro * pTabuleiro, char * pNome, char cor, char* pCoordenada);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Mover peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pOrigem tem apenas 2 caracteres e s�o referentes a uma casa
*  do tabuleiro
*  - pDestino tem apenas 2 caracteres e s�o referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  com o elemento da casa referente a origem na casa destino
*
*  $ED Descri��o da fun��o
*     move uma pe�a em um tabuleiro de xadrez
*    
*  $EP Par�metros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser inserido
*	 origem			- coordenada de origem
*	 destino		- coordenada de destino
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro n�o existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inv�lida
*	  TAB_CondRetMovimentoInvalido - movimento invalido
*
***********************************************************************/

	TAB_tpCondRet TAB_MoverPeca(TAB_tppTabuleiro * pTabuleiro, char * origem, char * destino);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Retirar peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e s�o referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  com o elemento da casa referente a coordenada retirado
*
*  $ED Descri��o da fun��o
*     Retira pe�a de um tabuleiro de xadrez
*
*  $EP Par�metros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser retirado
*	 pCoordenada	- ponteiro para coordenada da casa
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro n�o existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inv�lida
*
***********************************************************************/

	TAB_tpCondRet TAB_RetirarPeca(TAB_tppTabuleiro * pTabuleiro, char* pCoordenada);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e s�o referentes a uma casa
*  do tabuleiro
*  - cor dever� ser o char 'p', 'P', 'b' ou 'B'
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pNome tem que estar preenchido com o nome da pe�a da casa 
*  referenciada por pCoordenada
*
*  $ED Descri��o da fun��o
*     Obter pe�a de um tabuleiro de xadrez
*
*  $EP Par�metros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser obtido
*	 pCoordenada	- ponteiro para coordenada da casa
*	 pCor			- ponteiro para onde sera retornado a cor
*	 pNome			- ponteiro para onde sera retornado o nome
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente
*	  TAB_CondRetNaoExiste       - Tabuleiro n�o existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inv�lida
*     TAB_CondRetCasaVazia       - N�o h� pe�a na casa
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterPeca(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, char * pCor, char ** pNome );

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter lista amea�antes
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e s�o referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pLista tem que estar preenchido com a lista ameacantes da casa  
*  referenciada por pCoordenada
*
*  $ED Descri��o da fun��o
*     Obter lista amea�antes de uma pe�a de um tabuleiro de xadrez
*
*  $EP Par�metros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser obtido
*	 pCoordenada	- ponteiro para coordenada da casa
*	 pLista			- ponteiro para a lista a ser preenchida
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro n�o existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inv�lida
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter lista amea�ados
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e s�o referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*  - pLista tem que estar preenchido com a lista ameacados da casa 
*  referenciada por pCoordenada
*
*  $ED Descri��o da fun��o
*     Obter lista amea�ados de uma pe�a de um tabuleiro de xadrez
*
*  $EP Par�metros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser obtido
*	 pCoordenada	- ponteiro para coordenada da casa
*	 pLista			- ponteiro para a lista a ser preenchida
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro n�o existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inv�lida
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterListaAmeacados(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Destruir tabuleiro
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabe�a de tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro n�o pode estar apontando para uma cabe�a de tabuleiro
*
*  $ED Descri��o da fun��o
*     Destroi o tabuleiro
*
*  $EP Par�metros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser destruido
*
*  $FV Valor retornado
*     TAB_CondRetOK - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro n�o existe
*
***********************************************************************/

	TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro * pTabuleiro);


#ifdef _DEBUG
	TAB_tpCondRet TAB_Verifica ( TAB_tppTabuleiro * pTabuleiro, int* numErros );
	TAB_tpCondRet TAB_Deturpa( TAB_tppTabuleiro * pTabuleiroeiro, int acao );
#endif

#undef TABULEIRO_EXT


/********** Fim do m�dulo de defini��o: TAB  Tabuleiro de xadrez **********/

#else
#endif
