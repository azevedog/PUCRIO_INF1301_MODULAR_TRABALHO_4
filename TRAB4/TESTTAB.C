/***************************************************************************
*  $MCI MÛdulo de implementaÁ„o: TTAB Teste tabuleiro de xadrez
*
*  Arquivo gerado:              TestTAB.c
*  Letras identificadoras:      TTAB
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas
*			mcs - Maria Carolina Santos
*			gbha - Gustavo Azevedo
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  5 	  mcs	15/dez/2016	mudanças para t4
*     4        fpf   04/out/2016  desenvolvimento de testes
*     3        mmq   04/out/2016  desenvolvimento de testes
*     2        fpf   02/out/2016  implementaÁ„o do esqueleto
*     1        mmq   02/out/2016  inÌcio do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Tabuleiro.h"

#ifdef _DEBUG
	
#include "CESPDIN.H"

#endif


static const char CRIAR_TABULEIRO_CMD         [ ] = "=criarTab"		;
static const char INSERIR_PECA_CMD            [ ] = "=inserirPeca"	;
static const char MOVER_PECA_CMD			  [ ] = "=moverPeca"	;
static const char RETIRAR_PECA_CMD			  [	] = "=retirarPeca"	;
static const char OBTER_PECA_CMD			  [ ] = "=obterPeca"	;
static const char OBTER_LIS_AMDO_CMD		  [ ] = "=obterLisAmdo"	;
static const char OBTER_LIS_AMTE_CMD		  [ ] = "=obterLisAmte"	;
static const char DESTRUIR_TABULEIRO_CMD      [ ] = "=destruirTab"	;

#ifdef _DEBUG
	#define DETURPAR_TABULEIRO_CMD  "=deturpar"
	#define VERIFICAR_TABULEIRO_CMD "=verificar"            
#endif


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NULO     0
#define NAO_NULO 1

#define DIM_VT_TABULEIRO   10

#define DIM_VALOR     100

TAB_tppTabuleiro vtTabuleiros[DIM_VT_TABULEIRO];

/***** ProtÛtipos das funÁıes encapuladas no mÛdulo *****/

static int  ValidarInxTab( int inxTab , int Modo ) ;

/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/


/***********************************************************************
*
*  $FC FunÁ„o: TTAB &Testar tabuleiro
*
*  $ED DescriÁ„o da funÁ„o
*     Podem ser criadas atÈ 10 tabuleiros, identificados pelos Ìndices 0 a 9
*
*     Comandos disponÌveis:
*
*     =criarTab			inxTabuleiro							CondRetEsp
*     =inserirPeca		inxTabuleiro	nome	cor		coord	CondRetEsp 
*     =moverPeca		inxTabuleiro	orig	dest			CondRetEsp
*     =retirarPeca		inxTabuleiro	coord					CondRetEsp
*     =obterPeca		inxTabuleiro	coord	NomeEsp	CorEsp	CondRetEsp
*     =obterLisAmdo		inxTabuleiro	coord					CondRetEsp
*     =obterLisAmte		inxTabuleiro	coord					CondRetEsp
*     =destruirTab		inxTabuleiro							CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int inxTab   = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;

	TST_tpCondRet CondRet = TST_CondRetOK;
	TST_tpCondRet CondRetAux = TST_CondRetOK;

	char corDado;
	char nomeDado[4];
	char coordOrigDado[3];
	char coordDestDado[3];

	LIS_tppLista listaAux;

	char   pCor;
	char * pNome;

	#ifdef _DEBUG
		int tipoDeturpacao;
		int numErros;
		int errosEsperados;
	#endif

	/* TAB  &Criar tabuleiro */

		if ( strcmp( ComandoTeste , CRIAR_TABULEIRO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (    ( numLidos != 2 )
				 || ( ! ValidarInxTab( inxTab , VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_CriarTabuleiro( &vtTabuleiros[inxTab] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao criar tabuleiro." ) ;

		} /* fim ativa: TAB  &Criar tabuleiro */

	/* TAB  &Inserir peca */

		if ( strcmp( ComandoTeste , INSERIR_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "iscsi" , 
					&inxTab, nomeDado, &corDado, coordDestDado, &CondRetEsp );

			if (   ( numLidos != 5 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_InserirPeca( &vtTabuleiros[inxTab], nomeDado, corDado, coordDestDado );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao inserir peca." ) ;

		} /* fim ativa: TAB  &Inserir peca */


	/* TAB  &Mover peca */

		if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "issi" , 
				&inxTab, coordOrigDado, coordDestDado, &CondRetEsp );

			if (   ( numLidos != 4 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_MoverPeca( &vtTabuleiros[inxTab], coordOrigDado, coordDestDado );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao mover peca." ) ;

		} /* fim ativa: TAB  &Mover peca */


	/* TAB  &Retirar peca */

		if ( strcmp( ComandoTeste , RETIRAR_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros("isi", &inxTab, coordOrigDado, &CondRetEsp);

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_RetirarPeca( &vtTabuleiros[inxTab], coordOrigDado );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao retirar peca." ) ;

		} /* fim ativa: TAB  &Retirar peca */


	/* TAB  &Obter peca */

		if ( strcmp( ComandoTeste , OBTER_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "iscsi" , 
				&inxTab, coordOrigDado, &corDado, nomeDado, &CondRetEsp );

			if (   ( numLidos != 5 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_ObterPeca( &vtTabuleiros[inxTab], coordOrigDado, &pCor, &pNome );

			CondRet = TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao obter peca." );
			if(    CondRet    != TST_CondOK 
				|| CondRetEsp == TAB_CondRetNaoExiste
				|| CondRetEsp == TAB_CondRetCasaVazia
				|| CondRetEsp == TAB_CondRetCasaInexistente )
			{
				return CondRet;
			}

			CondRet = TST_CompararChar( corDado, pCor, "Cor da peca diferente da esperada." );
			if( CondRet != TST_CondOK	)
			{
				return CondRet;
			}

			return TST_CompararString( nomeDado, pNome, "Tipo de peca diferente do esperado." );

		} /* fim ativa: TAB  &Obter peca */


	/* TAB  &Obter lista ameaÁantes */

		if ( strcmp( ComandoTeste , OBTER_LIS_AMTE_CMD ) == 0 )
		{

			numLidos = LER_LerParametros("isi", &inxTab, coordOrigDado, &CondRetEsp);

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_ObterListaAmeacantes(&vtTabuleiros[inxTab], coordOrigDado, &listaAux);

			CondRetAux = TST_CompararPonteiroNulo(NAO_NULO, listaAux, "Ponteiro para lista nulo.");
			
			if (CondRetAux != TST_CondOK)
			{
				return CondRetAux;
			}

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao obter lista ameacantes." ) ;

		} /* fim ativa: TAB  &Obter lista ameaÁantes */


	/* TAB  &Obter lista ameaÁados */

		if ( strcmp( ComandoTeste , OBTER_LIS_AMDO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros("isi", &inxTab, coordOrigDado, &CondRetEsp);

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_ObterListaAmeacados(&vtTabuleiros[inxTab], coordOrigDado, &listaAux);

			CondRetAux = TST_CompararPonteiroNulo(NAO_NULO, listaAux, "Ponteiro para lista nulo.");

			if (CondRetAux != TST_CondOK)
			{
				return CondRetAux;
			}

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao obter lista ameacados." ) ;

		} /* fim ativa: TAB  &Obter lista ameaÁados */



	/* TAB  &Destruir tabuleiro */

		else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			#ifdef _DEBUG
				CED_InicializarIteradorEspacos();
				while( CED_ExisteEspacoCorrente() != 0){
					CED_ExcluirEspacoCorrente();
				}
			#endif

			CondRet = TAB_DestruirTabuleiro( &vtTabuleiros[inxTab] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao destruir tabuleiro." ) ;

		} /* fim ativa: TAB  &Destruir tabuleiro */

/* Testar TAB deturpar tabuleiro */
#ifdef _DEBUG
		/* Realizar deturpacao */
        else if ( strcmp( ComandoTeste , DETURPAR_TABULEIRO_CMD  ) == 0 ) {

            NumLidos = LER_LerParametros( "ii" , &inxTab, &tpDeturpacao) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			return TST_CompararInt( PIL_CondRetOK , PIL_Deturpa(&vtTabuleiros[inxTab], tpDeturpacao),
                     "Erro ao deturpar."  ) ;

        } /* fim ativa: Realizar deturpacao */

		/* Realizar verificao estrututral */
        else if ( strcmp( ComandoTeste , VERIFICAR_TABULEIRO_CMD  ) == 0 ) {

			NumLidos = LER_LerParametros( "ii" , &inxTab, &errosEsperados) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
           
			PIL_Verifica( &vtTabuleiros[inxTab], &numErros );

            return TST_CompararInt( errosEsperados , numErros ,
                     "Total de erros errado ao verificar estrutura."  ) ;
		}

#endif


		

	return TST_CondRetNaoConhec ;
} /* Fim funÁ„o: TTAB &Testar tabuleiro */


/*****  CÛdigo das funÁıes encapsuladas no mÛdulo  *****/

/***********************************************************************
*
*  $FC FunÁ„o: TTAB -Validar indice do tabuleiro
*
***********************************************************************/

int ValidarInxTab( int inxTab , int Modo )
{

	if (   ( inxTab <  0 )
		|| ( inxTab >= DIM_VT_TABULEIRO ) )
	{
		return FALSE ;
	} /* if */

	if ( Modo == VAZIO )
	{
		if ( vtTabuleiros[ inxTab ] != NULL )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vtTabuleiros[ inxTab ] == NULL )
		{
			return FALSE ;
		} /* if */
	} /* if */

	return TRUE ;

} /* Fim funÁ„o: TTAB -Validar indice do tabuleiro */

/********** Fim do mÛdulo de implementaÁ„o: TTAB Teste tabuleiro de xadrez **********/

