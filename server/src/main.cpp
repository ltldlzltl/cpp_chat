/*
 * @Description: 
 * @Author: Tianling Lyu
 * @Date: 2020-11-16 13:17:48
 * @LastEditors: Tianling Lyu
 * @LastEditTime: 2020-11-27 10:30:57
 */

#define WIN32

#include <cstdio>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN // 避免引入早期冲突的库
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#endif

int main()
{
    // 启动Windows socket
    WORD ver = MAKEWORD(2, 2);
    WSADATA data;
    WSAStartup(ver, &data);

    // 服务器部分
    // 创建socket
    SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // ipv4, 流， tcp
    // 绑定端口
    sockaddr_in _sin = {};
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(8888);
    _sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR) {
        // deal with error
        printf("ERROR, 绑定端口失败...\n");
    } else {
        printf("绑定端口成功...\n");
    }
    // 监听端口
    if (SOCKET_ERROR == listen(_sock, 5)) /* socket,最大连接数*/ {
        // deal with error
        printf("ERROR, 监听端口失败...\n");
    } else {
        printf("监听端口成功...\n");
    }

    sockaddr_in clientAddr = {};
    int nAddrLen = sizeof(clientAddr);
    SOCKET _cSock = INVALID_SOCKET;
    char msgBuf[] = "Hello, I'm Server.";
    int msgLen = strlen(msgBuf) + 1;
    while (true) {
        // 等待接受客户端链接
        _cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
        if (INVALID_SOCKET == _cSock) {
            // deal with error
            printf("ERROR，接收到无效客户端socket...\n");
        }
        printf("新客户端加入: IP = %s \n", inet_ntoa(clientAddr.sin_addr));

        // 发送数据
        send(_cSock, msgBuf, msgLen, 0);
    }

    // 关闭socket
    closesocket(_sock);

    // 清除
    WSACleanup();
}