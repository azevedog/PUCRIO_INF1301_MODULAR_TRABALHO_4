/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs - Arndt Von Staa
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas
*			pf - Pedro Ferreira Alves Pinto
*
*  $HA Histórico de evolução:
*     Versão  Autor		Data		Observações
*	  10	  fpf		11/set/2016	funções LIS_InserirElementoAntes e LIS_InserirElementoApos encapsuladas no módulo
*     9       mmq		09/set/2016 correcao de bugs
*	  8		  fpf/pf	08/set/2016	adaptação das funções para tratar o novo tipo
*	  7		  fpf/pf	07/set/2016	implementação das funções LIS_InserirElementoOrdenado e LIS_ExibirConteudoLista
*	  6		  fpf		06/set/2016	implementação da função preencheEstrutura
*	  5		  fpf/pf	03/set/2016	implementação da estrutura a ser usada como valor
*     4       avs		01/fev/2006 criar linguagem script simbólica
*     3       avs		08/dez/2004 uniformização dos exemplos
*     2       avs		07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs		16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Estrutura iniciais-nomes
*
*
***********************************************************************/

	typedef struct tagConteudo {

		char * iniciais;
		char * nome;

	} tpConteudo;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

	typedef struct tagElemLista {

		tpConteudo * pValor;
		/* Ponteiro para o valor contido no elemento */

		struct tagElemLista * pAnt;
		/* Ponteiro para o elemento predecessor */

		struct tagElemLista * pProx;
		/* Ponteiro para o elemento sucessor */

	} tpElemLista;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

	typedef struct LIS_tagLista {

		tpElemLista * pOrigemLista;
		/* Ponteiro para a origem da lista */

		tpElemLista * pFimLista;
		/* Ponteiro para o final da lista */

		tpElemLista * pElemCorr;
		/* Ponteiro para o elemento corrente da lista */

		int numElem;
		/* Número de elementos da lista */

		void(*ExcluirValor) (tpConteudo * pValor);
		/* Ponteiro para a função de destruição do valor contido em um elemento */

	} LIS_tpLista;

/***** Protótipos das funções encapuladas no módulo *****/

	static void LiberarElemento(LIS_tppLista   pLista,
		tpElemLista  * pElem);

	static tpElemLista * CriarElemento(LIS_tppLista pLista,
		tpConteudo * pValor);

	static void LimparCabeca(LIS_tppLista pLista);

	static void preencheEstrutura(tpConteudo ** estrutura,
		char * iniciais, char * nome);

	static LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista,
		char * iniciais, char * nome);

	static LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista,
		char * iniciais, char * nome);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

	LIS_tppLista LIS_CriarLista(
		void(*ExcluirValor) (tpConteudo * pDado))
	{

		LIS_tpLista * pLista = NULL;

		pLista = (LIS_tpLista *)malloc(sizeof(LIS_tpLista));
		if (pLista == NULL)
		{
			return NULL;
		} /* if */

		LimparCabeca(pLista);

		pLista->ExcluirValor = ExcluirValor;

		return pLista;

	} /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

	void LIS_DestruirLista(LIS_tppLista pLista)
	{

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		LIS_EsvaziarLista(pLista);

		free(pLista);

	} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

	void LIS_EsvaziarLista(LIS_tppLista pLista)
	{

		tpElemLista * pElem;
		tpElemLista * pProx;

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		pElem = pLista->pOrigemLista;
		while (pElem != NULL)
		{
			pProx = pElem->pProx;
			LiberarElemento(pLista, pElem);
			pElem = pProx;
		} /* while */

		LimparCabeca(pLista);

	} /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

	LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista)
	{

		tpElemLista * pElem;

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		if (pLista->pElemCorr == NULL)
		{
			return LIS_CondRetListaVazia;
		} /* if */

		pElem = pLista->pElemCorr;

		/* Desencadeia à esquerda */

		if (pElem->pAnt != NULL)
		{
			pElem->pAnt->pProx = pElem->pProx;
			pLista->pElemCorr = pElem->pAnt;
		}
		else {
			pLista->pElemCorr = pElem->pProx;
			pLista->pOrigemLista = pLista->pElemCorr;
		} /* if */

		/* Desencadeia à direita */

		if (pElem->pProx != NULL)
		{
			pElem->pProx->pAnt = pElem->pAnt;
		}
		else
		{
			pLista->pFimLista = pElem->pAnt;
		} /* if */

		LiberarElemento(pLista, pElem);

		return LIS_CondRetOK;

	} /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

	tpConteudo * LIS_ObterValor(LIS_tppLista pLista)
	{

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		if (pLista->pElemCorr == NULL)
		{
			return NULL;
		} /* if */

		return pLista->pElemCorr->pValor;

	} /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

	void IrInicioLista(LIS_tppLista pLista)
	{

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		pLista->pElemCorr = pLista->pOrigemLista;

	} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

	void IrFinalLista(LIS_tppLista pLista)
	{

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		pLista->pElemCorr = pLista->pFimLista;

	} /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

	LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista,
		int numElem)
	{

		int i;

		tpElemLista * pElem;

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		/* Tratar lista vazia */

		if (pLista->pElemCorr == NULL)
		{

			return LIS_CondRetListaVazia;

		} /* fim ativa: Tratar lista vazia */

		/* Tratar avançar para frente */

		if (numElem > 0)
		{

			pElem = pLista->pElemCorr;
			for (i = numElem; i > 0; i--)
			{
				if (pElem == NULL)
				{
					break;
				} /* if */
				pElem = pElem->pProx;
			} /* for */

			if (pElem != NULL)
			{
				pLista->pElemCorr = pElem;
				return LIS_CondRetOK;
			} /* if */

			pLista->pElemCorr = pLista->pFimLista;
			return LIS_CondRetFimLista;

		} /* fim ativa: Tratar avançar para frente */

		/* Tratar avançar para trás */

		else if (numElem < 0)
		{

			pElem = pLista->pElemCorr;
			for (i = numElem; i < 0; i++)
			{
				if (pElem == NULL)
				{
					break;
				} /* if */
				pElem = pElem->pAnt;
			} /* for */

			if (pElem != NULL)
			{
				pLista->pElemCorr = pElem;
				return LIS_CondRetOK;
			} /* if */

			pLista->pElemCorr = pLista->pOrigemLista;
			return LIS_CondRetFimLista;

		} /* fim ativa: Tratar avançar para trás */

		/* Tratar não avançar */

		return LIS_CondRetOK;

	} /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

	LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista,
		char * iniciais, char * nome)
	{

		tpElemLista * pElem;

	#ifdef _DEBUG
		assert(pLista != NULL);
	#endif

		if (pLista->pElemCorr == NULL)
		{
			return LIS_CondRetListaVazia;
		} /* if */

		for ( pElem  = pLista->pOrigemLista;
			  pElem != NULL;
			  pElem  = pElem->pProx)
		{
			if ( strcmp(pElem->pValor->iniciais, iniciais) == 0 && 
				strcmp(pElem->pValor->nome, nome) == 0 )
			{
				pLista->pElemCorr = pElem;
				return LIS_CondRetOK;
			} /* if */
		} /* for */

		return LIS_CondRetNaoAchou;

	} /* Fim função: LIS  &Procurar elemento contendo valor */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento ordenado
*  ****/

	LIS_tpCondRet LIS_InserirElementoOrdenado(LIS_tppLista pLista,
		char * iniciais, char * nome)

	{
		int cmp;
		 
		tpElemLista * pElem;
		tpElemLista * aux;
		tpConteudo * conteudo;

	#ifdef _DEBUG
			assert(pLista != NULL);
	#endif

		preencheEstrutura(&conteudo, iniciais, nome);
		if (conteudo == NULL)
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		/* Criar elemento a inserir */

		pElem = CriarElemento(pLista, conteudo);
		if (pElem == NULL)
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		/* Encadear o elemento ordenado */
		
		if (pLista->pElemCorr == NULL)
		{
			pLista->pOrigemLista = pElem;
			pLista->pFimLista = pElem;
		}
		else
		{
			for (aux = pLista->pOrigemLista; aux != NULL; aux = aux->pProx)
			{
				cmp = strcmp(iniciais, aux->pValor->iniciais);
				if (cmp < 0)
				{
					break;
				}
			}

			if (aux == NULL)
			{
				pLista->pFimLista->pProx = pElem;
				pElem->pAnt = pLista->pFimLista;
				pLista->pFimLista = pElem;
			}
			else 
			{                               // null <-  novo  -> null | ant <-> aux    
				pElem->pProx = aux;         // null <-  novo  -> aux  | ant <-> aux
				aux->pAnt    = pElem;       // null <-  novo <-> aux  | ant  -> aux
		    //  pElem->pAnt = aux->pAnt;    // ant  <-  novo  -> aux  | ant <-> aux
		    //  pElem->pAnt->pProx = pElem; // ant  <-> novo <-> aux

				if( aux == pLista->pOrigemLista )
				{
					pLista->pOrigemLista = pElem;
				}
				else
				{
					pElem->pAnt        = aux->pAnt;  // ant  <-  novo  -> aux  | ant <-> aux
					pElem->pAnt->pProx = pElem;      // ant  <-> novo <-> aux
				}
			} /* if */


		} /* if */

		pLista->pElemCorr = pElem;

		return LIS_CondRetOK;

	} /* Fim função: LIS  &Inserir elemento ordenado */

/***************************************************************************
*
*  Função: LIS  &Exibir conteudo lista
*  ****/

	void LIS_ExibirConteudoLista(LIS_tppLista pLista)
	{

		tpElemLista * aux;

	#ifdef _DEBUG
			assert(pLista != NULL);
	#endif
		
		printf("\n\nINICIAIS\t\tNOME\n\n");
		
		for (aux = pLista->pOrigemLista; aux != NULL; aux = aux->pProx)
		{
			printf("%s\t\t%s\n",aux->pValor->iniciais,aux->pValor->nome);
		}

	} /* Fim função: LIS  &Exibir conteudo lista */


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

	void LiberarElemento(LIS_tppLista   pLista,
		tpElemLista  * pElem)
	{

		if ((pLista->ExcluirValor != NULL)
			&& (pElem->pValor != NULL))
		{
			pLista->ExcluirValor(pElem->pValor);
		} /* if */

		free(pElem);

		pLista->numElem--;

	} /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

	tpElemLista * CriarElemento(LIS_tppLista pLista,
		tpConteudo * pValor)
	{

		tpElemLista * pElem;

		pElem = (tpElemLista *)malloc(sizeof(tpElemLista));
		if (pElem == NULL)
		{
			return NULL;
		} /* if */

		pElem->pValor = pValor;
		pElem->pAnt = NULL;
		pElem->pProx = NULL;

		pLista->numElem++;

		return pElem;

	} /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

	void LimparCabeca(LIS_tppLista pLista)
	{

		pLista->pOrigemLista = NULL;
		pLista->pFimLista = NULL;
		pLista->pElemCorr = NULL;
		pLista->numElem = 0;

	} /* Fim função: LIS  -Limpar a cabeça da lista */

/***********************************************************************
*
*  $FC Função: LIS  -Preencher estrutura
*
***********************************************************************/

	void preencheEstrutura( tpConteudo ** estrutura, char * iniciais, char * nome )
	{
		( *estrutura ) = ( tpConteudo * ) malloc( sizeof ( tpConteudo ) );
		( *estrutura )->iniciais = ( char * ) malloc( strlen ( iniciais ) + 1 );
		( *estrutura )->nome = ( char * )malloc( strlen( nome ) + 1 );
		strcpy( ( * estrutura )->iniciais, iniciais );
		strcpy( ( * estrutura )->nome, nome );
	} /* Fim função: LIS  -Preencher estrutura */

/***********************************************************************
*
*  $FC Função: LIS  -Inserir elemento antes
*
***********************************************************************/

	LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista,
		char * iniciais, char * nome)
	{

		tpElemLista * pElem;
		tpConteudo * conteudo;

	#ifdef _DEBUG
			assert(pLista != NULL);
	#endif

		preencheEstrutura(&conteudo, iniciais, nome);
		if (conteudo == NULL)
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		/* Criar elemento a inserir antes */

		pElem = CriarElemento(pLista, conteudo);
		if (pElem == NULL)
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		/* Encadear o elemento antes do elemento corrente */

		if (pLista->pElemCorr == NULL)
		{
			pLista->pOrigemLista = pElem;
			pLista->pFimLista = pElem;
		}
		else
		{
			if (pLista->pElemCorr->pAnt != NULL)
			{
				pElem->pAnt = pLista->pElemCorr->pAnt;
				pLista->pElemCorr->pAnt->pProx = pElem;
			}
			else
			{
				pLista->pOrigemLista = pElem;
			} /* if */

			pElem->pProx = pLista->pElemCorr;
			pLista->pElemCorr->pAnt = pElem;
		} /* if */

		pLista->pElemCorr = pElem;

		return LIS_CondRetOK;

	} /* Fim função: LIS  -Inserir elemento antes */

/***********************************************************************
*
*  $FC Função: LIS  -Inserir elemento após
*
***********************************************************************/

	LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista,
		char * iniciais, char * nome)

	{

		tpElemLista * pElem;
		tpConteudo * conteudo;

	#ifdef _DEBUG
			assert(pLista != NULL);
	#endif

		preencheEstrutura(&conteudo, iniciais, nome);
		if (conteudo == NULL)
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		/* Criar elemento a inerir após */

		pElem = CriarElemento(pLista, conteudo);
		if (pElem == NULL)
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		/* Encadear o elemento após o elemento */

		if (pLista->pElemCorr == NULL)
		{
			pLista->pOrigemLista = pElem;
			pLista->pFimLista = pElem;
		}
		else
		{
			if (pLista->pElemCorr->pProx != NULL)
			{
				pElem->pProx = pLista->pElemCorr->pProx;
				pLista->pElemCorr->pProx->pAnt = pElem;
			}
			else
			{
				pLista->pFimLista = pElem;
			} /* if */

			pElem->pAnt = pLista->pElemCorr;
			pLista->pElemCorr->pProx = pElem;

		} /* if */

		pLista->pElemCorr = pElem;

		return LIS_CondRetOK;

	} /* Fim função: LIS  -Inserir elemento após */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

