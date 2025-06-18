#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//variaveis globais
int login=0, nivelacesso=0;

//prototipos
int Verificarlogin();
int Login();
void Menu();
void MenuConsulta();
int cadastrarItem();
int cadastrarPessoa();
void registrarVenda();
void salvarProdutos(char nome[50], int Código, int qtd, float preco, bool generico, bool remedio);
void salvarPessoa(char nome[50], char cpf[12], char email[100]);
int validarCliente(char cpfVerificar[]); 
void ListarProdutos();
void ListarClientes();
void PesquisaProduto(char Códigodigitado[]);
void pesquisaCódigo();
void pesquisaNome();
void PesquisaCliente(char nomedigitado[]);
void ProdutosBaixaqtd();

//struct
struct produto{
	char nome[50];
	int Código, qtd;
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
		printf("----- MENU ADMINISTRATIVO ------\n");
		printf("--------------------------------\n");
		printf("1. Cadastrar cliente\n2. Cadastrar produto\n3. Registrar venda\n4. Consulta\n5. Sair do programa\n");
		//em consulta adicionar listagem de clientes e produtos, pesquisa de ambos e produtos em baixa qtd
		printf("--------------------------------\n");
		printf("Escolha uma opção: ");
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
				registrarVenda();
				Menu();
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
				registrarVenda();
				Menu();
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
			ListarClientes();
			MenuConsulta();
			break;
		case 2:
			ListarProdutos();//adicionar algo para esperar o enter do usuario para avançar e voltar ao menu principal
			MenuConsulta();
			break;
		case 3:
			pesquisaNome();
			MenuConsulta();
			break;
		case 4:
			pesquisaCódigo();
			MenuConsulta();
			break;
		case 5:
			ProdutosBaixaqtd();
			MenuConsulta();
			break;
		case 6:
			break;
	}	
}

int Login(){
	
	int nivel;
	
	nivel = Verificarlogin();
	if(nivel==1){
		printf("Permissão de administrador concedida\n");
		login=1;
	} else if (nivel==2){
		printf("Permissão de vendedor concedida\n");
		login=1;
	} else {
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
        return 0;
    }
    
    int tentativas=0;
    while(tentativas<3){
		
	    char usu[20];
		char senha[10];
		
		printf("Digite o usuário: ");
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
        if(scanf("%d", &produtos.Código) != 1) {
            printf("Erro: Digite apenas números!\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }
        
        if(produtos.Código <= 0) {
            printf("Erro: Código deve ser um número positivo!\n");
            continue; 
        }

        FILE *arquivo;
        int CódigoExiste = 0;
        
        arquivo = fopen("produtos.txt", "r");
        
        // Só executa a verificação se o arquivo já existir
        if (arquivo != NULL) {
            char linha[200];
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                int CódigoArquivo;
                // Extrai o código da linha (o segundo valor, após o primeiro ';')
                sscanf(linha, "%*[^;];%d", &CódigoArquivo);

                if (CódigoArquivo == produtos.Código) {
                    CódigoExiste = 1;
                    break; // Encontrou código duplicado, pode parar de ler
                }
            }
            fclose(arquivo); // Fecha o arquivo após a verificação
        }

        if (CódigoExiste) {
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
    
    // Validação se é genérico
	if(produtos.remedio){
	    do {
	        printf("Ele é genérico? [s/n]: ");
	        while (getchar() != '\n'); 
			scanf("%c", &temp);
	       
	        if(temp == 's' || temp == 'S'){
	            produtos.generico = true;
	            break;
	        } else if(temp == 'n' || temp == 'N'){
	            produtos.generico = false;
	            break;
	        } else {
	            printf("Erro: Digite apenas 's' para sim ou 'n' para não!\n");
	        }
    	} while(1);
	} else { 
		produtos.generico = false;
	}
    
	salvarProdutos(produtos.nome, produtos.Código, produtos.qtd, produtos.preco, produtos.generico, produtos.remedio);
    
    printf("\nProduto cadastrado com sucesso!\n");
	system("pause");
	system("cls");
    return 1;
}

void salvarProdutos(char nome[50], int Código, int qtd, float preco, bool generico, bool remedio){
	FILE *arquivo;
	    
	arquivo = fopen("produtos.txt", "a");
	if(arquivo == NULL){
	    printf("Erro ao abrir arquivo para salvar produtos!\n");
	    return;
	}
	    
	fprintf(arquivo, "%s;%d;%.2f;%d;%d;%d\n", 
	        nome, 
	        Código, 
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
    char *nome, *Código, *valor, *qtd, *gener, *remed;
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

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;

        // Separa os registros usando strtok
        nome = strtok(linha, ";");
        Código = strtok(NULL, ";");
        valor = strtok(NULL,";");
        qtd = strtok(NULL,";");
        remed = strtok(NULL, ";");
        gener = strtok(NULL,";");

        if (nome != NULL && Código != NULL && valor!=NULL && qtd != NULL && remed!= NULL && gener!= NULL) {
        	
        	if(strcmp(remed,"1")==0){
        		remed= "Sim";
			} else {
				remed = "Não";
			}
			if(strcmp(gener,"1")==0){
				gener = "Sim";
			} else {
				gener = "Não";
			}
        	
            printf("Produto %d:\n", numproduto);
            printf("  Nome: %s\n", nome);
            printf("  Código: %s\n", Código);
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

void pesquisaCódigo(){
	system("cls");
	
	char Código[10];
	bool Códigocorreto = true;
	
	do{
		int i;
		printf("Digite o código do produto desejado: ");
		fgets(Código,sizeof(Código),stdin);
		Código[strcspn(Código,"\n")]=0; 
		for(i=0;i<strlen(Código);i++){
			if(isdigit(Código[i])){
				Códigocorreto=true;
			}else{
				printf("Digite apenas números para o código do produto!\n");
				Códigocorreto=false;
				break;
			}
		}
		if(Códigocorreto){
			break;
		}
	} while(1);

	PesquisaProduto(Código);
}

void PesquisaProduto(char Códigodigitado[]){
	system("cls");
	
	FILE *arquivo;
    char linha[200];
    char *nome, *Código, *valor, *qtd, *gener, *remed;

    // Abre o arquivo para leitura
    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        system("pause");
        return;
    }

    printf("\nProduto com código '%s':\n",Códigodigitado);
    printf("----------------------------------\n");
	bool produtoencontrado = false;

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;
        
		nome = strtok(linha,";");
		Código=strtok(NULL,";");
		
		if(Código != NULL && strcmp(Códigodigitado,Código)==0){
			valor = strtok(NULL,";");
       	 	qtd = strtok(NULL,";");
        	remed = strtok(NULL, ";");
	        gener = strtok(NULL,";");

	        if (nome != NULL && Código != NULL && valor!=NULL && qtd != NULL && remed!= NULL && gener!= NULL) {
        	
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
	            printf("  Código: %s\n", Código);
	            printf("  Valor: %s\n",valor);
	            printf("  Quantidade: %s\n",qtd);
	            printf("  É um remédio?: %s\n",remed);
	            printf("  É genérico?: %s\n\n",gener);
	            
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
	
	// Validação do nome da pessoa
    do {
        printf("Digite o nome do cliente: ");
        fgets(pessoas.nome, sizeof(pessoas.nome), stdin);
        pessoas.nome[strcspn(pessoas.nome, "\n")] = '\0';
		        
        if(strlen(pessoas.nome) == 0){
            printf("Erro: Nome do cliente não pode estar vazio! Tente novamente.\n");
        } else {
            break; 
        }
    } while(1);
    
    // Validação do cpf da pessoa
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
            printf("Erro: CPF inválido! Deve conter exatamente 11 dígitos numéricos. Tente novamente.\n");
        } else {
            break; 
        }        
    } while(1);
 
    // Validação do email da pessoa  
    do {
        printf("Digite o email do cliente: ");
        fgets(pessoas.email, sizeof(pessoas.email), stdin);
        pessoas.email[strcspn(pessoas.email, "\n")] = '\0';
        
        if(strlen(pessoas.email) == 0){
            printf("Erro: Email não pode estar vazio! Tente novamente.\n");
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

void ListarClientes(){
	system("cls");
	
	FILE *arquivo;
    char linha[200];
    char *nome, *cpf,*email;
    int numcliente = 1;

    // Abre o arquivo para leitura
    arquivo = fopen("clientes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        system("pause");
        return;
    }

    printf("\nLista dos clientes cadastrados:\n");
    printf("----------------------------------\n");

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;

        // Separa os registros usando strtok
        nome = strtok(linha, ";");
        cpf = strtok(NULL, ";");
        email = strtok(NULL,";");

        if (nome != NULL && cpf != NULL && email!=NULL) {
        	
            printf("Cliente %d:\n", numcliente);
            printf("  Nome: %s\n", nome);
            printf("  CPF: %s\n", cpf);
            printf("  Email: %s\n\n",email);

        } else {
            printf("Cliente %d: %s (formato inválido)\n", numcliente, linha);
        }
        numcliente++;
    }

    printf("----------------------------------\n");

    fclose(arquivo);
	
	system("pause");
}

void pesquisaNome(){
	system("cls");
	
	char nome[100];
	int i;
	
	
	do{
		bool nomecorreto = false;
		printf("Digite o nome do cliente desejado: ");
		fgets(nome,sizeof(nome),stdin);
		nome[strcspn(nome,"\n")]=0;
		
		for(i=0; i<strlen(nome); i++){
			if(!isalpha(nome[i]) && !isspace(nome[i])){
				printf("Digite apenas letras para o nome!\n");
				nomecorreto=false;
				break;
			}else{
				nomecorreto=true;
			}
		}
		if(nomecorreto){
			break;
		}
	}while(1);
	//adicionar verificação
	 
	
	for(i=0;i<strlen(nome);i++){
		nome[i] = tolower(nome[i]);
	}
	
	PesquisaCliente(nome);
}

void PesquisaCliente(char nomedigitado[]){
	system("cls");
	
	FILE *arquivo;
    char linha[200];
    char *nome, *cpf,*email;
    int numcliente=1;

    // Abre o arquivo para leitura
    arquivo = fopen("clientes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        system("pause");
        return;
    }

    printf("Cliente(s) '%s' encontrado(s):\n", nomedigitado);
    printf("----------------------------------\n");
	bool clienteencontrado = false;

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;
        
		nome = strtok(linha,";");
		//Variavel para poder pesquisar nome sem se importar com maiusculo ou minusculo
		char nomeformatado[100];
		
		//copia do nome cadastrado para minusculo
		int i;
		for(i=0;i<strlen(nome);i++){
			nomeformatado[i] = tolower(nome[i]);
		}
		
		nomeformatado[i] = '\0';
		
		//Analisa os nomes
		if(strcmp(nomedigitado,nomeformatado)==0){
			cpf = strtok(NULL,";");
			email= strtok(NULL,";");

	         if (nome != NULL && cpf != NULL && email!=NULL) {
        	
	            printf("Cliente %d:\n", numcliente);
	            printf("  Nome: %s\n", nome); //Apresenta o nome salvo
 	      		printf("  CPF: %s\n", cpf);
	            printf("  Email: %s\n\n",email);
		            
		        clienteencontrado=true;
		        numcliente++;
			}
    	}
	}
	if(!clienteencontrado){
		printf("Nenhum cliente foi encontrado!\n");
	}
	
    printf("----------------------------------\n");

    fclose(arquivo);
		
	system("pause");
	
}


void ProdutosBaixaqtd(){
	system("cls");
	
	FILE *arquivo;
    char linha[200];
    char *nome, *Código, *valor, *qtd, *gener, *remed;
    int numproduto = 1;

    // Abre o arquivo para leitura
    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        system("pause");
        return;
    }

    printf("\nLista dos produtos com baixa quantidade no estoque (<10):\n");
    printf("-----------------------------------------------------------\n");

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;

        // Separa os registros usando strtok
        nome = strtok(linha, ";");
        Código = strtok(NULL, ";");
        valor = strtok(NULL,";");
        qtd = strtok(NULL,";");
        
        if(atoi(qtd)<10){
           remed = strtok(NULL, ";");
 	       gener = strtok(NULL,";");

 	       if (nome != NULL && Código != NULL && valor!=NULL && qtd != NULL && remed!= NULL && gener!= NULL) {
        	
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
 	           printf("  Código: %s\n", Código);
 	           printf("  Valor: %s\n",valor);
 	           printf("  Quantidade: %s\n",qtd);
 	           printf("  É um remédio?: %s\n",remed);
  	        printf("  É genérico?: %s\n\n",gener);
      	 	} else {
      	      printf("Produto %d: %s (formato inválido)\n", numproduto, linha);
     	   }
 	       numproduto++;
		}
        
    }

    printf("----------------------------------\n");

    fclose(arquivo);	
	
	system("pause");
}

void registrarVenda() {
    system("cls"); 
    FILE *arquivoProdutos, *arquivoTemp, *arquivoVendas;
    
	char cpfCliente[12], CódigoProduto[10], linha[200];
    int qtdVendida, novaQtd;     
    bool produtoEncontrado = false,estoqueSuficiente = false;

    printf("--------- REGISTRO DE VENDA -----------\n");
    
    do{
    	printf("Digite o CPF do cliente (apenas números): ");
   		scanf("%11s", cpfCliente);
	    while (getchar() != '\n');
		int i;
		bool cpfcorreto=false;
		
		if(strlen(cpfCliente)!=11){
			printf("Digite um CPF válido!\n");
			cpfcorreto=false;
		}else{
			
			for(i=0;i<strlen(cpfCliente);i++){
			if(isdigit(cpfCliente[i])){
				cpfcorreto=true;
			}else{
				printf("Digite apenas números para o CPF do cliente!\n");
				cpfcorreto=false;
				break;
			}
			}
			if(cpfcorreto){
				if (!validarCliente(cpfCliente)) {
 		     		 printf("\nERRO: Cliente com CPF '%s' não cadastrado!\n", cpfCliente);
   		 		}else{
    				break;
				}
			}
		}
		
	}while(1);
    
    bool Códigocorreto = false;
	do{
	    printf("Digite o código do produto: ");
    	scanf("%s", CódigoProduto);
    	while (getchar() != '\n');
    	int i;
    	for(i=0;i<strlen(CódigoProduto);i++){
			if(isdigit(CódigoProduto[i])){
				Códigocorreto=true;
			}else{
				printf("Digite apenas números para o código do produto!\n");
				Códigocorreto=false;
				break;
			}
		}
		if(Códigocorreto){
			break;
		}
    		
	}while(1);


    arquivoProdutos = fopen("produtos.txt", "r");
    arquivoTemp = fopen("produtos_temp.txt", "w"); // Arquivo temporário para reescrever os dados

    if (arquivoProdutos == NULL || arquivoTemp == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de produtos.\n");
        if(arquivoProdutos) fclose(arquivoProdutos);
        if(arquivoTemp) fclose(arquivoTemp);
        system("pause");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoProdutos) != NULL) {
        char linhaOriginal[200];
        strcpy(linhaOriginal, linha);

        char *nome = strtok(linha, ";");
        char *Código = strtok(NULL, ";");

        if (Código != NULL && strcmp(Código, CódigoProduto) == 0) {
            produtoEncontrado = true;

            char* precoStr = strtok(NULL, ";");
            char* qtdStr = strtok(NULL, ";");
            char* remedioStr = strtok(NULL, ";");
            char* genericoStr = strtok(NULL, ";");

            int qtdAtual = atoi(qtdStr);
            float preco = atof(precoStr);

            printf("\nProduto encontrado: %s\nEstoque atual: %d\n", nome, qtdAtual);

            if (qtdAtual > 0) {
                printf("Digite a quantidade a ser vendida: ");
                scanf("%d", &qtdVendida);
                while (getchar() != '\n');

                if (qtdVendida > 0 && qtdVendida <= qtdAtual) {
                    estoqueSuficiente = true;
                    novaQtd = qtdAtual - qtdVendida;

                    // Reescreve a linha do produto com a nova quantidade
                    fprintf(arquivoTemp, "%s;%s;%.2f;%d;%s;%s", nome, Código, preco, novaQtd, remedioStr, genericoStr);

                    // Abre o arquivo de vendas para adicionar o registro
                    arquivoVendas = fopen("vendas.txt", "a");
                    if (arquivoVendas != NULL) {
                        fprintf(arquivoVendas, "CPF: %s;Código: %s;Produto: %s;Qtd vendida: %d;Valor unidade: %.2f;Total: %.2f\n",
                                cpfCliente, Código, nome, qtdVendida, preco, preco * qtdVendida);
                        fclose(arquivoVendas);
                    }

                    printf("\nVenda registrada com sucesso!\n");

                } else {
                    printf("\nERRO: Quantidade inválida ou maior que o estoque!\n");
                    fputs(linhaOriginal, arquivoTemp);
                }
            } else {
                printf("\nERRO: Produto sem estoque!\n");
                fputs(linhaOriginal, arquivoTemp);
            }
        } else {
            fputs(linhaOriginal, arquivoTemp); 
        }
    }

    fclose(arquivoProdutos);
    fclose(arquivoTemp);

    if (!produtoEncontrado) {
        printf("\nERRO: Produto com código '%s' não encontrado!\n", CódigoProduto);
        remove("produtos_temp.txt"); // Apaga o arquivo temporário pois nada mudou
    } else if(estoqueSuficiente) {
        // substitui o arquivo antigo pelo novo
        remove("produtos.txt");
        rename("produtos_temp.txt", "produtos.txt");
    } else {
        // Se o produto foi encontrado mas a venda falhou, apaga o temp
        remove("produtos_temp.txt");
    }

    system("pause");
}

int validarCliente(char cpfVerificar[]) {
    FILE *arquivo = fopen("clientes.txt", "r");
    char linha[200];
    
    if (arquivo == NULL) {
        return 0; 
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *nome = strtok(linha, ";");
        char *cpf = strtok(NULL, ";");
        if (cpf != NULL && strcmp(cpf, cpfVerificar) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}
