/*
 * @Description: main.cpp
 * @Author: Tianling Lyu
 * @Date: 2020-11-16 10:08:15
 * @LastEditors: Tianling Lyu
 * @LastEditTime: 2020-11-27 11:25:06
 */

#define WIN32

#include <cstdio>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN // 避免引入早期冲突的库
#include <windows.h>
#include <WinSock2.h>
#endif

int main()
{
    // 启动Windows socket
    WORD ver = MAKEWORD(2, 2);
    WSADATA data;
    WSAStartup(ver, &data);

    // 创建socket
    SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0); // ipv4, 流， tcp
    if (INVALID_SOCKET == _sock) {
        printf("Socket construction error...\n");
    }
    // 连接服务器
    sockaddr_in _sin = {};
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(8888);
    _sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
    if (SOCKET_ERROR == ret) {
        printf("Connection failed...\n");
    }

    // 接收服务器信息
    char recvBuf[256] = {};
    int dlen = recv(_sock, recvBuf, 256, 0);
    if (0 >= dlen) {
        printf("Receiving data failed...\n");
    } else {
        printf("接收到数据：%s\n", recvBuf);
    }

    // 关闭socket
    closesocket(_sock);

    // 清除
    WSACleanup();
}