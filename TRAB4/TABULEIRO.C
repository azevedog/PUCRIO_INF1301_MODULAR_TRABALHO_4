/***************************************************************************
*  $MCI M�dulo de implementa��o: TAB  Tabuleiro do Xadrez
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas	
*			mcs - Maria Carolina Santos
*			gbha - Gustavo Azevedo
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  7 	  mcs	15/dez/2016	mudan�as para t4
*     6       mmq    05/out/2016  revisao modulo e corre��es
*     5       mmq    04/out/2016  correcao de bugs
*     4       fpf    02/out/2016  desenvolvimento de fun��es
*     3       pf     02/out/2016  desenvolvimento de fun��es
*     2       fpf	 01/out/2016  implementa��o da estrutura do tabuleiro e fun��es
*     1       pf     25/set/2016  in�cio da implementa��o das pe�as
*
***************************************************************************/

#include   <stdlib.h>
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "TABULEIRO.H"

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#undef TABULEIRO_OWN

#define pathArquivo "PecasXadrez.txt"

#define FALSE 0
#define TRUE  1

#define COR_CASA_VAZIA  'u'
#define PECA_CASA_VAZIA "xxx"


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabe�a do Tabuleiro
*
*
***********************************************************************/

typedef struct TAB_tagTabuleiro
{
	LIS_tppLista pPecas;
		   /* Cabe�a da lista com as pe�as disponiveis */

	LIS_tppLista pMatriz;
		   /* Cabe�a da matriz */

	#ifdef _DEBUG
		char tipoTabuleiro;
		char quantidadeNos;
	#endif

} TAB_tpTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de pe�as
*
*
***********************************************************************/

typedef struct tagPeca{
	
	char nome[4];
			/* Nome da pe�a */

	LIS_tppLista pAndar;
			/* Ponteiro da Lista contendo os movimentos da pe�a de andar */

	LIS_tppLista pComer;
			/* Ponteiro da Lista contendo os movimentos da pe�a de comer */

} tpPeca;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de movimentos da pecas
*
*
***********************************************************************/

typedef struct tagMovimentoPeca{

	int coordenadas[4];
		/* Vetor de inteiros que representa as coordenadas Oeste = 0, 
		Norte = 1, Leste =2 e Sul = 3 */

	int max;
		/* Numero maximo de vezes que esse movimento pode ser repetido em uma jogada */

	int min;
		/* Numero minimo de vezes que esse movimento pode ser repetido em uma jogada */

	int primeiroMov;
		/* Movimento que so pode ser executado na primeira jogada daquela pe�a */

} tpMovimentoPeca;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de casas
*
*
***********************************************************************/

typedef struct tagCasa{

	#ifdef _DEBUG
		char tipoCasa;
	#endif

	char nome[4];
			/* Nome da pe�a na casa */

	char cor;
			/* Cor da pe�a na casa */

	int primeiroMov;
			/* Movimento que so pode ser executado na primeira jogada daquela pe�a */

	LIS_tppLista pAmeacantes;
			/* Ponteiro da Lista contendo as casas que cont�m pe�as que legalmente amea�am a presente casa */

	LIS_tppLista pAmeacados;
			/* Ponteiro da Lista contendo as casas legalmente amea�adas pela pe�a na presente casa */

} tpCasa;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

static void DestruirValorPeca(void * pValor);

static void DestruirValorGenerico(void * pValor);

static void DestruirValorMatriz(void * pValor); 

static void DestruirValorCasa(void * pValor);

static TAB_tpCondRet CriarCasa( tpCasa ** pCasa );

static TAB_tpCondRet CriarPeca( tpPeca ** Peca );

static TAB_tpCondRet LerArquivoPecas( LIS_tppLista * pListaPecas );

static int ValidarTipoPeca(LIS_tppLista pLista, char * nome);

static int ValidarCorPeca( char cor );

static int ValidarCoordenada( char * pCoordenada );

static tpCasa * ObterCasa(LIS_tppLista pLista, char * pCoordenada);

static int ValidarMovimento(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino, int atualizarLista);

static void AtualizaListas(TAB_tppTabuleiro pTabuleiro );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: TAB  &Criar tabuleiro
*  ****/

TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTabuleiro)
{
   int i, j;

   TAB_tppTabuleiro pTabuleiroTemp;
   TAB_tpCondRet    CondRetTab;
   LIS_tpCondRet    CondRetLis;

   /* Cria o tabuleiro */
   pTabuleiroTemp = ( TAB_tpTabuleiro * ) malloc( sizeof( TAB_tpTabuleiro ) );
   if ( pTabuleiroTemp == NULL )
   {
	   return TAB_CondRetFaltouMemoria;
   } /* if */

   /* Preenche a lista com os tipos de pe�a existentes */
   CondRetTab = LerArquivoPecas( &pTabuleiroTemp->pPecas );
   if( CondRetTab != TAB_CondRetOK )
   {
	   return CondRetTab;
   } /* if */
   
   /* Cria a matriz do tabuleiro */
   CondRetLis = LIS_CriarLista( "matx", DestruirValorMatriz, &pTabuleiroTemp->pMatriz );
   if ( CondRetLis != LIS_CondRetOK )
   {
	   return TAB_CondRetFaltouMemoria;
   } /* if */

   #ifdef _DEBUG
	   &pTabuleiroTemp->tipo = "t";
	   &pTabuleiroTemp->quantidadeNos = 0;
   #endif

   for ( i = 0; i < 8; i++ )
   {
	   LIS_tppLista pListaColunasTemp;

	   char id = ( i + '0' );

	   /* Cria as colunas da matriz */
	   CondRetLis = LIS_CriarLista( &id, DestruirValorCasa, &pListaColunasTemp );
	   if ( CondRetLis != TAB_CondRetOK )
	   {
		   return TAB_CondRetFaltouMemoria;
	   } /* if */

	   for ( j = 0; j < 8; j++ )
	   {
		   /* Inseres os elementos na coluna da matriz */
		   tpCasa * pCasa;

		   CondRetTab = CriarCasa( &pCasa );
		   if( CondRetTab != TAB_CondRetOK )
		   {
			   return TAB_CondRetFaltouMemoria;
		   }

		   CondRetLis = LIS_InserirElemento( pListaColunasTemp, pCasa );
		   if ( CondRetLis != TAB_CondRetOK )
		   {
			   return TAB_CondRetFaltouMemoria;
		   } /* if */

			#ifdef _DEBUG
				&pTabuleiroTemp->quantidadeNos += 1;
			#endif
	   }

	   /* Insere as colunas na matriz */
	   CondRetLis = LIS_InserirElemento( pTabuleiroTemp->pMatriz, pListaColunasTemp );
	   if ( CondRetLis != TAB_CondRetOK )
	   {
		   return TAB_CondRetFaltouMemoria;
	   } /* if */
   }

   *pTabuleiro = pTabuleiroTemp;

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Criar tabuleiro */


/***************************************************************************
*
*  Fun��o: TAB  &Inserir peca
*  ****/

TAB_tpCondRet TAB_InserirPeca(TAB_tppTabuleiro * pTabuleiro, char * pNome, char cor, char * pCoordenada)
{
   TAB_tppTabuleiro pTabTemp;

   tpCasa * pCasa;

   if ( pTabuleiro == NULL )
   {
	   return TAB_CondRetNaoExiste;
   } /* if */
   
   pTabTemp = *pTabuleiro;

   if ( ! ValidarTipoPeca( pTabTemp->pPecas, pNome ) )
   {
	   return TAB_CondRetPecaInexistente;
   } /* if */

   if ( ! ValidarCorPeca( cor ) )
   {
	   return TAB_CondRetCorInexistente;
   } /* if */

   if ( ! ValidarCoordenada( pCoordenada ) )
   {
	   return TAB_CondRetCasaInexistente;
   } /* if */
	
   pCasa = ObterCasa( pTabTemp->pMatriz, pCoordenada );
   pCasa->cor = cor;
   strcpy( pCasa->nome, pNome );
   pCasa->primeiroMov = 1;

	AtualizaListas( pTabTemp );

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Inserir peca */

/***************************************************************************
*
*  Fun��o: TAB  &Mover peca
*  ****/

TAB_tpCondRet TAB_MoverPeca(TAB_tppTabuleiro * pTabuleiro, char * origem, char * destino)
{
   tpCasa * pCasaOrigem;
   tpCasa * pCasaDestino;

   TAB_tppTabuleiro pTabTemp;

   if (pTabuleiro == NULL)
   {
	   return TAB_CondRetNaoExiste;
   } /* if */

   pTabTemp = *pTabuleiro;

   if ( ! ValidarCoordenada( origem ) || ! ValidarCoordenada( destino ) )
   {
	   return TAB_CondRetCasaInexistente;
   }

   pCasaDestino = ObterCasa(pTabTemp->pMatriz, destino);
   pCasaOrigem = ObterCasa(pTabTemp->pMatriz, origem);
   if( pCasaOrigem->cor == COR_CASA_VAZIA )
   {
	   return TAB_CondRetCasaVazia;
   }

   if ( ! ValidarMovimento( pTabTemp, origem, destino, FALSE ) )
   {
	   return TAB_CondRetMovimentoInvalido;
   }

   pCasaDestino->cor = pCasaOrigem->cor;
   strcpy( pCasaDestino->nome, pCasaOrigem->nome);

   pCasaOrigem->cor = COR_CASA_VAZIA;
   strcpy( pCasaOrigem->nome, PECA_CASA_VAZIA );

   pCasaOrigem->primeiroMov  = 0;
   pCasaDestino->primeiroMov = 0;
   	
   AtualizaListas( pTabTemp );

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Mover peca */


/***************************************************************************
*
*  Fun��o: TAB  &Retirar peca
*  ****/

TAB_tpCondRet TAB_RetirarPeca(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada)
{	
   tpCasa * pCasa;
   TAB_tppTabuleiro pTabTemp;

   if (pTabuleiro == NULL)
   {
	   return TAB_CondRetNaoExiste;
   } /* if */

   pTabTemp = *pTabuleiro;

   if ( ! ValidarCoordenada( pCoordenada ) )
   {
	   return TAB_CondRetCasaInexistente;
   } /* if */

   pCasa = ObterCasa(pTabTemp->pMatriz, pCoordenada);
   pCasa->cor = COR_CASA_VAZIA;
   strcpy(pCasa->nome, PECA_CASA_VAZIA);
   
   AtualizaListas( pTabTemp );

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Retirar peca */


/***************************************************************************
*
*  Fun��o: TAB  &Obter peca
*  ****/

TAB_tpCondRet TAB_ObterPeca(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, char * pCor, char ** pNome)
{
   TAB_tppTabuleiro pTabTemp;

   tpCasa * pCasa;

   if (pTabuleiro == NULL)
   {
	   return TAB_CondRetNaoExiste;
   } /* if */

   pTabTemp = *pTabuleiro;

   if ( ! ValidarCoordenada( pCoordenada ) )
   {
	   return TAB_CondRetCasaInexistente;
   } /* if */

   pCasa  = ObterCasa( pTabTemp->pMatriz, pCoordenada );

   *pCor  = pCasa->cor;
   *pNome = ( char * ) malloc( (strlen( pCasa->nome ) + 1) * sizeof( char ) );
   strcpy( *pNome, pCasa->nome );

   if (pCasa->cor == COR_CASA_VAZIA)
   {
	   return TAB_CondRetCasaVazia;
   }

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Obter peca */


/***************************************************************************
*
*  Fun��o: TAB  &Obter lista amea�antes
*  ****/

TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista)
{
   tpCasa * pCasa;
   TAB_tppTabuleiro pTabTemp;

   if (pTabuleiro == NULL)
   {
	   return TAB_CondRetNaoExiste;
   } /* if */

   pTabTemp = *pTabuleiro;

   if (! ValidarCoordenada( pCoordenada ) )
   {
	   return TAB_CondRetCasaInexistente;
   } /* if */

   pCasa   = ObterCasa(pTabTemp->pMatriz, pCoordenada);
   *pLista = pCasa->pAmeacantes;

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Obter lista ameacantes */


/***************************************************************************
*
*  Fun��o: TAB  &Obter lista amea�ados
*  ****/

TAB_tpCondRet TAB_ObterListaAmeacados(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista)
{
   tpCasa * pCasa;
   TAB_tppTabuleiro pTabTemp;

   if (pTabuleiro == NULL)
   {
	   return TAB_CondRetNaoExiste;
   } /* if */

   pTabTemp = *pTabuleiro;

   if ( ! ValidarCoordenada( pCoordenada ) )
   {
	   return TAB_CondRetCasaInexistente;
   } /* if */

   pCasa   = ObterCasa(pTabTemp->pMatriz, pCoordenada);
   *pLista = pCasa->pAmeacados;

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Obter lista ameacados */


/***************************************************************************
*
*  Fun��o: TAB  &Destruir tabuleiro
*  ****/

TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro * pTabuleiro)
{
   TAB_tppTabuleiro pTabTemp;

   if ( pTabuleiro == NULL )
   {
	   return TAB_CondRetNaoExiste;
   } /* if */

   pTabTemp = *pTabuleiro;

   LIS_DestruirLista( pTabTemp->pMatriz );
   LIS_DestruirLista( pTabTemp->pPecas  );
   free( pTabTemp );

   return TAB_CondRetOK;

} /* Fim fun��o: TAB  &Destruir tabuleiro */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor peca
*
***********************************************************************/

void DestruirValorPeca(void * pValor)
{
	tpPeca * tempPeca = (tpPeca*)pValor;
	LIS_DestruirLista( tempPeca->pAndar );
	LIS_DestruirLista( tempPeca->pComer );
	free(pValor);
} /* Fim fun��o: TAB -Destruir valor peca*/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor generico
*
***********************************************************************/

void DestruirValorGenerico(void * pValor)
{
	free( pValor );
} /* Fim fun��o: TAB -Destruir valor generico*/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor matriz
*
***********************************************************************/

void DestruirValorMatriz(void * pValor)
{
	LIS_DestruirLista( (LIS_tppLista) pValor );
} /* Fim fun��o: TAB -Destruir valor matriz*/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor casa
*
***********************************************************************/

void DestruirValorCasa(void * pValor)
{
	tpCasa * tempCasa = (tpCasa*)pValor;
	LIS_DestruirLista(tempCasa->pAmeacados);
	LIS_DestruirLista(tempCasa->pAmeacantes);
	free(pValor);
} /* Fim fun��o: TAB -Destruir valor casa*/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Criar casa
*
***********************************************************************/

TAB_tpCondRet CriarCasa( tpCasa ** pCasa )
{
	LIS_tpCondRet CondRet;

	tpCasa * pCasaTemp = ( tpCasa * ) malloc( sizeof( tpCasa ) );
	if( pCasaTemp == NULL )
	{
		return TAB_CondRetFaltouMemoria;
	}

	pCasaTemp->primeiroMov = 0;
	pCasaTemp->cor = COR_CASA_VAZIA;

	#ifdef _DEBUG
		pCasaTemp->tipoCasa = 'c';
	#endif

	strcpy( pCasaTemp->nome, PECA_CASA_VAZIA );

	CondRet = LIS_CriarLista( "amdo", DestruirValorGenerico, &pCasaTemp->pAmeacados  );
	if( CondRet != LIS_CondRetOK )
	{
		return TAB_CondRetFaltouMemoria;
	}

	CondRet = LIS_CriarLista( "amte", DestruirValorGenerico, &pCasaTemp->pAmeacantes );
	if( CondRet != LIS_CondRetOK )
	{
		return TAB_CondRetFaltouMemoria;
	}

	*pCasa = pCasaTemp;

	return TAB_CondRetOK;

} /* Fim fun��o: TAB -Criar casa*/

/***********************************************************************
*
*  $FC Fun��o: TLIS -Criar pe�a
*
***********************************************************************/

TAB_tpCondRet CriarPeca( tpPeca ** pPeca )
{
	tpPeca * novaPeca;

	LIS_tpCondRet CondRetLista;

	novaPeca = ( tpPeca * ) malloc( sizeof( tpPeca ) );
	if( novaPeca == NULL )
	{
		return TAB_CondRetFaltouMemoria;
	}

	CondRetLista = LIS_CriarLista( "a", DestruirValorGenerico, &novaPeca->pAndar );
	if( CondRetLista != LIS_CondRetOK )
	{
		return TAB_CondRetFaltouMemoria;
	}

	CondRetLista = LIS_CriarLista( "c", DestruirValorGenerico, &novaPeca->pComer );
	if( CondRetLista != LIS_CondRetOK )
	{
		return TAB_CondRetFaltouMemoria;
	}

	*pPeca = novaPeca;

	return TAB_CondRetOK;

} /* Fim fun��o: TAB -Criar peca*/

/***********************************************************************
*
*  $FC Fun��o: TAB  -Ler Arquivo de pe�as
*
***********************************************************************/

TAB_tpCondRet LerArquivoPecas( LIS_tppLista * pListaPecas )
{
	LIS_tpCondRet CondRetLista;
	TAB_tpCondRet CondRetTab;

	tpPeca* pecaTemp;
	tpMovimentoPeca* movPeca;

	char line[50];
	FILE * pFile = fopen(pathArquivo, "r");
	if ( pFile == NULL )
	{
		printf( "\nErro, nao foi possivel abrir o arquivo de entrada.\n" );
		return TAB_CondRetEntradaInvalida;
	}

	CondRetLista = LIS_CriarLista("p", DestruirValorPeca, pListaPecas );
	if( CondRetLista != LIS_CondRetOK )
	{
		return TAB_CondRetFaltouMemoria;
	}

	while ( fgets (line, sizeof( line ), pFile ) != NULL )
	{
		if ( strncmp( line, ">>>>>>>>>>", 10 ) == 0 )
		{
			CondRetTab = CriarPeca( &pecaTemp );
			if( CondRetTab != TAB_CondRetOK )
			{
				return TAB_CondRetFaltouMemoria;
			}
		}
		else if ( strncmp( line, "Nome", 4 ) == 0 )
		{
			int i;
			strncpy( pecaTemp->nome, &line[5], 4 );

			for ( i = 0; i < 4; i++ )
			{
				if ( pecaTemp->nome[i] == '\n' )
				{
					pecaTemp->nome[i] = '\0';
				}
			}

		}
		else if ( ( strncmp( line, "--Andar", 7 ) == 0 ) || ( strncmp( line, "--Comer", 7 ) == 0) )
		{
			movPeca = ( tpMovimentoPeca * ) malloc( sizeof( tpMovimentoPeca ) );
			if( movPeca == NULL )
			{
				return TAB_CondRetFaltouMemoria;
			}
		}
		else if ( strncmp( line, "Oeste", 5 ) == 0 )
		{
			movPeca->coordenadas[0] = line[6] - '0';
		}
		else if ( strncmp( line, "Norte", 5 ) == 0 )
		{
			movPeca->coordenadas[1] = line[6] - '0';
		}
		else if ( strncmp( line, "Leste", 5 ) == 0 )
		{
			movPeca->coordenadas[2] = line[6] - '0';
		}
		else if ( strncmp( line, "Sul", 3 ) == 0 )
		{
			movPeca->coordenadas[3] = line[4] - '0';
		}
		else if ( strncmp( line, "Max", 3 ) == 0 ) 
		{
			movPeca->max = line[4] - '0';
		}
		else if ( strncmp( line, "Min", 3 ) == 0 )
		{
			movPeca->min = line[4] - '0';
		}
		else if ( strncmp( line, "Primeiro", 8 ) == 0 )
		{
			movPeca->primeiroMov = line[9] - '0';
		}
		else if ( strncmp( line, "--FimAndar", 10 ) == 0 )
		{	
			CondRetLista = LIS_InserirElemento(pecaTemp->pAndar, movPeca);
			if( CondRetLista != LIS_CondRetOK )
			{
				return TAB_CondRetFaltouMemoria;
			}
		}
		else if (strncmp(line, "--FimComer", 10) == 0)
		{
			CondRetLista = LIS_InserirElemento(pecaTemp->pComer, movPeca);
			if( CondRetLista != LIS_CondRetOK )
			{
				return TAB_CondRetFaltouMemoria;
			}
		}
		else if ( strncmp( line, "<<<<<<<<<<", 10 ) == 0 )
		{
			CondRetLista = LIS_InserirElemento( *pListaPecas, pecaTemp);
			if( CondRetLista != LIS_CondRetOK )
			{
				return TAB_CondRetFaltouMemoria;
			}
		}
		else
		{
			return TAB_CondRetEntradaInvalida;
		}
	}
	fclose(pFile);
	return TAB_CondRetOK;
}

/***********************************************************************
*
*  $FC Fun��o: TAB  -Validar Tipo Peca
*
***********************************************************************/

int ValidarTipoPeca( LIS_tppLista pLista, char * nome )
{
	tpPeca * pPeca;
	LIS_tpCondRet CondRet;

	CondRet = LIS_AndarInicio( pLista );
	while( CondRet == LIS_CondRetOK  )
	{
		LIS_ObterElemento( pLista, ( void ** ) &pPeca );
		if ( strcmp( nome, pPeca->nome ) == 0 )
		{
			return TRUE;
		}

		CondRet = LIS_IrProxElemento( pLista );
	}

	return FALSE;
}

/***********************************************************************
*
*  $FC Fun��o: TAB  -Validar Cor Peca
*
***********************************************************************/

int ValidarCorPeca( char cor )
{
	if (cor != 'p' && cor != 'b' && cor != 'P' && cor != 'B')
	{
		return FALSE;
	} /* if */

	return TRUE;
}

/***********************************************************************
*
*  $FC Fun��o: TAB  -Validar Coordenada
*
***********************************************************************/

int ValidarCoordenada( char * pCoordenada )
{
	if ( ! ( pCoordenada[0] >= 'A' && pCoordenada[0] <= 'H' ) &&
	     ! ( pCoordenada[0] >= 'a' && pCoordenada[0] <= 'h' ) )
	{
		return FALSE;
	} /* if */

	if ( ! ( pCoordenada[1] >= '1' && pCoordenada[1] <= '8' ) )
	{
		return FALSE;
	} /* if */

	return TRUE;
}

/***********************************************************************
*
*  $FC Fun��o: TAB  -Obter Casa
*
***********************************************************************/

tpCasa * ObterCasa(LIS_tppLista pLista, char * pCoordenada)
{
	int linha, coluna, i;
	tpCasa * pCasa;
	LIS_tppLista pListaCasa;

	coluna = ( pCoordenada[0] < 'a' ) ? pCoordenada[0] - 'A' : pCoordenada[0] - 'a';
	linha  =   pCoordenada[1] - '1';

	LIS_AndarInicio(pLista);
	for ( i = 0; i < coluna; i ++ )
	{
		LIS_IrProxElemento(pLista);
	}

	LIS_ObterElemento(pLista, (void**) &pListaCasa);

	LIS_AndarInicio( pListaCasa );
	for ( i = 0; i < linha; i++ )
	{
		LIS_IrProxElemento(pListaCasa);
	}

	LIS_ObterElemento( pListaCasa, (void**) &pCasa );

	return pCasa;

}

/***********************************************************************
*
*  $FC Fun��o: TAB  -Validar movimento
*
***********************************************************************/

int ValidarMovimento(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino, int atualizarLista)
{
	int i;

	char pAlcance[3];

	int comer, branco;

	LIS_tppLista  pMovimento = NULL;
	LIS_tpCondRet CondRet = LIS_CondRetOK;

	tpPeca * pPeca;
	tpMovimentoPeca * pMov;

	tpCasa * pCasaOrigem;
	tpCasa * pCasaDestino;
	tpCasa * pCasaTemp;

	if( strcmp( origem, destino ) == 0 )
	{
		return FALSE;
	}

	pCasaOrigem  = ObterCasa( pTabuleiro->pMatriz, origem );
	pCasaDestino = ObterCasa( pTabuleiro->pMatriz, destino );

	if( pCasaOrigem->cor == pCasaDestino->cor )
	{
		return FALSE;
	}

	if (!strcmp(pCasaOrigem->nome, PECA_CASA_VAZIA))
	{
		return FALSE;
	}

	comer  = strcmp( pCasaDestino->nome, PECA_CASA_VAZIA ) ? TRUE : FALSE;
	branco = ( pCasaOrigem->cor == 'b' || pCasaOrigem->cor == 'B' ) ? 1 : -1;

	for ( LIS_AndarInicio( pTabuleiro->pPecas ); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento( pTabuleiro->pPecas ) )
	{
		LIS_ObterElemento( pTabuleiro->pPecas, ( void ** ) &pPeca );

		if ( strcmp( pCasaOrigem->nome, pPeca->nome ) == 0 )
		{
			/* Verifica se a pe�a vai andar ou comer, menos no caso de atualizar listas amea�ante e amea�ado */
			if (atualizarLista)
			{
				pMovimento = pPeca->pComer;
			}
			else
			{
				comer ? (pMovimento = pPeca->pComer) : (pMovimento = pPeca->pAndar);
			}
			break;
		
		}
	}

	for ( LIS_AndarInicio( pMovimento ); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento( pMovimento ) )
	{
		LIS_ObterElemento( pMovimento, ( void ** ) &pMov );

		if ( pMov->primeiroMov && ! pCasaOrigem->primeiroMov )
		{
			/*
			 * Verifica se � o primeiro movimento da pe�a
			 * Se sim permite a utiza��o de movimentos
			 * autorizados somente no primeiro movimento.
			 */
			continue;
		}

		pAlcance[0] = origem[0];
		pAlcance[1] = origem[1];

		for ( i = 1; i <= pMov->max; i++ )
		{
			pAlcance[0] = pAlcance[0] + branco * ( pMov->coordenadas[2] ) - branco * ( pMov->coordenadas[0] );
			pAlcance[1] = pAlcance[1] + branco * ( pMov->coordenadas[1] ) - branco * ( pMov->coordenadas[3] );
			pAlcance[2] = '\0';

			if ( ! ValidarCoordenada ( pAlcance ) )
			{
				/*
				* Movimento j� est� fora do tabuleiro!
				* Pe�a n�o precisa mover mais do que isso.
				*/
				break;
			}

			pCasaTemp = ObterCasa( pTabuleiro->pMatriz, pAlcance );

			if ( strcmp( pAlcance, destino ) == 0 )
			{
				/* Movimento para a casa destino existe! */
				//pCasaTemp = ObterCasa( pTabuleiro->pMatriz, pAlcance );
				if( strcmp( pCasaTemp->nome, PECA_CASA_VAZIA ) != 0 )
				{
					/* Ops! A casa destino est� ocupada! */
					if( ! comer )
					{
						/*
						* Pe�a n�o pode se mover para casa j� ocupada!
						* Pe�a n�o precisa mover mais do que isso.
						*/
						break;
					}
				}

				if( i >= pMov->min )
				{
					/* Pe�a j� andou o m�nimo necess�rio */
					return TRUE;
				}
			}
			else
			{
				if (strcmp(pCasaTemp->nome, PECA_CASA_VAZIA) != 0)
				{
					/* Ops! Ocorreu uma colis�o */
					break;
				}
			}
		}
	}

	return FALSE;
}

/***********************************************************************
*
*  $FC Fun��o: TAB  -Atualiza listas
*
***********************************************************************/

static void AtualizaListas( TAB_tppTabuleiro pTabuleiro )
{
	int i, j, k, l;

	int ameaca, ameacado;

	char  coordenada[3];
	char  alcance[3];
	char* pValor;

	LIS_tppLista pAmeacados, pAmeacantes;
	tpCasa * pCasa;
	tpCasa * pCasaTemp;

	for ( i = 0; i < 8; i++ )
	{
		for ( j = 0; j < 8; j++ )
		{
			/*
			 * Itera por todas as casas do tabuleiro
			 */
			coordenada[0] = 'A' + i;
			coordenada[1] = '1' + j;
			coordenada[2] = '\0';

			LIS_CriarLista( "amdo", DestruirValorGenerico, &pAmeacados  );
			LIS_CriarLista( "amte", DestruirValorGenerico, &pAmeacantes );

			pCasa = ObterCasa( pTabuleiro->pMatriz, coordenada );

			for ( k = 0; k < 8; k++ )
			{
				for ( l = 0; l < 8; l++ )
				{
					/*
					* Testa em todas as casas do tabuleiro se as mesmas
					* possuem uma pe�a inimiga que amea�a ou � amea�ada
					* pela pe�a obtida anteriormente.
					*/

					alcance[0] = 'A' + k;
					alcance[1] = '1' + l;
					alcance[2] = '\0';

					if( strcmp( coordenada, alcance ) == 0 )
					{
						/*
						 * Coordenada e Alcance s�o a mesma casa.
						 */
						break;
					}

					ameaca   = ValidarMovimento( pTabuleiro, coordenada, alcance, TRUE );
					ameacado = ValidarMovimento( pTabuleiro, alcance, coordenada, TRUE );

					pCasaTemp = ObterCasa( pTabuleiro->pMatriz, alcance );

					if( ameaca && ( pCasa->cor != COR_CASA_VAZIA ) && ( pCasa->cor != pCasaTemp->cor ) )
					{
						/*
						* Se amea�a uma casa contendo uma pe�a inimiga,
						* a casa inimiga � adicionada a lista de casas amea�adas.
						*/
						pValor = ( char* ) malloc( sizeof( alcance ) );
						if( pValor == NULL )
						{
							exit( 1 );
						}
						strcpy( pValor, alcance );
						LIS_InserirElemento( pAmeacados, pValor );
					}
					if( ameacado && ( pCasaTemp->cor != COR_CASA_VAZIA ) && ( pCasa->cor != pCasaTemp->cor ) )
					{
						/*
						* Se � amea�ada por uma casa contendo uma pe�a inimiga,
						* a casa inimiga � adicionada a lista de casas amea�antes.
						*/
						pValor = ( char* ) malloc( sizeof( alcance ) );
						if( pValor == NULL )
						{
							exit(1);
						}
						strcpy( pValor, alcance );
						LIS_InserirElemento( pAmeacantes, pValor );
					}
				}
			}

			LIS_DestruirLista( pCasa->pAmeacados  );
			LIS_DestruirLista( pCasa->pAmeacantes );

			pCasa->pAmeacados  = pAmeacados;
			pCasa->pAmeacantes = pAmeacantes;
		}
	}
}

#ifdef _DEBUG
/***********************************************************************
*
*  $FC Fun��o: TAB  -Verifica
*
***********************************************************************/
	TAB_tpCondRet TAB_Verifica ( TAB_tppTabuleiro * pTabuleiro, int* numErros )
{
	LIS_tpCondRet retLis;
	CAR_tppCarta pCarta;
	int numCasas;
	int i = 0;
	(*numErros) = 0;

	if( pTabuleiro != NULL && pTabuleiro->quantidadeNos > 0)
	{
		if( LIS_VerificaCorrenteNull( pTabuleiro->pMatriz ))
		{
			CNT_CONTAR("ERRO-no-corrente-nulo");
			(*numErros) ++;
		}
		else if (LIS_RetornaCorrente(pTabuleiro->pMatriz) == 'x')
		{
			CNT_CONTAR("ERRO-no-corrente-com-lixo");
			(*numErros) ++;
		}
	}
	else
	{
		CNT_CONTAR("OK-no-corrente-consistente");
	}
	retLis = LIS_IrInicioLista(pTabuleiro->pMatriz);
	if( retLis == 1 && pTabuleiro->quantidadeNos == 0)
	{
		CNT_CONTAR("OK-matriz-existe-mas-sem-nos");
	}

	// Prevendo origem NULA
	if( !LIS_VerificaCorrenteNull( pTabuleiro->pMatriz ))
	{
		numCasas = pTabuleiro->quantidadeNos;

		if(pTabuleiro != NULL)
		{
			if(LIS_QtdNos(pTabuleiro->pMatriz) == numCartasAntes)
			{
				// Teste tipo 
				i=0;
				LIS_IrInicioLista(pTabuleiro->pMatriz);
				if(LIS_RetornaCorrente(pTabuleiro->pMatriz) != 'x')
				{
					do
					{
						i++;
						if(LIS_RetornaCorrente(pTabuleiro->pMatriz) != 'x')
						{
							retLis = LIS_ObterValor( pTabuleiro->pMatriz,(void **) &pMatriz);
							if ( retLis == 0 && pMatriz != NULL )
							{

								if (pPilha->tipo == CAR_ObterTipo(pCarta))
								{
									CNT_CONTAR("OK-tipo-correto");
								}
								else
								{
									CNT_CONTAR("ERRO-tipo");
									(*numErros) ++;
								}
							}
						}
					}while((i < (pTabuleiro->qtdNos))  &&  LIS_AvancarElementoCorrente( pTabuleiro->pMatriz, 1 ) == 0); //tirei -1 do qtdnos

					if( pTabuleiro->qtdNos > 0)
					{
						CNT_CONTAR("OK-qtdNos-maior-0");

						/*Teste do sucessor altera*/

						LIS_IrInicioLista(pTabuleiroe->pMatriz);
						i = 0 ;
						do
						{
							i++;
							if ( LIS_RetornaSucessor( pTabuleiro->pMatriz ) == NULL )
							{
								CNT_CONTAR("ERRO-sucessor-nulo-quando-nao-deveria");
								(*numErros) ++;
							}
							else
							{
								CNT_CONTAR("OK-sucessor-nao-nulo");
							}
							if (LIS_RetornaSucessor(pTabuleiro->pMatrizp) == 'x')
							{
								CNT_CONTAR("ERRO-sucessor-com-lixo");
								(*numErros) ++;
							}
							else
							{
								CNT_CONTAR("OK-sucessor-sem-lixo");
							}
						} while( (i < (pTabuleiro->qtdNos -1))  && LIS_AvancarElementoCorrente( pTabuleiro->pMatriz, 1 ) == 0);


						/*Teste do antecessor - lixo atribu�do ou altera*/
						i = 0;
						LIS_IrFinalLista( pTabuleiro->pMatriz );
						do
						{
							i++;
							if ( LIS_RetornaAntecessor( pTabuleiro->pMatriz ) == NULL )
							{
								CNT_CONTAR("ERRO-antecessor-nulo-quando-nao-deveria");
								(*numErros) ++;
							}
							else 
							{
								CNT_CONTAR("OK-antecessor-nao-nulo");
							}
							if (LIS_RetornaAntecessor(pTabuleiro->pMatriz) == 'x')
							{
								CNT_CONTAR("ERRO-antecessor-com-lixo");
								(*numErros) ++;
							}
							else
							{
								CNT_CONTAR("OK-antecessor-sem-lixo");
							}
						} while((i < pTabuleiro->qtdNos -1) && LIS_AvancarElementoCorrente( pTabuleiro->pMatriz, -1 ) == 0);

					}
				}
			}

		}
	}

	/*Teste Origem Nula*/
	if ( LIS_OrigemNula(pTabuleiro->pMatriz) && pTabuleiro->qtdNos > 0 )
	{
		CNT_CONTAR("ERRO-origem-nula");
		(*numErros)++;
	}
	else
	{
		CNT_CONTAR("OK-origem-consistente");
	}

	return TAB_CondRetOK;
}


	TAB_tpCondRet TAB_Deturpa( TAB_tppTabuleiro * pTabuleiroeiro, int acao )
	{

		if( acao == 1 )
		{
			LIS_AndarInicio( pTabuleiro->pMatriz );
			LIS_AvancarElementoCorrente( pTabuleiro->pMatriz , 1);
			LiberarElemento( pTabuleiro->pMatriz ) ;
		}
		else if( acao == 2 )
		{
			LIS_AndarInicio( pTabuleiro->pMatriz );
			LIS_AvancarElementoCorrente( pTabuleiro->pMatriz , 1);
			LIS_AlteraSucessor( pTabuleiro->pMatriz ) ;
		}
		else if( acao == 3 )
		{
			LIS_AndarInicio( pTabuleiro->pMatriz );
			LIS_AvancarElementoCorrente( pTabuleiro->pMatriz , 1);
			LIS_AlteraPredecessor( pTabuleiro->pMatriz ) ;
		}
		else if( acao == 4 )
		{
			LIS_AndarInicio( pTabuleiro->pListaCartas );
			LIS_AvancarElementoCorrente( pTabuleiro->pMatriz , 1);
			LIS_AtribuiLixoSucessor( pTabuleiro->pMatriz ) ;
		}
		else if( acao == 5 )
		{
			LIS_AndarInicio( pTabuleiro->pMatriz );
			LIS_AvancarElementoCorrente( pTabuleiro->pMatriz , 1);
			LIS_AtribuiLixoPredecessor( pTabuleiro->pMatriz ) ;
		}
		else if( acao == 6 )
		{
			LIS_AndarInicio( pTabuleiro->pMatriz );
			LIS_AvancarElementoCorrente( pTabuleiro->pMatriz , 1);
			LIS_AlterarElemento( pTabuleiro->pMatriz, NULL) ;
		}
		else if( acao == 7 ){
			LIS_AndarInicio( pTabuleiro->pMatriz );
			LIS_AlterarElemento( pTabuleiro->pMatriz, NULL) ;

		}
		return TAB_CondRetOK ;
	}
#endif







