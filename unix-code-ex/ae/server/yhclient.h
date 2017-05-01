/**
 * 在服务端，保存客户端状态信息使用，每次更新。 
 * 实时用户信息的数据结构
 * 
 * yuhao@~
 * 2014.1.27
 */

#ifndef YH_CLIENT_H
#define YH_LCIENT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "zmalloc.h"
#include "anet.h"
#include "yhlog.h"

#define IP_STR_LEN 16
#define CUID_SIZE 32
#define CLIENT_DATA_SIZE 64
#define BUF_SIZE 1024

typedef struct yhclient {
	char cuid[CUID_SIZE];
	char os[8];

	char cip[IP_STR_LEN];
	int cport;

	int cellId[4];
	double lng;
	double lat;
	long long geohash;

	time_t ctime;
	time_t lastinteraction;

	int fd;
	char data[CLIENT_DATA_SIZE];
} yhclient;

yhclient* createClient(int fd){
	yhclient* c = (yhclient*)zmalloc(sizeof(yhclient));
	c->fd = fd;

	anetNonBlock(NULL,fd);
	anetEnableTcpNoDelay(NULL,fd);
	anetKeepAlive(NULL, fd, 1);

	return c;
}

void freeClient(yhclient * c){
	zfree(c);
}

void setKeyVal(yhclient* c, char* key, char* value){
	printf("key:%s,val:%s\n", key, value);
	if(strcmp(key, "cuid")==0){
		memcpy(c->cuid, value, CUID_SIZE);
	} else if(strcmp(key, "mcc")==0){
		c->cellId[0] = atoi(value);	
	} else if(strcmp(key, "mnc")==0){
		c->cellId[1] = atoi(value);	
	} else if(strcmp(key, "lac")==0){
		c->cellId[2] = atoi(value);
	} else if(strcmp(key, "cid")==0){
		c->cellId[3] = atoi(value);
	}
}

void copyStr(char* dest, char* start, char* end){
	char * tmp = start;
	while(tmp != end){
		*dest++ = *tmp++;
	}
}

void processBuf(char* buf, yhclient* c){
	
    yhDebug("\nclient info: %s, %d, %d, %d, %d\n", c->cuid, c->cellId[0], c->cellId[1], c->cellId[2], c->cellId[3]);
}


#endif

