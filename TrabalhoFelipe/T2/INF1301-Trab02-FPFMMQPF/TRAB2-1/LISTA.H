#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs - Arndt Von Staa
*           fpf - Felipe Pessoa de Freitas
*           mmq - Matheus de Mello Queiroz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  7		  fpf	01/out/2016	Alteração das funções para somente retornar tpCondRet
*     6       mmq   23/set/2016 adaptar para a utilizacao na aplicacao "Juiz de Xadrez"
*     5       mmq   11/set/2016 alterar a função LIS_ProcuraValor
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( LISTA_OWN )
#define LISTA_EXT
#else
#define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

typedef enum {

	LIS_CondRetOK ,
	/* Concluiu corretamente */

	LIS_CondRetNaoAchou ,
	/* Não encontrou o valor procurado */

	LIS_CondRetListaVazia ,
	/* A lista não contém elementos */

	LIS_CondRetNaoExiste ,
	/* A lista não existe */

	LIS_CondRetFimLista ,
	/* Foi atingido o fim de lista */

	LIS_CondRetOrigemLista ,
	/* Foi atingido o fim de lista */

	LIS_CondRetFaltouMemoria
	/* Faltou memória ao tentar criar um elemento de lista */

} LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $AE Assertivas de entrada
*	  - id tem que ser uma string de tamanho menor ou igual a quatro
*	  - excluir valor tem que tratar da liberação de memoria do valor
*		contido no elemento
*	  - pLista não pode ter memoria alocada
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*	  - pLista tem que estar apontada para um lista duplamente encadeada 
*		com cabeça
*	  
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*	  id			- ponteiro para a string id que identifica a lista.
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*	  pLista		- ponteiro para a lista a ser criada.
*
*  $FV Valor retornado
*     LIS_CondRetOK            - Executou corretamente.
*	  LIS_CondRetFaltouMemoria - Ocorreu algum erro de falta de memória 
*
***********************************************************************/

LIS_tpCondRet LIS_CriarLista(char * id,
							 void  ( * ExcluirValor ) ( void * pDado ), 
							 LIS_tppLista * pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o identificador da lista
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabeça
*	  - pId tem que estar preenchido com a identificação de pLista
*
*  $ED Descrição da função
*     Obtem a referência para o valor identificador da lista
*
*  $EP Parâmetros
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
*  $FC Função: LIS  &Inserir elemento
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabeça
*	  - pLista possui novo elemento com valor sendo pValor
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
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
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabeça
*	  - pValor tem que estar preenchido com o valor do elemento 
*		corrente de pLista
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*	  pValor - ponteiro onde será armazenado o valor
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
*  $FC Função: LIS  &Excluir elemento
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada 
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*	  - elemento corrente de pLista tem de ter sido excluido 
*		e o corrente aponta para o elemento anterior ou proximo
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se o elemento foi excluido
*     LIS_CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o proximo elemento
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*	  - elemento corrente de pLista aponta para o proximo elemento
*
*  $ED Descrição da função
*     Avança o no corrente.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se tiver andado
*     LIS_CondRetListaVazia - se a lista está vazia
*     LIS_CondRetFimLista   - se encontrou o fim da lista antes de andar
*
***********************************************************************/

LIS_tpCondRet LIS_IrProxElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o nó anterior
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*	  - elemento corrente de pLista aponta para o elemento anterior
*
*  $ED Descrição da função
*     Retrocede o no corrente.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     LIS_CondRetOK          - se tiver andado
*     LIS_CondRetListaVazia  - se a lista está vazia
*     LIS_CondRetOrigemLista - se encontrou o início da lista antes de andar
*
***********************************************************************/

LIS_tpCondRet LIS_IrAntElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Andar para o nó inicial
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*	  - elemento corrente de pLista aponta para o primeiro elemento
*
*  $ED Descrição da função
*     Retrocede o no corrente para o inicial.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     LIS_CondRetOK - se tiver andado para o início
*
***********************************************************************/

LIS_tpCondRet LIS_AndarInicio(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Alterar o valor contido no elemento
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*	  - valor do elemento corrente de pLista aponta para pValor
*
*  $ED Descrição da função
*     Altera o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
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
*  $FC Função: LIS  &Destruir lista
*
*  $AE Assertivas de entrada
*	  - pLista não pode ser null
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*  $AS Assertivas de saida
*	  - valem as assertivas estruturais da lista duplamente encadeada
*		com cabeça
*	  - pLista tem de ter sido desalocada na memoria
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser destruída
*
*  $FV Valor retornado
*     LIS_CondRetOK - destruiu sem problemas
*
***********************************************************************/

LIS_tpCondRet LIS_DestruirLista(LIS_tppLista pLista);

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif