#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "sqlite3.h"
#define SQL_OK 0

static sqlite3 * db;

/*
  所有返回值为int类型的返回值表示操作成功与否，0表示失败，1表示成功
 */

//初始化数据库
void init_db();

//关闭数据库
void close_db();

//向用户数据表中插入用户信息，参数分别为用户ID,用户名，密码以及用户头像ID
int insert_userinfo (int userID, char * username, char * password, int image);

//向好友数据表中插入用户信息，参数分别为当前用户ID,他的好友ID,好友用户名
//和好友头像ID
int insert_friend(int id, int friend_id, char * friend_name, int image_id);

//删除好友，参数分别为当前用户ID和被删好友ID
int delete_friend(int id, int friend_id);

//更新用户数据表，参数分别为用户ID，用户名，用户密码和用户头像ID
int update_user(int id, char * username, char * password, int image_id);

//用户信息展示函数，根据用户ID查找信息
//resValue为一个指向二维数组的地址，二维数组负责存放数据库放回信息
//nrow和ncol分别为返回结果的行数和列数
int show_user(int id, char *** resValue, int * nrow, int * ncol);

//好友显示函数，根据用户ID查找他的所有好友
//resValue为一个指向二维数组的地址，二维数组负责存放数据库返回信息
//nrow和ncol分别为返回结果的行数和列数
int show_friend(int id, char *** resValue, int * nrow, int * ncol);

//插入消息记录，参数分别为消息ID，发送方用户ID，接收方用户ID，内容以及时间
int insert_message(int message_id, int from_id, int to_id, char * content,
		char * time);

//显示聊天记录，可以根据ID查找用户收到和发送的聊天记录，按照消息ID升序排列
//resValue为一个指向二维数组的地址，二维数组负责存放数据库返回信息
//nrow和ncol分别为返回结果的行数和列数
int show_message(int id, char *** resValue, int * nrow, int *col);

/*
接口使用示例：
char ** resValue;
	int nrow;
       	int ncol;	
	init_db();
	insert_userinfo(2,"123","123",1);插入用户信息
	insert_friend(1,2,"123",1);插入好友信息
	delete_friend(1,2);删除好友信息
	update_user(1,"234","321",1);更新用户信息
	show_user(2,&resValue,&nrow,&ncol);显示用户信息
	for (int i=4;i<4+nrow*ncol;i++)打印用户信息查询结果
	{
		puts(resValue[i]);
	}
	show_friend(1,&resValue,&nrow,&ncol);显示好友信息
	for (int i=4;i<4+nrow*ncol;i++)
		puts(resValue[i]);
	insert_message(1,1,2,"12431234","10:00:00");插入消息信息
	insert_message(2,2,1,"asdfasdf","10:00:01");
	show_message(1,&resValue,&nrow,&ncol);显示消息信息
	for (int i=5;i<5+nrow*ncol;i++)
		puts(resValue[i]);	
*/
