#pragma execution_character_set("utf-8")  
#include <QApplication>
#include "Core/Model/user.h"
#include "Core/Client/conf.h"
#include "Core/Client/Common/Login/loginWindow.h"


User *user = nullptr;

int main(int argc, char *argv[]) {
	/*
		这里别乱动
	*/
	QApplication app(argc, argv);
	ReadConf::read();

	LoginWindow *login_win = new LoginWindow;
	login_win->show();

	/*
		测试写这里	
	*/

	return app.exec();
}
