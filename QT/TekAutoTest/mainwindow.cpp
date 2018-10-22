#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	ViSession	rm = VI_NULL, rm1 = VI_NULL, rm2 = VI_NULL, rm3 = VI_NULL, vi = VI_NULL;
	//ViSession	rm, rm1 , rm2 , rm3, vi;
	ViFindList list;
	ViStatus	status;
	ViChar		desc[256], id[256], buffer[256];
	ViUInt32	retCnt, itemCnt;
	ViUInt32	i;

	//printf("begin");
	// Open a d efault Session
	status = viOpenDefaultRM(&rm);
	if (status < VI_SUCCESS)
	{
		qDebug() << "error";
		//printf("error");
	}

	//查找资源
	status = viFindRsrc(rm ,"?*INSTR" , &list , &itemCnt , desc);
	//status = viOpen(rm,"USB::0x0699::0x03A3::C010602::INSTR", VI_NULL, VI_NULL, &vi);
	//qDebug() << "viOpen";
	//status = viWrite(vi, (ViBuf)"*idn?", 5, &retCnt);
	//memset(buffer, 0, sizeof(buffer));
	//status = viRead(vi, (ViBuf) buffer, sizeof(buffer), &retCnt);
	

	// Print the response
	//printf("id: %s\n", buffer);

	ui->listWidget->addItem(tr("--------------------设备列表----------------\n"));
	ui->listWidget->addItem(tr("端口数量: %1\n").arg(itemCnt));
	ui->listWidget->addItem(tr("描述符: %1\n").arg(desc));            //显示找到设备的数量
	

	// Clean up
	viClose(vi); // Not needed, but makes things a bit more understandable
	viClose(rm);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
