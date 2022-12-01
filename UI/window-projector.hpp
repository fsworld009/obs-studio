#pragma once

#include <QSize>
#include <obs.hpp>
#include "qt-display.hpp"
#include "multiview.hpp"
#include <QMenu>
#include <vector>

enum class ProjectorType {
	Source,
	Scene,
	Preview,
	StudioProgram,
	Multiview,
};

class QMouseEvent;

class OBSProjector : public OBSQTDisplay {
	Q_OBJECT

private:
	OBSWeakSourceAutoRelease weakSource;
	OBSSignal destroyedSignal;

	static void OBSRenderMultiview(void *data, uint32_t cx, uint32_t cy);
	static void OBSRender(void *data, uint32_t cx, uint32_t cy);
	static void OBSSourceDestroyed(void *data, calldata_t *params);

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void enterEvent(QEnterEvent *) override;
	void leaveEvent(QEvent *) override;
	void closeEvent(QCloseEvent *event) override;

	bool hideFrame;
	bool isAlwaysOnTop;
	bool isAlwaysOnTopOverridden = false;
	int savedMonitor = -1;
	ProjectorType type = ProjectorType::Source;

	Multiview *multiview = nullptr;

	bool ready = false;

	void UpdateMultiview();
	void UpdateProjectorTitle(QString name);

	QRect prevGeometry;
	void SetMonitor(int monitor);

	QScreen *screen = nullptr;
	QSize GetTargetSize();
	QMenu *GetWindowResizeMenu();
	std::pair<int, int> GetScaledSize(int scale);
	QRect GetScreenSize();
	std::vector<int> GetResizeScalePresets();

	QPoint onMousePressMouseOffset;

private slots:
	void EscapeTriggered();
	void OpenFullScreenProjector();
	void ResizeToContent();
	void ResizeToScale(int scale);
	void ResizeToResolution(int width, int height);
	void OpenCustomWindowSizeDialog();
	void OpenWindowedProjector();
	void AlwaysOnTopToggled(bool alwaysOnTop);
	void ScreenRemoved(QScreen *screen_);

public:
	OBSProjector(QWidget *widget, obs_source_t *source_, int monitor,
		     ProjectorType type_);
	~OBSProjector();

	OBSSource GetSource();
	ProjectorType GetProjectorType();
	int GetMonitor();
	static void UpdateMultiviewProjectors();
	void RenameProjector(QString oldName, QString newName);
	void SetHideCursor();

	bool IsAlwaysOnTop() const;
	bool IsAlwaysOnTopOverridden() const;
	void SetHideFrame(bool hideFrame);
	void SetIsAlwaysOnTop(bool isAlwaysOnTop, bool isOverridden);
	std::vector<std::pair<int, int>> GetResizeResolutionPresets();
};
