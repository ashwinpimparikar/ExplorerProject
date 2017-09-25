#ifndef FILEDIALOG_H
#define FILEDIALOG_H

class QEvent;

#include <QFileDialog>
#include <QString>

class FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    explicit FileDialog(QWidget *parent = 0);
public:
    bool eventFilter(QObject *o, QEvent *e);
    void setTopDir(const QString &path);
    QString topDir() const;
private:
    bool pathFits(const QString &path) const;
private slots:
    void checkHistory();
    void checkGoToParent();
    void checkLineEdit(const QString &text);
private:
    QString mtopDir;
};

#endif // FILEDIALOG_H
