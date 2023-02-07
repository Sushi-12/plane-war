#pragma once
#include<windows.h>
#include<easyx.h>
#include<map>
using namespace std;

//3. ��Ϸ����
LRESULT CALLBACK RunGame(_In_  HWND hwnd,_In_  UINT uMsg,_In_  WPARAM wParam,_In_  LPARAM lParam);

#define INIT_MSGMAP(MSGID,MSGTYPE)\
m_MsgMap[MSGID].MsgType = MSGTYPE;\
m_MsgMap[MSGID].MsgFun##MSGTYPE = &CGameFrame::ON_##MSGID;

class CGameFrame {
	// friend:������Ԫ�Ĺؼ��֣��� RunGame ������ CGameFrame �����ѣ�������Runame �п���ʹ��CGameFrame ��˽�г�Ա
	friend LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
protected:
	HWND m_hWnd;
private:
	bool m_isQuit; //�Ƿ��˳��ı�־��true:�˳���false: ���˳�

	typedef void (CGameFrame::* P_FUN_EX_MOUSE)(POINT&);//������
	typedef void (CGameFrame::* P_FUN_EX_KEY)(WPARAM);//�������
	typedef void (CGameFrame::* P_FUN_EX_CHAR)(WPARAM);//�ַ����
	typedef void(CGameFrame::* P_FUN_EX_WINDOW)(WPARAM, LPARAM); //�������
	/*/
	#define EX_MOUSE		1
	#define EX_KEY			2
	#define EX_CHAR			4
	#define EX_WINDOW		8
	*/
	//��Ϣ���ͺ���ָ���װ
	struct Type_Fun {
		int MsgType; //��Ϣ���
		union {
			P_FUN_EX_MOUSE MsgFunEM_MOUSE;	//�����Ϣ����Ӧ�Ĵ�����ָ��
			P_FUN_EX_KEY   MsgFunEM_KEY;	//������Ϣ����Ӧ�Ĵ�����ָ��
			P_FUN_EX_CHAR  MsgFunEM_CHAR;//�ַ���Ϣ����Ӧ�Ĵ�����ָ��
			P_FUN_EX_WINDOW MsgFunEM_WINDOW;	//������Ϣ����Ӧ�Ĵ�����ָ��
		};
	};
	map<UINT,Type_Fun> m_MsgMap;//��Ϣӳ���
public:
	CGameFrame() {
		m_isQuit = false;
		m_hWnd = NULL;
	}
	virtual ~CGameFrame() {}

	bool GetQuit() {return m_isQuit;}
private:
	void InitMsgMap() {
		//�����Ϣӳ��
		INIT_MSGMAP(WM_LBUTTONDOWN, EM_MOUSE);
		INIT_MSGMAP(WM_KEYDOWN, EM_KEY);
		INIT_MSGMAP(WM_CHAR, EM_CHAR);
		INIT_MSGMAP(WM_CLOSE, EM_WINDOW)
		INIT_MSGMAP(WM_PAINT, EM_WINDOW)
		INIT_MSGMAP(WM_TIMER, EM_WINDOW)		//���Ӷ�ʱ������Ϣ
		INIT_MSGMAP(WM_LBUTTONUP, EM_MOUSE)
	}

public:
	//1. ��ʼ����Ϸ
	void InitGame(int width, int height, int x, int y, const TCHAR* pTitle) {

		m_hWnd = ::initgraph(width, height);		//��������

	
		::setbkcolor(RGB(255, 255, 255));	//���ô��ڵı���ɫ
		cleardevice();   //�����˱���ɫ֮������������Ч

		//�趨���ڳ��ֵ�λ��
		::MoveWindow(m_hWnd, x, y, width, height, true);

		//TCHAR ������� ���ֽ��£� TCHAR == char ,�ڿ��ֽ��� TCHAR == wchar_t
		//�趨���ڵı���
		::SetWindowText(m_hWnd, pTitle);

		//��ʼ����Ϣӳ���б�
		InitMsgMap();

		//�趨���ڵĻص�����
		::SetWindowLong(m_hWnd, GWLP_WNDPROC, (LONG)&RunGame);

		//��ʼ��������Ϸ
		Init();
	}
	//2. �ػ���Ϸ
	void ON_WM_PAINT(WPARAM, LPARAM) {
		::BeginBatchDraw();  //��ʼ������ͼ
		::cleardevice();  //�����һ�εĻ�ͼ�ۼ�
		//-------------------------------------
		Paint();
		//-------------------------------------
		::EndBatchDraw();  //����������ͼ
	}

	//4. �ر�
	void ON_WM_CLOSE(WPARAM w, LPARAM l){
		//������Ϸ�Ĵ��ڹر�
		Close(w,l);
		//�ر�������
		::closegraph();

		m_isQuit = true;   //�����˳�
	}

	//----������Ϸ��صĺ���-------------------------------------
	virtual void Init()=0;
	//������Ϸ���ػ�
	virtual void  Paint()=0 ;
	//���ڹرմ�����
	virtual void Close(WPARAM w, LPARAM l) = 0;
	//���������´�����
	virtual void ON_WM_LBUTTONDOWN(POINT& po) {}
	//������̧��
	virtual void ON_WM_LBUTTONUP(POINT&) {}
	//���̰�����Ϣ������
	virtual void ON_WM_KEYDOWN(WPARAM vk) {}
	//�ַ���Ϣ������
	virtual void ON_WM_CHAR(WPARAM vk) {}
	//��ʱ����Ϣ������
	virtual void ON_WM_TIMER(WPARAM w, LPARAM l) {}
};






