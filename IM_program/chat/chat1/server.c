/*=====================================================
*软件名：server.c
*软件描述：局域网即时通信软件的服务器端
*软件运行环境：linux
*创建人：林振华
*====================================================*/

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>

#define OURPORT   8080 //用户端口
#define MAX_USERS 8    //最多的用户连接数

/*
*定义用户数据结构
*/
struct _client
{
    gint sd; //用户的套结字
    gboolean in_use; //定义in_use为布尔类型，只有TURE和FALSE
    gchar name[64]; //用户名
    gchar buf[1024]; //发送数据的缓冲
};
/*
*定义用户数据区
*/
typedef struct _client client;
client user[MAX_USERS];
/*
*定义服务线程
*/
void do_service(gpointer id)
{
   char tobuf[1024]; //发送缓冲
   gint i;

   while(read(user[GPOINTER_TO_INT(id)].sd,
               user[GPOINTER_TO_INT(id)].buf, 1024) != -1)
   {
       sprintf(tobuf, "%s: %s\n", user[GPOINTER_TO_INT(id)].name,
               user[GPOINTER_TO_INT(id)].buf);
       for(i = 0; i < MAX_USERS; i++)
       {
           if(user[i].in_use)
           {
               write(user[i].sd, tobuf, 1024);
               g_print("%s", tobuf);
           }
       }
   }
   user[GPOINTER_TO_INT(id)].in_use = FALSE;
   close(user[GPOINTER_TO_INT(id)].sd);
}
/*
*主函数
*/
int main(int argc, char *argv[])
{
    gint sd, newsd;
    struct sockaddr_in *sin;
    gint slen;
    gint count = 0;
    gint flags;
    gchar buf[1024];
    gchar tobuf[1024];
    gint length;
    int i;

 /*
 *使用函数g_thread_supported来判断线程是否已经初始化，如果未初始化
 *就返回FALSE值，使用g_thread_init来初始化线程应用
 */
    if( !g_thread_supported() ) 
        g_thread_init(NULL);
/*
*创建套结字
*返回非负描述字就成功，否则失败
*/
    if( ( sd = socket(AF_INET, SOCK_STREAM, 0) ) == -1)
    {
        g_print("create socket error!\n");
        return -1;
    }
    else
    {
        g_print("create socket success!\n");
    }
    
    sin = g_new(struct sockaddr_in, 1); //为套结字地址分配内存
    sin->sin_family = AF_INET; //套结字类型 
    sin->sin_port = OURPORT; //端口号
    slen = sizeof(struct sockaddr_in);
/*
*向指定端口绑定
*返回0成功，-1出错
*/
    if(bind(sd, (struct sockaddr *)sin, slen) < 0)
    {
        g_print("bind error!\n");
        return -1;
    }
    else
    {
        g_print("bind success!\n");
    }
/*
*监听
*返回0成功，-1出错
*/
    if(listen(sd, 8) < 0)
    {
        g_print("listen error!\n");
        return -1;
    }
    else
    {
        g_print("listen success!\n");
    }

    for(i = 0; i < MAX_USERS; i++)
        user[i].in_use = FALSE;

    flags = fcntl(sd, F_GETFL); //取得套结字的文件描述字
    fcntl(sd, F_SETFL, flags&~O_NDELAY); //关闭非阻塞状态
   
    for(;;)  //无限死循环，等待用户连接
    {
/*
*接收用户连接
*返回非负描述字成功，-1失败
*/
       if( (newsd = accept(sd, (struct sockaddr *)sin, &slen) ) == -1 )
       {
           g_print("accept error!\n");
           break;
       }
       else
       {
           if(count >= MAX_USERS)
           {
               sprintf(buf, "用户数量过多，服务端不能连接！\n");
               write(newsd, buf, 1024);
               close(newsd);
           }
           else
           {
               flags = fcntl(user[i].sd, F_GETFL);
               fcntl(user[i].sd, F_SETFL, O_NONBLOCK); //设置为非阻塞
               user[count].sd = newsd;
               user[count].in_use = TRUE;
               read(newsd, user[count].name, 64);
/*
*创建为用户服务的线程
*/
               g_thread_create((GThreadFunc)do_service, 
                       (gpointer)count, TRUE, NULL);
               count++;
           }
       }
    }
    close(sd);
    g_free(sin);

    return 0;
}

