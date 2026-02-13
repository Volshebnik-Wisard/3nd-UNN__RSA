
// RSADlg.cpp: файл реализации
//

#include <math.h>
#include "pch.h"
#include "framework.h"
#include "RSA.h"
#include "RSADlg.h"
#include "afxdialogex.h"


#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <ctime>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
wstring buffCr;


// Диалоговое окно CRSADlg

CRSADlg::CRSADlg(CWnd* pParent /*=nullptr*/)
: CDialogEx(IDD_RSA_DIALOG, pParent)
, OTXT(L"Ware wa naseru kotoba nogotoku Ware wa tsukuru kotoba nogotoku Ware wa kowasu kotoba nogotoku	Shizumi izuru kurikaesu hi yo")
, CTXT(L"")
, q(0)
, p(0)
, z(0)
, e(0)
, n(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OTXT, OTXT);
	DDX_Text(pDX, IDC_CTXT, CTXT);
	DDX_Control(pDX, IDC_DEC, RADIO_DEC);
	DDX_Control(pDX, IDC_CR, RADIO_CR);
	DDX_Text(pDX, IDC_e2, p);
	DDX_Text(pDX, IDC_n2, q);
	DDX_Text(pDX, IDC_e3, z);
	DDX_Text(pDX, IDC_e, e);
	DDX_Text(pDX, IDC_n, n);
}

BEGIN_MESSAGE_MAP(CRSADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_OTXT, &CRSADlg::OnBnClickedLoadOtxt)
	ON_BN_CLICKED(IDC_SAVE_OTXT, &CRSADlg::OnBnClickedSaveOtxt)
	ON_BN_CLICKED(IDC_LOAD_CTXT, &CRSADlg::OnBnClickedLoadCtxt)
	ON_BN_CLICKED(IDC_SAVE_CTXT, &CRSADlg::OnBnClickedSaveCtxt)
	ON_BN_CLICKED(ID_RSA2, &CRSADlg::OnBnClickedRsa2)
	ON_BN_CLICKED(IDC_CR, &CRSADlg::OnBnClickedCr)
	ON_BN_CLICKED(IDC_DEC, &CRSADlg::OnBnClickedDec)
END_MESSAGE_MAP()


// Обработчики сообщений CRSADlg

BOOL CRSADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CRSADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CRSADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CRSADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//функции нажатия кнопок в окне

void CRSADlg::OnBnClickedLoadOtxt()
{
	CFileDialog FileForEnc(TRUE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::in | wfstream::binary);
	wstring str = L"";
	if (file.is_open()) {
		wchar_t c;

		while (file >> noskipws >> c) {
			str += c;
		}
	}
	OTXT = str.c_str();
	file.close();
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedSaveOtxt()
{
	UpdateData(TRUE);
	CFileDialog FileForEnc(FALSE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::out | wfstream::binary);
	wstring otxt = OTXT;
	for (wchar_t c : otxt) {
		file << c;
	}
	file.close();
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedLoadCtxt()
{
	CFileDialog FileForEnc(TRUE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::in | wfstream::binary);
	wstring str = L"";
	if (file.is_open()) {
		wchar_t c;

		while (file >> noskipws >> c) {
			str += c;
		}
	}
	CTXT = str.c_str();
	file.close();
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedSaveCtxt()
{
	UpdateData(TRUE);
	CFileDialog FileForEnc(FALSE);
	if (FileForEnc.DoModal() != IDOK) return;
	wfstream file;
	file.open(FileForEnc.GetPathName(), wfstream::out | wfstream::binary);
	wstring ctxt = CTXT;
	for (wchar_t c : ctxt) {
		file << c;
	}
	file.close();
	UpdateData(FALSE);
}


/////////////////////////////////////////////
//RSA

long long unsigned powmod(long long unsigned x, long long y, long long unsigned N)
{
	if (y == 0) {
		return 1;
	}
	unsigned long long int z = powmod(x, y / 2, N);
	if (y % 2 == 0)
		return ((z % N) * (z % N)) % N;
	else
		return ((((x % N) * (z % N)) % N) * (z % N)) % N;

}

long long unsigned modexp(long long unsigned base, long long unsigned exp, long long unsigned modulo)
{
	unsigned res = 1;

	while (exp != 0)
	{
		if ((exp & 1) != 0)
		{
			res = (1ll * res * base) % modulo;
		}

		base = (1ll * base * base) % modulo;
		exp >>= 1;
	}

	return res;
}

bool RSA::ferma(unsigned long long int n) {
	for (long long i = 2; i <= sqrt(n); i++)
	if (n % i == 0)
		return false;
	return true;


}



unsigned int RSA::gcd(unsigned c, unsigned d) {
	unsigned r(0), a, b;
	if (c > d) {
		a = c;
		b = d;
	}
	else {
		a = d;
		b = c;
	}
	do {
		r = a % b;
		a = b;
		b = r;
	} while (r != 0);
	return a;
}

long long unsigned RSA::EuclidAlgorithm(long long unsigned e, long long unsigned phi, long long unsigned& d)
{

	long long unsigned a = e;//uint a = e;
	long long unsigned b = phi;//uint b = phi;
	long long  y[2] = { 1, 0 };
	long long  u[2] = { 0, 1 };
	long long  ybuf, ubuf;
	long long unsigned r;//uint r;
	long long unsigned q;//uint q;
	while (b != 0)
	{
		q = a / b;

		r = a % b;
		a = b;
		b = r;

		ybuf = y[1];
		ubuf = u[1];

		y[1] = y[0] - q * y[1];
		u[1] = u[0] - q * u[1];

		y[0] = ybuf;
		u[0] = ubuf;

	}

	if (a == 1) {
		d = y[0] % phi;
	}
	return a;
}



CString RSA::Crypt(CString OTXT) {
	wchar_t temp;
	CString CTXT(L"");
	for (int i = 0; i < OTXT.GetLength(); i++) {
		temp = OTXT[i];
		long long unsigned simbol = modexp(temp, e, n);
		CTXT += to_string(simbol).c_str();
		CTXT += " ";
	}
	return CTXT;
}


CString RSA::Decrypt(CString CTXT) {
	wchar_t c, check(' ');
	string str("");
	CString OTXT(L"");
	long long unsigned temp;
	for (int i = 0; i < CTXT.GetLength(); i++) {
		while ((int)CTXT[i] != 32) {
			str += CTXT[i];
			i++;
		}
		temp = stoul(str);
		c = modexp(temp, d, n);
		str = "";
		str += c;
		OTXT += str.c_str();
		str = "";
	}
	return OTXT;
}

void RSA::newpq() {
	srand(time(NULL));
	do {
		p = rand() % (1 << 15) + (1 << 15);
		if (p % 2 == 0)	p--;
	} while (ferma(p) == false);
	do {
		q = rand() % (1 << 15) + (1 << 15);
		if (q % 2 == 0)	q--;
		if (q == p) q = rand() % (1 << 15) + (1 << 15);
	} while (ferma(q) == false || q == p);
	n = p * q;
	phi = (p - 1) * (q - 1);
	do
	{
		e = rand() % phi;
	} while (EuclidAlgorithm(e, phi, d) != 1 || d <= 0 || e < 11500 || d > 80000000);
}

RSA Test;

void CRSADlg::OnBnClickedRsa2()
{
	Test.newpq();
	q = Test.q;
	p = Test.p;
	z = Test.d;
	e = Test.e;
	n = Test.n;
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedCr()
{
	UpdateData(TRUE);
	if (IsDlgButtonChecked(IDC_CR)) CTXT = Test.Crypt(OTXT);
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedDec()
{
	UpdateData(TRUE);
	if (IsDlgButtonChecked(IDC_DEC))OTXT = Test.Decrypt(CTXT);
	UpdateData(FALSE);
}
