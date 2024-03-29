#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
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
*			mcs - Maria Carolina Santos
*			gbha - Gustavo Azevedo
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  8 	  mcs	15/dez/2016	mudan�as para t4
*	  7		  fpf	01/out/2016	Altera��o das fun��es para somente retornar tpCondRet
*     6       mmq   23/set/2016 adaptar para a utilizacao na aplicacao "Juiz de Xadrez"
*     5       mmq   11/set/2016 alterar a fun��o LIS_ProcuraValor
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( LISTA_OWN )
#define LISTA_EXT
#else
#define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

typedef enum {

	LIS_CondRetOK ,
	/* Concluiu corretamente */

	LIS_CondRetNaoAchou ,
	/* N�o encontrou o valor procurado */

	LIS_CondRetListaVazia ,
	/* A lista n�o cont�m elementos */

	LIS_CondRetNaoExiste ,
	/* A lista n�o existe */

	LIS_CondRetFimLista ,
	/* Foi atingido o fim de lista */

	LIS_CondRetOrigemLista ,
	/* Foi atingido o fim de lista */

	LIS_CondRetFaltouMemoria
	/* Faltou mem�ria ao tentar criar um elemento de lista */

} LIS_tpCondRet ;


#ifdef _DEBUG
tpElemLista * LIS_RetornaSucessor( LIS_tppLista pLista );
tpElemLista * LIS_RetornaAntecessor( LIS_tppLista pLista );
tpElemLista * LIS_RetornaCorrente( LIS_tppLista pLista  );
int LIS_VerificaCorrenteNull( LIS_tppLista pLista);
int LIS_QtdNos(LIS_tppLista pLista);
int LIS_OrigemNula(LIS_tppLista pLista);
void LIS_AlteraSucessor( LIS_tppLista pLista );
void LIS_AlteraPredecessor( LIS_tppLista pLista );
void LIS_AtribuiLixoSucessor( LIS_tppLista pLista );
void LIS_AtribuiLixoPredecessor( LIS_tppLista pLista );

#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $AE Assertivas de entrada
*	  - id tem que ser uma string de tamanho menor ou igual a quatro
*	  - excluir valor tem que tratar da libera��o de memoria do valor
*		contido no elemento
*	  - pLista n�o pode ter memoria alocada
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*	  - pLista tem que estar apontada para um lista duplamente encadeada 
*		com cabe�a
*	  
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*	  id			- ponteiro para a string id que identifica a lista.
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*	  pLista		- ponteiro para a lista a ser criada.
*
*  $FV Valor retornado
*     LIS_CondRetOK            - Executou corretamente.
*	  LIS_CondRetFaltouMemoria - Ocorreu algum erro de falta de mem�ria 
*
***********************************************************************/

LIS_tpCondRet LIS_CriarLista(char * id,
							 void  ( * ExcluirValor ) ( void * pDado ), 
							 LIS_tppLista * pLista);

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o identificador da lista
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabe�a
*	  - pId tem que estar preenchido com a identifica��o de pLista
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor identificador da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*	  pId	 - ponteiro para char a ser preenchido
*
*  $FV Valor retornado
*     LIS_CondRetOK - se o elemento corrente existe
*
***********************************************************************/

LIS_tpCondRet LIS_ObterId(LIS_tppLista pLista, char ** pId);

/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabe�a
*	  - pLista possui novo elemento com valor sendo pValor
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

LIS_tpCondRet LIS_InserirElemento( LIS_tppLista pLista ,
                                      void * pValor         ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabe�a
*	  - pValor tem que estar preenchido com o valor do elemento 
*		corrente de pLista
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*	  pValor - ponteiro onde ser� armazenado o valor
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se o elemento corrente existe
*     LIS_CondRetListaVazia - se a lista estiver vazia
*                Pode ocorrer se o valor inserido no elemento for NULL.
*
***********************************************************************/

LIS_tpCondRet LIS_ObterElemento(LIS_tppLista pLista,
								void ** pValor	  ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*	  - elemento corrente de pLista tem de ter sido excluido 
*		e o corrente aponta para o elemento anterior ou proximo
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se o elemento foi excluido
*     LIS_CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o proximo elemento
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*	  - elemento corrente de pLista aponta para o proximo elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o no corrente.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se tiver andado
*     LIS_CondRetListaVazia - se a lista est� vazia
*     LIS_CondRetFimLista   - se encontrou o fim da lista antes de andar
*
***********************************************************************/

LIS_tpCondRet LIS_IrProxElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o n� anterior
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*	  - elemento corrente de pLista aponta para o elemento anterior
*
*  $ED Descri��o da fun��o
*     Retrocede o no corrente.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     LIS_CondRetOK          - se tiver andado
*     LIS_CondRetListaVazia  - se a lista est� vazia
*     LIS_CondRetOrigemLista - se encontrou o in�cio da lista antes de andar
*
***********************************************************************/

LIS_tpCondRet LIS_IrAntElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Andar para o n� inicial
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*	  - elemento corrente de pLista aponta para o primeiro elemento
*
*  $ED Descri��o da fun��o
*     Retrocede o no corrente para o inicial.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se tiver andado para o in�cio
*     LIS_CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

LIS_tpCondRet LIS_AndarInicio(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Fun��o: LIS  &Alterar o valor contido no elemento
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*	  - valor do elemento corrente de pLista aponta para pValor
*
*  $ED Descri��o da fun��o
*     Altera o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser alterada
*	  pValor - ponteiro para o valor a ser inserido
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

LIS_tpCondRet LIS_AlterarElemento(LIS_tppLista pLista,
								  void * pValor		) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $AE Assertivas de entrada
*	  - pLista n�o pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabe�a
*	  - pLista tem de ter sido desalocada na memoria
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser destru�da
*
*  $FV Valor retornado
*     LIS_CondRetOK - destruiu sem problemas
*
***********************************************************************/

LIS_tpCondRet LIS_DestruirLista(LIS_tppLista pLista);

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif