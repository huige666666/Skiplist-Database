//#include <WINSOCK2.H>   
#include <stdio.h>  
#include<string>
#include <iostream>
//#include<windows.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>
#include "Command.h"
#include <cassert>
using namespace std;

//#pragma warning( disable : 4996 )
//���������ʹ�õĳ���      
#define SERVER_ADDRESS "127.0.0.1" //��������IP��ַ      
#define PORT           5150         //�������Ķ˿ں�      
#define MSGSIZE        1024         //�շ��������Ĵ�С      
#define MAXBYTE        1024
//#pragma comment(lib, "ws2_32.lib")      

int main()
{
    //WSADATA wsaData;
    //���������׽���      
    //SOCKET sClient;
    //����Զ�̷������ĵ�ַ��Ϣ      
    //SOCKADDR_IN server;
    //�շ�������      
    char szMessage[MSGSIZE];
    //�ɹ������ֽڵĸ���      
   // int ret;

    // Initialize Windows socket library      
    //WSAStartup(0x0202, &wsaData);

    // �����ͻ����׽���      
    //sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/IPЭ���壻      
                                                         //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��    
	 int sClient = socket(AF_INET, SOCK_STREAM, 0);
	 assert(sClient >= 0);
    // ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�IP��ַ��)      
  /*  memset(&server, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0      
    server.sin_family = PF_INET; //������ַ��ʽ��TCP/IP��ַ��ʽ      
    server.sin_port = htons(PORT); //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order      
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //ָ�����ӷ�������IP��ַ      
                                                        //�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���IP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���IP��ַ      
                                                        //inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��ΪIP��ַ��ʽ      
    //�����ղ�ָ���ķ�������      
    connect(sClient, (struct sockaddr*)&server, sizeof(SOCKADDR_IN)); //���Ӻ������sClient��ʹ���������      
    cout << "Redis_client by Stack start-up...\n";     */                                                 //server������Զ�̷������ĵ�ַ��Ϣ      
    struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr.s_addr);
	//printf("[%x]\n", serv.sin_addr.s_addr);
	int ret = connect(sClient, (struct sockaddr *)&serv, sizeof(serv));
	if(ret<0)
	{
		//perror("connect error");
		cout<<"connect error"<<endl;
		return -1;
	}	
	
	while (1) {

        cout<<"Stack_Redis>";
        //�Ӽ�������  
        string message;
        getline(cin, message); //The gets() functionreads characters from stdin and loads them into szMessage      
        strcpy(szMessage, message.c_str());
        Command C(message);
        if (!C.is_valid_command()) {
            continue;
        }

        // ��������      
        send(sClient, szMessage, strlen(szMessage), 0); //sClientָ�����ĸ����ӷ��ͣ� szMessageָ�����������ݵı����ַ ��strlen(szMessage)ָ�����ݳ���      
        char szBuffer[MAXBYTE] = { 0 };
        if (recv(sClient, szBuffer, MAXBYTE, 0) <= 0) {
            break;
        }
        //����յ�������
        cout << "Server reply: " << szBuffer << endl;

    }

    // �ͷ����Ӻͽ��н�������      
    close(sClient);
    //WSACleanup();
    return 0;
}
