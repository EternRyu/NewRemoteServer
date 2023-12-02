#include "SocketLink.h"

//=================================================================
//全局变量区
SOCKET SocketSrv;
SOCKET SocketConn;
SOCKADDR_IN AddrSrv;
SOCKADDR_IN AddrClient;

//=================================================================

BOOL InitSocket()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA lpWSAData;
	int nRet = WSAStartup(wVersionRequested, &lpWSAData);
	if (nRet != 0)
	{
		return FALSE;
	}
	if (LOBYTE(lpWSAData.wVersion) != 2 || HIBYTE(lpWSAData.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}
	SocketSrv = socket(AF_INET, SOCK_STREAM, 0);//创建链接
	AddrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//任意IP
	AddrSrv.sin_port = htons(8000);//端口
	AddrSrv.sin_family = AF_INET;//设置家族

	char opt = -1;
	setsockopt(SocketSrv, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//设置端口复用
	bind(SocketSrv, (sockaddr*)&AddrSrv, sizeof(sockaddr));//设置绑定
	listen(SocketSrv, 1000);//监听
	return TRUE;
}

DWORD SocketThreadCallBack(LPVOID lpBuffer)
{
	int nLength = sizeof(sockaddr);
	while (true)
	{
		LPVOID lpRetBuffer=NULL;
		SocketConn = accept(SocketSrv, (sockaddr*)&AddrClient, &nLength);
		DWORD RetFileLength = GetSocketData(&lpRetBuffer);
		DWORD dwTempValue = *(PDWORD)lpRetBuffer;
		switch (dwTempValue)
		{
		case MSG_FUNCTION_CODE_NETWIRKING:
		{
			LinkInfo NetWorkingBuffer = *(LinkInfo*)lpRetBuffer;
			LinkInfo* pNetWorkingBuffer = &NetWorkingBuffer;
			NetWorkingBuffer = *(LinkInfo*)lpRetBuffer;
			memcpy(NetWorkingBuffer.szNetWorkIP, inet_ntoa(AddrClient.sin_addr), strlen(inet_ntoa(AddrClient.sin_addr)));
			ClientSocketInfo TempInfo;
			TempInfo.SockClient = SocketConn;
			memset(TempInfo.szNetWorkIP, 0, 20);
			memcpy(TempInfo.szNetWorkIP, NetWorkingBuffer.szNetWorkIP, strlen(NetWorkingBuffer.szNetWorkIP));
			HWND hWndDlg = FindWindow(NULL, L"RemoteServer");
			SendMessage(hWndDlg, MSG_FUNCTION_CODE_SEND_EQULSIT, USER_MSG_NETWORKING, (LPARAM)pNetWorkingBuffer);
			PostMessage(hWndDlg, USER_MSG, USER_MSG_SOCKET, (LPARAM)&TempInfo);
			free(lpRetBuffer);
			break;
		}
		case MSG_FUNCTION_CODE_GET_PROCESS_LIST:
		{
			ProcessListInfo PLInfoBuffer = *(ProcessListInfo_PTR)lpRetBuffer;
			ProcessListInfo_PTR PLInfoBuffer_PTR = &PLInfoBuffer;
			HWND hWndDlg = FindWindow(NULL, L"ReProcess");
			SendMessage(hWndDlg, MSG_FUNCTION_CODE_SEND_PROCESSLIST, NULL, (LPARAM)PLInfoBuffer_PTR);
			break;
		}
		case MSG_FUNCTION_CODE_DEIVE_LETTER:
		{
			DriveLetterInfo DriveLetterBuffer = *(PDriveLetterInfo)lpRetBuffer;
			PDriveLetterInfo pDriveLetterBuffer = &DriveLetterBuffer;
			HWND hWndDlg = FindWindow(NULL, L"FileManager");
			SendMessage(hWndDlg, MSG_FUNCTION_CODE_SEND_DRIVE_LEREER, NULL, (LPARAM)pDriveLetterBuffer);
			break;
		}
		case MSG_FUNCTION_CODE_FILE_TRAVERSAL:
		{
			DiskFileInfo DiskFileBuffer = *(PDiskFileInfo)lpRetBuffer;
			PDiskFileInfo pDiskFileBuffer = &DiskFileBuffer;
			HWND hWndDlg = FindWindow(NULL, L"FileManager");
			SendMessage(hWndDlg, MSG_FUNCTION_CODE_SEND_FILE_TRAVERSAL, NULL, (LPARAM)pDiskFileBuffer);
			break;
		}
		default:
			break;
		}
	}
	return 0;
}

int CharToWchar(wchar_t* wcharStr, const char* charStr)//CHAR to WCHAR
{
	int len = MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, charStr, strlen(charStr), wcharStr, len);
	wcharStr[len] = '\0';
	return len;
}

//动态接收数据
DWORD GetSocketData(LPVOID* lpRetFileBuffer)
{
	DWORD64 dwRetFileLength = 0;
	recv(SocketConn, (PCHAR)&dwRetFileLength, sizeof(DWORD64), 0);
	*lpRetFileBuffer = malloc(dwRetFileLength);
	ZeroMemory(*lpRetFileBuffer, dwRetFileLength);
	recv(SocketConn, (PCHAR)*lpRetFileBuffer, dwRetFileLength, 0);
	return dwRetFileLength;
}

//动态发送数据
VOID SendData(LPVOID lpSendBuffer, DWORD64 dwBufferLength)
{
	send(g_Socket, (char*)&dwBufferLength, sizeof(DWORD64), 0);
	send(g_Socket, (char*)lpSendBuffer, dwBufferLength, 0);
	return;
}





