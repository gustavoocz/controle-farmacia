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
void salvarProdutos(char nome[50], int codigo, int qtd, float preco, bool generico, bool remedio);
void salvarPessoa(char nome[50], char cpf[12], char email[100]);
int validarCliente(char cpfVerificar[]); 
void ListarProdutos();
void ListarClientes();
void listarVendas();
void PesquisaProduto(char codigodigitado[]);
void pesquisaCodigo();
void pesquisaNome();
void PesquisaCliente(char nomedigitado[]);
void ProdutosBaixaqtd();
void DeletarCliente();
void DeletarProduto();
void deletarVenda();

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
		printf("----- MENU ADMINISTRATIVO ------\n");
		printf("--------------------------------\n");
		printf("1. Cadastrar cliente\n2. Cadastrar produto\n3. Registrar venda\n4. Consulta\n5. Deletar cliente\n6. Deletar produto\n7. Deletar venda\n8. Sair do programa\n");
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
				DeletarCliente();
				Menu();
				break;
			case 6:
				DeletarProduto();
				Menu();
				break;
			case 7:
    				deletarVenda();
    				Menu();
    				break;
			case 8:  
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
			default:
				printf("\nValor inválido. Tente novamente\n\n");
				system("pause");
				system("cls");
				Menu();
				break;
		}
	}
}

void MenuConsulta(){
	int op;
	system("cls");
	printf("--------- MENU DE CONSULTA -----------\n");
	printf("--------------------------------------\n");
	printf("1. Listar clientes\n2. Listar produtos\n3. Listar vendas\n4. Pesquisar cliente (nome)\n5. Pesquisar produto (código)\n6. Produtos em baixa no estoque\n7. Voltar ao Menu principal\n");
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
			ListarProdutos();
			MenuConsulta();
			break;
		case 3:
			listarVendas();
			MenuConsulta();
			break;
		case 4:
			pesquisaNome();
			MenuConsulta();
			break;
		case 5:
			pesquisaCodigo();
			MenuConsulta();
			break;
		case 6:
			ProdutosBaixaqtd();
			MenuConsulta();
			break;
		case 7:
			break;
		default:
			printf("\nValor inválido. Tente novamente\n\n");
			system("pause");
			system("cls");
			MenuConsulta();
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
        int codigoExiste  = 0;
        
        arquivo = fopen("produtos.txt", "r");
        
        // Só executa a verificação se o arquivo já existir
        if (arquivo != NULL) {
            char linha[200];
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                int codigoArquivo;
                // Extrai o código da linha (o segundo valor, após o primeiro ';')
                sscanf(linha, "%*[^;];%d", &codigoArquivo);

                if (codigoArquivo == produtos.codigo) {
                    codigoExiste  = 1;
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
            printf("  Código: %s\n", codigo);
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

void pesquisaCodigo(){
	system("cls");
	
	char codigo[10];
	bool codigocorreto = true;
	
	do{
		int i;
		printf("Digite o código do produto desejado: ");
		fgets(codigo,sizeof(codigo),stdin);
		codigo[strcspn(codigo,"\n")]=0; 
		for(i=0;i<strlen(codigo);i++){
			if(isdigit(codigo[i])){
				codigocorreto=true;
			}else{
				printf("Digite apenas números para o código do produto!\n");
				codigocorreto=false;
				break;
			}
		}
		if(codigocorreto){
			break;
		}
	} while(1);

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

    printf("\nProduto com código '%s':\n",codigodigitado);
    printf("----------------------------------\n");
	bool produtoencontrado = false;

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove a quebra de linha
        linha[strcspn(linha, "\n")] = 0;
        
		nome = strtok(linha,";");
		codigo=strtok(NULL,";");
		
		if(codigo != NULL && strcmp(codigodigitado,codigo)==0){
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
	            printf("  Código: %s\n", codigo);
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
    char *nome, *codigo, *valor, *qtd, *gener, *remed;
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
        codigo = strtok(NULL, ";");
        valor = strtok(NULL,";");
        qtd = strtok(NULL,";");
        
        if(atoi(qtd)<10){
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
 	           printf("  Código: %s\n", codigo);
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
    
	char cpfCliente[12], codigoProduto[10], linha[200];
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
    
    bool codigocorreto = false;
	do{
	    printf("Digite o código do produto: ");
    	scanf("%s", codigoProduto);
    	while (getchar() != '\n');
    	int i;
    	for(i=0;i<strlen(codigoProduto);i++){
			if(isdigit(codigoProduto[i])){
				codigocorreto=true;
			}else{
				printf("Digite apenas números para o código do produto!\n");
				codigocorreto=false;
				break;
			}
		}
		if(codigocorreto){
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
        char *codigo  = strtok(NULL, ";");

        if (codigo  != NULL && strcmp(codigo , codigoProduto) == 0) {
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
                    fprintf(arquivoTemp, "%s;%s;%.2f;%d;%s;%s", nome, codigo, preco, novaQtd, remedioStr, genericoStr);

                    // Abre o arquivo de vendas para adicionar o registro
                    arquivoVendas = fopen("vendas.txt", "a");
                    if (arquivoVendas != NULL) {
                        fprintf(arquivoVendas, "CPF: %s;Código: %s;Produto: %s;Qtd vendida: %d;Valor unidade: %.2f;Total: %.2f\n",
                                cpfCliente, codigo, nome, qtdVendida, preco, preco * qtdVendida);
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
        printf("\nERRO: Produto com código '%s' não encontrado!\n", codigoProduto);
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


void DeletarCliente(){
	system("cls");
	
	FILE *arquivocliente,*tempcliente;
	char cpf[12], linha[200];
	bool exclusaocorreta=false;
	
	do{
		printf("Digite o CPF do cliente a ser excluído: ");
		fgets(cpf,sizeof(cpf),stdin);
		cpf[strcspn(cpf,"\n")]=0;
		int i;
		bool cpfcorreto = false;
		for(i=0;i<strlen(cpf);i++){
			if(!isdigit(cpf[i])){
				printf("Digite apenas números para o cpf!\n");
				cpfcorreto=false;
				break;
			}else{
				cpfcorreto=true;
			}
		}
		if(cpfcorreto){
			if (!validarCliente(cpf)) {
 		     		printf("\nERRO: Cliente com CPF '%s' não foi encontrado!\n", cpf);
   		 		}else{
    				break;
				}
		}
	}while(1);
	
	arquivocliente = fopen("clientes.txt","r");
	tempcliente = fopen("tempcliente.txt","w");
	
    if (arquivocliente == NULL || tempcliente == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de clientes.\n");
        if(arquivocliente) fclose(arquivocliente);
        if(tempcliente) fclose(tempcliente);
        system("pause");
        return;
    }
    
    while (fgets(linha, sizeof(linha), arquivocliente) != NULL) {
        char linhaOriginal[200];
        strcpy(linhaOriginal, linha);

        char *nome = strtok(linha, ";");
        char *cpf_  = strtok(NULL, ";");

        if (strcmp(cpf_ , cpf) == 0) {
            exclusaocorreta = true;

            printf("\nExclusão concluída!\n");                            
        } else {
            fputs(linhaOriginal, tempcliente); 
        }
    }
    fclose(arquivocliente);
    fclose(tempcliente);

    if (!exclusaocorreta) {
        remove("tempcliente.txt");
    }else {
        remove("clientes.txt");
        rename("tempcliente.txt","clientes.txt");
    }

    system("pause");
}

void DeletarProduto(){
	system("cls");
	
	FILE *arquivoprodutos,*tempprodutos;
	char codigo[10], linha[200];
	bool exclusaocorreta=false,produtoencontrado=false;
	
	do{
		printf("Digite o código do produto a ser excluído: ");
		fgets(codigo,sizeof(codigo),stdin);
		codigo[strcspn(codigo,"\n")]=0;
		int i;
		bool codigocorreto = true;
		for(i=0;i<strlen(codigo);i++){
			if(!isdigit(codigo[i])){
				printf("Digite apenas números para o código!\n");
				codigocorreto=false;
				break;
			}else{
				codigocorreto=true;
			}
		}
		if(codigocorreto){
			break;
		}
	}while(1);
	
	arquivoprodutos = fopen("produtos.txt","r");
	tempprodutos = fopen("tempprodutos.txt","w");
	
    if (arquivoprodutos == NULL || tempprodutos == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de produtos.\n");
        if(arquivoprodutos) fclose(arquivoprodutos);
        if(tempprodutos) fclose(tempprodutos);
        system("pause");
        return;
    }
    
    while (fgets(linha, sizeof(linha), arquivoprodutos) != NULL) {
        char linhaOriginal[200];
        strcpy(linhaOriginal, linha);

        char *nome = strtok(linha, ";");
        char *codigo_  = strtok(NULL, ";");

        if (codigo_ != NULL && strcmp(codigo_ , codigo) == 0) {
            exclusaocorreta = true;
            produtoencontrado=true;

            printf("\nExclusão concluída!\n");                            
        } else {
            fputs(linhaOriginal, tempprodutos); 
        }
    }
    fclose(arquivoprodutos);
    fclose(tempprodutos);

	if (!produtoencontrado) {
        printf("\nERRO: Produto com código '%s' não encontrado!\n", codigo);
        remove("tempprodutos.txt"); // Apaga o arquivo temporário pois nada mudou
    } else if(exclusaocorreta) {
        // substitui o arquivo antigo pelo novo
        remove("produtos.txt");
        rename("tempprodutos.txt", "produtos.txt");
    } else {
        // Se o produto foi encontrado mas a venda falhou, apaga o temp
        remove("tempprodutos.txt");
    }

    system("pause");
}

void listarVendas(){
    system("cls");
    
    FILE *arquivo;       
    char linha[200];     
    int numVenda = 1;    
  
    arquivo = fopen("vendas.txt", "r");  

    if (arquivo == NULL) {
        printf("Nenhuma venda foi registrada ainda ou erro ao abrir arquivo!\n");
        system("pause");
        return; 
    }

    printf("\n===== LISTA DE VENDAS REGISTRADAS =====\n");
    printf("----------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        
        linha[strcspn(linha, "\n")] = 0;
        
        printf("Venda %d:\n", numVenda);
        
      
        char *pos = linha;   
        printf("  ");        
       
        while (*pos != '\0') {  
            
            if (*pos == ';') {             
                printf("\n  ");            
            } else {                        
                printf("%c", *pos);        
            }
            pos++;                         
        }
        
        
        printf("\n");                                
        printf("----------------------------------------\n"); 
        numVenda++;                                      
    }

    fclose(arquivo);
    system("pause");
}

void deletarVenda(){
    system("cls");
    
    FILE *arquivoVendas, *tempVendas, *arquivoProdutos, *tempProdutos;
    char linha[200], linhaVendaExcluida[200];
    int numeroVenda, contadorVenda = 1;
    bool exclusaoCorreta = false;
    char codigoProdutoExcluido[10];
    int qtdVendidaExcluida = 0;
    
    printf("===== VENDAS REGISTRADAS =====\n");
    printf("-------------------------------\n");
    
    arquivoVendas = fopen("vendas.txt", "r");
    if (arquivoVendas == NULL) {
        printf("Nenhuma venda registrada ou erro ao abrir arquivo!\n");
        system("pause");
        return;
    }
    
    while (fgets(linha, sizeof(linha), arquivoVendas) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        printf("Venda %d: %s\n", contadorVenda, linha);
        contadorVenda++;
    }
    fclose(arquivoVendas);
    
    if (contadorVenda == 1) {
        printf("Nenhuma venda encontrada!\n");
        system("pause");
        return;
    }
    
    printf("-------------------------------\n");
    
    do {
        printf("Digite o número da venda a ser excluída (1 a %d): ", contadorVenda - 1);
        scanf("%d", &numeroVenda);
        while (getchar() != '\n');
        
        if (numeroVenda < 1 || numeroVenda >= contadorVenda) {
            printf("Número inválido! Digite um número entre 1 e %d.\n", contadorVenda - 1);
        } else {
            break;
        }
    } while(1);
    
    arquivoVendas = fopen("vendas.txt", "r");
    tempVendas = fopen("tempvendas.txt", "w");
    
    if (arquivoVendas == NULL || tempVendas == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de vendas.\n");
        if(arquivoVendas) fclose(arquivoVendas);
        if(tempVendas) fclose(tempVendas);
        system("pause");
        return;
    }
    
    contadorVenda = 1;
    
    // Copia todas as vendas exceto a que deve ser excluída
    while (fgets(linha, sizeof(linha), arquivoVendas) != NULL) {
        if (contadorVenda != numeroVenda) {
            fputs(linha, tempVendas);
        } else {
            strcpy(linhaVendaExcluida, linha);
            
            // Formato: CPF: xxx;Código: xxx;Produto: xxx;Qtd vendida: xxx;Valor unidade: xxx;Total: xxx
            char *token = strtok(linhaVendaExcluida, ";");

            token = strtok(NULL, ";");
            if (token != NULL) {
                sscanf(token, "Código: %s", codigoProdutoExcluido);
            }
            
            token = strtok(NULL, ";");
            token = strtok(NULL, ";"); 
            if (token != NULL) {
                sscanf(token, "Qtd vendida: %d", &qtdVendidaExcluida);
            }
            
            printf("\nVenda %d excluída! Devolvendo %d unidades do produto código %s ao estoque.\n", 
                   numeroVenda, qtdVendidaExcluida, codigoProdutoExcluido);
        }
        contadorVenda++;
    }
    
    fclose(arquivoVendas);
    fclose(tempVendas);
    
    if (exclusaoCorreta) {
        arquivoProdutos = fopen("produtos.txt", "r");
        tempProdutos = fopen("tempprodutos_venda.txt", "w");
        
        if (arquivoProdutos == NULL || tempProdutos == NULL) {
            printf("ERRO: Não foi possível abrir o arquivo de produtos para atualizar estoque.\n");
            if(arquivoProdutos) fclose(arquivoProdutos);
            if(tempProdutos) fclose(tempProdutos);
            system("pause");
            return;
        }
        
        while (fgets(linha, sizeof(linha), arquivoProdutos) != NULL) {
            char linhaOriginal[200];
            strcpy(linhaOriginal, linha);
            
            char *nome = strtok(linha, ";");
            char *codigo = strtok(NULL, ";");
            
            if (codigo != NULL && strcmp(codigo, codigoProdutoExcluido) == 0) {
                char *precoStr = strtok(NULL, ";");
                char *qtdStr = strtok(NULL, ";");
                char *remedioStr = strtok(NULL, ";");
                char *genericoStr = strtok(NULL, ";");
                
                int qtdAtual = atoi(qtdStr);
                int novaQtd = qtdAtual + qtdVendidaExcluida; 
                float preco = atof(precoStr);
                
                fprintf(tempProdutos, "%s;%s;%.2f;%d;%s;%s", nome, codigo, preco, novaQtd, remedioStr, genericoStr);
                printf("Estoque atualizado: %s agora tem %d unidades.\n", nome, novaQtd);
            } else {
                fputs(linhaOriginal, tempProdutos);
            }
        }
        
        fclose(arquivoProdutos);
        fclose(tempProdutos);
        
        // Substitui os arquivos
        remove("vendas.txt");
        rename("tempvendas.txt", "vendas.txt");
        
        remove("produtos.txt");
        rename("tempprodutos_venda.txt", "produtos.txt");
        
        printf("\nOperação concluída com sucesso!\n");
    } else {
        remove("tempvendas.txt");
    }
    
    system("pause");
}
