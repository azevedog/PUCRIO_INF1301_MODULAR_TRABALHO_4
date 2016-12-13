/***************************************************************************
*  $MCI Módulo de implementação: Modulo MATRIZ
*
*  Arquivo gerado:              Matriz.c
*  Letras identificadoras:      MAT
*
*  Autores: bap - Bruna Aleixo Penna Pereira
*           jpp - João Parreiras Martins Pereira
*           pgb - Pedro Gomes Branco
*
***************************************************************************/
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#include "CESPDIN.H"
#include "CONTA.H"
#endif

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor cabeça de matriz
*
***********************************************************************/
typedef struct MAT_tagMatriz {
	LIS_tppLista pLista; /* Ponteiro p/ corrente da matriz */
	int tam; /* Tamanho da matriz */
} MAT_tpMatriz;


/***********************************************************************
*
*  $FC Função: MAT &Criar matriz
*
***********************************************************************/
 MAT_tpCondRet MAT_CriarMatriz(MAT_tppMatriz* ppMatriz, int tam) {
	 int linhaCorrente;
	 int colunaCorrente;

	 if (tam <= 0) { 
		 return MAT_CondRetTamanhoInvalido;
	 }

	 #ifdef _DEBUG
	 	CNT_CONTAR("Criar-matriz");
	 #endif

	 // Cria a cabeca da matriz
	 *ppMatriz = (MAT_tpMatriz*)malloc(sizeof(MAT_tpMatriz));
	 if (*ppMatriz == NULL) { 
		 return MAT_CondRetFaltouMemoria; 
	 }

	 if(LIS_CriarLista("mat", &((*ppMatriz)->pLista)) == LIS_CondRetFaltouMemoria) {
		 free(*ppMatriz);
		 return MAT_CondRetFaltouMemoria;
	 }
	 (*ppMatriz)->tam = tam;

	 #ifdef _DEBUG
	 	CNT_CONTAR("Criar-matriz-pr0");
	 #endif

	 // Encadeia as celulas da matriz criada e inicializa ponteiro p/ lista em cada celula
	 for(linhaCorrente = 0; linhaCorrente < tam; linhaCorrente++) {
		#ifdef _DEBUG
			 CNT_CONTAR("Criar-matriz-for0");
		#endif

		 for(colunaCorrente = 0; colunaCorrente < tam; colunaCorrente++) {
		 	#ifdef _DEBUG
				CNT_CONTAR("Criar-matriz-for1");
			#endif

			if(LIS_InserirNo((*ppMatriz)->pLista, NULL) != LIS_CondRetOK) {
				#ifdef _DEBUG
					CNT_CONTAR("Criar-matriz-for1-if0");
				#endif
				 LIS_DestruirLista((*ppMatriz)->pLista);
				 free(*ppMatriz);
				 return MAT_CondRetFaltouMemoria;
			 }
		 }
	 }

	 LIS_IrInicioLista((*ppMatriz)->pLista);

	 #ifdef _DEBUG
	 	CNT_CONTAR("Criar-matriz-pr1");
	 	CED_MarcarEspacoAtivo(*ppMatriz);
	 #endif

	 return MAT_CondRetOK;
 }

/***********************************************************************
*
*  $FC Função: MAT &Destruir matriz
*
***********************************************************************/
 MAT_tpCondRet MAT_DestruirMatriz(MAT_tppMatriz pMatriz) {
	 if (pMatriz == NULL) {
		 return MAT_CondRetNulo;
	 }

	 LIS_DestruirLista(pMatriz->pLista);
	 free(pMatriz);

	#ifdef _DEBUG
	 	CNT_CONTAR("Destruir-matriz");
	 	CED_MarcarEspacoNaoAtivo(pMatriz);
	 #endif

	 return MAT_CondRetOK;
 }

/***********************************************************************
*
*  $FC Função: MAT &Mover célula corrente da matriz
*
***********************************************************************/
MAT_tpCondRet MAT_MoverCorrente(MAT_tppMatriz pMatriz, MAT_tpDirecao direcao) {
	 int qtdParaAndar = 0;
	 int i;
	 int j;
	 int k;

	 if (pMatriz == NULL) {
		 return MAT_CondRetNulo;
	 }

	 #ifdef _DEBUG
		CNT_CONTAR("Mover-corrente");
	 #endif

	 while(LIS_IrAnt(pMatriz->pLista) != LIS_CondRetNoCorrentePrimeiro) {
	 	 #ifdef _DEBUG
			CNT_CONTAR("Mover-corrente-while0");
		 #endif

		 qtdParaAndar++;
	 }

	 i = qtdParaAndar/pMatriz->tam;
	 j = qtdParaAndar - (pMatriz->tam * i);

	 MAT_DefinirCorrente(pMatriz, i, j);

	 #ifdef _DEBUG
		CNT_CONTAR("Mover-corrente-pr0");
	 #endif

	 if(direcao == MAT_DIR_C) {
	 	#ifdef _DEBUG
			CNT_CONTAR("Mover-corrente-if0");
	 	#endif

		 if (i <= 0) {
		 	#ifdef _DEBUG
				CNT_CONTAR("Mover-corrente-if0-if0");
	 		#endif
			 return MAT_CondRetDirecaoInvalida;
		 }
		 for(k = 0; k < pMatriz->tam; k++) {
		 	#ifdef _DEBUG
				CNT_CONTAR("Mover-corrente-if0-while0");
	 		#endif
			LIS_IrAnt(pMatriz->pLista);
		 }
	 } 
	 else if (direcao == MAT_DIR_B) {
	 	#ifdef _DEBUG
			CNT_CONTAR("Mover-corrente-if1");
	 	#endif

		 if (i >= pMatriz->tam-1) {
		 	#ifdef _DEBUG
				CNT_CONTAR("Mover-corrente-if1-if0");
	 		#endif

			 return MAT_CondRetDirecaoInvalida;
		 }
		 for(k = 0; k < pMatriz->tam; k++) {
		 	#ifdef _DEBUG
				CNT_CONTAR("Mover-corrente-if1-while0");
	 		#endif
			LIS_IrProx(pMatriz->pLista);
		 }
	 }
	 else if (direcao == MAT_DIR_E) {
	 	#ifdef _DEBUG
			CNT_CONTAR("Mover-corrente-if2");
	 	#endif
		
		 if(j-1 < 0) { 
		 	#ifdef _DEBUG
				CNT_CONTAR("Mover-corrente-if2-if0");
	 		#endif

			 return MAT_CondRetDirecaoInvalida; 
		 }

		 LIS_IrAnt(pMatriz->pLista);
	 }
	 else if (direcao == MAT_DIR_D) {
	 	#ifdef _DEBUG
			CNT_CONTAR("Mover-corrente-if3");
	 	#endif
		
		 if(j+1 > pMatriz->tam) { 
		 	#ifdef _DEBUG
				CNT_CONTAR("Mover-corrente-if3-if0");
	 		#endif
			 return MAT_CondRetDirecaoInvalida; 
		 }

		 LIS_IrProx(pMatriz->pLista);
	 }

	 return MAT_CondRetOK;
 }

/***********************************************************************
*
*  $FC Função: MAT &Definir célula corrente da matriz
*
***********************************************************************/
 MAT_tpCondRet MAT_DefinirCorrente(MAT_tppMatriz pMatriz, int i, int j) {
	 int qtdParaAndar;
	 int k;

	 if (pMatriz == NULL) {
		 return MAT_CondRetNulo;
	 }

	#ifdef _DEBUG
		CNT_CONTAR("Definir-corrente");
	 #endif

	 qtdParaAndar = i*(pMatriz->tam) + j;

	 // 'i' nem 'j' podem ser maiores que o numero de linhas e colunas, respectivamente.
	 if (i < 0 || i > (pMatriz->tam-1) || j < 0 || j > (pMatriz->tam - 1)) {
	 	#ifdef _DEBUG
			CNT_CONTAR("Definir-corrente-if0");
	 	#endif

		 return MAT_CondRetPosicaoInvalida;
	 }

	#ifdef _DEBUG
		CNT_CONTAR("Definir-corrente-pr0");
	 #endif

	 LIS_IrInicioLista(pMatriz->pLista);

	 for(k = 0; k < qtdParaAndar; k++) {
	 	#ifdef _DEBUG
			CNT_CONTAR("Definir-corrente-for0");
	 	#endif

		 if(LIS_IrProx(pMatriz->pLista) == LIS_CondRetNoCorrenteUltimo) {
		 	#ifdef _DEBUG
				CNT_CONTAR("Definir-corrente-for0-if0");
	 		#endif
			 return MAT_CondRetPosicaoInvalida;
		 }
	 }

	 #ifdef _DEBUG
		CNT_CONTAR("Definir-corrente-pr1");
	 #endif
	
	 return MAT_CondRetOK;
 }


/***********************************************************************
*  $FC Função: MAT Definir valor corrente
***********************************************************************/
 MAT_tpCondRet MAT_DefinirValorCorrente(MAT_tppMatriz pMatriz, void *pValor) {
	 if(pMatriz == NULL) {
		 return MAT_CondRetNulo;
	 }
	
	#ifdef _DEBUG
		CNT_CONTAR("Definir-valor-corrente");
	 #endif

	 LIS_AlterarNoCorrente(pMatriz->pLista, (void*)pValor);

	 return MAT_CondRetOK;
 }


/***********************************************************************
*  $FC Função: MAT Obter valor corrente
***********************************************************************/
 MAT_tpCondRet MAT_ObterValorCorrente(MAT_tppMatriz pMatriz, void **ppValor) {
	 if (pMatriz == NULL) {
		 return MAT_CondRetNulo;
	 }

	#ifdef _DEBUG
	 	CNT_CONTAR("Obter-valor-corrente");
	 #endif

	 LIS_ObterNo(pMatriz->pLista, (void**)ppValor);

	 return MAT_CondRetOK;
 }


 #ifdef _DEBUG
/***********************************************************************
*
*  $FC FunÁ„o: MAT Verificar estrutura
*
***********************************************************************/
 MAT_tpCondRet MAT_VerificarEstrutura( MAT_tppMatriz pMatriz, int * numErros) {
	 int numElem;
	 (*numErros) = 0;

     
	 if (pMatriz != NULL) {
		 LIS_ObterNumElementos(pMatriz->pLista, &numElem);
		 if (numElem != (pMatriz->tam * pMatriz->tam)) {
			 CNT_CONTAR("TAB-num-elems-diferente-esperado");
			 (*numErros)++;
         } else {
             CNT_CONTAR("TAB-num-elems-correto");
         }

		 LIS_VerificarEstrutura(pMatriz->pLista, numErros, qtdParaAndar);
     } else {
         if (CED_EhEspacoAtivo(pLista)) {
             CNT_CONTAR("TAB-tabuleiro-inexistente-espaco-ativo");
             (*numErros)++;
         }
     }
 }

/***********************************************************************
 *
 *  $FC Funcao: MAT Deturpar estrutura
 *
 ***********************************************************************/
MAT_tpCondRet MAT_Deturpar( MAT_tppMatriz pMatriz, int cmd, int i, int j  ) {
    int qtdParaAndar;
    
    qtdParaAndar = i*(pMatriz->tam) + j;
    
    if (pMatriz != NULL) {
        LIS_Deturpar(pMatriz->pLista, cmd, qtdParaAndar);
    }
    
    return MAT_CondRetOK;
}

#endif
