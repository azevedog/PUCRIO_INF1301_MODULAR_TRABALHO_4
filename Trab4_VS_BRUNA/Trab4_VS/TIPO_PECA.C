/***************************************************************************
*  $MCI Módulo de implementação: Modulo Tipo Peça
*
*  Arquivo gerado:              TIPO_PECA.c
*  Letras identificadoras:      TPC
*
*  Autores: bap - Bruna Aleixo Penna Pereira
*           jpp - João Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TIPO_PECA_OWN
#include "TIPO_PECA.H"
#undef TIPO_PECA_OWN

/***** Protótipo das funções encapuladas no módulo *****/

static void DestruirMovimento (void * pMovimento) ;

/***********************************************************************
*
*
*  $ED Descrição do tipo
*     Um tipo de peça possui um identificador (string) e uma lista de movimentos.
*     Um movimento é uma ponteiro ao tipo de dados TPC_tpMovimento.
*
***********************************************************************/

typedef struct TPC_tagTipoPeca {

    char * nome;

    LIS_tppLista movimentos;

} TPC_tpTipoPeca ;

/***** Tipos de dados encapsulados no módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: TPC &Descritor de um movimento de um tipo de peça
*
*  $ED Descrição do tipo
*     Estrutura simples que armazena dois inteiros, correspondentes aos
*     componentes X e Y do movimento de um tipo de peça.
*
***********************************************************************/

typedef struct TPC_tagMovimento {
    int movX;
    char movY;
} TPC_tpMovimento;

/***********************************************************************
*
*  $FC Função: TPC &Criar tipo de peça
*
***********************************************************************/

TPC_tpCondRet TPC_CriarTipoPeca(TPC_tppTipoPeca* ppTipoPeca, char *nome) {

	TPC_tpTipoPeca * pTipoPeca;
	LIS_tpCondRet lisCondRet;

	pTipoPeca = (TPC_tpTipoPeca*) malloc(sizeof(TPC_tpTipoPeca));

	if (pTipoPeca == NULL) {
		return TPC_CondRetFaltouMemoria;
	}

	pTipoPeca->nome = (char*) malloc(sizeof(char) * (strlen(nome) + 1));

	if (pTipoPeca->nome == NULL) {
		return TPC_CondRetFaltouMemoria;
	}

	strcpy(pTipoPeca->nome, nome);

	lisCondRet = LIS_CriarLista(nome, &(pTipoPeca->movimentos));

	if (lisCondRet == LIS_CondRetFaltouMemoria) {
		free(pTipoPeca->nome);
        free(pTipoPeca);
        return TPC_CondRetFaltouMemoria;
	}

	*ppTipoPeca = pTipoPeca;

	return TPC_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: TPC &Destruir tipo de peça
*
***********************************************************************/

TPC_tpCondRet TPC_DestruirTipoPeca(TPC_tppTipoPeca pTipoPeca) {

	LIS_tpCondRet lisCondRet;

	if (pTipoPeca == NULL) {
		return TPC_CondRetPonteiroNulo;
	}

	lisCondRet = LIS_DestruirLista(pTipoPeca->movimentos);

	if (lisCondRet == LIS_CondRetListaInexistente) {
		return TPC_CondRetPonteiroNulo;
	}

	free(pTipoPeca->nome);
    free(pTipoPeca);

    return TPC_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: TPC &Obter número de movimentos (= número de elementos na lista) do tipo de peça
*
***********************************************************************/

TPC_tpCondRet TPC_ObterNumMovimentos( TPC_tppTipoPeca pTipoPeca , int * numMovimentos ) {
    if(pTipoPeca == NULL) {
        return TPC_CondRetPonteiroNulo;
    }

    LIS_ObterNumElementos(pTipoPeca->movimentos, numMovimentos);

    return TPC_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: TPC &Obter o n-ésimo movimento do tipo de peça
*
***********************************************************************/

TPC_tpCondRet TPC_ObterMovimento(TPC_tppTipoPeca pTipoPeca, int n, int * pMovX, int * pMovY) {
    int numElem;
	int i;
	TPC_tpMovimento** movimento;

	movimento = (TPC_tpMovimento**)malloc(sizeof(TPC_tpMovimento));
	if(movimento == NULL) {
		return TPC_CondRetFaltouMemoria;
	}

    if(pTipoPeca == NULL) {
        return TPC_CondRetPonteiroNulo;
    }

    TPC_ObterNumMovimentos(pTipoPeca, &numElem);

    if(n < 0 || n > numElem - 1) {
        return TPC_CondRetArgumentosInvalidos;
    }

    if (LIS_IrInicioLista(pTipoPeca->movimentos) != LIS_CondRetOK) {
    	return TPC_CondRetPonteiroNulo;
    }

    for(i = 0; i < n; i++) {
    	LIS_IrProx(pTipoPeca->movimentos);
    }
   
    LIS_ObterNo(pTipoPeca->movimentos, (void**)movimento);

    *pMovX = (*movimento)->movX;
    *pMovY = (*movimento)->movY;

    return TPC_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: CPC Conferir movimento de um tipo de peça
*
***********************************************************************/

TPC_tpCondRet TPC_ConferirMovimento( TPC_tppTipoPeca pTipoPeca , int movX , int movY , int * resposta ) {
    int numMovimentos;
    int i;
    int movXObtido, movYObtido;

    if(pTipoPeca == NULL) {
        return TPC_CondRetPonteiroNulo;
    }

    if(movX > 7 || movY > 7 || movX < -7 || movY < -7) {
    	// movimento inválido (movimento ultrapassa limites do tabuleiro)
        *resposta = 2;
        return TPC_CondRetOK;
    }

    TPC_ObterNumMovimentos(pTipoPeca, &numMovimentos);

    for(i = 0; i < numMovimentos; i++) {
        TPC_ObterMovimento(pTipoPeca, i, &movXObtido, &movYObtido);
        if(movXObtido == movX && movYObtido == movY) {
        	// movimento válido (encontrou movimento na lista de movimentos)
            *resposta = 1;
            return TPC_CondRetOK;      
        }
    }

    // Movimento inválido (não encontrou movimento na lista de movimentos)
    *resposta = 0;

    return TPC_CondRetOK;      
}
/***********************************************************************
*
*  $FC Função: TPC &Adicionar movimento ao tipo de peça
*
***********************************************************************/

TPC_tpCondRet TPC_AdicionarMovimento(TPC_tppTipoPeca pTipoPeca, int x, int y) {
	TPC_tpMovimento* movimento;
	int resposta; 
	LIS_tpCondRet condRet;

	if(pTipoPeca == NULL) {
        return TPC_CondRetPonteiroNulo;
    }

	// Checa se o movimento ja existe para a dada peca
    TPC_ConferirMovimento(pTipoPeca, x, y, &resposta);
    if(resposta == 1 || resposta == 2) {
        return TPC_CondRetArgumentosInvalidos;
    }

	movimento = (TPC_tpMovimento*)malloc(sizeof(TPC_tpMovimento));
	if (movimento == NULL) {
		return TPC_CondRetFaltouMemoria;
	}

	movimento->movX = x;
	movimento->movY = y;

	condRet = LIS_InserirNo(pTipoPeca->movimentos, (TPC_tpMovimento*)movimento);

	if (condRet == LIS_CondRetListaInexistente) {
        return TPC_CondRetPonteiroNulo;
	} 
	if (condRet == LIS_CondRetFaltouMemoria) {
        return TPC_CondRetFaltouMemoria;
	} 

    return TPC_CondRetOK;      
}


/***********************************************************************
*  $FC Função: CPC Obter nome de classe de peça
***********************************************************************/

TPC_tpCondRet TPC_ObterNome(TPC_tppTipoPeca pTipoPeca , char ** pNome) {
    if(pTipoPeca == NULL) {
        return TPC_CondRetPonteiroNulo;
    }

    *pNome = pTipoPeca->nome;

    return TPC_CondRetOK;
}

/***** Código das funções encapuladas no módulo *****/

/***********************************************************************
*
*  $FC Função: Destruir Movimento
*
*  $ED Descrição da função
*     Encapsula a função de destruição de um movimento.
*     Função recebe lista de movimentos
*
***********************************************************************/

static void DestruirMovimento (void * pMovimento) {
    free(pMovimento);
}


/********** Fim do módulo de implementação: Módulo tipo de peça de xadrez **********/