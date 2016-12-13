/***************************************************************************
*  $MCI Módulo de implementação: Módulo Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      TAB
*
*  Projeto: T3 INF1301 2016.2
*  Autores: bap - Bruna Aleixo Penna
*           jpp - Joao Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
***************************************************************************/

#include   <stdio.h>
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
#include "CESPDIN.H"
#include "CONTA.H"
#endif

#define TABULEIRO_OWN
#include "TABULEIRO.H"
#undef TABULEIRO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeça de um Tabuleiro
*
*
*  $ED Descrição do tipo
*     A cabeça do tabuleiro é o ponto de acesso para um determinado tabuleiro.
*	  Atraves da referencia para uma matriz, podemos navegar pelo tabuleiro.
*
***********************************************************************/
typedef struct TAB_tagTabuleiro {

	MAT_tppMatriz pMatriz; /* Cabeca da matriz */
	int i; /* Coordenada  i do corrente */
	char j; /* Coordenada j do corrente */

} TAB_tpTabuleiro;

typedef struct TAB_tagCasa {

	void*	 pPeca; /* Ponteiro para a estrutura da peca */
	int		 cor; /* Cor da peca, que define o jogador */
	LIS_tppLista pAmeacantes; /* Lista de pecas ameacantes na dada casa */
	LIS_tppLista pAmeacados; /* Lista de pecas ameacadas na dada casa */

} TAB_tpCasa;

/***** Protótipos das funções encapuladas no módulo *****/

static TAB_tpCondRet TAB_AtribuirValorCorrente(TAB_tppTabuleiro pTabuleiro, TAB_tppCasa pCasa);

static TAB_tpCondRet TAB_ObterValorCorrente(TAB_tppTabuleiro pTabuleiro, TAB_tppCasa* ppCasa);

// Funcoes exportadas pelo modulo


/***********************************************************************
*  $FC Função: TAB Obter peca da casa
***********************************************************************/
TAB_tpCondRet TAB_ObterPecaDaCasa(TAB_tppCasa pCasa, void** pPeca) {

	#ifdef _DEBUG
	 	CNT_CONTAR("TAB-obter-peca-casa");
	#endif

	if (pCasa == NULL) {
		 #ifdef _DEBUG
	 		CNT_CONTAR("TAB-obter-peca-casa-pCasa-nula");
		 #endif

		return TAB_CondRetPonteiroNulo;
	}

	*pPeca = pCasa->pPeca;
	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Criar Tabuleiro
***********************************************************************/
TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro* ppTabuleiro) {
	TAB_tppTabuleiro pTabuleiro;

	#ifdef _DEBUG
	 	CNT_CONTAR("TAB-criar-tabuleiro");
	#endif

	if (ppTabuleiro == NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-criar-tabuleiro-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	pTabuleiro = (TAB_tpTabuleiro*)malloc(sizeof(TAB_tpTabuleiro));
	if(pTabuleiro == NULL || MAT_CriarMatriz(&(pTabuleiro->pMatriz), 8) != MAT_CondRetOK) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-criar-tabuleiro-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	pTabuleiro->i = 0;
	pTabuleiro->j = 'A';

	*ppTabuleiro = pTabuleiro;

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Destruir Tabuleiro
***********************************************************************/
TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro pTabuleiro) {
	#ifdef _DEBUG
		CNT_CONTAR("TAB-destruir-tabuleiro-tabuleiro-nulo");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-destruir-tabuleiro-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	MAT_DestruirMatriz(pTabuleiro->pMatriz);
	free(pTabuleiro);

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Definir Posicao Corrente
***********************************************************************/
TAB_tpCondRet TAB_DefinirPosCorrente(TAB_tppTabuleiro pTabuleiro, int i, char j) {
	#ifdef _DEBUG
	 	CNT_CONTAR("TAB-definir-pos-corrente");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-definir-pos-corrente-tabuleiro-nulo");
		#endif

		TAB_CondRetPonteiroNulo;
	}

	if(TAB_ChecarPosicaoValida(i, j) == TAB_CondRetCasaInexistente || MAT_DefinirCorrente(pTabuleiro->pMatriz, i-1, (int)(j-'A')) == MAT_CondRetPosicaoInvalida) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-definir-pos-corrente-pos-invalida");
		#endif

		return TAB_CondRetCasaInexistente;
	}

	pTabuleiro->i = i;
	pTabuleiro->j = j;

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Obter Posicao Corrente
***********************************************************************/
TAB_tpCondRet TAB_ObterPosCorrente(TAB_tppTabuleiro pTabuleiro, int* i, char* j) {
	#ifdef _DEBUG
	 	CNT_CONTAR("TAB-obter-pos-corrente");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-obter-pos-corrente-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	*i = (int)pTabuleiro->i;
	*j = (char)pTabuleiro->j;

	return TAB_CondRetOK;
}


/***********************************************************************
*  $FC Função: TAB Obter Peca corrente
***********************************************************************/
TAB_tpCondRet TAB_ObterPecaCorrente(TAB_tppTabuleiro pTabuleiro, void** pPeca, int* cor) {
	TAB_tpCasa* pCasa;

	#ifdef _DEBUG
	 	CNT_CONTAR("TAB-obter-peca-corrente");
	#endif

	pCasa = (TAB_tpCasa*)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		#ifdef _DEBUG
		 	CNT_CONTAR("TAB-obter-peca-corrente-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	TAB_ObterValorCorrente(pTabuleiro, &pCasa);

	if (pCasa != NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-obter-pecca-corrente-casa-nao-vazia");
		#endif

		*pPeca = pCasa->pPeca;
		*cor = pCasa->cor;
		return TAB_CondRetOK;
	}

	#ifdef _DEBUG
	 	CNT_CONTAR("TAB-obter-peca-corrente-casa-vazia");
	#endif

	return TAB_CondRetCasaVazia;
}

/***********************************************************************
*  $FC Função: TAB Obter Peca
***********************************************************************/
TAB_tpCondRet TAB_ObterPeca(TAB_tppTabuleiro pTabuleiro, int i, char j, void** pPeca, int* cor) {
	int iOrig;
	char jOrig;
	TAB_tpCasa** ppCasa;

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-obter-peca");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-obter-peca-tabuleiro-nulo");
		#endif
		return TAB_CondRetPonteiroNulo;
	}

	if(TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-obter-peca-posicao-invalida");
		#endif

		return TAB_CondRetCasaInexistente;
	}

	ppCasa = (TAB_tpCasa**)malloc(sizeof(TAB_tpCasa));
	if (ppCasa == NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-obter-peca-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	TAB_ObterPosCorrente(pTabuleiro, &iOrig, &jOrig);
	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, ppCasa);
	TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);

	if ((*ppCasa) == NULL) {
		#ifdef _DEBUG
	 		CNT_CONTAR("TAB-obter-peca-casa-vazia");
		#endif

		return TAB_CondRetCasaVazia;
	}

	#ifdef _DEBUG
	 	CNT_CONTAR("TAB-obter-peca-casa-nao-vazia");
	#endif

	*pPeca = (*ppCasa)->pPeca;
	*cor = (*ppCasa)->cor;

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Mover Peca
***********************************************************************/
TAB_tpCondRet TAB_MoverPeca(TAB_tppTabuleiro pTabuleiro, int iOrig, char jOrig, int iDest, char jDest, void** pecaComida, int* jogadorComido) {
	int jogador1, jogador2;
	TAB_tppCasa pCasaOrig, pCasaDest;
	#ifdef _DEBUG
 		CNT_CONTAR("TAB-mover-peca");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-mover-peca-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	// Checa se a posicao de origem e destino dadas sao validas.
	if(TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetCasaInexistente || 
		TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetCasaInexistente) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-mover-peca-posicao-invalida");
		#endif
		
		return TAB_CondRetCasaInexistente;
	}

	pCasaOrig = (TAB_tppCasa)malloc(sizeof(TAB_tppCasa));
	if (pCasaOrig == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-mover-peca-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	pCasaDest = (TAB_tppCasa)malloc(sizeof(TAB_tppCasa));
	if (pCasaDest == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-mover-peca-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
	TAB_ObterValorCorrente(pTabuleiro, &pCasaOrig);
	TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
	TAB_ObterValorCorrente(pTabuleiro, &pCasaDest);

	// Se tentar mover uma peça de um jogador para uma casa que está ocupada por
    // uma peça do mesmo jogador, não é um movimento legal. Caso contrario,
	// Removemos a peca da casa do destino e colocamos em seu lugar a peca
	// da casa de origem.

	if(pCasaDest != NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-mover-peca-casa-destino-ocupada");
		#endif

		jogador1 = pCasaOrig->cor;
		jogador2 = pCasaDest->cor;

		// casa vazia
		if(jogador2 != 0 && jogador2 != 1) {
			int iTemp;
			char jTemp;
			TAB_ObterPosCorrente(pTabuleiro, &iTemp, &jTemp);
			TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
			TAB_AtribuirValorCorrente(pTabuleiro, pCasaOrig);
			TAB_RetirarPeca(pTabuleiro, iTemp, jTemp);
		}

		if(jogador1 != jogador2) {
			#ifdef _DEBUG
 				CNT_CONTAR("TAB-mover-peca-jogada-valida");
			#endif

			TAB_ObterPeca(pTabuleiro, iDest, jDest, pecaComida, jogadorComido);
			TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
			TAB_RetirarPeca(pTabuleiro, iOrig, jOrig);
			TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
			TAB_AtribuirValorCorrente(pTabuleiro, pCasaOrig);
		}
	} 
	else {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-mover-peca-casa-destino-vazia");
		#endif

		TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
		TAB_ObterValorCorrente(pTabuleiro, &pCasaOrig);
		TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
		TAB_AtribuirValorCorrente(pTabuleiro, pCasaOrig);
		TAB_RetirarPeca(pTabuleiro, iOrig, jOrig);
	}

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Voltar Peca
***********************************************************************/
TAB_tpCondRet TAB_VoltarPeca(TAB_tppTabuleiro pTabuleiro, int iOrig, char jOrig, int iDest, char jDest, void** pPecaComida) {
	TAB_tppCasa pCasa;

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-voltar-peca");
	#endif

	if (pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-voltar-peca-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetCasaInexistente || TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetCasaInexistente) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-voltar-peca-posicao-invalida");
		#endif

		return TAB_CondRetCasaInexistente;
	}

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-voltar-peca-voltou-peca");
	#endif

	TAB_DefinirPosCorrente(pTabuleiro, iDest, jDest);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);
	TAB_RetirarPeca(pTabuleiro, iDest, jDest);
	*pPecaComida = pCasa;
	TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);
	TAB_AtribuirValorCorrente(pTabuleiro, pCasa);

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Checar Posicao Valida
***********************************************************************/
TAB_tpCondRet TAB_ChecarPosicaoValida(int i, char j) {
	#ifdef _DEBUG
 		CNT_CONTAR("TAB-checar-posicao-valida");
	#endif

	if(j < 'A' || j > 'H' || i < 1 || i > 8) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-checar-posicao-posicao-invalida");
		#endif
		return TAB_CondRetCasaInexistente;
	}

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Inserir Peca
***********************************************************************/
TAB_tpCondRet TAB_InserirPeca(TAB_tppTabuleiro pTabuleiro, void* pPeca, int i, char j, int cor) {
	TAB_tpCasa* pCasa;

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-inserir-peca");
	#endif

	if (pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-inserir-peca-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i ,j) != TAB_CondRetOK) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-inserir-peca-posicao-invalida");
		#endif

		return TAB_CondRetCasaInexistente;
	}

	pCasa = (TAB_tpCasa*)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-inserir-peca-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-inserir-peca-inseriu-peca");
	#endif

	// Definir posicao corrente para i,j
	TAB_DefinirPosCorrente(pTabuleiro, i, j);

	// Configurar o tpCasa
	pCasa->pPeca = pPeca;
	pCasa->cor = cor;
	LIS_CriarLista("ameacados", &(pCasa->pAmeacados));
	LIS_CriarLista("ameacantes", &(pCasa->pAmeacantes));

	// Atribuir valor de tpCasa ao corrente
	MAT_DefinirValorCorrente(pTabuleiro->pMatriz, (void*)pCasa);

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Retirar Peca
***********************************************************************/
TAB_tpCondRet TAB_RetirarPeca(TAB_tppTabuleiro pTabuleiro, int i, char j) {
	TAB_tppCasa* ppCasa;

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-retirar-peca");
	#endif

	if (pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-retirar-peca-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-retirar-peca-posicao-invalida");
		#endif

		return TAB_CondRetCasaInexistente;
	}

	ppCasa = (TAB_tppCasa*)malloc(sizeof(TAB_tppCasa));
	if(ppCasa == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-retirar-peca-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	// Vamos ate a casa pela dada coordenada e obtemos seu valor.
	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, ppCasa);

	if (ppCasa == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-retirar-peca-casa-vazia");
		#endif

		return TAB_CondRetCasaVazia;
	}

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-retirar-peca-retirou-peca");
	#endif
	// Retiramos a referencia da casa, logo da peca, da celula na dada coordenada.
	MAT_DefinirValorCorrente(pTabuleiro->pMatriz, NULL);

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Obter Lista Ameacantes
***********************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_tppTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista) {
	TAB_tppCasa pCasa;
	void* pPeca;
	int cor;

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-obter-lista-ameacantes");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacantes-ponteiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacantes-posicao-invalida");
		#endif

		return TAB_CondRetCasaInexistente;
	}

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacantes-faltou-memoria");
		#endif
		
		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);

	if (TAB_ObterPeca(pTabuleiro, i, j, &pPeca, &cor) == TAB_CondRetOK) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacantes-obteve-lista");
		#endif

		*pLista = pCasa->pAmeacantes;
	} else {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacantes-casa-vazia");
		#endif

		return TAB_CondRetCasaVazia;
	}

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Obter Lista Ameacados
***********************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacados(TAB_tppTabuleiro pTabuleiro, int i, char j, LIS_tppLista* pLista) {
	TAB_tppCasa pCasa;
	void* pPeca;
	int cor;

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-obter-lista-ameacados");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacados-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	if (TAB_ChecarPosicaoValida(i, j) != TAB_CondRetOK) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacados-posicao-invalida");
		#endif

		return TAB_CondRetCasaInexistente;
	}

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacados-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);

	if (TAB_ObterPeca(pTabuleiro, i, j, &pPeca, &cor) == TAB_CondRetOK) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacados-obteve-lista");
		#endif

		*pLista = pCasa->pAmeacados;
	} else {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-lista-ameacados-casa-vazia");
		#endif

		return TAB_CondRetCasaVazia;
	}

	return TAB_CondRetOK;
}


/***********************************************************************
*  $FC Função: TAB Obter valor da casa
***********************************************************************/

TAB_tpCondRet TAB_AdicionarListaAmeacantesAmeacados(TAB_tppTabuleiro pTabuleiro, int iAmeacante, char jAmeacante, int iAmeacado, char jAmeacado) {
	LIS_tpCondRet condRet1, condRet2;
	int iOrig;
	char jOrig;
	TAB_tppCasa pCasaAmeacante, pCasaAmeacada;

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-adicionar-lista-ameacantes-ameacados");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-adicionar-lista-ameacantes-ameacados-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	TAB_ObterPosCorrente(pTabuleiro, &iOrig, &jOrig);
	TAB_DefinirPosCorrente(pTabuleiro, iAmeacante, jAmeacante);
	TAB_ObterValorCorrente(pTabuleiro, &pCasaAmeacante);
	TAB_DefinirPosCorrente(pTabuleiro, iAmeacado, jAmeacado);
	TAB_ObterValorCorrente(pTabuleiro, &pCasaAmeacada);
	TAB_DefinirPosCorrente(pTabuleiro, iOrig, jOrig);

	condRet1 = LIS_InserirNo(pCasaAmeacante->pAmeacados, (void*)pCasaAmeacada);
	condRet2 = LIS_InserirNo(pCasaAmeacada->pAmeacantes, (void*)pCasaAmeacante);

	if(condRet1 == LIS_CondRetFaltouMemoria || condRet2 == LIS_CondRetFaltouMemoria ) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-adicionar-lista-ameacantes-ameacados-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	if(condRet1 == LIS_CondRetListaInexistente || condRet2 == LIS_CondRetListaInexistente ) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-adicionar-lista-ameacantes-ameacados-ponteiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-adicionar-lista-ameacantes-ameacados-adicionou-listas");
	#endif

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Esvaziar lista ameacantes e ameacados 
***********************************************************************/

TAB_tpCondRet TAB_EsvaziarListasDaCasa(TAB_tppTabuleiro pTabuleiro, int i, char j) {
	int oldI;
	char oldJ;
	TAB_tppCasa pCasa;
	void* pPeca;
	int cor;
	
	#ifdef _DEBUG
 		CNT_CONTAR("TAB-esvaziar-listas-da-casa");
	#endif

	if (pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-esvaziar-listas-da-casa-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tpCasa));
	if (pCasa == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-esvaziar-listas-da-casa-faltou-memoria");
		#endif

		return TAB_CondRetFaltouMemoria;
	}

	TAB_ObterPosCorrente(pTabuleiro, &oldI, &oldJ);
	TAB_DefinirPosCorrente(pTabuleiro, i, j);
	TAB_ObterValorCorrente(pTabuleiro, &pCasa);
	if (TAB_ObterPeca(pTabuleiro, i, j, &pPeca, &cor) == TAB_CondRetOK) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-esvaziar-listas-da-casa-esvaziou-listas");
		#endif

		LIS_EsvaziarLista(pCasa->pAmeacantes);
		LIS_EsvaziarLista(pCasa->pAmeacados);
	}
	TAB_DefinirPosCorrente(pTabuleiro, oldI, oldJ);


	return TAB_CondRetOK;
}

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*  $FC Função: TAB Atribuir Valor Corrente
***********************************************************************/
static TAB_tpCondRet TAB_AtribuirValorCorrente(TAB_tppTabuleiro pTabuleiro, TAB_tppCasa pCasa) {
	#ifdef _DEBUG
 		CNT_CONTAR("TAB-atribuir-valor-corrente");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-atribuir-valor-corrente-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-atribuir-valor-corrente-atribuiu");
	#endif

	MAT_DefinirValorCorrente(pTabuleiro->pMatriz, (void*)pCasa);

	return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Obter Valor Corrente
***********************************************************************/
static TAB_tpCondRet TAB_ObterValorCorrente(TAB_tppTabuleiro pTabuleiro, TAB_tppCasa* ppCasa) {
	#ifdef _DEBUG
 		CNT_CONTAR("TAB-obter-valor-corrente");
	#endif

	if(pTabuleiro == NULL) {
		#ifdef _DEBUG
 			CNT_CONTAR("TAB-obter-valor-corrente-tabuleiro-nulo");
		#endif

		return TAB_CondRetPonteiroNulo;
	}

	#ifdef _DEBUG
 		CNT_CONTAR("TAB-obter-valor-corrente-obteve");
	#endif
	MAT_ObterValorCorrente(pTabuleiro->pMatriz, (void**)ppCasa);

	return TAB_CondRetOK;
}


 #ifdef _DEBUG
/***********************************************************************
*
*  $FC FunÁ„o: TAB Deturpar estrutura
*
***********************************************************************/

TAB_tpCondRet TAB_Deturpar( TAB_tppTabuleiro pTabuleiro, int cmd ) {
    
    if( pTabuleiro != NULL ) {
        MAT_Deturpar(pTabuleiro->pMatriz, cmd, pTabuleiro->i, (int)(pTabuleiro->j-'A'));
    }
    
    return TAB_CondRetOK;
}

/***********************************************************************
*
*  $FC FunÁ„o: TAB Verificar estrutura
*
***********************************************************************/
TAB_tpCondRet TAB_VerificarEstrutura( TAB_tppTabuleiro pTabuleiro, int * numErros ) {
	int numElem;
	(*numErros) = 0;

	if (pTabuleiro != NULL) {
		if (!TAB_ChecarPosicaoValida(pTabuleiro->i, pTabuleiro->j)) {
			CNT_CONTAR("TAB-verificar-estrutura-posicao-invalida");
			(*numErros)++;
		} 

		MAT_VerificarEstrutura(pTabuleiro->pMatriz, numErros);
	}
}

#endif
