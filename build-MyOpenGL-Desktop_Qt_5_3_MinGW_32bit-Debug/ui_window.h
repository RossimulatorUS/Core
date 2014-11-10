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
    QTabWidget *Display;
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
    QRadioButton *m_radioButtonExponentielle;
    QLineEdit *m_lineEditTauxExponentielle;
    QWidget *tab_2;
    QPushButton *m_boutonDrawRoad;
    QLabel *label_3;
    QCheckBox *m_checkboxOneWay;
    QSpinBox *m_spinBoxNombreDeVoies;
    QWidget *tab_3;
    QWidget *tab_4;
    QLineEdit *currentScale;
    QLabel *label_4;
    QLineEdit *xOffset;
    QLineEdit *yOffset;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *offsetRight;
    QPushButton *offsetDown;
    QPushButton *offsetUp;
    QPushButton *offsetLeft;
    QLabel *m_labelTimer;
    QGroupBox *groupBox;
    QLineEdit *m_lineEditNorth;
    QLineEdit *m_lineEditEast;
    QLineEdit *m_lineEditWest;
    QLineEdit *m_lineEditSouth;
    QPushButton *pushButton;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(996, 675);
        myGLWidget = new MyGLWidget(Window);
        myGLWidget->setObjectName(QStringLiteral("myGLWidget"));
        myGLWidget->setEnabled(true);
        myGLWidget->setGeometry(QRect(90, 10, 891, 511));
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
        Display = new QTabWidget(Window);
        Display->setObjectName(QStringLiteral("Display"));
        Display->setGeometry(QRect(0, 530, 1001, 151));
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
        m_groupBoxDistribution->setGeometry(QRect(170, 10, 631, 101));
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
        m_radioButtonExponentielle = new QRadioButton(m_groupBoxDistribution);
        m_radioButtonExponentielle->setObjectName(QStringLiteral("m_radioButtonExponentielle"));
        m_radioButtonExponentielle->setGeometry(QRect(10, 80, 82, 17));
        m_lineEditTauxExponentielle = new QLineEdit(m_groupBoxDistribution);
        m_lineEditTauxExponentielle->setObjectName(QStringLiteral("m_lineEditTauxExponentielle"));
        m_lineEditTauxExponentielle->setGeometry(QRect(120, 80, 113, 20));
        Display->addTab(tab, QString());
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
        Display->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        Display->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        currentScale = new QLineEdit(tab_4);
        currentScale->setObjectName(QStringLiteral("currentScale"));
        currentScale->setGeometry(QRect(90, 10, 113, 20));
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 71, 16));
        xOffset = new QLineEdit(tab_4);
        xOffset->setObjectName(QStringLiteral("xOffset"));
        xOffset->setGeometry(QRect(90, 40, 113, 20));
        yOffset = new QLineEdit(tab_4);
        yOffset->setObjectName(QStringLiteral("yOffset"));
        yOffset->setGeometry(QRect(90, 70, 113, 20));
        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 40, 71, 16));
        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 70, 71, 16));
        offsetRight = new QPushButton(tab_4);
        offsetRight->setObjectName(QStringLiteral("offsetRight"));
        offsetRight->setGeometry(QRect(930, 30, 61, 51));
        offsetDown = new QPushButton(tab_4);
        offsetDown->setObjectName(QStringLiteral("offsetDown"));
        offsetDown->setGeometry(QRect(870, 60, 61, 51));
        offsetUp = new QPushButton(tab_4);
        offsetUp->setObjectName(QStringLiteral("offsetUp"));
        offsetUp->setGeometry(QRect(870, 10, 61, 51));
        offsetLeft = new QPushButton(tab_4);
        offsetLeft->setObjectName(QStringLiteral("offsetLeft"));
        offsetLeft->setGeometry(QRect(810, 30, 61, 51));
        Display->addTab(tab_4, QString());
        m_labelTimer = new QLabel(Window);
        m_labelTimer->setObjectName(QStringLiteral("m_labelTimer"));
        m_labelTimer->setGeometry(QRect(10, 510, 71, 16));
        groupBox = new QGroupBox(Window);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 170, 91, 201));
        m_lineEditNorth = new QLineEdit(groupBox);
        m_lineEditNorth->setObjectName(QStringLiteral("m_lineEditNorth"));
        m_lineEditNorth->setGeometry(QRect(20, 30, 51, 20));
        m_lineEditEast = new QLineEdit(groupBox);
        m_lineEditEast->setObjectName(QStringLiteral("m_lineEditEast"));
        m_lineEditEast->setGeometry(QRect(40, 60, 51, 20));
        m_lineEditWest = new QLineEdit(groupBox);
        m_lineEditWest->setObjectName(QStringLiteral("m_lineEditWest"));
        m_lineEditWest->setGeometry(QRect(0, 90, 51, 20));
        m_lineEditSouth = new QLineEdit(groupBox);
        m_lineEditSouth->setObjectName(QStringLiteral("m_lineEditSouth"));
        m_lineEditSouth->setGeometry(QRect(20, 120, 51, 20));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 160, 75, 23));

        retranslateUi(Window);
        QObject::connect(m_boutonSimulation1, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation1()));
        QObject::connect(m_boutonSimulation4, SIGNAL(pressed()), myGLWidget, SLOT(CreateSimulation4()));
        QObject::connect(m_boutonStartSimulation, SIGNAL(clicked()), myGLWidget, SLOT(StartSimulation()));
        QObject::connect(m_boutonDrawRoad, SIGNAL(pressed()), myGLWidget, SLOT(DrawRoadPressed()));
        QObject::connect(m_boutonDrawSource, SIGNAL(pressed()), myGLWidget, SLOT(DrawSourcePressed()));

        Display->setCurrentIndex(3);


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
        m_lineEditTauxUniforme->setText(QApplication::translate("Window", "1000", 0));
        label_2->setText(QApplication::translate("Window", "ms : ", 0));
        m_lineEditTauxBernouilli->setText(QApplication::translate("Window", "0.08", 0));
        m_lineEditTauxBernouilli->setPlaceholderText(QString());
        label->setText(QApplication::translate("Window", "Taux : ", 0));
        m_radioButtonExponentielle->setText(QApplication::translate("Window", "Exponentielle", 0));
        m_lineEditTauxExponentielle->setText(QApplication::translate("Window", "1.5", 0));
        Display->setTabText(Display->indexOf(tab), QApplication::translate("Window", "Noeud", 0));
        m_boutonDrawRoad->setText(QApplication::translate("Window", "Draw Road", 0));
        label_3->setText(QApplication::translate("Window", "Nombre de voies :", 0));
        m_checkboxOneWay->setText(QApplication::translate("Window", "One way", 0));
        Display->setTabText(Display->indexOf(tab_2), QApplication::translate("Window", "Route", 0));
        Display->setTabText(Display->indexOf(tab_3), QApplication::translate("Window", "Statistiques", 0));
        currentScale->setText(QApplication::translate("Window", "1.0", 0));
        currentScale->setPlaceholderText(QString());
        label_4->setText(QApplication::translate("Window", "Current scale:", 0));
        xOffset->setText(QApplication::translate("Window", "0.0", 0));
        xOffset->setPlaceholderText(QString());
        yOffset->setText(QApplication::translate("Window", "0.0", 0));
        yOffset->setPlaceholderText(QString());
        label_5->setText(QApplication::translate("Window", "X offset:", 0));
        label_6->setText(QApplication::translate("Window", "Y offset:", 0));
        offsetRight->setText(QApplication::translate("Window", "RIGHT", 0));
        offsetDown->setText(QApplication::translate("Window", "DOWN", 0));
        offsetUp->setText(QApplication::translate("Window", "UP", 0));
        offsetLeft->setText(QApplication::translate("Window", "LEFT", 0));
        Display->setTabText(Display->indexOf(tab_4), QApplication::translate("Window", "Page", 0));
        m_labelTimer->setText(QApplication::translate("Window", "TextLabel", 0));
        groupBox->setTitle(QApplication::translate("Window", "Importation", 0));
        m_lineEditNorth->setText(QApplication::translate("Window", "45.3825079", 0));
        m_lineEditEast->setText(QApplication::translate("Window", "-71.9212199", 0));
        m_lineEditWest->setText(QApplication::translate("Window", "-71.9330645", 0));
        m_lineEditSouth->setText(QApplication::translate("Window", "45.3758762", 0));
        pushButton->setText(QApplication::translate("Window", "Import", 0));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
