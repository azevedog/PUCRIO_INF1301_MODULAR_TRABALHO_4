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
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
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

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetListaInexistente ,
               /* Lista especificada não existe */

         LIS_CondRetNoCorrenteUltimo ,
               /* Nó corrente já é o último da lista */

         LIS_CondRetNoCorrentePrimeiro ,
               /* Nó corrente já é o primeiro da lista */

         LIS_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de lista */

		 LIS_CondRetNaoAchou
				/* Nao achou o no buscado */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     id      - string identificador da lista
*     lista   - se a função executar corretamente, contém o ponteiro 
*               para a lista criada. Caso contrário, a lista é nula.
*
*  $FV Valor retornado
*     LIS_CondRetOK                  - destruiu sem problemas
*     LIS_CondRetFaltouMemoria       - faltou memória 
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(char * id, LIS_tppLista *lista);

/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK                  - destruiu sem problemas
*     LIS_CondRetListaInexistente    - lista não existe
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista );

   /***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Se a lista anteriormente estava vazia, agora contém um elemento,
*         com valor pValor. O nó corrente torna-se este elemento.
*       Do contrário, a lista agora contém um elemento a mais, sendo este
*         inserido imediatamente antes do nó corrente. O nó corrente não
*         é modificado.
*     Se LIS_CondRetFaltouMemoria:
*       A lista não é modificada.
*
***********************************************************************/
   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista , void * pValor ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Inserir nó
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirNo( LIS_tppLista pLista , void* pValor );


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
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
*     LIS_CondRetOK
*     LIS_CondRetListaInexistente 
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirNoCorrente( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter a id da lista
*
*  $ED Descrição da função
*     Obtem a identificação da lista contida na sua cabeça
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*     id*  - ponteiro onde se quer guardar o valor do identificador da lista
* 
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaInexistente 
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterIdLista(LIS_tppLista pLista, char* id);

/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

   
/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
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
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     CondRetOK                   - Alteração bem sucedida
*     CondRetListaVazia           - se a lista está vazia
*     LIS_CondRetListaInexistente - se a lista não existe
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterNo(LIS_tppLista pLista, void** valor);

/***********************************************************************
*
*  $FC Função: LIS  &Alterar No Corrente
*
*  $ED Descrição da função
*     Altera o conteúdo do nó corrente da lista para o valor passado
*
*  $EP Parâmetros
*     pLista     - ponteiro para a lista onde se quer alterar o valor
*     pValorNovo - ponteiro para o valor pelo qual deve ser substituido
*
*  $FV Valor retornado
*     CondRetOK                   - Alteração bem sucedida
*     CondRetListaVazia           - se a lista está vazia
*     LIS_CondRetListaInexistente - se a lista não existe
*
***********************************************************************/

   LIS_tpCondRet LIS_AlterarNoCorrente(LIS_tppLista pLista, void* pValorNovo);

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*     CondRetOK                   - Alteração bem sucedida
*     CondRetListaVazia           - se a lista está vazia
*     LIS_CondRetListaInexistente - se a lista não existe
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente em 1 
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK                 - Movimentação bem sucedida
*     CondRetNoCorrenteUltimo   - Nó corrente é o último
*     CondRetListaVazia         - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_IrProx(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Voltar elemento
*
*  $ED Descrição da função
*     Volta o elemento corrente em 1 
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK                 - Movimentação bem sucedida
*     CondRetNoCorrentePrimeiro - Nó corrente é o primeiro
*     CondRetListaVazia         - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_IrAnt(LIS_tppLista pLista);


/***********************************************************************
*
*  $FC Função: LIS  &Obter numero de elementos
*
*  $ED Descrição da função
*     Obtem o numero de elementos da lista 
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElementos  - ponteiro para retornar o numero de elementos
*
*  $FV Valor retornado
*     CondRetOK                 - Movimentação bem sucedida
*     CondRetListaInexistente   - Lista nao existe
*
***********************************************************************/
   LIS_tpCondRet LIS_ObterNumElementos(LIS_tppLista pLista, int *numElementos);

// Esvaziar lista

   void LIS_EsvaziarLista(LIS_tppLista pLista);

#ifdef _DEBUG

/***********************************************************************
*
*  $FC FunÁ„o: LIS Verificar estrutura
*
*  $ED DescriÁ„o da funÁ„o
*  Verifica a estrutura, contabilizando o total de erros encontrados.
*
*  $EP Parametros
*     $P pLista - ponteiro para a lista.
*     $P numErros - ponteiro para inteiro que recebera o total de erros.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*
***********************************************************************/

   LIS_tpCondRet LIS_VerificarEstrutura( LIS_tppLista pLista, int * numErros ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS Deturpar estrutura
*
*  $ED DescriÁ„o da funÁ„o
*  Deturpa a estrutura, de acordo com o comando fornecido.
*
*  $EP Par‚metros
*     $P pLista - ponteiro para a lista.
*     $P pos - posição do elemento corrente do tabuleiro na lista.
*     $P flag - tipo de deturpacao, pode ser:
*		1 - elimina o elemento corrente da estrutura escolhida.
*		2 - atribui NULL ao ponteiro para uma casa sucessora.
*		3 - atribui NULL ao ponteiro para uma casa predecessora.
*		4 - atribui lixo ao ponteiro para a referência a uma casa sucessora.
*		5 - atribui lixo ao ponteiro para a referência a uma casa predecessora.
*		6 - atribui NULL ao ponteiro para o conteúdo da casa.
*		7 - altera o tipo de estrutura apontado na casa.
*		8 - destaca casa da matriz sem liberá-lo com free.
*		9 - atribui NULL ao ponteiro corrente	
*
*  $FV Valor retornado
*     LIS_CondRetOK
*
***********************************************************************/

   LIS_tpCondRet LIS_Deturpar( LIS_tppLista pLista, int cmd, pos );

#endif

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
