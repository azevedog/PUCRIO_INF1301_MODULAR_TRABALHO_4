#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB	Tabuleiro de xadrez
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
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
*     3       mmq   04/out/2016 revisao e correções
*     2       fpf   02/out/2016 incluindo definição de funções implementadas
*     1       fpf   01/out/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa tabuleiro de xadrez
*     O tabuleiro possui uma cabeça encapsulando o seu estado.
*
*
***************************************************************************/

#include "LISTA.H"

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */

typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK,
	/* Concluiu corretamente */

	TAB_CondRetEntradaInvalida,
	/* Erro ao abrir o arquivo de entrada */

	TAB_CondRetNaoExiste,
	/* O tabuleiro não existe */

	TAB_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de tabuleiro */

	TAB_CondRetCasaInexistente,
	/* Coordenada para casa inválida */

	TAB_CondRetPecaInexistente,
	/* Peça inexistente */

	TAB_CondRetCorInexistente,
	/* Cor inexistente */

	TAB_CondRetMovimentoInvalido,
	/* Movimento invalido */

	TAB_CondRetCasaVazia
	/* Não existe peça na casa especificada */

} TAB_tpCondRet;


/***********************************************************************
*
*  $FC Função: TAB  &Criar tabuleiro
*
*  $AE Assertivas de entrada
*  - pTabuleiro não deve ter memoria alocada
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro de xadrez
*    
*  $EP Parâmetros
*	 pTabuleiro - referencia para o tabuleiro a ser criado
*
*  $FV Valor retornado
*     TAB_CondRetOK            - Executou corretamente.
*	  TAB_CondRetFaltouMemoria - Ocorreu algum erro de falta de memória
*
***********************************************************************/

	TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Inserir peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pNome não deve estar NULL e deve possuir no máximo 4 caracteres
*  - cor deverá ser o char 'p', 'P', 'b' ou 'B'
*  - pCoordenada tem apenas 2 caracteres e são referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  com um novo elemento na casa referente a coordenada
*
*  $ED Descrição da função
*     Insere peça em um tabuleiro de xadrez
*    
*  $EP Parâmetros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser inserido
*	 pNome			- ponteiro para o nome da peça
*	 cor			- cor da peça
*	 pCoordenada	- ponteiro para coordenada da casa
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro não existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inválida
*	  TAB_CondRetPecaInexistente - Peça a ser inserida não existe
*	  TAB_CondRetCorInexistente  - Cor não existe
*
***********************************************************************/

	TAB_tpCondRet TAB_InserirPeca(TAB_tppTabuleiro * pTabuleiro, char * pNome, char cor, char* pCoordenada);

/***********************************************************************
*
*  $FC Função: TAB  &Mover peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pOrigem tem apenas 2 caracteres e são referentes a uma casa
*  do tabuleiro
*  - pDestino tem apenas 2 caracteres e são referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  com o elemento da casa referente a origem na casa destino
*
*  $ED Descrição da função
*     move uma peça em um tabuleiro de xadrez
*    
*  $EP Parâmetros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser inserido
*	 origem			- coordenada de origem
*	 destino		- coordenada de destino
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro não existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inválida
*	  TAB_CondRetMovimentoInvalido - movimento invalido
*
***********************************************************************/

	TAB_tpCondRet TAB_MoverPeca(TAB_tppTabuleiro * pTabuleiro, char * origem, char * destino);

/***********************************************************************
*
*  $FC Função: TAB  &Retirar peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e são referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  com o elemento da casa referente a coordenada retirado
*
*  $ED Descrição da função
*     Retira peça de um tabuleiro de xadrez
*
*  $EP Parâmetros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser retirado
*	 pCoordenada	- ponteiro para coordenada da casa
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro não existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inválida
*
***********************************************************************/

	TAB_tpCondRet TAB_RetirarPeca(TAB_tppTabuleiro * pTabuleiro, char* pCoordenada);

/***********************************************************************
*
*  $FC Função: TAB  &Obter peca
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e são referentes a uma casa
*  do tabuleiro
*  - cor deverá ser o char 'p', 'P', 'b' ou 'B'
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pNome tem que estar preenchido com o nome da peça da casa 
*  referenciada por pCoordenada
*
*  $ED Descrição da função
*     Obter peça de um tabuleiro de xadrez
*
*  $EP Parâmetros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser obtido
*	 pCoordenada	- ponteiro para coordenada da casa
*	 pCor			- ponteiro para onde sera retornado a cor
*	 pNome			- ponteiro para onde sera retornado o nome
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente
*	  TAB_CondRetNaoExiste       - Tabuleiro não existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inválida
*     TAB_CondRetCasaVazia       - Não há peça na casa
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterPeca(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, char * pCor, char ** pNome );

/***********************************************************************
*
*  $FC Função: TAB  &Obter lista ameaçantes
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e são referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pLista tem que estar preenchido com a lista ameacantes da casa  
*  referenciada por pCoordenada
*
*  $ED Descrição da função
*     Obter lista ameaçantes de uma peça de um tabuleiro de xadrez
*
*  $EP Parâmetros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser obtido
*	 pCoordenada	- ponteiro para coordenada da casa
*	 pLista			- ponteiro para a lista a ser preenchida
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro não existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inválida
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista);

/***********************************************************************
*
*  $FC Função: TAB  &Obter lista ameaçados
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pCoordenada tem apenas 2 caracteres e são referentes a uma casa
*  do tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*  - pLista tem que estar preenchido com a lista ameacados da casa 
*  referenciada por pCoordenada
*
*  $ED Descrição da função
*     Obter lista ameaçados de uma peça de um tabuleiro de xadrez
*
*  $EP Parâmetros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser obtido
*	 pCoordenada	- ponteiro para coordenada da casa
*	 pLista			- ponteiro para a lista a ser preenchida
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro não existe
*	  TAB_CondRetCasaInexistente - Coordenada da casa inválida
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterListaAmeacados(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista);

/***********************************************************************
*
*  $FC Função: TAB  &Destruir tabuleiro
*
*  $AE Assertivas de entrada
*  - pTabuleiro tem que estar apontando para uma cabeça de tabuleiro
*
*  $AS Assertiva de saida
*  - pTabuleiro não pode estar apontando para uma cabeça de tabuleiro
*
*  $ED Descrição da função
*     Destroi o tabuleiro
*
*  $EP Parâmetros
*	 pTabuleiro		- ponteiro para o tabuleiro a ser destruido
*
*  $FV Valor retornado
*     TAB_CondRetOK - Executou corretamente.
*	  TAB_CondRetNaoExiste       - Tabuleiro não existe
*
***********************************************************************/

	TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro * pTabuleiro);

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro de xadrez **********/

#else
#endif
