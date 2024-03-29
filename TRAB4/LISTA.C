/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs - Arndt Von Staa
*           fpf - Felipe Pessoa de Freitas
*           mmq - Matheus de Mello Queiroz
*           mcs - Maria Carolina Marinho
*           gbha - Gustavo Azevedo
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     8       mcs   10/dez/2016 Adicionar funcoes para o T4
*	   7		  fpf	 01/out/2016	Altera��o das fun��es para somente retornar tpCondRet
*     6       mmq   23/set/2016 adaptar para a utilizacao na aplicacao "Juiz de Xadrez"
*     5       mmq   11/set/2016 alterar a fun��o LIS_ProcuraValor
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
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
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

		 char * pIdLista;
			   /* Identificador da Lista */

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

   } LIS_tpLista ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

   static void LimparCabeca( LIS_tppLista pLista ) ;

   static void EsvaziarLista( LIS_tppLista pLista ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static LIS_tpCondRet AvancarElementoCorrente( LIS_tppLista pLista ,
										  int numElem ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

#ifdef _DEBUG
tpElemLista * LIS_RetornaSucessor( LIS_tppLista pLista )
{
   return pLista->pElemCorr->pProx;
}

tpElemLista * LIS_RetornaAntecessor( LIS_tppLista pLista )
{
   return pLista->pElemCorr->pAnt;
}

tpElemLista * LIS_RetornaCorrente( LIS_tppLista pLista  )
{
   return (CAR_tppCarta)pLista->pElemCorr;
}

int LIS_VerificaCorrenteNull( LIS_tppLista pLista)
{
   if ( pLista->pElemCorr == NULL )
      return 1;
   return 0;
}

int LIS_QtdNos(LIS_tppLista pLista)
{
   return pLista->numElem;
}

int LIS_OrigemNula(LIS_tppLista pLista)
{
   if (pLista->pOrigemLista == NULL)
      return 1;
   return 0;
}

void LIS_AlteraSucessor( LIS_tppLista pLista )
{
   pLista->pElemCorr->pProx = NULL ;
}
void LIS_AlteraPredecessor( LIS_tppLista pLista )
{
   pLista->pElemCorr->pAnt = NULL ;
}

void LIS_AtribuiLixoSucessor( LIS_tppLista pLista )
{
   pLista->pElemCorr->pProx = 'x';
}

void LIS_AtribuiLixoPredecessor( LIS_tppLista pLista )
{
   pLista->pElemCorr->pAnt = 'x';
}


#endif

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista(char * id,
								void   ( * ExcluirValor ) ( void * pDado ), 
								LIS_tppLista * pLista1)
   {

	  LIS_tppLista pLista;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista ) ) ;
      if ( pLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( pLista ) ;

	  pLista->pIdLista = ( char * ) malloc( ( strlen( id ) + 1 ) * sizeof( char ) );
	  if( pLista-> pIdLista == NULL )
	  {
		  return LIS_CondRetFaltouMemoria;
	  } /* if */

	  strcpy( pLista->pIdLista, id );

      pLista->ExcluirValor = ExcluirValor ;

	  *pLista1 = pLista;

      return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Criar lista */

   /***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o identificador da lista
*  ****/

   LIS_tpCondRet LIS_ObterId(LIS_tppLista pLista, char ** pId)
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

	  *pId = pLista->pIdLista;

	  return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o identificador da lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento
*  ****/

   LIS_tpCondRet LIS_InserirElemento( LIS_tppLista pLista ,
                                          void * pValor      )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir ap�s */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterElemento( LIS_tppLista pLista,
									void ** pValor	)
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
        *pValor = NULL ;
		return LIS_CondRetListaVazia;
      } /* if */

	  *pValor = pLista->pElemCorr->pValor;

	  return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
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

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o proximo n�
*  ****/

   LIS_tpCondRet LIS_IrProxElemento( LIS_tppLista pLista  )
   {

	   return AvancarElementoCorrente( pLista, 1 );

   } /* Fim fun��o: LIS  &Ir para o proximo n� */
   
/***************************************************************************
*
*  Fun��o: LIS  &Ir para o n� anterior
*  ****/

   LIS_tpCondRet LIS_IrAntElemento( LIS_tppLista pLista  )
   {

	   return AvancarElementoCorrente( pLista, -1 );

   } /* Fim fun��o: LIS  &Ir para o n� anterior */

/***************************************************************************
*
*  Fun��o: LIS  &Andar para o n� inicial
*  ****/

   LIS_tpCondRet LIS_AndarInicio( LIS_tppLista pLista )
   {
		#ifdef _DEBUG
			assert( pLista != NULL ) ;
		#endif
		
		pLista->pElemCorr = pLista->pOrigemLista;
		return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Andar para o n� inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Alterar o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_AlterarElemento( LIS_tppLista pLista, 
									  void * pValor )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		  return LIS_CondRetListaVazia ;
      } /* if */

	  pLista->ExcluirValor( pLista->pElemCorr->pValor );
	  pLista->pElemCorr->pValor = pValor;

	  return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  LIS  &Alterar o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista(LIS_tppLista pLista)
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      EsvaziarLista( pLista ) ;

	  free( pLista->pIdLista );
      free( pLista ) ;

	  return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Destruir lista */



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {
	   pLista->pIdLista     = NULL;
      pLista->pOrigemLista = NULL ;
      pLista->pFimLista    = NULL ;
      pLista->pElemCorr    = NULL ;
      pLista->numElem      = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
***********************************************************************/

   void EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  -Esvaziar lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


   /***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Avancar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
***********************************************************************/

   LIS_tpCondRet AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetOrigemLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  -Avan�ar elemento */

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/