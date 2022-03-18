/********************************************************************************
** Form generated from reading UI file 'rttvis_gui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTTVIS_GUI_H
#define UI_RTTVIS_GUI_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLStereoWidget.h"

QT_BEGIN_NAMESPACE

class Ui_RTTVIS_GUI
{
public:
    QAction *actionHow_to_use_the_interface;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_6;
    QFrame *InputImages;
    QVBoxLayout *Step_1;
    QLabel *step1_label;
    QGridLayout *gridLayout_3;
    QPushButton *push_FOD;
    QPushButton *push_ACT;
    QPushButton *push_Mask;
    QPushButton *push_T1;
    QLineEdit *fname_Mask_line;
    QLineEdit *fname_ACT_line;
    QLineEdit *fname_T1_line;
    QLineEdit *fname_FOD_line;
    QFrame *line_2;
    QLabel *interact_label;
    QFrame *StartTracker;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer;
    QComboBox *FOD_orderOfDirections;
    QCheckBox *FOD_discretization;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *push_start;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGridLayout *gridLayout_14;
    QScrollArea *scrollArea_1;
    QWidget *scrollAreaWidgetContents_4;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_9;
    QLabel *label_29;
    QSpinBox *txt_maxStreamlineCount;
    QLabel *label_31;
    QLabel *label_30;
    QSpinBox *txt_peelNo;
    QDoubleSpinBox *txt_tubeRadius;
    QDoubleSpinBox *txt_addOpacity;
    QSpinBox *txt_batchCount;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_4;
    QDoubleSpinBox *txt_seed_radius;
    QLabel *txt_seed_radius_label;
    QWidget *tab_2;
    QGridLayout *gridLayout_10;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_8;
    QLabel *label_11;
    QDoubleSpinBox *txt_minLength;
    QLabel *txt_minFODamp_label;
    QDoubleSpinBox *txt_stepSize;
    QSpinBox *txt_writeInterval;
    QLabel *label_8;
    QLabel *label_14;
    QLabel *label_27;
    QDoubleSpinBox *txt_dataSupportExponent;
    QLabel *label_12;
    QDoubleSpinBox *txt_minRadiusOfCurvature;
    QLabel *label_13;
    QDoubleSpinBox *txt_maxLength;
    QDoubleSpinBox *txt_minFODamp;
    QLabel *label_9;
    QSpinBox *txt_seed_maxTrials;
    QSpinBox *txt_numberOfThreads;
    QLabel *txt_numberOfThreads_label;
    QComboBox *txt_atMaxLength;
    QComboBox *txt_directionality;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_3;
    QGridLayout *gridLayout_13;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_12;
    QSpinBox *txt_maxEstInterval;
    QLabel *label_15;
    QSpinBox *txt_initMaxEstTrials;
    QLabel *label_19;
    QSpinBox *txt_propMaxEstTrials;
    QLabel *label_20;
    QSpinBox *txt_maxSamplingPerStep;
    QLabel *label_21;
    QCheckBox *check_useBestAtInit;
    QFrame *line_4;
    QLabel *label_22;
    QGridLayout *gridLayout;
    QDoubleSpinBox *txt_probeRadius;
    QSpacerItem *verticalSpacer_5;
    QSpinBox *txt_probeQuality;
    QLabel *label_25;
    QSpinBox *txt_probeCount;
    QLabel *label_16;
    QDoubleSpinBox *txt_ignoreWeakLinks;
    QDoubleSpinBox *txt_probeLength;
    QLabel *label_24;
    QLabel *label_17;
    QLabel *label_23;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_7;
    QLabel *progressText;
    QProgressBar *progressBar;
    QVBoxLayout *verticalLayout_6;
    QVTKOpenGLStereoWidget *qvtkOpenGLStereoWidget;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *push_centerView;
    QPushButton *push_copyToClipboard;
    QLineEdit *txt_coordinates;
    QLabel *txt_info;
    QMenuBar *menuBar;
    QMenu *menuHelp;

    void setupUi(QMainWindow *RTTVIS_GUI)
    {
        if (RTTVIS_GUI->objectName().isEmpty())
            RTTVIS_GUI->setObjectName(QString::fromUtf8("RTTVIS_GUI"));
        RTTVIS_GUI->resize(1272, 1058);
        RTTVIS_GUI->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionHow_to_use_the_interface = new QAction(RTTVIS_GUI);
        actionHow_to_use_the_interface->setObjectName(QString::fromUtf8("actionHow_to_use_the_interface"));
        actionAbout = new QAction(RTTVIS_GUI);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(RTTVIS_GUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(360, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        InputImages = new QFrame(frame);
        InputImages->setObjectName(QString::fromUtf8("InputImages"));
        InputImages->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(InputImages->sizePolicy().hasHeightForWidth());
        InputImages->setSizePolicy(sizePolicy1);
        Step_1 = new QVBoxLayout(InputImages);
        Step_1->setSpacing(0);
        Step_1->setObjectName(QString::fromUtf8("Step_1"));
        Step_1->setContentsMargins(0, 0, 0, 0);
        step1_label = new QLabel(InputImages);
        step1_label->setObjectName(QString::fromUtf8("step1_label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        step1_label->setFont(font);
        step1_label->setLayoutDirection(Qt::LeftToRight);
        step1_label->setAutoFillBackground(false);
        step1_label->setTextFormat(Qt::RichText);
        step1_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        Step_1->addWidget(step1_label);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        push_FOD = new QPushButton(InputImages);
        push_FOD->setObjectName(QString::fromUtf8("push_FOD"));

        gridLayout_3->addWidget(push_FOD, 5, 2, 1, 1);

        push_ACT = new QPushButton(InputImages);
        push_ACT->setObjectName(QString::fromUtf8("push_ACT"));

        gridLayout_3->addWidget(push_ACT, 6, 2, 1, 1);

        push_Mask = new QPushButton(InputImages);
        push_Mask->setObjectName(QString::fromUtf8("push_Mask"));

        gridLayout_3->addWidget(push_Mask, 3, 2, 1, 1);

        push_T1 = new QPushButton(InputImages);
        push_T1->setObjectName(QString::fromUtf8("push_T1"));

        gridLayout_3->addWidget(push_T1, 1, 2, 1, 1);

        fname_Mask_line = new QLineEdit(InputImages);
        fname_Mask_line->setObjectName(QString::fromUtf8("fname_Mask_line"));

        gridLayout_3->addWidget(fname_Mask_line, 3, 0, 1, 1);

        fname_ACT_line = new QLineEdit(InputImages);
        fname_ACT_line->setObjectName(QString::fromUtf8("fname_ACT_line"));

        gridLayout_3->addWidget(fname_ACT_line, 6, 0, 1, 1);

        fname_T1_line = new QLineEdit(InputImages);
        fname_T1_line->setObjectName(QString::fromUtf8("fname_T1_line"));
        fname_T1_line->setReadOnly(true);

        gridLayout_3->addWidget(fname_T1_line, 1, 0, 1, 1);

        fname_FOD_line = new QLineEdit(InputImages);
        fname_FOD_line->setObjectName(QString::fromUtf8("fname_FOD_line"));

        gridLayout_3->addWidget(fname_FOD_line, 5, 0, 1, 1);


        Step_1->addLayout(gridLayout_3);

        line_2 = new QFrame(InputImages);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        Step_1->addWidget(line_2);


        gridLayout_6->addWidget(InputImages, 0, 0, 1, 1);

        interact_label = new QLabel(frame);
        interact_label->setObjectName(QString::fromUtf8("interact_label"));
        interact_label->setEnabled(false);
        sizePolicy1.setHeightForWidth(interact_label->sizePolicy().hasHeightForWidth());
        interact_label->setSizePolicy(sizePolicy1);
        interact_label->setFont(font);
        interact_label->setTextFormat(Qt::RichText);
        interact_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(interact_label, 4, 0, 1, 1);

        StartTracker = new QFrame(frame);
        StartTracker->setObjectName(QString::fromUtf8("StartTracker"));
        StartTracker->setEnabled(false);
        sizePolicy1.setHeightForWidth(StartTracker->sizePolicy().hasHeightForWidth());
        StartTracker->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(StartTracker);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 2, 1, 1, 1);

        FOD_orderOfDirections = new QComboBox(StartTracker);
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->addItem(QString());
        FOD_orderOfDirections->setObjectName(QString::fromUtf8("FOD_orderOfDirections"));

        gridLayout_4->addWidget(FOD_orderOfDirections, 1, 0, 2, 1);

        FOD_discretization = new QCheckBox(StartTracker);
        FOD_discretization->setObjectName(QString::fromUtf8("FOD_discretization"));
        FOD_discretization->setChecked(true);

        gridLayout_4->addWidget(FOD_discretization, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 1, 2, 1);


        verticalLayout_2->addLayout(gridLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        push_start = new QPushButton(StartTracker);
        push_start->setObjectName(QString::fromUtf8("push_start"));

        verticalLayout_2->addWidget(push_start);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        line_3 = new QFrame(StartTracker);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);


        gridLayout_6->addWidget(StartTracker, 2, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        gridLayout_14 = new QGridLayout(tab_1);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        scrollArea_1 = new QScrollArea(tab_1);
        scrollArea_1->setObjectName(QString::fromUtf8("scrollArea_1"));
        scrollArea_1->setEnabled(false);
        sizePolicy2.setHeightForWidth(scrollArea_1->sizePolicy().hasHeightForWidth());
        scrollArea_1->setSizePolicy(sizePolicy2);
        scrollArea_1->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 318, 426));
        gridLayout_15 = new QGridLayout(scrollAreaWidgetContents_4);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(0);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_29 = new QLabel(scrollAreaWidgetContents_4);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_9->addWidget(label_29, 2, 1, 1, 1);

        txt_maxStreamlineCount = new QSpinBox(scrollAreaWidgetContents_4);
        txt_maxStreamlineCount->setObjectName(QString::fromUtf8("txt_maxStreamlineCount"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(txt_maxStreamlineCount->sizePolicy().hasHeightForWidth());
        txt_maxStreamlineCount->setSizePolicy(sizePolicy3);
        txt_maxStreamlineCount->setMinimum(1);
        txt_maxStreamlineCount->setMaximum(100000);

        gridLayout_9->addWidget(txt_maxStreamlineCount, 2, 0, 1, 1);

        label_31 = new QLabel(scrollAreaWidgetContents_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_9->addWidget(label_31, 5, 1, 1, 1);

        label_30 = new QLabel(scrollAreaWidgetContents_4);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_9->addWidget(label_30, 4, 1, 1, 1);

        txt_peelNo = new QSpinBox(scrollAreaWidgetContents_4);
        txt_peelNo->setObjectName(QString::fromUtf8("txt_peelNo"));
        txt_peelNo->setMaximum(30);
        txt_peelNo->setValue(0);

        gridLayout_9->addWidget(txt_peelNo, 0, 0, 1, 1);

        txt_tubeRadius = new QDoubleSpinBox(scrollAreaWidgetContents_4);
        txt_tubeRadius->setObjectName(QString::fromUtf8("txt_tubeRadius"));
        txt_tubeRadius->setSingleStep(0.100000000000000);

        gridLayout_9->addWidget(txt_tubeRadius, 4, 0, 1, 1);

        txt_addOpacity = new QDoubleSpinBox(scrollAreaWidgetContents_4);
        txt_addOpacity->setObjectName(QString::fromUtf8("txt_addOpacity"));
        txt_addOpacity->setMinimum(-1.000000000000000);
        txt_addOpacity->setMaximum(1.000000000000000);
        txt_addOpacity->setSingleStep(0.050000000000000);

        gridLayout_9->addWidget(txt_addOpacity, 5, 0, 1, 1);

        txt_batchCount = new QSpinBox(scrollAreaWidgetContents_4);
        txt_batchCount->setObjectName(QString::fromUtf8("txt_batchCount"));
        txt_batchCount->setMaximum(10000);

        gridLayout_9->addWidget(txt_batchCount, 3, 0, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_9->addWidget(label_3, 0, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer_6, 6, 1, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_9->addWidget(label_4, 3, 1, 1, 1);

        txt_seed_radius = new QDoubleSpinBox(scrollAreaWidgetContents_4);
        txt_seed_radius->setObjectName(QString::fromUtf8("txt_seed_radius"));
        txt_seed_radius->setEnabled(false);
        sizePolicy3.setHeightForWidth(txt_seed_radius->sizePolicy().hasHeightForWidth());
        txt_seed_radius->setSizePolicy(sizePolicy3);
        txt_seed_radius->setDecimals(3);
        txt_seed_radius->setMaximum(10.000000000000000);
        txt_seed_radius->setSingleStep(0.100000000000000);

        gridLayout_9->addWidget(txt_seed_radius, 1, 0, 1, 1);

        txt_seed_radius_label = new QLabel(scrollAreaWidgetContents_4);
        txt_seed_radius_label->setObjectName(QString::fromUtf8("txt_seed_radius_label"));
        txt_seed_radius_label->setEnabled(false);

        gridLayout_9->addWidget(txt_seed_radius_label, 1, 1, 1, 1);


        gridLayout_15->addLayout(gridLayout_9, 0, 0, 1, 1);

        scrollArea_1->setWidget(scrollAreaWidgetContents_4);

        gridLayout_14->addWidget(scrollArea_1, 0, 0, 1, 1);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_10 = new QGridLayout(tab_2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        scrollArea_2 = new QScrollArea(tab_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        sizePolicy2.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy2);
        scrollArea_2->setMinimumSize(QSize(0, 0));
        scrollArea_2->setMaximumSize(QSize(16777215, 16777215));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 318, 426));
        gridLayout_7 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_7->setSpacing(0);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(0);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_8->addWidget(label_11, 8, 1, 1, 1);

        txt_minLength = new QDoubleSpinBox(scrollAreaWidgetContents);
        txt_minLength->setObjectName(QString::fromUtf8("txt_minLength"));
        txt_minLength->setDecimals(3);
        txt_minLength->setMaximum(1000000.000000000000000);

        gridLayout_8->addWidget(txt_minLength, 3, 0, 1, 1);

        txt_minFODamp_label = new QLabel(scrollAreaWidgetContents);
        txt_minFODamp_label->setObjectName(QString::fromUtf8("txt_minFODamp_label"));

        gridLayout_8->addWidget(txt_minFODamp_label, 7, 1, 1, 1);

        txt_stepSize = new QDoubleSpinBox(scrollAreaWidgetContents);
        txt_stepSize->setObjectName(QString::fromUtf8("txt_stepSize"));
        txt_stepSize->setDecimals(3);
        txt_stepSize->setMinimum(0.001000000000000);
        txt_stepSize->setMaximum(10.000000000000000);
        txt_stepSize->setSingleStep(0.001000000000000);

        gridLayout_8->addWidget(txt_stepSize, 5, 0, 1, 1);

        txt_writeInterval = new QSpinBox(scrollAreaWidgetContents);
        txt_writeInterval->setObjectName(QString::fromUtf8("txt_writeInterval"));
        txt_writeInterval->setMaximum(1000);

        gridLayout_8->addWidget(txt_writeInterval, 9, 0, 1, 1);

        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_8->addWidget(label_8, 5, 1, 1, 1);

        label_14 = new QLabel(scrollAreaWidgetContents);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_8->addWidget(label_14, 9, 1, 1, 1);

        label_27 = new QLabel(scrollAreaWidgetContents);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_8->addWidget(label_27, 1, 1, 1, 1);

        txt_dataSupportExponent = new QDoubleSpinBox(scrollAreaWidgetContents);
        txt_dataSupportExponent->setObjectName(QString::fromUtf8("txt_dataSupportExponent"));
        txt_dataSupportExponent->setDecimals(3);
        txt_dataSupportExponent->setMaximum(100.000000000000000);
        txt_dataSupportExponent->setSingleStep(0.100000000000000);

        gridLayout_8->addWidget(txt_dataSupportExponent, 8, 0, 1, 1);

        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_8->addWidget(label_12, 3, 1, 1, 1);

        txt_minRadiusOfCurvature = new QDoubleSpinBox(scrollAreaWidgetContents);
        txt_minRadiusOfCurvature->setObjectName(QString::fromUtf8("txt_minRadiusOfCurvature"));
        txt_minRadiusOfCurvature->setDecimals(3);
        txt_minRadiusOfCurvature->setMinimum(0.001000000000000);
        txt_minRadiusOfCurvature->setMaximum(10.000000000000000);
        txt_minRadiusOfCurvature->setSingleStep(0.001000000000000);
        txt_minRadiusOfCurvature->setValue(0.001000000000000);

        gridLayout_8->addWidget(txt_minRadiusOfCurvature, 6, 0, 1, 1);

        label_13 = new QLabel(scrollAreaWidgetContents);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_8->addWidget(label_13, 4, 1, 1, 1);

        txt_maxLength = new QDoubleSpinBox(scrollAreaWidgetContents);
        txt_maxLength->setObjectName(QString::fromUtf8("txt_maxLength"));
        txt_maxLength->setDecimals(3);
        txt_maxLength->setMaximum(1000000.000000000000000);

        gridLayout_8->addWidget(txt_maxLength, 4, 0, 1, 1);

        txt_minFODamp = new QDoubleSpinBox(scrollAreaWidgetContents);
        txt_minFODamp->setObjectName(QString::fromUtf8("txt_minFODamp"));
        txt_minFODamp->setDecimals(3);
        txt_minFODamp->setMaximum(1.000000000000000);
        txt_minFODamp->setSingleStep(0.001000000000000);
        txt_minFODamp->setValue(0.000000000000000);

        gridLayout_8->addWidget(txt_minFODamp, 7, 0, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_8->addWidget(label_9, 6, 1, 1, 1);

        txt_seed_maxTrials = new QSpinBox(scrollAreaWidgetContents);
        txt_seed_maxTrials->setObjectName(QString::fromUtf8("txt_seed_maxTrials"));
        sizePolicy3.setHeightForWidth(txt_seed_maxTrials->sizePolicy().hasHeightForWidth());
        txt_seed_maxTrials->setSizePolicy(sizePolicy3);
        txt_seed_maxTrials->setMinimum(1);
        txt_seed_maxTrials->setMaximum(100000);

        gridLayout_8->addWidget(txt_seed_maxTrials, 1, 0, 1, 1);

        txt_numberOfThreads = new QSpinBox(scrollAreaWidgetContents);
        txt_numberOfThreads->setObjectName(QString::fromUtf8("txt_numberOfThreads"));
        txt_numberOfThreads->setMinimum(1);
        txt_numberOfThreads->setMaximum(1000000);

        gridLayout_8->addWidget(txt_numberOfThreads, 0, 0, 1, 1);

        txt_numberOfThreads_label = new QLabel(scrollAreaWidgetContents);
        txt_numberOfThreads_label->setObjectName(QString::fromUtf8("txt_numberOfThreads_label"));

        gridLayout_8->addWidget(txt_numberOfThreads_label, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_8);

        txt_atMaxLength = new QComboBox(scrollAreaWidgetContents);
        txt_atMaxLength->addItem(QString());
        txt_atMaxLength->addItem(QString());
        txt_atMaxLength->addItem(QString());
        txt_atMaxLength->setObjectName(QString::fromUtf8("txt_atMaxLength"));

        verticalLayout->addWidget(txt_atMaxLength);

        txt_directionality = new QComboBox(scrollAreaWidgetContents);
        txt_directionality->addItem(QString());
        txt_directionality->addItem(QString());
        txt_directionality->addItem(QString());
        txt_directionality->setObjectName(QString::fromUtf8("txt_directionality"));

        verticalLayout->addWidget(txt_directionality);

        verticalSpacer_4 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        gridLayout_7->addLayout(verticalLayout, 0, 0, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents);

        gridLayout_10->addWidget(scrollArea_2, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_13 = new QGridLayout(tab_3);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        scrollArea_3 = new QScrollArea(tab_3);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        sizePolicy2.setHeightForWidth(scrollArea_3->sizePolicy().hasHeightForWidth());
        scrollArea_3->setSizePolicy(sizePolicy2);
        scrollArea_3->setMinimumSize(QSize(0, 0));
        scrollArea_3->setMaximumSize(QSize(16777215, 16777215));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 318, 426));
        scrollAreaWidgetContents_2->setMaximumSize(QSize(16777215, 600));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(0);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(0);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        txt_maxEstInterval = new QSpinBox(scrollAreaWidgetContents_2);
        txt_maxEstInterval->setObjectName(QString::fromUtf8("txt_maxEstInterval"));
        txt_maxEstInterval->setMaximum(100000);

        gridLayout_12->addWidget(txt_maxEstInterval, 0, 0, 1, 1);

        label_15 = new QLabel(scrollAreaWidgetContents_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_12->addWidget(label_15, 0, 1, 1, 1);

        txt_initMaxEstTrials = new QSpinBox(scrollAreaWidgetContents_2);
        txt_initMaxEstTrials->setObjectName(QString::fromUtf8("txt_initMaxEstTrials"));
        txt_initMaxEstTrials->setMaximum(100000);

        gridLayout_12->addWidget(txt_initMaxEstTrials, 1, 0, 1, 1);

        label_19 = new QLabel(scrollAreaWidgetContents_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_12->addWidget(label_19, 1, 1, 1, 1);

        txt_propMaxEstTrials = new QSpinBox(scrollAreaWidgetContents_2);
        txt_propMaxEstTrials->setObjectName(QString::fromUtf8("txt_propMaxEstTrials"));
        txt_propMaxEstTrials->setMaximum(100000);

        gridLayout_12->addWidget(txt_propMaxEstTrials, 2, 0, 1, 1);

        label_20 = new QLabel(scrollAreaWidgetContents_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_12->addWidget(label_20, 2, 1, 1, 1);

        txt_maxSamplingPerStep = new QSpinBox(scrollAreaWidgetContents_2);
        txt_maxSamplingPerStep->setObjectName(QString::fromUtf8("txt_maxSamplingPerStep"));
        txt_maxSamplingPerStep->setMaximum(100000);

        gridLayout_12->addWidget(txt_maxSamplingPerStep, 3, 0, 1, 1);

        label_21 = new QLabel(scrollAreaWidgetContents_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_12->addWidget(label_21, 3, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout_12, 0, 0, 1, 1);

        check_useBestAtInit = new QCheckBox(scrollAreaWidgetContents_2);
        check_useBestAtInit->setObjectName(QString::fromUtf8("check_useBestAtInit"));
        check_useBestAtInit->setChecked(false);

        gridLayout_11->addWidget(check_useBestAtInit, 1, 0, 1, 1);

        line_4 = new QFrame(scrollAreaWidgetContents_2);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_4, 2, 0, 1, 1);

        label_22 = new QLabel(scrollAreaWidgetContents_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_11->addWidget(label_22, 3, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        txt_probeRadius = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        txt_probeRadius->setObjectName(QString::fromUtf8("txt_probeRadius"));
        txt_probeRadius->setDecimals(3);
        txt_probeRadius->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(txt_probeRadius, 1, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 5, 1, 1, 1);

        txt_probeQuality = new QSpinBox(scrollAreaWidgetContents_2);
        txt_probeQuality->setObjectName(QString::fromUtf8("txt_probeQuality"));
        txt_probeQuality->setMinimum(1);
        txt_probeQuality->setMaximum(100000);

        gridLayout->addWidget(txt_probeQuality, 3, 0, 1, 1);

        label_25 = new QLabel(scrollAreaWidgetContents_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout->addWidget(label_25, 4, 1, 1, 1);

        txt_probeCount = new QSpinBox(scrollAreaWidgetContents_2);
        txt_probeCount->setObjectName(QString::fromUtf8("txt_probeCount"));
        txt_probeCount->setMinimum(1);
        txt_probeCount->setMaximum(100000);

        gridLayout->addWidget(txt_probeCount, 2, 0, 1, 1);

        label_16 = new QLabel(scrollAreaWidgetContents_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 0, 1, 1, 1);

        txt_ignoreWeakLinks = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        txt_ignoreWeakLinks->setObjectName(QString::fromUtf8("txt_ignoreWeakLinks"));

        gridLayout->addWidget(txt_ignoreWeakLinks, 4, 0, 1, 1);

        txt_probeLength = new QDoubleSpinBox(scrollAreaWidgetContents_2);
        txt_probeLength->setObjectName(QString::fromUtf8("txt_probeLength"));
        txt_probeLength->setDecimals(3);
        txt_probeLength->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(txt_probeLength, 0, 0, 1, 1);

        label_24 = new QLabel(scrollAreaWidgetContents_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout->addWidget(label_24, 3, 1, 1, 1);

        label_17 = new QLabel(scrollAreaWidgetContents_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 1, 1, 1, 1);

        label_23 = new QLabel(scrollAreaWidgetContents_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout->addWidget(label_23, 2, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout, 4, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_11, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 1, 0, 1, 1);

        scrollArea_3->setWidget(scrollAreaWidgetContents_2);

        gridLayout_13->addWidget(scrollArea_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_4->addWidget(tabWidget);

        verticalSpacer_7 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_7);

        progressText = new QLabel(frame);
        progressText->setObjectName(QString::fromUtf8("progressText"));
        progressText->setEnabled(true);
        sizePolicy2.setHeightForWidth(progressText->sizePolicy().hasHeightForWidth());
        progressText->setSizePolicy(sizePolicy2);
        progressText->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Hack")});
        font1.setPointSize(8);
        font1.setItalic(false);
        progressText->setFont(font1);
        progressText->setLayoutDirection(Qt::LeftToRight);
        progressText->setTextFormat(Qt::AutoText);
        progressText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressText->setMargin(1);

        verticalLayout_4->addWidget(progressText);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        sizePolicy2.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy2);
        progressBar->setMinimumSize(QSize(0, 10));
        progressBar->setMaximumSize(QSize(16777215, 10));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Hack")});
        font2.setPointSize(8);
        font2.setItalic(false);
        font2.setKerning(false);
        progressBar->setFont(font2);
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        verticalLayout_4->addWidget(progressBar);


        verticalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_5->addWidget(frame);


        gridLayout_2->addLayout(verticalLayout_5, 0, 1, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        qvtkOpenGLStereoWidget = new QVTKOpenGLStereoWidget(centralwidget);
        qvtkOpenGLStereoWidget->setObjectName(QString::fromUtf8("qvtkOpenGLStereoWidget"));
        sizePolicy2.setHeightForWidth(qvtkOpenGLStereoWidget->sizePolicy().hasHeightForWidth());
        qvtkOpenGLStereoWidget->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(qvtkOpenGLStereoWidget);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(0, 30));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(0);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        push_centerView = new QPushButton(frame_2);
        push_centerView->setObjectName(QString::fromUtf8("push_centerView"));
        push_centerView->setEnabled(false);
        push_centerView->setStyleSheet(QString::fromUtf8("background-color: rgb(35, 35, 35);"));

        horizontalLayout_2->addWidget(push_centerView);

        push_copyToClipboard = new QPushButton(frame_2);
        push_copyToClipboard->setObjectName(QString::fromUtf8("push_copyToClipboard"));
        push_copyToClipboard->setEnabled(false);
        push_copyToClipboard->setMinimumSize(QSize(0, 0));
        push_copyToClipboard->setStyleSheet(QString::fromUtf8("background-color: rgb(35, 35, 35);"));

        horizontalLayout_2->addWidget(push_copyToClipboard);

        txt_coordinates = new QLineEdit(frame_2);
        txt_coordinates->setObjectName(QString::fromUtf8("txt_coordinates"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(txt_coordinates->sizePolicy().hasHeightForWidth());
        txt_coordinates->setSizePolicy(sizePolicy4);
        txt_coordinates->setMinimumSize(QSize(0, 0));
        txt_coordinates->setMaximumSize(QSize(16777215, 16777215));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Hack")});
        font3.setPointSize(8);
        txt_coordinates->setFont(font3);
        txt_coordinates->setFocusPolicy(Qt::StrongFocus);
        txt_coordinates->setContextMenuPolicy(Qt::NoContextMenu);
        txt_coordinates->setStyleSheet(QString::fromUtf8("color: rgb(100, 100, 100);"));
        txt_coordinates->setReadOnly(true);

        horizontalLayout_2->addWidget(txt_coordinates);

        txt_info = new QLabel(frame_2);
        txt_info->setObjectName(QString::fromUtf8("txt_info"));
        txt_info->setEnabled(false);
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(txt_info->sizePolicy().hasHeightForWidth());
        txt_info->setSizePolicy(sizePolicy5);
        txt_info->setMinimumSize(QSize(180, 0));
        txt_info->setMaximumSize(QSize(180, 16777215));
        txt_info->setFont(font3);
        txt_info->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        txt_info->setMargin(3);

        horizontalLayout_2->addWidget(txt_info);


        verticalLayout_6->addWidget(frame_2);


        gridLayout_2->addLayout(verticalLayout_6, 0, 0, 1, 1);

        RTTVIS_GUI->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(RTTVIS_GUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1272, 30));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        RTTVIS_GUI->setMenuBar(menuBar);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(RTTVIS_GUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RTTVIS_GUI);
    } // setupUi

    void retranslateUi(QMainWindow *RTTVIS_GUI)
    {
        RTTVIS_GUI->setWindowTitle(QCoreApplication::translate("RTTVIS_GUI", "Real-time tractogram visualizer", nullptr));
        actionHow_to_use_the_interface->setText(QCoreApplication::translate("RTTVIS_GUI", "How to use the interface", nullptr));
        actionAbout->setText(QCoreApplication::translate("RTTVIS_GUI", "About", nullptr));
        step1_label->setText(QCoreApplication::translate("RTTVIS_GUI", "Initialize", nullptr));
        push_FOD->setText(QCoreApplication::translate("RTTVIS_GUI", "Load FOD", nullptr));
        push_ACT->setText(QCoreApplication::translate("RTTVIS_GUI", "Load ACT", nullptr));
        push_Mask->setText(QCoreApplication::translate("RTTVIS_GUI", "Load Mask", nullptr));
        push_T1->setText(QCoreApplication::translate("RTTVIS_GUI", "Load T1", nullptr));
        fname_Mask_line->setText(QCoreApplication::translate("RTTVIS_GUI", "N/A", nullptr));
        fname_ACT_line->setText(QCoreApplication::translate("RTTVIS_GUI", "N/A", nullptr));
        fname_T1_line->setText(QCoreApplication::translate("RTTVIS_GUI", "N/A", nullptr));
        fname_FOD_line->setText(QCoreApplication::translate("RTTVIS_GUI", "N/A", nullptr));
        interact_label->setText(QCoreApplication::translate("RTTVIS_GUI", "Interact", nullptr));
        FOD_orderOfDirections->setItemText(0, QCoreApplication::translate("RTTVIS_GUI", "Order Of Directions", nullptr));
        FOD_orderOfDirections->setItemText(1, QCoreApplication::translate("RTTVIS_GUI", "XYZ", nullptr));
        FOD_orderOfDirections->setItemText(2, QCoreApplication::translate("RTTVIS_GUI", "XYz", nullptr));
        FOD_orderOfDirections->setItemText(3, QCoreApplication::translate("RTTVIS_GUI", "XyZ", nullptr));
        FOD_orderOfDirections->setItemText(4, QCoreApplication::translate("RTTVIS_GUI", "Xyz", nullptr));
        FOD_orderOfDirections->setItemText(5, QCoreApplication::translate("RTTVIS_GUI", "xYZ", nullptr));
        FOD_orderOfDirections->setItemText(6, QCoreApplication::translate("RTTVIS_GUI", "xYz", nullptr));
        FOD_orderOfDirections->setItemText(7, QCoreApplication::translate("RTTVIS_GUI", "xyZ", nullptr));
        FOD_orderOfDirections->setItemText(8, QCoreApplication::translate("RTTVIS_GUI", "xyz", nullptr));
        FOD_orderOfDirections->setItemText(9, QCoreApplication::translate("RTTVIS_GUI", "XZY", nullptr));
        FOD_orderOfDirections->setItemText(10, QCoreApplication::translate("RTTVIS_GUI", "XZy", nullptr));
        FOD_orderOfDirections->setItemText(11, QCoreApplication::translate("RTTVIS_GUI", "XzY", nullptr));
        FOD_orderOfDirections->setItemText(12, QCoreApplication::translate("RTTVIS_GUI", "Xzy", nullptr));
        FOD_orderOfDirections->setItemText(13, QCoreApplication::translate("RTTVIS_GUI", "xZY", nullptr));
        FOD_orderOfDirections->setItemText(14, QCoreApplication::translate("RTTVIS_GUI", "xZy", nullptr));
        FOD_orderOfDirections->setItemText(15, QCoreApplication::translate("RTTVIS_GUI", "xzY", nullptr));
        FOD_orderOfDirections->setItemText(16, QCoreApplication::translate("RTTVIS_GUI", "xzy", nullptr));
        FOD_orderOfDirections->setItemText(17, QCoreApplication::translate("RTTVIS_GUI", "YXZ", nullptr));
        FOD_orderOfDirections->setItemText(18, QCoreApplication::translate("RTTVIS_GUI", "YXz", nullptr));
        FOD_orderOfDirections->setItemText(19, QCoreApplication::translate("RTTVIS_GUI", "YxZ", nullptr));
        FOD_orderOfDirections->setItemText(20, QCoreApplication::translate("RTTVIS_GUI", "Yxz", nullptr));
        FOD_orderOfDirections->setItemText(21, QCoreApplication::translate("RTTVIS_GUI", "yXZ", nullptr));
        FOD_orderOfDirections->setItemText(22, QCoreApplication::translate("RTTVIS_GUI", "yXz", nullptr));
        FOD_orderOfDirections->setItemText(23, QCoreApplication::translate("RTTVIS_GUI", "yxZ", nullptr));
        FOD_orderOfDirections->setItemText(24, QCoreApplication::translate("RTTVIS_GUI", "yxz", nullptr));
        FOD_orderOfDirections->setItemText(25, QCoreApplication::translate("RTTVIS_GUI", "YZX", nullptr));
        FOD_orderOfDirections->setItemText(26, QCoreApplication::translate("RTTVIS_GUI", "YZx", nullptr));
        FOD_orderOfDirections->setItemText(27, QCoreApplication::translate("RTTVIS_GUI", "YzX", nullptr));
        FOD_orderOfDirections->setItemText(28, QCoreApplication::translate("RTTVIS_GUI", "Yzx", nullptr));
        FOD_orderOfDirections->setItemText(29, QCoreApplication::translate("RTTVIS_GUI", "yZX", nullptr));
        FOD_orderOfDirections->setItemText(30, QCoreApplication::translate("RTTVIS_GUI", "yZx", nullptr));
        FOD_orderOfDirections->setItemText(31, QCoreApplication::translate("RTTVIS_GUI", "yzX", nullptr));
        FOD_orderOfDirections->setItemText(32, QCoreApplication::translate("RTTVIS_GUI", "yzx", nullptr));
        FOD_orderOfDirections->setItemText(33, QCoreApplication::translate("RTTVIS_GUI", "ZYX", nullptr));
        FOD_orderOfDirections->setItemText(34, QCoreApplication::translate("RTTVIS_GUI", "ZYx", nullptr));
        FOD_orderOfDirections->setItemText(35, QCoreApplication::translate("RTTVIS_GUI", "ZyX", nullptr));
        FOD_orderOfDirections->setItemText(36, QCoreApplication::translate("RTTVIS_GUI", "Zyx", nullptr));
        FOD_orderOfDirections->setItemText(37, QCoreApplication::translate("RTTVIS_GUI", "zYX", nullptr));
        FOD_orderOfDirections->setItemText(38, QCoreApplication::translate("RTTVIS_GUI", "zYx", nullptr));
        FOD_orderOfDirections->setItemText(39, QCoreApplication::translate("RTTVIS_GUI", "zyX", nullptr));
        FOD_orderOfDirections->setItemText(40, QCoreApplication::translate("RTTVIS_GUI", "zyx", nullptr));
        FOD_orderOfDirections->setItemText(41, QCoreApplication::translate("RTTVIS_GUI", "ZXY", nullptr));
        FOD_orderOfDirections->setItemText(42, QCoreApplication::translate("RTTVIS_GUI", "ZXy", nullptr));
        FOD_orderOfDirections->setItemText(43, QCoreApplication::translate("RTTVIS_GUI", "ZxY", nullptr));
        FOD_orderOfDirections->setItemText(44, QCoreApplication::translate("RTTVIS_GUI", "Zxy", nullptr));
        FOD_orderOfDirections->setItemText(45, QCoreApplication::translate("RTTVIS_GUI", "zXY", nullptr));
        FOD_orderOfDirections->setItemText(46, QCoreApplication::translate("RTTVIS_GUI", "zXy", nullptr));
        FOD_orderOfDirections->setItemText(47, QCoreApplication::translate("RTTVIS_GUI", "zxY", nullptr));
        FOD_orderOfDirections->setItemText(48, QCoreApplication::translate("RTTVIS_GUI", "zxy", nullptr));

        FOD_discretization->setText(QCoreApplication::translate("RTTVIS_GUI", "Discretize FOD image", nullptr));
        push_start->setText(QCoreApplication::translate("RTTVIS_GUI", "Start real-time tracker", nullptr));
        label_29->setText(QCoreApplication::translate("RTTVIS_GUI", "Max # of streamlines to show", nullptr));
        label_31->setText(QCoreApplication::translate("RTTVIS_GUI", "Additional opacity", nullptr));
        label_30->setText(QCoreApplication::translate("RTTVIS_GUI", "Tube radius", nullptr));
        label_3->setText(QCoreApplication::translate("RTTVIS_GUI", "Peel no", nullptr));
        label_4->setText(QCoreApplication::translate("RTTVIS_GUI", "# of streamlines per batch", nullptr));
        txt_seed_radius_label->setText(QCoreApplication::translate("RTTVIS_GUI", "Seed radius", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("RTTVIS_GUI", "Visualization", nullptr));
        label_11->setText(QCoreApplication::translate("RTTVIS_GUI", "dataSupportExponent", nullptr));
        txt_minFODamp_label->setText(QCoreApplication::translate("RTTVIS_GUI", "minFODamp", nullptr));
        label_8->setText(QCoreApplication::translate("RTTVIS_GUI", "stepSize", nullptr));
        label_14->setText(QCoreApplication::translate("RTTVIS_GUI", "writeInterval", nullptr));
        label_27->setText(QCoreApplication::translate("RTTVIS_GUI", "seed_maxTrials", nullptr));
        label_12->setText(QCoreApplication::translate("RTTVIS_GUI", "minLength", nullptr));
        label_13->setText(QCoreApplication::translate("RTTVIS_GUI", "maxLength", nullptr));
        label_9->setText(QCoreApplication::translate("RTTVIS_GUI", "minRadiusOfCurvature", nullptr));
        txt_numberOfThreads_label->setText(QCoreApplication::translate("RTTVIS_GUI", "numberOfThreads", nullptr));
        txt_atMaxLength->setItemText(0, QCoreApplication::translate("RTTVIS_GUI", "atMaxLength", nullptr));
        txt_atMaxLength->setItemText(1, QCoreApplication::translate("RTTVIS_GUI", "stop", nullptr));
        txt_atMaxLength->setItemText(2, QCoreApplication::translate("RTTVIS_GUI", "discard", nullptr));

        txt_directionality->setItemText(0, QCoreApplication::translate("RTTVIS_GUI", "directionality", nullptr));
        txt_directionality->setItemText(1, QCoreApplication::translate("RTTVIS_GUI", "one_sided", nullptr));
        txt_directionality->setItemText(2, QCoreApplication::translate("RTTVIS_GUI", "two_sided", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("RTTVIS_GUI", "Tracking", nullptr));
        label_15->setText(QCoreApplication::translate("RTTVIS_GUI", "maxEstInterval", nullptr));
        label_19->setText(QCoreApplication::translate("RTTVIS_GUI", "initMaxEstTrials", nullptr));
        label_20->setText(QCoreApplication::translate("RTTVIS_GUI", "propMaxEstTrials", nullptr));
        label_21->setText(QCoreApplication::translate("RTTVIS_GUI", "maxSamplingPerStep", nullptr));
        check_useBestAtInit->setText(QCoreApplication::translate("RTTVIS_GUI", "useBestAtInit", nullptr));
        label_22->setText(QCoreApplication::translate("RTTVIS_GUI", "Probe options", nullptr));
        label_25->setText(QCoreApplication::translate("RTTVIS_GUI", "ignoreWeakLinks", nullptr));
        label_16->setText(QCoreApplication::translate("RTTVIS_GUI", "probeLength", nullptr));
        label_24->setText(QCoreApplication::translate("RTTVIS_GUI", "probeQuality", nullptr));
        label_17->setText(QCoreApplication::translate("RTTVIS_GUI", "probeRadius", nullptr));
        label_23->setText(QCoreApplication::translate("RTTVIS_GUI", "probeCount", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("RTTVIS_GUI", "Advanced", nullptr));
        progressText->setText(QCoreApplication::translate("RTTVIS_GUI", "Waiting for images", nullptr));
        push_centerView->setText(QCoreApplication::translate("RTTVIS_GUI", "Center view", nullptr));
        push_copyToClipboard->setText(QCoreApplication::translate("RTTVIS_GUI", "Copy coordinates to clipboard", nullptr));
        txt_coordinates->setText(QString());
        txt_info->setText(QString());
        menuHelp->setTitle(QCoreApplication::translate("RTTVIS_GUI", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RTTVIS_GUI: public Ui_RTTVIS_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTTVIS_GUI_H
