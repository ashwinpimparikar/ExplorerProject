
#include "filedialog.h"

#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QList>
#include <QToolButton>
#include <QDir>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QEvent>
#include <QKeyEvent>
#include <QAbstractButton>
#include <QCompleter>
#include <QAbstractItemView>
#include <QFileInfo>

FileDialog::FileDialog(QWidget *parent) :
    QFileDialog(parent)
{
    connect(this, SIGNAL(directoryEntered(QString)), this, SLOT(checkHistory()));
    connect(this, SIGNAL(directoryEntered(QString)), this, SLOT(checkGoToParent()));
    connect(findChild<QToolButton *>("backButton"), SIGNAL(clicked()), this, SLOT(checkGoToParent()));
    connect(findChild<QToolButton *>("forwardButton"), SIGNAL(clicked()), this, SLOT(checkGoToParent()));
    connect(findChild<QLineEdit *>("fileNameEdit"), SIGNAL(textChanged(QString)), this, SLOT(checkLineEdit(QString)));
    findChild<QLineEdit *>("fileNameEdit")->installEventFilter(this);
    findChild<QWidget *>("listView")->installEventFilter(this);
    findChild<QWidget *>("treeView")->installEventFilter(this);
    findChild<QLineEdit *>("fileNameEdit")->completer()->popup()->installEventFilter(this);
    setOption(DontUseNativeDialog, true);
}

bool FileDialog::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() != QEvent::KeyPress)
        return false;
    int key = static_cast<QKeyEvent *>(e)->key();
    if (o->objectName() == "listView" || o->objectName() == "treeView")
    {
        return (Qt::Key_Backspace == key && !pathFits(directory().absolutePath()));
    }
    else
    {
        if (Qt::Key_Return != key && Qt::Key_Enter != key)
            return false;
        QString text = findChild<QLineEdit *>("fileNameEdit")->text();
        QString path = QDir::cleanPath(directory().absolutePath() + (text.startsWith("/") ? "" : "/") + text);
        bool a = QDir(text).isAbsolute();
        return !((!a && pathFits(path)) || (a && pathFits(text)));
    }
}

void FileDialog::setTopDir(const QString &path)
{
    if (path == mtopDir)
        return;
    mtopDir = (!path.isEmpty() && QFileInfo(path).isDir()) ? path : QString();
    if (!pathFits(path))
    {
        setDirectory(mtopDir);
        checkHistory();
        checkLineEdit(findChild<QLineEdit *>("fileNameEdit")->text());
    }
    else
    {
        QLineEdit *ledt = findChild<QLineEdit *>("fileNameEdit");
        ledt->setText(ledt->text());
    }
    findChild<QWidget *>("lookInCombo")->setEnabled(mtopDir.isEmpty());
    findChild<QWidget *>("sidebar")->setEnabled(mtopDir.isEmpty());
    checkGoToParent();
}

QString FileDialog::topDir() const
{
    return mtopDir;
}

bool FileDialog::pathFits(const QString &path) const
{
    return mtopDir.isEmpty() || (path.startsWith(mtopDir) && path.length() > mtopDir.length());
}

void FileDialog::checkHistory()
{
    QStringList list = history();
    for (int i = list.size() - 1; i >= 0; --i)
        if (!pathFits(list.at(i)))
            list.removeAt(i);
    setHistory(list);
}

void FileDialog::checkGoToParent()
{
    findChild<QToolButton *>("toParentButton")->setEnabled(pathFits(directory().absolutePath()));
}

void FileDialog::checkLineEdit(const QString &text)
{
    QAbstractButton *btn = findChild<QDialogButtonBox *>("buttonBox")->buttons().first();
    QString path = QDir::cleanPath(directory().absolutePath() + (text.startsWith("/") ? "" : "/") + text);
    bool a = QDir(text).isAbsolute();
    btn->setEnabled(btn->isEnabled() && ((!a && pathFits(path)) || (a && pathFits(text))));
}

