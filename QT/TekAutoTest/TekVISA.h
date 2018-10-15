#ifndef INTERLOCUTOR_H
#define INTERLOCUTOR_H

#include <string>
#include "cstring"
#include <queue>
#include <sstream>
#include "visa.h"
#include "visatype.h"
#include <QWidget>

class tekVisa : public QWidget
{
	Q_OBJECT
public:
	explicit tekVisa(QWidget *parent);

        bool openSession();
        //bool closeSession();

private:
        ViSession	rm = VI_NULL, rm1 = VI_NULL,rm2 = VI_NULL,rm3 = VI_NULL,vi = VI_NULL;
        ViStatus	status;
        //ViChar		buffer[256];
		ViChar		desc[256], id[256], buffer[256];
        ViUInt32	retCnt , itemCnt;
		ViFindList	list;
};

#endif // INTERLOCUTOR_H
