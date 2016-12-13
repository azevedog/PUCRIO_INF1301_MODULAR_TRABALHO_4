#if ! defined( MATRIZ_ )
#define MATRIZ_

/***********************************************************************
 *
 *  $MCD Módulo de definição: Módulo matriz quadrada
 *
 *  Arquivo gerado:              MATRIZ.H
 *  Letras identificadoras:      MAT
 *
 *  Autores: bap - Bruna Aleixo Penna Pereira
 *           jpp - João Parreiras Martins Pereira
 *           pgb - Pedro Gomes Branco
 *
 *  $ED Descrição do módulo
 *     Implementa funções de criação e manipulação de matrizes quadradas.
 *
 ***************************************************************************/

#if defined( MATRIZ_OWN )
#define MATRIZ_EXT
#else
#define MATRIZ_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct MAT_tagMatriz * MAT_tppMatriz ;

/***********************************************************************
 *
 *  $TC Tipo de dados: MAT Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções da matriz
 *
 ***********************************************************************/

typedef enum {
	   
	   MAT_CondRetOK, /* Concluiu corretamente */
    
	   MAT_CondRetNulo, /* Recebeu um ponteiro nulo */
    
	   MAT_CondRetTamanhoInvalido, /* Recebeu um tamanho invalido para a matriz */
    
	   MAT_CondRetDirecaoInvalida, /* Recebeu uma direcao invalida para se movimentar */
    
	   MAT_CondRetPosicaoInvalida, /* Recebeu uma posicao invalida para se movimentar */
    
	   MAT_CondRetFaltouMemoria, /* Faltou memoria ao tentar criar um elemento de matriz */
    
} MAT_tpCondRet ;


/***********************************************************************
 *
 *  $TC Tipo de dados: MAT &Direcoes
 *
 *  $ED Descrição do tipo
 *     Direcoes disponíveis para mover a célula corrente da matriz
 *
 ***********************************************************************/

typedef enum {
	   MAT_DIR_C, /* Direcao p/ cima */
	   MAT_DIR_B, /* Direcao p/ baixo */
	   MAT_DIR_D, /* Direcao p/ direita */
	   MAT_DIR_E, /* Direcao p/ esquerda */
} MAT_tpDirecao;


/***********************************************************************
 *
 *  $FC Função: MAT &Criar matriz
 *
 *  $ED Descrição da função
 *     Cria uma nova matriz de com tam linhas e tam colunas.
 *     O ponteiro para a nova matriz será passado por referência no valor do ponteiro
 *     de ponteiro para matriz.
 *
 *  $EP Parâmetros
 *     $P ppMatriz - ponteiro para o ponteiro de matriz.
 *     $P tam      - tamanho da matriz
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetTamanhoInvalido
 *     MAT_CondRetFaltouMemoria
 *
 ***********************************************************************/
MAT_tpCondRet MAT_CriarMatriz(MAT_tppMatriz* ppMatriz, int tam);


/***********************************************************************
 *
 *  $FC Função: MAT &Destruir matriz
 *
 *  $ED Descrição da função
 *     Destrói o corpo e a cabeça da matriz, liberando o espaço alocado.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetPonteiroNulo
 *
 ***********************************************************************/
MAT_tpCondRet MAT_DestruirMatriz(MAT_tppMatriz pMatriz);


/***********************************************************************
 *
 *  $FC Função: MAT &Mover a célula corrente.
 *
 *  $ED Descrição da função
 *     Move a célula corrente da matriz, de acordo com a direcao fornecida.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz.
 *     $P direcao - direção para a qual mover.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetPonteiroNulo
 *     MAT_CondRetDirecaoInvalida
 *
 ***********************************************************************/
MAT_tpCondRet MAT_MoverCorrente(MAT_tppMatriz pMatriz, MAT_tpDirecao direcao);


/***********************************************************************
 *
 *  $FC Função: MAT &Definir célula corrente.
 *
 *  $ED Descrição da função
 *     Define a célula corrente da matriz, de acordo com as coordenadas fornecidas.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz.
 *     $P i - coordenada vertical.
 *     $P j - coordenada horizontal.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetPonteiroNulo
 *     MAT_CondRetPosicaoInvalida
 *
 ***********************************************************************/
MAT_tpCondRet MAT_DefinirCorrente(MAT_tppMatriz pMatriz, int i, int j);


/***********************************************************************
 *
 *  $FC Função: MAT &Definir valor corrente
 *
 *  $ED Descrição da função
 *     Atribui o valor fornecido à célula corrente da matriz.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz.
 *     $P pValor  - ponteiro para o valor a ser atribuído
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetPonteiroNulo
 *
 ***********************************************************************/
MAT_tpCondRet MAT_DefinirValorCorrente(MAT_tppMatriz pMatriz, void *pValor);


/***********************************************************************
 *
 *  $FC Função: MAT &Obter valor corrente
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz.
 *     $P ppValor - ponteiro para o ponteiro do valor a ser obtido
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetPonteiroNulo
 *
 ***********************************************************************/
MAT_tpCondRet MAT_ObterValorCorrente(MAT_tppMatriz pMatriz, void **ppValor);



#ifdef _DEBUG

/***********************************************************************
 *
 *  $FC FunÁ„o: LIS Verificar estrutura
 *
 *  $ED DescriÁ„o da funÁ„o
 *  Verifica a estrutura, contabilizando o total de erros encontrados.
 *
 *  $EP Parametros
 *     $P pLista - ponteiro para a lista.
 *     $P numErros - ponteiro para inteiro que recebera o total de erros.
 *
 *  $FV Valor retornado
 *     LIS_CondRetOK
 *
 ***********************************************************************/

MAT_tpCondRet MAT_VerificarEstrutura(MAT_tppMatriz pMatriz, int * numErros ) ;

/***********************************************************************
 *
 *  $FC Funcao: MAT Deturpar estrutura
 *
 *  $ED Descricao da funcao
 *  Deturpa a estrutura, de acordo com o comando fornecido.
 *
 *  $EP Parametros
 *     $P pLista - ponteiro para a lista.
 *     $P i - posição da linha do elemento corrente
 $     $P j - posição da coluna do elemento corrente
 *     $P flag - tipo de deturpacao, pode ser:
 *		1 - elimina o elemento corrente da estrutura escolhida.
 *		2 - atribui NULL ao ponteiro para uma casa sucessora.
 *		3 - atribui NULL ao ponteiro para uma casa predecessora.
 *		4 - atribui lixo ao ponteiro para a referência a uma casa sucessora.
 *		5 - atribui lixo ao ponteiro para a referência a uma casa predecessora.
 *		6 - atribui NULL ao ponteiro para o conteúdo da casa.
 *		7 - altera o tipo de estrutura apontado na casa.
 *		8 - destaca casa da matriz sem liberá-lo com free.
 *		9 - atribui NULL ao ponteiro corrente
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *
 ***********************************************************************/

MAT_tpCondRet MAT_Deturpar( MAT_tppMatriz pMatriz, int cmd, int i, int j ) ;

#endif

#undef MATRIZ_EXT

/********** Fim do módulo de definição: MAT Matriz **********/

#else
#endif
