#include"GameFrame.h"
#include<Windowsx.h>

//������Ϸ�ǵ�ָ��
CGameFrame* pGame = nullptr;
//�����ľ�����Ϸ���ڲ������� 
extern int wndWidth;
extern int wndHeight;
extern int wndPosX;
extern int wndPosY;
extern const TCHAR* wndTitle;



//3. ��Ϸ���� �ڻص������д���
//hwnd :���ھ����
// uMsg: ��ϢID ��Ч��  msg.message
//wParam ,lParam : ��ϢЯ������Ϣ
LRESULT CALLBACK RunGame(_In_  HWND hwnd, _In_  UINT uMsg, _In_  WPARAM wParam, _In_  LPARAM lParam) {
	if (pGame->m_MsgMap.count(uMsg)) {	//��ϢID��ӳ����д���
		switch (pGame->m_MsgMap[uMsg].MsgType) {
		case EM_MOUSE: {
			//��ȡ�����
			POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_MOUSE)(po);
		}
					 break;
		case EM_KEY: {
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_KEY)(wParam);
		}
					 break;
		case EM_CHAR: {

			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_CHAR)(wParam);
		}
					 break;
		case EM_WINDOW: {
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_WINDOW)(wParam, lParam);
		}
					 break;
		}
		//---------------------------------
		//���»��ƴ��ڣ�����֤��ʱˢ�£�������Ӧ�������ֶ����� WM_PAINT
		RECT rect{0,0,wndWidth,wndHeight};//������α���
		::InvalidateRect(pGame->m_hWnd,   //���Ǹ����ڱ�Ϊ��Ч��
			&rect,						  //�����ڵ��Ĳ��ֱ�Ϊ��Ч��
			false);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);   //���ڲ����ĵ���Ϣ����windowĬ�ϵĴ�����ȥ����
}





int main() {
	CGameFrame* CreateObject();//��������
	pGame = CreateObject();
	//��ʼ������
	pGame->InitGame(wndWidth, wndHeight, wndPosX, wndPosY, wndTitle);
	//��������ѭ����ѭ���˳����������˳�
	while (!pGame->GetQuit()) {
		Sleep(1000);
	}
	//������Դ
	delete pGame;
	pGame = nullptr;
	return 0;
}