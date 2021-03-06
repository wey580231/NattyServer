/*
 *  Author : WangBoJing , email : 1989wangbojing@gmail.com
 * 
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of Author. (C) 2016
 * 
 *
 
****       *****
  ***        *
  ***        *                         *               *
  * **       *                         *               *
  * **       *                         *               *
  *  **      *                        **              **
  *  **      *                       ***             ***
  *   **     *       ******       ***********     ***********    *****    *****
  *   **     *     **     **          **              **           **      **
  *    **    *    **       **         **              **           **      *
  *    **    *    **       **         **              **            *      *
  *     **   *    **       **         **              **            **     *
  *     **   *            ***         **              **             *    *
  *      **  *       ***** **         **              **             **   *
  *      **  *     ***     **         **              **             **   *
  *       ** *    **       **         **              **              *  *
  *       ** *   **        **         **              **              ** *
  *        ***   **        **         **              **               * *
  *        ***   **        **         **     *        **     *         **
  *         **   **        **  *      **     *        **     *         **
  *         **    **     ****  *       **   *          **   *          *
*****        *     ******   ***         ****            ****           *
                                                                       *
                                                                      *
                                                                  *****
                                                                  ****


 *
 */



#ifndef __DAVE_MQ_H__
#define __DAVE_MQ_H__

#include "NattyAbstractClass.h"
#include "NattyUserProtocol.h"
#include "NattyConfig.h"


#define DAVE_MESSAGE_LENGTH			1024

#define NTY_HTTP_GET_HANDLE_STRING			"GET"
#define NTY_HTTP_POST_HANDLE_STRING			"POST"
#define NTY_HTTP_RET_HANDLE_STRING			"RET"

typedef int (*DAVE_MESSAGE_CALLBACK)(void *arg);


typedef enum {
	MSG_TYPE_START = 0,
	MSG_TYPE_QJK_FALLEN = MSG_TYPE_START,
	MSG_TYPE_WEATHER_API,
	MSG_TYPE_LOCATION_WIFI_API,
	MSG_TYPE_LOCATION_LAB_API,
	MSG_TYPE_FALLDOWN_API,
	MSG_TYPE_GAODE_WIFI_CELL_API,
	MSG_TYPE_VOICE_ACK_HANDLE,
	MSG_TYPE_APP_COMMON_ACK_HANDLE,
	MSG_TYPE_DEVICE_COMMON_ACK_HANDLE,
	MSG_TYPE_VOICE_DATA_REQ_HANDLE,
	MSG_TYPE_VOICE_REQ_HANDLE,
	MSG_TYPE_BIND_CONFIRM_REQ_HANDLE,
	MSG_TYPE_BIND_CHECK_STATUS_HANDLE,
	MSG_TYPE_BIND_SELECT_ADMIN_HANDLE,
	MSG_TYPE_BIND_JSON_PARSER_HANDLE,
	MSG_TYPE_BIND_PUSH_ADMINISTRATOR_HANDLE,
	MSG_TYPE_VOICE_OFFLINE_READ_HANDLE,
	MSG_TYPE_BIND_OFFLINE_PUSH_HANDLE,
	MSG_TYPE_ONLINE_MSG_REQ_HANDLE,
	MSG_TYPE_OFFLINE_MSG_REQ_HANDLE,
	MSG_TYPE_LOCATION_BROADCAST_HANDLE,
	MSG_TYPE_COMMON_REQ_HANDLE,
	MSG_TYPE_IOS_PUSH_HANDLE,
	MSG_TYPE_LOCATION_GPS_API,
	MSG_TYPE_MTK_QUICKLOCATION,
	MSG_TYPE_END = MSG_TYPE_MTK_QUICKLOCATION,
} MESSAGE_TYPE;

typedef struct _MESSAGETAG {
	MESSAGE_TYPE Type;
#if ENABLE_DAVE_MSGQUEUE_MALLOC
	U8 *Tag;
#else
	U8 Tag[DAVE_MESSAGE_LENGTH];
#endif
	int length;
	int arg;
	C_DEVID fromId;
	C_DEVID toId;
	C_DEVID gId;
	U8 u8LocationType;
#if 1
	DAVE_MESSAGE_CALLBACK cb;
#else
	int (*cb)(void *arg);
#endif
} MessageTag;

//typedef int VALUE_TYPE;
typedef MessageTag VALUE_TYPE;


typedef struct _DaveNode {
	VALUE_TYPE *value;
	struct _DaveNode *next;
	struct _DaveNode *prev;
} DaveNode ;

typedef struct _DaveQueue {
	const void *_;
	DaveNode *head;
	DaveNode *tail;
	DaveNode *nil;
} DaveQueue;

typedef struct _DaveQueueHandle {
	int size;
	void* (*ctor)(void *_self);
	void* (*dtor)(void *_self);
	void (*enqueue)(void *_self, VALUE_TYPE *value);
	void* (*dequeue)(void *_self);
} DaveQueueHandle;

void *ntyDaveMqWorkerInstance(void);
//int ntyClassifyMessageType(C_DEVID fromId, C_DEVID toId, U8 *data, int length);

void ntyDaveMqStart(void);
void ntyDaveMqWorkerInit(void);



int ntyDaveMqPushMessage(VALUE_TYPE *tag);




#endif


