#include <locale.h>
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
void salvarProdutos();

//estrutura global
struct produto{
	char nome[50];
	int codigo, qtd;
	float preco;
	bool generico, remedio;
};
struct produto produtos[100];
int contador = 0;

void main(){
	setlocale(LC_ALL, "Portuguese");
	if(login!=1){
		nivelacesso=Login();
	}
	
	if(nivelacesso!=0 && login==1){
		//chamar menu e nele analisar o nivel de acesso
		sleep(1);
		Menu();
	}
}


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
    int codigoTemp, qtdTemp, i;
    float precoTemp;
    
    if(contador >= 100){
        printf("Limite de produtos atingido!\n");
        return 0;
    }
    

    // Validação do nome do produto
    do {
    	while (getchar() != '\n'); 
        printf("Digite o nome do produto: ");
        fgets(produtos[contador].nome, sizeof(produtos[contador].nome), stdin);
        produtos[contador].nome[strcspn(produtos[contador].nome, "\n")] = '\0';
        
        if(strlen(produtos[contador].nome) == 0){
            printf("Erro: Nome do produto não pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
    
    // Validação do código do produto
    do {
        printf("Digite o código do produto (número positivo): ");
        if(scanf("%d", &codigoTemp) != 1) {
            printf("Erro: Digite apenas números!\n");
            while (getchar() != '\n'); 
            codigoTemp = -1; //caso o scanf falhe, codigoTemp valerá um valor anterior, então aqui ele é declarado como -1 pra forçar o erro e ser lido novamente
        } else if(codigoTemp <= 0) {
            printf("Erro: Código deve ser um número positivo!\n");
        } else {
            // Verifica se o código já existe
            int codigoExiste = 0;
            for(i = 0; i < contador; i++){
                if(produtos[i].codigo == codigoTemp){
                    printf("Erro: Este código já existe! Digite outro código.\n");
                    codigoExiste = 1;
                    break;
                }
            }
            if(!codigoExiste) {
                produtos[contador].codigo = codigoTemp;
                break;
            }
        }
    } while(1);
    
    // Validação do preço
    do {
        printf("Digite o preço do produto (valor positivo): R$ ");
        if(scanf("%f", &precoTemp) != 1) {
            printf("Erro: Digite um número válido!\n");
            while (getchar() != '\n'); 
        } else if(precoTemp <= 0) {
            printf("Erro: Preço deve ser maior que zero!\n");
        } else {
            produtos[contador].preco = precoTemp;
            break;
        }
    } while(1);
    
    // Validação da quantidade
    do {
        printf("Digite a quantidade do produto (número não negativo): ");
        if(scanf("%d", &qtdTemp) != 1) {
            printf("Erro: Digite apenas números!\n");
            while (getchar() != '\n'); 
        } else if(qtdTemp < 0) {
            printf("Erro: Quantidade não pode ser negativa!\n");
        } else {
            produtos[contador].qtd = qtdTemp;
            break;
        }
    } while(1);
    
    // Validação se é genérico
    do {
        printf("Ele é genérico? [s/n]: ");
        while (getchar() != '\n'); 
        scanf("%c", &temp);
        
        if(temp == 's' || temp == 'S'){
            produtos[contador].generico = true;
            break;
        } else if(temp == 'n' || temp == 'N'){
            produtos[contador].generico = false;
            break;
        } else {
            printf("Erro: Digite apenas 's' para sim ou 'n' para não!\n");
        }
    } while(1);
    
    // Validação se é remedio ou outro tipo de produto
    do {
        printf("É um remédio? [s/n]: ");
        while (getchar() != '\n'); 
        scanf("%c", &temp);
        
        if(temp == 's' || temp == 'S'){
            produtos[contador].generico = true;
            break;
        } else if(temp == 'n' || temp == 'N'){
            produtos[contador].generico = false;
            break;
        } else {
            printf("Erro: Digite apenas 's' para sim ou 'n' para não!\n");
        }
    } while(1);
    
    contador++; 
    salvarProdutos();
    printf("\nProduto cadastrado com sucesso!\n");
	system("pause");
	system("cls");
    return 1;
}

void salvarProdutos(){
    FILE *arquivo;
    
    int i;
    
    arquivo = fopen("produtos.txt", "a");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo para salvar produtos!\n");
        return;
    }
    
    for(i = 0; i < contador; i++){
        fprintf(arquivo, "%s;%d;%.2f;%d;%d;%d\n", 
                produtos[i].nome, 
                produtos[i].codigo, 
                produtos[i].preco, 
                produtos[i].qtd, 
                produtos[i].remedio ? 1 : 0,
                produtos[i].generico ? 1 : 0);
    }
    
    fclose(arquivo);
}	

