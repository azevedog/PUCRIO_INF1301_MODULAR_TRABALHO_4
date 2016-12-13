/***************************************************************************
*  $MCI Módulo de implementação: Modulo Peça
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PEC
*
*  Autores: bap - Bruna Aleixo Penna Pereira
*           jpp - João Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

#include "TIPO_PECA.H"


/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor peça
*
***********************************************************************/

typedef struct PEC_tagPeca {

    TPC_tppTipoPeca pTipoPeca;
        /* ponteiro para a classe de peça à qual a peça pertence */

    PEC_tpJogador jogador;
        /* o jogador ao qual a peça pertence */

} PEC_tpPeca;


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: PEC &Criar peça
*
***********************************************************************/


PEC_tpCondRet PEC_CriarPeca( PEC_tppPeca * ppPeca , TPC_tppTipoPeca pTipoPeca , PEC_tpJogador jogador ) {
    
    PEC_tpPeca* pPeca;

    if(pTipoPeca == NULL) {
        return PEC_CondRetPonteiroNulo;
    }

    pPeca = (PEC_tpPeca*)malloc(sizeof(PEC_tpPeca));

    if (pPeca == NULL) {
        return PEC_CondRetFaltouMemoria; 
    }

    pPeca->pTipoPeca = pTipoPeca;
    pPeca->jogador = jogador;

    *ppPeca = pPeca;

    return PEC_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: PEC &Destruir peça
*
***********************************************************************/


PEC_tpCondRet PEC_DestruirPeca( PEC_tppPeca pPeca ) {
    
    if(pPeca == NULL) {
        return PEC_CondRetPonteiroNulo;
    }

    free(pPeca);

    return PEC_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: PEC &Atribuir classe da peça
*
***********************************************************************/

PEC_tpCondRet PEC_AtribuirTipoPeca( PEC_tppPeca pPeca , TPC_tppTipoPeca pTipoPeca ) {
    
    if(pPeca == NULL || pTipoPeca == NULL) {
        return PEC_CondRetPonteiroNulo;
    }

    pPeca->pTipoPeca = pTipoPeca;

    return PEC_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: PEC &Obter classe da peça
*
***********************************************************************/

PEC_tpCondRet PEC_ObterTipoPeca( PEC_tppPeca pPeca , TPC_tppTipoPeca * ppTipoPeca ) {
    
    if(pPeca == NULL) {
        return PEC_CondRetPonteiroNulo;
    }

    *ppTipoPeca = pPeca->pTipoPeca;

    return PEC_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: PEC &Obter jogador ao qual pertence a peça
*
***********************************************************************/

PEC_tpCondRet PEC_ObterJogador( PEC_tppPeca pPeca , PEC_tpJogador * pJogador ) {
    if(pPeca == NULL) {
        return PEC_CondRetPonteiroNulo;
    }

	*pJogador = pPeca->jogador;

    return PEC_CondRetOK;
}


/********** Fim do módulo de implementação: Módulo peça **********/