/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"

static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char INSERIR_NO_CMD          [ ] = "=inserirno"      ;
static const char OBTER_ID_LISTA_CMD      [ ] = "=obterIdLista"   ;
static const char OBTER_NO_CMD            [ ] = "=obterno"        ;
static const char EXCLUIR_NO_CMD          [ ] = "=excluirno"      ;
static const char IR_PROX_CMD             [ ] = "=irprox"         ;
static const char IR_ANT_CMD              [ ] = "=irant"          ;
static const char ALTERAR_NO_CMD	      [ ] = "=alterarno"      ;
static const char CRIAR_MATRIZ_CMD		  [ ] = "=criarmatriz"	  ;		 

#ifdef _DEBUG
static const char DETURPAR_LISTA_CMD      [ ] = "=deturpar"             ;
static const char VERIFICAR_LISTA_CMD     [ ] = "=verificar"            ;
#endif

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR       5

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ComparaStrings( void * pValorElem, void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarLista                   inxLista  string  CondRet
*     =obterIdLista                 inxLista  string  CondRet
*     =inserirNo                    inxLista  char  CondRet
*     =obterNo                      inxLista  char  CondRet
*     =excluirNo                    inxLista  CondRet
*     =irProx                       inxLista  CondRet
*     =irAnt                        inxLista  CondRet
*     =alterarNo                    inxLista  char  CondRet
*     =destruirlista                inxLista  CondRet
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char StringDado[DIM_VALOR] ;
      char CharDado;
      char * cDado;
      char * pDado ;
  
      int i ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || (strlen(StringDado) > 4))
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;

            CondRet = LIS_CriarLista( pDado,  &vtListas[inxLista]) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar lista.") ;

         } /* fim ativa: Testar CriarLista */

        /* Testar obter id lista */

         else if ( strcmp( ComandoTeste , OBTER_ID_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 ))
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = (char*) malloc(sizeof(strlen(StringDado) + 1));
			
			if(pDado == NULL) {
				return TST_CondRetMemoria;
			}

			strcpy(pDado, StringDado);

            CondRet = LIS_ObterIdLista( vtListas[ inxLista ], pDado) ;

            if ( CondRet != LIS_CondRetOK )
            {
               return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao obter id lista.") ;
            } /* if */

            return TST_CompararString( StringDado , pDado ,
                         "Id lista errado." ) ;

         } /* fim ativa: Testar obter id lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao destruir lista.") ;

         } /* fim ativa: Testar Destruir lista */


      /* Testar inserir elemento */

         else if ( strcmp( ComandoTeste , INSERIR_NO_CMD ) == 0 )
         {


			numLidos = LER_LerParametros( "ici" ,
					&inxLista , &CharDado , &CondRetEsp ) ;

			if ( numLidos != 3 )
			{
				return TST_CondRetParm ;
			} /* if */

			pDado = ( char * ) malloc( sizeof( char ) ) ;
			if ( pDado == NULL )
			{
				return TST_CondRetMemoria ;
			} /* if */

			*pDado = CharDado;

			CondRet = LIS_InserirNo( vtListas[ inxLista ] , pDado ) ;

			if ( CondRet != LIS_CondRetOK )
			{
				free( pDado ) ;
			} /* if */

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao inserir no." ) ;

         } /* fim ativa: Testar inserir elemento */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXCLUIR_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirNoCorrente( vtListas[ inxLista ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ici" ,
                       &inxLista , &CharDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 ))
            {
               return TST_CondRetParm ;
            } /* if */

			cDado = (char*) malloc(sizeof(char));
			if(cDado == NULL) {
				return TST_CondRetMemoria;
			}
			*cDado = CharDado;

            CondRet = LIS_ObterNo( vtListas[ inxLista ], (void**)&cDado) ;

            if ( CondRet != CondRetEsp )
            {
               return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao obter no.") ;
            } /* if */

			if (CondRet == LIS_CondRetListaVazia || CondRet == LIS_CondRetListaInexistente) {
				return TST_CondRetOK;
			} /* if */

            return TST_CompararChar( CharDado , *cDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

        /* Testar alterar valor do elemento corrente */

         else if ( strcmp( ComandoTeste , ALTERAR_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ici" ,
                       &inxLista , &CharDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 ))
            {
               return TST_CondRetParm ;
            } /* if */

			
			cDado = (char*) malloc(sizeof(char));

			if(cDado == NULL) {
				return TST_CondRetMemoria;
			}

			*cDado = CharDado;

            CondRet = LIS_AlterarNoCorrente( vtListas[ inxLista ], cDado) ;

            if ( CondRet != CondRetEsp )
            {
               return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao alterar elemento corrente.") ;
            } /* if */

            return TST_CompararChar( CharDado , *cDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar alterar valor do elemento corrente */

      /* LIS  &Ir Proximo */

         else if ( strcmp( ComandoTeste , IR_PROX_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_IrProx( vtListas[ inxLista ] ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Ir Proximo */


      /* LIS  &Ir Anterior */

         else if ( strcmp( ComandoTeste , IR_ANT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_IrAnt( vtListas[ inxLista ] ) ,
                      "Condicao de retorno errada ao retornar" ) ;

         } /* fim ativa: LIS  &Ir Anterior */

#ifdef _DEBUG
    /* Realizar deturpacao */
        else if ( strcmp( ComandoTeste , DETURPAR_LISTA_CMD  ) == 0 ) {
            int cmd;
            numLidos = LER_LerParametros( "ii" , &inxLista, &cmd) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

      return TST_CompararInt( LIS_CondRetOK , LIS_Deturpar(vtListas[ inxLista ], cmd),
                     "Erro ao deturpar."  ) ;

        } /* fim ativa: Realizar deturpacao */

    /* Realizar verificao estrututral */
        else if ( strcmp( ComandoTeste , VERIFICAR_LISTA_CMD  ) == 0 ) {
            int numErros, numErrosEsp;

            numLidos = LER_LerParametros( "ii" , &inxLista, &numErrosEsp) ;

            if ( numLidos != 2  )
            {
               return TST_CondRetParm ;
            } /* if */
           
      LIS_VerificarEstrutura( vtListas[ inxLista ], &numErros );

            return TST_CompararInt( numErrosEsp , numErros ,
                     "Total de erros errado ao verificar estrutura."  ) ;

        } /* fim ativa: Realizar verificao estrututral */

#endif

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */



/***********************************************************************
*
*  $FC Função: TLIS -Compara valor
*
***********************************************************************/

   int ComparaStrings( void * pValorElem, void * pValor )
   {
     if( strcmp( (char *) pValorElem, (char *) pValor ) == 0 )
     {
       return TRUE;
     }
      
     return FALSE;

   } /* Fim função: TLIS -Compara valor */

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

