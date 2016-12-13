#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo jogo
*
*  Arquivo gerado:              JOGO.H
*  Letras identificadoras:      JGO
*
*  Autores: bap - Bruna Aleixo Penna Pereira
*           jpp - Jo�o Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
*  $ED Descri��o do m�dulo
*     Implementa fun��es para jogar xadrez.
*
***************************************************************************/
 
#if defined( JOGO_OWN )
   #define JOGO_EXT
#else
   #define JOGO_EXT extern
#endif

#include "LISTA.H"
#include "TIPO_PECA.H"
#include "PECA.H"
#include "TABULEIRO.H"

/***********************************************************************
*
*  $TC Tipo de dados: JGO Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do jogo
*
***********************************************************************/
typedef enum {

	JGO_CondRetOK,
	/* Concluiu corretamente */

	JGO_CondRetPonteiroNulo,
	/* Ponteiro passado eh nulo */

	JGO_CondRetFaltouMemoria,
	/* Faltou memoria ao tentar criar um elemento de tabuleiro */

	JGO_CondRetCaminhoInvalido,
	/* Caminho para arquivo especificado invalido */

	JGO_CondRetPosicaoInvalida,
	/* Posicao {linha, coluna} invalida */

	JGO_CondRetTipoInexistente,
	/* Tipo de peca fornecida nao existe */

	JGO_CondRetTipoJaExiste
	/* Tipo de peca fornecida ja existe */

} JGO_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: JGO Inicializa
*
*  $ED Descri��o da fun��o
*     Inicia a variavel global, criando as estruturas necessarias.
*
***********************************************************************/

JGO_tpCondRet JGO_Inicializa(void);

/***********************************************************************
*
*  $FC Fun��o: JGO Inicia Jogo
*
*  $ED Descri��o da fun��o
*     Inicia o jogo
*
***********************************************************************/

JGO_tpCondRet JGO_IniciaJogo(void);


/***********************************************************************
*
*  $FC Fun��o: JGO Novo Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria um tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_NovoTabuleiro(void);

/***********************************************************************
*
*  $FC Fun��o: JGO Abrir Tabuleiro
*
*  $ED Descri��o da fun��o
*    Tenta abrir um arquivo de tabuleiro e o cria no programa.
*
*
***********************************************************************/

JGO_tpCondRet JGO_AbrirTabuleiro(char* dir);

/***********************************************************************
*
*  $FC Fun��o: JGO Salvar Tabuleiro
*
*  $ED Descri��o da fun��o
*    Salva o tabuleiro no caminho oferecido pelo usuario.
*	 O arquivo a ser salvo busca na lista de pecas e,
*	 para cada peca insere seus respectivos movimentos.
*
*
***********************************************************************/

JGO_tpCondRet JGO_SalvarTabuleiro(char* dir);


/***********************************************************************
*
*  $FC Fun��o: JGO Exibe Tabuleiro
*
*  $ED Descri��o da fun��o
*     Exibe a configuracao atual do tabuleiro
*
***********************************************************************/

JGO_tpCondRet JGO_ExibeTabuleiro();

/***********************************************************************
*
*  $FC Fun��o: JGO cria peca
*
*  $ED Descri��o da fun��o
*     Abre o menu para colocar uma peca no tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_CriarPeca(char* nomeTipo, int jogador, char coluna, int linha);


/***********************************************************************
*
*  $FC Fun��o: JGO altera  pe�a
*
*  $ED Descri��o da fun��o
*     Abre o menu para alterar uma pe�a.
*
***********************************************************************/

JGO_tpCondRet JGO_AlterarPosicaoPeca(int linha, char coluna, int linha2, int coluna2);

/***********************************************************************
*
*  $FC Fun��o: JGO altera posicao pe�a
*
*  $ED Descri��o da fun��o
*     Altera a posicao da pe�a na coordenada linha .
*
***********************************************************************/

JGO_tpCondRet JGO_AlterarTipoPeca(char* nomeTipo, int linha, char coluna);

/***********************************************************************
*
*  $FC Fun��o: JGO cria tipo de pe�a
*
*  $ED Descri��o da fun��o
*     Abre o menu para criar um novo tipo de pe�a.
*
***********************************************************************/

JGO_tpCondRet JGO_CriarTipo(char* nomeTipo, int* movsI, int* movsJ, int qtdMovs);

/***********************************************************************
*
*  $FC Fun��o: JGO Excluir Peca
*
*  $ED Descri��o da fun��o
*     Abre o menu para excluir uma pe�a do tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_ExcluirPeca(int linha, char coluna);

/***********************************************************************
*
*  $FC Fun��o: JGO Listar Pecas
*
*  $ED Descri��o da fun��o
*     Printa uma lsta com as pe�as contindas no tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_ListarPecas();

/***********************************************************************
*
*  $FC Fun��o: JGO Listar Tipos
*
*  $ED Descri��o da fun��o
*     Lista todas as possibilidades de pecas que podem ser inseridas no tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_ListarTipos( void );


/***********************************************************************
*
*  $FC Fun��o: JGO funcao de saida
*
*  $ED Descri��o da fun��o
*     Fecha o programa.
*
*  $FV Valor retornado
*     JGO_CondRetOK
*     JGO_CondRetFaltouMemoria
*
***********************************************************************/

void JGO_Sair(int code);

#undef JOGO_EXT

/********** Fim do m�dulo de defini��o: M�dulo tipo de pe�a de xadrez **********/

#else
#endif