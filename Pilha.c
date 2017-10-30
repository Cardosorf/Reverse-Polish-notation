#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct _tno{
    int key;
    struct _tno *next;
} tno;

enum boolean{False, True};

void init(tno *); /* Inicializa com Null o ponteiro do tipo tno que sera responsavel por apontar para o ultimo elemento da pilha */
int empty(tno *); /* Verifica se o ponteiro do tipo tno se encontra vazio*/
void push(tno *, int); /* Adiciona os elementos na pilha e faz o ponteiro do tipo tno apontar para o elemento adicionado */
void pop(tno *); /* Remove o ultimo elemento da pilha e faz o ponteiro do tipo tno apontar para o elemento seguinte */
int validate_exp(char *); /* Verifica se a expressao e valida */


int main(int argc, char *argv[])
{
    tno *numbers;
    char * exp;
    tno *operators;
    int i, j, count = 0;
    char valores[50];

    exp = (char *)malloc(sizeof(char)*50);
    numbers = (tno *)malloc(sizeof(tno));
    operators = (tno *)malloc(sizeof(tno));

    if(!numbers && !exp && !operators){
        puts("Erro de alocacao!");
        exit(1);
    }

    init(numbers);
    init(operators);
    puts("Insera a expressao");
    scanf("%[^\n]s", exp);


    /* Verifica se a expressao e valida */
    if(validate_exp(exp)){
        for(i = 0; i < (int)strlen(exp); i++){
            j = i;
            /* Identica o numero ou uma sequencia de numeros */
            while(isdigit(exp[i])){
                count++;
                i++;
            }
            if(count != 0){
                /* Pega a posicao em que se encontra o numero ou a sequencia de numeros,
                     copia para uma variavel e adiciona o numero na pilha */
                strncpy(valores, exp+j, count);
                push(numbers, atoi(valores));
                count = 0;
                memset(valores, '\0', sizeof(valores));
            }

            /* Identifica o operador e o adiciona na pilha de operadores */
            if(exp[i] == '+' || exp[i] == '-' || exp[i] == '/' || exp[i] == '*' || exp[i] == 'x'){
                push(operators, (int)exp[i]);
            }

            /* Ao encontrar um ')' resolve a expressao utilizando o ultimo operador passado para a pilha de operadores
                e os 2 ultimos numeros que se encontram na pilha numerica. Ao resolver, a pilha e atualizada com o novo
                valor e os numeros e operadores utilizados sao removidos da pilha */
            if(exp[i] == ')'){
                switch((char)operators->next->key){
                    case '+' :
                    numbers->next->next->key += numbers->next->key;
                    pop(numbers);
                    pop(operators);
                    break;

                    case '-' :
                    numbers->next->next->key -= numbers->next->key;
                    pop(numbers);
                    pop(operators);
                    break;

                    case 'x' :
                    case '*' :
                    numbers->next->next->key *= numbers->next->key;
                    pop(numbers);
                    pop(operators);
                    break;

                    case '/' :
                    numbers->next->next->key /= numbers->next->key;
                    pop(numbers);
                    pop(operators);
                    break;
                }
            }
        }
    }

    else{
        puts("Expressao invalida.");
    }

    printf("Resultado da expressao: %d\n", numbers->next->key);

    free(numbers);
    free(operators);
    free(exp);
    return 0;
}


/* Inicializa com Null o ponteiro do tipo tno que sera responsavel por apontar para o ultimo elemento da pilha */
void init(tno *stack){
    stack->key = (int)NULL;
    stack->next = NULL;
}


/* Verifica se o ponteiro do tipo tno se encontra vazio*/
int empty(tno *stack){
    if(stack->next == NULL && stack->key == (int)NULL)
        return True;
    else
        return False;
}


/* Adiciona os elementos na pilha e faz o ponteiro do tipo tno apontar para o elemento adicionado */
void push(tno *stack, int value){
    tno *temp;
    temp = (tno *)malloc(sizeof(tno));
    if(!temp){
        puts("Erro de alocacao!");
        exit(1);
    }

    if(empty(stack)){
        temp->key = value;
        temp->next = NULL;
        stack->next = temp;
    }
    else{
        temp->key = value;
        temp->next = stack->next;
        stack->next = temp;
    }
}


/* Remove o ultimo elemento da pilha e faz o ponteiro do tipo tno apontar para o elemento seguinte */
void pop(tno* stack){
    if(empty(stack))
        return;
    else{
        tno* temp;
        temp = (tno*)malloc(sizeof(tno));
        if(!temp){
            puts("Erro de alocação!");
            exit(1);
        }
        stack->next = stack->next->next;
    }
}


/* Verifica se a expressao e valida */
int validate_exp(char *exp){
    int count = 0,i;

    for(i = 0; i < (int)strlen(exp); i++){
        if(exp[i] == '(')
            count++;
        else if(exp[i] == ')')
            count --;
    }
    if (count!= 0)
        return False;
    else
        return True;
}
