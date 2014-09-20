/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <myglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    MyGLWidget *myGLWidget;
    QPushButton *m_boutonSimulation4;
    QPushButton *m_boutonSimulation1;
    QPushButton *m_boutonStartSimulation;
    QFrame *line;
    QTabWidget *m_tabSimulation;
    QWidget *tab;
    QPushButton *m_boutonDrawSource;
    QGroupBox *m_groupBoxTypeNoeud;
    QRadioButton *m_radioButtonIntersection;
    QRadioButton *m_radioButtonSource;
    QGroupBox *m_groupBoxDistribution;
    QRadioButton *m_radioButtonBernouilli;
    QRadioButton *m_radioButtonUniforme;
    QLineEdit *m_lineEditTauxUniforme;
    QLabel *label_2;
    QLineEdit *m_lineEditTauxBernouilli;
    QLabel *label;
    QWidget *tab_2;
    QPushButton *m_boutonDrawRoad;
    QLabel *label_3;
    QCheckBox *m_checkboxOneWay;
    QSpinBox *m_spinBoxNombreDeVoies;
    QWidget *tab_3;
    QLabel *m_labelTimer;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(996, 675);
        myGLWidget = new MyGLWidget(Window);
        myGLWidget->setObjectName(QStringLiteral("myGLWidget"));
        myGLWidget->setGeometry(QRect(90, 10, 891, 531));
        m_boutonSimulation4 = new QPushButton(Window);
        m_boutonSimulation4->setObjectName(QStringLiteral("m_boutonSimulation4"));
        m_boutonSimulation4->setGeometry(QRect(10, 130, 75, 23));
        m_boutonSimulation1 = new QPushButton(Window);
        m_boutonSimulation1->setObjectName(QStringLiteral("m_boutonSimulation1"));
        m_boutonSimulation1->setGeometry(QRect(10, 100, 75, 23));
        m_boutonStartSimulation = new QPushButton(Window);
        m_boutonStartSimulation->setObjectName(QStringLiteral("m_boutonStartSimulation"));
        m_boutonStartSimulation->setGeometry(QRect(0, 10, 91, 71));
        line = new QFrame(Window);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 80, 91, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        m_tabSimulation = new QTabWidget(Window);
        m_tabSimulation->setObjectName(QStringLiteral("m_tabSimulation"));
        m_tabSimulation->setGeometry(QRect(0, 540, 1001, 141));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        m_boutonDrawSource = new QPushButton(tab);
        m_boutonDrawSource->setObjectName(QStringLiteral("m_boutonDrawSource"));
        m_boutonDrawSource->setGeometry(QRect(840, -10, 161, 131));
        m_groupBoxTypeNoeud = new QGroupBox(tab);
        m_groupBoxTypeNoeud->setObjectName(QStringLiteral("m_groupBoxTypeNoeud"));
        m_groupBoxTypeNoeud->setGeometry(QRect(10, 10, 151, 91));
        m_radioButtonIntersection = new QRadioButton(m_groupBoxTypeNoeud);
        m_radioButtonIntersection->setObjectName(QStringLiteral("m_radioButtonIntersection"));
        m_radioButtonIntersection->setGeometry(QRect(10, 20, 82, 17));
        m_radioButtonSource = new QRadioButton(m_groupBoxTypeNoeud);
        m_radioButtonSource->setObjectName(QStringLiteral("m_radioButtonSource"));
        m_radioButtonSource->setGeometry(QRect(10, 40, 82, 17));
        m_radioButtonSource->setChecked(true);
        m_groupBoxDistribution = new QGroupBox(tab);
        m_groupBoxDistribution->setObjectName(QStringLiteral("m_groupBoxDistribution"));
        m_groupBoxDistribution->setGeometry(QRect(170, 10, 271, 91));
        m_radioButtonBernouilli = new QRadioButton(m_groupBoxDistribution);
        m_radioButtonBernouilli->setObjectName(QStringLiteral("m_radioButtonBernouilli"));
        m_radioButtonBernouilli->setGeometry(QRect(10, 20, 82, 17));
        m_radioButtonBernouilli->setChecked(true);
        m_radioButtonUniforme = new QRadioButton(m_groupBoxDistribution);
        m_radioButtonUniforme->setObjectName(QStringLiteral("m_radioButtonUniforme"));
        m_radioButtonUniforme->setGeometry(QRect(10, 50, 82, 17));
        m_lineEditTauxUniforme = new QLineEdit(m_groupBoxDistribution);
        m_lineEditTauxUniforme->setObjectName(QStringLiteral("m_lineEditTauxUniforme"));
        m_lineEditTauxUniforme->setGeometry(QRect(120, 50, 113, 20));
        label_2 = new QLabel(m_groupBoxDistribution);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 50, 41, 16));
        m_lineEditTauxBernouilli = new QLineEdit(m_groupBoxDistribution);
        m_lineEditTauxBernouilli->setObjectName(QStringLiteral("m_lineEditTauxBernouilli"));
        m_lineEditTauxBernouilli->setGeometry(QRect(120, 20, 113, 20));
        label = new QLabel(m_groupBoxDistribution);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 20, 41, 16));
        m_tabSimulation->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        m_boutonDrawRoad = new QPushButton(tab_2);
        m_boutonDrawRoad->setObjectName(QStringLiteral("m_boutonDrawRoad"));
        m_boutonDrawRoad->setGeometry(QRect(870, 0, 121, 111));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 91, 16));
        m_checkboxOneWay = new QCheckBox(tab_2);
        m_checkboxOneWay->setObjectName(QStringLiteral("m_checkboxOneWay"));
        m_checkboxOneWay->setGeometry(QRect(10, 40, 131, 17));
        m_spinBoxNombreDeVoies = new QSpinBox(tab_2);
        m_spinBoxNombreDeVoies->setObjectName(QStringLiteral("m_spinBoxNombreDeVoies"));
        m_spinBoxNombreDeVoies->setGeometry(QRect(100, 10, 42, 22));
        m_spinBoxNombreDeVoies->setMinimum(1);
        m_spinBoxNombreDeVoies->setMaximum(5);
        m_tabSimulation->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        m_tabSimulation->addTab(tab_3, QString());
        m_labelTimer = new QLabel(Window);
        m_labelTimer->setObjectName(QStringLiteral("m_labelTimer"));
        m_labelTimer->setGeometry(QRect(10, 510, 71, 16));

        retranslateUi(Window);
        QObject::connect(m_boutonSimulation1, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation1()));
        QObject::connect(m_boutonSimulation4, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation4()));
        QObject::connect(m_boutonStartSimulation, SIGNAL(clicked()), myGLWidget, SLOT(StartSimulation()));
        QObject::connect(m_boutonDrawRoad, SIGNAL(pressed()), myGLWidget, SLOT(DrawRoadPressed()));
        QObject::connect(m_boutonDrawSource, SIGNAL(pressed()), myGLWidget, SLOT(DrawSourcePressed()));

        m_tabSimulation->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "Window", 0));
        m_boutonSimulation4->setText(QApplication::translate("Window", "Simulation4", 0));
        m_boutonSimulation1->setText(QApplication::translate("Window", "Simulation1", 0));
        m_boutonStartSimulation->setText(QApplication::translate("Window", "Start", 0));
        m_boutonDrawSource->setText(QApplication::translate("Window", "Draw Node", 0));
        m_groupBoxTypeNoeud->setTitle(QApplication::translate("Window", "Type de noeud", 0));
        m_radioButtonIntersection->setText(QApplication::translate("Window", "Intersection", 0));
        m_radioButtonSource->setText(QApplication::translate("Window", "Source", 0));
        m_groupBoxDistribution->setTitle(QApplication::translate("Window", "Loi de distribution", 0));
        m_radioButtonBernouilli->setText(QApplication::translate("Window", "Bernouilli", 0));
        m_radioButtonUniforme->setText(QApplication::translate("Window", "Uniforme", 0));
        label_2->setText(QApplication::translate("Window", "ms : ", 0));
        m_lineEditTauxBernouilli->setText(QApplication::translate("Window", "0.2", 0));
        m_lineEditTauxBernouilli->setPlaceholderText(QString());
        label->setText(QApplication::translate("Window", "Taux : ", 0));
        m_tabSimulation->setTabText(m_tabSimulation->indexOf(tab), QApplication::translate("Window", "Noeud", 0));
        m_boutonDrawRoad->setText(QApplication::translate("Window", "Draw Road", 0));
        label_3->setText(QApplication::translate("Window", "Nombre de voies :", 0));
        m_checkboxOneWay->setText(QApplication::translate("Window", "One way", 0));
        m_tabSimulation->setTabText(m_tabSimulation->indexOf(tab_2), QApplication::translate("Window", "Route", 0));
        m_tabSimulation->setTabText(m_tabSimulation->indexOf(tab_3), QApplication::translate("Window", "Statistiques", 0));
        m_labelTimer->setText(QApplication::translate("Window", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
