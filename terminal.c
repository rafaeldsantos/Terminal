/*
Nome: Rafael Santos
Nome: Davy Souza
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAX 256
#define TRUE 1
#define FALSE 0


int main() {
	char comando[MAX], copia[MAX];
	int pid, count=0;
	char *parmList[30];
	char *token;
	FILE *fp;
	char aux;
	char nome_arq[30];
	int segundo_plano,i,redirecionamentoIn,redirecionamentoOut, flag;
	while (1) {
		count=0;
		segundo_plano=FALSE;
		redirecionamentoIn = FALSE;
		redirecionamentoOut = FALSE;
		flag = FALSE;
    	printf("> ");
		scanf("%[^\n]", comando);
		getchar();
		strcpy(copia, comando);
		token = strtok(comando," ");
		while(token!=NULL){
			if(strcmp(token,">")==0) break;
			else if(strcmp(token,"<")==0) break;
			parmList[count++] = token;
			token = strtok(NULL," ");


		}
		parmList[count] = NULL;

		if (!strcmp(comando, "exit")) {
		  exit(EXIT_SUCCESS);
		}
		// comando "<"
		//verifica se o comando é execultado em paralelo com o terminal
		for(i=0;copia[i]!='\0';i++){
			if(copia[i]=='&')segundo_plano = TRUE;
			if(copia[i]=='<')redirecionamentoIn = TRUE;
			if(copia[i]=='>')redirecionamentoOut = TRUE;

				if(redirecionamentoOut && copia[i]!=' '&& copia[i]!='>' && !flag){
					strcpy(nome_arq,&copia[i]);
					int x;
					for(x=0;nome_arq[x]!='\0';x++) if(nome_arq[x] == ' '){nome_arq[x]='\0';break;}

					flag = TRUE;
				}
				if(redirecionamentoIn && copia[i]!=' '&& copia[i]!='<' && !flag){
					strcpy(nome_arq,&copia[i]);
					int x;
					for(x=0;nome_arq[x]!='\0';x++) if(nome_arq[x] == ' '){nome_arq[x]='\0';break;}

					flag = TRUE;
				}
		}


    	pid = fork();
		if (pid) {
		  if(segundo_plano == FALSE) waitpid(pid, NULL, 0);
		} else if(pid == 0) {
			if(redirecionamentoOut){
			 fp = freopen(nome_arq, "w+", stdout);
			}
			if(redirecionamentoIn)
				freopen(nome_arq, "r", stdin);
			execvp(parmList[0], parmList);
			printf("Erro ao executar comando!\n");
			exit(EXIT_FAILURE);
		}

	}
	return 0;
}
