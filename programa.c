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
void salvarProdutos(char nome[50], int codigo, int qtd, float preco, bool generico, bool remedio);

//estrutura global
struct produto{
	char nome[50];
	int codigo, qtd;
	float preco;
	bool generico, remedio;
};
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
	
    int i;
    char temp;
    struct produto produtos;
    // Valida��o do nome do produto
    do {
    	while (getchar() != '\n'); 
        printf("Digite o nome do produto: ");
        fgets(produtos.nome, sizeof(produtos.nome), stdin);
        produtos.nome[strcspn(produtos.nome, "\n")] = '\0';
        
        if(strlen(produtos.nome) == 0){
            printf("Erro: Nome do produto n�o pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
    
    // Valida��o do c�digo do produto
    do {
        printf("Digite o c�digo do produto (n�mero positivo): ");
        if(scanf("%d", &produtos.codigo) != 1) {
            printf("Erro: Digite apenas n�meros!\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue; // Volta para o in�cio do la�o
        }
        
        if(produtos.codigo <= 0) {
            printf("Erro: C�digo deve ser um n�mero positivo!\n");
            continue; // Volta para o in�cio do la�o
        }

        // ---- In�cio da valida��o de duplicidade embutida ----
        FILE *arquivo;
        int codigoExiste = 0;
        
        arquivo = fopen("produtos.txt", "r");
        
        // S� executa a verifica��o se o arquivo j� existir
        if (arquivo != NULL) {
            char linha[200];
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                int codigoArquivo;
                // Extrai o c�digo da linha (o segundo valor, ap�s o primeiro ';')
                sscanf(linha, "%*[^;];%d", &codigoArquivo);

                if (codigoArquivo == produtos.codigo) {
                    codigoExiste = 1;
                    break; // Encontrou c�digo duplicado, pode parar de ler
                }
            }
            fclose(arquivo); // Fecha o arquivo ap�s a verifica��o
        }
        // ---- Fim da valida��o ----

        if (codigoExiste) {
            printf("Erro: Este c�digo j� existe! Digite outro c�digo.\n");
        } else {
            break; // C�digo � v�lido e �nico, sai do la�o
        }
    } while(1);
    
    // Valida��o do pre�o
    do {
        printf("Digite o pre�o do produto (valor positivo): R$ ");
        if(scanf("%f", &produtos.preco) != 1) {
            printf("Erro: Digite um n�mero v�lido!\n");
            while (getchar() != '\n'); 
        } else if(produtos.preco <= 0) {
            printf("Erro: Pre�o deve ser maior que zero!\n");
        } else {
            break;
        }
    } while(1);
    
    // Valida��o da quantidade
    do {
        printf("Digite a quantidade do produto (n�mero n�o negativo): ");
        if(scanf("%d", &produtos.qtd) != 1) {
            printf("Erro: Digite apenas n�meros!\n");
            while (getchar() != '\n'); 
        } else if(produtos.qtd < 0) {
            printf("Erro: Quantidade n�o pode ser negativa!\n");
        } else {
            break;
        }
    } while(1);
    
    // Valida��o se � gen�rico
    do {
        printf("Ele � gen�rico? [s/n]: ");
        while (getchar() != '\n'); 
        scanf("%c", &temp);
        
        if(temp == 's' || temp == 'S'){
            produtos.generico = true;
            break;
        } else if(temp == 'n' || temp == 'N'){
            produtos.generico = false;
            break;
        } else {
            printf("Erro: Digite apenas 's' para sim ou 'n' para n�o!\n");
        }
    } while(1);
    
    // Valida��o se � remedio ou outro tipo de produto
    do {
        printf("� um rem�dio? [s/n]: ");
        while (getchar() != '\n'); 
        scanf("%c", &temp);
        
        if(temp == 's' || temp == 'S'){
            produtos.generico = true;
            break;
        } else if(temp == 'n' || temp == 'N'){
            produtos.generico = false;
            break;
        } else {
            printf("Erro: Digite apenas 's' para sim ou 'n' para n�o!\n");
        }
    } while(1);
    
    contador++; 
    
	salvarProdutos(produtos.nome, produtos.codigo, produtos.qtd, produtos.preco, produtos.remedio, produtos.generico);
    
    printf("\nProduto cadastrado com sucesso!\n");
	system("pause");
	system("cls");
    return 1;
}

void salvarProdutos(char nome[50], int codigo, int qtd, float preco, bool generico, bool remedio){
    FILE *arquivo;
    
    arquivo = fopen("produtos.txt", "a");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo para salvar produtos!\n");
        return;
    }
    
    fprintf(arquivo, "%s;%d;%.2f;%d;%d;%d\n", 
            nome, 
            codigo, 
            preco, 
            qtd, 
            remedio ? 1 : 0,
            generico ? 1 : 0);
    
    
    fclose(arquivo);
}	
