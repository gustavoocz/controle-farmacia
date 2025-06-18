#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//variaveis globais
int login=0, nivelacesso=0, contador = 0;

//prototipos
int Verificarlogin();
int Login();
void Menu();
int cadastrarItem();
void salvarProdutos(char nome[50], int codigo, int qtd, float preco, bool generico, bool remedio);
int cadastrarPessoa();
void salvarPessoa(char nome[50], char cpf[12], char email[100]); 
void MenuConsulta();
void ListarProdutos();
void PesquisaProduto(char codigodigitado[]);
void Pesquisacodigo();

//struct
struct produto{
	char nome[50];
	int codigo, qtd;
	float preco;
	bool generico, remedio;
};

struct pessoa {
	char nome[50], cpf[12], email[100];
};

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
	system("cls");
	
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
		while (getchar() != '\n'); 
		switch(op){
			case 1:
				cadastrarPessoa();
				Menu();
				break;
			case 2:
				cadastrarItem();
				Menu();
				break;
			case 3:
				printf("registrar venda");
				break;
			case 4:
				MenuConsulta();
				Menu();
				break;
			case 5:
				printf("\nSaindo...");sleep(1);printf(".....");
				break;
		}
	} else {
		//menu para o vendedor
		printf("------- MENU DE VENDAS ---------\n");
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
				MenuConsulta();
				Menu();
				break;
			case 3:
				printf("\nSaindo...");sleep(1);printf(".....");
				break;
		}
	}
}

void MenuConsulta(){
	int op;
	system("cls");
	printf("--------- MENU DE CONSULTA -----------\n");
	printf("--------------------------------------\n");
	printf("1. Listar clientes\n2. Listar produtos\n3. Pesquisar cliente (nome)\n4. Pesquisar produto (código)\n5. Produtos em baixa no estoque\n6. Voltar ao Menu principal\n");
	printf("--------------------------------------\n");
	printf("Escolha uma opção: ");
	scanf("%d",&op);
	getchar();
	switch(op){
		case 1:
			printf("lista de clientes");
			break;
		case 2:
			ListarProdutos();//adicionar algo para esperar o enter do usuario para avançar e voltar ao menu principal
			MenuConsulta();
			break;
		case 3:
			printf("pesquisa de cliente");
			break;
		case 4:
			Pesquisacodigo();
			MenuConsulta();
			break;
		case 5:
			printf("produtos em baixa");
			break;
		case 6:
			break;
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
	system("cls");
	
    int i;
    char temp;
    struct produto produtos;
    // Validação do nome do produto
    do { 
        printf("Digite o nome do produto: ");
        fgets(produtos.nome, sizeof(produtos.nome), stdin);
        produtos.nome[strcspn(produtos.nome, "\n")] = '\0';
        
        if(strlen(produtos.nome) == 0){
            printf("Erro: Nome do produto não pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
    
    // Validação do código do produto
    do {
        printf("Digite o código do produto (número positivo): ");
        if(scanf("%d", &produtos.codigo) != 1) {
            printf("Erro: Digite apenas números!\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }
        
        if(produtos.codigo <= 0) {
            printf("Erro: Código deve ser um número positivo!\n");
            continue; 
        }

        FILE *arquivo;
        int codigoExiste = 0;
        
        arquivo = fopen("produtos.txt", "r");
        
        // Só executa a verificação se o arquivo já existir
        if (arquivo != NULL) {
            char linha[200];
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                int codigoArquivo;
                // Extrai o código da linha (o segundo valor, após o primeiro ';')
                sscanf(linha, "%*[^;];%d", &codigoArquivo);

                if (codigoArquivo == produtos.codigo) {
                    codigoExiste = 1;
                    break; // Encontrou código duplicado, pode parar de ler
                }
            }
            fclose(arquivo); // Fecha o arquivo após a verificação
        }

        if (codigoExiste) {
            printf("Erro: Este código já existe! Digite outro código.\n");
        } else {
            break; // Código é válido e único, sai do laço
        }
    } while(1);
    
    // Validação do preço
    do {
        printf("Digite o preço do produto (valor positivo): R$ ");
        if(scanf("%f", &produtos.preco) != 1) {
            printf("Erro: Digite um número válido!\n");
            while (getchar() != '\n'); 
        } else if(produtos.preco <= 0) {
            printf("Erro: Preço deve ser maior que zero!\n");
        } else {
            break;
        }
    } while(1);
    
    // Validação da quantidade
    do {
        printf("Digite a quantidade do produto (número não negativo): ");
        if(scanf("%d", &produtos.qtd) != 1) {
            printf("Erro: Digite apenas números!\n");
            while (getchar() != '\n'); 
        } else if(produtos.qtd < 0) {
            printf("Erro: Quantidade não pode ser negativa!\n");
        } else {
            break;
        }
    } while(1);
    
    // Validação se é remedio ou outro tipo de produto
    do {
        printf("É um remédio? [s/n]: ");
        while (getchar() != '\n'); 
        scanf("%c", &temp);
        
        if(temp == 's' || temp == 'S'){
            produtos.remedio = true;
            break;
        } else if(temp == 'n' || temp == 'N'){
            produtos.remedio = false;
            break;
        } else {
            printf("Erro: Digite apenas 's' para sim ou 'n' para não!\n");
        }
    } while(1);
    
    // Validaï¿½ï¿½o se ï¿½ genï¿½rico
	if(produtos.remedio){
	    do {
	        printf("Ele ï¿½ genï¿½rico? [s/n]: ");
	        while (getchar() != '\n'); 
			scanf("%c", &temp);
	       
	        if(temp == 's' || temp == 'S'){
	            produtos.generico = true;
	            break;
	        } else if(temp == 'n' || temp == 'N'){
	            produtos.generico = false;
	            break;
	        } else {
	            printf("Erro: Digite apenas 's' para sim ou 'n' para nï¿½o!\n");
	        }
    	} while(1);
	} else { 
		produtos.generico = false;
	}
    
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

void ListarProdutos(){
	system("cls");
	
	FILE *arquivo;
    char linha[200];
    char *nome, *codigo, *valor, *qtd, *gener, *remed;
    int numproduto = 1;

    // Abre o arquivo para leitura
    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        return;
    }

    printf("\nLista dos produtos cadastrados:\n");
    printf("----------------------------------\n");

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;

        // Separa os registros usando strtok
        nome = strtok(linha, ";");
        codigo = strtok(NULL, ";");
        valor = strtok(NULL,";");
        qtd = strtok(NULL,";");
        remed = strtok(NULL, ";");
        gener = strtok(NULL,";");

        if (nome != NULL && codigo != NULL && valor!=NULL && qtd != NULL && remed!= NULL && gener!= NULL) {
        	
        	if(strcmp(remed,"1")==0){
        		remed= "Sim";
			}else{
				remed = "Não";
			}
			if(strcmp(gener,"1")==0){
				gener = "Sim";
			}else{
				gener = "Não";
			}
        	
            printf("Produto %d:\n", numproduto);
            printf("  Nome: %s\n", nome);
            printf("  Codigo: %s\n", codigo);
            printf("  Valor: %s\n",valor);
            printf("  Quantidade: %s\n",qtd);
            printf("  É um remédio?: %s\n",remed);
            printf("  É genérico?: %s\n\n",gener);
        } else {
            printf("Produto %d: %s (formato inválido)\n", numproduto, linha);
        }
        numproduto++;
    }

    printf("----------------------------------\n");

    fclose(arquivo);
	
	
	system("pause");
}

void Pesquisacodigo(){
	system("cls");
	
	char codigo[10];
	
	printf("Digite o código do produto desejado: ");
	fgets(codigo,sizeof(codigo),stdin);
	codigo[strcspn(codigo,"\n")]=0; 
	
	PesquisaProduto(codigo);
}

void PesquisaProduto(char codigodigitado[]){
	system("cls");
	
	FILE *arquivo;
    char linha[200];
    char *nome, *codigo, *valor, *qtd, *gener, *remed;
    int numproduto = 1;

    // Abre o arquivo para leitura
    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        return;
    }

    printf("\nProduto com código '%s':\n",codigodigitado);
    printf("----------------------------------\n");

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;
		
		nome = strtok(linha,";");
		codigo=strtok(NULL,";");
		
		if(strcmp(codigodigitado,codigo)==0){
			valor = strtok(NULL,";");
       	 qtd = strtok(NULL,";");
        	remed = strtok(NULL, ";");
	        gener = strtok(NULL,";");

	        if (nome != NULL && codigo != NULL && valor!=NULL && qtd != NULL && remed!= NULL && gener!= NULL) {
        	
	        	if(strcmp(remed,"1")==0){
	        		remed= "Sim";
				}else{
					remed = "Não";
				}
				if(strcmp(gener,"1")==0){
					gener = "Sim";
				}else{
					gener = "Não";
				}
			
			
				printf("  Nome: %s\n", nome);
	            printf("  Codigo: %s\n", codigo);
	            printf("  Valor: %s\n",valor);
	            printf("  Quantidade: %s\n",qtd);
	            printf("  É um remédio?: %s\n",remed);
	            printf("  É genérico?: %s\n\n",gener);
			}
    	}else{
    		printf("Nenhum produto foi encontrado!\n");
    		break;
		}
	}

    printf("----------------------------------\n");

    fclose(arquivo);
	
	
	system("pause");
	
}

int cadastrarPessoa(){
	
	struct pessoa pessoas;
	int i;
	
	// Validação do nome da pessoa
    do {
        printf("Digite seu nome: ");
        fgets(pessoas.nome, sizeof(pessoas.nome), stdin);
        pessoas.nome[strcspn(pessoas.nome, "\n")] = '\0';
		        
        if(strlen(pessoas.nome) == 0){
            printf("Erro: Nome do produto não pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
    
    // Validação do cpf da pessoa
    do {
        printf("Digite seu CPF: ");
        scanf("%s", pessoas.cpf);
        while (getchar() != '\n');
        
        bool cpfValido = true;
        
        if(strlen(pessoas.cpf) != 11){
            cpfValido = false;
        } else {
            for (i = 0; i < 11; i++) {
                if (!isdigit(pessoas.cpf[i])) {
                    cpfValido = false;
                    break; 
                }
            }
        }
        if(!cpfValido){
            printf("Erro: CPF inválido! Deve conter exatamente 11 dígitos numéricos. Tente novamente.\n");
        } else {
            break; 
        }        
    } while(1);
 
    // Validação do email da pessoa  
    do {
        printf("Digite seu email: ");
        fgets(pessoas.email, sizeof(pessoas.email), stdin);
        pessoas.email[strcspn(pessoas.email, "\n")] = '\0';
        
        if(strlen(pessoas.email) == 0){
            printf("Erro: Email não pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
	
	salvarPessoa(pessoas.nome, pessoas.cpf, pessoas.email);
    
    printf("\nPessoa cadastrada com sucesso!\n");
    system("pause");
    system("cls");
    
    return 1;	
}

void salvarPessoa(char nome[50], char cpf[12], char email[100]){
    FILE *arquivo;
    
    arquivo = fopen("clientes.txt", "a");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo para salvar pessoas!\n");
        return;
    }
    
    fprintf(arquivo, "%s;%s;%s\n", nome, cpf, email);
    
    fclose(arquivo);
}
