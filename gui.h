#ifndef GUI_H
#define GUI_H
#include <QtWidgets/QMainWindow>
#include <Qt>
#include <QGraphicsView>
#include <QtWidgets/QToolBar>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include <QToolBar>
#include "Graphics.h"
#include "Painter.h"
#include "DescriptionVisitor.h"
#include "DrawerVisitor.h"
#include "GraphicsFactory.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <utility>
#include "util.h"

using namespace std;


class gui: public QMainWindow
{
    Q_OBJECT
    public:
        gui();
        virtual ~gui();
        QGraphicsView *graphicsView;
        QGraphicsScene *scene;
        QWidget *widget;

        void Display();
        void CreateView();
        void MessageBox(const QString _message);
        void CreateActions();
        void CreateMenus();
        void SetActionConnection();

    protected:

    private:
        QAction *aboutDeveloper;
        QAction *fileLoad;
        QAction *fileSave;
        QAction *fileLoad_tool;
        QAction *fileSave_tool;
        QAction *lock;
        QAction *unlock;
        QAction *newCir;
        QAction *newRec;
        QAction *newSqu;
        QAction *undo;
        QAction *redo;
        QAction *createSquare;
        QAction *createRectangle;
        QAction *createCircle;
        QAction *removeItem;
        QMenu *about;
        QMenu *file;
        QMenu *createShape;
        QToolBar *toolBar;
        GraphicsFactory gf;
        vector<Graphics *> gs;
    private slots:
        void save(string s);
        void drawOnCanvas();
        void MessageDialog();
        void Group();
        void UnGroup();
        void LoadFile();
        void SaveFile();
        void CreateSquare();
        void CreateRectangle();
        void CreateCircle();
        void Remove();

};

#endif // GUI_H
