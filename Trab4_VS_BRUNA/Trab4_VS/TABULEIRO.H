#if ! defined(TABULEIRO_)
#define TABULEIRO_

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: T3 INF1301 2013.2
*  Autores: bap - Bruna Aleixo Penna
*           jpp - Joao Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
*  $ED Descrição do módulo
*     Implementa funções para criar e manipular tabuleiros quadrados.
*     Os tabuleiros possuem uma cabeça, que dita seu estado atual.
*     Cada posição do tabuleiro pode armazenar uma variável do tipo referência
*	  para uma casa.
*
***************************************************************************/

#if defined(TABULEIRO_OWN)
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

#include "Matriz.h"
#include "Lista.h"

/*** Declaracoes exportadas pelo modulo ***/

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */
typedef struct TAB_tagTabuleiro* TAB_tppTabuleiro;

/* Tipo referência para uma casa */
typedef struct TAB_tagCasa*	TAB_tppCasa;


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

	TAB_CondRetPonteiroNulo,
	/* Ponteiro passado eh nulo */

	TAB_CondRetNaoExiste,
	/* O tabuleiro nao existe */

	TAB_CondRetFaltouMemoria,
	/* Faltou memoria ao tentar criar um elemento de tabuleiro */

	TAB_CondRetCasaInexistente,
	/* Coordenada para casa invalida */

	TAB_CondRetCasaVazia
	/* Nao existe peca na casa especificada */

} TAB_tpCondRet;


/***********************************************************************
*
*  $FC Função: TAB Criar Tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro quadrado
*     O ponteiro para o tabuleiro criado será fornecido no valor do ponteiro
*     de ponteiro para tabuleiro. A posição corrente incial é 'A'-1
*
*  $EP Parâmetros
*     $P ppTabuleiro - ponteiro para o ponteiro de um tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/

// Não há assertivas de entrada.

TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro* ppTabuleiro);

// Assertivas de saída: passa por referência ao parâmetro ppTabuleiro o ponteiro para
// o tabuleiro criado. Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Destruir tabuleiro
*
*  $ED Descrição da função
*     Destroi todo o tabuleiro, e libera o espaco allocado.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro

TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro pTabuleiro);

// Assertivas de saída: Libera todos os elementos do tabuleiro, assim como
// sua cabeça e o espaço alocado para o tabuleiro. Retorna uma condição indicando
// se houve erro ou não.


/***********************************************************************
*
*  $FC Função: TAB Obter Peca da Casa
*
*  $ED Descrição da função
*     Obtem a peca na casa fornecida como parametro 
*
*  $EP Parâmetros
*     $P pCasa - ponteiro para uma casa no tabuleiro.
*	  $P pPeca - ponteiro para o ponteiro de peca
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

TAB_tpCondRet TAB_ObterPecaDaCasa(TAB_tppCasa pCasa, void** pPeca);

/***********************************************************************
*
*  $FC Função: TAB Definir posição corrente.
*
*  $ED Descrição da função
*     Define a posição corrente do tabuleiro por meio de coordenadas i,j.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P i - coordenada vertical, de 1 a 8.
*     $P j - coordenada horizontal, de 'A' a 'H'.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*     TAB_CondRetPosicaoInvalida
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro, um inteiro
// indicando o deslocamento vertical e um char indicando o deslocamento horizontal
// pelo tabuleiro.

TAB_tpCondRet TAB_DefinirPosCorrente(TAB_tppTabuleiro pTabuleiro, int i, char j);

// Assertivas de saída: Retorna apenas uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Obter Posição Corrente.
*
*  $ED Descrição da função
*     Obtem as coordenadas da posição corrente do tabuleiro.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P i - ponteiro que receberá um int com a coordenada vertical
*     $P j - coordenada que receberá um char com a coordenada horizontal.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro.

TAB_tpCondRet TAB_ObterPosCorrente(TAB_tppTabuleiro pTabuleiro, int* i, char* j);

// Assertivas de saída: Passa por valor para o inteiro a coordenada 'i' do
// corrente do tabuleiro, e passa também por valor para o char a coordenada 'j'
// deste mesmo corrente. Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Obter Peca Corrente
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P pPeca - ponteiro para o ponteiro do valor a ser obtido	  
*     $P cor - ponteiro para a cor da peca
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetCasaVazia
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro.

TAB_tpCondRet TAB_ObterPecaCorrente(TAB_tppTabuleiro pTabuleiro, void** pPeca, int* cor);

// Assertivas de saida: Passa por referencia um ponteiro para a peca obtida, e passa
// por valor um inteiro relacionado a cor de tal peca. Retorna uma condicao
// indicando se houve erro ou nao.

/***********************************************************************
*
*  $FC Função: TAB Obter Peca
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P i - coordenada horizontal
*     $P j - coordenada vertical
*     $P pPeca - ponteiro para o ponteiro do valor a ser obtido	  
*     $P cor - ponteiro para o valor da cor da dada peça.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro, um inteiro com a
// coordenada 'i' e um char com a coordenada 'j'.

TAB_tpCondRet TAB_ObterPeca(TAB_tppTabuleiro pTabuleiro, int i, char j, void** pPeca, int* cor);

// Assertivas de saída: Passa por referência um ponteiro para pPeca, valor que está
// contido na dada coordenada. Passa por valor ao inteiro 'cor' a cor da peça na
// dada coordenada. Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Mover peca de uma casa a outra
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P iOrig - coordenada vertical da origem
*     $P jOrig - coordenada horizontal da origem
*     $P iDest - coordenada vertical do destino
*     $P jDest - coordenada horizontal do destino
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosicaoInvalida
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro e coordenadas (conjuntos de
// int e char) de origem e destino.

TAB_tpCondRet TAB_MoverPeca(TAB_tppTabuleiro pTabuleiro, int iOrig, char jOrig, int iDest, char jDest, void** pecaComida, int* jogadorComido);

// Assertivas de saída: Retorna uma condição indicando se houve erro ou não.


/***********************************************************************
*
*  $FC Função: TAB - Checar Posição Válida
*
*  $ED Descrição da função
*     Função auxiliar que checa se uma dada posicao (coordenadas i,j) eh valida.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosicaoInvalida
*
***********************************************************************/

// Assertivas de entrada: Recebe uma coordenada (inteiro 'i' e char 'j').

TAB_tpCondRet TAB_ChecarPosicaoValida(int i, char j);

// Assertivas de saída: Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Inserir Peca
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P pPeca - ponteiro para a peca a ser inserida
*     $P i - coordenada horizontal
*     $P j - coordenada vertical
*     $P cor - cor do jogador (int 0 ou 1) que comanda a dada peca.  
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*     TAB_CondRetCasaInexistente
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro, um ponteiro para uma
// peça, um conjunto de int e char para as coordenadas e um int indicando a cor da peça.

TAB_tpCondRet TAB_InserirPeca(TAB_tppTabuleiro pTabuleiro, void* pPeca, int i, char j, int cor);

// Assertivas de saída: Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Retirar Peca
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P i - coordenada horizontal da peca a ser retirada
*     $P j - coordenada vertical da peca a ser retirada
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*	  TAB_CondRetCasaInexistente
*	  TAB_CondRetCasaVazia
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro, e um inteiro 'i'
// e char 'j' indicando as coordenadas no tabuleiro.

TAB_tpCondRet TAB_RetirarPeca(TAB_tppTabuleiro pTabuleiro, int i, char j);

// Assertivas de saída: Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Obter Lista Ameacantes
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P i - coordenada horizontal da peca a ser retirada
*     $P j - coordenada vertical da peca a ser retirada
*     $P pLisat - ponteiro para o ponteiro da lista de ameacantes
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro, e um int 'i' e
// char 'j' indicando as coordenadas no tabuleiro.

TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_tppTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista);

// Assertivas de saída: Passa por referência um ponteiro para uma lista
// de ameacantes para a dada coordenada.
// Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Obter Lista Ameacados
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P i - coordenada horizontal da peca a ser retirada
*     $P j - coordenada vertical da peca a ser retirada
*     $P pLista - ponteiro para o ponteiro da lista de ameacados
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

// Assertivas de entrada: Recebe um ponteiro para um tabuleiro, e um int 'i' e
// char 'j' indicando as coordenadas no tabuleiro.

TAB_tpCondRet TAB_ObterListaAmeacados(TAB_tppTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista);

// Assertivas de saída: Passa por referência um ponteiro para uma lista
// de ameacados para a dada coordenada.
// Retorna uma condição indicando se houve erro ou não.

/***********************************************************************
*
*  $FC Função: TAB Adicionar Lista de Ameacantes e Ameacados
*
*  $ED Descrição da função
*     Adiciona à lista de ameacados da peça da casa com coordenadas iAmeacante e jAmeacantes a peça na casa 
*  	  de coordenadas iAmeacado e jAmeacado e adiciona à listas de ameacantes a peça da casa com coordenadas iAmeacado e jAmeacado
*  	  na casa com coordenadas iAmeacante e jAmeacantes
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P iAmeacante - coordenada horizontal da peca que ameaça a peça da casa com coordenadas iAmeacado e jAmeacado
*     $P jAmeacante - coordenada vertical da peca que ameaça a peça da casa com coordenadas iAmeacado e jAmeacado
*     $P iAmeacado - coordenada horizontal da peca sendo ameacada pela peça da casa com coordenadas iAmeacante e jAmeacante
*     $P jAmeacado - coordenada vertical da peca sendo ameacada pela peça da casa com coordenadas iAmeacante e jAmeacante
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

TAB_tpCondRet TAB_AdicionarListaAmeacantesAmeacados(TAB_tppTabuleiro pTabuleiro, int iAmeacante, char jAmeacante, int iAmeacado, char jAmeacado); 

/***********************************************************************
*
*  $FC Função: TAB Esvaziar Listas da Casa
*
*  $ED Descrição da função
*     Esvazia listas de ameacantes e ameacados da casa
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P i - coordenada horizontal da casa cuja lista deve ser esvaziada
*     $P j - coordenada vertical da casa cuja lista deve ser esvaziada
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/

TAB_tpCondRet TAB_EsvaziarListasDaCasa(TAB_tppTabuleiro pTabuleiro, int i, char j);

/***********************************************************************
*
*  $FC Função: TAB Voltar Peca
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro
*     $P iOrig - coordenada horizontal da peca a ser movida
*     $P jOrig - coordenada vertical da peca a ser movida
*	  $P iDest - coordenada horizontal para onde a peca sera movida
*     $P jDest - coordenada vertical para onde a peca sera movida
*     $P pPecaComida
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*	  TAB_CondRetPosicaoInvalida
*
***********************************************************************/

TAB_tpCondRet TAB_VoltarPeca(TAB_tppTabuleiro pTabuleiro, int iOrig, char jOrig, int iDest, char jDest, void** pPecaComida);

/***********************************************************************
*
*  $FC Funcao: TAB Verificar estrutura
*
*  $ED Descricao da funcao
*  Verifica a estrutura, contabilizando o total de erros encontrados.
*
*  $EP Parametros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P numErros - ponteiro para inteiro que recebera o total de erros.
*
*  $FV Valor retornado
* TAB_CondRetOK
*
***********************************************************************/
TAB_tpCondRet TAB_VerificarEstrutura( TAB_tppTabuleiro pTabuleiro, int * numErros );

/***********************************************************************
 *
 *  $FC Funcao: TAB Deturpar estrutura
 *
 *  $ED Descricao da funcao
 *  Deturpa a estrutura, de acordo com o comando fornecido.
 *
 *  $EP Parametros
 *     $P pLista - ponteiro para a lista.
 *     $P i - inteiro representando a linha corrente
 *     $P j - inteiro representando a coluna corrente
 *     $P flag - tipo de deturpacao, pode ser:
 *		1 - elimina o elemento corrente da estrutura escolhida.
 *		2 - atribui NULL ao ponteiro para uma casa sucessora.
 *		3 - atribui NULL ao ponteiro para uma casa predecessora.
 *		4 - atribui lixo ao ponteiro para a referência a uma casa sucessora.
 *		5 - atribui lixo ao ponteiro para a referência a uma casa predecessora.
 *		6 - atribui NULL ao ponteiro para o conteúdo da casa.
 *		7 - altera o tipo de estrutura apontado na casa.
 *		8 - destaca casa da matriz sem liberá-lo com free.
 *		9 - atribui NULL ao ponteiro corrente
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK
 *
 ***********************************************************************/
TAB_tpCondRet TAB_Deturpar( TAB_tppTabuleiro pTabuleiro, int cmd, int i, int j ) ;
#undef TABULEIRO_EXT


/*** Fim do modulo de definicao: Modulo Tabuleiro ***/

#else
#endif
