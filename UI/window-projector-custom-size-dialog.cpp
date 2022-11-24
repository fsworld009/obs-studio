#include <limits.h>
#include <QBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include "obs-app.hpp"
#include "window-projector-custom-size-dialog.hpp"

OBSProjectorCustomSizeDialog::OBSProjectorCustomSizeDialog(QWidget *parent)
	: QDialog(parent)
{
	QSize parentSize = parent->size();
	this->setWindowTitle(QTStr("ResizeProjectorWindow"));
	this->setAttribute(Qt::WA_DeleteOnClose);

	QVBoxLayout *layout = new QVBoxLayout(this);

	// Input method dropdown
	customMethod = new QComboBox();
	customMethod->addItem(QTStr("ResizeProjectorWindowCustomResolution"));
	customMethod->addItem(QTStr("ResizeProjectorWindowCustomScale"));
	layout->addWidget(customMethod);
	connect(customMethod,
		QOverload<int>::of(&QComboBox::currentIndexChanged), this,
		&OBSProjectorCustomSizeDialog::ChangeCustomMethod);

	// layout to contain both resolution and scale input
	inputLayout = new QStackedLayout();

	// resolution input
	QFrame *resolutionInput = new QFrame();
	QGridLayout *resolutionInputLayout = new QGridLayout();
	resolutionInput->setLayout(resolutionInputLayout);

	width = CreateSpinBox(parentSize.width());
	resolutionInputLayout->addWidget(width, 0, 0);
	resolutionInputLayout->setColumnStretch(0, 1);
	QLabel *resolutionLabel = new QLabel(QString("x"));
	resolutionInputLayout->addWidget(resolutionLabel, 0, 1);
	height = CreateSpinBox(parentSize.height());
	resolutionInputLayout->addWidget(height, 0, 2);
	resolutionInputLayout->setColumnStretch(2, 1);
	inputLayout->addWidget(resolutionInput);

	// scale input
	QFrame *scaleInput = new QFrame();
	QGridLayout *scaleInputLayout = new QGridLayout();
	scaleInput->setLayout(scaleInputLayout);
	scale = CreateSpinBox(100);
	scaleInputLayout->addWidget(scale, 0, 0);
	scaleInputLayout->setColumnStretch(0, 1);
	QLabel *scaleLabel = new QLabel(QString("%"));
	scaleInputLayout->addWidget(scaleLabel, 0, 1);
	inputLayout->addWidget(scaleInput);

	// only show resolution input on open
	inputLayout->setCurrentIndex(0);

	layout->addLayout(inputLayout);

	// OK button
	QPushButton *okButton = new QPushButton(QTStr("OK"));
	layout->addWidget(okButton);
	connect(okButton, &QPushButton::clicked, this,
		&OBSProjectorCustomSizeDialog::ConfirmAndClose);

	this->setLayout(layout);
}

QSpinBox *OBSProjectorCustomSizeDialog::CreateSpinBox(int initValue)
{
	QSpinBox *spinbox = new QSpinBox();
	spinbox->setMinimum(1);
	spinbox->setMaximum(INT_MAX);
	spinbox->setValue(initValue);
	return spinbox;
}

void OBSProjectorCustomSizeDialog::ChangeCustomMethod(int index)
{
	inputLayout->setCurrentIndex(index);
}

void OBSProjectorCustomSizeDialog::ConfirmAndClose()
{
	if (customMethod->currentIndex() == 0) {
		emit ApplyResolution(width->value(), height->value());
	} else {
		emit ApplyScale(scale->value());
	}
	emit accept();
}
