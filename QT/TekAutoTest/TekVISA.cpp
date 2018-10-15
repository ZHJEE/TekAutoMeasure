#include "TekVISA.h"
#include <iostream>
#include <QDebug>
#include <QMessageBox>
tekVisa::tekVisa(QWidget *parent)
{
	//openSession();

}
bool tekVisa::openSession()
{
    // Open a d efault Session
    status = viOpenDefaultRM(&rm);
	
	if (status < VI_SUCCESS)
	{
	QMessageBox::information(this, tr("Information"), tr("Could no open a session to the VISA Resource!"), QMessageBox::Ok);
	}

	//USB::0x0699::0x03A3::C010603::INSTR
	// Find all USB devices
	//status = viFindRsrc(rm, (ViString)"USB::0x0699::0x03A3::C010603::INSTR", 
	//					&list, &itemCnt ,desc);
	//if (status != VI_SUCCESS)
	//{
	//	qDebug() << "Cann't queries a VISA system to locate the resources"
	//		" associated with a specified interface";
	//	viClose(rm);
	//	return false;
	//}
	//status = viOpen(rm, (ViString)"USB::0x0699::0x03A3::C010603::INSTR",
	//				VI_NULL, VI_NULL, &vi);
	if (status = VI_SUCCESS)
		qDebug() << "viOpen SUCCESS";

		
	return 1;

}