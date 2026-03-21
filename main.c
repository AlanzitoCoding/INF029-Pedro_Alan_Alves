#include <stdio.h>

int main(){
    unsigned int opc, qntLivros = 0, listaLivros[3];
    

    do{
        printf("========== Menu ==========\n\n");
        printf("1 - Cadastrar Livro\n2 - Listar Livros\n3 - Editar Livro\n4 - Excluir Livro\n0 - Sair\nOpção: ");
        scanf("%d", &opc);

        switch(opc){
            case 1:{
                if(qntLivros == 3){
                    printf("Limite de livros atingidos!");
                    break;
                }
                printf("========== Cadastrar Livro ==========\n\n");
                printf("Digite o ano de criação do livro: ");
                scanf("%d", &listaLivros[qntLivros]);
                break;
            }
            case 2:{
                if(qntLivros == 0){
                    printf("Lista vazia!");
                    break;
                }

                printf("========== Cadastrar Livro ==========\n\n");
                for(int i = 0; i < qntLivros; i++){
                    printf("Ano: %d\n", listaLivros[i]);
                }
                break;
            }
        }
    }while(opc != 0);

    return 0;
}