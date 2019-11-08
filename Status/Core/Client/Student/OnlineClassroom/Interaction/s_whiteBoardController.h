#pragma once
#pragma execution_character_set("utf-8")
#include <QThread>
#include "Core/Client/Student/OnlineClassroom/s_onlineclassroomWidget.h"
#include "Core/Network/socket.h"
#include "Core/Client/onlineEdu.h"
#include "Core/Client/conf.h"


class s_whiteBoardController : public QObject {
	Q_OBJECT

public:
	s_whiteBoardController(SOnlineClassroomWidget *online_classroom_widget, QObject *parent = nullptr);
	virtual ~s_whiteBoardController();

	void createPaintConnection(QMap<QString, QVariant> &data);
	void distroyPaintConnection();

protected:
	void handlePaintConnectionRecv();
	void handleCommandPaintCommand(QJsonObject &data);
	void sendPaintCommand(QJsonObject &data);

	void setPaintConnectionSendBaseInfo(QString uid, QString course_id, QString lesson_id);
	
	SOnlineClassroomWidget *m_online_classroom_widget;
	Connection *m_paint_connection;  // �����Tcp����
	QMap<QString, QVariant> m_send_base_info;
};