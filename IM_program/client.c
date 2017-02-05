/*=============================================================
*文件名：client.c
*文件描述：局域网即时通信软件客户端
*运行环境：linux
*创建人：林振华
*文件说明：由于要用到GTK的图形界面编程，所以用到了
*大量的GTK函数，但是我们主要了解的是在linux下的
*socket和多线程的编程，所以GTK的函数没有写出注释
*=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <gtk/gtk.h>
#include <pthread.h>

 #define OURPORT 8080 //定义端口

gint sd; //套结字
struct sockaddr_in s_in;//套结字数据结构
gchar username[64];//用户名
gchar buf[1024]; //写缓冲区
gchar get_buf[2048];//读缓冲区
gboolean isconnected = FALSE; //定义逻辑值表示是否连接

static GtkWidget *text;
static GtkTextBuffer *buffer; //显示对话内容的文本显示缓冲区
static GtkWidget *message_entry; //显示输入消息的单行录入控件
static GtkWidget *name_entry; //输入用户名的单行录入控件
static GtkWidget *login_button; //登陆按钮

/*
*线程要执行的函数，读取来自服务端的数据
*/
void get_message(void)
{
    GtkTextIter iter;
    gchar get_buf[1024];
    gchar buf[1024];
    
    while(read(sd, buf, 1024) != -1) //只要读取数据成功就循环执行
    {
        sprintf(get_buf, "%s", buf);
        gdk_threads_enter();  //进入
        gtk_text_buffer_get_end_iter(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, get_buf, -1); //显示读取的数据
        gdk_threads_leave(); //离开
    }
}

/*
*当前关闭登陆窗口时执行
*/
void on_destroy(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    sprintf(username, "guest");
    if(do_connect() == TRUE)
    {
        gtk_widget_set_sensitive(login_button, FALSE);
        g_thread_create((GThreadFunc)get_message, NULL, FALSE, NULL);
    }
    gtk_widget_destroy(widget);
}

/*
*当点击登陆窗口的登陆按钮时执行
*/
void on_button_clicked(GtkButton *button, gpointer data)
{
    const gchar *name;

    name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    sprintf(username, "%s", name);
    if(do_connect() )
    {
        gtk_widget_set_sensitive(login_button, FALSE);
        g_thread_create((GThreadFunc)get_message, NULL, FALSE, NULL);
    }
    gtk_widget_destroy(data);
}

/*
*创建登陆窗口
*/
void create_win(void )
{
    GtkWidget *win, *vbox;
    GtkWidget *button;

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "输入用户名");
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    g_signal_connect(G_OBJECT(win), "delete_event", 
            G_CALLBACK(on_destroy), NULL);
    gtk_window_set_modal(GTK_WINDOW(win), TRUE);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(win), vbox);

    name_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), name_entry, TRUE, TRUE, 5);
    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect(G_OBJECT(button), "clicked", 
            G_CALLBACK(on_button_clicked), win);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);

    gtk_widget_show_all(win);
}

/*
*连接聊天服务端
*/
gboolean do_connect(void)
{
    GtkTextIter iter;
    gint slen;
/*
*创建套结字
返回非负描述字成功，否则失败
*/
    if( (sd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ) //创建套结字
    {
        gtk_text_buffer_get_end_iter(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, "打开套结字时出错！\n", -1);
        return FALSE;
    }
    s_in.sin_family = AF_INET;
    s_in.sin_port = OURPORT;
    slen = sizeof(s_in);

/*
*连接
*返回0成功，-1失败
*/
    if(connect(sd, (struct sockaddr *)&s_in, slen ) < 0)
    {
        gtk_text_buffer_get_end_iter(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, "连接服务端时出错！\n", -1);
        return FALSE;
    }
    else
    {
        gtk_text_buffer_get_end_iter(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, username, -1);
        gtk_text_buffer_get_end_iter(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, "\n成功与服务端连接...\n",-1);

        write(sd, username, 64);//向服务端发送用户名

        isconnected = TRUE;
        return TRUE;
    }
}
/*
*向服务端发送数据
*/
void on_send(GtkButton *button, gpointer data )
{
    const char *message;

    if(isconnected == FALSE)
        return;

    message = gtk_entry_get_text(GTK_ENTRY(message_entry));
    sprintf(buf, "%s\n", message);
    write(sd, buf, 1024);  //发送
    gtk_entry_set_text(GTK_ENTRY(message_entry), "");//清除单行录中的文字
}

/*
*点击登陆按钮时执行
*/
void on_login(GtkWidget *button, gpointer data)
{
    create_win();
}


/*
*关闭主窗口时执行
*/
void on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    close(sd); //关闭
    gtk_main_quit();
}

/*
*主函数
*grac表示在命令行中输入参数的个数
*argv表示在命令输入的参数
*/
int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkWidget *vbox, *hbox, *button, *label, *view;

    if(!g_thread_supported())
        g_thread_init(NULL); //初始化线程
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "客户端");
    g_signal_connect(G_OBJECT(window), "delete_event", 
            G_CALLBACK(on_delete_event), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
    label = gtk_label_new("点击登陆按钮连接服务端");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
    login_button = gtk_button_new_with_label("登陆");
    gtk_box_pack_start(GTK_BOX(hbox), login_button, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(login_button), "clicked", 
            G_CALLBACK(on_login), NULL);

    view = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view), 
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    text = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 5);     
    gtk_container_add(GTK_CONTAINER(view), text);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
    
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

    label = gtk_label_new("输入消息：");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);

    message_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), message_entry, FALSE, FALSE, 5);

    button = gtk_button_new_with_label("发送");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(button), "clicked", 
            G_CALLBACK(on_send), NULL);

    gtk_widget_show_all(window);

    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();

    return 0;
}

