#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#define SQL_OK 0

sqlite3 *db;

void init_db()
{
	int rc=sqlite3_open("database.db", &db);
	if (rc != SQL_OK)
	{
		printf("数据库连接失败，请重试！\n");
		printf("return %d\n",rc);
	}
	//数据库连接成功，开始建表
	else
	{
		char * sql_userinfo = "CREATE TABLE USERINFO(" \
				       "ID       INTEGER PRIMARY KEY  NOT NULL,"\
				       "USERNAME TEXT  NOT NULL,"\
				       "PASSWORD TEXT  NOT NULL,"\
				       "IMAGE    INTEGER DEFAULT 1);";

		char * sql_friend = "CREATE TABLE FRIEND("\
				     "HOST_ID     INTEGER  NOT NULL,"\
				     "FRIEND_ID   INTEGER  NOT NULL,"\
				     "FRIEND_NAME TEXT     NOT NULL,"\
				     "IMAGE       INTEGER  NOT NULL,"\
				     "FOREIGN KEY(HOST_ID) REFERENCES USERINFO(ID),"\
				     "PRIMARY KEY(HOST_ID, FRIEND_ID));";

		char * sql_message = "CREATE TABLE MESSAGE(" \
				      "MESSAGEID  INTEGER   PRIMARY KEY    NOT NULL,"\
				      "FROMID     INTEGER   NOT NULL,"\
				      "TOID       INTEGER   NOT NULL,"\
				      "CONTENT    TEXT      NOT NULL,"\
				      "TIME       TEXT      NOT NULL);";

		sqlite3_exec(db, sql_userinfo, NULL, NULL, NULL);
		sqlite3_exec(db, sql_friend, NULL, NULL, NULL);
		sqlite3_exec(db, sql_message, NULL, NULL, NULL);

		printf("table created\n");
	}
}

//关闭数据库
void close_db()
{
	sqlite3_close(db);
}

//往用户表里插入信息，返回成功与否,1表示成功，0表示失败，下同
int insert_userinfo (int userID, char * username, char * password, int image)
{
	int res;//记录sql语句执行结果
	char *sql_insert;//sql语句
	sql_insert= (char *)malloc(500*sizeof(char));
	memset(sql_insert,'\0',sizeof(sql_insert));
	sprintf(sql_insert, "INSERT INTO USERINFO VALUES (\'%d\', \'%s\', \'%s\', \'%d\')",userID, username, password, image);
	char *errmsg;//记录错误信息
	res = sqlite3_exec(db, sql_insert, NULL, NULL,&errmsg);//执行sql语句
	free(sql_insert);
	//数据库更新失败
	if (res!= SQL_OK)
	{
		puts(errmsg);
		return 0;
	}
	//更新成功
	printf("用户信息插入成功！\n");
	return 1;
}

//插入好友关系
int insert_friend(int id, int friend_id, char * friend_name, int image_id)
{
	int res;//记录sql语句返回值
	char *sql_insert;
        sql_insert= (char *)malloc(500*sizeof(char));
	char * errmsg;//错误信息
	memset(sql_insert,'\0',sizeof(sql_insert));
	sprintf(sql_insert,"INSERT INTO FRIEND VALUES (\'%d\', \'%d\', \'%s\', \'%d\')", id, friend_id, friend_name, image_id);
	res = sqlite3_exec(db, sql_insert, NULL, NULL, &errmsg);//执行sqlyuju
	free(sql_insert);
	//更新失败
	if (res!=SQL_OK)
	{
		puts(errmsg);
		return 0;
	}
	//更新成功
	printf("好友插入成功！\n");
	return 1;
}

//删除好友关系
int delete_friend(int id, int friend_id)
{
	int res;//记录sql语句返回值
	char *sql_delete;
        sql_delete= (char *)malloc(500*sizeof(char));
	char * errmsg;
	memset(sql_delete, '\0', sizeof(sql_delete));
	sprintf(sql_delete, "DELETE FROM FRIEND WHERE HOST_ID = \'%d\' AND FRIEND_ID = '\%d\'", id, friend_id);//将sql语句复制到sql_delete中
	res = sqlite3_exec(db, sql_delete, NULL, NULL, &errmsg);//执行sql
	free(sql_delete);
	if (res!=SQL_OK)//错误处理
	{
		puts(errmsg);
		return 0;
	}
	printf("删除好友成功！\n");
	return 1;
}


//修改用户表的信息
int update_user(int id, char * username, char * password, int image_id)
{
	int res;//记录sql语句返回值
	char *sql_update;
        sql_update= (char *)malloc(500*sizeof(char));
	char * errmsg;//错误信息
	memset(sql_update, '\0', sizeof(sql_update));
	sprintf(sql_update, "UPDATE USERINFO SET USERNAME = \'%s\', PASSWORD = \'%s\', IMAGE = \'%d\' WHERE ID = '\%d\'", username, password, image_id, id);
	res = sqlite3_exec(db, sql_update, NULL, NULL, &errmsg);//执行sql语句
	free(sql_update);
	if (res!=SQL_OK)//错误处理
	{
		puts(errmsg);
		return 0;
	}
	printf("用户修改成功！\n");
	return 1;
}

//显示用户表信息
int show_user(int id, char *** resValue, int *nrow, int * ncol)
{
	int res;//记录sql返回值
	char *sql_select;
	sql_select=(char *)malloc(500*sizeof(char));
	char * errmsg;//记录错误信息
	memset(sql_select, '\0', sizeof(sql_select));
	sprintf(sql_select, "SELECT * FROM USERINFO WHERE ID = \'%d\'", id);
//       	int nrow;//记录查询结果的数量
//       	int ncol;//记录查询结果有几列
	res = sqlite3_get_table(db, sql_select, resValue, nrow, ncol,&errmsg);//执行查询语句
	free(sql_select);
	if (res!=SQL_OK)//错误处理
	{
		puts(errmsg);
		return 0;
	}
	printf("%d\n",*ncol);
	printf("%d\n",*nrow);
	
//	for (int i=4;i<4+(*ncol)*(*nrow);i++)//打印查询结果
//		puts(resValue[i]);
	printf("用户查询成功！\n");
	return 1;
}

//显示好友表信息
int show_friend(int id, char *** resValue, int *nrow, int * ncol)
{
	int res;
//        char **resValue;//保存查询结果
//	int nrow;//记录查询结果的数量
//	int ncol;//记录查询结果有几列
        char *sql_select;
	sql_select=(char *)malloc(500*sizeof(char));
	char * errmsg;//保存错误信息
        memset(sql_select, '\0', sizeof(sql_select));
        sprintf(sql_select, "SELECT * FROM FRIEND WHERE HOST_ID = \'%d\'", id);
        res = sqlite3_get_table(db, sql_select, resValue, nrow, ncol, &errmsg);//执行查询语句
        free(sql_select);
	if (res!=SQL_OK)//错误处理
	{
		puts(errmsg);
                return 0;
	}
//	for (int i=4;i<4+ncol*nrow;i++)//输出查询结果
//		puts(resValue[i]);
        printf("好友查询成功！\n");
        return 1;

}

//插入聊天记录信息
int insert_message(int message_id, int from_id, int to_id, char * content, char * time)
{
	int res;//保存sql返回值
	char * sql_insert;
	sql_insert=(char *)malloc(500*sizeof(char));
	char * errmsg;//保存错误信息
	memset(sql_insert, '\0',sizeof(char));
	sprintf(sql_insert, "INSERT INTO MESSAGE VALUES (\'%d\', \'%d\', \'%d\', \'%s\', \'%s\')", message_id, from_id, to_id, content, time);
       	res = sqlite3_exec(db, sql_insert, NULL, NULL, &errmsg);//执行sql语句
	free(sql_insert);
	if (res!=SQL_OK)//错误处理
	{
		puts(errmsg);
		return 0;
	}
	printf("聊天信息插入成功！\n");
	return 1;
}

//显示聊天记录
int show_message(int id, char ***resValue, int *nrow, int *ncol)
{
	int res;
//	char **resValue;//保存查询结果
//	int nrow;//查询结果数量
//	int ncol;//查询结果有几列
	char * sql_select;
	sql_select=(char *)malloc(500*sizeof(char));
	char * errmsg;
	memset(sql_select, '\0', sizeof(char));
	sprintf(sql_select, "SELECT * FROM MESSAGE WHERE FROMID = \'%d\' OR TOID = \'%d\' ORDER BY MESSAGEID", id, id);
	res = sqlite3_get_table(db, sql_select, resValue, nrow, ncol, &errmsg);//执行查询语句
	free(sql_select);
	if (res!=SQL_OK)//错误处理
	{
		puts(errmsg);
		return 0;
	}
//	for (int i=5;i<5+ncol*nrow;i++)//打印查询结果
//		puts(resValue[i]);
	printf("消息记录查询成功！\n");
	return 1;
}


int main ()
{
	char ** resValue;
	int nrow;
       	int ncol;	
	init_db();
	insert_userinfo(2,"123","123",1);
	insert_friend(1,2,"123",1);
	delete_friend(1,2);
	update_user(1,"234","321",1);
	show_user(2,&resValue,&nrow,&ncol);
	for (int i=4;i<4+nrow*ncol;i++)
	{
		puts(resValue[i]);
	}
	show_friend(1,&resValue,&nrow,&ncol);
	for (int i=4;i<4+nrow*ncol;i++)
		puts(resValue[i]);
	insert_message(1,1,2,"12431234","10:00:00");
	insert_message(2,2,1,"asdfasdf","10:00:01");
	show_message(1,&resValue,&nrow,&ncol);
	for (int i=5;i<5+nrow*ncol;i++)
		puts(resValue[i]);	
	return 0;
}

