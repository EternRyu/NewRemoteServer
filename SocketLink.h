#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

//=================================================================
//宏
//网络功能码 
#define MSG_FUNCTION_CODE_NETWIRKING 0x1		//上线
#define MSG_FUNCTION_CODE_GET_PROCESS_LIST 0x2	//进程列表
#define MSG_FUNCTION_CODE_KEILL_PROCESS 0x3		//结束进程
#define MSG_FUNCTION_CODE_DEIVE_LETTER 0x4		//获取盘符
#define MSG_FUNCTION_CODE_FILE_TRAVERSAL 0x5	//遍历文件
#define MSG_FUNCTION_CODE_GET_FILE_INFO 0x6		//获取文件尺寸
#define MSG_FUNCTION_CODE_GET_FILE 0x7			//获取文件
#define MSG_FUNCTION_CODE_SEND_FILE 0x8			//发送文件信息
#define MSG_FUNCTION_CODE_FILE_BUFFER 0x9		//发送文件缓冲


#define USER_MSG WM_USER+1
#define USER_MSG_NETWORKING 0x0
#define USER_MSG_SOCKET 0x1			//客户端soket保存
#define USER_MSG_PROCESS 0x2
#define USER_MSG_FILE_SIZE 0x3
#define USER_MSG_SET_FILE_SIZE 0x4
#define USER_MSG_FILE_GET 0x5
#define USER_MSG_FILE_SEND 0x6

#define MSG_FUNCTION_CODE_SEND_EQULSIT 5001			//设备列表
#define MSG_FUNCTION_CODE_SEND_PROCESSLIST 5002		//线程列表
#define MSG_FUNCTION_CODE_SEND_DRIVE_LEREER 5003	//盘符
#define MSG_FUNCTION_CODE_SEND_FILE_TRAVERSAL 5004	//文件遍历

//=================================================================
//结构体
typedef struct _LinkInfo
{
	DWORD dwFuncCode;	//功能号
	char szComputerName[30];	//计算机名称
	char szSystenVersion[30];	//计算机系统版本
	char szIntranetIP[20];	//外网IP
	char szNetWorkIP[20];	//内网IP
}LinkInfo, * PLinkInfo;

//客户端Socket结构
typedef struct _ClientSocketInfo
{
	SOCKET SockClient;//客户端得到的SOCKET
	char szNetWorkIP[20];//IP地址(外网)
}ClientSocketInfo, * PClientSocketInfo;

//进程信息结构
typedef struct _ProcessListInfo
{
	DWORD dwFuncCode;				//功能号
	DWORD dwProcessID;				//进程ID
	DWORD dwParenProcessID;			//父进程ID
	char szProcessName[128];		//进程名
	char szProcessPath[MAX_PATH];	//进程路径
}ProcessListInfo, * ProcessListInfo_PTR;

//结束进程结构
typedef struct _KillProcessInfo
{
	DWORD dwFuncCode;				//功能号
	DWORD dwProcessID;				//进程ID
}KillProcessInfo, * PKillProcessInfo;

//盘符遍历结构
typedef struct _DriveLetterInfo
{
	DWORD dwFuncCode;				//功能号
	char szDisk[10];				//盘符名称
	char szDiskType[20];			//盘符类型
	SHFILEINFO FileInfo;			//文件信息
}DriveLetterInfo, * PDriveLetterInfo;

//文件遍历结构
typedef struct _DiskFileInfo
{
	DWORD dwFuncCode;				//功能号
	char szFilePath[MAX_PATH];		//文件路径
	char szFileInfo[50];			//备注信息
	SHFILEINFO FileInfo;			//文件信息
}DiskFileInfo, * PDiskFileInfo;

//文件取回结构
typedef struct _GetFileInfo
{
	DWORD dwFuncCode;				//功能号
	DWORD dwFileSize;				//文件尺寸
	char szFilePath[MAX_PATH];		//文件路径
}GetFileInfo, * PGetFileInfo;

//文件下发结构
typedef struct _SendFileInfo
{
	DWORD dwFuncCode;				//功能号

}SendFileInfo, * PSendFileInfo;
//=================================================================

extern SOCKET g_Socket;

//=================================================================
//函数声明

BOOL InitSocket();//初始化套接字
DWORD SocketThreadCallBack(LPVOID lpBuffer);//套接字回调函数
DWORD GetSocketData(LPVOID* lpRetFileBuffer);//动态接收缓冲区数据
VOID SendData(LPVOID lpSendBuffer, DWORD64 dwBufferLength);//动态发送数据
int CharToWchar(wchar_t* wcharStr, const char* charStr);//CHAR to WCHAR

