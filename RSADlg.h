
// RSADlg.h: файл заголовка
//
#pragma once
#include "afxwin.h"
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;
// Диалоговое окно CRSADlg

class CRSADlg : public CDialogEx
{
	// Создание
public:
	CRSADlg(CWnd* pParent = nullptr);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	CStringW OTXT;
	CStringW CTXT;

	afx_msg void OnBnClickedLoadOtxt();
	afx_msg void OnBnClickedSaveOtxt();
	afx_msg void OnBnClickedLoadCtxt();
	afx_msg void OnBnClickedSaveCtxt();
	CButton RADIO_DEC;
	CButton RADIO_CR;

	long long unsigned int p;
	long long unsigned int q;
	long long unsigned int z;
	long long unsigned int e;
	long long unsigned int n;
	afx_msg void OnBnClickedRsa2();
	afx_msg void OnBnClickedCr();
	afx_msg void OnBnClickedDec();
};


class RSA {
public:
	unsigned long long n, p, q, phi, e, d;
	RSA() {
		//генерируем числа
		do {
			p = rand() % (1 << 15) + (1 << 15);
			if (p % 2 == 0)	p--;
		} while (ferma(p) == false);
		do {
			q = rand() % (1 << 15) + (1 << 15);
			if (q % 2 == 0)	q--;
		} while (ferma(q) == false || q == p);
		n = p * q;
		phi = (p - 1) * (q - 1);
		do
		{
			e = rand() % phi;
		} while (EuclidAlgorithm(e, phi, d) != 1 || d <= 0 || e < 11500 || d > 80000000);
	}
	RSA(unsigned long long p, unsigned long long q) {
		n = p * q;
		phi = (p - 1) * (q - 1);
		do
		{
			e = rand() % phi;
		} while (EuclidAlgorithm(e, phi, d) != 1 || d <= 0 || e < 11500 || d > 80000000);
	}
	unsigned int gcd(unsigned c, unsigned d);
	bool ferma(unsigned long long int c);
	CString Crypt(CString OTXT);
	CString Decrypt(CString CTXT);
	long long unsigned EuclidAlgorithm(long long unsigned e, long long unsigned phi, long long unsigned& d);
	void newpq();
};