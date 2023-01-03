//tipo baseado na árvore
typedef struct no arvore;

//Estrutura
struct no{
  //dados básicos
  int codigo;
  
  //Ponteiros
  arvore *esquerda;
  arvore *direita;
};

//Protótipo
void menu();
arvore* criarNulo();
arvore* criarNo(int cod);
arvore* inserirNo(arvore *arv, int cod);
void percorrerIn(arvore *arv);
void percorrerPre(arvore *arv);
void percorrerPos(arvore *arv);
void pesquisarNo(arvore **no, arvore **pai, int cod);
int gerarCodigoRandomico();
int solicitarCodigo();
arvore* deletarNo(arvore *pai, int x);
arvore* acharMinimo(arvore *pai);
