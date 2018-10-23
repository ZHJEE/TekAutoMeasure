#pragma execution_character_set("utf-8")
#include <assert.h>
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
	int DevIte = 1;
	//printf("begin");
	// Open a d efault Session
	status = viOpenDefaultRM(&rm);
	if (status < VI_SUCCESS)
	{
		qDebug() << "error";
		//printf("error");
	}

	//²éÕÒ×ÊÔ´
	status = viFindRsrc(rm ,"?*INSTR" , &list , &itemCnt , desc);
	

	for (i = 0; i < itemCnt; i++) {
		// Open resource found in rsrc list
		status = viOpen(rm, desc, VI_NULL, VI_NULL, &vi);
		//if (status < VI_SUCCESS)
		// Send an ID query.
		status = viWrite(vi, (ViBuf) "*idn?", 5, &retCnt);
		//if (status < VI_SUCCESS)
		// Clear the buffer and read the response
		memset(id, 0, sizeof(id));
		status = viRead(vi, (ViBuf)id, sizeof(id), &retCnt);
		//if (status < VI_SUCCESS)

		// Print the response
		ui->comboBox->addItem(tr("%1").arg(id));		
		// We're done with this device so close it
		viClose(vi);
		// Get the next item
		viFindNext(list, desc);
	}

	viClose(rm);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

double* ReadWaveform(ViSession vi, long* elements) {
	ViStatus	status;
	float		yoffset, ymult;
	ViChar		buffer[256];
	ViChar		c;
	long		count, i;
	double*		ptr = NULL;
	unsigned char		szBuff[256] = { 0, };

	assert(elements != NULL);

	status = viSetAttribute(vi, VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
	status = viSetAttribute(vi, VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);

	// Turn headers off, this makes parsing easier
	status = viPrintf(vi, "header off\n");
	if (status < VI_SUCCESS) goto error;

	// Get record length value
	status = viQueryf(vi, "hor:reco?\n", "%ld", elements);
	if (status < VI_SUCCESS) goto error;

	// Make sure start, stop values for curve query match the full record length
	status = viPrintf(vi, "data:start 1;data:stop %d\n", *elements);
	if (status < VI_SUCCESS) goto error;

	// Get the yoffset to help calculate the vertical values.

	status = viQueryf(vi, "WFMOutpre:YOFF?\n", "%f", &yoffset);
	if (status < VI_SUCCESS) goto error;

	// Get the ymult to help calculate the vertical values.
	status = viQueryf(vi, "WFMOutpre:YMULT?\n", "%f", &ymult);
	if (status < VI_SUCCESS) goto error;

	// Request 8bit binary data on the curve query
	status = viPrintf(vi, "DATA:ENCDG RIBINARY;WIDTH 1\n");
	if (status < VI_SUCCESS) goto error;

	// Request the curve
	status = viPrintf(vi, "CURVE?\n");
	if (status < VI_SUCCESS) goto error;

	// Always flush if a viScanf follows a viPrintf or viBufWrite.
	status = viFlush(vi, VI_WRITE_BUF | VI_READ_BUF_DISCARD);
	if (status < VI_SUCCESS) goto error;

	// Get first char and validate
	status = viSetAttribute(vi, VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_DISABLE);
	status = viScanf(vi, "%c", &c);
	if (status < VI_SUCCESS) goto error;
	assert(c == '#');

	// Get width of element field.
	status = viScanf(vi, "%c", &c);
	if (status < VI_SUCCESS) goto error;
	assert(c >= '0' && c <= '9');

	// Read element characters
	count = c - '0';
	for (i = 0; i < count; i++) {
		status = viScanf(vi, "%c", &c);
		if (status < VI_SUCCESS) goto error;
		assert(c >= '0' && c <= '9');
	}

	// Read waveform into allocated storage
	ptr = (double*)malloc(*elements * sizeof(double));

	for (i = 0; i < *elements; i++) {
		status = viScanf(vi, "%c", &c);
		if (status < VI_SUCCESS) goto error;
		ptr[i] = (((double)c) - yoffset) * ymult;
	}

	status = viFlush(vi, VI_WRITE_BUF | VI_READ_BUF_DISCARD);
	if (status < VI_SUCCESS) goto error;

	return ptr;

error:
	// Report error and clean up
	viStatusDesc(vi, status, buffer);
	fprintf(stderr, "failure: %s\n", buffer);
	if (ptr != NULL) free(ptr);
	return NULL;
}
