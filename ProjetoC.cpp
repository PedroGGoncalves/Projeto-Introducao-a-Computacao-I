#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Enums
typedef enum e_cor { 	PRETA=1, BRANCA, PRATA } cor;
typedef enum e_categoria {	HATCH =1,SEDAN,SUV,JIPE} categoria_e;

//Union
union opcao {	int x;};

//Structs
typedef struct s_endereco
{
	char rua[50];
	int numero;
	char bairro[50];
	char cidade[50];
} endereco;

typedef struct s_cliente  
{
	char nome[50];
	endereco e;
	char telefone[15];
	int tipo_pessoa;
	char pessoa[20];
	int situacao;	
} cliente;

typedef struct s_carro{
	char renavan[15];
	char placa[15];
	char marca[50];
	char modelo[50];
	int ano;
	cor tipo_cor;
	categoria_e tipo_categoria;
	int situacao;
} carro;

typedef struct s_categoria{
	int categoria;
	float valor;
	int pontos;
} categoria;

typedef struct s_locacao{
	int codigo;
	int tipo_pessoa;
	char pessoa[20];
	char renavan[15];
	int dia_retirada;
	int mes_retirada;
	int ano_retirada;
	int dia_devolucao;
	int mes_devolucao;
	int ano_devolucao;
	int situacao;
	int qtd;
	categoria_e tipo_categoria;
	char nome[50];
} locacao;

//Globais referente ao tamanho dos arrays
const int tam_cliente = 15;
const int tam_carro = 10;
const int tam_categoria = 4;
const int tam_locacao = 5;

//Funções de consulta simples
int consultaTipoCliente (int tipo){
	if (tipo!=1 && tipo!=2){
		printf("ERRO: opcao invalida\n");
		return 0;
	}
	return 1;
}

int consultaCadastroCliente (cliente *c, int **i){
	for (int j=0;j<**i;j++){
		if(strcmp(c[**i].pessoa,c[j].pessoa)==0){
			printf("ERRO: ja cadastrado\n");
			return 0;
		}
	}
	return 1;
}

int consultaCadastroCarro (carro *c, int **i){
	for(int j=0; j<**i;j++){
		if(strcmp(c[**i].renavan,c[j].renavan)==0)
		{
			printf("ERRO: ja cadastrado\n");
			return 0;
		}
	}
	return 1;
}

int consultaCadastroCategoria(categoria *c,int **i){
	for(int j; j<**i;j++){
		if(c[**i].categoria==c[j].categoria)
		{
			printf("ERRO: ja cadastrado\n");
			return 0;
		}
	}
	return 1;
}

int consultaTipoCategoria(carro *c,int **i){
	switch (c[**i].tipo_categoria)
	{
		case HATCH: break;
		case SEDAN: break;
		case SUV: break;
		case JIPE: break;
		default: printf("ERRO: opcao invalida\n"); return 0; 
	}
	return 1;
}

int consultaTipoCategoria2(categoria *c,int **i){
	switch (c[**i].categoria)
	{
		case HATCH: break;
		case SEDAN: break;
		case SUV: break;
		case JIPE: break;
		default: printf("ERRO: opcao invalida\n"); return 0; 
	}
	return 1;
}
//Funções de Cadastro
int cadastrarCliente(cliente *c, int *i){
	//Return 0 - Algum erro //Return 1 Cliente cadastrado com sucesso
	
	int tipo_cliente, valido; 
	printf("Tipo do Cliente:");	scanf("%d",&tipo_cliente);
	
	valido=consultaTipoCliente(tipo_cliente); 
	if(valido==0) //Não é um tipo válido
		return 0;

	c[*i].tipo_pessoa=tipo_cliente;
	printf("CPF/CNPJ:"); 	scanf(" %s",c[*i].pessoa);
	
	valido=consultaCadastroCliente(c,&i);
	if(valido==0) //O Cliente já está cadastrado
		return 0;
	
	if(strlen("XXX.XXX.XXX-XX")==strlen(c[*i].pessoa)) //Confere se tipo da Pessoa digitado - CPF
		tipo_cliente=1;
	else if (strlen("XX.XXX.XXX/XXXX-XX")==strlen(c[*i].pessoa)) //Confere se tipo  da Pessoa digitado - CNPJ
		tipo_cliente=2;

	if(tipo_cliente!=c[*i].tipo_pessoa){ //Confere se tipo informado é igual ao tipo da Pessoa digitado
		printf("ERRO: opcao invalida\n");
		c[*i].tipo_pessoa=0; //limpa variável
		return 0;
	}

	//Recebe entradas para cadastro
	printf("Nome:");	scanf(" %[^\n]%*c", c[*i].nome);
	printf("Endereço\nRua:"); 	scanf(" %[^\n]%*c", c[*i].e.rua);
	printf("Número:");scanf(" %d",&c[*i].e.numero);
	printf("Bairro:");scanf(" %[^\n]%*c", c[*i].e.bairro);
	printf("Cidade:");scanf(" %[^\n]%*c", c[*i].e.cidade);
	printf("Telefone:");scanf(" %s", c[*i].telefone);
	c[*i].situacao=0; //Situação 0 é Cliente sem Locações em Aberto
	*i = *i + 1; //Aumenta o número de clientes cadastrados
	
	return 1;
}
int cadastrarCarro(carro *c, int *i){
	//Return 0 - Algum erro //Return 1 Cliente cadastrado com sucesso
	
	int valido;
	
	printf("Renavan:");	scanf(" %s",c[*i].renavan);
	
	valido=consultaCadastroCarro(c,&i); 
	if(valido==0) //O Carro já está cadastrado
		return 0;
	
	printf("Categoria"); scanf(" %u",&c[*i].tipo_categoria);
	valido=consultaTipoCategoria(c,&i); 
	if(valido==0) //Tipo invalida
		return 0;
	
	//Validação das cores
	printf("Cor:");		scanf(" %u",&c[*i].tipo_cor);
	if(c[*i].tipo_cor<1 || c[*i].tipo_cor>4){
		printf("ERRO: opcao invalida\n");
		return 0;
	}
	
	//Recebe entradas para cadastro
	printf("Placa:");	scanf(" %s",c[*i].placa);
	printf("Marca:");	scanf(" %[^\n]%*c", c[*i].marca);
	printf("Modelo:");	scanf(" %[^\n]%*c", c[*i].modelo);
	printf("Ano:");		scanf("%d",&c[*i].ano);
	c[*i].situacao=0; //Carro não locado
	*i = *i + 1; ////Aumenta o número de carros cadastrados
	return 1;
}
int cadastrarCategoria(categoria *c, int *i){
	
	int valido;
	
	printf("Categoria:");	scanf(" %d",&c[*i].categoria); 
	
	valido=consultaCadastroCategoria(c,&i); 
	if(valido==0) //A Categoria já está cadastrada
		return 0;
		
	valido=consultaTipoCategoria2(c,&i); 
	if(valido==0) //Tipo invalida
		return 0;
	//Recebe entradas para cadastro
	printf("Valor:");	scanf(" %f",&c[*i].valor);
	printf("Pontos:");	scanf(" %d",&c[*i].pontos);
	*i++;//Aumenta o número de categorias cadastradas
	return 1;
}
	
int cadastrarLocacao(locacao l[][tam_locacao],cliente *cli,int *j,carro *car,int *z, categoria *cat, int k){
	
	char aux_renavan[15],aux_cliente[20];
	int i=0, cont_cliente=0,aux_tipo,mark=0,cont=0,cont_car=0, valido;
	
	printf("Renavan:");	scanf(" %s",aux_renavan);
	
	//Busca Carro e vê se ele já está locado
	for(cont=0; cont<*z;cont++){
		if(strcmp(car[cont].renavan,aux_renavan)==0)
		{
			if(car[cont].situacao==1){
				printf("ERRO: locacao em aberto\n");
				return 0;
			}
			else{
				mark=1;
				cont_car=cont;
				break;
			}
		}
	}
	if(mark==0){ //Se achou o carro ou não
		printf("ERRO: nao cadastrado\n");
		return 0;
	}
	mark=0;
	
	printf("Tipo:");	scanf(" %d",&aux_tipo);
	
	valido=consultaTipoCliente(aux_tipo);
	if(valido==0)
		return 0;
		
	printf("CPF/CNPJ:");	scanf(" %s",aux_cliente);
	
	//Busca Cliente e vê se ele tem locação em aberto
	for(cont=0; cont<*j;cont++){
		if(strcmp(cli[cont].pessoa,aux_cliente)==0)
		{
			if(cli[cont].situacao==1){
				printf("ERRO: locacao em aberto\n");
				return 0;
			}
			else{
				mark=1;
				cont_cliente=cont;
				break;
			}
		}
	}
	if(mark==0){//Se o Cliente está cadastro ou não
		printf("ERRO: nao cadastrado\n");
		return 0;
	}

	for(cont=0; cont<tam_locacao;cont++){
		if(strcmp(l[cont_cliente][cont].pessoa,aux_cliente)==0)
		{
			i++; //Conta quantidade de locações que cliente fez
			break;
		}
	}
	if(i==5){ //Cliente pode ter feito no máximo 5 locações
		printf("ERRO: sem espaco\n");
		return 0;
	}
	
	//Recebe entradas para cadastro
	printf("Data de retirada:\n");
	printf("Dia:");	scanf(" %d",&l[cont_cliente][i].dia_retirada);
	printf("Mês:");	scanf(" %d",&l[cont_cliente][i].mes_retirada);
	printf("Ano:");	scanf(" %d",&l[cont_cliente][i].ano_retirada);
	
	//Preenche alguns áreas do cadastro
	cli[cont_cliente].situacao=1; //Situação 1 é Cliente com Locação em Aberto
	car[cont_car].situacao=1; //Carro locado
	strcpy(l[cont_cliente][i].renavan,aux_renavan); 	//Copia o renavan para a locação
	l[cont_cliente][i].tipo_pessoa=aux_tipo;			//Copia o tipo da pesso para a locação
	strcpy(l[cont_cliente][i].pessoa,aux_cliente);	//Copia o CPF/CNPJ para a locação
	strcpy(l[cont_cliente][i].nome,cli[cont_cliente].nome);	//Copia o nome do cliente para a locação
	l[cont_cliente][i].codigo=k+1001;					//Soma o código de locação para cada cliente novo, começando em 1001
	l[cont_cliente][i].dia_devolucao=0;				//Preenche o dia da devolução com 0
	l[cont_cliente][i].mes_devolucao=0;				//Preenche o mês da devolução com 0
	l[cont_cliente][i].ano_devolucao=0;				//Preenche o ano da devolução com 0
	l[cont_cliente][i].situacao=1;					//Locação em aberto
	l[cont_cliente][i].tipo_categoria=car[cont_car].tipo_categoria; //Copia o tipo da categoria para a locação
	
	printf("%d ",l[cont_cliente][i].codigo);
	return 1;
}

//Funções de alteração de dados
int devolverCarro(locacao l[][tam_locacao], int *i,cliente *cli,int *j,carro *car,int *z, categoria *cat){
	
	char aux_cliente[20];
	int aux_tipo=0,mark=0,valido,cont_cliente,diaria=0;
	
	printf("Tipo:");	scanf(" %d",&aux_tipo);
	
	valido=consultaTipoCliente(aux_tipo);
	if(valido==0)
		return 0;
		
	printf("CPF/CNPJ:");	scanf("%s",aux_cliente);
	
	//Busca Cliente
	for(int cont=0; cont<*j;cont++){
		if(strcmp(cli[cont].pessoa,aux_cliente)==0)
		{
			mark=1;
			cont_cliente=cont;
			break;
		}
	}
	if(mark==0){//Se o Cliente está cadastro ou não
		printf("ERRO: nao cadastrado\n");
		return 0;
	}
	
	for (int cont_locacao=0;cont_locacao<tam_locacao;cont_locacao++){//Procura nas locações do cliente

		if(l[cont_cliente][cont_locacao].situacao==1){ //Tem que ter locação em aberto
			printf("Data devolução:\n");
			printf("Dia:");	scanf("%d",&l[cont_cliente][cont_locacao].dia_devolucao);
			printf("Mês:");	scanf("%d",&l[cont_cliente][cont_locacao].mes_devolucao);
			printf("Ano:");	scanf("%d",&l[cont_cliente][cont_locacao].ano_devolucao);
			
			//Se a data de retirada e locação foram iguais, a locação deve ser cancelada
			if(l[cont_cliente][cont_locacao].dia_devolucao==l[cont_cliente][cont_locacao].dia_retirada &&
			l[cont_cliente][cont_locacao].mes_devolucao==l[cont_cliente][cont_locacao].mes_retirada && 
			l[cont_cliente][cont_locacao].ano_devolucao==l[cont_cliente][cont_locacao].ano_retirada){
				printf("Locacao cancelada\n");
				//Como foi cancelada a data de devolução tem que ser 0/0/0
				l[cont_cliente][cont_locacao].dia_devolucao=0; 
				l[cont_cliente][cont_locacao].mes_devolucao=0;
				l[cont_cliente][cont_locacao].ano_devolucao=0;
				l[cont_cliente][cont_locacao].situacao=2; //Situação 2 é locação cancelada
				
				for(int cont_car=0;cont_car<*z;cont_car++){
					if(strcmp(l[cont_cliente][cont_locacao].renavan,car[cont_car].renavan)==0)
						car[cont_car].situacao=0; //Muda a situação, pois a locação não está mais em aberto
				}
				return 0;
			}
			//Validação da data
			//Dia>=1 e Dia<=31			//Mês>=1 e Mês<=12
			//Ano de devolução tem quer maior ou igual ao de retirada
			//Se ano igual, mês de devolução tem quer ser maior ou igual ao de retirada
			//Se ano e mês iguais, dia de devolução tem que ser maior ao de retirada
			if((l[cont_cliente][cont_locacao].dia_devolucao<1 || l[cont_cliente][cont_locacao].dia_devolucao>31 
			|| l[cont_cliente][cont_locacao].mes_devolucao>12 || l[cont_cliente][cont_locacao].mes_devolucao<1
			)|| ((l[cont_cliente][cont_locacao].ano_devolucao<l[cont_cliente][cont_locacao].ano_retirada) || 
			(l[cont_cliente][cont_locacao].ano_devolucao==l[cont_cliente][cont_locacao].ano_retirada 
			&& l[cont_cliente][cont_locacao].mes_devolucao<l[cont_cliente][cont_locacao].mes_retirada)  
			|| ((l[cont_cliente][cont_locacao].ano_devolucao==l[cont_cliente][cont_locacao].ano_retirada 
			&& l[cont_cliente][cont_locacao].mes_devolucao==l[cont_cliente][cont_locacao].mes_retirada 
			&& l[cont_cliente][cont_locacao].dia_devolucao<l[cont_cliente][cont_locacao].dia_retirada)))){
				printf("ERRO: data invalida\n");
				//Como data invalida, não foi devolvido e nem cancelada, assim a data de devolução tem que ser 0/0/0
				l[cont_cliente][cont_locacao].dia_devolucao=0;
				l[cont_cliente][cont_locacao].mes_devolucao=0;
				l[cont_cliente][cont_locacao].ano_devolucao=0;
				for(int cont_car=0;cont_car<*z;cont_car++){
					if(strcmp(l[cont_cliente][cont_locacao].renavan,car[cont_car].renavan)==0)
						car[cont_car].situacao=0;//Muda a situação, pois a locação não está mais em aberto
				}
				return 0;
			}
			//Se chegou aqui a locação irá ser fechada
			l[cont_cliente][cont_locacao].situacao=0; //Situação 0 sem locação em aberto
			cli[cont_cliente].situacao=0; //Situação 0 sem locação em aberto
			for(int cont_car=0;cont_car<*z;cont_car++){
				if(strcmp(l[cont_cliente][cont_locacao].renavan,car[cont_car].renavan)==0){ //Busca carro locado
					car[cont_car].situacao=0; //Carro foi devolvido, não está locado
										
					//Cálculo do tempo de locação (Devolução-retirada)
					diaria=(l[cont_cliente][cont_locacao].ano_devolucao-l[cont_cliente][cont_locacao].ano_retirada)*365;
					if(l[cont_cliente][cont_locacao].ano_devolucao>l[cont_cliente][cont_locacao].ano_retirada)//Se ano de devolução é maior
						diaria=diaria-(l[cont_cliente][cont_locacao].mes_retirada-l[cont_cliente][cont_locacao].mes_devolucao)*30;
					else //Se ano de devolução é igual
						diaria=diaria+(l[cont_cliente][cont_locacao].mes_devolucao-l[cont_cliente][cont_locacao].mes_retirada)*30;
					if(l[cont_cliente][cont_locacao].mes_devolucao>l[cont_cliente][cont_locacao].mes_retirada) //Se mês é maior
						diaria=diaria-(l[cont_cliente][cont_locacao].dia_retirada-l[cont_cliente][cont_locacao].dia_devolucao);
					else //Se mês é igual
						diaria=diaria+(l[cont_cliente][cont_locacao].dia_devolucao-l[cont_cliente][cont_locacao].dia_retirada);
					for(int cont_cat=0;cont_cat<tam_categoria;cont_cat++){ //Busca categoria do carro (1-4)
						if(car[cont_car].tipo_categoria==cat[cont_cat].categoria){ 
							float valor=0;
							valor =diaria*cat[cont_cat].valor;
							printf("Valor devido: %.2f\n", valor);//Valor de pagamento é total de dias * valor da categoria do carro
							float x=0;
							if(cont_locacao>0){
								for(int cont_car=0;cont_car<*z;cont_car++){
									if(strcmp(l[cont_cliente][cont_locacao-1].renavan,car[cont_car].renavan)==0){
										for(int cont_cat=0;cont_cat<tam_categoria;cont_cat++){
											if (cat[cont_cat].pontos>=1000) //Para ter desconto os pontos da categoria tem que ser maior que 1000
											{
												x = (cat[cont_cat].pontos/1000)*50; //Cálculo do desconto
												if(x>0.3*valor) //Valor do desconto não pode ser superior à 30% do valor total
													x=(valor)*0.3;
											}
										}
									}
								}
							}
							printf("Desconto: %.2f\n", x);	
						}
					}
					break;
				}
			}
			return 1; //Carro devolvido com sucesso
		}
	}
	printf("ERRO: nenhuma locacao em aberto\n");	
	return 0;
}
int atualizarCliente(cliente *c, int *i){
	
	int tipo, valido, op;
	char pessoa[20];
	
	printf("Tipo:");	scanf("%d",&tipo);
	
	valido=consultaTipoCliente(tipo);
	if(valido==0)
		return 0;
	
	printf("CPF/CNPJ:");	scanf(" %s",pessoa);
	
	for(int j=0;j<*i;j++){
		if(strcmp(c[j].pessoa,pessoa)==0){ //Se Pessoa está cadastrada

			printf("Opção: (1)Atualizar endereço ou (2)Atualizar telefone");	scanf("%d",&op);
			if(op==1){
				printf("Endereço:\n");
				printf("Rua:");		scanf(" %[^\n]%*c", c[j].e.rua);
				printf("Número:");	scanf(" %d",&c[j].e.numero);
				printf("Bairro:");	scanf(" %[^\n]%*c", c[j].e.bairro);
				printf("Cidade:");	scanf(" %[^\n]%*c", c[j].e.cidade);
				return 1;
			}
			else if(op==2){
				printf("Telefone:");	scanf(" %s", c[j].telefone);
				return 1;
			}
			printf("ERRO: opcao invalida\n");
			return 0;
		}	
	}
	printf("ERRO: nao cadastrado\n");	
	return 0;
}

//Funções de consultar e listar
int exibirLocacao (locacao l[][5], int *j, int *z){ //Printar dados consultados
	printf("codigo da locacao: %d\n",l[*j][*z].codigo);
	if(strlen("XXX.XXX.XXX-XX")==strlen(l[*j][*z].pessoa))//Vê se é CPF
		printf("cpf: %s\n",l[*j][*z].pessoa);
	else if (strlen("XX.XXX.XXX/XXXX-XX")==strlen(l[*j][*z].pessoa)) //Ou CNPJ
		printf("cnpj: %s\n",l[*j][*z].pessoa);
	printf("nome: %s\n", l[*j][*z].nome);
	printf("renavam: %s\n",l[*j][*z].renavan);
	printf("data retirada: %02d/%02d/%02d\n",l[*j][*z].dia_retirada,l[*j][*z].mes_retirada,l[*j][*z].ano_retirada);
	printf("data entrega: %02d/%02d/%02d\n",l[*j][*z].dia_devolucao,l[*j][*z].mes_devolucao,l[*j][*z].ano_devolucao);
	return 0;
}

int consultarCliente(cliente *c, int *i){
	
	int tipo,valido;
	char pessoa[50];
	
	printf("Tipo:");	scanf("%d",&tipo);
	
	valido=consultaTipoCliente(tipo);
	if(valido==0)
		return 0;
	
	printf("CPF/CNPJ:");	scanf(" %s",pessoa);
	
	for(int j=0;j<*i;j++){
		if(strcmp(c[j].pessoa,pessoa)==0){//Se Pessoa está cadastrada
			printf("nome: %s\n",c[j].nome);
			printf("rua: %s\n",c[j].e.rua);
			printf("num: %d\n",c[j].e.numero);
			printf("bairro: %s\n",c[j].e.bairro);
			printf("cidade: %s\n",c[j].e.cidade);
			printf("telefone: %s\n",c[j].telefone);
			return 1;
		}
	}
	printf("ERRO: nao cadastrado\n");
	return 0;
}

int consultarLocacao(locacao l[][5], int *i){
	
	int codigo;
	printf("Código da locação:");	scanf("%d",&codigo);
	
	for(int j=0;j<*i;j++){
		for(int z=0;z<tam_locacao;z++){
			if(codigo==l[j][z].codigo){
				if(l[j][z].situacao==2){//Vê se locação foi cancelada
					printf("ERRO: locacao foi cancelada\n");
					return 0;
				}
				exibirLocacao(l,&j,&z);
				return 1;
			}
		}
	}
	printf("ERRO: nao cadastrado\n");
	return 0;
}
int listarLocacoesCliente(locacao l[][5], int *i){
	
	char nome[20];
	int tipo, valido, mark=0, op;
	
	printf("Tipo:");	scanf("%d",&tipo);
	
	valido=consultaTipoCliente(tipo);
	if(valido==0)
		return 0;
		
	printf("CPF/CNPJ:");	scanf(" %s",nome);

	for(int j=0;j<*i;j++){
		for(int z=0;z<tam_locacao;z++){
			if(strcmp(nome,l[j][z].pessoa)==0){ //Vê se pessoa está cadastrada
				printf("%s %s\n",nome,l[j][z].pessoa);
				mark=1;
				break;
			}
		}
	}
	if(mark==1){ //Pessoa está cadastrada
		printf("Opção: (1)Todas locações, (2)Encerradas ou (3)Em aberto");	scanf("%d",&op);
		if(op>3 || op<1){
			printf("ERRO: opcao invalida\n");
			return 0;
		}
		for(int j=0;j<*i;j++){
			for(int z=0;z<tam_locacao;z++){
				if(op==1){
					if(strcmp(nome,l[j][z].pessoa)==0 &&l[j][z].situacao!=2){//Todas locações, menos as canceladas
						exibirLocacao(l,&j,&z);
						return 1;
					}
				}
				else if(op==2){
					if(strcmp(nome,l[j][z].pessoa)==0 && l[j][z].situacao==0){//Locações encerradas
						exibirLocacao(l,&j,&z);
						return 1;
					}
				}
				else{
					if(strcmp(nome,l[j][z].pessoa)==0 && l[j][z].situacao==1){//Locações em aberto
						exibirLocacao(l,&j,&z);
						return 1;
					}
				}
			}
		}
	}
	printf("ERRO: nao cadastrado\n");
	return 0;
}

int listarLocacoesAbertas(locacao l[][5], int *i){
	
	int tipo,valido,mark=0;
	
	printf("Tipo:");	scanf("%d",&tipo);
	
	valido=consultaTipoCliente(tipo);
	if(valido==0)
		return 0;
		
	for(int j=0;j<*i;j++){
		for(int z=0;z<tam_locacao;z++){
			if(1==l[j][z].situacao && l[j][z].codigo>1000){ //Locação aberta e códigos são válidos apenas se maior que 1000
				exibirLocacao(l,&j,&z);
				mark=1;
			}
		}
	}
	if(mark!=0) //Listagem foi um sucesso
		return 1;
		
	printf("ERRO: nenhum dado cadastrado\n");
	return 0;
}
//Outras funções
int frequenciaLocacaoCategoria(locacao l[][5],carro *c,categoria *cat, int *i){
	
	int tipo,aux,valido,vetor[4]={0,0,0,0},v[4]={1,2,3,4},aux2;
	
	scanf("%d",&tipo);
	valido=consultaTipoCliente(tipo);
	if(valido==0)
		return 0;
		
	int j=0,z=0,p=0,teste=0;

	for(j=0;j<15;j++){
		for(z=0;z<tam_locacao;z++){
			if(l[j][z].tipo_pessoa==tipo &&l[j][z].situacao!=2) //Vê se o tipo é compatível e se a locação não foi cancelada
				vetor[l[j][z].tipo_categoria-1]++; //Soma +1, na posição correspondente a categoria - Posição 0 = Categoria 1, e é a mesma lógica pro resto
		}
	}

	for (int i=0; i<tam_categoria-1; i++) //Irá ordenar o vetor em ordem crescente
	{       
        if(vetor[i]<vetor[i+1])
		{
          	 aux=vetor[i+1];
             vetor[i+1]=vetor[i];
             vetor[i]=aux;
             
             aux2=v[i+1]; //Também irá o vetor correspondente as categorias (1 a 4), afim de auxiliar na exibição
             v[i+1]=v[i];
             v[i]=aux2;
        }  
	}
	for (int i=0;i<4;i++) //Exibição das frequências da categoria em ordem crescente
	{
		if (v[i]==1) 
			printf("Categoria hatch: %d\n", vetor[i]);
		else if (v[i]==2)
			printf("Categoria sedan: %d\n", vetor[i]);	
		else if (v[i]==3)
			printf("Categoria suv: %d\n", vetor[i]);	
		else if (v[i]==4)
			printf("Categoria jipe: %d\n", vetor[i]);
	}
	return 0;
}

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int retorno,cont_cliente=0,cont_car=0,cont_cat=0,contando=0,cont_loc=0,tam_matriz=0;
	union opcao op;
	
	cliente c[tam_cliente];
	carro car[tam_carro];
	categoria cat[tam_categoria];
	locacao loc[tam_cliente][tam_locacao];

	//Limpando lixos de memória
	for(int i=0;i<tam_cliente;i++)
		strcpy(c[i].pessoa," ");
	
	for(int i=0;i<tam_categoria;i++)
		for(int j=0;j<tam_locacao;j++)
			loc[i][j].codigo=0;
	
	do 	
	{
		printf("-------------------------------------------\n");
		printf("1-Cadastro de Cliente\n");
		printf("2-Atualiza cliente\n");
		printf("3-Lista os dados de um dado cliente\n");
		printf("4-Cadastro de Carro\n");
		printf("5-Cadastro de Dados da Categoria\n");
		printf("6-Cadastro de Locação\n");
		printf("7-Devolve Carro\n");
		printf("8-Lista dados de uma determinada locação\n");
		printf("9-Lista locações de um dado cliente\n");
		printf("10-Lista locações em aberto\n");
		printf("11-Frequência de locação por categoria\n");
		printf("0-Sair\n");
		printf("-------------------------------------------\n");	
		printf("Digite uma opção:");
		scanf (" %d",&op.x);
		switch(op.x){
		case 1:
			{
				if(cont_cliente<tam_cliente){
					retorno = cadastrarCliente(c,&cont_cliente);
					if(retorno ==1)
						printf("Cadastrado com Sucesso\n");
				}
				else
					printf("ERRO: sem espaco\n");
			
				break;
			}
		case 2:
			{
				retorno = atualizarCliente(c,&cont_cliente);
				if(retorno ==1)
						printf("Cadastrado com Sucesso\n");
				break;
			}
		case 3:
			{
				retorno = consultarCliente(c,&cont_cliente);
				break;
			}
		case 4:
			{
				if(cont_car<tam_carro){
					retorno = cadastrarCarro(car,&cont_car);
					if(retorno ==1)
						printf("Cadastrado com Sucesso\n");
				}
				else
					printf("ERRO: sem espaco\n");
				break;
			}
		case 5:
			{
				cont_cat=contando;
				retorno = cadastrarCategoria(cat,&cont_cat);
					if(retorno ==1){
						printf("Cadastrado com Sucesso\n");
						contando++;
				}
				break;
			}
		case 6:
			{
				if(tam_matriz<15*5){
					retorno = cadastrarLocacao(loc,c,&cont_cliente,car,&cont_car,cat,tam_matriz);
					if(retorno ==1){
						printf("Cadastrado com Sucesso\n");
						tam_matriz=tam_matriz+1;
					}
				}
				else
					printf("ERRO: sem espaco\n");

				break;
			}
		case 7:
			{
				devolverCarro(loc,&cont_loc,c,&cont_cliente,car,&cont_car,cat);
				break;
			}
		case 8:
			{
				consultarLocacao(loc,&cont_cliente);
				break;
			}
		case 9:
			{
				listarLocacoesCliente(loc,&cont_cliente);
				break;
			}
		case 10:
			{
				listarLocacoesAbertas(loc,&cont_cliente);
				break;
			}
		case 11:
			{
				frequenciaLocacaoCategoria(loc,car,cat,&cont_cliente);
				break;
			}
		case 0:
			{
				printf("Saindo...");
				break;
			}
		default:
			{
				printf("ERRO: opcao invalida\n");
				break;
			}
	}
		printf("\n");
	} while (op.x!=0);		
}
