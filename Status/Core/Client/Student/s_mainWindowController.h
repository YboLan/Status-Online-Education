#pragma once
#pragma execution_character_set("utf-8")  
#include <QStack>
#include "s_mainWindow.h"
#include "Core/Model/user.h"
#include "Core/Model/course.h"
#include "Core/Client/Student/CourseManagement/s_courseManagementController.h"
#include "Core/Client/Student/OnlineClassroom/s_onlineClassroomController.h"
#include "Core/Component/Toast/toast.h"


class SMainWindowController : public QObject {
	Q_OBJECT

public:
	SMainWindowController(SMainWindow *win, User* user);
	virtual ~SMainWindowController();

	void undo();  // 窗口返回
	void redo();  // 窗口前进

	void showCourseManagementWidget();
	void showOnlineClassroomWidget();
	void buttonPush(QAbstractButton *button);

protected:
	SMainWindow *m_win;
	User *m_user;
	SCourseManagementController *m_course_management_controller;
	SOnlineClassroomController *m_online_classroom_controller;
	QStack<QAbstractButton*> m_child_widget_undo_stack;  // 切换子窗的返回栈
	QStack<QAbstractButton*> m_child_widget_redo_stack;  // 切换子窗的前加栈

	void clearWidget();
};