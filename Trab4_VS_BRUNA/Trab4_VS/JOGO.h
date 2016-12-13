#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo jogo
*
*  Arquivo gerado:              JOGO.H
*  Letras identificadoras:      JGO
*
*  Autores: bap - Bruna Aleixo Penna Pereira
*           jpp - João Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
*  $ED Descrição do módulo
*     Implementa funções para jogar xadrez.
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
*  $TC Tipo de dados: JGO Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do jogo
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
*  $FC Função: JGO Inicializa
*
*  $ED Descrição da função
*     Inicia a variavel global, criando as estruturas necessarias.
*
***********************************************************************/

JGO_tpCondRet JGO_Inicializa(void);

/***********************************************************************
*
*  $FC Função: JGO Inicia Jogo
*
*  $ED Descrição da função
*     Inicia o jogo
*
***********************************************************************/

JGO_tpCondRet JGO_IniciaJogo(void);


/***********************************************************************
*
*  $FC Função: JGO Novo Tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_NovoTabuleiro(void);

/***********************************************************************
*
*  $FC Função: JGO Abrir Tabuleiro
*
*  $ED Descrição da função
*    Tenta abrir um arquivo de tabuleiro e o cria no programa.
*
*
***********************************************************************/

JGO_tpCondRet JGO_AbrirTabuleiro(char* dir);

/***********************************************************************
*
*  $FC Função: JGO Salvar Tabuleiro
*
*  $ED Descrição da função
*    Salva o tabuleiro no caminho oferecido pelo usuario.
*	 O arquivo a ser salvo busca na lista de pecas e,
*	 para cada peca insere seus respectivos movimentos.
*
*
***********************************************************************/

JGO_tpCondRet JGO_SalvarTabuleiro(char* dir);


/***********************************************************************
*
*  $FC Função: JGO Exibe Tabuleiro
*
*  $ED Descrição da função
*     Exibe a configuracao atual do tabuleiro
*
***********************************************************************/

JGO_tpCondRet JGO_ExibeTabuleiro();

/***********************************************************************
*
*  $FC Função: JGO cria peca
*
*  $ED Descrição da função
*     Abre o menu para colocar uma peca no tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_CriarPeca(char* nomeTipo, int jogador, char coluna, int linha);


/***********************************************************************
*
*  $FC Função: JGO altera  peça
*
*  $ED Descrição da função
*     Abre o menu para alterar uma peça.
*
***********************************************************************/

JGO_tpCondRet JGO_AlterarPosicaoPeca(int linha, char coluna, int linha2, int coluna2);

/***********************************************************************
*
*  $FC Função: JGO altera posicao peça
*
*  $ED Descrição da função
*     Altera a posicao da peça na coordenada linha .
*
***********************************************************************/

JGO_tpCondRet JGO_AlterarTipoPeca(char* nomeTipo, int linha, char coluna);

/***********************************************************************
*
*  $FC Função: JGO cria tipo de peça
*
*  $ED Descrição da função
*     Abre o menu para criar um novo tipo de peça.
*
***********************************************************************/

JGO_tpCondRet JGO_CriarTipo(char* nomeTipo, int* movsI, int* movsJ, int qtdMovs);

/***********************************************************************
*
*  $FC Função: JGO Excluir Peca
*
*  $ED Descrição da função
*     Abre o menu para excluir uma peça do tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_ExcluirPeca(int linha, char coluna);

/***********************************************************************
*
*  $FC Função: JGO Listar Pecas
*
*  $ED Descrição da função
*     Printa uma lsta com as peças contindas no tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_ListarPecas();

/***********************************************************************
*
*  $FC Função: JGO Listar Tipos
*
*  $ED Descrição da função
*     Lista todas as possibilidades de pecas que podem ser inseridas no tabuleiro.
*
***********************************************************************/

JGO_tpCondRet JGO_ListarTipos( void );


/***********************************************************************
*
*  $FC Função: JGO funcao de saida
*
*  $ED Descrição da função
*     Fecha o programa.
*
*  $FV Valor retornado
*     JGO_CondRetOK
*     JGO_CondRetFaltouMemoria
*
***********************************************************************/

void JGO_Sair(int code);

#undef JOGO_EXT

/********** Fim do módulo de definição: Módulo tipo de peça de xadrez **********/

#else
#endif