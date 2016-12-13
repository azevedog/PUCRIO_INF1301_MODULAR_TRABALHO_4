/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro do Xadrez
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas	
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data       Observações
*     6       mmq    05/out/2016  revisao modulo e correções
*     5       mmq    04/out/2016  correcao de bugs
*     4       fpf    02/out/2016  desenvolvimento de funções
*     3       pf     02/out/2016  desenvolvimento de funções
*     2       fpf	 01/out/2016  implementação da estrutura do tabuleiro e funções
*     1       pf     25/set/2016  início da implementação das peças
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

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
*  $TC Tipo de dados: TAB Descritor da cabeça do Tabuleiro
*
*
***********************************************************************/

typedef struct TAB_tagTabuleiro
{
	LIS_tppLista pPecas;
		   /* Cabeça da lista com as peças disponiveis */

	LIS_tppLista pMatriz;
		   /* Cabeça da matriz */

} TAB_tpTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de peças
*
*
***********************************************************************/

	typedef struct tagPeca{
		
		char nome[4];
				/* Nome da peça */

		LIS_tppLista pAndar;
				/* Ponteiro da Lista contendo os movimentos da peça de andar */

		LIS_tppLista pComer;
				/* Ponteiro da Lista contendo os movimentos da peça de comer */

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
			/* Movimento que so pode ser executado na primeira jogada daquela peça */

	} tpMovimentoPeca;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de casas
*
*
***********************************************************************/

	typedef struct tagCasa{
		
		char nome[4];
				/* Nome da peça na casa */

		char cor;
				/* Cor da peça na casa */

		int primeiroMov;
				/* Movimento que so pode ser executado na primeira jogada daquela peça */

		LIS_tppLista pAmeacantes;
				/* Ponteiro da Lista contendo as casas que contém peças que legalmente ameaçam a presente casa */

		LIS_tppLista pAmeacados;
				/* Ponteiro da Lista contendo as casas legalmente ameaçadas pela peça na presente casa */

	} tpCasa;

/***** Protótipos das funções encapsuladas no módulo *****/

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

	static int ValidarMovimento(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino);

	static void AtualizaListas(TAB_tppTabuleiro pTabuleiro, char * pCoordenada);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar tabuleiro
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

	   /* Preenche a lista com os tipos de peça existentes */
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

   } /* Fim função: TAB  &Criar tabuleiro */


/***************************************************************************
*
*  Função: TAB  &Inserir peca
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

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Inserir peca */

/***************************************************************************
*
*  Função: TAB  &Mover peca
*  ****/

   TAB_tpCondRet TAB_MoverPeca(TAB_tppTabuleiro * pTabuleiro, char * origem, char * destino)
   {
	   int i, j;
	   char alcance[3];
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

	   if ( ! ValidarMovimento( pTabTemp, origem, destino ) )
	   {
		   return TAB_CondRetMovimentoInvalido;
	   }

	   pCasaDestino->cor = pCasaOrigem->cor;
	   strcpy( pCasaDestino->nome, pCasaOrigem->nome);

	   pCasaOrigem->cor = COR_CASA_VAZIA;
	   strcpy( pCasaOrigem->nome, PECA_CASA_VAZIA );

	   pCasaOrigem->primeiroMov  = 0;
	   pCasaDestino->primeiroMov = 0;
	   	
	   for (i = 0; i < 8; i++)
	   {
		   for (j = 0; j < 8; j++)
		   {
			   alcance[0] = 'A' + i;
			   alcance[1] = '1' + j;
			   alcance[2] = '\0';
			   //AtualizaListas(pTabTemp, alcance);
		   }
	   }

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Mover peca */

   
/***************************************************************************
*
*  Função: TAB  &Retirar peca
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

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Retirar peca */


/***************************************************************************
*
*  Função: TAB  &Obter peca
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

	   if( pCasa->cor == COR_CASA_VAZIA )
	   {
		   return TAB_CondRetCasaVazia;
	   }

	   *pCor  = pCasa->cor;
	   *pNome = ( char * ) malloc( strlen( pCasa->nome ) + 1 * sizeof( char ) );
	   strcpy( *pNome, pCasa->nome );

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Obter peca */


/***************************************************************************
*
*  Função: TAB  &Obter lista ameaçantes
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

   } /* Fim função: TAB  &Obter lista ameacantes */


/***************************************************************************
*
*  Função: TAB  &Obter lista ameaçados
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

   } /* Fim função: TAB  &Obter lista ameacados */


/***************************************************************************
*
*  Função: TAB  &Destruir tabuleiro
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

   } /* Fim função: TAB  &Destruir tabuleiro */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor peca
*
***********************************************************************/

	void DestruirValorPeca(void * pValor)
	{
		tpPeca * tempPeca = (tpPeca*)pValor;
		LIS_DestruirLista( tempPeca->pAndar );
		LIS_DestruirLista( tempPeca->pComer );
		free(pValor);
	} /* Fim função: TAB -Destruir valor peca*/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor generico
*
***********************************************************************/

	void DestruirValorGenerico(void * pValor)
	{
		free( pValor );
	} /* Fim função: TAB -Destruir valor generico*/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor matriz
*
***********************************************************************/

	void DestruirValorMatriz(void * pValor)
	{
		LIS_DestruirLista( (LIS_tppLista) pValor );
	} /* Fim função: TAB -Destruir valor matriz*/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor casa
*
***********************************************************************/

	void DestruirValorCasa(void * pValor)
	{
		tpCasa * tempCasa = (tpCasa*)pValor;
		LIS_DestruirLista(tempCasa->pAmeacados);
		LIS_DestruirLista(tempCasa->pAmeacantes);
		free(pValor);
	} /* Fim função: TAB -Destruir valor casa*/


/***********************************************************************
*
*  $FC Função: TLIS -Criar casa
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

	} /* Fim função: TAB -Criar casa*/

/***********************************************************************
*
*  $FC Função: TLIS -Criar peça
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

	} /* Fim função: TAB -Criar peca*/

/***********************************************************************
*
*  $FC Função: TAB  -Ler Arquivo de peças
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

				printf( "\n%s\n", pecaTemp->nome );
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
				printf( "---------\n" );
				printf( "Andar\n" );
				printf( "coord = %d %d %d %d\n", movPeca->coordenadas[0], movPeca->coordenadas[1], movPeca->coordenadas[2], movPeca->coordenadas[3] );
				printf( "max   = %d\n", movPeca->max );
				printf( "min   = %d\n", movPeca->min );
				printf( "prim  = %d\n", movPeca->primeiroMov );

				CondRetLista = LIS_InserirElemento(pecaTemp->pAndar, movPeca);
				if( CondRetLista != LIS_CondRetOK )
				{
					return TAB_CondRetFaltouMemoria;
				}
			}
			else if (strncmp(line, "--FimComer", 10) == 0)
			{
				printf( "---------\n" );
				printf( "Comer\n" );
				printf( "coord = %d %d %d %d\n", movPeca->coordenadas[0], movPeca->coordenadas[1], movPeca->coordenadas[2], movPeca->coordenadas[3] );
				printf( "max   = %d\n", movPeca->max );
				printf( "min   = %d\n", movPeca->min );
				printf( "prim  = %d\n", movPeca->primeiroMov );

				CondRetLista = LIS_InserirElemento(pecaTemp->pComer, movPeca);
				if( CondRetLista != LIS_CondRetOK )
				{
					return TAB_CondRetFaltouMemoria;
				}
			}
			else if ( strncmp( line, "<<<<<<<<<<", 10 ) == 0 )
			{
				printf("----------\n");
				printf( "Nome = %s\n", pecaTemp->nome );
				printf( "\n>>>>>>>>>>>>>>>\n" );

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
*  $FC Função: TAB  -Validar Tipo Peca
*
***********************************************************************/

	int ValidarTipoPeca( LIS_tppLista pLista, char * nome )
	{
		tpPeca * pPeca;

		LIS_tpCondRet CondRet = LIS_CondRetOK;
		for( LIS_AndarInicio( pLista ); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento( pLista ) )
		{
			LIS_ObterElemento( pLista, ( void ** ) &pPeca );
			if ( strcmp( nome, pPeca->nome ) == 0 )
			{
				return TRUE;
			}
		}

		return FALSE;
	}

/***********************************************************************
*
*  $FC Função: TAB  -Validar Cor Peca
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
*  $FC Função: TAB  -Validar Coordenada
*
***********************************************************************/

	int ValidarCoordenada( char * pCoordenada )
	{
		if ( ! ( pCoordenada[0] >= 'A' && pCoordenada[0] <= 'H' ) &&
		     ! ( pCoordenada[0] <= 'a' && pCoordenada[0] >= 'h' ) )
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
*  $FC Função: TAB  -Obter Casa
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
*  $FC Função: TAB  -Validar movimento
*
***********************************************************************/

	int ValidarMovimento(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino)
	{
		int i;

		char pAlcance[3];

		int comer, branco;

		LIS_tppLista  pMovimento;
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

		comer  = strcmp( pCasaDestino->nome, PECA_CASA_VAZIA ) ? TRUE : FALSE;
		branco = ( pCasaDestino->cor != 'b' || pCasaDestino->cor != 'B' ) ? -1 : 1;

		for ( LIS_AndarInicio( pTabuleiro->pPecas ); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento( pTabuleiro->pPecas ) )
		{
			LIS_ObterElemento( pTabuleiro->pPecas, ( void ** ) &pPeca );

			if ( strcmp( pCasaOrigem->nome, pPeca->nome ) == 0 )
			{
				/* Verifica se a peça vai andar ou comer */
				comer ? ( pMovimento = pPeca->pComer ) : ( pMovimento = pPeca->pAndar );
				break;
			}
		}

		for ( LIS_AndarInicio( pMovimento ); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento( pMovimento ) )
		{
			LIS_ObterElemento( pMovimento, ( void ** ) &pMov );

			if ( pMov->primeiroMov && ! pCasaOrigem->primeiroMov )
			{
				/*
				 * Verifica se é o primeiro movimento da peça
				 * Se sim permite a utização de movimentos
				 * autorizados somente no primeiro movimento.
				 */
				continue;
			}

			pAlcance[0] = origem[0];
			pAlcance[1] = origem[1];

			for ( i = 1; i <= pMov->max; i++ )
			{
				pAlcance[0] = pAlcance[0] + branco * ( pMov->coordenadas[1] ) - branco * ( pMov->coordenadas[3] );
				pAlcance[1] = pAlcance[1] + branco * ( pMov->coordenadas[0] ) - branco * ( pMov->coordenadas[2] );
				pAlcance[2] = '\0';

				if ( ! ValidarCoordenada ( pAlcance ) )
				{
					/*
					* Movimento já está fora do tabuleiro!
					* Peça não precisa mover mais do que isso.
					*/
					break;
				}

				pCasaTemp = ObterCasa( pTabuleiro->pMatriz, pAlcance );
				if( strcmp( pCasaTemp->nome, PECA_CASA_VAZIA ) != 0 )
				{
					/* Ops! Ocorreu uma colisão */
					break;
				}

				if ( strcmp( pAlcance, destino ) == 0 )
				{
					/* Movimento para a casa destino existe! */
					pCasaTemp = ObterCasa( pTabuleiro->pMatriz, pAlcance );
					if( strcmp( pCasaTemp->nome, PECA_CASA_VAZIA ) != 0 )
					{
						/* Ops! A casa destino está ocupada! */
						if( ! comer )
						{
							/*
							* Peça não pode se mover para casa já ocupada!
							* Peça não precisa mover mais do que isso.
							*/
							break;
						}
					}

					if( i >= pMov->min )
					{
						/* Peça já andou o mínimo necessário */
						return TRUE;
					}
				}
			}
		}

		return FALSE;
	}

/***********************************************************************
*
*  $FC Função: TAB  -Atualiza listas
*
***********************************************************************/

	static void AtualizaListas( TAB_tppTabuleiro pTabuleiro, char * coordenada)
	{
		int i, j;
		int ameaca, ameacado;
		char alcance[3];
		LIS_tppLista pAmeacados, pAmeacantes;
		tpCasa * pCasa;

		LIS_CriarLista( "amdo", DestruirValorGenerico, &pAmeacados  );
		LIS_CriarLista( "amte", DestruirValorGenerico, &pAmeacantes );

		for ( i = 0; i < 8; i++ )
		{
			for ( j = 0; j < 8; j++ )
			{
				alcance[0] = 'A' + i;
				alcance[1] = '1' + j;
				alcance[2] = '\0';

				ameaca   = ValidarMovimento( pTabuleiro, coordenada, alcance );
				ameacado = ValidarMovimento( pTabuleiro, alcance, coordenada );
				if ( ameaca )
				{
					LIS_InserirElemento( pAmeacados, alcance );
				}
				if ( ameacado )
				{
					LIS_InserirElemento( pAmeacantes, alcance );
				}
			}
		}

		pCasa = ObterCasa( pTabuleiro->pMatriz, coordenada );

		LIS_DestruirLista( pCasa->pAmeacados  );
		LIS_DestruirLista( pCasa->pAmeacantes );

		pCasa->pAmeacados  = pAmeacados;
		pCasa->pAmeacantes = pAmeacantes;
	}