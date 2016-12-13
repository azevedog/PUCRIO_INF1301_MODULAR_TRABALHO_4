/***************************************************************************
*  $MCI Módulo de implementação: JOGO	Jogo de xadrez
*
*  Arquivo gerado:              JOGO.c
*  Letras identificadoras:      JOGO
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
*     3       mmq     16/nov/2016  correção de bugs
*     2       fpf     31/out/2016  implementação da interface gráfica do jogo
*     1       fpf     21/out/2016  início da implementação
*
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h>

#define TRUE  1
#define FALSE 0

#define JOGO_OWN
#include "JOGO.h"
#undef JOGO_OWN

/***** Protótipos das funções encapsuladas no módulo *****/

	static void FinalizaJogo( );


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: JOGO  &Mostra tabuleiro
*  ****/

	JOGO_tpCondRet JOGO_MostraTabuleiro(TAB_tppTabuleiro pTabuleiro)
	{
		TAB_tpCondRet tabCondRet;

		int   i, j;
		char  pCoordenada[3] = { 'A', '1', '\0' };
		char  pCor;
		char* pNome;

		#ifdef _WIN32 
			HANDLE hConsole;
			CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
			WORD saved_attributes;

			/* Save current attributes */
			hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
			GetConsoleScreenBufferInfo( hConsole, &consoleInfo );
			saved_attributes = consoleInfo.wAttributes;
		#endif

		if( ! jogoRodando )
		{
			return JOGO_CondRetJogoParado;
		}

		if( pTabuleiro == NULL )
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		printf("\n\n");
		printf("  A   B   C   D   E   F   G   H\n");
		printf("---------------------------------\n");
		for (i = 8; i > 0; i--)
		{
			pCoordenada[1] = i + 48;
			for (j = 0; j < 8; j++)
			{
				pCoordenada[0] = j + 65;				
				tabCondRet = TAB_ObterPeca(&pTabuleiro, pCoordenada, &pCor, &pNome);
				if( tabCondRet != TAB_CondRetOK && tabCondRet != TAB_CondRetCasaVazia )
				{
					return tabCondRet;
				}
				if( tabCondRet != TAB_CondRetCasaVazia )
				{
					printf("|");

					#ifdef _WIN32
						if (pCor == 'b')
						{
							SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						}
						else
						{
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
						}
					#endif

					printf("%s%c ", pNome, pCor);

					#ifdef _WIN32
						SetConsoleTextAttribute(hConsole, saved_attributes);
					#endif
				}
				else
				{
					printf("|   ");
				}
			}
			printf("| %d\n---------------------------------\n",i);
		}
		printf("\n\n");

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Mostra tabuleiro */


/***************************************************************************
*
*  Função: JOGO  &Recebe jogada
*  ****/

	JOGO_tpCondRet JOGO_RecebeJogada(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino)
	{
		LIS_tpCondRet lisCondRet;
		TAB_tpCondRet tabCondRet;

		LIS_tppLista pLista;

		char   pCor;
		char * pNome;
		char * pValor;
		
		if( ! jogoRodando )
		{
			return JOGO_CondRetJogoParado;
		}

		if( pTabuleiro == NULL )
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		if( ! strcmp( origem, "FIM" ) )
		{
			FinalizaJogo( );
			return JOGO_CondRetOK;
		}

		
		tabCondRet = TAB_ObterPeca( &pTabuleiro, origem, &pCor, &pNome );
		if( tabCondRet != TAB_CondRetOK )
		{
			/*
			 * Não existe peça na casa origem.
			 */
			printf( "\nMovimento Invalido\n" );
			return JOGO_CondRetMovimentoInvalido;
		}

		if( pCor != jogCorr && pCor != ( jogCorr + ( 'a' - 'A' ) ) )
		{
			/*
			 * Peça na casa de origem não pertence ao jogador corrente.
			 */
			printf( "\nMovimento Invalido\n" );
			return JOGO_CondRetMovimentoInvalido;
		}

		tabCondRet = TAB_MoverPeca( &pTabuleiro, origem, destino );
		if( tabCondRet != TAB_CondRetOK )
		{
			/* Peça não pode ser movida para a casa destino. */
			printf( "\nMovimento Invalido\n" );
			return JOGO_CondRetMovimentoInvalido;
		}

		/*
		 * Troca o jogador corrente.
		 */
		if( jogCorr == 'B' )
		{
			jogCorr = 'P';
		}
		else
		{
			jogCorr = 'B';
		}

		/* Ameaçados */
		tabCondRet = TAB_ObterListaAmeacados(&pTabuleiro, destino, &pLista);

		if (tabCondRet != TAB_CondRetOK)
		{
			return tabCondRet;
		}
		
		printf("\nCasas ameacadas pela peca:\n");
		lisCondRet = LIS_IrProxElemento(pLista);
		if (lisCondRet != LIS_CondRetListaVazia)
		{
			lisCondRet = LIS_CondRetOK;
			for (LIS_AndarInicio(pLista); lisCondRet == LIS_CondRetOK; lisCondRet = LIS_IrProxElemento(pLista))
			{
				LIS_ObterElemento(pLista, (void**)&pValor);
				printf("%s\n", pValor);
			}
		}

		/* Ameaçantes */
		tabCondRet = TAB_ObterListaAmeacantes(&pTabuleiro, destino, &pLista);

		if (tabCondRet != TAB_CondRetOK)
		{
			return tabCondRet;
		}
		
		printf("\nCasas que ameacam a peca:\n");
		lisCondRet = LIS_IrProxElemento(pLista);
		if (lisCondRet != LIS_CondRetListaVazia)
		{
			lisCondRet = LIS_CondRetOK;
			for (LIS_AndarInicio(pLista); lisCondRet == LIS_CondRetOK; lisCondRet = LIS_IrProxElemento(pLista))
			{
				LIS_ObterElemento(pLista, (void**)&pValor);
				printf("%s\n", pValor);
			}
		}

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Recebe jogada */

/***************************************************************************
*
*  Função: JOGO  &Recebe jogadores
*  ****/

	JOGO_tpCondRet JOGO_RecebeJogadores(char * jogB, char * jogP)
	{
		if( jogoRodando )
		{
			return JOGO_CondRetJogoEmAndamento;
		}


		if( jogadorB != NULL )
		{
			free( jogadorB );
		}

		jogadorB = ( char* ) malloc( ( strlen( jogB ) + 1 ) * sizeof( char ) );
		if (jogadorB == NULL)
		{
			return JOGO_CondRetFaltouMemoria;
		} /* if */

		strcpy(jogadorB, jogB);


		if( jogadorP != NULL )
		{
			free( jogadorP );
		}

		jogadorP = ( char* )malloc( ( strlen( jogP ) + 1 ) * sizeof( char ) );
		if( jogadorP == NULL )
		{
			return JOGO_CondRetFaltouMemoria;
		} /* if */

		strcpy( jogadorP, jogP );


		/*
 		 *  No Xadrez, o jogador com peças branca
		 *  começa o jogo.
		 */
		jogCorr = 'B';

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Recebe jogadores */

/***************************************************************************
*
*  Função: JOGO  &Monta tabuleiro
*  ****/

	JOGO_tpCondRet JOGO_MontaTabuleiro(TAB_tppTabuleiro pTabuleiro, char * nomeArq)
	{
		TAB_tpCondRet condret;

		FILE * pFile;

		int i;

		char cor = 'u';
		char nome[4];
		char pCoordenada[3];

		char line[50];

		if( jogoRodando )
		{
			return JOGO_CondRetJogoEmAndamento;
		}

		if( pTabuleiro == NULL )
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		pFile = fopen( nomeArq, "r" );
		if( pFile == NULL )
		{
			printf("\nErro, nao foi possivel abrir o arquivo de pecas do tabuleiro.\n");
			return JOGO_CondRetArquivoPecasNaoExiste;
		}

		while( fgets( line, sizeof( line ), pFile ) != NULL )
		{
			if( strncmp( line, ">>>>>>>>>>", 10 ) == 0 )
			{
				/* Nome */
				if( fgets( line, sizeof( line ), pFile ) == NULL )
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				strncpy( nome, line, 4 );
				for( i = 0; i < 4; i++ )
				{
					if( nome[i] == '\n' )
					{
						nome[i] = '\0';
					}
				}

				/* Cor */
				if( fgets( line, sizeof( line ), pFile ) == NULL )
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				cor = line[0];

				/* Coordenada X */
				if( fgets( line, sizeof( line ), pFile ) == NULL )
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				pCoordenada[0] = line[0];

				/* Coordenada Y */
				if (fgets(line, sizeof(line), pFile) == NULL)
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				pCoordenada[1] = line[0];
				pCoordenada[2] = '\0';

			}
			else if( strncmp( line, "<<<<<<<<<<", 10 ) == 0 )
			{
				condret = TAB_InserirPeca( &pTabuleiro, nome, cor, pCoordenada );
				if( condret == TAB_CondRetNaoExiste )
				{
					return ( JOGO_tpCondRet ) condret;
				}
				else if( condret != TAB_CondRetOK )
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
			}
		}

		fclose( pFile );

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Monta tabuleiro */

/***************************************************************************
*
*  Função: JOGO  &Inicia jogo
*  ****/

	JOGO_tpCondRet JOGO_IniciaJogo()
	{
		if( jogoRodando )
		{
			return JOGO_CondRetJogoEmAndamento;
		}

		if( jogadorB == NULL || jogadorP == NULL )
		{
			return JOGO_CondRetJogoNaoPodeIniciar;
		}

		jogoRodando = TRUE;
		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Inicia jogo */

/***************************************************************************
*
*  Função: JOGO  &Cheque mate
*  ****/

	JOGO_tpCondRet JOGO_ChequeMate( TAB_tppTabuleiro pTabuleiro, char* jogador )
	{
		LIS_tpCondRet lisCondRet;
		TAB_tpCondRet tabCondRet;

		LIS_tppLista pListaAmeacantes, pListaTemp;

		char  pCor;
		char* pNome;
		char  pCoordRei[3] = { 'A', '1', '\0' };
		char* pCoordTemp;
		int   i, j;

		int achouRei   = FALSE;
		int chequeMate = FALSE;

		if( ! jogoRodando )
		{
			return JOGO_CondRetJogoParado;
		}

		if( pTabuleiro == NULL )
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		/*
		 * Busca o Rei do jogador corrente no tabuleiro.
		 */
		for( i = 0; i < 8 && ! achouRei; i++ )
		{
			for( j = 0; j < 8 && ! achouRei; j++ )
			{
				pCoordRei[0] = i + 'A';
				pCoordRei[1] = j + '1';
				pCoordRei[2] = '\0';

				tabCondRet = TAB_ObterPeca( &pTabuleiro, &pCoordRei[0], &pCor, &pNome );
				if( tabCondRet == TAB_CondRetCasaInexistente )
				{
					return tabCondRet;
				}

				if( strncmp( pNome, "k", 1 ) == 0 )
				{
					char cor;

					if( strcmp( jogadorB, jogador ) == 0 )
					{
						cor = 'B';
					}
					else
					{
						cor = 'P';
					}

					if( pCor == cor || pCor == cor + ( 'a' - 'A' ) )
					{
						achouRei = TRUE;
					}
				}
			}
		}

		if( ! achouRei )
		{
			return JOGO_CondRetNaoExisteRei;
		}

		/*
		 * Obtem a lista de peças que ameaçam o rei.
		 */
		tabCondRet = TAB_ObterListaAmeacantes( &pTabuleiro, pCoordRei, &pListaAmeacantes );
		if( tabCondRet != TAB_CondRetOK )
		{
			return tabCondRet;
		}


		for( lisCondRet = LIS_AndarInicio( pListaAmeacantes ); lisCondRet == LIS_CondRetOK; lisCondRet = LIS_IrProxElemento( pListaAmeacantes ) )
		{
			pCoordTemp = ( char* ) malloc( sizeof( pCoordRei ) );
			lisCondRet = LIS_ObterElemento( pListaAmeacantes, ( void** ) &pCoordTemp );
			if( lisCondRet == LIS_CondRetListaVazia )
			{
				/*
				 * Lista de peças que ameaçam o rei está vazia.
				 */
				return JOGO_CondRetOK;
			}

			tabCondRet = TAB_ObterListaAmeacantes( &pTabuleiro, pCoordTemp, &pListaTemp );
			if( tabCondRet != TAB_CondRetOK )
			{
				return tabCondRet;
			}

			if( strcmp( pCoordRei, pCoordTemp ) == 0 )
			{

			}
			else if( LIS_IrProxElemento( pListaTemp ) == LIS_CondRetListaVazia )
			{
				/*
				 * Não é possível comer a peça que ameaça o Rei.
				 * Check Mate.
				 */
				chequeMate = TRUE;
			}
		}

		if( ! chequeMate )
		{
			/*
			 * As peças que ameaçam o Rei podem ser comidas.
			 */
			printf( "\n\nJOGADOR %s ESTA EM XEQUE!!\n\n", jogador );
			return JOGO_CondRetCheque;
		}

		for( i = 0; i < 8; i++ )
		{ 
			/*
			* Testa se o Rei pode se mover e se isso o salvaria do check mate.
			*/
			strcpy( pCoordTemp, pCoordRei );
			switch( i )
			{
			case 0:
				pCoordTemp[0] -= 1;
				break;
			case 1:
				pCoordTemp[0] += 1;
				break;
			case 2:
				pCoordTemp[1] -= 1;
				break;
			case 3:
				pCoordTemp[1] += 1;
				break;
			case 4:
				pCoordTemp[0] -= 1;
				pCoordTemp[1] += 1;
				break;
			case 5:
				pCoordTemp[0] -= 1;
				pCoordTemp[1] -= 1;
				break;
			case 6:
				pCoordTemp[0] += 1;
				pCoordTemp[1] += 1;
				break;
			case 7:
				pCoordTemp[0] += 1;
				pCoordTemp[1] -= 1;
				break;
			default:
				break;
			}

			if( TAB_ObterPeca( &pTabuleiro, pCoordTemp, &pCor, &pNome ) == TAB_CondRetCasaVazia )
			{
				/*
				* Possivel destino de movimento é casa vazia!
				*/
				tabCondRet = TAB_ObterListaAmeacantes( &pTabuleiro, pCoordTemp, &pListaTemp );
				if( tabCondRet != TAB_CondRetOK )
				{
					return tabCondRet;
				}

				if( LIS_IrProxElemento( pListaAmeacantes ) == LIS_CondRetListaVazia )
				{
					/*
					* Possivel destino de movimento não possui ameacantes!
					*/
					printf( "\n\nJOGADOR %s ESTA EM XEQUE!!\n\n", jogador );

					return JOGO_CondRetCheque;
				}
			}
		}

		printf( "\n\nJOGADOR %s ESTA EM XEQUE MATE!!\n\n", jogador );
		FinalizaJogo( );

		return JOGO_CondRetChequeMate;
	}/* Fim função: JOGO  &Cheque mate */

/***********************************************************************
*
*  $FC Função: TAB  -Finalizar Jogo
*
***********************************************************************/

	void FinalizaJogo( )
	{
		jogoRodando = FALSE;
		free( jogadorB );
		free( jogadorP );
		jogCorr = 'u';
	}

/********** Fim do módulo de implementação: JOGO  Jogo de xadrez **********/