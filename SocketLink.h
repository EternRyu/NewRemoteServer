#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

//=================================================================
//��
//���繦���� 
#define MSG_FUNCTION_CODE_NETWIRKING 0x1		//����
#define MSG_FUNCTION_CODE_GET_PROCESS_LIST 0x2	//�����б�
#define MSG_FUNCTION_CODE_KEILL_PROCESS 0x3		//��������
#define MSG_FUNCTION_CODE_DEIVE_LETTER 0x4		//��ȡ�̷�
#define MSG_FUNCTION_CODE_FILE_TRAVERSAL 0x5	//�����ļ�
#define MSG_FUNCTION_CODE_GET_FILE_INFO 0x6		//��ȡ�ļ��ߴ�
#define MSG_FUNCTION_CODE_GET_FILE 0x7			//��ȡ�ļ�
#define MSG_FUNCTION_CODE_SEND_FILE 0x8			//�����ļ���Ϣ
#define MSG_FUNCTION_CODE_FILE_BUFFER 0x9		//�����ļ�����


#define USER_MSG WM_USER+1
#define USER_MSG_NETWORKING 0x0
#define USER_MSG_SOCKET 0x1			//�ͻ���soket����
#define USER_MSG_PROCESS 0x2
#define USER_MSG_FILE_SIZE 0x3
#define USER_MSG_SET_FILE_SIZE 0x4
#define USER_MSG_FILE_GET 0x5
#define USER_MSG_FILE_SEND 0x6

#define MSG_FUNCTION_CODE_SEND_EQULSIT 5001			//�豸�б�
#define MSG_FUNCTION_CODE_SEND_PROCESSLIST 5002		//�߳��б�
#define MSG_FUNCTION_CODE_SEND_DRIVE_LEREER 5003	//�̷�
#define MSG_FUNCTION_CODE_SEND_FILE_TRAVERSAL 5004	//�ļ�����

//=================================================================
//�ṹ��
typedef struct _LinkInfo
{
	DWORD dwFuncCode;	//���ܺ�
	char szComputerName[30];	//���������
	char szSystenVersion[30];	//�����ϵͳ�汾
	char szIntranetIP[20];	//����IP
	char szNetWorkIP[20];	//����IP
}LinkInfo, * PLinkInfo;

//�ͻ���Socket�ṹ
typedef struct _ClientSocketInfo
{
	SOCKET SockClient;//�ͻ��˵õ���SOCKET
	char szNetWorkIP[20];//IP��ַ(����)
}ClientSocketInfo, * PClientSocketInfo;

//������Ϣ�ṹ
typedef struct _ProcessListInfo
{
	DWORD dwFuncCode;				//���ܺ�
	DWORD dwProcessID;				//����ID
	DWORD dwParenProcessID;			//������ID
	char szProcessName[128];		//������
	char szProcessPath[MAX_PATH];	//����·��
}ProcessListInfo, * ProcessListInfo_PTR;

//�������̽ṹ
typedef struct _KillProcessInfo
{
	DWORD dwFuncCode;				//���ܺ�
	DWORD dwProcessID;				//����ID
}KillProcessInfo, * PKillProcessInfo;

//�̷������ṹ
typedef struct _DriveLetterInfo
{
	DWORD dwFuncCode;				//���ܺ�
	char szDisk[10];				//�̷�����
	char szDiskType[20];			//�̷�����
	SHFILEINFO FileInfo;			//�ļ���Ϣ
}DriveLetterInfo, * PDriveLetterInfo;

//�ļ������ṹ
typedef struct _DiskFileInfo
{
	DWORD dwFuncCode;				//���ܺ�
	char szFilePath[MAX_PATH];		//�ļ�·��
	char szFileInfo[50];			//��ע��Ϣ
	SHFILEINFO FileInfo;			//�ļ���Ϣ
}DiskFileInfo, * PDiskFileInfo;

//�ļ�ȡ�ؽṹ
typedef struct _GetFileInfo
{
	DWORD dwFuncCode;				//���ܺ�
	DWORD dwFileSize;				//�ļ��ߴ�
	char szFilePath[MAX_PATH];		//�ļ�·��
}GetFileInfo, * PGetFileInfo;

//�ļ��·��ṹ
typedef struct _SendFileInfo
{
	DWORD dwFuncCode;				//���ܺ�

}SendFileInfo, * PSendFileInfo;
//=================================================================

extern SOCKET g_Socket;

//=================================================================
//��������

BOOL InitSocket();//��ʼ���׽���
DWORD SocketThreadCallBack(LPVOID lpBuffer);//�׽��ֻص�����
DWORD GetSocketData(LPVOID* lpRetFileBuffer);//��̬���ջ���������
VOID SendData(LPVOID lpSendBuffer, DWORD64 dwBufferLength);//��̬��������
int CharToWchar(wchar_t* wcharStr, const char* charStr);//CHAR to WCHAR

