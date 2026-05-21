// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Pedro Alan de Santana Alves
//  E-mail pessoal: alanzito006@gmail.com
//  E-mail institucional: 20252160031@ifba.edu.br
//  Matrícula: 20252160031
//  Semestre: 2026.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);
DataQuebrada validarData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
*/

int q1(char data[])
{
    DataQuebrada dq = validarData(data);

    return dq.valido;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
*/

int checarDataMaior(DataQuebrada di, DataQuebrada df){
    long long int diInt = di.iAno*10000 + di.iMes*100 + di.iDia;
    long long int dfInt = df.iAno*10000 + df.iMes*100 + df.iDia;

    if(diInt > dfInt){
        return 0;
    }
    return 1;
}

int checarMes(int m){
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12){
        return 1;
    }
    
    if(m == 4 || m == 6 || m == 5 || m == 9 || m == 11){
        return 2;
    }

    if(m == 2){
        return 3;
    }
}

DiasMesesAnos diffDatas(DataQuebrada di, DataQuebrada df){
    DiasMesesAnos dma;
    if(checarDataMaior(di, df) == 0){
        dma.retorno = 4;
        return dma;
    }

    dma.qtdAnos = df.iAno - di.iAno;
    dma.qtdMeses = df.iMes - di.iMes;
    dma.qtdDias = df.iDia - di.iDia;
    if(dma.qtdDias < 0){
        dma.qtdMeses--;
        if(checarMes(di.iMes) == 1){
            dma.qtdDias = 31 + dma.qtdDias; 
        }
        else if(checarMes(di.iMes) == 2){
            dma.qtdDias = 30 + dma.qtdDias; 
        }
        else{
            dma.qtdDias = 28 + dma.qtdDias; 
        }
        
    }
    dma.retorno = 1;
    return dma;
}

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    DataQuebrada dI = validarData(datainicial);
    DataQuebrada dF = validarData(datafinal);
    if (dI.valido == 0){
      dma.retorno = 2;
      return dma;
    } 
    if (dF.valido == 0){
      dma.retorno = 3;
      return dma;
    }
    
    dma = diffDatas(dI, dF);
    return dma;
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */

 int charInString(char *s, char c, int isCaseSensitive){
    int occ = 0;

    if(isCaseSensitive == 1){
        for(int i = 0; s[i] != '\0'; i++){
            if(s[i] == c){
                occ++;
            }
        }
    }
    else{
        char aux;

        if(c >= 'a' && c <= 'z'){
            aux = c-32;
        }
        else if(c >= 'A' && c <= 'Z'){
            aux = c+32;
        }

        for(int i = 0; s[i] != '\0'; i++){
            if(s[i] == c || s[i] == aux){
                occ++;
            }
        }
    }

    return occ;
}

int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = charInString(texto, c, isCaseSensitive);

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */

int convertStringInIntArr(char s[250], int v[250]){
    int arrSize = 0;
    
    for(int i = 0; i < strlen(s); i++){
        if(s[i] != -61){
            v[arrSize] = s[i];
            arrSize++;
        }
    }

    return arrSize;
}

 int findSubString(char mainString[250], char subString[250], int pos[30]){
    int occ = 0, l = 0, substringSize = strlen(subString);
    int msIntArr[250], ssIntArr[250], msArrSize, ssArrSize;

    msArrSize = convertStringInIntArr(mainString, msIntArr);
    ssArrSize = convertStringInIntArr(subString, ssIntArr);
   
    for(int i = 0; i < msArrSize; i++){
        int flag = 1;
       
        if(msIntArr[i] == ssIntArr[0]){
            for(int j = 1; j < ssArrSize; j++){
                if(msIntArr[i+j] != ssIntArr[j]){
                    flag = 0;
                    break;
                }
            }
           
            if(flag == 1){
                occ++;
                pos[l] = i + 1;
                pos[l+1] = i + substringSize;
                l = l + 2;
                i = i + substringSize - 1;
            }
        }
    }
   
    return occ;
}

int q4(char strTexto[250], char strBusca[250], int posicoes[30])
{
    int qtdOcorrencias = findSubString(strTexto, strBusca, posicoes);

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int inverterNum(int n){
    if(n < 0){
        return -1;
    }

    int invN = 0, nV[20], mult = 1, count = 0;

    while(n/10 > 0){
        mult = mult*10;
        
        nV[count] = n%10;
        n = n/10;
        count++;
    }

    nV[count] = n%10;
    
    for(int i = 0; i <= count; i++){
        invN += nV[i] * mult;

        if(mult/10 > 0)
            mult = mult/10;
    }

    return invN;
}

int q5(int num)
{
    int invN = inverterNum(num);
    return invN;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int occNum(int n, int b){
    if(n < 0 || b < 0){
        return -1;
    }

    int occ = 0;
    unsigned int nV[20], buscaV[20], multN = 1, countN = 0, multB = 1, countB = 0;

    while(n/10 > 0){
        multN = multN*10;
        
        nV[countN] = n%10;
        n = n/10;
        countN++;
    }

    nV[countN] = n%10;

    while(b/10 > 0){
        multB = multB*10;
        
        buscaV[countB] = b%10;
        b = b/10;
        countB++;
    }

    buscaV[countB] = b%10;

    int flag = 0;
    for(int i = 0; i <= countN; i++){
        flag = 0;

        if(nV[i] == buscaV[0]){
            flag = 1;
            for(int j = 1; j <= countB; j++){
                if(nV[i+j] != buscaV[j]){
                    flag = 0;
                    break;                  
                }
            }
        }

        if(flag == 1)
            occ++;
    }

    return occ;
}

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = occNum(numerobase, numerobusca);
    return qtdOcorrencias;
}

/*
    Q7 = jogo busca palavras
    @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
    @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
    @saida
    1 se achou 0 se não achou
*/

int cacaPalavras(char m[8][10], char s[6]){
    int flag;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 10; j++){
            if(m[i][j] == s[0]){
                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(i+k > 8 || m[i+k][j] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}

                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(i-k < 0 || m[i-k][j] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}

                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(j+k > 10 || m[i][j+k] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}

                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(j-k < 0 || m[i][j-k] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}

                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(i+k > 8 || j+k > 10 || m[i+k][j+k] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}

                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(i-k < 0 || j-k < 0 || m[i-k][j-k] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}

                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(i-k < 0 || j+k > 10 || m[i-k][j+k] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}

                flag = 1;
                for(int k = 1; k < 5; k++){
                    if(i+k > 8 || j-k > 0 || m[i+k][j-k] != s[k]){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1){return 1;}
            }
        }
    }

    return 0;
}

int q7(char matriz[8][10], char palavra[6]){
    int achou = cacaPalavras(matriz, palavra);
    return achou;
}



DataQuebrada validarData(char data[]){
    DataQuebrada dq = quebraData(data);

    if(dq.valido == 1){
        if(dq.iDia < 1 || dq.iDia > 31){
            dq.valido = 0;
            return dq;
        }
        if(dq.iMes < 1 || dq.iMes > 12){
            dq.valido = 0;
            return dq;
        }

        int isBissexto = 0;

        if(dq.iAno/1000 == 0){
            dq.iAno = dq.iAno + 2000;
        }

        if((dq.iAno % 4 == 0 && dq.iAno % 100 != 0) || (dq.iAno % 400 == 0)){
            isBissexto = 1;
        }

        if(dq.iMes == 4 || dq.iMes == 6 || dq.iMes == 9 || dq.iMes == 11){
            if(dq.iDia <= 30){
                return dq;
            }
            dq.valido = 0;
            return dq;
        }

        if(dq.iMes == 2){
            if(isBissexto == 1){
                if(dq.iDia <= 29){
                    return dq;
                }
                dq.valido = 0;
                return dq;
            }
            else{
                if(dq.iDia <= 28){
                    return dq;
                }
                dq.valido = 0;
                return dq;
            }
        }

        return dq;
    }
    else{
        return dq;
    }
}

DataQuebrada quebraData(char data[]){
    DataQuebrada dq;
    char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
        if(data[i] >= '0' && data[i] <= '9'){
            sDia[i] = data[i];	
        }
        else{
            dq.valido = 0;
            return dq;
        }
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}
    else {
		dq.valido = 0;
        return dq;
    }  
	
	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
        if(data[j] >= '0' && data[j] <= '9'){
            sMes[i] = data[j];	
            i++;
        }
        else{
            dq.valido = 0;
            return dq;
        }
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}
    else {
		dq.valido = 0;
        return dq;
    }
	
	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
        if(data[j] >= '0' && data[j] <= '9'){
            sAno[i] = data[j];
            i++;	
        }
        else{
            dq.valido = 0;
            return dq;
        }
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}
    else {
		dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno); 

    dq.valido = 1;
    
    return dq;
}
