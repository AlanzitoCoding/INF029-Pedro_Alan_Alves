// Louvado seja o Senhor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 3

typedef struct{
    char nome[100];
    char autor[100];
    int anoLancamento;
} Livro;

int main(){
    unsigned int opc, qntLivros = 0;
    Livro listaLivros[TAM];    

    do{
        printf("\n\n========== Menu ==========\n\n");
        printf("1 - Cadastrar Livro\n2 - Listar Livros\n3 - Editar Livro\n4 - Excluir Livro\n0 - Sair\nOpção: ");
        scanf("%d", &opc);

        switch(opc){
            case 1:{
                if(qntLivros == TAM){
                    printf("Limite de livros atingidos!");
                    break;
                }

                getchar();

                printf("\n\n========== Cadastrar Livro ==========\n\n");
                printf("Digite o nome do livro: ");
                fgets(listaLivros[qntLivros].nome, 100, stdin);

                printf("Digite o autor do livro: ");
                fgets(listaLivros[qntLivros].autor, 100, stdin);

                printf("Digite o ano de criação do livro: ");
                scanf("%d", &listaLivros[qntLivros].anoLancamento);
                qntLivros++;
                break;
            }
            case 2:{
                if(qntLivros == 0){
                    printf("\n\nLista vazia!\n\n");
                    break;
                }

                printf("\n\n========== Lista dos Livros ==========\n\n");
                for(int i = 0; i < qntLivros; i++){
                    printf("Livro %d:\n\nNome: %sAutor: %sAno de Lançamento: %d\n\n", i+1, listaLivros[i].nome, listaLivros[i].autor, listaLivros[i].anoLancamento);
                }
                break;
            }
            case 3:{
                if(qntLivros == 0){
                    printf("\n\nLista vazia!\n\n");
                    break;
                }

                getchar();

                char busca[100];

                printf("\n\n========== Editar Livro ==========\n\n");
                printf("Digite o nome do livro que deseja editar: ");
                fgets(busca, 100, stdin);

                for(int i = 0; i < qntLivros; i++){
                    if(strcmp(listaLivros[i].nome, busca) == 0){
                        printf("Digite o novo nome do livro: ");
                        fgets(listaLivros[i].nome, 100, stdin);

                        printf("Digite o novo autor do livro: ");
                        fgets(listaLivros[i].autor, 100, stdin);

                        printf("Digite o novo ano de criação do livro: ");
                        scanf("%d", &listaLivros[i].anoLancamento);

                        printf("Livro editado com sucesso!");
                    }
                    else if(strcmp(listaLivros[i].nome, busca) != 0 && i == qntLivros-1){
                        printf("Livro não encontrado!");
                    }

                }
                break;
            }            
            case 4:{
                if(qntLivros == 0){
                    printf("\n\nLista vazia!\n\n");
                    break;
                }

                getchar();

                char busca[100];

                printf("\n\n========== Excluir Livro ==========\n\n");
                printf("Digite o nome do livro que deseja excluir: ");
                fgets(busca, 100, stdin);

                for(int i = 0; i < qntLivros; i++){
                    if(strcmp(listaLivros[i].nome, busca) == 0){
                        if(qntLivros > 1){
                            for(int i = 0; i < qntLivros-1; i++){
                                strcpy(listaLivros[i].nome, listaLivros[i+1].nome); 
                                strcpy(listaLivros[i].autor, listaLivros[i+1].autor); 
                                listaLivros[i].anoLancamento = listaLivros[i+1].anoLancamento; 

                                printf("Livro excluído com sucesso!");
                            }
                        }

                        qntLivros--;
                    }
                    else if(strcmp(listaLivros[i].nome, busca) != 0 && i == qntLivros-1){
                        printf("Livro não encontrado!");
                    }

                }
                break;
            }            
        }
    }while(opc != 0);

    return 0;
}