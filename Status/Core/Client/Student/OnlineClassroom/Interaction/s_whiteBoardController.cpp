#include "s_whiteBoardController.h"

s_whiteBoardController::s_whiteBoardController(SOnlineClassroomWidget *online_classroom_widget, QObject *parent)
	: QObject(parent), m_online_classroom_widget(online_classroom_widget) {
	this->connect(this->m_online_classroom_widget->board(), &WhiteBoard::paintCommandReady, this, &s_whiteBoardController::sendPaintCommand);
}

s_whiteBoardController::~s_whiteBoardController() {

}

void s_whiteBoardController::createPaintConnection(QMap<QString, QVariant> &data) {
	/*
		/*
		|-data(QMap<QString, QVariant>)
			|-course_id(QString)
			|-lesson_id(QString)
			|-uid(QString)
	*/
	QJsonObject paint_request_json_obj;
	this->m_paint_connection = new Connection;
	QThread *connection_thread = new QThread(this->m_online_classroom_widget);
	this->m_paint_connection->moveToThread(connection_thread);
	connection_thread->start();

	this->m_paint_connection->connect(ReadConf::G_SOCKET_HOST, ReadConf::G_SOCKET_PORT);
	paint_request_json_obj["command"] = TransportCmd::CreatePaintConnection;
	paint_request_json_obj["account_type"] = AccountType::Student;
	paint_request_json_obj["course_id"] = data["course_id"].toString();
	paint_request_json_obj["lesson_id"] = data["lesson_id"].toString();
	paint_request_json_obj["uid"] = data["uid"].toString();

	this->m_paint_connection->send(paint_request_json_obj);

	this->setPaintConnectionSendBaseInfo(data["uid"].toString(), data["course_id"].toString(), data["lesson_id"].toString());

	// �����źŰ�
	this->connect(this->m_paint_connection, &Connection::bufferReadyRead, this, &s_whiteBoardController::handlePaintConnectionRecv);

	return;
}

void s_whiteBoardController::distroyPaintConnection() {
	QThread *thread = this->m_paint_connection->thread();
	delete this->m_paint_connection;
	this->m_paint_connection = nullptr;
	thread->exit(0);

	return;
}

void s_whiteBoardController::handlePaintConnectionRecv() {
	QJsonObject data = this->m_paint_connection->recv();
	TransportCmd cmd = TransportCmd(data["command"].toInt());

	switch (cmd) {
	case TransportCmd::PaintCommand: handleCommandPaintCommand(data); break;
	}

	return;
}

void s_whiteBoardController::handleCommandPaintCommand(QJsonObject &data) {
	this->m_online_classroom_widget->board()->paintByPaintCommand(data);

	return;
}

void s_whiteBoardController::sendPaintCommand(QJsonObject &data) {
	data["command"] = TransportCmd::PaintCommand;
	data["account_type"] = AccountType::Student;
	data["course_id"] = this->m_send_base_info["course_id"].toString();
	data["lesson_id"] = this->m_send_base_info["lesson_id"].toString();
	data["uid"] = this->m_send_base_info["uid"].toString();

	this->m_paint_connection->realSend(data);
}

void s_whiteBoardController::setPaintConnectionSendBaseInfo(QString uid, QString course_id, QString lesson_id) {
	this->m_send_base_info["uid"] = uid;
	this->m_send_base_info["course_id"] = course_id;
	this->m_send_base_info["lesson_id"] = lesson_id;

	return;
}