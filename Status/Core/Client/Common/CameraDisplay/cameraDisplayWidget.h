#pragma once
#include <QWidget>
#include "ui_c_cameraDisplayWidget.h"


class CameraDisplayWidget : public QWidget {
	Q_OBJECT

public:
	CameraDisplayWidget(QWidget *parent = nullptr);
	virtual ~CameraDisplayWidget();
	const Ui::CameraDisplayWidget& ui() const { return this->m_ui; };
	
	void mineCameraDisplay(QImage &frame);

protected:
	Ui::CameraDisplayWidget m_ui;
};
