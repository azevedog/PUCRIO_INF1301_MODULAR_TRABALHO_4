#if ! defined( TIPO_PECA_ )
#define TIPO_PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo classe de peça de xadrez
*
*  Arquivo gerado:              CLASSE_PECA.H
*  Letras identificadoras:      CPC
*
*  Autores: bap - Bruna Aleixo Penna Pereira
*           jpp - João Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
*  $ED Descrição do módulo
*     Implementa funções para criar e manipular os tipos de peças 
*    de xadrez.
*
***************************************************************************/
 
#if defined( TIPO_PECA_OWN )
   #define TIPO_PECA_EXT
#else
   #define TIPO_PECA_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma classe_peca */

typedef struct TPC_tagTipoPeca * TPC_tppTipoPeca ;

/***********************************************************************
*
*  $TC Tipo de dados: CPC Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da classe_peca
*
***********************************************************************/

    typedef enum {

        TPC_CondRetOK ,
            /* Executou corretamente */

        TPC_CondRetPonteiroNulo ,
            /* Foi passado um ponteiro para NULL */

        TPC_CondRetArgumentosInvalidos ,
            /* Foram passados valores inválidos para argumentos.
            Por exemplo, índice de movimento inválido ou fora dos
            limites (-7 a 7.) */

        TPC_CondRetFaltouMemoria 
            /* Faltou memória ao alocar dados */

    } TPC_tpCondRet ;


/***********************************************************************
*
*  $FC Função: TPC &Criar tipo de peça
*
*  $ED Descrição da função
*     Cria um tipo de peça de xadrez
*     O ponteiro para o tipo criado será passado por referência para o 
*     parâmetro ppTipoPeca
*
*  $EP Parâmetros
*     $P ppTipoPeca - ponteiro para ponteiro de tipo de peça
*     $P nome - string contendo o identificador do tipo de peça 
*     (será o idenficador da lista de movimentos criada)
*
*  $FV Valor retornado
*     TPC_CondRetOK
*     TPC_CondRetFaltouMemoria
*
***********************************************************************/

    TPC_tpCondRet TPC_CriarTipoPeca(TPC_tppTipoPeca* ppTipoPeca, char *nome);

/***********************************************************************
*
*  $FC Função: TPC &Destruir tipo de peça
*
*  $ED Descrição da função
*     Destrói o tipo de peça, liberando o espaço alocado.
*
*  $EP Parâmetros
*     $P pTipoPeca - ponteiro para o tipo de peça a ser destruído
*
*  $FV Valor retornado
*     TPC_CondRetOK
*     TPC_CondRetPonteiroNulo
*
***********************************************************************/

    TPC_tpCondRet TPC_DestruirTipoPeca(TPC_tppTipoPeca pTipoPeca);

/***********************************************************************
*
*  $FC Função: TPC &Adicionar movimento ao tipo de peça
*
*  $ED Descrição da função
*     Adiciona um tipo de movimento ao tipo de peça dada.
*     Um movimento é composto pelos seus componentes horizontal e vertical.
*
*  $EP Parâmetros
*     $P pClassePeca - ponteiro para um tipo de peça
*     $P x - inteiro de -7 a 7 (limites horizontais do tabuleiro) contendo o 
*     valor vertical do movimento
*     $P y - inteiro de -7 a 7 (limites verticais do tabuleiro) contendo o 
*     valor horizontal do movimento
*
*  $FV Valor retornado
*     TPC_CondRetOK
*     TPC_CondRetArgumentosInvalidos
*     TPC_CondRetPonteiroNulo
*
***********************************************************************/

    TPC_tpCondRet TPC_AdicionarMovimento(TPC_tppTipoPeca pTipoPeca, int x, int y);

/***********************************************************************
*
*  $FC Função: TPC &Obter o n-ésimo movimento do tipo de peça
*
*  $ED Descrição da função
*     Obtém os componentes do movimento com o dado índice
*
*  $EP Parâmetros
*     $P pTipoPeca - ponteiro para o tipo de peça
*     $P n - índice do movimento, inteiro de 0 até (numMovimentos - 1)
*     $P pMovX - ponteiro para inteiro que conterá a componente vertical do movimento
*     $P pMovY - ponteiro para char que conterá a componente horizontal do movimento
*
*  $FV Valor retornado
*     TPC_CondRetOK
*     TPC_CondRetArgumentosInvalidos
*     TPC_CondRetPonteiroNulo
*
***********************************************************************/

    TPC_tpCondRet TPC_ObterMovimento( TPC_tppTipoPeca pTipoPeca , int n , int * pMovX , int * pMovY );

/***********************************************************************
*
*  $FC Função: TPC &Conferir movimento de um tipo de peça
*
*  $ED Descrição da função
*     Confere se o movimento é válido para determinado tipo de peça
*
*  $EP Parâmetros
*     $P pTipoPeca - ponteiro para o tipo de peça
*     $P movX - inteiro de -7 a 7 (limites horizontais do tabuleiro) contendo 
*     o valor vertical do movimento
*     $P movY - inteiro de -7 a 7 (limites verticais do tabuleiro) contendo o 
*     valor horizontal do movimento
*     $P resposta - ponteiro para inteiro que conterá a resposta (1, caso o 
*     movimento exista ou 0 caso contrário)
*
*  $FV Valor retornado
*     TPC_CondRetOK
*     TPC_CondRetArgumentosInvalidos
*     TPC_CondRetPonteiroNulo
*
***********************************************************************/

    TPC_tpCondRet TPC_ConferirMovimento( TPC_tppTipoPeca pTipoPeca , int movX , int movY , int * resposta );

/***********************************************************************
*
*  $FC Função: TPC &Obter nome do tipo de peça
*
*  $ED Descrição da função
*     Obtém o nome do tipo de peça dada.
*
*  $EP Parâmetros
*     $P pTipoPeca - ponteiro para o tipo de peça
*     $P pNome - ponteiro para string que conterá o nome
*
*  $FV Valor retornado
*     TPC_CondRetOK
*     TPC_CondRetPonteiroNulo
*
***********************************************************************/

    TPC_tpCondRet TPC_ObterNome(TPC_tppTipoPeca pTipoPeca , char ** pNome) ;


	// Obter Num Movimentos
	TPC_tpCondRet TPC_ObterNumMovimentos(TPC_tppTipoPeca pTipoPeca , int * numMovimentos);


#undef TIPO_PECA_EXT

/********** Fim do módulo de definição: Módulo tipo de peça de xadrez **********/

#else
#endif