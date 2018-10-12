#include "tekmodule.h"
#include <iostream>
#include <QDebug>
genModule::genModule()
{
	openSession();

}
bool genModule::openSession()
{
    // Open a d efault Session
    status = viOpenDefaultRM(&rm);
	qDebug() << "status:"<<status;
	if (status < VI_SUCCESS)
	{
	qDebug() << "Could not open a session to the VISA Resource Manager!\n";
	return 0;
	}
	//USB::0x0699::0x03A3::C010603::INSTR
	// Find all USB devices
	status = viFindRsrc(rm, (ViString)"USB?*INSTR", 
						&list, &itemCnt ,desc);

	return 1;

}