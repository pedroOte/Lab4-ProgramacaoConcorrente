/* 
Pedro Luis Mello Otero
DRE: 121074528
*/

#ifndef _leitorescritor_H_
#define _leitorescritor_H_


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//declaração das variáveis globais
extern int nEscrita; 
extern int nLeitura;
extern pthread_cond_t condEscrita;
extern pthread_cond_t condLeitura;
extern pthread_mutex_t mutex;

int iniciaEscrita(){
	pthread_mutex_lock(&mutex);
	while(nEscrita > 0 || nLeitura > 0)
		pthread_cond_wait(&condEscrita, &mutex);
	nEscrita++;
	pthread_mutex_unlock(&mutex);
}	

int terminaEscrita(){
	pthread_mutex_lock(&mutex);
	nEscrita--;
	pthread_cond_signal(&condEscrita);
	pthread_cond_broadcast(&condLeitura);
	pthread_mutex_unlock(&mutex);
}

int iniciaLeitura(){
	pthread_mutex_lock(&mutex);
	while(nEscrita > 0)
		pthread_cond_wait(&condLeitura, &mutex);
	nLeitura++;
	pthread_mutex_unlock(&mutex);
}

int terminaLeitura(){
	pthread_mutex_lock(&mutex);
    nLeitura--;
    if (nLeitura == 0)
		pthread_cond_signal(&condEscrita);
	pthread_mutex_unlock(&mutex);
}


#endif