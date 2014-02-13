/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <myglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    MyGLWidget *myGLWidget;
    QPushButton *m_boutonDrawNode;
    QPushButton *m_boutonSimulation4;
    QPushButton *m_boutonSimulation3;
    QPushButton *m_boutonSimulation2;
    QPushButton *m_boutonSimulation1;
    QPushButton *m_boutonSimulation5;
    QPushButton *m_boutonStartSimulation;
    QPushButton *m_boutonDrawRoad;
    QPushButton *m_boutonClearWidget;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(796, 553);
        myGLWidget = new MyGLWidget(Window);
        myGLWidget->setObjectName(QStringLiteral("myGLWidget"));
        myGLWidget->setGeometry(QRect(90, 10, 691, 531));
        m_boutonDrawNode = new QPushButton(Window);
        m_boutonDrawNode->setObjectName(QStringLiteral("m_boutonDrawNode"));
        m_boutonDrawNode->setGeometry(QRect(10, 10, 75, 23));
        m_boutonDrawNode->setCheckable(true);
        m_boutonSimulation4 = new QPushButton(Window);
        m_boutonSimulation4->setObjectName(QStringLiteral("m_boutonSimulation4"));
        m_boutonSimulation4->setGeometry(QRect(10, 470, 75, 23));
        m_boutonSimulation3 = new QPushButton(Window);
        m_boutonSimulation3->setObjectName(QStringLiteral("m_boutonSimulation3"));
        m_boutonSimulation3->setGeometry(QRect(10, 440, 75, 23));
        m_boutonSimulation2 = new QPushButton(Window);
        m_boutonSimulation2->setObjectName(QStringLiteral("m_boutonSimulation2"));
        m_boutonSimulation2->setGeometry(QRect(10, 410, 75, 23));
        m_boutonSimulation1 = new QPushButton(Window);
        m_boutonSimulation1->setObjectName(QStringLiteral("m_boutonSimulation1"));
        m_boutonSimulation1->setGeometry(QRect(10, 380, 75, 23));
        m_boutonSimulation5 = new QPushButton(Window);
        m_boutonSimulation5->setObjectName(QStringLiteral("m_boutonSimulation5"));
        m_boutonSimulation5->setGeometry(QRect(10, 500, 75, 23));
        m_boutonStartSimulation = new QPushButton(Window);
        m_boutonStartSimulation->setObjectName(QStringLiteral("m_boutonStartSimulation"));
        m_boutonStartSimulation->setGeometry(QRect(10, 270, 75, 23));
        m_boutonDrawRoad = new QPushButton(Window);
        m_boutonDrawRoad->setObjectName(QStringLiteral("m_boutonDrawRoad"));
        m_boutonDrawRoad->setGeometry(QRect(10, 40, 75, 23));
        m_boutonClearWidget = new QPushButton(Window);
        m_boutonClearWidget->setObjectName(QStringLiteral("m_boutonClearWidget"));
        m_boutonClearWidget->setGeometry(QRect(10, 300, 75, 23));

        retranslateUi(Window);
        QObject::connect(m_boutonSimulation1, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation1()));
        QObject::connect(m_boutonSimulation2, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation2()));
        QObject::connect(m_boutonSimulation3, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation3()));
        QObject::connect(m_boutonSimulation4, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation4()));
        QObject::connect(m_boutonSimulation5, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation5()));
        QObject::connect(m_boutonStartSimulation, SIGNAL(clicked()), myGLWidget, SLOT(StartSimulation()));
        QObject::connect(m_boutonDrawNode, SIGNAL(pressed()), myGLWidget, SLOT(DrawNodePressed()));
        QObject::connect(m_boutonDrawRoad, SIGNAL(pressed()), myGLWidget, SLOT(DrawRoadPressed()));
        QObject::connect(m_boutonClearWidget, SIGNAL(pressed()), myGLWidget, SLOT(ClearWidget()));

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "Window", 0));
        m_boutonDrawNode->setText(QApplication::translate("Window", "Draw Node", 0));
        m_boutonSimulation4->setText(QApplication::translate("Window", "Simulation4", 0));
        m_boutonSimulation3->setText(QApplication::translate("Window", "Simulation3", 0));
        m_boutonSimulation2->setText(QApplication::translate("Window", "Simulation2", 0));
        m_boutonSimulation1->setText(QApplication::translate("Window", "Simulation1", 0));
        m_boutonSimulation5->setText(QApplication::translate("Window", "Simulation5", 0));
        m_boutonStartSimulation->setText(QApplication::translate("Window", "Start", 0));
        m_boutonDrawRoad->setText(QApplication::translate("Window", "Draw Road", 0));
        m_boutonClearWidget->setText(QApplication::translate("Window", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
