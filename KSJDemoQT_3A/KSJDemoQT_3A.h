#ifndef KSJDEMOQT_BASE_H
#define KSJDEMOQT_BASE_H

#include <QtWidgets/QDialog>
#include "ui_KSJDemoQT_3A.h"

#include "..\Common\KSJ_GS.H"
#include "..\KSJApi.Inc\KSJApi.h"

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi64.lib" )
#else
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi64.lib" )
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi.lib" )
#else
#pragma comment( lib, "..\\KSJApi.Lib\\KSJApi.lib" )
#endif
#endif

#define MAX_DEVICE    64

struct DEVICEINFO
{
	int                 nIndex;
	KSJ_DEVICETYPE		DeviceType;
	int					nSerials;
	WORD				wFirmwareVersion;
	WORD                wFpgaVersion;
};

class KSJDemoQT_3A : public QDialog
{
    Q_OBJECT

public:
    explicit KSJDemoQT_3A(QWidget *parent = 0);
    ~KSJDemoQT_3A();


private slots:
    void on_DEVICE_LIST_ComboBox_currentIndexChanged(int index);

    void on_ExposureTimeSpinBox_valueChanged(int arg1);

    void on_ExposureLinesSpinBox_valueChanged(int arg1);

    void on_GainSpinBox_valueChanged(int arg1);

    void on_SetPreviewFovButton_clicked();


    void on_PreviewButton_clicked();

    void on_SetCaptureFovButton_clicked();

    void on_CaptureButton_clicked();

	void on_ShowCheckBox_clicked(bool arg1);

	void on_AESetRegionButton_clicked();

	void on_AEStartButton_clicked();

	void on_AFSetRegionButton_clicked();

	void on_AFStartButton_clicked();
private:
    Ui::KSJDemoQT_3A *ui;
	int m_nDeviceNum;
	int m_nDeviceCurSel;
	DEVICEINFO    m_DeviceInfo[MAX_DEVICE];
	QVector<QRgb> m_vcolorTable; //生成灰度颜色表
	bool  m_bPreview;
	bool  m_bAEStart;
	bool  m_bAFStart;
	QColor m_col;
public:
	void UpdateInterfaceFunction();
	void UpdateInterface();
	void UpdateDeviceList();
	void GetRealExposureTime();
	void ConvetData(unsigned char *pData, int nWidth, int nHeight, int nBitCount, unsigned char* pConvertData);
	void ShowErrorInfo(int nRet);
	void AeCallback(KSJ_AE_STATUS Status, int nResult);
	void AfCallback(int nResult);
};

#endif // KSJDEMOQT_BASE_H
