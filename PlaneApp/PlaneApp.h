#pragma once
#include "../GameFrame/GameFrame.h"  //../ÉÏ²ãÄ¿Â¼
#include"../BackGround/BackGround.h"
#include"../Player/Player.h"
#include"../GunnerBox/GunnerBox.h"
#include"../FoePlaneBox/FoePlaneBox.h"



#define CREATE_OBJECT(OBJECT)\
		CGameFrame*CreateObject(){\
		return new OBJECT;\
		}

#define WINDOWS_PARAM(WIDTH,HEIGHT,X,Y,TITLE)\
		int wndWidth			=WIDTH;\
		int wndHeight			=HEIGHT;\
		int wndPosX				=X;\
		int wndPosY				=Y;\
		const TCHAR* wndTitle = TITLE;\




class CPlaneApp :public CGameFrame{
public:
	CBackGround m_back;
	CPlayer m_player;
	CGunnerBox m_gunBox;
	CFoePlaneBox m_foeBox;
	int m_score;
	IMAGE m_board;

public:
	CPlaneApp();
	~CPlaneApp();
	virtual void Init();
	virtual void  Paint();
	virtual void Close(WPARAM w, LPARAM l);
	virtual void ON_WM_TIMER(WPARAM w, LPARAM l);
	virtual void ON_WM_KEYDOWN(WPARAM vk);


	void SetTimer();
	void GameOver();
	void ShowScore();
};