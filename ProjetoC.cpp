/*atenção tem um problema na situação do carro (alugado, devolvido), que ainda nao foi corrigida*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	char pessoa[20];
	int situacao;	
} cliente;

typedef enum e_cores { PRETA=1, BRANCA, PRATA } cores;

typedef enum e_categorias {	HATCH =1,SEDAN,SUV,JIPE	} categorias;

typedef struct s_carro 
{
	char renavam[15];
	char placa[15];  
	char marca[50];
	char modelo[50];
	int ano;
	int cor; 
	int categoria; 
} carro;

typedef struct u_categorias 
{
	int c;	
	float valor;
	int pontos;
	
} categorias_u;	
typedef struct s_locacao
{
	int codigo;
	int  tipo_cliente;
	char pessoa[20]; 
	char renavan[15]; 
	int dia;
	int mes;
	int ano;
	int devolucaodia;
	int devolucaomes;
	int devolucaoano;
	int situacao;
	int contador;
	
}locacao;

union opcao
{
	int x;
};

int cadastra_cliente (cliente *c,int *pos,locacao l[][5])
{
	int i=*pos,j,aux;
	
	scanf(" %d",&aux);
	if (aux!=1 && aux!=2)
	{	
		return 2;
	}
	scanf(" %s", c[i].pessoa);
	
	for (j=0; j<*pos; j++)
	  	  	if (strcmp(c[i].pessoa,c[j].pessoa)==0)
	  	  	  return 0;
	
	if (strlen("XXX.XXX.XXX-XX")==strlen(c[i].pessoa))
	{
		l[i][0].tipo_cliente=1;
	}
	else if (strlen("XX.XXX.XXX/XXXX-XX")==strlen(c[i].pessoa))
	{
		l[i][0].tipo_cliente=2;
	}

	scanf(" %[^\n]%*c", c[i].nome);
	scanf(" %[^\n]%*c", c[i].e.rua);
	scanf(" %d",&c[i].e.numero);
	scanf(" %[^\n]%*c", c[i].e.bairro);
	scanf(" %[^\n]%*c", c[i].e.cidade);
	scanf(" %s", c[i].telefone);
	c[i].situacao=0;
	*pos = *pos + 1;
	return 1;
}
int cadastra_carro (carro *car,int *pos)
{
	int i=*pos, j;
	
	scanf(" %s", car[i].renavam);
	
	for (j=0; j<*pos; j++)
	  	  	if (strcmp(car[i].renavam,car[j].renavam)==0)
	  	  	  return 0;
		
	scanf(" %d",&car[i].categoria);
	
	switch (car[i].categoria) 
		{
			case HATCH: break; 
			case SEDAN: break;
			case SUV: break;
			case JIPE: break;
			default: return 2;
		}
	scanf(" %d",&car[i].cor);  
	switch (car[i].cor)
		{
			case PRETA: break;
			case BRANCA: break;
			case PRATA: break;
			default: return 2;
		}
	
	scanf(" %s", car[i].placa);
	scanf(" %[^\n]%*c", car[i].marca);
	scanf(" %[^\n]%*c", car[i].modelo);
	scanf (" %d",&car[i].ano);
	
	*pos = *pos + 1;
	return 1;
}
int cadastra_categoria(categorias_u *cat,int *pos)
{
	int i= *pos, j;
	
	scanf(" %d",&cat[i].c);
	
	for (j=0; j<*pos; j++)
	  	  	if (cat[i].c==cat[j].c)
	  	  	  return 0;
	
	switch (cat[i].c)
	{
		case HATCH: break;
		case SEDAN: break;
		case SUV: break;
		case JIPE: break;
		default: return 2;
	}
	scanf(" %f",&cat[i].valor);     
	scanf(" %d",&cat[i].pontos);  
	
	*pos = *pos + 1;	
	return 1;
}

int cadastra_loc(locacao l[][5],int *pos,int *poss,cliente *c,carro *car, int *v, int *cod,int *ve,int *conti,int *carr) 
{
	int i=*pos, j=*poss,k=0,z=0,cont=0,aux=0;
	char pessoa[20];
	
	scanf (" %s", l[i][j].renavan);
	for (k=0;k<15;k++)
	{
		for (z=0;z<5;z++)
		{
			
			if (strcmp (l[i][j].renavan,l[k][z].renavan)==0)
			{
				
				if (l[k][z].situacao==2)
				{
					for (k=0; k<*carr; k++)
					{
					if (strcmp (l[i][j].renavan,car[k].renavam)==0)
					{	
					v[k]=0;
					}
				
					}
				}
			}
		}
	}
	
	for (k=0; k<*carr; k++)
	{
		if (strcmp (l[i][j].renavan,car[k].renavam)==0)
		{
			cont = 1;
			v[k]=v[k]+1;
			l[i][j].contador=car[k].categoria;
			if (v[k]>1)
			{
				printf ("ERRO!: locacao em aberto\n");
				printf("k:%d",&k);
				return 4;
			}
			break;
		}
	}

	if (cont==0)
	{
		return 0;
	} cont=0;
	
	scanf (" %d",&aux); 
	
	if (aux!=1 && aux!=2) 
	{
		for (k=0; k<*carr; k++)
	{
		if (strcmp (l[i][j].renavan,car[k].renavam)==0)
		{
			v[k]=v[k]-1;
			break;
		}
	}	return 2;
	}

	scanf(" %s", pessoa); 
	
	for (k=0;k<*pos;k++)
	{
		for (z=0;z<*poss;z++)
		{
			if (strcmp (l[i][j].renavan,l[k][z].renavan)==0)
			{
				ve[k]=0;
				if (l[k][z].situacao==2)
				{
					for (k=0; k<*conti; k++)
					{
						printf ("aaaaaa");
					if (strcmp (pessoa,c[k].pessoa)==0)
					{
					ve[k]=0;
					printf("AAA%s",c[k].pessoa);
					}
					}
				}
			}
		}
	}
	for(k=0;k<*conti;k++) //att erro no ve[k] por algum motivo tem 1 e n era pra ter
	{
		printf("%d %sc \n",ve[k],c[k].pessoa);
	}
	for (k=0; k<*conti; k++)
	{
		
		if (strcmp (pessoa,c[k].pessoa)==0)
		{
			cont = 1;
			c[k].situacao=1;
			printf("%d %da\n",ve[k],k);
			ve[k]=ve[k]+1;
			printf("%d %da\n",ve[k],k);
			if (ve[k]>1)
			{
				for (k=0; k<*carr; k++)
				{
				if (strcmp (l[i][j].renavan,car[k].renavam)==0)
				{
				v[k]=v[k]-1;
			
				break;
				}
				}
				printf ("ERRO: locacao em aberto\n");
				printf("k:%d\n",k);
				return 4;
			} 		
			break;
		}
	}
	if (cont==0)
	{
		for (k=0; k<*carr; k++)
	{
		if (strcmp (l[i][j].renavan,car[k].renavam)==0)
		{
			v[k]=v[k]-1;
			
			break;
		}
	}
		return 0; 
	}
	cont=0;
	
	l[i][j].situacao =1;
	l[i][j].tipo_cliente=aux;
	l[i][j].codigo=1001+*cod;
	strcpy (l[i][j].pessoa,pessoa);
	scanf (" %d", &l[i][j].dia);
	scanf (" %d", &l[i][j].mes);
	scanf (" %d", &l[i][j].ano);
	l[i][j].devolucaodia=0;
	l[i][j].devolucaomes=0;
	l[i][j].devolucaoano=0;
	
	*poss = *poss + 1;
	if (j==15)
	{
		*pos = *pos + 1;
		*poss=0;
	}
	*cod= *cod+1;
	printf ("%d ",l[i][j].codigo);
	return 3;
}

int atualiza_cliente (cliente *c, int *pos)
{
	int i=0,cont=0,pessoa,submenu=0;
	
	char aux[15];
	scanf (" %d",&pessoa);
	if (pessoa!=1 && pessoa!=2)
	{
		printf("ERRO: opcao invalida\n");
		return 2;
	}
	scanf(" %s", aux);
	
	for (i=0;i<*pos;i++)
	{
		if (strcmp(aux,c[i].pessoa)==0) 
		{
			scanf (" %d",&submenu);	
		if (submenu==1)
		{
		scanf(" %[^\n]%*c", c[i].e.rua);
		scanf(" %d",&c[i].e.numero);
		scanf(" %[^\n]%*c", c[i].e.bairro);
		scanf(" %[^\n]%*c", c[i].e.cidade);
		cont=1;
		}
		else if (submenu==2)
		{
		scanf(" %s", c[i].telefone);
		cont=1;
		}
		else 
		{
			printf("ERRO: opcao invalida\n");
			return 2;
		}
		}	
	}
	if (cont==0)
	{
		printf("ERRO: nao cadastrado\n");
		return 1;
	}
	return 0;
}

int mostra_cliente (cliente *c, int *pos)
{
	int i=0,pessoa=0,cont=0;
	char aux[15];
	
	scanf (" %d",&pessoa);
	if (pessoa!=1 && pessoa!=2)
	{
		printf ("ERRO: opcao invalida\n");
		return 2;
	}
	scanf(" %s", aux);

	for (i=0;i<*pos;i++)
	{
		if (strcmp(aux,c[i].pessoa)==0) 
		{
			printf ("nome: %s\n",c[i].nome);
			printf ("rua: %s\n",c[i].e.rua);
			printf ("num: %d\n",c[i].e.numero);
			printf ("bairro: %s\n",c[i].e.bairro);
			printf ("cidade: %s\n",c[i].e.cidade);
			printf ("telefone: %s\n",c[i].telefone);
			cont =1;
			break;
		}
	}
	if (cont==0)
	{
		printf("ERRO: nao cadastrado\n");
	}
	return 0;
}

int mostra_locacao (locacao l[][5],cliente *c, int *pos,int *poss) 
{
	int i=0,j=0,k=0,cont=0;
	int aux;
	
	scanf(" %d",&aux);

	for (i=0;i<*pos;i++)
	{
		for (j=0;j<*poss;j++)
		{
			if (aux==l[i][j].codigo)
			{
				cont=1;
				if (l[i][j].contador !=0)
				{
					for (k=0;k<*pos;k++)
				{
					if (strcmp(l[i][j].pessoa,c[k].pessoa)==0)
					{
						printf ("codigo da locacao: %d\n",l[i][j].codigo);
						printf("cpf: %s\n",l[i][j].pessoa);
						printf ("nome: %s\n",c[k].nome);
						printf("renavam: %s \n",l[i][j].renavan); 
						if (l[i][j].mes>=1 && l[i][j].mes<=9)
						{
							printf("data retirada: %d/0%d/%d\n",l[i][j].dia,l[i][j].mes,l[i][j].ano); 
						}
						else
						{
							printf("data retirada: %d/%d/%d\n",l[i][j].dia,l[i][j].mes,l[i][j].ano); 
						}
						printf ("data entrega: %02d/%02d/%02d\n",l[i][j].devolucaodia,l[i][j].devolucaomes,l[i][j].devolucaoano);
						return 3;
					}
				}
				}	
			}
		}
	}
	if (cont==0)
	{
		return 1;
	}
	return 2;
}
int locacao_cliente(cliente *c,locacao l[][5],int *pos,int *poss) 
{
	int i=0,j=0,aux2=0,cont=0,contt=0,k=0;
	
	char aux[15];
	scanf(" %d", &aux2);
	if (aux2!=1 && aux2!=2)
	{
		printf("ERRO: opcao invalida\n"); 
		return 0;
	}
	scanf(" %s", aux);
	scanf(" %d", &aux2); 
	for (i=0;i<*pos;i++)
	{
		for (j=0;j<*poss;j++)
		{
			if (strcmp(aux,l[i][j].pessoa)==0)
			{
				contt=1;
				if (l[i][j].codigo==0)
				{
					printf ("ERRO: nada cadastrado\n");
					return 3;
				}
				
				if (aux2!=1 && aux2!=2 && aux2!=3)
				{
					printf ("ERRO: opcao invalida\n");
					return 3;
				}
				else if (aux2==1)
				{
							
							printf ("codigo da locacao: %d\n",l[i][j].codigo);
							printf("cpf: %s\n",l[i][j].pessoa);
							for (k=0;k<*pos;k++)
							{
								if (strcmp(c[k].pessoa,l[i][j].pessoa)==0)
								{
								printf ("nome: %s\n",c[k].nome);
								}
							}
							printf("renavam: %s\n",l[i][j].renavan); 
							printf("data retirada: %02d/%02d/%d\n",l[i][j].dia,l[i][j].mes,l[i][j].ano); 
							printf("data entrega: %02d/%02d/%02d\n",l[i][j].devolucaodia,l[i][j].devolucaomes,l[i][j].devolucaoano); 
							return 3;
					
				}
				else if (aux2==2)
				{
					if (l[i][j].situacao==2)
					{
							printf ("codigo da locacao: %d\n",l[i][j].codigo);
							printf("cpf: %s\n",l[i][j].pessoa);
							for (k=0;k<*pos;k++)
							{
								if (strcmp(c[k].pessoa,l[i][j].pessoa)==0)
								{
								printf ("nome: %s\n",c[k].nome);
								}
							}
							printf("renavam: %s\n",l[i][j].renavan); 
							printf("data retirada: %02d/%02d/%d\n",l[i][j].dia,l[i][j].mes,l[i][j].ano); 
							printf("data entrega: %02d/%02d/%02d\n",l[i][j].devolucaodia,l[i][j].devolucaomes,l[i][j].devolucaoano); 
					}
					else if (l[i][j].situacao==1) 
					{
							printf ("ERRO: nada cadastrado\n");
							return 3;
					}
				}
				else if (aux2==3)
				{
					if (l[i][j].situacao==1)
					{
							printf ("codigo da locacao: %d\n",l[i][j].codigo);
							printf("cpf: %s\n",l[i][j].pessoa);
							for (k=0;k<*pos;k++)
							{
								if (strcmp(c[k].pessoa,l[i][j].pessoa)==0)
								{
								printf ("nome: %s\n",c[k].nome);
								}
							}
							printf("renavam: %s\n",l[i][j].renavan); 
							printf("data retirada: %02d/%02d/%d\n",l[i][j].dia,l[i][j].mes,l[i][j].ano); 
							printf("data entrega: %02d/%02d/%02d\n",l[i][j].devolucaodia,l[i][j].devolucaomes,l[i][j].devolucaoano); 
							return 3;
					}
					else if (l[i][j].situacao==2)
					{
							printf ("ERRO: nada cadastrado\n");
					}
				}
				cont =1;
				break;
			}
		}
	}

	if (contt==0)
	{
		printf ("ERRO: nao cadastrado\n");
		return 0;
	}
	if (cont==0)
	{
		printf ("ERRO: nenhuma locacao em aberto\n");
		return 0;
	}
	return 3;
	
}
int lista(cliente *c,locacao l[][5],int *posss,int*pos,int *poss)
{
	int i=0,j=0,k=0,aux,cont=0;
	scanf(" %d", &aux);
	if (aux!=1 && aux!=2)
	{
		printf("ERRO: opcao invalida\n"); 
		return 0;
	}
	
	for (k=0;k<*posss;k++)
	{
	for (i=0;i<*pos;i++)
	{
		for (j=0;j<*poss;j++)
		{
			if (strcmp(c[k].pessoa,l[i][j].pessoa)==0)
			{
				if (cont==0) 
				{
						printf ("codigo da locacao: %d\n",l[i][j].codigo);
						printf("cpf: %s\n",l[i][j].pessoa);
						printf ("nome: %s\n",c[k].nome);
						printf("renavam: %s \n",l[i][j].renavan); 
						if (l[i][j].mes>=1 && l[i][j].mes<=9)
						{
						printf("data retirada: %d/0%d/%d\n",l[i][j].dia,l[i][j].mes,l[i][j].ano);	
						}
						else
						{
							printf("data retirada: %d/%d/%d\n",l[i][j].dia,l[i][j].mes,l[i][j].ano);
						}
						printf ("data entrega: %02d/%02d/%02d\n",l[i][j].devolucaodia,l[i][j].devolucaomes,l[i][j].devolucaoano); //acho q aki muda
						cont=1;
				}										
			}	
			}	
		}
		cont=0;
	}
	return 0;
}
int devolve (locacao l[][5],carro *car,cliente *c,categorias_u *cat,int *pos,int *poss,int *posss,int *pis,int *pjs,int *v,int *ve)
{
	int i=0,j=0,aux,cont=0,dia,mes,ano,k=0,z=0,cc=0,diaria=0,d=0,m=0,a=0,contt=0;
	float x=0;
	char aux2[15];
	scanf(" %d", &aux);
	if (aux!=1 && aux!=2)
	{
		printf("ERRO: opcao invalida\n"); 
		return 4;
	}
	
	scanf(" %s", aux2);
	for (i=0;i<*pos;i++)
	{
		if (strcmp (aux2,c[i].pessoa)==0)
		{
			cont=1;
		}
	}
	if (cont==0)
	{
		printf("ERRO: nao cadastrado\n");
		return 0;
	}cont=0;
	for (i=0;i<*pos;i++)
	{
		for (j=0;j<*pjs;j++)
		{
			if (strcmp(aux2,l[i][j].pessoa)==0) 
		{
			if (l[i][j].situacao==2)
			{
				contt=contt+1;
				
			}
			
		}
		}
	}
	
	for (i=0;i<*pos;i++)
	{
		for (j=0;j<*pjs;j++)
		{
			if (strcmp(aux2,l[i][j].pessoa)==0) 
		{
			cont =1;
			
			scanf(" %d", &dia);
			scanf(" %d", &mes);
			scanf(" %d", &ano);
			if (ano == l[i][j].ano && mes == l[i][j].mes && dia == l[i][j].dia)
			{
				printf ("Locacao cancelada\n");
				l[i][j].codigo=0; 
				
				return 0; 
			}
			if ((ano < l[i][j].ano) || (ano ==l[i][j].ano && mes< l[i][j].mes) ||( ano==l[i][j].ano && mes==l[i][j].mes && dia < l[i][j].dia))
			{
				printf("ERRO: data invalida\n");
				
				return 0;
			}
			else
			{
				d=l[i][j].dia;
				m=l[i][j].mes;
				a=l[i][j].ano;
				do
				{
					do
					{
						if (m==mes)
						{
							diaria=diaria+dia-1;
							d=29;
						}
						if (l[i][j].mes==mes)
						{
							diaria=mes-l[i][j].mes-1;
							d=29;
							m=mes+1;
							a=ano+1;
						}
						do
						{
							diaria++;
							d++;
						}while(d<30);
						d=0;
						m++;
						
					}while (m<=mes);
					m=1;
					a++;
				}while(a<=ano);
				
				for (k=0;k<*poss;k++)
				{
					
					if (strcmp(l[i][j].renavan,car[k].renavam)==0 && cc==0)
					{
						
						for (z=0;z<*posss;z++)
						{
							
							if(car[k].categoria==cat[z].c)
							{
								
								l[i][j].situacao=2; 
								printf("Valor devido: %.2f\n", cat[z].valor*diaria); 
								if (cat[z].valor*diaria>=1000 &&cat[z].pontos>=1500) 
								{
									if (contt!=0)
										x = (cat[z].pontos/1500)*50;
									
								}
								printf("Desconto: %.2f\n", x); 
								
								l[i][j].devolucaodia=dia;
								l[i][j].devolucaomes=mes;
								l[i][j].devolucaoano=ano;
								l[i][j].contador=0; 
								cc=1;
								v[k]=0;
								printf("k:%d vk:%d",k,v[k]);
								ve[k]=-2;
								printf("ve%d\n",ve[k]);
								//teste
								strcpy(l[i][j].renavan," ");
								strcpy(l[i][j].pessoa," ");
								strcpy(c[k].pessoa," ");
								return 0;
					}
				}
			}
	}
}
			break;
		}
		}
	}
	if (cont==0)
	{
		printf("ERRO: nenhuma locacao em aberto\n");
	}
	return 4;
}

int frequencia (locacao l[][5],carro *car,int *pos,int *poss,int *posss)
{
	int i,j,x11=0,aux=0,vet[*posss]={0,0,0,0},v[*posss]={1,2,3,4},aux2=0;
	
	scanf (" %d",&aux);
	if (aux!=1 && aux!=2)
	{
		printf ("Opcao invalida\n");
		return 0;
	}
	if (*pos==0)
	{
		i=*pos;
		for (j=0;j<*poss;j++)
		{
			if(l[i][j].tipo_cliente==1 && aux==1)
			{
				if (l[i][j].contador==1)
					vet[0]=vet[0]+1;
				else if (l[i][j].contador==2)
					vet[1]=vet[1]+1;
				else if (l[i][j].contador==3)
					vet[2]=vet[2]+1;
				else if (l[i][j].contador==4)
					vet[3]=vet[3]+1;
			}
		}
	}else 
	{
		for (i=0;i<*pos;i++)
	{
		for (j=0;j<*poss;j++)
		{
			if(l[i][j].tipo_cliente==1)
			{
				printf ("%d\n",l[i][j].codigo);
				x11++;
			}
		}
	}
	}
	for (i=0; i<*posss-1; i++)
	{       
        if(vet[i]<vet[i+1])
		{
          	 aux=vet[i+1];
             vet[i+1]=vet[i];
             vet[i]=aux;
             
             aux2=v[i+1];
             v[i+1]=v[i];
             v[i]=aux2;
        }  }
	for (i=0;i<*posss;i++)
	{
		if (v[i]==1) 
			printf("Categoria hatch: %d\n", vet[i]);
		else if (v[i]==2)
			printf("Categoria sedan: %d\n", vet[i]);	
		else if (v[i]==3)
			printf("Categoria suv: %d\n", vet[i]);	
		else if (v[i]==4)
			printf("Categoria jipe: %d\n", vet[i]);
	}return 0;
}

int main ()
{
	const int c_cli = 15;
	const int c_car =10;
	const int  c_loc=5;
	int c_cat =4;
	cliente c[c_cli];
	carro   car[c_car];
	locacao	l[c_cli][c_loc];
	categorias_u cat[c_cat];
	int cont_c=0,cont_car=0,cont_cat=0,ret,cont_i=0,cont_j=0,vet[c_cli],cont_cod=0,vett[c_cli];
	union opcao op;
	do 
	{
		scanf (" %d",&op.x);			
		switch (op.x)
	{
		case 1:	
			{
				if (cont_c<c_cli)
				{
					ret = cadastra_cliente (c,&cont_c,l);
					if (ret==0)
					{
						printf("ERRO: ja cadastrado\n");
					}
					else if (ret==2)
					{
						printf("ERRO: opcao invalida\n");
						break;
					}
					else
					{
						printf("Cadastrado com Sucesso\n");
					}
				}
				else printf("ERRO: sem espaco\n");
				break;
			}
		case 2: 
			{
				ret = atualiza_cliente(c,&cont_c);
				if (ret==0)
				{
					printf("Cadastrado com Sucesso\n");
				}
				break; 
			}
		case 3:	
			{
				mostra_cliente (c,&cont_c);
				break;
			}
		case 4: 
			{
				if (cont_car<c_car)
				{
					ret = cadastra_carro (car,&cont_car);
					if (ret==0)
					{
						printf("ERRO: ja cadastrado\n");
					}
					else if (ret==2)
					{
						printf("ERRO: opcao invalida\n");
						break;
					}
					else printf("Cadastrado com Sucesso\n");
				}
				else printf("ERRO: sem espaco\n");
				break;
			}
		case 5: 
			{
				if (cont_cat<c_cat)
				{
					ret =cadastra_categoria(cat,&cont_cat); 
					if (ret==0)
					{
						break;
					}
					if (ret==2)
					{
						printf("ERRO: opcao invalida\n");
						break;
					}
					else printf("Cadastrado com Sucesso\n"); break;
				}
				else printf("ERRO: opcao invalida\n"); break;
			}
		case 6: 
			{
				ret = cadastra_loc(l,&cont_i,&cont_j,c,car,vet,&cont_cod,vett,&cont_c,&cont_car);
				if (ret==0)
				{
					printf("ERRO: nao cadastrado\n");
					break;
				}
				else if (ret==2)
				{
					printf("ERRO: opcao invalida\n");
					break;
				}
				else if (ret==1)
				{
					printf("ERRO: sem espaco\n");
				}
				else if (ret==3)
				{
					printf("cadastrado com sucesso\n");
				}
				break;
			}
		case 7: 
			{
				ret =devolve (l,car,c,cat,&cont_c,&cont_car,&cont_cat,&cont_i,&cont_j,vet,vett);
				break;
			}
		case 8:
			{
				ret =mostra_locacao (l,c,&cont_c,&cont_j); 
				if (ret==1)
				{
					printf("ERRO: nao cadastrado\n");
				}
				if (ret==2)
				{
					printf("ERRO: locacao foi cancelada\n");
				}
				break;
			}
		case 9: 
			{
				locacao_cliente(c,l,&cont_c,&cont_j);
				break;
			}
		case 10: 
			{
				lista(c,l,&cont_car,&cont_c,&cont_j);
				break;
			}
		case 11:
			{
				frequencia (l,car,&cont_i,&cont_j,&c_cat); 
				break;
			}
		case 0:
			{	
				break;
			}
		default: {
			printf("ERRO: opcao invalida\n"); 
			break;
		}
	}
	}while (op.x!=0);
}
