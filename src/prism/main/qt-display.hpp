#pragma once

#include <QWidget>
#include <obs.hpp>
#include <QLabel>
#include <QVBoxLayout>

#define GREY_COLOR_BACKGROUND 0xFF4C4C4C
#define OBJECT_MAIN_PREVIEW "mainPreviewDisplay"

class PLSQTDisplay : public QWidget {
	Q_OBJECT
	Q_PROPERTY(QColor displayBackgroundColor MEMBER backgroundColor READ GetDisplayBackgroundColor WRITE SetDisplayBackgroundColor)

	OBSDisplay display;
	QLabel *displayText;
	QLabel *resizeScreen;
	QLabel *resizeCenter;
	OBSSource source;
	bool isResizing = false;
	bool isDisplayActive = false;

	void CreateDisplay();
	void AdjustResizeUI();

	virtual bool eventFilter(QObject *object, QEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	void resizeManual();

signals:
	void DisplayCreated(PLSQTDisplay *window);
	void DisplayResized();
	void AdjustResizeView(QLabel *screen, QLabel *view, bool &handled);

public slots:
	void OnSourceStateChanged();
	void UpdateSourceState(obs_source_t *source);
	void beginResizeSlot();
	void endResizeSlot();

public:
	static void OnSourceCaptureState(void *data, calldata_t *calldata);

	explicit PLSQTDisplay(QWidget *parent = nullptr, Qt::WindowFlags flags = nullptr);
	virtual ~PLSQTDisplay();

	virtual QPaintEngine *paintEngine() const override;

	inline obs_display_t *GetDisplay() const { return display; }

	uint32_t backgroundColor = GREY_COLOR_BACKGROUND;

	QColor GetDisplayBackgroundColor() const;
	void SetDisplayBackgroundColor(const QColor &color);
	void UpdateDisplayBackgroundColor();

	void AttachSource(OBSSource src) { source = src; }
};