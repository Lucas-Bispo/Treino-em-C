#include<stdio.h>
#include<stdlib.h> //teste

struct item{//Aenas para guardar a variável inteira.
    int cod;
};
typedef struct item Item;//redefinição de tipo

struct node{
    Item item;
    struct node *left;//ponteiro para esquerda
    struct node *right;//ponteiro para a direita.
};
typedef struct node Node;// redefinição do tipo de dado

Node *inicializar(){//inicialização da árvore da raiz 
    return NULL; //retorna ao ponteiro NULL
}
Item itemCreate(int cod){//passagem de valor interiro para estrutura atráves de um função
    Item item;//crio uma estrutura do tipo item e dentro dela existe uma variável que tem um inteiro e vai
    //receber o valor inteiro que vem por parâmentro 
    item.cod = cod;//passagem de valor
    return item; //retorno da estrutura.
}
Node *inserir(Node *root, Item x){//retorna ponteiro mais recur 
    if (root == NULL){//se a raiz da arvore apontar para NULL vai ser criado um no conde esses ponteiros estão 
    //apontando a NULL
        Node *aux = (Node*)malloc(sizeof(Node));// alocação de memória no tamanho de NODE com cast que é conversão 
        aux->item = x;//recebe a estrutura que vem por parâmetro
        aux->left = NULL;//o nó que foi criado tem um ponteiro esquerdo que aponta para Null por conta de ser um nó 
        //que foi criado.
        aux->right = NULL;//a mesma lógica se aplica, por conta de ser o primeiro nó a ser criado tanto o nó que aponta a 
        //esquerda quanto a direita apontaram para NULL.
        return aux;//retornando aux, a raiz será esse ponteiro que está sendo retornado.
    }else{// caso exita uma raiz o elemento que será criado vai se movimentar na árvore de acordo com as regras
    //se for menor que a raiz irá ser movimentado para esquerda se não irá para a direita.
        if(x.cod > root->item.cod){//verificação de valor em relação a raiz 
        //sendo maior ele vai ser movimentado para a direita.
           root->right = inserir(root->right,x);//procedimento de recursão, como eu passo root->direita aponta para NULL ele cai no if, 
           //logo após a árvore é retornada de maneria conpleta pois a recurssão existe justamente pq os ponteiros estão para NULL.
        }else if ( x.cod < root->item.cod){//caso o valor seja seja menor que a raiz o valor será movimentado para esquerda
            root->left = inserir(root->left,x);//chamada de função para que a recursão aconteça, como os ponteiros estão direcionados para NULL
            //ele cai em if e a mágica acontece, o nó é criado e os ponteiros são direcionados pata NULL 
        }
    }
    return root;
}
void print(Node *root){//recursão de impressão, onde se aplica a regra da estrutura de dados, percorre toda a árvore para esquerda
//depois para a direita.
    if(root != NULL){ //como a árvore será sempre diferente de NULL vai imprimir todos os valores a esquerda depois a direita 
    //assim a árvore sempre será impressa ordenada.
        printf("%d ",root->item.cod);//imprime o valor inteiro 
        print(root->left); //chamada para a esquerda
        print(root->right);//chamada para direita 
    }
}
void FFree(Node *root){//recursão, chamada para limpar memória  
    if (root != NULL){//sempre será diferente de NULL 
    FFree(root->right);//chamada de recursão 
    FFree(root->left);//chamada de recursão 
    free(root);//liberação de memória 
    }
}
Node *Searrch(Node *root,int cod){//função de busca, com recursão.
    if(root != NULL){//se for diferente de NULL,o objetivo é encontrar NULL pois são os ponteiros finais.
        if (root->item.cod == cod){//comparação para saber de o valor que vem por parâmetro 
            return root; //no caso a raiz, 
        }
        else//se a raiz não for igual fazemos a recursão 
        {
            if(cod > root->item.cod){//caso seja maior que raiz fazemos recursão na direita
                return Searrch(root->right,cod);// a recursão será feita até que encontre o valor e 
            }
            else//se o valor for menor se faz a recursão pela esquer e passará pelo if e quando o valor não for igual
            {// então cai no else que que faz o procedimento de comparação para fazer a recursão
                return Searrch(root->left,cod);//recursão para esquerda.
            }
        }
    }
    return NULL;
}
Node *Menorno(Node *root){// esta função é criada para ser usada na função de remoção pois 
//caso a raiz seja removida, a regra da estrutura é pegar o menor elemento da sub árvore da direta.
    if (root != NULL)// por já existir uma árvore, que o parâmetro que será passado é root->direita
    {//então fazemos a declaração de uma variável auxiliar dizemos que ela receberá o enderço de root->direita.
        Node *aux = root;//assim eu percorro toda a árvore 
        while (aux->left != NULL)//para a esquerda buscando o menor elemento
        {
            aux = aux->left;//elemento encontrado eu passo para aux
        }//e esse aux é retornado pela função.
    }
    return NULL;
}
Node *treeRemove(Node *root, int cod){//passagem da raiz mais o número que irá ser deletado
    if(root != NULL)//será diferente pois os ponteiros do nó apontaram para NULL caso sejam os ultimos
    {//primeira condição +
        if(cod > root->item.cod)//comparando a raiz para saber se deve ir para 
        {//indo para a direita e realizando a recursão
            root->right = treeRemove(root->right,cod);//ralizando a recursão
        }
        else if (cod < root->item.cod)//verificaçao para realizar recursão para esquerda.
        {
            root->left = treeRemove(root->left,cod);//chamada de função e realização de recursão
        }
        else{
            if (root->left == NULL && root->right ==NULL)//verificação para liberar memória 
            {//se os ponteiros tiverem apontando para NULL
                free(root);//liberação de de nó
                return NULL;
            }else if (root->left == NULL && root->right != NULL)//verificação caso para nós tenham apenas um ponteiro nulo 
            {
                Node *aux = root->right;//precisa passar o endereço de dos ponteiros a direita para a variável auxiar
                free(root);
                return aux;
            }else if (root->left != NULL && root->right == NULL)//verificação caso os nós tenham um ponteiro nulo
            {
                Node *aux = root->left;//recebe o endereço de onde o ponteiro a esquerda está apontadno  
                free(root);//é liberada a memória
                return aux;// o endereço é retornado assim não se perde a árvore na memória
            }
            else{//o truque de remover a raiz 
                Node *aux = Menorno(root->right);//é pegar o menor elemento da sub-árvore direito,
                Item itemaux = aux->item;//fazer um cópia e passar para raiz e da um free onde aquele valor 
                root = treeRemove(root, itemaux.cod);//foi encontrado
                root->item = itemaux;//passagem do valor que foi copiado para a raiz, 
                //assim supostamente a raiz foi removida quando o que ouve foi um troca valores.
            }
           
        }
        return root;
    }  
    return NULL;
}
int main() {
    Node *root = inicializar();//chamada de função para inicializar a árvore vazia
    root = inserir(root,itemCreate(10));//chamada de fução para inserir um elemento porém a função que está sendo chamada dentro de inserir
    //é do tipo struct que armazena o valor inteiro e retornar o estrutura.
    root = inserir(root,itemCreate(15));
    root = inserir(root,itemCreate(20));
    root = inserir(root,itemCreate(12));
    root = inserir(root,itemCreate(5));
    Node *tmp = Searrch(root,12);//verificação de busca onde é retornado o ponteiro para que seja acionado as funções de escrever na tela
    if (tmp == NULL){
        printf("Elemento nao encontrado!\n");
    }else{
        printf("Elemento encontrado\n");
    }
    printf("Antes de treeRemover.\n");
    print(root);//chamada de funçao para imprimir a árvore 
    root = treeRemove(root,13); //chamada para remover elementos da árvore 
    printf("Depois de remover\n");
    print(root);//imprimir árvore

    printf("\n");
    FFree(root);//liberação de memória 
    return 0;
}
