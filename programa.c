#include <locale.h>
<<<<<<< Updated upstream
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//variaveis globais
int login=0,nivelacesso=0;

//prototipos
int Verificarlogin();
int Login();
void Menu();
int cadastrarItem();
>>>>>>> Stashed changes

//estrutura global
struct produto{
	char nome[50];
	int codigo, qtd;
	float preco;
	bool generico;
};
struct produto produtos[100];
int contador = 0;

<<<<<<< Updated upstream

int main(){
=======
void main(){
	setlocale(LC_ALL, "Portuguese");
	if(login!=1){
		nivelacesso=Login();
	}
>>>>>>> Stashed changes
	
	setlocale(LC_ALL,"Portuguese");
	
	//teste
	return 0;
}

<<<<<<< Updated upstream
//teste
//teste
=======

void Menu(){
	int op;
	//ao final de todas as funções, o main ou Menu devem ser chamados para dar continuidade ao programa
	if(nivelacesso==1){
		//menu para o admin
		printf("\n----- MENU ADMINISTRATIVO ------\n");
		printf("--------------------------------\n");
		printf("1. Cadastrar cliente\n2. Cadastrar produto\n3. Registrar venda\n4. Consulta\n5. Sair do programa\n");
		//em consulta adicionar listagem de clientes e produtos, pesquisa de ambos e produtos em baixa qtd
		printf("--------------------------------\n");
		printf("Escolha uma opção: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				printf("cadastro de clientes");
				break;
			case 2:
				cadastrarItem();
				Menu();
				break;
			case 3:
				printf("registrar venda");
				break;
			case 4:
				printf("consulta");
				break;
			case 5:
				printf("\nSaindo...");sleep(1);printf(".....");
				break;
		}
	}else{
		//menu para o vendedor
		printf("\n------- MENU DE VENDAS ---------\n");
		printf("--------------------------------\n");
		printf("1. Registrar venda\n2. Consulta\n3. Sair do programa\n");
		//em consulta adicionar listagem de clientes e produtos, pesquisa de ambos e produtos em baixa qtd
		printf("--------------------------------\n");
		printf("Escolha uma opção: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				printf("registrar venda");
				break;
			case 2:
				printf("consulta");
				break;
			case 3:
				printf("\nSaindo...");sleep(1);printf(".....");
				break;
		}
	}
}


int Login(){
	int nivel;
	nivel = Verificarlogin();
	if(nivel==1){
		printf("Permissão de admin concedida\n");
		login=1;
	}else if(nivel==2){
		printf("Permissão de vendedor concedida\n");
		login=1;
	}else{
		printf("Acesso negado");
		//fecha o programa
		return 0;
	}
	return nivel;	
}



int Verificarlogin() {
    FILE *arquivo;
    char linha[200];
    char *registro1, *registro2;
    int numeroLinha = 1;

    // Abre o arquivo para leitura
    arquivo = fopen("senhas.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        return;
    }
    
    int tentativas=0;
    while(tentativas<3){
		
	    char usu[20];
		char senha[10];
		
		printf("Digite o usuario: ");
		fgets(usu,sizeof(usu),stdin);
		usu[strcspn(usu,"\n")] =0;
		printf("Digite a senha: ");
		fgets(senha,sizeof(senha),stdin);
		senha[strcspn(senha,"\n")]=0;

    	// Lê linha por linha do arquivo
    		//reinicia a leitura do arquivo, permitindo as tentativas
    		rewind(arquivo);
    	while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        	// Remove a quebra de linha
        	
        	linha[strcspn(linha, "\n")] = 0;

        	// Separa os registros usando strtok
        	registro1 = strtok(linha, ";");
        	registro2 = strtok(NULL, ";"); // continua de onde parou o ponteiro

        	if(strcmp(registro1,usu)==0 && strcmp(registro2,senha)==0){
        		printf("Login autenticado\n");
        	
    	    	int nivel = atoi(strtok(NULL,";"));
        		
	        	if(nivel==1){
	        		return 1;	
				}else{
					return 2;
				}	
			}			
    	}
    	printf("\nDados incorretos\n");
		
    	printf("--------------------\n");
		tentativas++;
	}

    // Fecha o arquivo
    fclose(arquivo);
    return 0;
}

int cadastrarItem(){
	
	char temp;

    if(contador >= 100){
        printf("Limite de produtos atingido!\n");
        return 0;
    } 
	
    printf("Digite o nome do produto: ");
    while (getchar() != '\n'); // Limpa o buffer
    fgets(produtos[contador].nome, sizeof(produtos[contador].nome), stdin);
    produtos[contador].nome[strcspn(produtos[contador].nome, "\n")] = '\0';
    
    printf("Digite o código do produto: ");
    scanf("%d",&produtos[contador].codigo);
    
    printf("Digite o preço do produto: ");
    scanf("%f",&produtos[contador].preco);
    
    printf("Digite a quantidade do produto: ");
    scanf("%d",&produtos[contador].qtd);
    
    printf("Ele é genérico?[s/n]: ");
    while (getchar() != '\n'); 
    scanf("%c",&temp);
    
    if(temp == 's' || temp == 'S'){
        produtos[contador].generico = true;
    } else {
        produtos[contador].generico = false;
    }
    
    contador++; 
    printf("Produto cadastrado com sucesso!\n");
    
    return 1;
}












>>>>>>> Stashed changes
