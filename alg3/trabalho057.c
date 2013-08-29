#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct Arvore{
        char letra;//letra do nodo
        char palavra[50];//caso o nodo seja o final de uma palavra a mesma ser� guardada aqui
        int verificador;//verifica se ha uma palavra no nodo
        struct Arvore *let[27],*pai;//*let[] � um ponteiro com 27 letras ou seja da posi��o de 1 � 26 s�o as letras do alfabeto e a posi��o 27 uma letra acentuada.
}Arvore;

int RetornaD(char c){//retorna o valor da posicao da letra no vetor
        int d;
        c=tolower(c);
        d=(int) c;
        d=d-97;
        if(d<0)//palavras que tem acento possuem valor negativo nessa conta por isso se joga para a ultima posicao depois da letra z
           d=26;
        return d;
}r


void CriarArvore(Arvore **no,char *arquivo)//SOYOSOSOSOS
{
      Arvore *raiz;
      int i,k,d;
      char c,f,palavra[50];
      FILE *fp;
      k=0;
      for(i=0;i<50;i++)
          palavra[i]='\0';//zerando a string palavra que servira para armezenar as palavras nos nodo.
      fp=fopen(arquivo,"r");//abre o arquivo apontado em *arquivo
      if (!fp)//caso o arquivo nao possa ser aberto imprime essa mensagem
          printf ("Erro na abertura do arquivo.\n");
      else{
           c=fgetc(fp);//pega o caractere apontado por fp
           (*no)=(Arvore *)malloc(sizeof(Arvore));//cria o no raiz
           raiz=(*no);//define o no como no raiz
           while(!feof(fp)){//enquanto n�o for o fim do arquivo ele fica dentro do la�o    
                    while(c!='\n'){ //pega o caracterer que esta na posicao indicada por fp e enquanto ele n�o for nova linha continua pegando
                          d=RetornaD(c);//pega a posicao do vetor
                          if((*no)->let[d]==NULL){//verifica se o nodo existe se nao existir cria um novo
                              (*no)->let[d]=(Arvore *)malloc(sizeof(Arvore));//cria nodo
                              (*no)->let[d]->letra=c;//coloca a letra no nodo
                              (*no)->let[d]->verificador=0;//coloca ele sem palavra dentro
                              (*no)->let[d]->pai=(*no);//aponta seu pai
                          }
                          palavra[k]=c;//pega o caractere correspondende e coloca na string
                          (*no)=(*no)->let[d];//vai para o nodo apontado por d
                          c=fgetc(fp);//pega o caractere apontado por fp
                          k++;//incrementa o k para a string palavra
                    }
                    strcpy((*no)->palavra,palavra);//quando sai do la�o anterior ele copia a palavra no ultimo nodo 
                    for(i=0;i<50;i++)//zerando a string palavra que servira para armezenar as palavras nos nodo.
                           palavra[i]='\0';
                    (*no)->verificador=1;//coloca o verificador para dizer que ele tem uma palavra dentro
                    (*no)=raiz;//volta para a raiz
                    c=getc(fp);//pega um novo caracter
                    k=0;//zera o k para a string palavra
           }
      }
      (*no)=raiz;//volta para a raiz                  
      fclose(fp);//fecha o arquivo apontado por fp
}

int AcharFilho(Arvore *no,int i){//Fun��o Para Achar o filho n�o nulo de um n� e retorna essa posicao
     while(no->let[i]==NULL && i<27)
               i++;
     return i;
}

int palavra(Arvore *no,int opc){
        int i;
        if(opc > 0 && no!=NULL){

            if(no->verificador==1){
                printf("--%s\n",no->palavra);
                opc--;
            }
            i=AcharFilho(no,0);
            if(i<27)
               opc=palavra(no->let[i],opc);  
            i=AcharFilho(no,i+1);
            if(i>=27)
                no=no->pai;
            else if(opc > 0)
               opc=palavra(no->let[i],opc);
        }
        return(opc);   
}


void ProcuraArvore(Arvore *no,char *num){
     Arvore *aux,*raiz;
     int opc,d,k=-1,cont,i=0;
     opc=atoi(num);
     char c,plv[50];
     aux=no;
     printf("-----------SISTEMA DE PALAVRAS-----------\nSe quiser sair do programa pressione esc\n");
     system("stty echo raw");
     c = getchar();
     system("stty echo -raw");
     printf("\n\n");
     while(c!=27){
	   if(c!=91){
              d=RetornaD(c);
	      k++;
              plv[k]=c;
              if(aux->let[d]!=NULL){
                 aux=aux->let[d];
                 raiz=aux;
              }
	   }
	   else if (c==91){
		if(aux->pai!=NULL){
	           aux=aux->pai;
	           raiz=aux;
		}
                plv[k]='\0';
                k--;
	   }
	   
           if(aux!=NULL)
              cont=palavra(aux,opc);
	   printf("\n%s",plv);
           system("stty echo raw");
	   c = getchar();
           system("stty echo -raw");
	   printf("\n\n");
           aux=raiz;
     }
     printf("\n");
}



int main(int argc, char *argv[]){
    Arvore *no=NULL;
    CriarArvore(&no,argv[1]);
    ProcuraArvore(no,argv[2]);
}
