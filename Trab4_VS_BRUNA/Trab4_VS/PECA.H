#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo peça de xadrez
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Autores: bap - Bruna Aleixo Penna Pereira
*           jpp - João Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
*  $ED Descrição do módulo
*     Implementa funções de criação e manipulação das peças de xadrez. 
*
***************************************************************************/

#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

#include "TIPO_PECA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct PEC_tagPeca * PEC_tppPeca ;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peca
*
***********************************************************************/

    typedef enum {

        PEC_CondRetOK ,
            /* Concluiu corretamente */

        PEC_CondRetPonteiroNulo ,
            /* Foi passado um ponteiro para NULL */

        PEC_CondRetFaltouMemoria 
            /* Faltou memória ao alocar memória */

    } PEC_tpCondRet ;



/***********************************************************************
*
*  $TC Tipo de dados: PEC Jogadores
*
*  $ED Descrição do tipo
*     Jogadores do xadrez
*
***********************************************************************/

    typedef enum {
        JOGADOR_BRANCO ,
            /* Jogador branco */

        JOGADOR_PRETO 
            /* Jogador preto  */

    } PEC_tpJogador ;


/***********************************************************************
*
*  $FC Função: PEC &Criar peça
*
*  $ED Descrição da função
*     Cria um peça de xadrez do o tipo fornecido.
*     A peça criada será passada por referência para o parametro pPeca.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para ponteiro de peça
*     $P pTipoPeca - ponteiro para o tipo de peça
*     $P jogador - jogador ao qual pertence a peça
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
***********************************************************************/

    PEC_tpCondRet PEC_CriarPeca( PEC_tppPeca * ppPeca , TPC_tppTipoPeca pTipoPeca , PEC_tpJogador jogador ) ;

 
/***********************************************************************
*
*  $FC Função: PEC &Destruir peça
*
*  $ED Descrição da função
*     Destrói a peça, liberando o espaço alocado.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça a ser destruída
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPonteiroNulo
*
***********************************************************************/

    PEC_tpCondRet PEC_DestruirPeca( PEC_tppPeca pPeca ) ;


/***********************************************************************
*
*  $FC Função: PEC &Atribuir classe da peça
*
*  $ED Descrição da função
*     Atribui uma nova classe à peça
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça
*     $P pTipoPeca - ponteiro que contém o novo tipo da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPonteiroNulo
*
***********************************************************************/

    PEC_tpCondRet PEC_AtribuirTipoPeca( PEC_tppPeca pPeca , TPC_tppTipoPeca pTipoPeca ) ;


/***********************************************************************
*
*  $FC Função: PEC &Obter tipo da peça
*
*  $ED Descrição da função
*     Obtém a tipo da peça e preenche o ponteiro passado como parâmetro
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça
*     $P ppClassePeca - ponteiro para ponteiro que conterá o tipo da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPonteiroNulo
*
***********************************************************************/

    PEC_tpCondRet PEC_ObterTipoPeca( PEC_tppPeca pPeca , TPC_tppTipoPeca * ppTipoPeca ) ;


/***********************************************************************
*
*  $FC Função: PEC &Obter jogador ao qual pertence a peça
*
*  $ED Descrição da função
*     Obtém o jogador ao qual pertence a peça dada.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça
*     $P pJogador - ponteiro que conterá o jogador da peça dada
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPonteiroNulo
*
***********************************************************************/

    PEC_tpCondRet PEC_ObterJogador( PEC_tppPeca pPeca , PEC_tpJogador * pJogador ) ;


#undef PECA_EXT

/********** Fim do módulo de definição: Módulo peça de xadrez **********/

#else
#endif
