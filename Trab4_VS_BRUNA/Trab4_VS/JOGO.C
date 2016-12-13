#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "TABULEIRO.H"
#include "LISTA.H"
#include "TIPO_PECA.H"
#include "PECA.H"
#include "JOGO.h"

#define MAXNOME 100
#define MAXNOME_S "100"

/***********************************************************************
*
*  $TC Tipo de dados: JGO Descritor da cabeça de uma simulação
*
*
*  $ED Descrição do tipo
*     Armazena referências para o tabuleiro e para as cabeças das
*     listas de peças e tipos de peças.
*
***********************************************************************/

typedef struct JGO_tagSimulacao {
	TAB_tppTabuleiro pTab;
	/* Ponteiro para o tabuleiro corrente */
	
	LIS_tppLista pListaPecas;
	/* Ponteiro para a lista de peças */

	LIS_tppLista pListaTipos;
	/* Ponteiro para a lista de tipos de peças */
} JGO_tpSimulacao;

/*****  Variável global que armazena a simulação corrente  *****/
JGO_tpSimulacao simulacao;

static int JGO_ChecarMovimentoPulo (int movX, int movY);
static int JGO_ChecarLegalidade (PEC_tpJogador jogador, int xOrigem, char yOrigem, int xDestino, char yDestino);
static void JGO_AtualizarListaAmeacantesAmeacados();
static void JGO_ListarAmeacantesAmeacados();
static TPC_tppTipoPeca JGO_ProcurarTipo(char *nomeProcurado);
static PEC_tppPeca JGO_ObterRei(int* i, char* j, PEC_tpJogador jogador);
static int JGO_ChecarAmeacaRei(PEC_tpJogador jogador);
static int JGO_ChecarChequeMate(PEC_tpJogador jogador);
static int JGO_MoverPeca(int jogadorAtual);
static JGO_CarregarArquivoMovimentos(char * path);

/***********************************************************************
*
*  $FC Função: JGO funcao de saida
*
***********************************************************************/

void JGO_Sair(int code) {
	exit(code);
}

/***********************************************************************
*
*  $FC Função: JGO Exibe Tabuleiro
*
***********************************************************************/

JGO_tpCondRet JGO_ExibeTabuleiro() {
	int i, j;
	int jogador;
	char cor;
	char * pNomeTipo;
	PEC_tppPeca pPeca;
	TPC_tppTipoPeca pTipoPeca;

	TAB_tpCondRet condret;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	printf("\n\n");
	printf("    A     B     C     D     E     F     G     H\n");
	printf("------------------------------------------------\n");
	for (i = 8; i > 0; i--)
	{
		for (j = 0; j < 8; j++)
		{
			if (TAB_ObterPeca(simulacao.pTab, i, j+65, (void**)&pPeca, &jogador) == TAB_CondRetOK) {
				PEC_ObterTipoPeca(pPeca, &pTipoPeca);
				TPC_ObterNome(pTipoPeca, &pNomeTipo);

				printf("|");

				cor = jogador ? 'P' : 'B';

				if (cor == 'P') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				}
				

				printf("%s", pNomeTipo, cor);

				SetConsoleTextAttribute(hConsole, saved_attributes);
			} else {
				printf("|     ");
			}
		}
		printf("| %d\n------------------------------------------------\n", i);
	}
	printf("\n\n");

	return JGO_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: JGO Inicializa
*
***********************************************************************/

JGO_tpCondRet JGO_Inicializa(void) {
	if (TAB_CriarTabuleiro(&(simulacao.pTab)) != TAB_CondRetOK) {
		printf("Erro de memoria ao criar o tabuleiro.");
		return JGO_CondRetFaltouMemoria;
		exit(1);
	}

	if (LIS_CriarLista("Tipos", &(simulacao.pListaTipos)) == LIS_CondRetFaltouMemoria) {
		TAB_DestruirTabuleiro(simulacao.pTab);
		printf("Erro de memoria ao criar lista com tipo de pecas.");
		return JGO_CondRetFaltouMemoria;
		exit(1);
	}

	if (LIS_CriarLista("Pecas", &(simulacao.pListaPecas)) == LIS_CondRetFaltouMemoria) {
		TAB_DestruirTabuleiro(simulacao.pTab);
		LIS_DestruirLista(simulacao.pListaTipos);
		printf("Erro de memoria ao criar lista de pecas.");
		return JGO_CondRetFaltouMemoria;
		exit(1);
	}

	return JGO_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: JGO Inicia
*
***********************************************************************/

JGO_tpCondRet JGO_IniciaJogo(void) {
	int jogadorAtual = 0;
	char jogador[7];

	JGO_ExibeTabuleiro( );

	while (JGO_ChecarChequeMate((PEC_tpJogador)0) == 0 && JGO_ChecarChequeMate((PEC_tpJogador)1) == 0) {
		if (jogadorAtual == 0) {
			strcpy(jogador, "Branco");
		} else {
			strcpy(jogador, "Preto");
		}

		printf("\n\nVez do jogador %s\n\n", jogador);

		if(JGO_MoverPeca(jogadorAtual)) {
			if (jogadorAtual == 0) {
				jogadorAtual = 1;
			} else {
				jogadorAtual = 0;
			}

			JGO_ExibeTabuleiro( );
			JGO_AtualizarListaAmeacantesAmeacados( );
			JGO_ListarAmeacantesAmeacados( );
		} else {
			printf("Movimento invalido!\n");
		}
	}

	JGO_Sair(1);
	return JGO_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: JGO Novo Tabuleiro
*
***********************************************************************/

JGO_tpCondRet JGO_NovoTabuleiro(void) {

	LIS_DestruirLista(simulacao.pListaTipos);
	LIS_DestruirLista(simulacao.pListaPecas);
	TAB_DestruirTabuleiro(simulacao.pTab);

	simulacao.pTab = NULL;
	simulacao.pListaTipos = NULL;
	simulacao.pListaPecas = NULL;

	JGO_Inicializa();

	return JGO_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: JGO Abrir Tabuleiro
*
***********************************************************************/
JGO_tpCondRet JGO_AbrirTabuleiro(char* dir) {
	JGO_NovoTabuleiro();

	if (JGO_CarregarArquivoMovimentos(dir) == 1) {
		printf("\nArquivo %s aberto.\n", dir);
		return JGO_CondRetOK;
	}

	return JGO_CondRetCaminhoInvalido;
}


/***********************************************************************
*
*  $FC Função: JGO Salvar Tabuleiro
*
***********************************************************************/
JGO_tpCondRet JGO_SalvarTabuleiro(char* dir) {
	TPC_tppTipoPeca pTipo;
	PEC_tppPeca pPeca;

	int i, j, ic, count, nMovs;
	char* nome;
	PEC_tpJogador jogador;
	FILE* fp;

	fp = fopen(dir, "w");

	if (!fp) {
		printf("\nCaminho invalido.\n");
		return JGO_CondRetCaminhoInvalido;
	}

	LIS_IrInicioLista(simulacao.pListaTipos);
	while (LIS_ObterNo(simulacao.pListaTipos, (void**)&pTipo) == LIS_CondRetOK) {

		TPC_ObterNome(pTipo, &nome);
		fprintf(fp, "TIPO %s\n", nome);
		TPC_ObterNumMovimentos(pTipo, &nMovs);

		for(count = 0; count < nMovs; count++) {
			TPC_ObterMovimento(pTipo, count, &i, &j);
			fprintf(fp, "MOV %d %d\n", i, j);
		}

		if (LIS_IrProx(simulacao.pListaTipos) != LIS_CondRetOK) {
			break;
		}
	}

	fprintf(fp, "TABULEIRO\n");
	for (ic = 1; ic <= 8; ic++) {
		for (j = 'A'; j <= 'H'; j++) {
			if (TAB_ObterPeca(simulacao.pTab, ic, j, (void**)&pPeca, (int*)&jogador) != TAB_CondRetOK) {
				continue;
			}

			PEC_ObterTipoPeca(pPeca, &pTipo);
			TPC_ObterNome(pTipo, &nome);

			fprintf(fp, "%c %c %d %s\n", (jogador == JOGADOR_BRANCO) ? 'B' : 'P', ic, j, nome);
		}
	}

	printf("\nArquivo salvo com sucesso.\n");
	fclose(fp);
	return JGO_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: JGO cria peca
*
***********************************************************************/

JGO_tpCondRet JGO_CriarPeca(char* nomeTipo, int jogador, char coluna, int linha) 
{
	int cor;
    PEC_tppPeca pPeca;
    PEC_tppPeca pPecaAux;
    TPC_tppTipoPeca pTipoPeca;

    printf("\nCriacao de Peca\n");

    pTipoPeca = JGO_ProcurarTipo(nomeTipo);

    if(pTipoPeca==NULL) { 
        printf("Tipo inexistente\n");
        return JGO_CondRetTipoInexistente;
    }

    PEC_CriarPeca(&pPeca, pTipoPeca, (PEC_tpJogador)jogador);

    if(pPeca==NULL) {
        printf("Falta de memoria ao criar peca\n");
        return JGO_CondRetFaltouMemoria;
    }

    if(TAB_DefinirPosCorrente( simulacao.pTab, linha, coluna ) == TAB_CondRetCasaInexistente) {
        printf("\nEsta posicao nao existe!\n");
        return JGO_CondRetPosicaoInvalida;
    }

    if(TAB_ObterPeca(simulacao.pTab, linha, coluna, (void**)&pPecaAux, &cor) != TAB_CondRetCasaVazia) {
        printf("\nJa existe uma peca nesta casa. Por favor, escolha outra.\n");
        return JGO_CondRetPosicaoInvalida;
    }       

    if(TAB_InserirPeca(simulacao.pTab, pPeca, linha, coluna, jogador) == TAB_CondRetFaltouMemoria) {
        printf("Erro de memoria ao atribuir peca ao local do tabuleiro.\n");
		return JGO_CondRetFaltouMemoria;
        JGO_Sair(1);
    }

    if(LIS_InserirNo(simulacao.pListaPecas, pPeca) == LIS_CondRetFaltouMemoria) {
        printf("Erro de memoria ao inserir peca na lista de pecas.\n");
		return JGO_CondRetFaltouMemoria;
        JGO_Sair(1);
    }
}

/***********************************************************************
*
*  $FC Função: JGO altera peça
*
***********************************************************************/

JGO_tpCondRet JGO_AlterarPosicaoPeca(int linha, char coluna, int linha2, int coluna2) {

	char* nomeTipoPeca;
    int opcao, cor, jogadorComido, movValido;
    PEC_tppPeca pPeca, pPecaAux;
    TPC_tppTipoPeca pTipoPeca;
    char nomeTipo[MAXNOME];

	if(TAB_DefinirPosCorrente( simulacao.pTab, linha, coluna ) == TAB_CondRetCasaInexistente) {
        printf("\nEsta posicao nao existe!\n");
        return JGO_CondRetPosicaoInvalida;
    }

	if(TAB_ObterPeca(simulacao.pTab, linha, coluna, (void**)&pPeca, &cor) != TAB_CondRetOK) {
		printf("\nEsta posicao nao contem uma peca!\n");
        return JGO_CondRetPosicaoInvalida;
	}

	PEC_ObterTipoPeca(pPeca, &pTipoPeca);

	if(TAB_DefinirPosCorrente( simulacao.pTab, linha2, coluna2 ) == TAB_CondRetCasaInexistente) {
		printf("\nEsta posicao nao existe!\n");
		return JGO_CondRetPosicaoInvalida;
	}

	if (TAB_ObterPeca(simulacao.pTab, linha2, coluna2, (void**)&pPecaAux, &cor) == TAB_CondRetOK) {
		printf("\nJa existe uma peca nessa posicao!\n");
		return JGO_CondRetPosicaoInvalida;
	}

	TAB_MoverPeca(simulacao.pTab, linha, coluna, linha2, coluna2, (void**)&pPecaAux, &jogadorComido);

	return JGO_CondRetOK;
}

JGO_tpCondRet JGO_AlterarTipoPeca(char* nomeTipo, int linha, char coluna) {
    TPC_tppTipoPeca pTipoPeca;
	PEC_tppPeca pPeca;
	int cor;

	if(TAB_DefinirPosCorrente( simulacao.pTab, linha, coluna ) == TAB_CondRetCasaInexistente) {
        printf("\nEsta posicao nao existe!\n");
        return JGO_CondRetPosicaoInvalida;
    }

	if(TAB_ObterPeca(simulacao.pTab, linha, coluna, (void**)&pPeca, &cor) != TAB_CondRetOK) {
		printf("\nEsta posicao nao contem uma peca!\n");
        return JGO_CondRetPosicaoInvalida;
	}

	pTipoPeca = JGO_ProcurarTipo(nomeTipo);

    if(pTipoPeca==NULL) {
		printf("\nTipo inexistente\n");
        return JGO_CondRetTipoInexistente;
    }

    PEC_AtribuirTipoPeca(pPeca, pTipoPeca);

	return JGO_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: JGO Excluir Peca
*
***********************************************************************/

JGO_tpCondRet JGO_ExcluirPeca(int linha, char coluna) {

    char jCorr;
    int cor, iCorr;
    PEC_tppPeca pPeca;

    if(TAB_DefinirPosCorrente( simulacao.pTab, linha, coluna ) == TAB_CondRetCasaInexistente) {
        printf("\nEsta posicao nao existe!\n");
        return JGO_CondRetPosicaoInvalida;
    }

	if (TAB_ObterPeca(simulacao.pTab, linha, coluna, (void**)&pPeca, &cor) != TAB_CondRetOK) {
        printf("\nEsta posicao nao contem uma peca!\n");
        return JGO_CondRetPosicaoInvalida;
    }

	TAB_ObterPosCorrente(simulacao.pTab, &iCorr, &jCorr);
	TAB_RetirarPeca(simulacao.pTab, iCorr, jCorr);

	LIS_IrInicioLista(simulacao.pListaPecas);

    if(LIS_ProcurarValor( simulacao.pListaPecas, pPeca) == LIS_CondRetOK) {
        LIS_ExcluirElemento( simulacao.pListaPecas );
    } else {
        printf("Erro ao excluir peca da lista de pecas");
        JGO_Sair( 1 );
    }

    printf("\nPeca destruida com sucesso!\n");
	return JGO_CondRetOK;
}


/***********************************************************************
*
*  $FC Função: JGO Listar Pecas
*
***********************************************************************/

JGO_tpCondRet JGO_ListarPecas() {
	TPC_tppTipoPeca pTipo;
	PEC_tppPeca pPeca;
	int ic;
	char * nome, j;
	PEC_tpJogador jogador;

	printf("\nLista de pecas:\n");

	for (ic = 1; ic <= 8; ic++) {
		for (j = 'A'; j <= 'H'; j++) {
			if (TAB_ObterPeca(simulacao.pTab, ic, j, (void**)&pPeca, (int*)&jogador) == TAB_CondRetOK) {
				if(pPeca != NULL) {
					PEC_ObterJogador(pPeca, &jogador);
					PEC_ObterTipoPeca(pPeca, &pTipo);
					TPC_ObterNome(pTipo, &nome);

					printf("* [%c] %d%c %s\n", (jogador == JOGADOR_BRANCO) ? 'B' : 'P', ic, j, nome);
				}
			}
		}
	}

	return JGO_CondRetOK;
	printf("<FIM>\n");
}


/***********************************************************************
*
*  $FC Função: JGO cria tipo de peça
*
***********************************************************************/

JGO_tpCondRet JGO_CriarTipo(char* nomeTipo, int* movsI, int* movsJ, int qtdMovs ) {
    int i;
    TPC_tppTipoPeca pTipoPeca, pTipoPecaAux;
	LIS_tpCondRet lisCondRet;
	char* nomeTipoPeca;

	pTipoPecaAux = (TPC_tppTipoPeca)malloc(sizeof(TPC_tppTipoPeca));
	if (pTipoPecaAux == NULL) {
		return JGO_CondRetFaltouMemoria;
		JGO_Sair(1);
	}

    if(JGO_ProcurarTipo(nomeTipo) != NULL) { 
        printf("Tipo de peca com esse nome ja existe\n");
        return JGO_CondRetTipoJaExiste;
    }

    TPC_CriarTipoPeca(&pTipoPeca, nomeTipo);

    if(pTipoPeca == NULL) {
        printf("Erro de memoria ao alocar novo tipo de peca.");
		return JGO_CondRetFaltouMemoria;
        JGO_Sair(1);
    }

	for(i = 0; i < qtdMovs; i++) {
		if( TPC_AdicionarMovimento(pTipoPeca, movsI[i], movsJ[i]) == TPC_CondRetFaltouMemoria) {
            printf("Erro de memoria ao adicionar movimento.");
			return JGO_CondRetFaltouMemoria;
            JGO_Sair(1);
        }
	}

	while(LIS_IrProx(simulacao.pListaTipos) == LIS_CondRetOK) {}

    LIS_InserirNo(simulacao.pListaTipos, pTipoPeca);

	return JGO_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: JGO Listar Tipos
*
***********************************************************************/

JGO_tpCondRet JGO_ListarTipos( void ) {
    TPC_tppTipoPeca pTipo;
    char * nome;
    int count, nMovs;
    int movI, movJ;

    printf("Lista de tipos criados:\n");

	pTipo = (TPC_tppTipoPeca)malloc(sizeof(TPC_tppTipoPeca));
	if(pTipo == NULL) {
		JGO_Sair(1);
	}

    LIS_IrInicioLista( simulacao.pListaTipos );
    while (LIS_ObterNo( simulacao.pListaTipos, (void**)&pTipo ) == LIS_CondRetOK) {
        TPC_ObterNome((TPC_tppTipoPeca)pTipo, &nome);
        printf("* %s ",nome);

        TPC_ObterNumMovimentos((TPC_tppTipoPeca)pTipo, &nMovs);
        for(count = 0; count < nMovs; count++) {
            TPC_ObterMovimento( pTipo, count, &movI, &movJ);
            printf("{%d,%d} ", movI, movJ);
        }

        printf("\n");

        if( LIS_IrProx( simulacao.pListaTipos) != LIS_CondRetOK )
            break;
    }

	return JGO_CondRetOK;
    printf("<fim>\n");
}


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: JGO checa se movimento é do tipo pulo
*
*  $ED Descrição da função
*     Checa se o movimento descrito pelos parâmetros é do tipo pulo ou não.
*     Se for um movimento vertical, horizontal ou diagonal, não é de pulo.  
*
*  $FV Valor retornado
*     1 se o movimento é pulo
*     0 se o movimento não é pulo
*
***********************************************************************/

static int JGO_ChecarMovimentoPulo (int movX, int movY) {
    if(movX == movY || movX == -movY || movX == 0 || movY == 0){
        return 0;
    }

    return 1;
}


/***********************************************************************
*
*  $FC Função: JGO checar legalidade de movimento
*
*  $ED Descrição da função
*     Checa se um movimento é legal, CHECANDO SOMENTE OBSTACULOS NO CAMINHO
*       E CONFLITOS DE DESTINO COM PEÇAS DO MESMO JOGADOR.
*     ASSUME-SE QUE O MOVIMENTO PRIMITIVO É UM MOVIMENTO VÁLIDO PARA O
*       TIPO DA PEÇA NA ORIGEM.
*
*  $FV Valor retornado
*     1 se o movimento é legal
*     0 se o movimento é ilegal
*
***********************************************************************/

static int JGO_ChecarLegalidade (PEC_tpJogador jogador, int xOrigem, char yOrigem, int xDestino, char yDestino) {
    PEC_tppPeca pPeca;
    PEC_tpJogador jogadorDefensor;
    PEC_tppPeca obstaculo;
    int movX, movY;
    int x;
	int cor;
	char y;

    movX = xDestino - xOrigem;
    movY = yDestino - yOrigem;

    // Se tentar mover uma peça de um jogador para uma casa que está ocupada por
    // uma peça do mesmo jogador, não é um movimento legal.
    // (não é permitido comer peças próprias)
	if(TAB_ObterPeca(simulacao.pTab, xDestino, yDestino, (void**)&pPeca, (int*)&jogadorDefensor) == TAB_CondRetOK) {
        if(jogadorDefensor == jogador){
            return 0;
        }
    }

    if(JGO_ChecarMovimentoPulo(movX, movY) == 1) {
        // Sendo um movimento de pulo, não há necessidade de checar obstáculos
        // Logo, o movimento é válido

        return 1;
    }

    // Não sendo um movimento de pulo, precisamos saber se há obstáculos.

    if( movY == 0 ) {
        if( movX > 0 ) {
            // movimento horizontal para a direita
            y = yOrigem; // = yDestino;

            for( x = xOrigem + 1; x < xDestino; x++ ) {
                if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        } 
        if ( movX < 0 ) {
            // movimento horizontal para a esquerda
            y = yOrigem; // = yDestino;

            for( x = xOrigem - 1 ; x > xDestino; x-- ) {
				 if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        }
    }   

    if( movX == 0 ) {
        if( movY > 0 ) {
            // movimento vertical para cima 
            x = xOrigem; // = xDestino;

            for( y = yOrigem + 1; y < yDestino; y++ ) {
                if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        } 
        if ( movY < 0 ) {
            // movimento vertical para baixo
            x = xOrigem; // = xDestino;

            for( y = yOrigem - 1; y > yDestino; y-- ) {
                 if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        }
    } 

    if( movY > 0 ) {
        if( movX > 0 ) {
            // movimento diagonal para cima e para a direita
            for( x = xOrigem + 1, y = yOrigem + 1; x < xDestino && y < yDestino; x++, y++ ) {
                 if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        }
        else {
            // movimento diagonal para cima e para a esquerda
            for( x = xOrigem - 1, y = yOrigem + 1; x > xDestino && y < yDestino; x--, y++ ) {
                 if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        }
    }

    else { 
        if( movX > 0 ) {
            // movimento diagonal para baixo e para a direita
            for( x = xOrigem + 1, y = yOrigem - 1; x < xDestino && y > yDestino; x++, y--) {
                 if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        }
        else {
            // movimento diagonal para baixo e para a esquerda
            for( x = xOrigem - 1, y = yOrigem - 1; x > xDestino && y > yDestino; x--, y--) {
                 if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&obstaculo, &cor) == TAB_CondRetOK) {
                    return 0;
                }
            }

            return 1;
        }
    }

}
/***********************************************************************
*
*  $FC Função: JGO atualiza as listas de ameaçantes e ameaçados de cada casa
*  do tabuleiro 
*
*  $ED Descrição da função
*     Atualiza as listas de ameaçantes e ameaçados de cada casa do tabuleiro
*
*
***********************************************************************/

static void JGO_AtualizarListaAmeacantesAmeacados() {
    int x, xDest, movX, legalidade, c, nMovs, movY;
    char y, yDest;
	PEC_tpJogador jogadorAtual, jogadorOposto;
    PEC_tppPeca pPecaAtual, pPecaDest;
    TPC_tppTipoPeca tipoDaPecaAtual;
	LIS_tppLista lista;

    for(x = 1; x <= 8; x++) {
        for(y = 'A'; y <= 'H'; y++) {
			TAB_EsvaziarListasDaCasa(simulacao.pTab, x, y);
        }
    }
    // Vamos percorrer todas as peças do tabuleiro. Para cada peça, vamos ver quais dos seus movimentos   
    // válidos ameaça uma peça do jogador oposto. 
    // Depois de cada movimento, se a peça 'comer' uma peça da cor oposta, a peça comida será adicionada
    // para a lista de ameaçados pela peça em questão, e será adicionada para a lista de ameaçantes da peça
    // comida.

    for(x = 1; x <= 8; x++) {
        for(y = 'A'; y <= 'H'; y++) {
            if (TAB_ObterPeca(simulacao.pTab, x, y, (void**)&pPecaAtual, (int*)&jogadorAtual) == TAB_CondRetOK) {

                if(PEC_ObterTipoPeca(pPecaAtual, &tipoDaPecaAtual) == PEC_CondRetPonteiroNulo){
                    printf("Erro: peca com tipo inexistente.");
                    JGO_Sair(1);
                }                    

                TPC_ObterNumMovimentos(tipoDaPecaAtual, &nMovs);

                for(c = 0; c < nMovs; c++){
                    TPC_ObterMovimento(tipoDaPecaAtual, c, &movX, &movY );

                    xDest = x + movX;
                    yDest = y + movY;

                    if(TAB_ChecarPosicaoValida(xDest, yDest) == TAB_CondRetOK) {

                        //checar se movimento eh legal
						legalidade = JGO_ChecarLegalidade( jogadorAtual, x, y, xDest, yDest);
                        
                        if( legalidade == 1 ) {

                            if(TAB_ObterPeca(simulacao.pTab, xDest, yDest, (void**)&pPecaDest, (int*)&jogadorOposto) == TAB_CondRetOK) {
                                TAB_AdicionarListaAmeacantesAmeacados(simulacao.pTab, x, y, xDest, yDest);

                            }
                        }
                    }
                }
            }
        }
    }
}


/***********************************************************************
*
*  $FC Função: JGO Printar Ameacantes Ameacados
*
***********************************************************************/

static void JGO_ListarAmeacantesAmeacados() {
    int ic, jogador, cont, numElems;
    char * nome, *nomePecaAtual, j;
    LIS_tppLista pListaAmeacados, pListaAmeacantes; 
    PEC_tppPeca pPeca, pPecaAtual;
    TPC_tppTipoPeca pTipoPeca, pTipoPecaAtual;
	TAB_tppCasa pCasa; 

    nome = (char*)malloc(10*sizeof(char));
    if ( nome == NULL ) {
       JGO_Sair(1);
    } /* if */

	nomePecaAtual = (char*)malloc(10*sizeof(char));
    if ( nomePecaAtual == NULL ) {
       JGO_Sair(1);
    } /* if */

	pCasa = (TAB_tppCasa)malloc(sizeof(TAB_tppCasa));
    if (pCasa == NULL) {
        JGO_Sair(1);
    }

    pPeca = (PEC_tppPeca)malloc(sizeof(PEC_tppPeca));
    if (pPeca == NULL) {
        JGO_Sair(1);
    }

	pPecaAtual = (PEC_tppPeca)malloc(sizeof(PEC_tppPeca));
    if (pPecaAtual == NULL) {
        JGO_Sair(1);
    }

    pTipoPeca = (TPC_tppTipoPeca)malloc(sizeof(TPC_tppTipoPeca));
    if (pTipoPeca == NULL) {
        JGO_Sair(1);
    }

	pTipoPecaAtual = (TPC_tppTipoPeca)malloc(sizeof(TPC_tppTipoPeca));
    if (pTipoPecaAtual == NULL) {
        JGO_Sair(1);
    }

    for (ic = 1; ic <= 8; ic++) {
        for (j = 'A'; j <= 'H'; j++) {

            if(TAB_ObterPeca(simulacao.pTab, ic, j, (void**)&pPecaAtual, &jogador) == TAB_CondRetOK) {
				PEC_ObterTipoPeca( pPecaAtual,  &pTipoPecaAtual);
				TPC_ObterNome(pTipoPecaAtual , &nomePecaAtual);

                if (TAB_ObterListaAmeacados(simulacao.pTab, ic, j, &pListaAmeacados) == TAB_CondRetOK) {
					
					printf("Lista de ameacados (%s na posicao %d %c):", nomePecaAtual, ic, j);

					LIS_ObterNumElementos(pListaAmeacados, &numElems);
					for (cont = 0; cont < numElems; cont++) {
						LIS_ObterNo(pListaAmeacados, (void**)&pCasa);
						TAB_ObterPecaDaCasa(pCasa, (void**)&pPeca);
                        PEC_ObterTipoPeca( pPeca,  &pTipoPeca);
                        TPC_ObterNome(pTipoPeca , &nome);
                            
                        printf("%s, ", nome);
                    }
                }
				printf("\n");

                if (TAB_ObterListaAmeacantes(simulacao.pTab, ic, j, &pListaAmeacantes) == TAB_CondRetOK) {
					printf("Lista de ameacantes (%s na posicao %d %c):", nomePecaAtual, ic, j);

					LIS_ObterNumElementos(pListaAmeacantes, &numElems);
                    for (cont = 0; cont < numElems; cont++) {
						LIS_ObterNo(pListaAmeacantes, (void**)&pCasa);
						TAB_ObterPecaDaCasa(pCasa, (void**)&pPeca);
                        PEC_ObterTipoPeca(pPeca,  &pTipoPeca);
                        TPC_ObterNome(pTipoPeca , &nome);
                            
                        printf("%s, ", nome);

                    }
                }
				printf("\n\n");
            }
            
            

        }
    }
    printf("<FIM>\n");
}

/***********************************************************************
*
*  $FC Função: JGO procurar tipo de peça
*
*  $ED Descrição da função
*     A partir da string dada, procura na lista de tipos de peças
*        por um tipo com tal nome.
*
*  $FV Valor retornado
*     Ponteiro para o tipo da peça encontrado, ou NULL se não achar
*
***********************************************************************/

static TPC_tppTipoPeca JGO_ProcurarTipo(char *nomeProcurado) {
    LIS_tpCondRet lisCondRet;
    TPC_tppTipoPeca pTipoPeca;
    char *nomeObtido;

    if (nomeProcurado == NULL) {
        return NULL;
    }

    LIS_IrInicioLista(simulacao.pListaTipos);

    do {
        if (LIS_ObterNo(simulacao.pListaTipos, (void**)&pTipoPeca) != LIS_CondRetListaVazia) {
			TPC_ObterNome(pTipoPeca, &nomeObtido);

            if (strcmp(nomeObtido, nomeProcurado) == 0) {
                return pTipoPeca;
            }
		}

        lisCondRet = LIS_IrProx(simulacao.pListaTipos);
    } while (lisCondRet != LIS_CondRetNoCorrenteUltimo && lisCondRet != LIS_CondRetListaVazia);

    return NULL;
}

/***********************************************************************
*
*  $FC Função: JGO Obter Rei
*
*  $ED Descrição da função
*    Percorre todo o tabuleiro, em busca de uma peca Rei
*	 pertencendo ao jogador atual.
*
*  $EP Parâmetros
*     $P i - ponteiro para inteiro onde sera armazenada a coordenada i da posicao do rei do jogador
*     $P j - ponteiro para inteiro onde sera armazenada a coordenada j da posicao do rei do jogador
*	  $P jogadorAtual - inteiro representando o jogador atual
*
*  $FV Valor retornado
*     ponteiro para o rei, caso ele seja encontrado, e NULL caso contrario
*
***********************************************************************/

static PEC_tppPeca JGO_ObterRei(int* i, char* j, PEC_tpJogador jogador) {
	PEC_tppPeca pPeca;
	PEC_tpJogador jogadorAtual;
	TPC_tppTipoPeca pTipo;
	
	int ic; 
	char jc;
	char *nome;

	for (ic = 1; ic <= 8; ic++) {
		for (jc = 'A'; jc <= 'H'; jc++) {
			TAB_ObterPeca(simulacao.pTab, ic, jc, (void**)&pPeca, (int*)&jogadorAtual);
			if (pPeca == NULL)
				continue;

			if (jogador != jogadorAtual)
				continue;

			PEC_ObterTipoPeca(pPeca, &pTipo);
			TPC_ObterNome(pTipo, &nome);

			if (strcmp(nome, "Rei") != 0)
				continue;

			*i = ic;
			*j = jc;
			return pPeca;
		}
	}

	return NULL;
}



/***********************************************************************
*
*  $FC Função: JGO Checar Ameaca Rei
*
*  $ED Descrição da função
*    Obtem o rei e analisa para cada outra peca no tabuleiro se
*	 ha algum movimento legal para cada peca que ameace diretamente
*	 o rei.
*
*  $EP Parâmetros
*     $P jogadorAtual - inteiro representando o jogador atual
*
*  $FV Valor retornado
*     0 - ha ameaca
*	  1 - nao ha ameaca
*
***********************************************************************/

static int JGO_ChecarAmeacaRei(PEC_tpJogador jogador) {
	int reiI; char reiJ;
	PEC_tppPeca rei, pecaAtual;
	TPC_tppTipoPeca tipoPecaAtual;

	int jogadorPecaAtual;
	int i;
	char j;
	int movI, movJ, resposta, legalidade;

	rei = JGO_ObterRei(&reiI, &reiJ, jogador);
	if (rei == NULL) {
		printf("Nao foi encontrado nenhum rei da cor buscada no tabuleiro.");
		return 0;
	}

	for (i = 1; i <= 8; i++) {
		for (j = 'A'; j <= 'H'; j++) {
			if (TAB_ObterPeca(simulacao.pTab, i, j, (void**)&pecaAtual, &jogadorPecaAtual) == TAB_CondRetOK) {

				if (jogadorPecaAtual != jogador) {
					PEC_ObterTipoPeca(pecaAtual, &tipoPecaAtual);

					if (tipoPecaAtual == NULL) {
						printf("Erro: peca com tipo nulo.");
						JGO_Sair(1);
					}

					movI = (reiI - i);
					movJ = (reiJ - j);

					TPC_ConferirMovimento(tipoPecaAtual, movI, movJ, &resposta);

					if (resposta == 1) {
						legalidade = JGO_ChecarLegalidade((PEC_tpJogador)jogadorPecaAtual, i, j, reiI, reiJ);
						if (legalidade == 1) {
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

/***********************************************************************
*
*  $FC Função: JGO Checar Cheque Mate
*
*  $ED Descrição da função
*	  Confere se o rei do jogador esta em cheque mate
*
*  $EP Parâmetros
*     $P jogadorAtual - inteiro representando o jogador atual
*
*  $FV Valor retornado
*     0 - ha cheque mate
*	  1 - nao ha chequemate
*
***********************************************************************/

static int JGO_ChecarChequeMate(PEC_tpJogador jogador) {
	int reiI; 
	char reiJ;
	PEC_tppPeca rei;

	int jogadorComido;
	int i, iDest;
	char j, jDest;
	char corJogador[10];
	PEC_tppPeca pecaAtual, pPecaComida;
	PEC_tpJogador jogadorPecaAtual;
	TPC_tppTipoPeca tipoPecaAtual;

	int nMovs, c, movI, ameaca, legalidade, movJ;

	if (jogador == JOGADOR_BRANCO) {
		strcpy(corJogador, "Branco");
	} else {
		strcpy(corJogador, "Preto");
	}


	rei = JGO_ObterRei(&reiI, &reiJ, jogador);
	if (rei == NULL) {
		printf("Nao foi encontrado nenhum rei no tabuleiro.\n");
		return 0;
	}
	if (JGO_ChecarAmeacaRei(jogador) == 0) {
		printf("Nao ha cheque-mate, nem cheque. (O rei %s nao esta ameacado)\n", corJogador);
		return 0;
	}

	for (i = 1; i <= 8; i++) {
		for (j = 'A'; j <= 'H'; j++) {
			TAB_ObterPeca(simulacao.pTab, i, j, (void**)&pecaAtual, (int*)&jogadorPecaAtual);

			if (pecaAtual != NULL) {

				if (jogadorPecaAtual == jogador) {
					PEC_ObterTipoPeca(pecaAtual, &tipoPecaAtual);

					if (tipoPecaAtual == NULL) {
						printf("Erro: peca com tipo nulo.\n");
						JGO_Sair(1);
					}

					TPC_ObterNumMovimentos(tipoPecaAtual, &nMovs);

					for (c = 0; c < nMovs; c++) {
						TPC_ObterMovimento(tipoPecaAtual, c, &movI, &movJ);

						iDest = i + movI;
						jDest = j + movJ;

						if (TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetOK) {

							legalidade = JGO_ChecarLegalidade(jogadorPecaAtual, i, j, iDest, jDest);
							if (legalidade == 1) {

								TAB_MoverPeca(simulacao.pTab, i, j, iDest, jDest, (void**)&pPecaComida, &jogadorComido);
								
                                ameaca = JGO_ChecarAmeacaRei(jogador);

								TAB_VoltarPeca(simulacao.pTab, i, j, iDest, jDest, (void**)&pPecaComida);
								
								if (ameaca == 0) {
									printf("O rei %s esta em cheque, mas nao em cheque-mate.\n"
										"Movimento: %d%c para %d%c.\n", corJogador, i, j, iDest, jDest);
									return 0;
								} 
							}
						}
					}
				}
			}
		}
	}

	printf("O jogador %s esta em cheque-mate.\n", corJogador);

	return 1;
}

/***********************************************************************
*
*  $FC Função: JGO mover peça
*
*  $ED Descrição da função
*     Move uma peca do jogador atual
*
*  $EP Parâmetros
*     $P jogadorAtual - inteiro representando o jogador atual
*
*  $FV Valor retornado
*     0 - foi possivel mover a peca
*	  1 - nao foi possivel mover a peca
*
***********************************************************************/

static int JGO_MoverPeca(int jogadorAtual) {
	char coluna, coluna2, qtdMovColuna;
	char* nomeTipoPeca;
    int linha, linha2, opcao, cor, cor2, jogadorComido, movValido, qtdMovLinha;
    PEC_tppPeca pPeca, pPecaComida;
    TPC_tppTipoPeca pTipoPeca;
    char nomeTipo[MAXNOME];

    printf("Digite as coordenadas do tabuleiro onde esta a peca que voce deseja alterar\n");
	printf("Para sair, digite ou a coordenada 'S' para coluna, ou '-1' para linha.\n");
    printf("Digite a coluna (A a H)\n> ");
    scanf(" %c", &coluna);
    printf("Digite a linha (1 a 8)\n> ");
    scanf("%d", &linha);

	if(coluna == 'S' || linha == -1) {
		JGO_Sair(1);
	}

    if(TAB_DefinirPosCorrente( simulacao.pTab, linha, coluna ) == TAB_CondRetCasaInexistente) {
        printf("\nEsta posicao nao existe!\n");
        return 0;
    }

	if(TAB_ObterPeca(simulacao.pTab, linha, coluna, (void**)&pPeca, &cor) != TAB_CondRetOK) {
		printf("\nEsta posicao nao contem uma peca!\n");
        return 0;
	}

	if(cor != jogadorAtual) {
		printf("\nTentou mover uma peca do oponente. Jogue novamente.\n");
		return 0;
	}
 
	
	printf("Digite as novas coordenadas da peca\n");
    printf("Digite a coluna (A a H)\n> ");
    scanf(" %c", &coluna2);
    printf("Digite a linha (1 a 8)\n> ");
    scanf("%d", &linha2);

	if(TAB_DefinirPosCorrente( simulacao.pTab, linha2, coluna2 ) == TAB_CondRetCasaInexistente) {
		printf("\nEsta posicao nao existe!\n");
		return 0;
	}

	if (TAB_ObterPeca(simulacao.pTab, linha2, coluna2, (void**)&pPecaComida, &cor2) == TAB_CondRetOK) {
		if (cor == cor2) {
			printf("\nEsta posicao contem uma peca pertencente ao mesmo jogador!\n");
			return 0;
		}
	}

	qtdMovLinha = linha2 - linha;
	qtdMovColuna = coluna2 - coluna;

	PEC_ObterTipoPeca(pPeca, &pTipoPeca);

	TPC_ConferirMovimento(pTipoPeca, qtdMovLinha, qtdMovColuna, &movValido);

	// Movimento encontrado na lista de movimentos da peca
	if (movValido == 1) {
		TPC_ObterNome(pTipoPeca, &nomeTipoPeca);

		// Tratamento especia para a peca Peao
		if (strcmp(nomeTipoPeca, "PeaoP") == 0 || strcmp(nomeTipoPeca, "PeaoB") == 0) {
			if (qtdMovColuna == -1 || qtdMovColuna == 1) {
				if (TAB_ObterPeca(simulacao.pTab, linha2, coluna2, (void**)&pPecaComida, &cor2) == TAB_CondRetOK) {
					TAB_MoverPeca(simulacao.pTab, linha, coluna, linha2, coluna2, (void**)&pPecaComida, &jogadorComido);
					return 1;
				} else {
					printf("Movimento invalido - tentativa de mover peao na diagonal sem comer peca.\n");
					return 0;
				}
			} else {
				if (TAB_ObterPeca(simulacao.pTab, linha2, coluna2, (void**)&pPecaComida, &cor2) == TAB_CondRetOK) {
					printf("Movimento invalido - tentativa de comer peca com movimento vertical.\n");
					return 0;
				} 
			}
		}

		if (TAB_ObterPeca(simulacao.pTab, linha2, coluna2, (void**)&pPecaComida, &cor2) == TAB_CondRetOK) {
			TAB_MoverPeca(simulacao.pTab, linha, coluna, linha2, coluna2, (void**)&pPecaComida, &jogadorComido);
			PEC_ObterTipoPeca( pPecaComida , &pTipoPeca );
			TPC_ObterNome(pTipoPeca, &nomeTipoPeca);
			printf("Peca comeu peca %s\n", nomeTipoPeca);
		} else {
			TAB_MoverPeca(simulacao.pTab, linha, coluna, linha2, coluna2, (void**)&pPecaComida, &jogadorComido);
		}
		return 1;
	}
}

/***********************************************************************
*
*  $FC Função: JGO - Le arquivo de configuracao
*
*  $ED Descrição da função
*     Lê o arquivo de configuração no caminho dado, carregando seus dados
*       no tabuleiro.
*
*  $FV Valor retornado
*     1 se leu com sucesso
*     0 caso contrário
*
***********************************************************************/

static int JGO_CarregarArquivoMovimentos(char * path) {
	char auxString[200], cor;
	int i, j;
    PEC_tpJogador jogador;
	FILE *fp;
	TPC_tppTipoPeca pTipo;
	PEC_tppPeca pPeca;

	fp = fopen(path, "r");
	if (!fp) {
		printf("\nPath invalido.\n\n");
		return 0;
	}

	while (fscanf(fp, " %s", auxString) == 1) {
		if (strcmp(auxString, "TIPO") == 0) {
			fscanf(fp, " %[^\n]", auxString);
			if (TPC_CriarTipoPeca(&pTipo, auxString) != TPC_CondRetOK) {
				printf("Faltou memória.");
				JGO_Sair(1);
			}
			LIS_InserirNo(simulacao.pListaTipos, (void *)pTipo);

		}
		else if (strcmp(auxString, "MOV") == 0) {
			fscanf(fp, " %d %d", &i, &j);
			if (TPC_AdicionarMovimento(pTipo, i, j) == TPC_CondRetFaltouMemoria) {
				printf("Faltou memória.");
				JGO_Sair(1);
			}

		}
		else if (strcmp(auxString, "TABULEIRO") == 0) {
			while (fscanf(fp, " %s %c %d %c", &auxString, &cor, &i, &j) == 4) {
				pTipo = JGO_ProcurarTipo(auxString);
                jogador = (cor == 'B') ? JOGADOR_BRANCO : JOGADOR_PRETO;
				if (!pTipo)
					continue;
				if (PEC_CriarPeca(&pPeca, pTipo, jogador) != PEC_CondRetOK) {
					printf("Faltou memória.");
					JGO_Sair(1);
				}
                TAB_InserirPeca(simulacao.pTab, pPeca, i, j, jogador);
			}
		}
	}

	fclose(fp);
	return 1;
}