#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//variaveis globais
int login=0,nivelacesso=0;

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

	//ao final de todas as fun√ß√µes, o main ou Menu devem ser chamados para dar continuidade ao programa
	if(nivelacesso==1){
		//menu para o admin
		printf("----- MENU ADMINISTRATIVO ------\n");
		printf("--------------------------------\n");
		printf("1. Cadastrar cliente\n2. Cadastrar produto\n3. Registrar venda\n4. Consulta\n5. Sair do programa\n");
		//em consulta adicionar listagem de clientes e produtos, pesquisa de ambos e produtos em baixa qtd
		printf("--------------------------------\n");
		printf("Escolha uma op√ß√£o: ");
		scanf("%d",&op);
		getchar();
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
	}else{
		//menu para o vendedor
		printf("------- MENU DE VENDAS ---------\n");
		printf("--------------------------------\n");
		printf("1. Registrar venda\n2. Consulta\n3. Sair do programa\n");
		//em consulta adicionar listagem de clientes e produtos, pesquisa de ambos e produtos em baixa qtd
		printf("--------------------------------\n");
		printf("Escolha uma op√ß√£o: ");
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
	printf("1. Listar clientes\n2. Listar produtos\n3. Pesquisar cliente (nome)\n4. Pesquisar produto (cÛdigo)\n5. Produtos em baixa no estoque\n6. Voltar ao Menu principal\n");
	printf("--------------------------------------\n");
	printf("Escolha uma opÁ„o: ");
	scanf("%d",&op);
	getchar();
	switch(op){
		case 1:
			printf("lista de clientes");
			break;
		case 2:
			ListarProdutos();//adicionar algo para esperar o enter do usuario para avanÁar e voltar ao menu principal
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
		printf("Permiss√£o de admin concedida\n");
		login=1;
	}else if(nivel==2){
		printf("Permiss√£o de vendedor concedida\n");
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

    	// L√™ linha por linha do arquivo
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
    // ValidaÁ„o do nome do produto
    do { 
        printf("Digite o nome do produto: ");
        fgets(produtos.nome, sizeof(produtos.nome), stdin);
        produtos.nome[strcspn(produtos.nome, "\n")] = '\0';
        
        if(strlen(produtos.nome) == 0){
            printf("Erro: Nome do produto n„o pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
    
    // ValidaÁ„o do cÛdigo do produto
    do {
        printf("Digite o cÛdigo do produto (n˙mero positivo): ");
        if(scanf("%d", &produtos.codigo) != 1) {
            printf("Erro: Digite apenas n˙meros!\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }
        
        if(produtos.codigo <= 0) {
            printf("Erro: CÛdigo deve ser um n˙mero positivo!\n");
            continue; 
        }

        FILE *arquivo;
        int codigoExiste = 0;
        
        arquivo = fopen("produtos.txt", "r");
        
        // SÛ executa a verificaÁ„o se o arquivo j· existir
        if (arquivo != NULL) {
            char linha[200];
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                int codigoArquivo;
                // Extrai o cÛdigo da linha (o segundo valor, apÛs o primeiro ';')
                sscanf(linha, "%*[^;];%d", &codigoArquivo);

                if (codigoArquivo == produtos.codigo) {
                    codigoExiste = 1;
                    break; // Encontrou cÛdigo duplicado, pode parar de ler
                }
            }
            fclose(arquivo); // Fecha o arquivo apÛs a verificaÁ„o
        }

        if (codigoExiste) {
            printf("Erro: Este cÛdigo j· existe! Digite outro cÛdigo.\n");
        } else {
            break; // CÛdigo È v·lido e ˙nico, sai do laÁo
        }
    } while(1);
    
    // ValidaÁ„o do preÁo
    do {
        printf("Digite o preÁo do produto (valor positivo): R$ ");
        if(scanf("%f", &produtos.preco) != 1) {
            printf("Erro: Digite um n˙mero v·lido!\n");
            while (getchar() != '\n'); 
        } else if(produtos.preco <= 0) {
            printf("Erro: PreÁo deve ser maior que zero!\n");
        } else {
            break;
        }
    } while(1);
    
    // ValidaÁ„o da quantidade
    do {
        printf("Digite a quantidade do produto (n˙mero n„o negativo): ");
        if(scanf("%d", &produtos.qtd) != 1) {
            printf("Erro: Digite apenas n˙meros!\n");
            while (getchar() != '\n'); 
        } else if(produtos.qtd < 0) {
            printf("Erro: Quantidade n„o pode ser negativa!\n");
        } else {
            break;
        }
    } while(1);
    
    // ValidaÁ„o se È remedio ou outro tipo de produto
    do {
        printf("… um remÈdio? [s/n]: ");
        while (getchar() != '\n'); 
        scanf("%c", &temp);
        
        if(temp == 's' || temp == 'S'){
            produtos.remedio = true;
            break;
        } else if(temp == 'n' || temp == 'N'){
            produtos.remedio = false;
            break;
        } else {
            printf("Erro: Digite apenas 's' para sim ou 'n' para n„o!\n");
        }
    } while(1);
    
    // ValidaÔøΩÔøΩo se ÔøΩ genÔøΩrico
	if(produtos.remedio){
	    do {
	        printf("Ele ÔøΩ genÔøΩrico? [s/n]: ");
	        while (getchar() != '\n'); 
			scanf("%c", &temp);
	       
	        if(temp == 's' || temp == 'S'){
	            produtos.generico = true;
	            break;
	        } else if(temp == 'n' || temp == 'N'){
	            produtos.generico = false;
	            break;
	        } else {
	            printf("Erro: Digite apenas 's' para sim ou 'n' para nÔøΩo!\n");
	        }
    	} while(1);
	} else { 
		produtos.generico = false;
	}
    
	salvarProdutos(produtos.nome, produtos.codigo, produtos.qtd, produtos.preco, produtos.generico, produtos.remedio);
    
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
        system("pause");
        return;
    }

    printf("\nLista dos produtos cadastrados:\n");
    printf("----------------------------------\n");

    // LÍ linha por linha do arquivo
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
				remed = "N„o";
			}
			if(strcmp(gener,"1")==0){
				gener = "Sim";
			}else{
				gener = "N„o";
			}
        	
            printf("Produto %d:\n", numproduto);
            printf("  Nome: %s\n", nome);
            printf("  Codigo: %s\n", codigo);
            printf("  Valor: %s\n",valor);
            printf("  Quantidade: %s\n",qtd);
            printf("  … um remÈdio?: %s\n",remed);
            printf("  … genÈrico?: %s\n\n",gener);
        } else {
            printf("Produto %d: %s (formato inv·lido)\n", numproduto, linha);
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
	
	printf("Digite o cÛdigo do produto desejado: ");
	fgets(codigo,sizeof(codigo),stdin);
	codigo[strcspn(codigo,"\n")]=0; 
	PesquisaProduto(codigo);
}

void PesquisaProduto(char codigodigitado[]){
	system("cls");
	
	FILE *arquivo;
    char linha[200];
    char *nome, *codigo, *valor, *qtd, *gener, *remed;

    // Abre o arquivo para leitura
    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        system("pause");
        return;
    }

    printf("\nProduto com cÛdigo '%s':\n",codigodigitado);
    printf("----------------------------------\n");
	bool produtoencontrado = false;

    // LÍ linha por linha do arquivo
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
					remed = "N„o";
				}
				if(strcmp(gener,"1")==0){
					gener = "Sim";
				}else{
					gener = "N„o";
				}
			
			
				printf("  Nome: %s\n", nome);
	            printf("  Codigo: %s\n", codigo);
	            printf("  Valor: %s\n",valor);
	            printf("  Quantidade: %s\n",qtd);
	            printf("  … um remÈdio?: %s\n",remed);
	            printf("  … genÈrico?: %s\n\n",gener);
	            
	            produtoencontrado=true;
	            break;
			}
    	}
	}
	if(!produtoencontrado){
		printf("Nenhum produto foi encontrado!\n");
	}
	
    printf("----------------------------------\n");

    fclose(arquivo);
	
	
	system("pause");
	
}

int cadastrarPessoa(){
	system("cls");
	
	struct pessoa pessoas;
	int i;
	
	// ValidaÁ„o do nome da pessoa
    do {
        printf("Digite o nome do cliente: ");
        fgets(pessoas.nome, sizeof(pessoas.nome), stdin);
        pessoas.nome[strcspn(pessoas.nome, "\n")] = '\0';
		        
        if(strlen(pessoas.nome) == 0){
            printf("Erro: Nome do cliente n„o pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
    
    // ValidaÁ„o do cpf da pessoa
    do {
        printf("Digite o CPF do cliente: ");
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
            printf("Erro: CPF inv·lido! Deve conter exatamente 11 dÌgitos numÈricos. Tente novamente.\n");
        } else {
            break; 
        }        
    } while(1);
 
    // ValidaÁ„o do email da pessoa  
    do {
        printf("Digite o email do cliente: ");
        fgets(pessoas.email, sizeof(pessoas.email), stdin);
        pessoas.email[strcspn(pessoas.email, "\n")] = '\0';
        
        if(strlen(pessoas.email) == 0){
            printf("Erro: Email n„o pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
	
	salvarPessoa(pessoas.nome, pessoas.cpf, pessoas.email);
    
    printf("\nCliente cadastrado com sucesso!\n");
    system("pause");
    system("cls");
    
    return 1;	
}

void salvarPessoa(char nome[50], char cpf[12], char email[100]){
    FILE *arquivo;
    
    arquivo = fopen("clientes.txt", "a");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo para salvar pessoas!\n");
        system("pause");
        return;
    }
    
    fprintf(arquivo, "%s;%s;%s\n", nome, cpf, email);
    
    fclose(arquivo);
}
