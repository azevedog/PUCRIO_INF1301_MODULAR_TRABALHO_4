/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Autores: avs - Arndt Von Staa
*           bap - Bruna Aleixo Penna Pereira
*           jpp - João Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
#include "CESPDIN.H"
#include "CONTA.H"
#endif

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
***********************************************************************/

typedef struct tagElemLista {

	void * pValor ;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt ;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx ;
	/* Ponteiro para o elemento sucessor */

#ifdef _DEBUG 
	LIS_tppLista pCabeca;
	int idTipo;
	int tamValor;
#endif

} tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
***********************************************************************/

typedef struct LIS_tagLista {
	char * id ;
	/* Cadeia identificadora da list */

	tpElemLista * pOrigemLista ;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista ;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr ;
	/* Ponteiro para o elemento corrente da lista */

	int numElem ;
	/* Número de elementos da lista */

#ifdef _DEBUG 
	int idTipo;
	int tamValores;
#endif

} LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento( LIS_tppLista   pLista ,
	tpElemLista  * pElem   ) ;

static tpElemLista * CriarElemento( LIS_tppLista pLista, void* pValor  ) ;

static void LimparCabeca( LIS_tppLista pLista ) ;

static void RemoverElemento ( LIS_tppLista pLista, tpElemLista* pElem) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

LIS_tpCondRet LIS_CriarLista(char * id, LIS_tppLista *lista)
{

	LIS_tppLista pLista = NULL ;

	pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
	if ( pLista == NULL ) {
		return LIS_CondRetFaltouMemoria ;
	} /* if */

	LimparCabeca( pLista ) ;

	pLista->id = (char*)malloc(sizeof(char)*(strlen(id)+1));
	if(pLista->id == NULL) {
		return LIS_CondRetFaltouMemoria;
	} /* if */


#ifdef _DEBUG 
	CED_MarcarEspacoAtivo(pLista);
	pLista->tamValores = 0;
#endif

	strcpy(pLista->id, id);

	*lista = pLista ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Criar lista */


/***************************************************************************
*
*  Função: LIS  &Obter ID Lista
*  ****/

LIS_tpCondRet LIS_ObterIdLista(LIS_tppLista pLista, char* id)
{
	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	strcpy(id, pLista->id);

	return LIS_CondRetOK;

} /* Fim função: LIS  &Obter ID Lista*/


/***************************************************************************
*
*  Função: LIS  &Obter Nó Corrente
*  ****/

LIS_tpCondRet LIS_ObterNo(LIS_tppLista  pLista, void** valor)
{

	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	*valor = pLista->pElemCorr->pValor;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Obter Nó Corrente


  /***************************************************************************
  *
  *  Função: LIS  &Ir Proximo
  *  ****/

LIS_tpCondRet LIS_IrProx(LIS_tppLista  pLista)
{

	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	if (pLista->pElemCorr->pProx == NULL) {
		return LIS_CondRetNoCorrenteUltimo ;
	} 

	pLista->pElemCorr = pLista->pElemCorr->pProx;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Ir Proximo


  /***************************************************************************
  *
  *  Função: LIS  &Ir para o elemento inicial
  *  ****/

LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista )
{

	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pLista->pElemCorr = pLista->pOrigemLista ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir Anterior
*  ****/

LIS_tpCondRet LIS_IrAnt(LIS_tppLista pLista)
{

	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */


	if (pLista->pElemCorr->pAnt == NULL) {
		return LIS_CondRetNoCorrentePrimeiro ;
	} 

	pLista->pElemCorr = pLista->pElemCorr->pAnt;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Ir Anterior

  /***************************************************************************
  *
  *  Função: LIS  &Alterar Nó Corrente
  *  ****/

LIS_tpCondRet LIS_AlterarNoCorrente(LIS_tppLista pLista, void* pValorNovo)
{

	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pLista->pElemCorr->pValor = pValorNovo;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Obter Nó Corrente


  /***************************************************************************
  *
  *  Função: LIS  &Destruir lista
  *  ****/

LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
{

	if (pLista == NULL) {
		return LIS_CondRetListaInexistente;
	} /* if */

	LIS_EsvaziarLista( pLista ) ;

	free( pLista ) ;

#ifdef _DEBUG 
	CED_MarcarEspacoNaoAtivo(pLista);
#endif

	pLista = NULL;

	return LIS_CondRetOK ;


} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista( LIS_tppLista pLista )
{

	tpElemLista * pElem ;
	tpElemLista * pProx ;

	pElem = pLista->pOrigemLista ;
	while ( pElem != NULL )
	{
		pProx = pElem->pProx ;
		LiberarElemento( pLista , pElem ) ;
		pElem = pProx ;
	} /* while */

	LimparCabeca( pLista ) ;

} /* Fim função: LIS  &Esvaziar lista */


/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista , void * pValor ) {
	tpElemLista * pElem ;

#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

	/* Criar elemento a inerir antes */

	pElem = CriarElemento( pLista , pValor ) ;
	if ( pElem == NULL ) {
		return LIS_CondRetFaltouMemoria ;
	} /* if */

	/* Encadear o elemento antes do elemento corrente */

	if ( pLista->pElemCorr == NULL ) {
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else {
		if ( pLista->pElemCorr->pAnt != NULL ) {
			pElem->pAnt  = pLista->pElemCorr->pAnt ;
			pLista->pElemCorr->pAnt->pProx = pElem ;
		} else {
			pLista->pOrigemLista = pElem ;
		} /* if */

		pElem->pProx = pLista->pElemCorr ;
		pLista->pElemCorr->pAnt = pElem ;
	} /* if */

	pLista->pElemCorr = pElem ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir No apos
*  ****/

LIS_tpCondRet LIS_InserirNo(LIS_tppLista pLista , void* pValor )  
{
	tpElemLista* pElem;

	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	/* Criar elemento a inserir ap�s */

	pElem = CriarElemento(pLista, pValor);
	if ( pElem == NULL )
	{
		return LIS_CondRetFaltouMemoria ;
	} /* if */

	/* Encadear o elemento ap�s o elemento */

	if ( pLista->pElemCorr == NULL )
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else {
		if ( pLista->pElemCorr->pProx != NULL ) {
			pElem->pProx  = pLista->pElemCorr->pProx ;
			pLista->pElemCorr->pProx->pAnt = pElem ;
		} else {
			pLista->pFimLista = pElem ;
		} /* if */

		pElem->pAnt = pLista->pElemCorr ;
		pLista->pElemCorr->pProx = pElem ;

	} /* if */

#ifdef _DEBUG 
	if (pLista->numElem == 1) {
		pLista->idTipo = CED_ObterTipoEspaco(pValor);
	}

	pElem->idTipo = CED_ObterTipoEspaco(pValor);
	pElem->tamValor = CED_ObterTamanhoValor(pValor);
	pElem->pCabeca = pLista;
	pLista->tamValores += pElem->tamValor;
#endif

	pLista->pElemCorr = pElem ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirNoCorrente( LIS_tppLista pLista )
{

	tpElemLista * pElem ;

	if ( pLista == NULL )
	{
		return LIS_CondRetListaInexistente ;
	} /* if */

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pElemCorr ;

	/* Desencadeia à esquerda */

	if ( pElem->pAnt != NULL )
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} 
	else {
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia à direita */

	if ( pElem->pProx != NULL )
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} 
	else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	LiberarElemento( pLista , pElem ) ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
	void * pValor        )
{

	tpElemLista * pElem ;

#ifdef _DEBUG
	assert( pLista  != NULL ) ;
#endif

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	for ( pElem  = pLista->pElemCorr ;
		pElem != NULL ;
		pElem  = pElem->pProx )
	{
		if ( pElem->pValor == pValor )
		{
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */
	} /* for */

	return LIS_CondRetNaoAchou ;

} /* Fim função: LIS  &Procurar elemento contendo valor */


/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
{

	tpElemLista * pElem ;

#ifdef _DEBUG
	assert( pLista  != NULL ) ;
#endif

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pElemCorr ;

	/* Desencadeia à esquerda */

	if ( pElem->pAnt != NULL )
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} else {
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia à direita */

	if ( pElem->pProx != NULL )
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	LiberarElemento( pLista , pElem ) ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Excluir elemento */

/*****************************************************************************
*
*  $FC Funcao: LIS - Remover elemento com free opcional
*
*  $ED Descricao da funcao
*  Remove pElem de pLista, refazendo todas as ligacoes entre o elemento anterior
*  e sucessor, e remove o conteudo armazenado no pElem.
*  - darFree deve ser 1 para que o espaco seja destruido, 0 caso contrario.
*
*****************************************************************************/

void RemoverElemento ( LIS_tppLista pLista, tpElemLista* pElem) {
	tpElemLista* pElemAnterior = pElem->pAnt;
	tpElemLista* pElemSucessor = pElem->pProx;

#ifdef _DEBUG
	CNT_CONTAR("RemoverElemento");
#endif

	// Refaz ligacao do elemento anterior
	if(pElemAnterior != NULL) {
#ifdef _DEBUG
		CNT_CONTAR("RemoverElemento-if-pElemAnterior-diferente-de-NULL");
#endif

		if(LIS_ProcurarValor(pLista, pElem->pValor) == LIS_CondRetOK) {
			if(LIS_IrAnt(pLista) == LIS_CondRetOK) {
				pLista->pElemCorr->pProx = pElemSucessor;
			} else {
				pLista->pOrigemLista = pElemSucessor;
			}
		}
	}

	// Remove ligacao com elemento sucessor
	if(pElemSucessor != NULL) {
#ifdef _DEBUG
		CNT_CONTAR("RemoverElemento-if-pElemSucessor-diferente-de-NULL");
#endif
		if(LIS_ProcurarValor(pLista, pElem->pValor) == LIS_CondRetOK) {
			if(LIS_IrProx(pLista) == LIS_CondRetOK) {
				pLista->pElemCorr->pAnt = pElemAnterior;
			} else {
				pLista->pFimLista = pElemAnterior;
			}
		}
	}
}



/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

void LiberarElemento( LIS_tppLista   pLista ,
	tpElemLista  * pElem   )
{
	free(pElem->pValor);

	free( pElem ) ;

#ifdef _DEBUG
	CED_MarcarEspacoNaoAtivo(pElem);
	pLista->tamValores -= pElem->tamValor;
#endif

	pLista->numElem-- ;

} /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento( LIS_tppLista pLista , void* pValor)
{

	tpElemLista* pElem ;

	pElem = (tpElemLista*)malloc(sizeof(tpElemLista));
	if ( pElem == NULL )
	{
		return NULL ;
	} /* if */

#ifdef _DEBUG
	CED_MarcarEspacoAtivo(pElem);
#endif

	pElem->pValor = pValor ;
	pElem->pAnt   = NULL  ;
	pElem->pProx  = NULL  ;

	pLista->numElem ++ ;

	return pElem ;

} /* Fim função: LIS  -Criar o elemento */



/***********************************************************************
*
*  $FC Função: LIS  -Obter numero de elementos da lista
*
***********************************************************************/

LIS_tpCondRet LIS_ObterNumElementos(LIS_tppLista pLista, int *numElementos) {
	if (pLista == NULL) {
		return LIS_CondRetListaInexistente;
	}

	*numElementos = pLista->numElem;

	return LIS_CondRetOK;
} /* Fim função: LIS  -Obter numero de elementos */

/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

void LimparCabeca( LIS_tppLista pLista )
{

	pLista->pOrigemLista = NULL ;
	pLista->pFimLista = NULL ;
	pLista->pElemCorr = NULL ;
	pLista->numElem   = 0 ;

} /* Fim função: LIS  -Limpar a cabeça da lista */


#ifdef _DEBUG
/***********************************************************************
*
*  $FC FunÁ„o: LIS Verificar estrutura
*
***********************************************************************/


LIS_tpCondRet LIS_VerificarEstrutura( LIS_tppLista pLista, int * numErros ) {
	int cont = 0, qtd = 0;
	(*numErros) = 0;

	if (pLista != NULL) {
		CNT_CONTAR("TAB-lista-existe");

		if (pLista->numElem == 0) {
			CNT_CONTAR("TAB-lista-vazia");

			if (pLista->pElemCorr == pLista->pOrigemLista && pLista->pElemCorr == pLista->pFimLista && pLista->pElemCorr == NULL) {
				CNT_CONTAR("TAB-tabuleiro-vazio-origem-fim-corrente-nulo");
			} else {
				CNT_CONTAR("TAB-tabuleiro-vazio-origem-fim-corrente-nao-nulo");
				(*numErros)++;
			}

			if (pLista->tamValores != 0) {
				CNT_CONTAR("TAB-tabuleiro-vazio-tam-diferente-0");
				(*numErros)++;
            } else {
                CNT_CONTAR("TAB-tabuleiro-vazio-tam-0");
            }
		}
		else {
			if (pLista->pElemCorr == NULL) {
				CNT_CONTAR("TAB-elem-corrente-nulo-tabuleiro-populado");
				(*numErros)++;
				return;
            } else {
                CNT_CONTAR("TAB-elem-corrente-nao-nulo-tabuleiro-populado");
            }

			if (pLista->numElem == 1) {
				CNT_CONTAR("TAB-unico-elemento");

				if (pLista->pElemCorr == pLista->pOrigemLista && pLista->pElemCorr == pLista->pFimLista) {
					CNT_CONTAR("TAB-tabuleiro-de-um-elemento-corrente-igual-fim-igual-inicio");
				}  else {
					CNT_CONTAR("TAB-tabuleiro-de-um-elemento-corrente-diferente-fim-diferente-inicio");
					(*numErros)++;
				}
			}

			if (pLista->pElemCorr != pLista->pOrigemLista) {
				CNT_CONTAR("TAB-corrente-diferente-origem");

				if (pLista->pElemCorr->pAnt != NULL) {
					CNT_CONTAR("TAB-anterior-corrente-nao-nulo");
					if (pLista->pElemCorr->pAnt->pProx != pLista->pElemCorr) {
						CNT_CONTAR("TAB-prox-anterior-diferente-corrente");
						(*numErros)++;
                    } else {
                        CNT_CONTAR("TAB-prox-anterior-igual-corrente");
                    }
				} else {
					CNT_CONTAR("TAB-anterior-corrente-nulo");
				}
			}

			if (pLista->pElemCorr != pLista->pFimLista) {
				CNT_CONTAR("TAB-corrente-diferente-fim");

				if (pLista->pElemCorr->pProx != NULL) {
					CNT_CONTAR("TAB-proximo-corrente-nao-nulo");
					if (pLista->pElemCorr->pProx->pAnt != pLista->pElemCorr) {
						CNT_CONTAR("TAB-anterior-prox-diferente-corrente");
						(*numErros)++;
                    } else {
                        CNT_CONTAR("TAB-anterior-prox-igual-corrente");
                    }
				} else {
					CNT_CONTAR("TAB-proximo-corrente-nulo");
				}

			}

			LIS_IrInicioLista(pLista);
			do {
				CNT_CONTAR("TAB-while");
				cont += pLista->pElemCorr->tamValor;

				if (pLista->pElemCorr->tamValor != CED_ObterTamanhoValor(pLista->pElemCorr->pValor)) {
					CNT_CONTAR("TAB-tam-valor-nao-compativel");
					(*numErros)++;
                } else {
                    CNT_CONTAR("TAB-tam-valor-compativel");
                }

				if (pLista->pElemCorr->idTipo != CED_ObterTipoEspaco(pLista->pElemCorr->pValor)) {
					CNT_CONTAR("TAB-id-no-nao-compativel");
					(*numErros)++;
                } else {
                    CNT_CONTAR("TAB-id-no-compativel");
                }

				if (pLista->pElemCorr->idTipo != pLista->idTipo) {
					CNT_CONTAR("TAB-id-no-nao-compativel-com-id-tabuleiro");
					(*numErros)++;
                } else {
                    CNT_CONTAR("TAB-id-no-compativel-com-id-tabuleiro");
                }

				if (pLista->pElemCorr->pCabeca != pLista) {
					CNT_CONTAR("TAB-cabeca-no-diferente-cabeca-tabuleiro");
					(*numErros)++;
                } else {
                    CNT_CONTAR("TAB-cabeca-no-igual-cabeca-tabuleiro");
                }

				qtd++;
			} while (LIS_IrProx(pLista) != LIS_CondRetNoCorrenteUltimo) ;


			if (pLista->numElem != qtd) {
				CNT_CONTAR("TAB-tam-tabuleiro-errado");
				(*numErros)++;
            } else {
                CNT_CONTAR("TAB-tam-tabuleiro-certo");
            }
			if (pLista->tamValores != cont) {
				CNT_CONTAR("TAB-tam-valores-errado");
				(*numErros)++;
            } else {
                CNT_CONTAR("TAB-tam-valores-certo");
            }

		}
	} else {
		if (CED_EhEspacoAtivo(pLista)) {
			CNT_CONTAR("TAB-tabuleiro-inexistente-espaco-ativo");
			(*numErros)++;
		}
	}

	return LIS_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: LIS Deturpar estrutura
*
***********************************************************************/

LIS_tpCondRet LIS_Deturpar( LIS_tppLista pLista, int cmd , int pos) {
    int i;
    tpElemLista* pElem;
	void* pValor;
	int concluido = 0;

    LIS_IrInicioLista(pLista);
    
    for (i=0; i<pos; i++) {
        LIS_IrProx(pLista);
    }
    
	pElem = pLista->pElemCorr;

	switch(cmd) {
	case 1:
		LIS_ExcluirNoCorrente(pLista);
		break;
	case 2:
		if(pElem->pProx != NULL) {
			pElem->pProx = NULL;
			concluido = 1;
		}
		break;
	case 3:
		if(pElem->pAnt != NULL) {
			pElem->pAnt = NULL;
			concluido = 1;
		}
		break;
	case 4:
		LIS_IrInicioLista(pLista);
		pElem = pLista->pElemCorr->pProx;
		if (pElem != NULL) {
			pElem = (tpElemLista*)0x00012345;
			concluido = 1;
		}
		break;
	case 5:
		pElem = pElem->pAnt;
		if(pElem != NULL) {
			pElem = (tpElemLista*)0x00012345;
			concluido = 1;
		}
		break;
	case 6:
		LIS_ObterNo(pLista, &pValor);
		if(pValor != NULL) {
			pElem->pValor = NULL;
			concluido = 1;
		}
		break;
	case 7:
		if(pElem != NULL) {
			pElem->idTipo = 99;
			concluido = 1;
		}
		break;
	case 8:
		if(pElem != NULL) {
			RemoverElemento(pLista, pElem);
			CED_MarcarEspacoNaoAtivo(pElem);
			concluido = 1;
		}
		break;
	case 9:
		if(pElem != NULL) {
			pElem = NULL;
			concluido = 1;
		}
		break;
	default:
		break;
	}
	return LIS_CondRetOK;
}


#endif

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
