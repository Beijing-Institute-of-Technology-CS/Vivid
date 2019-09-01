#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "sqlite3.h"
#define SQL_OK 0


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
int insert_Usermessage(int message_id, int from_id, int to_id, char * content,
		char * time);

//显示聊天记录，可以根据ID查找用户收到和发送的聊天记录，按照消息ID升序排列
//resValue为一个指向二维数组的地址，二维数组负责存放数据库返回信息
//nrow和ncol分别为返回结果的行数和列数
int show_Usermessage(int id, char *** resValue, int * nrow, int *col);

//插入群聊消息
int insert_Groupmessage(int message_id, int from_id, int to_id, char * content, char * time, int group_id);

//显示群聊消息
int show_Groupmessage(char *** resValue, int * nrow, int * ncol, int group_id);

//插入群组信息
int insert_Group(int group_id, int user_id);

//显示群组信息
int show_Groupinfo(char *** resValue, int * nrow, int * ncol, int user_id);

//判断消息是否是群聊  是返回2，不是返回1，查询错误返回0   参数为消息ID
int group_or_not(int message_id);

#endif
/*
接口使用示例：
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
        for (int i=ncol;i<ncol*(nrow+1);i++)
                puts(resValue[i]);

        insert_Usermessage(1,1,2,"12431234","10:00:00");
        insert_Usermessage(2,2,1,"asdfasdf","10:00:01");
        show_Usermessage(1,&resValue,&nrow,&ncol);
        for (int i=ncol;i<ncol*(nrow+1);i++)
                puts(resValue[i]);      
        insert_Group(2,2);
        show_Groupinfo(&resValue, &nrow, &ncol,2);
        for (int i=ncol;i<ncol*(nrow+1);i++)
                puts(resValue[i]);
        insert_Groupmessage(3,1,2,"1234543","11:11:11",123);
        show_Groupmessage(&resValue, &nrow, &ncol,123);
        for (int i=ncol;i<ncol*(nrow+1);i++)
                puts(resValue[i]);
        int ans;
        ans=group_or_not(2);
        printf("%d\n",ans);
        return 0;
}

*/
