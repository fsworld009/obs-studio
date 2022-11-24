#pragma once

#include <obs.hpp>
#include <QComboBox>
#include <QDialog>
#include <QStackedLayout>
#include <QSpinBox>

class OBSProjectorCustomSizeDialog : public QDialog {
	Q_OBJECT

public:
	OBSProjectorCustomSizeDialog(QWidget *parent);

private:
	QComboBox *customMethod;
	QSpinBox *width;
	QSpinBox *height;
	QSpinBox *scale;
	QStackedLayout *inputLayout;
	QSpinBox *CreateSpinBox(int initValue);

signals:
	void ApplyResolution(int width, int height);
	void ApplyScale(int scale);

private slots:
	void ChangeCustomMethod(int index);
	void ConfirmAndClose();
};
