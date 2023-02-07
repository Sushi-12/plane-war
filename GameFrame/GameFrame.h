#pragma once
#include<windows.h>
#include<easyx.h>
#include<map>
using namespace std;

//3. 游戏运行
LRESULT CALLBACK RunGame(_In_  HWND hwnd,_In_  UINT uMsg,_In_  WPARAM wParam,_In_  LPARAM lParam);

#define INIT_MSGMAP(MSGID,MSGTYPE)\
m_MsgMap[MSGID].MsgType = MSGTYPE;\
m_MsgMap[MSGID].MsgFun##MSGTYPE = &CGameFrame::ON_##MSGID;

class CGameFrame {
	// friend:定义友元的关键字，把 RunGame 看做是 CGameFrame 的朋友，所以在Runame 中可以使用CGameFrame 的私有成员
	friend LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
protected:
	HWND m_hWnd;
private:
	bool m_isQuit; //是否退出的标志，true:退出，false: 不退出

	typedef void (CGameFrame::* P_FUN_EX_MOUSE)(POINT&);//鼠标类别
	typedef void (CGameFrame::* P_FUN_EX_KEY)(WPARAM);//键盘类别
	typedef void (CGameFrame::* P_FUN_EX_CHAR)(WPARAM);//字符类别
	typedef void(CGameFrame::* P_FUN_EX_WINDOW)(WPARAM, LPARAM); //窗口类别
	/*/
	#define EX_MOUSE		1
	#define EX_KEY			2
	#define EX_CHAR			4
	#define EX_WINDOW		8
	*/
	//消息类别和函数指针封装
	struct Type_Fun {
		int MsgType; //消息类别
		union {
			P_FUN_EX_MOUSE MsgFunEM_MOUSE;	//鼠标消息类别对应的处理函数指针
			P_FUN_EX_KEY   MsgFunEM_KEY;	//键盘消息类别对应的处理函数指针
			P_FUN_EX_CHAR  MsgFunEM_CHAR;//字符消息类别对应的处理函数指针
			P_FUN_EX_WINDOW MsgFunEM_WINDOW;	//窗口消息类别对应的处理函数指针
		};
	};
	map<UINT,Type_Fun> m_MsgMap;//消息映射表
public:
	CGameFrame() {
		m_isQuit = false;
		m_hWnd = NULL;
	}
	virtual ~CGameFrame() {}

	bool GetQuit() {return m_isQuit;}
private:
	void InitMsgMap() {
		//添加消息映射
		INIT_MSGMAP(WM_LBUTTONDOWN, EM_MOUSE);
		INIT_MSGMAP(WM_KEYDOWN, EM_KEY);
		INIT_MSGMAP(WM_CHAR, EM_CHAR);
		INIT_MSGMAP(WM_CLOSE, EM_WINDOW)
		INIT_MSGMAP(WM_PAINT, EM_WINDOW)
		INIT_MSGMAP(WM_TIMER, EM_WINDOW)		//增加定时器的消息
		INIT_MSGMAP(WM_LBUTTONUP, EM_MOUSE)
	}

public:
	//1. 初始化游戏
	void InitGame(int width, int height, int x, int y, const TCHAR* pTitle) {

		m_hWnd = ::initgraph(width, height);		//创建窗口

	
		::setbkcolor(RGB(255, 255, 255));	//设置窗口的背景色
		cleardevice();   //更改了背景色之后，让其立即生效

		//设定窗口出现的位置
		::MoveWindow(m_hWnd, x, y, width, height, true);

		//TCHAR 如果是在 多字节下， TCHAR == char ,在宽字节下 TCHAR == wchar_t
		//设定窗口的标题
		::SetWindowText(m_hWnd, pTitle);

		//初始化消息映射列表
		InitMsgMap();

		//设定窗口的回调函数
		::SetWindowLong(m_hWnd, GWLP_WNDPROC, (LONG)&RunGame);

		//初始化具体游戏
		Init();
	}
	//2. 重绘游戏
	void ON_WM_PAINT(WPARAM, LPARAM) {
		::BeginBatchDraw();  //开始批量绘图
		::cleardevice();  //清除上一次的绘图痕迹
		//-------------------------------------
		Paint();
		//-------------------------------------
		::EndBatchDraw();  //结束批量绘图
	}

	//4. 关闭
	void ON_WM_CLOSE(WPARAM w, LPARAM l){
		//具体游戏的窗口关闭
		Close(w,l);
		//关闭主窗口
		::closegraph();

		m_isQuit = true;   //程序退出
	}

	//----具体游戏相关的函数-------------------------------------
	virtual void Init()=0;
	//具体游戏的重绘
	virtual void  Paint()=0 ;
	//窗口关闭处理函数
	virtual void Close(WPARAM w, LPARAM l) = 0;
	//鼠标左键按下处理函数
	virtual void ON_WM_LBUTTONDOWN(POINT& po) {}
	//鼠标左键抬起
	virtual void ON_WM_LBUTTONUP(POINT&) {}
	//键盘按下消息处理函数
	virtual void ON_WM_KEYDOWN(WPARAM vk) {}
	//字符消息处理函数
	virtual void ON_WM_CHAR(WPARAM vk) {}
	//定时器消息处理函数
	virtual void ON_WM_TIMER(WPARAM w, LPARAM l) {}
};






