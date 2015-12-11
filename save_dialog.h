#ifndef SAVE_DIALOG_H
#define SAVE_DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QComboBox>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
	Q_OBJECT

	public:
	explicit SaveDialog(QWidget *parent = 0);
	~SaveDialog();

	QPushButton *but_save;
	QLineEdit *in_path;
	QFileDialog *fd;
	QComboBox *cb_presets;

	public slots:
	void selectPreset();
	void updateButton(QString s);
	void selectFolder();

	private:
	Ui::SaveDialog *ui;
};

#endif // SAVE_DIALOG_H
