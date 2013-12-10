/** This program is an implemention of hp-finite elements for
*   three-dimensional linear piezoelectric beams.
*
*   © Copyright 2013 Roman Poya
*
*   This file is part of FEAPB.
*   FEAPB is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   any later version.
*
*   FEAPB is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with FEAPB.  If not, see <http://www.gnu.org/licenses/>.
*
*
*   Contact details: romanpoya@gmail.com or roman.poya@cimne.com
*/

#include "mainwindow.h"

using namespace FEAPB;

MainWindow::MainWindow()
{
    widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new LabelInfo;
    infoLabel->setText(tr("Input data appears here"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QWidget *midFiller = new QWidget;
    midFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    int marg = 80; int marg2 = 40;

    MainLabel *FEAPBLabel = new MainLabel;
    FEAPBLabel->setText(tr("<b><font size=5 face='Lucida Sans Unicode' color=#FFD300>FEA</font><font size=5 face='Lucida Sans Unicode' COLOR=#FD795B>PB</font></b>"));
    FEAPBLabel->setIndent(marg);

    infolabel_geom = new QLabel(tr("<div> Geometrical Properties: </div>"));
    infolabel_geom->setIndent(marg);
    infolabel_x1 = new QLabel(tr("<div> Height: </div>"));
    infolabel_x1->setIndent(marg+marg2);
    infolabel_x2 = new QLabel(tr("<div> Width: </div>"));
    infolabel_x2->setIndent(marg+marg2);
    infolabel_x3 = new QLabel(tr("<div> Length: </div>"));
    infolabel_x3->setIndent(marg+marg2);
    infolabel_shear = new QLabel(tr("<div> Shear Factor: </div>"));
    infolabel_shear->setIndent(marg+marg2);


    // Make parent window labels/text
    infoLabel_C = new QLabel(tr("<div> Order of Bases: </div>"));
    infoLabel_C->setIndent(marg);
    infoLabel_n = new QLabel(tr("<div> Number of Elements: </div>"));
    infoLabel_n->setIndent(marg);
    infoLabel_node_number = new QLabel(tr("<div> Number of Nodes: </div>"));
    infoLabel_node_number->setIndent(marg);
    infoLabel_analysis = new QLabel(tr("<div> Analysis Type: </div>"));
    infoLabel_analysis->setIndent(marg);
    infoLabel_bases = new QLabel(tr("<div> Basis Functions: </div>"));
    infoLabel_bases->setIndent(marg);
    infoLabel_numint = new QLabel(tr("<div> Numerical Integration: </div>"));
    infoLabel_numint->setIndent(marg);
    infoLabel_dynint = new QLabel(tr("<div> Dynamic Integration: </div>"));
    infoLabel_dynint->setIndent(marg);
    infoLabel_iso = new QLabel(tr("<div> Material Class: </div>"));
    infoLabel_iso->setIndent(marg);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(marg+marg2);
//    layout->addWidget(topFiller);
    layout->addWidget(FEAPBLabel);
    layout->addWidget(topFiller);

    layout->addWidget(infolabel_geom);
    layout->addWidget(infolabel_x1);
    layout->addWidget(infolabel_x2);
    layout->addWidget(infolabel_x3);
    layout->addWidget(infolabel_shear);

    layout->addWidget(midFiller);

    layout->addWidget(infoLabel_C);
    layout->addWidget(infoLabel_n);
    layout->addWidget(infoLabel_node_number);
    layout->addWidget(infoLabel_iso);
    layout->addWidget(infoLabel_analysis);
    layout->addWidget(infoLabel_bases);
    layout->addWidget(infoLabel_numint);
    layout->addWidget(infoLabel_dynint);

    layout->addWidget(bottomFiller);
    layout->addWidget(bottomFiller);
    layout->addWidget(bottomFiller);
    layout->addWidget(infoLabel);
    widget->setLayout(layout);

//    QDesktopWidget *desktop = new QDesktopWidget;

    fullScreenAct = new QAction(tr("Full Screen"),this);
    connect(fullScreenAct,SIGNAL(triggered()),this,SLOT(fullScreen()));

    createActions();
    createMenus();


    QString message = tr("Tooltips appear here");
    statusBar()->showMessage(message);

    setWindowTitle(tr("FEAPB"));
    setMinimumSize(100, 100);
    // resize(920, 640);
    fullScreen();     // showFullScreen(); // <- qt version
    widget->update();

    // Get full screen size
    if (isFullScreen())
    {
        fullScreenHeight = this->height();
        fullScreenWidth = this->width();
    }
    else
    {
        fullScreenHeight = 768;
        fullScreenWidth = 1366;
    }


    // Make new labels
    x1_label = new QLabel;
    x2_label = new QLabel;
    x3_label = new QLabel;
    shear_label = new QLabel;

    C_label = new QLabel;
    n_label = new QLabel;
    bases_label = new QLabel;

    iso_label = new QLabel;
    density_label = new QLabel;
    mu_label = new QLabel;
    lambda_label = new QLabel;
    c33_label = new QLabel;
    c34_label = new QLabel;
    c35_label = new QLabel;
    c44_label = new QLabel;
    c45_label = new QLabel;
    c55_label = new QLabel;

    e11_label = new QLabel;
    e12_label = new QLabel;
    e13_label = new QLabel;
    e21_label = new QLabel;
    e22_label = new QLabel;
    e23_label = new QLabel;
    e31_label = new QLabel;
    e32_label = new QLabel;
    e33_label = new QLabel;

    p11_Label = new QLabel;
    p12_Label = new QLabel;
    p13_Label = new QLabel;
    p14_Label = new QLabel;
    p15_Label = new QLabel;
    p16_Label = new QLabel;
    p21_Label = new QLabel;
    p22_Label = new QLabel;
    p23_Label = new QLabel;
    p24_Label = new QLabel;
    p25_Label = new QLabel;
    p26_Label = new QLabel;
    p31_Label = new QLabel;
    p32_Label = new QLabel;
    p33_Label = new QLabel;
    p34_Label = new QLabel;
    p35_Label = new QLabel;
    p36_Label = new QLabel;

    bc_nodes_label = new QLabel;
    bc_var_label = new QLabel;
    bc_amnt_label = new QLabel;

    point_loads_label = new QLabel;
    point_pos_label = new QLabel;
    udl_label = new QLabel;

    analysis_label = new QLabel;
    numint_label = new QLabel;
    dynint_label = new QLabel;
    openFile_label = new QLabel;


    /** Generate dialog boxes with their fields  */
    // Screen resolution dialog and fields
    width_label = new QLabel;   width_label->setText("920");
    height_label = new QLabel;  height_label->setText("640");
    wndDialog = new MainDialog;
    // wndDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // for framed dialogs without ?
    wndDialog->setWindowFlags(Qt::FramelessWindowHint);
    line_screen_width = new QLineEdit(wndDialog);
    line_screen_height = new QLineEdit(wndDialog);
    connect(line_screen_width,SIGNAL(textEdited(QString)),this,SLOT(setScreenWidth(QString)));
    connect(line_screen_height,SIGNAL(textEdited(QString)),this,SLOT(setScreenHeight(QString)));

    // Geometry Dialog and fields
    gwdg = new MainDialog;
    gwdg->setWindowFlags(Qt::FramelessWindowHint);
    line_x1 = new QLineEdit(gwdg);
    line_x2 = new QLineEdit(gwdg);
    line_x3 = new QLineEdit(gwdg);
    line_shear = new QLineEdit(gwdg);

    // Mesh dialog and and fields
    mwdg = new MainDialog;
    mwdg->setWindowFlags(Qt::FramelessWindowHint);
    box_C = new QSpinBox(mwdg);
    line_n = new QLineEdit(" ",mwdg);
    box_bases = new QComboBox(mwdg);

    // build strings for comboxes
    QStringList bases;
    bases <<"Lagrange" << "Lagrange ES" <<  "Legendre";
    box_bases->addItems(bases);

    connect(box_bases,SIGNAL(currentTextChanged(QString)),box_bases,SLOT(setCurrentText(QString)));

    // Mechanical properties and fields
    wdg_matm = new MainDialog;
    wdg_matm->setWindowFlags(Qt::FramelessWindowHint);
    box_iso = new QComboBox(wdg_matm);
    line_density = new QLineEdit(" ",wdg_matm);
    line_mu = new QLineEdit(" ",wdg_matm);
    line_lambda = new QLineEdit(" ",wdg_matm);
    line_c33 = new QLineEdit(" ",wdg_matm);
    line_c34 = new QLineEdit(" ",wdg_matm);
    line_c35 = new QLineEdit(" ",wdg_matm);
    line_c44 = new QLineEdit(" ",wdg_matm);
    line_c45 = new QLineEdit(" ",wdg_matm);
    line_c55 = new QLineEdit(" ",wdg_matm);

    QStringList iso;
    iso <<"Isotropic" << "Anisotropic";
    box_iso->addItems(iso);

    connect(box_iso,SIGNAL(currentTextChanged(QString)),box_iso,SLOT(setCurrentText(QString)));

    // Electrical properties and fields
    wdg_mate = new MainDialog;
    wdg_mate->setWindowFlags(Qt::FramelessWindowHint);
    line_e11= new QLineEdit(" ",wdg_mate);
    line_e12= new QLineEdit(" ",wdg_mate);
    line_e13= new QLineEdit(" ",wdg_mate);
    line_e21= new QLineEdit(" ",wdg_mate);
    line_e22= new QLineEdit(" ",wdg_mate);
    line_e23= new QLineEdit(" ",wdg_mate);
    line_e31= new QLineEdit(" ",wdg_mate);
    line_e32= new QLineEdit(" ",wdg_mate);
    line_e33= new QLineEdit(" ",wdg_mate);
    line_p11 = new QLineEdit(wdg_mate);
    line_p12 = new QLineEdit(wdg_mate);
    line_p13 = new QLineEdit(wdg_mate);
    line_p14 = new QLineEdit(wdg_mate);
    line_p15 = new QLineEdit(wdg_mate);
    line_p16 = new QLineEdit(wdg_mate);
    line_p21 = new QLineEdit(wdg_mate);
    line_p22 = new QLineEdit(wdg_mate);
    line_p23 = new QLineEdit(wdg_mate);
    line_p24 = new QLineEdit(wdg_mate);
    line_p25 = new QLineEdit(wdg_mate);
    line_p26 = new QLineEdit(wdg_mate);
    line_p31 = new QLineEdit(wdg_mate);
    line_p32 = new QLineEdit(wdg_mate);
    line_p33 = new QLineEdit(wdg_mate);
    line_p34 = new QLineEdit(wdg_mate);
    line_p35 = new QLineEdit(wdg_mate);
    line_p36 = new QLineEdit(wdg_mate);

    // Dirichlet dialog and fields
    wdg_bc_d = new MainDialog;
    wdg_bc_d->setWindowFlags(Qt::FramelessWindowHint);
    line_nodes = new QLineEdit(wdg_bc_d);
    line_var = new QLineEdit(wdg_bc_d);
    line_amnt = new QLineEdit(wdg_bc_d);

    // Neumann dialog and fields
    wdg_bc_n = new MainDialog;
    wdg_bc_n->setWindowFlags(Qt::FramelessWindowHint);
    line_point_loads = new QLineEdit(wdg_bc_n);
    line_point_pos = new QLineEdit(wdg_bc_n);
    line_udl = new QLineEdit(wdg_bc_n);

    awdg = new MainDialog;
    awdg->setWindowFlags(Qt::FramelessWindowHint);
    box_analysis = new QComboBox(awdg);
    box_numint = new QComboBox(awdg);
    box_dynint = new QComboBox(awdg);
    but_importdyn = new QPushButton("Browse",awdg);
    line_importdyn = new QLineEdit(awdg);
    line_nodes_dyn = new QLineEdit(awdg);
    line_var_dyn = new QLineEdit(awdg);
    line_out_dyn = new QLineEdit(awdg);

    // build strings for comboxes
    QStringList analyses, numint, dynint;
    numint << "Gauss" << "Gauss Lobatto";
    analyses << "Static" << "Modal" << "Dynamic";
    dynint << "Alpha" << "Newmark's" << "Generlised Alpha";

    box_numint->addItems(numint);
    box_analysis->addItems(analyses);
    box_dynint->addItems(dynint);

    connect(box_dynint,SIGNAL(currentTextChanged(QString)),box_dynint,SLOT(setCurrentText(QString)));
    connect(box_analysis,SIGNAL(currentTextChanged(QString)),box_analysis,SLOT(setCurrentText(QString)));
    connect(box_numint,SIGNAL(currentTextChanged(QString)),box_numint,SLOT(setCurrentText(QString)));

    connect(but_importdyn,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(line_importdyn,SIGNAL(textChanged(QString)),awdg,SLOT(setWindowTitle(QString)));


    // Solve
    progress  = new QProgressDialog;
    progress->setLabelText("Solving...");
    progress->setCancelButton(0);
    connect(&FutureWatcher, SIGNAL(finished()), this, SLOT(analysisFinished()));
    connect(&FutureWatcher, SIGNAL(finished()), progress, SLOT(cancel()));
//    connect(progress,SIGNAL(canceled()),&FutureWatcher,SLOT(cancel()));


    pwdg = new MainDialog;
    pwdg->setWindowFlags(Qt::FramelessWindowHint);
    plot = new QCustomPlot(pwdg);

    box_plot_static = new QComboBox(pwdg);
    // build strings for combobox
    QStringList variables;
    variables <<"Mechanical Displacement X1" << "Mechanical Dispalcement X2" << "Mechanical Dispalcement X3" << "Rotation X1" << "Rotation X2" << "Rotation X3" << "Electric Potential" << "Electric Gradient X1" << "Electric Gradient X2" << "Electric Hessian X1" << "Electric Hessian X2";
    box_plot_static->addItems(variables);
    connect(box_plot_static,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePlot(int)));

    next = new NextButton(pwdg);
    previous = new PreviousButton(pwdg);

    connect(next,SIGNAL(clicked()),this,SLOT(nextPlot()));
    connect(previous,SIGNAL(clicked()),this,SLOT(previousPlot()));

    static_plot_index_label = new QLabel;
    modal_plot_index_label = new QLabel; modal_plot_index_label->setNum(1);
    dynamic_plot_var_index_label = new QLabel; dynamic_plot_var_index_label->setNum(0);
    dynamic_plot_step_index_label = new QLabel; dynamic_plot_step_index_label->setNum(1);
    static_plot_index_label->setText("0");
    no_update_modal_plot = -1;
    no_update_dynamic_plot = -1;
    no_update_static_plot =-1;

    line_fast_access_index = new QLineEdit(pwdg);
    connect(line_fast_access_index,SIGNAL(textChanged(QString)),this,SLOT(updateModalDynamicPlot(QString)));


    but_save = new QPushButton("Save Figure",pwdg);
    connect(but_save,SIGNAL(clicked()),this,SLOT(saveImage()));


    // Disable some fields by default
    line_mu->setEnabled(1);
    line_lambda->setEnabled(1);
    line_c33->setEnabled(0);
    line_c34->setEnabled(0);
    line_c35->setEnabled(0);
    line_c44->setEnabled(0);
    line_c45->setEnabled(0);
    line_c55->setEnabled(0);

    box_dynint->setEnabled(0);
    but_importdyn->setEnabled(0);
    line_importdyn->setEnabled(0);
    line_nodes_dyn->setEnabled(0);
    line_var_dyn->setEnabled(0);
    line_out_dyn->setEnabled(0);

    path = QDir::currentPath();

    setAttribute(Qt::WA_DeleteOnClose,true);
}

void MainWindow::newFile()
{
    // Erase all labels which are used for data storage
    x1_label->setText("");
    x2_label->setText("");
    x3_label->setText("");
    shear_label->setText("");

    iso_label->setText("Isotropic");
    density_label->setText("");  mu_label->setText(""); lambda_label->setText("");
    c33_label->setText(""); c34_label->setText(""); c35_label->setText(""); c44_label->setText(""); c45_label->setText(""); c55_label->setText("");

    e11_label->setText("");     e12_label->setText("");    e13_label->setText("");    e21_label->setText("");    e22_label->setText("");    e23_label->setText("");    e31_label->setText("");    e32_label->setText("");    e33_label->setText("");

    p11_Label->setText("");    p12_Label->setText("");    p13_Label->setText("");    p14_Label->setText("");    p15_Label->setText("");    p16_Label->setText("");
    p21_Label->setText("");    p22_Label->setText("");    p23_Label->setText("");    p24_Label->setText("");    p25_Label->setText("");    p26_Label->setText("");
    p31_Label->setText("");    p32_Label->setText("");    p33_Label->setText("");    p34_Label->setText("");    p35_Label->setText("");    p36_Label->setText("");

    bc_nodes_label->setText(""); bc_var_label->setText(""); bc_amnt_label->setText("");
    point_loads_label->setText("");    point_pos_label->setText("");    udl_label->setText("");

    n_label->setText(""); C_label->setText(""); numint_label->setText(""); dynint_label->setText(""); analysis_label->setText("Static"); bases_label->setText("");

    // Empty all boxes/lines
    line_x1->setText("");     line_x2->setText("");     line_x3->setText("");     line_shear->setText("");

    box_iso->setCurrentIndex(0);
    line_density->setText("");    line_mu->setText("");     line_lambda->setText("");
    line_c33->setText("");    line_c34->setText("");    line_c35->setText("");    line_c44->setText("");    line_c45->setText("");    line_c55->setText("");

    line_e11->setText("");     line_e12->setText("");    line_e13->setText("");    line_e21->setText("");    line_e22->setText("");    line_e23->setText("");    line_e31->setText("");    line_e32->setText("");    line_e33->setText("");

    line_p11->setText("");    line_p12->setText("");    line_p13->setText("");    line_p14->setText("");    line_p15->setText("");    line_p16->setText("");
    line_p21->setText("");    line_p22->setText("");    line_p23->setText("");    line_p24->setText("");    line_p25->setText("");    line_p26->setText("");
    line_p31->setText("");    line_p32->setText("");    line_p33->setText("");    line_p34->setText("");    line_p35->setText("");    line_p36->setText("");

    line_nodes->setText(""); line_var->setText(""); line_amnt->setText("");
    line_point_loads->setText(""); line_point_pos->setText(""); line_udl->setText("");

    box_C->setValue(0);
    line_n->setText("");
    box_analysis->setCurrentIndex(0);
    box_bases->setCurrentIndex(0);
    box_dynint->setCurrentIndex(0);
    box_numint->setCurrentIndex(0);

    line_importdyn->setText(""); line_nodes_dyn->setText(""); line_var_dyn->setText(""); line_out_dyn->setText("");
    line_importdyn->setDisabled(1); line_nodes_dyn->setDisabled(1); line_var_dyn->setDisabled(1); line_out_dyn->setDisabled(1); but_importdyn->setDisabled(1);

    box_plot_static->setCurrentIndex(0);  line_fast_access_index->setText("");


    // Erase all labels on the screen
    infoLabel->setText(tr("Input data appears here"));
    infoLabel_analysis->setText(tr("<div> Analysis Type: </div>"));
    infoLabel_bases->setText(tr("<div> Basis Functions: </div>"));
    infoLabel_C->setText(tr("<div> Order of Bases: </div>"));
    infoLabel_iso->setText(tr("<div> Material Class: </div>"));
    infoLabel_dynint->setText(tr("<div> Dynamic Integration: </div>"));
    infoLabel_n->setText(tr("<div> Number of Elements: </div>"));
    infoLabel_node_number->setText(tr("<div> Number of Nodes: </div>"));
    infoLabel_numint->setText(tr("<div> Numerical Integration: </div>"));
    infolabel_shear->setText(tr("<div> Shear Factor: </div>"));
    infolabel_x1->setText(tr("<div> Height: </div>"));
    infolabel_x2->setText(tr("<div> Width: </div>"));
    infolabel_x3->setText(tr("<div> Length: </div>"));

    // Disable post-process
    plot_act->setEnabled(0);
    savetxt_act->setEnabled(0);
    genreport_act->setEnabled(0);
//    static_plot_index_label->setText("0");
    box_plot_static->setCurrentIndex(0);
    no_update_modal_plot = -1;
    non_bc_eigenmodes.resize(0);
    no_update_dynamic_plot = -1;
    no_update_static_plot =-1;
}

void MainWindow::wndResolution()
{
    // Build Labels
    int stw=30;     int sth=50;
    int w=120;      int h=20;       int gaph = 30;      int gapw=250;

    wndDialog->setFixedSize(350,150);
    QLabel *lab1 = new QLabel("<b><font color =#585858>Screen Width</font></b>",wndDialog);
    lab1->setGeometry(QRect(stw,sth,w,h));
    QLabel *lab2 = new QLabel("<b><font color =#585858>Screen Height</font></b>",wndDialog);
    lab2->setGeometry(QRect(stw,sth+gaph,w,h));

    line_screen_width->setGeometry(QRect(stw+gapw/1.5,sth,w/2,h));
    line_screen_height->setGeometry(QRect(stw+gapw/1.5,sth+gaph,w/2,h));

    QPushButton *but1 = new QPushButton("OK",wndDialog);
    but1->setGeometry(QRect(280,110,50,20));
    but1->setToolTip("Click to set the parameters");
    connect(but1,SIGNAL(clicked()),wndDialog,SLOT(accept()));

    QPropertyAnimation *animation = new QPropertyAnimation(wndDialog,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-150/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-350/2, fullScreenHeight/2-150/2, 1, 1));
    animation->start();

    wndDialog->exec();
}

void MainWindow::fullScreen()
{
    if(isFullScreen())
    {
        int screenWidth = this->width();
        int screenHeight = this->height();
        fullScreenAct->setText(tr("Full Screen"));
        this->resize(width_label->text().toInt(), height_label->text().toInt());
        this->move(screenWidth/2 - width_label->text().toInt()/2, screenHeight/2 - height_label->text().toInt()/2);
    }
    else
    {
        this->setWindowState(Qt::WindowFullScreen);
        fullScreenAct->setText(tr("Exit Full Screen"));
    }
}


void MainWindow::geom()
{
    gwdg->setFixedSize(550,350);
    gwdg->setWindowTitle("Geometry");

    // Build Labels
    int stw=70;     int sth=50;
    int w=120;      int h=20;       int gaph = 30;      int gapw=250;

    QLabel *lab1 = new QLabel("<b><FONT COLOR=#585858>Height (<FONT COLOR=#585858>x<sub>1</sub></font>)</b>",gwdg);
    lab1->setGeometry(QRect(stw,sth+1.5*gaph,w,h));
    QLabel *lab2 = new QLabel("<b><FONT COLOR=#585858>Width (<FONT COLOR=#585858>x<sub>2</sub></font>)</b>",gwdg);
    lab2->setGeometry(QRect(stw,sth+3.0*gaph,w,h));
    QLabel *lab3 = new QLabel("<b><FONT COLOR=#585858>Length (<FONT COLOR=#585858>x<sub>3</sub></font>)</b>",gwdg);
    lab3->setGeometry(QRect(stw,sth+4.5*gaph,w,h));

    line_x1->setGeometry(QRect(stw+gapw,sth+1.5*gaph,w/1.2,h));
    line_x1->setToolTip("Specify height of the beam");
    line_x2->setGeometry(QRect(stw+gapw,sth+3.0*gaph,w/1.2,h));
    line_x2->setToolTip("Specify width of the beam");
    line_x3->setGeometry(QRect(stw+gapw,sth+4.5*gaph,w/1.2,h));
    line_x3->setToolTip("Specify length of the beam");
    line_shear->setGeometry(QRect(stw+gapw,sth+6*gaph,w/1.2,h));
    line_shear->setToolTip("Specify shear factor. Must be between 0.5 and 1");

    QFrame *frame1 = new QFrame(gwdg);
    frame1->setFrameShape(QFrame::HLine);
    frame1->setGeometry(QRect(stw,sth+5.5*gaph,w/1.2+gapw,1));

    QLabel *lab4 = new QLabel("<b><font color=#585858>Shear Factor (</FONT><FONT COLOR=#585858>&#954;)</FONT><b>",gwdg);
    lab4->setGeometry(QRect(stw,sth+6*gaph,w,h));


    QPushButton *but1 = new QPushButton("OK",gwdg);
    but1->setGeometry(QRect(460,300,50,20));
    but1->setToolTip("Click to set the parameters");
    connect(but1,SIGNAL(clicked()),gwdg,SLOT(accept()));

    gwdg->connect(line_x1,SIGNAL(textEdited(QString)),this,SLOT(geom_x1(QString)));
    gwdg->connect(line_x2,SIGNAL(textEdited(QString)),this,SLOT(geom_x2(QString)));
    gwdg->connect(line_x3,SIGNAL(textEdited(QString)),this,SLOT(geom_x3(QString)));
    gwdg->connect(line_shear,SIGNAL(textEdited(QString)),this,SLOT(geom_shearfactor(QString)));

    connect(this,SIGNAL(destroyed()),gwdg,SLOT(close()));

    QPropertyAnimation *animation = new QPropertyAnimation(gwdg,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-350/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-550/2, fullScreenHeight/2-350/2, 1, 1));
    animation->start();

    gwdg->exec();
}

void MainWindow::mesh()
{
    // Build new Widget
    mwdg->setFixedSize(550,350);
    mwdg->setWindowTitle("Analysis Options");

    // Build Labels
    int stw=70;     int sth=50;
    int w=120;      int h=20;       int gaph = 30;      int gapw=250;

    QLabel *lab1 = new QLabel("<b><font color=#585858>Order of Bases</FONT>",mwdg);
    lab1->setGeometry(QRect(stw,sth+gaph,w,h));

    QLabel *lab2 = new QLabel("<b><font color=#585858>Number of Elements</FONT>",mwdg);
    lab2->setGeometry(QRect(stw,sth+2.5*gaph,w,h));

    QLabel *lab3 = new QLabel("<b><font color=#585858>Basis Functions</font></b>",mwdg);
    lab3->setGeometry(QRect(stw,sth+4*gaph,w,h));


    // Build boxes in front of them
    box_C->setGeometry(QRect(stw+gapw,sth+gaph,w,h));
    box_C->setToolTip("Specify order of basis functions. This is one less than polynomial degree");
    box_C->setRange(0,50);

    line_n->setGeometry(QRect(stw+gapw,sth+2.5*gaph,w,h));
    line_n->setToolTip("Specify number elements. Must be positive integer");

    box_bases->setGeometry(QRect(stw+gapw,sth+4*gaph,w,h));
    box_bases->setToolTip("Specify type of basis functions");

    QPushButton *but1 = new QPushButton("OK",mwdg);
    but1->setGeometry(QRect(460,300,50,20));
    but1->setToolTip("Click to set the parameters");
    connect(but1,SIGNAL(clicked()),mwdg,SLOT(accept()));

    // Handle signals and slots
    mwdg->connect(box_C,SIGNAL(valueChanged(QString)),this,SLOT(an_C(QString)));
    mwdg->connect(line_n,SIGNAL(textEdited(QString)),this,SLOT(an_n(QString)));
    mwdg->connect(box_bases,SIGNAL(currentTextChanged(QString)),this,SLOT(an_bases(QString)));

    mwdg->connect(box_C,SIGNAL(valueChanged(QString)),this,SLOT(an_node_C(QString)));
    mwdg->connect(line_n,SIGNAL(textEdited(QString)),this,SLOT(an_node_n(QString)));

    connect(this,SIGNAL(destroyed()),mwdg,SLOT(close()));


    QPropertyAnimation *animation = new QPropertyAnimation(mwdg,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-350/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-550/2, fullScreenHeight/2-350/2, 1, 1));
    animation->start();

    mwdg->exec();
}

void MainWindow::matm()
{
    wdg_matm->setFixedSize(550,350);
    wdg_matm->setWindowTitle("Mechanical Properties");

    // Build Labels
    int stw=70;     int sth=50;
    int w=130;      int h=20;       int gaph = 30;      int gapw=250;

    QLabel *lab1 = new QLabel("<b><font color=#585858>Material Class:</FONT></b>",wdg_matm);
    lab1->setGeometry(QRect(stw,sth,w,h));

    QLabel *lab2 = new QLabel("<b><FONT COLOR=#585858>Density</FONT></b>",wdg_matm);
    lab2->setGeometry(QRect(stw,sth+1*gaph,w,h));

    // Draw a line to seperate
    QFrame *frame1 = new QFrame(wdg_matm);
    frame1->setFrameShape(QFrame::HLine);
    frame1->setGeometry(QRect(stw,sth+2*gaph,w+gapw,1));

    QLabel *lab3 = new QLabel("<b><font color=#585858>Isotropic Properties:</FONT></b>",wdg_matm);
    lab3->setGeometry(QRect(stw,sth+2.1*gaph,w,h));

    QLabel *lab4 = new QLabel("<b><font color=#585858>&mu;</FONT></b>",wdg_matm);
    lab4->setGeometry(QRect(stw,sth+3*gaph,w,h));

    QLabel *lab5 = new QLabel("<b><FONT COLOR=#585858>&lambda;</FONT></b>",wdg_matm);
    lab5->setGeometry(QRect(stw,sth+4*gaph,w,h));

    QFrame *frame2 = new QFrame(wdg_matm);
    frame2->setFrameShape(QFrame::HLine);
    frame2->setGeometry(QRect(stw,sth+5*gaph,w+gapw,1));

    QLabel *lab6 = new QLabel("<b><font color=#585858>Anisotropic Properties:</FONT></b>",wdg_matm);
    lab6->setGeometry(QRect(stw,sth+5.1*gaph,w,h));
    QLabel *lab7 = new QLabel("<b><FONT COLOR=#585858>C<sub>33</sub></FONT></b>",wdg_matm);
    lab7->setGeometry(QRect(stw,sth+6*gaph,w/2.1,h));
    QLabel *lab8 = new QLabel("<b><FONT COLOR=#585858>C<sub>34</sub></FONT></b>",wdg_matm);
    lab8->setGeometry(QRect(stw+gapw/3.93,sth+6*gaph,w/2.1,h));
    QLabel *lab9 = new QLabel("<b><FONT COLOR=#585858>C<sub>35</sub></FONT></b>",wdg_matm);
    lab9->setGeometry(QRect(stw+2*gapw/3.93,sth+6*gaph,w/2.1,h));
    QLabel *lab10 = new QLabel("<b><FONT COLOR=#585858>C<sub>44</sub></FONT></b>",wdg_matm);
    lab10->setGeometry(QRect(stw+3*gapw/3.93,sth+6*gaph,w/2.1,h));
    QLabel *lab11 = new QLabel("<b><FONT COLOR=#585858>C<sub>45</sub></FONT></b>",wdg_matm);
    lab11->setGeometry(QRect(stw+4*gapw/3.93,sth+6*gaph,w/2.1,h));
    QLabel *lab12 = new QLabel("<b><FONT COLOR=#585858>C<sub>55</sub></FONT></b>",wdg_matm);
    lab12->setGeometry(QRect(stw+5*gapw/3.93,sth+6*gaph,w/2.1,h));

    // build strings for comboxes
    box_iso->setGeometry(QRect(stw+gapw,sth,w,h));
    box_iso->setToolTip("Specify material class");
    line_density->setGeometry(QRect(stw+gapw,sth+1*gaph,w,h));
    line_density->setToolTip("Density for modal and dynamic analysis");
    line_mu->setGeometry(QRect(stw+gapw,sth+3*gaph,w,h));
    line_mu->setToolTip("<div>Second Lam&eacute; parameter</div>");
    line_lambda->setGeometry(QRect(stw+gapw,sth+4*gaph,w,h));
    line_lambda->setToolTip("<div>First Lam&eacute; parameter</div>");
    line_c33->setGeometry(QRect(stw,sth+7*gaph,w/2.1,h));
    line_c33->setToolTip("<div>C<sub>33</sub></div>");
    line_c34->setGeometry(QRect(stw+gapw/3.93,sth+7*gaph,w/2.1,h));
    line_c34->setToolTip("<div>C<sub>34</sub></div>");
    line_c35->setGeometry(QRect(stw+2*gapw/3.93,sth+7*gaph,w/2.1,h));
    line_c35->setToolTip("<div>C<sub>35</sub></div>");
    line_c44->setGeometry(QRect(stw+3*gapw/3.93,sth+7*gaph,w/2.1,h));
    line_c44->setToolTip("<div>C<sub>44</sub></div>");
    line_c45->setGeometry(QRect(stw+4*gapw/3.93,sth+7*gaph,w/2.1,h));
    line_c45->setToolTip("<div>C<sub>45</sub></div>");
    line_c55->setGeometry(QRect(stw+5*gapw/3.93,sth+7*gaph,w/2.1,h));
    line_c55->setToolTip("<div>C<sub>55</sub></div>");

    QLabel *lab_info = new QLabel("<font color=#585858 size=2>*Full anisotropic elasticity tensor is not required.</font>",wdg_matm);
    lab_info->setGeometry(QRect(stw,sth+8*gaph,3.0*w,h));

    QPushButton *but_matm = new QPushButton("OK",wdg_matm);
    but_matm->setGeometry(QRect(460,300,50,20));
    but_matm->setToolTip("Click to set the parameters");
    but_matm->setObjectName("OK");

    // Handle signals and slots
    wdg_matm->connect(line_density,SIGNAL(textChanged(QString)),this,SLOT(mat_density(QString)));
    wdg_matm->connect(line_mu,SIGNAL(textEdited(QString)),this,SLOT(mat_mu(QString)));
    wdg_matm->connect(line_lambda,SIGNAL(textEdited(QString)),this,SLOT(mat_lambda(QString)));
    wdg_matm->connect(line_c33,SIGNAL(textEdited(QString)),this,SLOT(mat_c33(QString)));
    wdg_matm->connect(line_c34,SIGNAL(textEdited(QString)),this,SLOT(mat_c34(QString)));
    wdg_matm->connect(line_c35,SIGNAL(textEdited(QString)),this,SLOT(mat_c35(QString)));
    wdg_matm->connect(line_c44,SIGNAL(textEdited(QString)),this,SLOT(mat_c44(QString)));
    wdg_matm->connect(line_c45,SIGNAL(textEdited(QString)),this,SLOT(mat_c45(QString)));
    wdg_matm->connect(line_c55,SIGNAL(textEdited(QString)),this,SLOT(mat_c55(QString)));
    wdg_matm->connect(box_iso,SIGNAL(currentTextChanged(QString)),this,SLOT(mat_iso(QString)));
    // OK button
    wdg_matm->connect(but_matm,SIGNAL(clicked()),wdg_matm,SLOT(accept()));

    connect(this,SIGNAL(destroyed()),wdg_matm,SLOT(close())); // This does not make sense for dialogs though


    QPropertyAnimation *animation = new QPropertyAnimation(wdg_matm,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-350/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-550/2, fullScreenHeight/2-350/2, 1, 1));
    animation->start();

    wdg_matm->exec();
}

void MainWindow::mate()
{
    wdg_mate->setFixedSize(550,350);
    wdg_mate->setWindowTitle("Electrical Properties");

    // Build Labels
    int stw=70;     int sth=50;
    int w=130;      int h=20;       int gaph = 30;      int gapw=250;

    // Labels
    QLabel *lab1 = new QLabel("<b><font color=#585858>Dielectric Tensor (&#949;) :</FONT>",wdg_mate);
    lab1->setGeometry(QRect(stw,sth,w,h));
    QLabel *lab2 = new QLabel("<b><font color=#585858>Piezoelectric Tensor (P) :</FONT>",wdg_mate);
    lab2->setGeometry(QRect(stw,sth+4*gaph,w+10,h));

    int dumm = 35;

    // LineEdits
    line_e11->setGeometry(QRect(dumm+stw+1*gapw/3.5,sth+1*gaph,w/2.0,h));
    line_e12->setGeometry(QRect(dumm+stw+2*gapw/3.5,sth+1*gaph,w/2.0,h));
    line_e13->setGeometry(QRect(dumm+stw+3*gapw/3.5,sth+1*gaph,w/2.0,h));
    line_e21->setGeometry(QRect(dumm+stw+1*gapw/3.5,sth+2*gaph,w/2.0,h));
    line_e22->setGeometry(QRect(dumm+stw+2*gapw/3.5,sth+2*gaph,w/2.0,h));
    line_e23->setGeometry(QRect(dumm+stw+3*gapw/3.5,sth+2*gaph,w/2.0,h));
    line_e31->setGeometry(QRect(dumm+stw+1*gapw/3.5,sth+3*gaph,w/2.0,h));
    line_e32->setGeometry(QRect(dumm+stw+2*gapw/3.5,sth+3*gaph,w/2.0,h));
    line_e33->setGeometry(QRect(dumm+stw+3*gapw/3.5,sth+3*gaph,w/2.0,h));

    line_e11->setToolTip("<div>&epsilon;<sub>11</sub></div>");
    line_e12->setToolTip("<div>&epsilon;<sub>12</sub></div>");
    line_e13->setToolTip("<div>&epsilon;<sub>13</sub></div>");
    line_e21->setToolTip("<div>&epsilon;<sub>21</sub></div>");
    line_e22->setToolTip("<div>&epsilon;<sub>22</sub></div>");
    line_e23->setToolTip("<div>&epsilon;<sub>23</sub></div>");
    line_e31->setToolTip("<div>&epsilon;<sub>31</sub></div>");
    line_e32->setToolTip("<div>&epsilon;<sub>32</sub></div>");
    line_e33->setToolTip("<div>&epsilon;<sub>33</sub></div>");


    line_p11->setGeometry(QRect(stw+0*gapw/3.5,sth+5*gaph,w/2.0,h));
    line_p12->setGeometry(QRect(stw+1*gapw/3.5,sth+5*gaph,w/2.0,h));
    line_p13->setGeometry(QRect(stw+2*gapw/3.5,sth+5*gaph,w/2.0,h));
    line_p14->setGeometry(QRect(stw+3*gapw/3.5,sth+5*gaph,w/2.0,h));
    line_p15->setGeometry(QRect(stw+4*gapw/3.5,sth+5*gaph,w/2.0,h));
    line_p16->setGeometry(QRect(stw+5*gapw/3.5,sth+5*gaph,w/2.0,h));
    line_p21->setGeometry(QRect(stw+0*gapw/3.5,sth+6*gaph,w/2.0,h));
    line_p22->setGeometry(QRect(stw+1*gapw/3.5,sth+6*gaph,w/2.0,h));
    line_p23->setGeometry(QRect(stw+2*gapw/3.5,sth+6*gaph,w/2.0,h));
    line_p24->setGeometry(QRect(stw+3*gapw/3.5,sth+6*gaph,w/2.0,h));
    line_p25->setGeometry(QRect(stw+4*gapw/3.5,sth+6*gaph,w/2.0,h));
    line_p26->setGeometry(QRect(stw+5*gapw/3.5,sth+6*gaph,w/2.0,h));
    line_p31->setGeometry(QRect(stw+0*gapw/3.5,sth+7*gaph,w/2.0,h));
    line_p32->setGeometry(QRect(stw+1*gapw/3.5,sth+7*gaph,w/2.0,h));
    line_p33->setGeometry(QRect(stw+2*gapw/3.5,sth+7*gaph,w/2.0,h));
    line_p34->setGeometry(QRect(stw+3*gapw/3.5,sth+7*gaph,w/2.0,h));
    line_p35->setGeometry(QRect(stw+4*gapw/3.5,sth+7*gaph,w/2.0,h));
    line_p36->setGeometry(QRect(stw+5*gapw/3.5,sth+7*gaph,w/2.0,h));

    line_p11->setToolTip("<div>P<sub>11</sub></div>");
    line_p12->setToolTip("<div>P<sub>12</sub></div>");
    line_p13->setToolTip("<div>P<sub>13</sub></div>");
    line_p14->setToolTip("<div>P<sub>14</sub></div>");
    line_p15->setToolTip("<div>P<sub>15</sub></div>");
    line_p16->setToolTip("<div>P<sub>16</sub></div>");
    line_p21->setToolTip("<div>P<sub>21</sub></div>");
    line_p22->setToolTip("<div>P<sub>22</sub></div>");
    line_p23->setToolTip("<div>P<sub>23</sub></div>");
    line_p24->setToolTip("<div>P<sub>24</sub></div>");
    line_p25->setToolTip("<div>P<sub>25</sub></div>");
    line_p26->setToolTip("<div>P<sub>26</sub></div>");
    line_p31->setToolTip("<div>P<sub>31</sub></div>");
    line_p32->setToolTip("<div>P<sub>32</sub></div>");
    line_p33->setToolTip("<div>P<sub>33</sub></div>");
    line_p34->setToolTip("<div>P<sub>34</sub></div>");
    line_p35->setToolTip("<div>P<sub>35</sub></div>");
    line_p36->setToolTip("<div>P<sub>36</sub></div>");

    // OK button
    QPushButton *but_mate = new QPushButton("OK",wdg_mate);
    but_mate->setGeometry(QRect(460,300,50,20));
    but_mate->setToolTip("Click to set the parameters");
    wdg_mate->connect(but_mate,SIGNAL(clicked()),wdg_mate,SLOT(accept()));

    wdg_mate->connect(line_e11,SIGNAL(textEdited(QString)),this,SLOT(mat_e11(QString)));
    wdg_mate->connect(line_e12,SIGNAL(textEdited(QString)),this,SLOT(mat_e12(QString)));
    wdg_mate->connect(line_e13,SIGNAL(textEdited(QString)),this,SLOT(mat_e13(QString)));
    wdg_mate->connect(line_e21,SIGNAL(textEdited(QString)),this,SLOT(mat_e21(QString)));
    wdg_mate->connect(line_e22,SIGNAL(textEdited(QString)),this,SLOT(mat_e22(QString)));
    wdg_mate->connect(line_e23,SIGNAL(textEdited(QString)),this,SLOT(mat_e23(QString)));
    wdg_mate->connect(line_e31,SIGNAL(textEdited(QString)),this,SLOT(mat_e31(QString)));
    wdg_mate->connect(line_e32,SIGNAL(textEdited(QString)),this,SLOT(mat_e32(QString)));
    wdg_mate->connect(line_e33,SIGNAL(textEdited(QString)),this,SLOT(mat_e33(QString)));

    wdg_mate->connect(line_p11,SIGNAL(textEdited(QString)),this,SLOT(mat_p11(QString)));
    wdg_mate->connect(line_p12,SIGNAL(textEdited(QString)),this,SLOT(mat_p12(QString)));
    wdg_mate->connect(line_p13,SIGNAL(textEdited(QString)),this,SLOT(mat_p13(QString)));
    wdg_mate->connect(line_p14,SIGNAL(textEdited(QString)),this,SLOT(mat_p14(QString)));
    wdg_mate->connect(line_p15,SIGNAL(textEdited(QString)),this,SLOT(mat_p15(QString)));
    wdg_mate->connect(line_p16,SIGNAL(textEdited(QString)),this,SLOT(mat_p16(QString)));
    wdg_mate->connect(line_p21,SIGNAL(textEdited(QString)),this,SLOT(mat_p21(QString)));
    wdg_mate->connect(line_p22,SIGNAL(textEdited(QString)),this,SLOT(mat_p22(QString)));
    wdg_mate->connect(line_p23,SIGNAL(textEdited(QString)),this,SLOT(mat_p23(QString)));
    wdg_mate->connect(line_p24,SIGNAL(textEdited(QString)),this,SLOT(mat_p24(QString)));
    wdg_mate->connect(line_p25,SIGNAL(textEdited(QString)),this,SLOT(mat_p25(QString)));
    wdg_mate->connect(line_p26,SIGNAL(textEdited(QString)),this,SLOT(mat_p26(QString)));
    wdg_mate->connect(line_p31,SIGNAL(textEdited(QString)),this,SLOT(mat_p31(QString)));
    wdg_mate->connect(line_p32,SIGNAL(textEdited(QString)),this,SLOT(mat_p32(QString)));
    wdg_mate->connect(line_p33,SIGNAL(textEdited(QString)),this,SLOT(mat_p33(QString)));
    wdg_mate->connect(line_p34,SIGNAL(textEdited(QString)),this,SLOT(mat_p34(QString)));
    wdg_mate->connect(line_p35,SIGNAL(textEdited(QString)),this,SLOT(mat_p35(QString)));
    wdg_mate->connect(line_p36,SIGNAL(textEdited(QString)),this,SLOT(mat_p36(QString)));


    QPropertyAnimation *animation = new QPropertyAnimation(wdg_mate,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-350/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-550/2, fullScreenHeight/2-350/2, 1, 1));
    animation->start();

    wdg_mate->exec();
}


void MainWindow::bc_dirichlet()
{
    // Build dialogbox
    wdg_bc_d->setFixedSize(550,350);
    wdg_bc_d->setWindowTitle("Dirichlet Boundary Conditions");

    // Build Labels
    int stw=70;     int sth=50;
    int w=180;      int h=20;       int gaph = 30;      int gapw=250;

    // Labels
    QLabel *lab1 = new QLabel("<b><font color=#585858>Dirichlet Nodes :</FONT>",wdg_bc_d);
    lab1->setGeometry(QRect(stw,sth+1*gaph,w,h));
    QLabel *lab2 = new QLabel("<b><font color=#585858>Degrees of Freedom :</FONT>",wdg_bc_d);
    lab2->setGeometry(QRect(stw,sth+3*gaph,w,h));
    QLabel *lab3 = new QLabel("<b><font color=#585858>Imposed Values :</FONT>",wdg_bc_d);
    lab3->setGeometry(QRect(stw,sth+5*gaph,w,h));

    line_nodes->setGeometry(QRect(stw,sth+2*gaph,w+gapw,h));
    line_nodes->setToolTip("Separate Dirichlet nodes by a ;");
    line_var->setGeometry(QRect(stw,sth+4*gaph,w+gapw,h));
    line_var->setToolTip("Separate DoF's of a specific node by a , and keep ; between DoF's of different nodes");
    line_amnt->setGeometry(QRect(stw,sth+6*gaph,w+gapw,h));
    line_amnt->setToolTip("Specificed/known amount. Must be the same format as above (Degrees of Freedom)");

    // OK button
    QPushButton *but_m= new QPushButton("OK",wdg_bc_d);
    but_m->setGeometry(QRect(460,300,50,20));
    but_m->setToolTip("Click to set the parameters");
    wdg_bc_d->connect(but_m,SIGNAL(clicked()),wdg_bc_d,SLOT(accept()));

//    Cancel button (if needed)
//    QPushButton *but_m_cancel= new QPushButton("Cancel",dlg);
//    but_m_cancel->setGeometry(QRect(400,300,60,20));
//    but_m_cancel->setToolTip("Click to cancel");
//    dlg->connect(but_m_cancel,SIGNAL(clicked()),dlg,SLOT(reject()));

    wdg_bc_d->connect(line_var,SIGNAL(textEdited(QString)),this,SLOT(bc_var(QString)));
    wdg_bc_d->connect(line_nodes,SIGNAL(textEdited(QString)),this,SLOT(bc_nodes(QString)));
    wdg_bc_d->connect(line_amnt,SIGNAL(textEdited(QString)),this,SLOT(bc_amnt(QString)));


    QPropertyAnimation *animation = new QPropertyAnimation(wdg_bc_d,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-350/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-550/2, fullScreenHeight/2-350/2, 1, 1));
    animation->start();

    wdg_bc_d->exec();
}


void MainWindow::bc_neumann()
{
    // Build dialogbox
    wdg_bc_n->setFixedSize(550,350);
    wdg_bc_n->setWindowTitle("Neumann Boundary Conditions");

    // Build Labels
    int stw=70;     int sth=80;
    int w=180;      int h=20;       int gaph = 30;      int gapw=250;

    // Labels
    QLabel *lab1 = new QLabel("<b><font color=#585858>Point Loads/Moments :</FONT>",wdg_bc_n);
    lab1->setGeometry(QRect(stw,sth+0*gaph,w,h));
    QLabel *lab2 = new QLabel("<b><font color=#585858>Point Loads'/Moments' Positions :</FONT>",wdg_bc_n);
    lab2->setGeometry(QRect(stw,sth+2*gaph,w,h));
    QLabel *lab5 = new QLabel("<b><font color=#585858>Uniformly Distributed Load(s) :</FONT>",wdg_bc_n);
    lab5->setGeometry(QRect(stw,sth+4*gaph,2*w,h));

    line_point_loads->setGeometry(QRect(stw,sth+1*gaph,w+gapw,h));
    line_point_loads->setToolTip("Each point load has an amount and a degree of freedom it is applied upon, separated by a comma. All point loads are separated by a ;");
    line_point_pos->setGeometry(QRect(stw,sth+3*gaph,w+gapw,h));
    line_point_pos->setToolTip("Position of point loads in 3D space, formatted like '1.5,2,3.5; 3.2,0,2.9'");
    line_udl->setGeometry(QRect(stw,sth+5*gaph,w+gapw,h));
    line_udl->setToolTip("Each UDL has an amount, a specific degree of freedom, starting element and the number of elements it is applied upon");


    // OK button
    QPushButton *but_e = new QPushButton("OK",wdg_bc_n);
    but_e->setGeometry(QRect(460,300,50,20));
    but_e->setToolTip("Click to set the parameters");
    wdg_bc_n->connect(but_e,SIGNAL(clicked()),wdg_bc_n,SLOT(close()));

    wdg_bc_n->connect(line_point_loads,SIGNAL(textEdited(QString)),this,SLOT(point_loads(QString)));
    wdg_bc_n->connect(line_point_pos,SIGNAL(textEdited(QString)),this,SLOT(point_pos(QString)));
    wdg_bc_n->connect(line_udl,SIGNAL(textEdited(QString)),this,SLOT(udl(QString)));


    QPropertyAnimation *animation = new QPropertyAnimation(wdg_bc_n,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-350/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-550/2, fullScreenHeight/2-350/2, 1, 1));
    animation->start();

    wdg_bc_n->exec();
}

void MainWindow::an_opts()
{
    // Build new Widget
    awdg->setFixedSize(550,350);
    awdg->setWindowTitle("Analysis Options");

    // Build Labels
    int stw=70;     int sth=50;
    int w=120;      int h=20;       int gaph = 30;      int gapw=250;

    QLabel *lab1 = new QLabel("<b><font color=#585858>Analysis Type</FONT>",awdg);
    lab1->setGeometry(QRect(stw,sth+0*gaph,w,h));
    QLabel *lab2 = new QLabel("<b><FONT COLOR=#585858>Integration Scheme</FONT></b>",awdg);
    lab2->setGeometry(QRect(stw,sth+1*gaph,w,h));
    QLabel *lab3 = new QLabel("<b><font color=#585858>Dynamic Integrator</FONT>",awdg);
    lab3->setGeometry(QRect(stw,sth+2.5*gaph,w,h));
    QLabel *lab4 = new QLabel("<b><font color=#585858>Import Dynamic Data</FONT>",awdg);
    lab4->setGeometry(QRect(stw,sth+3.5*gaph,w+5,h));
    QLabel *lab5 = new QLabel("<b><font color=#585858>Imposed Nodes</FONT>",awdg);
    lab5->setGeometry(QRect(stw,sth+4.5*gaph,w,h));
    QLabel *lab6 = new QLabel("<b><font color=#585858>Imposed DoF's</FONT>",awdg);
    lab6->setGeometry(QRect(stw,sth+5.5*gaph,w,h));
    QLabel *lab7 = new QLabel("<b><font color=#585858>Output Node-DoF</FONT>",awdg);
    lab7->setGeometry(QRect(stw,sth+6.5*gaph,w,h));

    // Draw a line to seperate
    QFrame *frame1 = new QFrame(awdg);
    frame1->setFrameShape(QFrame::HLine);
    frame1->setGeometry(QRect(stw,sth+2*gaph,w+gapw,1));

    // Build boxes in front of them
    box_analysis->setGeometry(QRect(stw+gapw,sth+0*gaph,w,h));
    box_analysis->setToolTip("Specify type of analysis");

    box_numint->setGeometry(QRect(stw+gapw,sth+1*gaph,w,h));
    box_numint->setToolTip("Specify type of numerical integration");

    box_dynint->setGeometry(QRect(stw+gapw,sth+2.5*gaph,w,h));
    box_dynint->setToolTip("Specify type of dynamic integration");

    line_importdyn->setGeometry(QRect(stw+gapw-w/1.5,sth+3.5*gaph,w*1.125,h));
    line_importdyn->setToolTip("File link appears here");

    but_importdyn->setGeometry(QRect(stw+gapw+w*1.0/2.0,sth+3.5*gaph,w/2.0,h));
    but_importdyn->setToolTip("Browse for dynamic data file");

    line_nodes_dyn->setGeometry(QRect(stw+gapw-w/1.5,sth+4.5*gaph,w*1.67,h));
    line_nodes_dyn->setToolTip("Nodes on which dynamic load is to be applied");

    line_var_dyn->setGeometry(QRect(stw+gapw-w/1.5,sth+5.5*gaph,1.66*w,h));
    line_var_dyn->setToolTip("Degrees of freedom on which dynamic load is to be applied");

    line_out_dyn->setGeometry(QRect(stw+gapw-w/1.5,sth+6.5*gaph,1.66*w,h));
    line_out_dyn->setToolTip("Node and degree of freedom for which the results are to be output");

    QPushButton *but1 = new QPushButton("OK",awdg);
    but1->setGeometry(QRect(460,300,50,20));
    but1->setToolTip("Click to set the parameters");
    connect(but1,SIGNAL(clicked()),awdg,SLOT(accept()));

    // Handle signals and slots
    awdg->connect(box_numint,SIGNAL(currentTextChanged(QString)),this,SLOT(an_numint(QString)));
    awdg->connect(box_analysis,SIGNAL(currentTextChanged(QString)),this,SLOT(an_type(QString)));
    awdg->connect(box_dynint,SIGNAL(currentTextChanged(QString)),this,SLOT(an_dynint(QString)));


    QPropertyAnimation *animation = new QPropertyAnimation(awdg,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-350/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-550/2, fullScreenHeight/2-350/2, 1, 1));
    animation->start();

    awdg->exec();
}

void MainWindow::solve()
{
    // Build errorbox for outputing errors/warnings
    QMessageBox errorbox;
    errorbox.setWindowFlags(Qt::FramelessWindowHint);
    QImage img(path+"/img/rsz1_oops.png");
    QPixmap oops = QPixmap::fromImage(img);
    oops.fromImage(img);
    errorbox.setIconPixmap(oops);
    errorbox.setFixedSize(150,50);
    errorbox.setWindowFlags(Qt::FramelessWindowHint);


    // The first part of solve member function is read and check for input data
    bool check_data=true;
    // Reassign and check data:
    double x1 = x1_label->text().toDouble();
    double x2 = x2_label->text().toDouble();
    double Length = x3_label->text().toDouble();

    // Check for analysis options
   if (n_label->text().isEmpty() || n_label->text().toInt()==0)
   {
       n_label->setText("1");
   }

   if (analysis_label->text().isEmpty())
       analysis_label->setText("Static");

    // Check if geometry is entered correctly
    if (x1==0 && x2==0 && Length==0)
    {
        errorbox.setText("No geometry supplied.");
        errorbox.exec();
        check_data = false;
    }
    else if (Length==0)
    {
        errorbox.setText("Beam cannot have zero length.");
        errorbox.exec();
        check_data = false;
    }
    else if (x1==0)
    {
        errorbox.setText("Beam cannot have zero height.");
        errorbox.exec();
        check_data = false;
    }
    else if (x2==0)
    {
        errorbox.setText("Beam cannot have zero width.");
        errorbox.exec();
        check_data = false;
    }

    if (shear_label->text().isEmpty() || shear_label->text().toDouble()<0.5 || shear_label->text().toDouble()>1)
    {
        shear_label->setNum(1.0);
    }


    double density = density_label->text().toDouble();
    double mu = mu_label->text().toDouble();
    double lambda = lambda_label->text().toDouble();
    Eigen::Vector2d isoElast; isoElast << mu, lambda;

    // Build and fill dielectric tensor
    Eigen::Matrix<double,6,6> Elast; Elast.setZero(6,6);
    Elast(2,2)=c33_label->text().toDouble();
    Elast(3,3)=c44_label->text().toDouble();
    Elast(4,4)=c55_label->text().toDouble();
    Elast(2,3)=c34_label->text().toDouble();
    Elast(2,4)=c35_label->text().toDouble();
    Elast(3,4)=c45_label->text().toDouble();

    // Build and fill dielectric tensor
    Eigen::Matrix<double,3,3> Die; Die.setZero(3,3);
    Die << e11_label->text().toDouble(), e12_label->text().toDouble(), e13_label->text().toDouble(),
            e21_label->text().toDouble(), e22_label->text().toDouble(), e23_label->text().toDouble(),
            e31_label->text().toDouble(), e32_label->text().toDouble(), e33_label->text().toDouble();

    // Build and fill piezoelectric tensor
    Eigen::Matrix<double,3,9> Piezo = Eigen::Matrix<double,3,9>::Zero();
    Piezo << p11_Label->text().toDouble(), p12_Label->text().toDouble(), p13_Label->text().toDouble(), p14_Label->text().toDouble(), p15_Label->text().toDouble(), p16_Label->text().toDouble(), p14_Label->text().toDouble(), p15_Label->text().toDouble(), p16_Label->text().toDouble(),
            p21_Label->text().toDouble(), p22_Label->text().toDouble(), p23_Label->text().toDouble(), p24_Label->text().toDouble(), p25_Label->text().toDouble(), p26_Label->text().toDouble(), p24_Label->text().toDouble(), p25_Label->text().toDouble(), p26_Label->text().toDouble(),
            p31_Label->text().toDouble(), p32_Label->text().toDouble(), p33_Label->text().toDouble(), p34_Label->text().toDouble(), p35_Label->text().toDouble(), p36_Label->text().toDouble(), p34_Label->text().toDouble(), p35_Label->text().toDouble(), p36_Label->text().toDouble();

    if (iso_label->text().isEmpty())
        iso_label->setText("Isotropic");

    if (check_data)
    {
        if (iso_label->text().compare("Isotropic")==0 && mu==0 && lambda==0)
        {
            errorbox.setText("<div> Lam&eacute; parameters are not defined.</div>");
            errorbox.exec();
            check_data = false;
        }
        else if (iso_label->text().compare("Isotropic")==0 && mu!=0 && lambda==0)
        {
            errorbox.setText("<div> One Lam&eacute; parameter (&#955;) is not defined.</div>");
            errorbox.exec();
            check_data = false;
        }
        else if (iso_label->text().compare("Isotropic")==0 && mu==0 && lambda!=0)
        {
            errorbox.setText("<div> One Lam&eacute; parameter (&#956;) is not defined.</div>");
            errorbox.exec();
            check_data = false;
        }
        else if (iso_label->text().compare("Anisotropic")==0 && Elast.isZero(1e-30))
        {
            errorbox.setText("<div> Anisotropic material properties are not defined.</div>");
            errorbox.exec();
            check_data = false;
        }
        else if (iso_label->text().compare("Anisotropic")==0 && (Elast(2,2)==0 || Elast(3,3)==0 || Elast(4,4)==0))
        {
            errorbox.setText("<div> Sufficient anisotropic material properties are not defined.</div>");
            errorbox.exec();
            check_data = false;
        }
        else if (Die.isZero(1e-30))
        {
            errorbox.setText("<div> Dielectric material properties are not defined.</div>");
            errorbox.exec();
            check_data = false;
        }
        else if (Die(0,0)==0 || Die(1,1)==0 || Die(2,2)==0)
        {
            errorbox.setText("<div> Dielectric tensor has zero diagonal elements.</div>");
            errorbox.exec();
            check_data = false;
        }
    }


    // Build Dirichlet data
    // Start with variables (DoFs)
    QVector<double> bc_var_qtl;
    QStringList var = bc_var_label->text().split(";");
    for (int i=0; i<var.size(); ++i)
    {
        QStringList dum_var = var[i].split(",");
        for (int j=0; j<dum_var.size(); ++j)
        {
            bc_var_qtl.push_back(dum_var[j].toDouble());
        }
    }

    // Get Amounts
    QVector<double> bc_amnt_qtl;
    QStringList amnt = bc_amnt_label->text().split(";");
    QVector<int> no_dofs_per_node;
    for (int i=0; i<amnt.size(); ++i)
    {
        QStringList dum_amnt = amnt[i].split(",");
        no_dofs_per_node.push_back(dum_amnt.size());
        for (int j=0; j<dum_amnt.size(); ++j)
        {
            bc_amnt_qtl.push_back(dum_amnt[j].toDouble());
        }
    }

    // Check BC var and amnt compatibility
    if (check_data)
    {
        if (var.size()!=amnt.size())
        {
            errorbox.setText("Incompatible degrees of freedom and imposed values for boundary conditions.");
            errorbox.exec();
            check_data = false;
        }
        if (bc_var_qtl.size()!=bc_amnt_qtl.size())
        {
            errorbox.setText("Incompatible degrees of freedom and imposed values for boundary conditions.");
            errorbox.exec();
            check_data = false;
        }
    }

    // Ensure compatibility with number of nodes
    QStringList nodes = bc_nodes_label->text().split(";");
    if (check_data)
    {
        if (nodes.size()!=amnt.size())
        {
            errorbox.setText("Incompatible number of nodes, degrees of freedom/imposed values for boundary conditions.");
            errorbox.exec();
            check_data = false;
        }
    }

    // Now that we have ensured compatibility between var and amnt lets get boundary nodes
    QVector<double> bc_nodes_qtl;
    for (int i=0; i<no_dofs_per_node.size(); ++i)
    {
        for (int j=0; j<no_dofs_per_node[i]; ++j)
        {
            bc_nodes_qtl.push_back(nodes[i].toDouble());
        }
    }

    // Check Loads
    // Point loads
    QStringList ploads = point_loads_label->text().split(";");
    QVector<double> point_loads_amnt_qtl, point_loads_var_qtl;
    if (check_data)
    {
        for (int i=0; i<ploads.size(); ++i)
        {
            QStringList dum_point = ploads[i].split(",");
            // Check each load data
            if (dum_point.size()==2)
            {
                if (dum_point[1].toDouble()>11 || dum_point[1].toDouble()<1)
                {
                    errorbox.setText("Incorrect load data. DoF out of range.");
                    errorbox.exec();
                    check_data = false;
                }
                else
                {
                    point_loads_amnt_qtl.push_back(dum_point[0].toDouble());
                    point_loads_var_qtl.push_back(dum_point[1].toDouble());
                }
            }
        }
    }

    // Point load positions
    QStringList poss = point_pos_label->text().split(";");
    // Check if loads and their positions are compatible
    if (check_data)
    {
        if (ploads.size()!=poss.size())
        {
            errorbox.setText("Loads and their positions are not compatible.");
            errorbox.exec();
            check_data = false;
        }
    }


    QVector<double> pos_x1_qtl, pos_x2_qtl, pos_x3_qtl;
    if (check_data)
    {
        for (int i=0; i<poss.size(); ++i)
        {
            QStringList dum_pos = poss[i].split(",");
            // Check each load position data
            if (dum_pos.size()==3)
            {
                pos_x1_qtl.push_back(dum_pos[1].toDouble());
                pos_x2_qtl.push_back(dum_pos[2].toDouble());
                pos_x3_qtl.push_back(dum_pos[0].toDouble());
            }
        }
    }


    // Check UDL
    QStringList udl_loads = udl_label->text().split(";");
    QVector<double> udl_amnt_qtl, udl_var_qtl,udl_start_qtl,udl_elem_qtl;
    if (check_data)
    {
        for (int i=0; i<udl_loads.size(); ++i)
        {
            QStringList dum_udl = udl_loads[i].split(",");
            // Check each UDL data
            if (dum_udl.size()==4)
            {
                if (dum_udl[1].toDouble()>11 || dum_udl[1].toDouble()>11)
                {
                    errorbox.setText("Incorrect UDL data. DoF out of range.");
                    errorbox.exec();
                    check_data = false;
                }
                else
                {
                    udl_amnt_qtl.push_back(dum_udl[0].toDouble());
                    udl_var_qtl.push_back(dum_udl[1].toDouble());
                    udl_start_qtl.push_back(dum_udl[2].toDouble());
                    udl_elem_qtl.push_back(dum_udl[3].toDouble());
                }
            }
        }
    }



    // Check modal/dynamic data
    if (check_data)
    {
        if (analysis_label->text().compare("Static") && density==0)
        {
            errorbox.setText("Density not defined for "+analysis_label->text()+" analysis.");
            errorbox.exec();
            check_data = false;
        }
    }

    QVector<double> dyn_var_qtl;
    QStringList dyn_data = line_var_dyn->text().split(";");
    QVector<int> no_dofs_per_node_dyn;
    for (int i=0; i<dyn_data.size(); ++i)
    {
        QStringList dum_dyn = dyn_data[i].split(",");
        no_dofs_per_node_dyn.push_back(dum_dyn.size());
        for (int j=0; j<dum_dyn.size(); ++j)
        {
            dyn_var_qtl.push_back(dum_dyn[j].toDouble());
        }
    }

    // Ensure compatibility with number of nodes
    QStringList dyn_nodes = line_nodes_dyn->text().split(";");
    if (analysis_label->text().compare("Dynamic")==0)
    {
        if (check_data)
        {
            if (dyn_nodes.size()!=dyn_data.size())
            {
                errorbox.setText("Incompatible number of nodes and degrees of freedom for dynamic data.");
                errorbox.exec();
                check_data = false;
            }
        }

    }


    QVector<double> dyn_nodes_qtl;
    for (int i=0; i<no_dofs_per_node_dyn.size(); ++i)
    {
        for (int j=0; j<no_dofs_per_node_dyn[i]; ++j)
        {
            dyn_nodes_qtl.push_back(dyn_nodes[i].toDouble());
        }
    }

    // Check dynamic data file path exists
    if (analysis_label->text().compare("Dynamic")==0)
        if (check_data)
        {
            if (line_importdyn->text().isEmpty())
            {
                errorbox.setText("No dynamic data file supplied.");
                errorbox.exec();
                check_data = false;
            }
        }

    // Check dynamic output
    QStringList dyn_out = line_out_dyn->text().split(",");
    Eigen::Matrix<double,1,2> dynnode; dynnode.setZero(1,2);
    if (check_data)
    {
        if (analysis_label->text().compare("Dynamic")==0)
        {
            if (dyn_out.size()!=2)
            {
                errorbox.setText("Incorrect output data for dynamic analysis. Only one degree of freedom can be computed at a time.");
                errorbox.exec();
                check_data = false;
            }
            else
            {
                dynnode << dyn_out[0].toDouble(), dyn_out[1].toDouble();
            }
        }
    }



    Eigen::Matrix<double,Eigen::Dynamic,3> D_BC; D_BC.setZero(bc_var_qtl.size(),3);
    Eigen::MatrixXd pForce; pForce.setZero(point_loads_amnt_qtl.size(),2);
    Eigen::MatrixXd pForcePos; pForcePos.setZero(pos_x1_qtl.size(),3);
    Eigen::MatrixXd udl_force; udl_force.setZero(udl_amnt_qtl.size(),4);
    Eigen::Matrix<double,Eigen::Dynamic,2> dynP; dynP.setZero(dyn_nodes_qtl.size(),2);

    if (check_data)
    {
        // Convert matrices to Eigen (All Mapped Map)
        Eigen::Map<Eigen::VectorXd> bc_nodes(bc_nodes_qtl.data(),bc_nodes_qtl.size());
        Eigen::Map<Eigen::VectorXd> bc_var(bc_var_qtl.data(),bc_var_qtl.size());
        Eigen::Map<Eigen::VectorXd> bc_amnt(bc_amnt_qtl.data(),bc_amnt_qtl.size());
        D_BC.col(0) = bc_amnt; D_BC.col(1) = bc_nodes; D_BC.col(2) = bc_var;
        if (D_BC.isZero(1e-30))
        {
            errorbox.setText("Dirichlet boundary conditions are not defined.");
            errorbox.exec();
            check_data = false;
        }
        else if (D_BC.rows()<11)
        {
            errorbox.setText("Sufficient Dirichlet boundary conditions are not defined. Minimum 11 DoFs need to be fixed.");
            errorbox.exec();
            check_data = false;
        }

        Eigen::Map<Eigen::VectorXd> point_loads_amnt(point_loads_amnt_qtl.data(),point_loads_amnt_qtl.size());
        Eigen::Map<Eigen::VectorXd> point_loads_var(point_loads_var_qtl.data(),point_loads_var_qtl.size());
        pForce.col(0)=point_loads_amnt; pForce.col(1)=point_loads_var;

        Eigen::Map<Eigen::VectorXd> pos_x1(pos_x1_qtl.data(),pos_x1_qtl.size());
        Eigen::Map<Eigen::VectorXd> pos_x2(pos_x2_qtl.data(),pos_x2_qtl.size());
        Eigen::Map<Eigen::VectorXd> pos_x3(pos_x3_qtl.data(),pos_x3_qtl.size());
        pForcePos.col(0)=pos_x3; pForcePos.col(1)=pos_x1;  pForcePos.col(2)=pos_x2;

        Eigen::Map<Eigen::VectorXd> udl_amnt(udl_amnt_qtl.data(),udl_amnt_qtl.size());
        Eigen::Map<Eigen::VectorXd> udl_var(udl_var_qtl.data(),udl_var_qtl.size());
        Eigen::Map<Eigen::VectorXd> udl_start(udl_start_qtl.data(),udl_start_qtl.size());
        Eigen::Map<Eigen::VectorXd> udl_elem(udl_elem_qtl.data(),udl_elem_qtl.size());
        udl_force.col(0)=udl_amnt; udl_force.col(1)=udl_var; udl_force.col(2)=udl_start; udl_force.col(3)=udl_elem;

        Eigen::Map<Eigen::VectorXd> dyn_nodes_vec(dyn_nodes_qtl.data(),dyn_nodes_qtl.size());
        Eigen::Map<Eigen::VectorXd> dyn_var_vec(dyn_var_qtl.data(),dyn_var_qtl.size());
        dynP.col(0)=dyn_nodes_vec; dynP.col(1)=dyn_var_vec;

    }



    /** ---------------------------------------------------------------------------------------
     *  ------------------------    CALLING FEAPB MAIN ROUTINE     --------------------------*/
    if (check_data)
    {
        // Fill FEAPB's ReadData structure
        InputData.AIso = iso_label->text().toStdString();
        if (analysis_label->text().compare("Static")==0)
            InputData.Analysis = 1;
        else if (analysis_label->text().compare("Modal")==0)
            InputData.Analysis = 2;
        else if (analysis_label->text().compare("Dynamic")==0)
            InputData.Analysis = 3;
        InputData.Base = bases_label->text().toStdString();
        InputData.C = C_label->text().toInt();
        InputData.densi = density_label->text().toDouble();
        InputData.Die = Die;
        InputData.dim = 3;
        InputData.DInt = dynint_label->text().toStdString();
        InputData.Dirichlet_Boundary_Conditions = D_BC;
        InputData.DynFile = line_importdyn->text().toStdString();
        InputData.dynForce = dynP;
        InputData.dynNode = dynnode;
        InputData.Elast = Elast;
        InputData.IsoElast = isoElast;
        InputData.n = n_label->text().toInt();
        InputData.NInt = numint_label->text().toStdString();
        InputData.pForce = pForce;
        InputData.pForcePos = pForcePos;
        InputData.Piezo = Piezo;
        InputData.udl_Force = udl_force;
        InputData.x1 = x1_label->text().toDouble();
        InputData.x2 = x2_label->text().toDouble();
        InputData.x3 = x3_label->text().toDouble();
        InputData.shfac = shear_label->text().toDouble();
        InputData.nrows = 0; InputData.ncols = 0; InputData.nnz = 0;


        clock_t time = clock();
        // Define the problem
        problem = new DefineProblem(InputData);
        runAnalysis();
        // Total runtime
        time = clock()-time; runtime = ((double)time)/CLOCKS_PER_SEC;

        // Get result from main thread
        sol = future.result();
    }

    /** --------------------------------------------------------------------------------------*/


    // Activate post processing if analysis is done
    if (check_data)
    {
        plot_act->setEnabled(1);
        savetxt_act->setEnabled(1);
        genreport_act->setEnabled(1);
        no_update_modal_plot = -1;
        no_update_dynamic_plot = -1;
        non_bc_eigenmodes.resize(0);
        no_update_static_plot =-1;

        std::tie(conc,nodx,h)=FEAPB::ConcNodx(InputData.C,InputData.n,InputData.x3);
    }
}


void MainWindow::plotFEAPB()
{
    pwdg->setFixedSize(750,550);
    pwdg->setWindowTitle("FEAPB Plot");

    box_plot_static->setGeometry(QRect(70,500,200,20));
    box_plot_static->setToolTip("Choose a primary variable");

    line_fast_access_index->setGeometry(QRect(290,500,50,20));
    line_fast_access_index->setToolTip("Quick access to specific modes/steps");

    previous->setGeometry(QRect(20,550/2.0-60/2.0,40,60));
    previous->setToolTip("Previous");
    previous->setText("<");

    next->setGeometry(QRect(690,550/2.0-60/2.0,40,60));
    next->setText(">");
    next->setToolTip("Next");


    if (InputData.Analysis==1)
    {
        box_plot_static->setEnabled(1);
        line_fast_access_index->setDisabled(1);
        next->setDisabled(1); previous->setDisabled(1);

        if (no_update_static_plot ==-1)
        {
            QStringList variables;
            variables <<"Mechanical Displacement X1" << "Mechanical Dispalcement X2" << "Mechanical Dispalcement X3" << "Rotation X1" << "Rotation X2" << "Rotation X3" << "Electric Potential" << "Electric Gradient X1" << "Electric Gradient X2" << "Electric Hessian X1" << "Electric Hessian X2";
            box_plot_static->clear();
            box_plot_static->addItems(variables);
        }

        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(static_plot_index_label->text().toInt()+11*i);
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel(box_plot_static->currentText());
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        no_update_static_plot =1;
    }

    else if (InputData.Analysis==2)
    {
        box_plot_static->setDisabled(1);
        line_fast_access_index->setEnabled(1);
        next->setEnabled(1); previous->setEnabled(1);

        // Take out modes corresponding to boundary condition
        if (no_update_modal_plot==-1)
        {
            for (int i=0; i<sol.rows(); ++i)
                if (sol(i,0)!=1)
                    non_bc_eigenmodes.push_back(i);
        }

        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(6*i,non_bc_eigenmodes[modal_plot_index_label->text().toInt()]);
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel("Mode "+modal_plot_index_label->text());
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        no_update_modal_plot = 1;
    }

    else if (InputData.Analysis==3)
    {
        box_plot_static->setEnabled(1);
        line_fast_access_index->setEnabled(1);
        next->setEnabled(1); previous->setEnabled(1);

        if (no_update_dynamic_plot==-1)
        {
            box_plot_static->clear();
            QStringList variables;
            variables <<"Mechanical Displacement X1" << "Mechanical Dispalcement X2" << "Mechanical Dispalcement X3" << "Rotation X1" << "Rotation X2" << "Rotation X3";
            box_plot_static->addItems(variables);
        }

        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(dynamic_plot_var_index_label->text().toInt()+6*i,dynamic_plot_step_index_label->text().toInt());
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel(box_plot_static->currentText()+" (Step "+dynamic_plot_step_index_label->text()+")");
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        no_update_dynamic_plot = 1;
    }


    QPushButton *but1 = new QPushButton("OK",pwdg);
    but1->setGeometry(QRect(660,500,50,20));
    but1->setToolTip("Accept and close");
    connect(but1,SIGNAL(clicked()),pwdg,SLOT(accept()));

    but_save->setGeometry(QRect(550,500,100,20));
    but_save->setToolTip("Save figure");
    connect(but_save,SIGNAL(clicked()),pwdg,SLOT(accept()));

    plot->replot();

    connect(this,SIGNAL(destroyed()),pwdg,SLOT(close()));


    QPropertyAnimation *animation = new QPropertyAnimation(pwdg,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-550/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-750/2, fullScreenHeight/2-550/2, 1, 1));
    animation->start();


    pwdg->exec();
}

void MainWindow::exportFEAPB()
{
    QString outFileName = QFileDialog::getSaveFileName(this,tr("Save Results"), "",tr("FEAPB Results (*.txt);;All Files (*)"));
    if (InputData.Analysis==1)
    {
        QFile file(outFileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        for (int i=0; i<sol.rows(); ++i)
        {
            out << sol(i);
            out << "\n";
        }
        // optional, as QFile destructor will already do it:
        file.close();
    }
    else if (InputData.Analysis==2)
    {
        QFile file(outFileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        for (int i=0; i<sol.rows(); ++i)
        {
            if (sol(i,0)!=1)
            {
                out << sol(i,0);
                out << "\n";
            }
        }
        file.close();
    }
    else if (InputData.Analysis==3)
    {
        QFile file(outFileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        int nwant = 6*(InputData.dynNode(0,0)-1)+InputData.dynNode(0,1)-1;
        std::cout << nwant <<std::endl;
        for (int i=0; i<sol.cols(); ++i)
        {
            out << sol(nwant,i);
            out << "\n";
        }
        file.close();
    }
    infoLabel->setText("Results saved in text file: "+outFileName);
}

void MainWindow::reportFEAPB()
{
    QString repFileName = QFileDialog::getSaveFileName(this,tr("Save Results"), "",tr("FEAPB Report (*.pdf);;All Files (*)"));

    // Generate report
    QTextDocument report;
    QPrinter printer;
    printer.setOutputFileName(repFileName);
    printer.setOutputFormat(QPrinter::PdfFormat);

    QString outReportAnalysis; int numFullLU = (InputData.C+2)+1,numChol=0,numEigen=0;
    if (InputData.Analysis==1)
    { outReportAnalysis = "Static"; numChol = 0; numEigen=0;}
    else if (InputData.Analysis==2)
    { outReportAnalysis = "Modal"; numChol = 0; numEigen=1;}
    else if (InputData.Analysis==3)
    { outReportAnalysis = "Dynamic"; numChol = sol.cols()-1; numEigen=0;}

    report.setHtml("<h2><b><font color=#FFD300>FEA</FONT><FONT COLOR=#FD795B>PB</FONT>'s</b> InputData/Results</h2>"
                   "<br><div> Analysis: &nbsp; &nbsp; &nbsp; </div>"+outReportAnalysis+
                   "<div> Bases: &nbsp; &nbsp; &nbsp; </div>"+QString::fromStdString(InputData.Base)+
                   "<div> Order of Interpolation/Bases: &nbsp; &nbsp; &nbsp; </div>"+QString::number(InputData.C)+
                   "<div> Number of Elements: &nbsp; &nbsp; &nbsp; </div>"+QString::number(InputData.n)+
                   "<div> Numerical Integration: &nbsp; &nbsp; &nbsp; </div>"+QString::fromStdString(InputData.NInt)+
                   "<div> Material Class: &nbsp; &nbsp; &nbsp; </div>"+QString::fromStdString(InputData.AIso)+
                   "<br><div> Geometric Properties: </div></br>"
                   "<table border=''><tr><td> Height"+" = "+QString::number(InputData.x1)+", "+"<td> Width"+" = "+QString::number(InputData.x2)+", "+"<td> Length"+" = "+QString::number(InputData.x3)+"</table>"+
                   "<br><div> Elastic Isotropic Properties: </div></br>"
                   "<table border=''><tr><td> &mu;"+" = "+QString::number(InputData.IsoElast(0))+", "+"<td> &lambda;"+" = "+QString::number(InputData.IsoElast(1))+"</table>"+
                   "<br><div> Elastic Anisotropic Properties: </div></br>"
                   "<table border=''><tr><td> C<sub>33</sub>= "+" "+QString::number(InputData.Elast(2,2))+", "+"<td>C<sub>34</sub>= "+" "+QString::number(InputData.Elast(2,3))+", "+"<td>C<sub>35</sub>= "+" "+QString::number(InputData.Elast(2,4))+", "+
                   "<tr><td> C<sub>44</sub>= "+" "+QString::number(InputData.Elast(3,3))+", "+"<td> C<sub>45</sub>= "+" "+QString::number(InputData.Elast(3,4))+", "+"<td> C<sub>44</sub>= "+" "+QString::number(InputData.Elast(4,4))+"</table>"+
                   "<br><div> Material Density: </div>"+QString::number(InputData.densi)+
                   "<br><div> Dielectric Tensor: </div></br>"
                   "<table border=''><tr><td>"+QString::number(InputData.Die(0,0))+"<td>"+QString::number(InputData.Die(0,1))+"<td>"+QString::number(InputData.Die(0,2))+"<td>"+
                   "<tr><td>"+QString::number(InputData.Die(1,0))+"<td>"+QString::number(InputData.Die(1,1))+"<td>"+QString::number(InputData.Die(1,2))+
                   "<tr><td>"+QString::number(InputData.Die(2,0))+"<td>"+QString::number(InputData.Die(2,1))+"<td>"+QString::number(InputData.Die(2,2))+"</table>"+
                   "<br>"
                   "<br><div> Piezoelectric Tensor: </div></br>"
                   "<table border=''><tr><td>"+QString::number(InputData.Piezo(0,0))+"<td>"+QString::number(InputData.Piezo(0,1))+"<td>"+QString::number(InputData.Piezo(0,2))+"<td>"+QString::number(InputData.Piezo(0,3))+"<td>"+QString::number(InputData.Piezo(0,4))+"<td>"+QString::number(InputData.Piezo(0,5))+
                   "<tr><td>"+QString::number(InputData.Piezo(1,0))+"<td>"+QString::number(InputData.Piezo(1,1))+"<td>"+QString::number(InputData.Piezo(1,2))+"<td>"+QString::number(InputData.Piezo(1,3))+"<td>"+QString::number(InputData.Piezo(1,4))+"<td>"+QString::number(InputData.Piezo(1,5))+
                   "<tr><td>"+QString::number(InputData.Piezo(2,0))+"<td>"+QString::number(InputData.Piezo(2,1))+"<td>"+QString::number(InputData.Piezo(2,2))+"<td>"+QString::number(InputData.Piezo(2,3))+"<td>"+QString::number(InputData.Piezo(2,4))+"<td>"+QString::number(InputData.Piezo(2,5))+"</table>"+
                   "<br><div> Dirichlet Node(s): &nbsp; &nbsp; &nbsp; </div>"+line_nodes->text()+
                   "<div> Dirichlet DoF(s): &nbsp; &nbsp; &nbsp; </div>"+line_var->text()+
                   "<div> Dirichlet Imposed Value(s): &nbsp; &nbsp; &nbsp; </div>"+line_amnt->text()+
                   "<br><div> Point Loads: &nbsp; &nbsp; &nbsp; </div>"+line_point_loads->text()+
                   "<div> Point Load(s) Position(s): &nbsp; &nbsp; &nbsp; </div>"+line_point_pos->text()+
                   "<div> Uniformly Distributed Load(s): &nbsp; &nbsp; &nbsp; </div>"+line_udl->text()+
                   "<br><div> Dynamic Load Node(s): &nbsp; &nbsp; &nbsp; </div>"+line_nodes_dyn->text()+
                   "<div> Dynamic Load DoF(s): &nbsp; &nbsp; &nbsp; </div>"+line_var_dyn->text()+
                   "<div> Dynamic Output Node-DoF: &nbsp; &nbsp; &nbsp; </div>"+line_out_dyn->text()+
                   "<div> Dynamic Data File: &nbsp; &nbsp; &nbsp; </div>"+line_importdyn->text()+
                   "<br>"
                   "<br><div> Analysis Details: </div>"
                   "<div> Global Matrix/Matrices Size: &nbsp; &nbsp; &nbsp; </div>"+QString::number(InputData.nrows)+" x "+QString::number(InputData.ncols)+
                   "<div> Number of Non-zeros of Global Stiffness Matrix: &nbsp; &nbsp; &nbsp; </div>"+QString::number(InputData.nnz)+
                   "<div> Total Analysis Run-time: &nbsp; &nbsp; &nbsp; </div>"+QString::number(runtime)+"sec"
                   "<div> Number of Full Pivoted-LU Decomposition: &nbsp; &nbsp; &nbsp; </div>"+QString::number(numFullLU)+
                   "<div> Number of Cholesky Decomposition: &nbsp; &nbsp; &nbsp; </div>"+QString::number(numChol)+
                   "<div> Number of Eigen Decomposition: &nbsp; &nbsp; &nbsp; </div>"+QString::number(numEigen)+
                   "<br><br><br><br><div> Note: Boundary condition data may not correspond to the actual data at run-time if have you changed them after you run your analysis, as they are print-time variables. This exception only holds for boundary conditions/Loads. </div>"
                   );

    report.print(&printer);
    printer.newPage();
    infoLabel->setText("Report saved in: "+repFileName);
}


void MainWindow::about()
{
    MainDialog *abwdg = new MainDialog;
    abwdg->setWindowFlags(Qt::FramelessWindowHint);
    abwdg->setFixedSize(600,420);
    abwdg->setWindowTitle("About FEAPB");

    QLabel *lab1 = new QLabel(abwdg);
    QImage img(path+"/img/rsz_feapb_transparent.png");
    lab1->setGeometry(QRect(25,25,80,60));
    lab1->setPixmap(QPixmap::fromImage(img));
    lab1->show();

    QLabel *lab2 = new QLabel(abwdg);
    lab2->setGeometry(QRect(125,25,200,20));
    lab2->setText("<b><font size=5 'Lucida Sans Unicode' color=#FFD300>FEA</font><font size =5 color=#FF795B 'Lucida Sans Unicode' >PB</font><font size =5 color=#585858 'Lucida Sans Unicode'> 1.0</font></b>");
    lab2->show();

    QTextEdit *doc = new QTextEdit(abwdg);
    doc->setGeometry(QRect(125,65,410,280));
    doc->setText("<br><b><FONT COLOR=#FFD300>FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b><font color=#585858> (<i>hp</i>-Finite Element Analysis of Piezoelectric Beams) is a software "
                 " for solving linear static, modal and dynamic three-dimensional piezoelectric beam problems.</font>"
                 "<b><FONT COLOR=#FFD300> FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b><font color=#585858> is the outcome of an Erasmus Mundus project"
                 " on higher order FE for Piezoelectric Energy Harvesting Devices, carried out at the Civil & Computational Engineering Centre, Swansea University, Swansea, UK. <br>"
                 "<br></br><br></br>"
                 "&copy; Copyright 2013 <a href='mailto:romanpoya@gmail.com'><b>Roman Poya</b></a>, <a href='mailto:a.j.gil@swansea.ac.uk'><b>A.J. Gil</b></a>, <a href='mailto:p.d.ledger@swansea.ac.uk'><b>P.D. Ledger</b></a></br>"
                 "<br></br><br></br>"
                 "This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by "
                 "the Free Software Foundation, either version 3 of the License, or any later version."
                 "<br></br><br></br>"
                 "This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of "
                 "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details."
                 "<br></br><br></br>"
                 "You should have received a copy of the GNU General Public License along with this program.  If not, see <a href='http://www.gnu.org/licenses/'>http://www.gnu.org/licenses/</a>."
                 "<br></br><br></br>"
                 "<br><b><FONT COLOR=#FFD300> FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b><font color=#585858> has been developed in full compliance with ISO C++11 and the use of following open-source graphical/numerical linear algebra libraries is highly appreciated:</font></br><br></br>"
                            "<br><a href='http://eigen.tuxfamily.org/'><b>Eigen 3.2.0</b></a> </br>"
                            "<br><a href='http://qt-project.org/'><b>Qt 5.1.0</b></a> </br>"
                            "<br><a href='http://www.boost.org/'><b>Boost 1.5.4</b></a> </br>"
                            "<br><a href='http://www.qcustomplot.com/'><b>QCustomPlot 1.0.1</b></a> </br>"
                            "<br></br><br></br>"
                 "Contact details: &nbsp; <a href='mailto:romanpoya@gmail.com'> romanpoya@gmail.com</a>"
                 "<br> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  <a href='mailto:roman.poya@cimne.com'> roman.poya@cimne.com</a>"
                 );
    doc->setReadOnly(true);

    QPushButton *but1 = new QPushButton(tr("Ok"),abwdg);
    but1->setGeometry(QRect(510,370,50,20));
    but1->setToolTip("OK");
    connect(but1,SIGNAL(clicked()),abwdg,SLOT(accept()));


    QPropertyAnimation *animation = new QPropertyAnimation(abwdg,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-420/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-620/2, fullScreenHeight/2-420/2, 1, 1));
    animation->start();

    abwdg->exec();
}


void MainWindow::gendetails()
{
    MainDialog *genwdg = new MainDialog;
    genwdg->setWindowFlags(Qt::FramelessWindowHint);
    genwdg->setFixedSize(900,620);
    genwdg->setWindowTitle("Getting Started: FEAPB");

    QLabel *lab1 = new QLabel(genwdg);
    QImage img(path+"/img/rsz_feapb_transparent.png");
    lab1->setGeometry(QRect(25,25,80,60));
    lab1->setPixmap(QPixmap::fromImage(img));
    lab1->show();

    QLabel *lab2 = new QLabel(genwdg);
    lab2->setGeometry(QRect(125,25,200,20));
    lab2->setText("<b><font size=5 'Lucida Sans Unicode'>Getting Started</font></b>");
    lab2->show();

    QTextEdit *getStarted = new QTextEdit(genwdg);
    getStarted->setGeometry(QRect(125,65,710,490));
    getStarted->setText("<b><FONT COLOR=#FFD300> FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b> is designed to be intuitive and easy to use. To get started, first what you need to know is that <b><FONT COLOR=#FFD300> FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b> is a finite element program and hence there are elements, nodes and degrees of freedom. Each node has 11 degrees of freedom (DoFs) associated with it. These DoFs are arranged in a specific order and remembering the order is extremely important when applying boundary conditions."
                        " The order in which DoFs are arranged at any node is as follows:"
                        "<br></br>"
                        "<br>&nbsp; &nbsp; &nbsp; 1 - Mechanical Displacement X1 (Height Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 2 - Mechanical Displacement X2 (Width Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 3 - Mechanical Displacement X3 (Length Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 4 - Rotation X1 (Height Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 5 - Rotation X2 (Width Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 6 - Rotation X3 (Length Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 7 - Electric Potential Gradient X2 (Width Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 8 - Electric Potential Gradient X1 (Height Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 9 - Electric Potential (Scalar with no Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 10 - Electric Potential Hessian X2 (Width Direction)</br>"
                        "<br>&nbsp; &nbsp; &nbsp; 11 - Electric Potential Hessian X1 (Height Direction)</br>"
                        "<br></br>"
                        "<br>Majority of the input fields in <b><FONT COLOR=#FFD300> FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b> are self-explanatory, so here we only focus on showing how to apply boundary conditions."
                        "<br><br><b><font size=4>Applying Dirichlet Boundary Conditions: </font></b>"
                        "<br>To apply Dirichlet boundary conditions you need to fill three fields. </br>"
                        "<br><br><u>Dirichlet Nodes</u>: Fill in this field with node numbers you want to apply Dirichlet boundary conditions on. If there are more than one node on which boundary conditions are to be applied separate them by a semicolon (;).</br>"
                        "<br><br><u>Dirichlet Degrees of Freedom</u>: Fill in this field with degrees of freedom you want to apply Dirichlet boundary conditions on. If there are more than one DoF per node on which boundary conditions are to be applied separate them by a comma (,). If there are multiple nodes with multiple DoFs then separate the DoFs of a specific node with comma followed by a semicolon and the DoFs of other nodes and so on.</br>"
                        "<br><br><u>Dirichlet Imposed Values</u>: Fill in this field with values you want to impose on each Dirichlet DoF. The format of this field is similar to the Dirichlet DoF field i.e. there is one-to-one correspondence between the two.</br>"
                        "<br><br>For example applying Dirichlet boundary conditions on nodes 2,46 and 51, fixing (imposing a value of zero) all displacement and electric gradients in the first two nodes and imposing a value of (-1) on all rotations in third would look like this:"
                        "<br> Dirichlet Nodes: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; 2;51;46"
                        "<br> Dirichlet Degrees of Freedom: &nbsp; &nbsp; &nbsp; &nbsp; 1,2,3,7,8;4,5,6;1,2,3,7,8"
                        "<br> Dirichlet Imposed Values: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 0,0,0,0,0;-1,-1,-1;0,0,0,0,0"
                        "<br><br><br><b><font size=4>Applying Neumann Boundary Conditions (Point Loads): </font></b>"
                        "<br>Note that point loads also encompass moments, for example if you apply them rotational direction(s). We have also used a similar terminology for mechanical and electrical variables i.e. point loads can be electrical as well, so they can be applied on all 11 DoFs. To apply point loads you need to fill two fields. </br>"
                        "<br><br><u>Point Load(s)</u>: Fill in this field with the load value (amount) and the degree of freedom it is applied upon, separated by a comma. If there are more than one load separate them by a semicolon.</br>"
                        "<br><br><u>Point Load(s) Position(s)</u>: Fill in this field with the position of load in three-dimensional space separated by commas. The direction is X3,X1,X2 respectively. If there are more than one load separate their positions by semicolons. There is one-to-one correspondence between loads and their positions.</br>"
                        "<br><br>For example applying two point loads one with an amount of -12 on the direction of mechanical displacement X1 and other with a value of 0.4 on electric potential hessian X2 (second order moment), assuming the 3D position of loads to be in (320,45,18) and (120,23.7,7) respectively we would write:"
                        "<br> Point Load(s): &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; -12,1; 0.4,10"
                        "<br> Point Load(s) Position(s): &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp; 320,45,18;120,23.7,7"
                        "<br><br><br><b><font size=4>Applying Neumann Boundary Conditions (Uniformly Distributed Loads): </font></b>"
                        "<br>Uniformly distributed loads (UDL) can also be applied on all degrees of freedom except the axial directions (i.e. mechancial displacement X3, roation X3 and scalar electric potential), although they may not physically make sense. To apply UDLs you need to fill one field. </br>"
                        "<br><br><u>Uniformly Distributed Load(s)</u>: Fill in this field with the load value (amount), the degree of freedom it is applied upon, the starting element and number of elements it is applied upon all separated by commas. If there are more than one UDL separate them by semicolons.</br>"
                        "<br><br>For example applying UDLs of amounts -1,-2.5 on mechanical displacement X1 and X2 on the first and last 40 elements of a beam with 80 elements, respectively, would look like:"
                        "<br> Uniformly Distributed Load(s): &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; -2.5,2,41,40; -1,1,1,40"
                        "<br><br><br><b><font size=4>Applying Neumann Boundary Conditions (Dynamics): </font></b>"
                        "<br>For the time being, only point loads can be applied in dynamic scenarios. To apply dynamic point loads you need to fill four fields. </br>"
                        "<br><u>Import Dynamic Data</u>: You need to give the path to a file (any plain/non-rich document format) with accelration data. Check out DYNAMIC_DATA_ELCENTRO file which is supplied with <b><FONT COLOR=#FFD300> FEA</FONT><FONT COLOR=#FD795B>PB</FONT>'s all distribution.</b>"
                        "<br><br><u>Dynamic - Imposed Nodes</u>: Fill in this field with node number on which the above load is to be applied. It can be in any 11 direction. Separate each node by a semicolon."
                        "<br><br><u>Dynamic - Imposed DoFs</u>: Fill in this with DoFs corresponding to the nodes above. DoFs of a specific node are separated by comma those followed by a semicolon and then DoFs of other nodes."
                        "<br><br><u>Dynamic - Output Node-DoF</u>: This field is for the output data file that you may export. Specify only one node with a DoF for which the results are to exported."
                        "<br><br>For example applying three dynamic loads on node 20,30,40 all on rotational fields (hence moments), and considering the output file to export the X2 rotational result of node 30 would look like:"
                        "<br>Imposed Nodes: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 20,30,40"
                        "<br>Imposed DoFs: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 4,5,6;4,5,6;4,5,6"
                        "<br>Output Node-DoF: &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 30,5"
                        "<br><br><br><br>"
                        "<b><font size=4>To Remember: </font></b>"
                        "<br>1 - For the time being imposing non-zero dirichlet boundary conditions is not supported, that is you can only fix a degree of freedom (zero-value). This is mainly because of the computational cost as every Dirichlet boundary data requires resizing our large sparse global matrix, which we have avoided in <b><FONT COLOR=#FFD300>FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b>. Moreover non-zero boundary data requires indexing/accessing specific rows and columns which is not recommended for sparse matrices."
                        "<br>2 - While running modal or dynamic analysis make sure not to use a very fine mesh, as in such analyses we inevitably run into the situation of resizing our stiffness and mass matrices, as piezoelectric beams require an equivalent stiffness matrix. The way this is done is to again avoid resizing the matrices but create four more matrices and perform a full-pivoted LU decomposition to find the equivalent stiffness matrix. Moreover in a modal analysis we perform additional Eigen decomposition and in a dynamic scenario we perform Cholesky decompostion at each time step. Hence modal/dynamic scenarios are considerably costly."
                        "<br>3 - <b><FONT COLOR=#FFD300> FEA</FONT><FONT COLOR=#FD795B>PB</FONT></b> is designed with a good debugger and every time you do a mistake, it warns you. However there are some situation that the debugger cannot handle and the program will crash. A typical example would be out-of-memory issue."

                        "<br><br><br>"
                        "<b><font size=4>Additional Info: </font></b>"
                        "<br>For academic purposes, if this work is used to produce results in any shape or form please consider citing our work:"
                        "<br>I. Roman Poya, A.J.Gil and P.D.Ledger, (2013), <i>hp</i>-Finite elements for three-dimensional piezoelectric beams: Variational formulation, numerical implementation and closed-form solution, in preparation for submission."
                        "<br>II. Roman Poya, (2013), Higher order finite elements for energy harvesting piezoelectric beams, Master Thesis in Computational Mechanics, Swansea University, UK."
                        "<br>"
                        );
    getStarted->setReadOnly(true);


    QPropertyAnimation *animation = new QPropertyAnimation(genwdg,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, fullScreenHeight/2-600/2, 1, 1));
    animation->setEndValue(QRect(fullScreenWidth/2-800/2, fullScreenHeight/2-600/2, 1, 1));
    animation->start();


    QPushButton *but1 = new QPushButton(tr("Ok"),genwdg);
    but1->setGeometry(QRect(810,570,50,20));
    but1->setToolTip("OK");
    connect(but1,SIGNAL(clicked()),genwdg,SLOT(accept()));

    genwdg->exec();
}







// Sample problems
void MainWindow::run_sample_static()
{
    newFile();
    // Update corresponding labels used in solve member function
    x1_label->setText("0.1"); x2_label->setText("12"); x3_label->setText("60"); shear_label->setText("0.8");
    C_label->setText("2"); n_label->setText("200"); bases_label->setText("Lagrange ES");
    c33_label->setText("102830"); c34_label->setText("9920"); c44_label->setText("38610"); c55_label->setText("68810"); iso_label->setText("Anisotropic");
    e11_label->setText("3.921e-14"); e22_label->setText("3.982e-14"); e23_label->setText("8.6e-16"); e32_label->setText("8.6e-16"); e33_label->setText("4.042e-14");
    p11_Label->setText("1.71e-07"); p12_Label->setText("-1.52e-07"); p13_Label->setText("-1.87e-08"); p14_Label->setText("6.7e-08"); p25_Label->setText("1.08e-07"); p26_Label->setText("-9.5e-08"); p35_Label->setText("-7.61e-08"); p36_Label->setText("6.7e-08");
    bc_nodes_label->setText("1;601"); bc_var_label->setText("1,2,3,4,5,6,7,8,9,10,11; 7,8,9,10,11"); bc_amnt_label->setText("0,0,0,0,0,0,0,0,0,0,0; 0,0,0,0,0");
    point_loads_label->setText("-0.01,1;-5.35,2"); point_pos_label->setText("60,0,0;42.5,0,0"); udl_label->setText("-1e-05,1,1,100;-2.75,2,101,100");
    numint_label->setText("Gauss Lobatto"); analysis_label->setText("Static"); dynint_label->setText("Alpha");

    // Update fields
    line_x1->setText(x1_label->text()); line_x2->setText(x2_label->text()); line_x3->setText(x3_label->text()); line_shear->setText(shear_label->text());
    box_C->setValue(C_label->text().toInt()); line_n->setText(n_label->text()); box_bases->setCurrentText(bases_label->text());
    box_iso->setCurrentText(iso_label->text()); line_c33->setText(c33_label->text()); line_c34->setText(c34_label->text()); line_c44->setText(c44_label->text()); line_c55->setText(c55_label->text());
    line_e11->setText(e11_label->text()); line_e22->setText(e22_label->text()); line_e23->setText(e23_label->text()); line_e32->setText(e32_label->text()); line_e33->setText(e33_label->text());
    line_p11->setText(p11_Label->text());line_p12->setText(p12_Label->text());line_p13->setText(p13_Label->text());line_p14->setText(p14_Label->text());line_p25->setText(p25_Label->text()); line_p26->setText(p26_Label->text()); line_p35->setText(p35_Label->text()); line_p36->setText(p36_Label->text());
    line_nodes->setText(bc_nodes_label->text()); line_var->setText(bc_var_label->text()); line_amnt->setText(bc_amnt_label->text());
    line_point_loads->setText(point_loads_label->text()); line_point_pos->setText(point_pos_label->text()); line_udl->setText(udl_label->text());
    box_analysis->setCurrentText(analysis_label->text()); box_numint->setCurrentText(numint_label->text());

    line_mu->setEnabled(0);
    line_lambda->setEnabled(0);

    line_c33->setEnabled(1);
    line_c34->setEnabled(1);
    line_c35->setEnabled(1);
    line_c44->setEnabled(1);
    line_c45->setEnabled(1);
    line_c55->setEnabled(1);

    infolabel_x1->setText("<div> Height:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x1_label->text());
    infolabel_x2->setText("<div> Width: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x2_label->text());
    infolabel_x3->setText("<div> Length:&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x3_label->text());
    infolabel_shear->setText("<div> Shear Factor:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+shear_label->text());

    infoLabel_C->setText("<div> Order of Bases:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+C_label->text());
    infoLabel_n->setText("<div> Number of Elements:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  </div>"+n_label->text());
    infoLabel_bases->setText("<div> Basis Functions:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+bases_label->text());
    infoLabel_node_number->setText("<div> Number of Nodes:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+QString::number((C_label->text().toInt()+1)*n_label->text().toInt()+1));

    infoLabel_iso->setText("<div> Material Class: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+iso_label->text());

    infoLabel_analysis->setText("<div> Analysis Type: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+analysis_label->text());
    infoLabel_numint->setText("<div> Numerical Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+numint_label->text());
    infoLabel_dynint->setText("<div> Dynamic Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; NA</div>");

    solve();
    plotFEAPB();
}

void MainWindow::run_sample_modal()
{
    newFile();
    // Update corresponding labels used in solve member function
    x1_label->setText("1"); x2_label->setText("1"); x3_label->setText("100"); shear_label->setText("0.8333");
    C_label->setText("1"); n_label->setText("40"); bases_label->setText("Lagrange");
    mu_label->setText("23300"); lambda_label->setText("79400"); density_label->setText("7.5e-06"); iso_label->setText("Isotropic");
    e11_label->setText("1.505e-11"); e22_label->setText("1.505e-11"); e33_label->setText("1.3e-11");
    p15_Label->setText("1.7e-05"); p24_Label->setText("1.7e-05"); p31_Label->setText("-6.5e-06");  p32_Label->setText("-6.5e-06"); p33_Label->setText("2.33e-05");
    bc_nodes_label->setText("1"); bc_var_label->setText("1,2,3,4,5,6,7,8,9,10,11"); bc_amnt_label->setText("0,0,0,0,0,0,0,0,0,0,0");
    numint_label->setText("Gauss"); analysis_label->setText("Modal"); dynint_label->setText("Alpha");

    // Update fields
    line_x1->setText(x1_label->text()); line_x2->setText(x2_label->text()); line_x3->setText(x3_label->text()); line_shear->setText(shear_label->text());
    box_C->setValue(C_label->text().toInt()); line_n->setText(n_label->text()); box_bases->setCurrentText(bases_label->text());
    box_iso->setCurrentText(iso_label->text()); line_mu->setText(mu_label->text()); line_lambda->setText(lambda_label->text()); line_density->setText(density_label->text());
    line_e11->setText(e11_label->text()); line_e22->setText(e22_label->text()); line_e33->setText(e33_label->text());
    line_p15->setText(p15_Label->text()); line_p24->setText(p24_Label->text()); line_p31->setText(p31_Label->text()); line_p32->setText(p32_Label->text()); line_p33->setText(p33_Label->text());
    line_nodes->setText(bc_nodes_label->text()); line_var->setText(bc_var_label->text()); line_amnt->setText(bc_amnt_label->text());
    line_point_loads->setText(point_loads_label->text()); line_point_pos->setText(point_pos_label->text()); line_udl->setText(udl_label->text());
    box_analysis->setCurrentText(analysis_label->text()); box_numint->setCurrentText(numint_label->text());


    infolabel_x1->setText("<div> Height:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x1_label->text());
    infolabel_x2->setText("<div> Width: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x2_label->text());
    infolabel_x3->setText("<div> Length:&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x3_label->text());
    infolabel_shear->setText("<div> Shear Factor:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+shear_label->text());

    infoLabel_C->setText("<div> Order of Bases:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+C_label->text());
    infoLabel_n->setText("<div> Number of Elements:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  </div>"+n_label->text());
    infoLabel_bases->setText("<div> Basis Functions:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+bases_label->text());
    infoLabel_node_number->setText("<div> Number of Nodes:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+QString::number((C_label->text().toInt()+1)*n_label->text().toInt()+1));

    infoLabel_iso->setText("<div> Material Class: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+iso_label->text());

    infoLabel_analysis->setText("<div> Analysis Type: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+analysis_label->text());
    infoLabel_numint->setText("<div> Numerical Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+numint_label->text());
    infoLabel_dynint->setText("<div> Dynamic Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; NA</div>");

    solve();
    plotFEAPB();
}

void MainWindow::run_sample_dynamic()
{
    newFile();
    // Update corresponding labels used in solve member function
    x1_label->setText("1"); x2_label->setText("1"); x3_label->setText("100"); shear_label->setText("0.8333");
    C_label->setText("0"); n_label->setText("20"); bases_label->setText("Lagrange");
    mu_label->setText("23300"); lambda_label->setText("79400"); density_label->setText("7.5e-06"); iso_label->setText("Isotropic");
    e11_label->setText("1.505e-11"); e22_label->setText("1.505e-11"); e33_label->setText("1.3e-11");
    p15_Label->setText("1.7e-05"); p24_Label->setText("1.7e-05"); p31_Label->setText("-6.5e-06");  p32_Label->setText("-6.5e-06"); p33_Label->setText("2.33e-05");
    bc_nodes_label->setText("1"); bc_var_label->setText("1,2,3,4,5,6,7,8,9,10,11"); bc_amnt_label->setText("0,0,0,0,0,0,0,0,0,0,0");
    numint_label->setText("Gauss"); analysis_label->setText("Dynamic"); dynint_label->setText("Newmark's");

    // Update fields
    line_x1->setText(x1_label->text()); line_x2->setText(x2_label->text()); line_x3->setText(x3_label->text()); line_shear->setText(shear_label->text());
    box_C->setValue(C_label->text().toInt()); line_n->setText(n_label->text()); box_bases->setCurrentText(bases_label->text());
    box_iso->setCurrentText(iso_label->text()); line_mu->setText(mu_label->text()); line_lambda->setText(lambda_label->text()); line_density->setText(density_label->text());
    line_e11->setText(e11_label->text()); line_e22->setText(e22_label->text()); line_e33->setText(e33_label->text());
    line_p15->setText(p15_Label->text()); line_p24->setText(p24_Label->text()); line_p31->setText(p31_Label->text()); line_p32->setText(p32_Label->text()); line_p33->setText(p33_Label->text());
    line_nodes->setText(bc_nodes_label->text()); line_var->setText(bc_var_label->text()); line_amnt->setText(bc_amnt_label->text());
    line_point_loads->setText(point_loads_label->text()); line_point_pos->setText(point_pos_label->text()); line_udl->setText(udl_label->text());
    box_analysis->setCurrentText(analysis_label->text()); box_numint->setCurrentText(numint_label->text()); box_dynint->setCurrentText(dynint_label->text());

    line_nodes_dyn->setText("21");
    line_var_dyn->setText("1,2");
    line_out_dyn->setText("21,1");  // can be only for one dof

    box_dynint->setEnabled(1);
    but_importdyn->setEnabled(1);
    line_importdyn->setEnabled(1);
    line_nodes_dyn->setEnabled(1);
    line_var_dyn->setEnabled(1);
    line_out_dyn->setEnabled(1);

    line_importdyn->setText("DYNAMIC_DATA_ELCENTRO");


    infolabel_x1->setText("<div> Height:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x1_label->text());
    infolabel_x2->setText("<div> Width: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x2_label->text());
    infolabel_x3->setText("<div> Length:&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x3_label->text());
    infolabel_shear->setText("<div> Shear Factor:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+shear_label->text());

    infoLabel_C->setText("<div> Order of Bases:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+C_label->text());
    infoLabel_n->setText("<div> Number of Elements:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  </div>"+n_label->text());
    infoLabel_bases->setText("<div> Basis Functions:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+bases_label->text());
    infoLabel_node_number->setText("<div> Number of Nodes:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+QString::number((C_label->text().toInt()+1)*n_label->text().toInt()+1));

    infoLabel_iso->setText("<div> Material Class: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+iso_label->text());

    infoLabel_analysis->setText("<div> Analysis Type: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+analysis_label->text());
    infoLabel_numint->setText("<div> Numerical Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+numint_label->text());
    infoLabel_dynint->setText("<div> Dynamic Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Newmark's</div>");

    solve();
    plotFEAPB();
}


void MainWindow::updatePlot(int a)
{
    if (a==6)
        a=8;
    else if (a==8)
        a=6;
    else if (a==9)
        a=10;
    else if (a==10)
        a=9;

    // If static
    if (InputData.Analysis==1)
    {
        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;

        static_plot_index_label->setText(QString::number(a));
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(static_plot_index_label->text().toInt()+11*i);
            if (max_sol>y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol<y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel(box_plot_static->currentText());
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        plot->replot();
    }
    // If dynamic
    else if (InputData.Analysis==3)
    {
        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;

        dynamic_plot_var_index_label->setText(QString::number(a));
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(dynamic_plot_var_index_label->text().toInt()+6*i,dynamic_plot_step_index_label->text().toInt());
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel(box_plot_static->currentText()+" (Step "+dynamic_plot_step_index_label->text()+")");
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        plot->replot();
    }
}


void MainWindow::nextPlot()
{
    if (InputData.Analysis==2)
    {
        if (modal_plot_index_label->text().toInt()<non_bc_eigenmodes.size())
            modal_plot_index_label->setNum(modal_plot_index_label->text().toInt()+1);
        else
            modal_plot_index_label->setNum(1);

        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(6*i,non_bc_eigenmodes[modal_plot_index_label->text().toInt()]);
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel("Mode "+modal_plot_index_label->text());
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        plot->replot();
    }
    else if (InputData.Analysis==3)
    {
        if (dynamic_plot_step_index_label->text().toInt()<sol.cols()-1)
            dynamic_plot_step_index_label->setNum(dynamic_plot_step_index_label->text().toInt()+1);
        else
            dynamic_plot_step_index_label->setNum(1);

        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(dynamic_plot_var_index_label->text().toInt()+6*i,dynamic_plot_step_index_label->text().toInt());
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel(box_plot_static->currentText()+" (Step "+dynamic_plot_step_index_label->text()+")");
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        plot->replot();
    }
}

void MainWindow::previousPlot()
{
    if (InputData.Analysis==2)
    {
        if (modal_plot_index_label->text().toInt()>1)
            modal_plot_index_label->setNum(modal_plot_index_label->text().toInt()-1);
        else
            modal_plot_index_label->setNum(non_bc_eigenmodes.size());

        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(6*i,non_bc_eigenmodes[modal_plot_index_label->text().toInt()]);
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel("Mode "+modal_plot_index_label->text());
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        plot->replot();
    }
    else if (InputData.Analysis==3)
    {
        if (dynamic_plot_step_index_label->text().toInt()>1)
            dynamic_plot_step_index_label->setNum(dynamic_plot_step_index_label->text().toInt()-1);
        else
            dynamic_plot_step_index_label->setNum(sol.cols()-1);

        x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
        max_sol=0; min_sol=0;
        for (int i=0; i<nodx.rows(); ++i)
        {
            x_coordinate[i] = nodx(i,0); // beams alinged along the length
            y_coordinate[i] = sol(dynamic_plot_var_index_label->text().toInt()+6*i,dynamic_plot_step_index_label->text().toInt());
            if (max_sol<y_coordinate[i])
                max_sol=y_coordinate[i];
            if (min_sol>y_coordinate[i])
                min_sol=y_coordinate[i];
        }

        plot->addGraph();
        plot->setGeometry(QRect(70,50,610,430));
        plot->graph(0)->setData(x_coordinate,y_coordinate);
        plot->xAxis->setLabel("Beam's Length");
        plot->yAxis->setLabel(box_plot_static->currentText()+" (Step "+dynamic_plot_step_index_label->text()+")");
        plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
        plot->yAxis->setRange(min_sol, max_sol);

        plot->replot();
    }
}


void MainWindow::updateModalDynamicPlot(QString str)
{
    if (InputData.Analysis==2)
    {
        if (str.toInt()<non_bc_eigenmodes.size() && str.toInt()>=1)
        {
            modal_plot_index_label->setNum(str.toInt());

            x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
            max_sol=0; min_sol=0;
            for (int i=0; i<nodx.rows(); ++i)
            {
                x_coordinate[i] = nodx(i,0); // beams alinged along the length
                y_coordinate[i] = sol(6*i,non_bc_eigenmodes[modal_plot_index_label->text().toInt()]);
                if (max_sol<y_coordinate[i])
                    max_sol=y_coordinate[i];
                if (min_sol>y_coordinate[i])
                    min_sol=y_coordinate[i];
            }

            plot->addGraph();
            plot->setGeometry(QRect(70,50,610,430));
            plot->graph(0)->setData(x_coordinate,y_coordinate);
            plot->xAxis->setLabel("Beam's Length");
            plot->yAxis->setLabel("Mode "+modal_plot_index_label->text());
            plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
            plot->yAxis->setRange(min_sol, max_sol);

            plot->replot();
        }
    }
    else if (InputData.Analysis==3)
    {
        if (str.toInt()>=1 && str.toInt()<sol.cols()-1)
        {
            dynamic_plot_step_index_label->setNum(str.toInt());

            x_coordinate.fill(0,nodx.rows()); y_coordinate.fill(0,nodx.rows());
            max_sol=0; min_sol=0;
            for (int i=0; i<nodx.rows(); ++i)
            {
                x_coordinate[i] = nodx(i,0); // beams alinged along the length
                y_coordinate[i] = sol(dynamic_plot_var_index_label->text().toInt()+6*i,dynamic_plot_step_index_label->text().toInt());
                if (max_sol<y_coordinate[i])
                    max_sol=y_coordinate[i];
                if (min_sol>y_coordinate[i])
                    min_sol=y_coordinate[i];
            }

            plot->addGraph();
            plot->setGeometry(QRect(70,50,610,430));
            plot->graph(0)->setData(x_coordinate,y_coordinate);
            plot->xAxis->setLabel("Beam's Length");
            plot->yAxis->setLabel(box_plot_static->currentText()+" (Step "+dynamic_plot_step_index_label->text()+")");
            plot->xAxis->setRange(nodx.col(0).minCoeff(), nodx.col(0).maxCoeff());
            plot->yAxis->setRange(min_sol, max_sol);

            plot->replot();
        }
    }
}



















/**  Callback functions  **/

void MainWindow::setScreenWidth(QString w)
{
    this->resize(w.toInt(),height_label->text().toInt());
    width_label->setText(w);
}

void MainWindow::setScreenHeight(QString h)
{
    this->resize(width_label->text().toInt(),h.toInt());
    height_label->setText(h);
}


void MainWindow::geom_x1(QString x1)
{
    x1_label->setText(x1);
    infolabel_x1->setText("<div> Height:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x1);
    infoLabel->setText(x1);
}

void MainWindow::geom_x2(QString x2)
{
    x2_label->setText(x2);
    infolabel_x2->setText("<div> Width: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x2);
    infoLabel->setText(x2);
}

void MainWindow::geom_x3(QString x3)
{
    x3_label->setText(x3);
    infolabel_x3->setText("<div> Length:&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+x3);
    infoLabel->setText(x3);
}

void MainWindow::geom_shearfactor(QString kappa)
{
    shear_label->setText(kappa);
    infolabel_shear->setText("<div> Shear Factor:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+kappa);
    infoLabel->setText(kappa);
}


// material call back functions
void MainWindow::mat_density(QString density)
{
    density_label->setText(density);
    infoLabel->setText(density);
}

void MainWindow::mat_c33(QString c33)
{
    c33_label->setText(c33);
    infoLabel->setNum(c33.toDouble());
}

void MainWindow::mat_c34(QString c34)
{
    c34_label->setText(c34);
    infoLabel->setNum(c34.toDouble());
}

void MainWindow::mat_c35(QString c35)
{
    c35_label->setText(c35);
    infoLabel->setNum(c35.toDouble());
}

void MainWindow::mat_c44(QString c44)
{
    c44_label->setText(c44);
    infoLabel->setNum(c44.toDouble());
}

void MainWindow::mat_c45(QString c45)
{
    c45_label->setText(c45);
    infoLabel->setNum(c45.toDouble());
}

void MainWindow::mat_c55(QString c55)
{
    c55_label->setText(c55);
    infoLabel->setNum(c55.toDouble());
}

void MainWindow::mat_lambda(QString lambda)
{
    lambda_label->setText(lambda);
    infoLabel->setNum(lambda.toDouble());
}

void MainWindow::mat_mu(QString mu)
{
    mu_label->setText(mu);
    infoLabel->setNum(mu.toDouble());
}

void MainWindow::mat_iso(QString iso)
{
    iso_label->setText(iso);
    infoLabel_iso->setText("<div> Material Class: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+iso);
    infoLabel->setText(iso);
    if (iso.compare("Anisotropic")==0)
    {
        line_mu->setEnabled(0);
        line_lambda->setEnabled(0);

        line_c33->setEnabled(1);
        line_c34->setEnabled(1);
        line_c35->setEnabled(1);
        line_c44->setEnabled(1);
        line_c45->setEnabled(1);
        line_c55->setEnabled(1);
    }
    else
    {
        line_mu->setEnabled(1);
        line_lambda->setEnabled(1);

        line_c33->setEnabled(0);
        line_c34->setEnabled(0);
        line_c35->setEnabled(0);
        line_c44->setEnabled(0);
        line_c45->setEnabled(0);
        line_c55->setEnabled(0);
    }
}


void MainWindow::mat_e11(QString e)
{
    e11_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e12(QString e)
{
    e12_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e13(QString e)
{
    e13_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e21(QString e)
{
    e21_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e22(QString e)
{
    e22_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e23(QString e)
{
    e23_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e31(QString e)
{
    e31_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e32(QString e)
{
    e32_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_e33(QString e)
{
    e33_label->setText(e);
    infoLabel->setText(e);
}

void MainWindow::mat_p11(QString p)
{
    p11_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p12(QString p)
{
    p12_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p13(QString p)
{
    p13_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p14(QString p)
{
    p14_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p15(QString p)
{
    p15_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p16(QString p)
{
    p16_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p21(QString p)
{
    p21_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p22(QString p)
{
    p22_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p23(QString p)
{
    p23_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p24(QString p)
{
    p24_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p25(QString p)
{
    p25_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p26(QString p)
{
    p26_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p31(QString p)
{
    p31_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p32(QString p)
{
    p32_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p33(QString p)
{
    p33_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p34(QString p)
{
    p34_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p35(QString p)
{
    p35_Label->setText(p);
    infoLabel->setText(p);
}

void MainWindow::mat_p36(QString p)
{
    p36_Label->setText(p);
    infoLabel->setText(p);
}



void MainWindow::bc_nodes(QString bc)
{
    bc_nodes_label->setText(bc);
    infoLabel->setText(bc);
}

void MainWindow::bc_var(QString bc)
{
    bc_var_label->setText(bc);
    infoLabel->setText(bc);
}

void MainWindow::bc_amnt(QString bc)
{
    bc_amnt_label->setText(bc);
    infoLabel->setText(bc);
}


void MainWindow::point_loads(QString loads)
{
    point_loads_label->setText(loads);
    infoLabel->setText(loads);
}

void MainWindow::point_pos(QString pos)
{
    point_pos_label->setText(pos);
    infoLabel->setText(pos);
}

void MainWindow::udl(QString loads)
{
    udl_label->setText(loads);
    infoLabel->setText(loads);
}





void MainWindow::an_C(QString P)
{
    C_label->setText(P);
    infoLabel_C->setText("<div> Order of Bases:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+P);
    infoLabel->setText(P);
}

void MainWindow::an_n(QString nelem)
{
    n_label->setNum(nelem.toInt());
    infoLabel_n->setText("<div> Number of Elements:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  </div>"+nelem);
    infoLabel->setText(nelem);
}

void MainWindow::an_bases(QString bases)
{
    bases_label->setText(bases);
    infoLabel_bases->setText("<div> Basis Functions:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+bases);
    infoLabel->setText(bases);
}

void MainWindow::an_node_C(QString C)
{
    if (n_label->text().toInt()>0)
    {
        long nnode = (C.toInt()+1)*n_label->text().toInt()+1;
        infoLabel_node_number->setText("<div> Number of Nodes:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+QString::number(nnode));
    }
}

void MainWindow::an_node_n(QString n)
{
    if (C_label->text().toInt()>=0)
    {
        long nnode = (C_label->text().toInt()+1)*n.toInt()+1;
        infoLabel_node_number->setText("<div> Number of Nodes:&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  </div>"+QString::number(nnode));
    }
}

void MainWindow::an_numint(QString numint)
{
    numint_label->setText(numint);
    infoLabel_numint->setText("<div> Numerical Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+numint);
    infoLabel->setText(numint);
}

void MainWindow::an_type(QString analysis)
{
    analysis_label->setText(analysis);
    infoLabel_analysis->setText("<div> Analysis Type: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+analysis);
    infoLabel->setText(analysis);
    if (analysis.compare("Static")==0)
    {
        box_dynint->setEnabled(0);
        infoLabel_dynint->setText("<div> Dynamic Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; NA</div>");
        but_importdyn->setEnabled(0);
        line_importdyn->setEnabled(0);
        line_nodes_dyn->setEnabled(0);
        line_var_dyn->setEnabled(0);
        line_out_dyn->setEnabled(0);
    }
    else if (analysis.compare("Modal")==0)
    {
        box_dynint->setEnabled(0);
        infoLabel_dynint->setText("<div> Dynamic Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; NA</div>");
        but_importdyn->setEnabled(0);
        line_importdyn->setEnabled(0);
        line_nodes_dyn->setEnabled(0);
        line_var_dyn->setEnabled(0);
        line_out_dyn->setEnabled(0);
    }
    else if (analysis.compare("Dynamic")==0)
    {
        box_dynint->setEnabled(1);
        infoLabel_dynint->setText("<div> Dynamic Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Alpha</div>");
        but_importdyn->setEnabled(1);
        line_importdyn->setEnabled(1);
        line_nodes_dyn->setEnabled(1);
        line_var_dyn->setEnabled(1);
        line_out_dyn->setEnabled(1);
    }
}

void MainWindow::an_dynint(QString dynint)
{
    dynint_label->setText(dynint);
    infoLabel_dynint->setText("<div> Dynamic Integration: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; </div>"+dynint);
    infoLabel->setText(dynint);
}

void MainWindow::openFile()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open File..."),QString(), tr("Text Files (*.txt);;All Files (*)"));
    file_name.replace("/","\\");
    openFile_label->setText(file_name);
    line_importdyn->setText(file_name);
//    line_importdyn->setText(file_name.replace("/","\\"));
    infoLabel->setText(file_name);
    awdg->close();
}

void MainWindow::saveImage()
{
    QString picFileName = QFileDialog::getSaveFileName(this,tr("Save Figures"), "",tr("FEAPB Images (*.png);;FEAPB Images (*.jpg);;All Files (*)"));
    plot->savePng(picFileName,610,430);
    pwdg->close();
    infoLabel->setText("Image saved in: "+picFileName);
}





































//void MainWindow::keyPressEvent(QKeyEvent *event)
//{
//    if (event->key()==Qt::Key_Left)
//        std::cout << "Left!" << std::endl;
//    else if (event->key()==Qt::Key_Right)
//        std::cout << "Right!" << std::endl;
//}


//void MainWindow::mouseDoubleClickEvent(QMouseEvent *e) {
//  QWidget::mouseDoubleClickEvent(e);
//  if(isFullScreen()) {
////     this->setWindowState(Qt::WindowMinimized);
//      this->resize(920, 640);
//      setCentralWidget(widget);
////      this->update();
//  } else {
//     this->setWindowState(Qt::WindowFullScreen);
//  }
//}


/** .......................Defining actions..................*/

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Erases all input data"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    wndResolutionAct = new QAction(tr("Adjust Screen"),this);
    wndResolutionAct->setShortcut(tr("Ctrl+Shift+A"));
    wndResolutionAct->setStatusTip(tr("Adjust Screen Resolution"));
    connect(wndResolutionAct,SIGNAL(triggered()),this,SLOT(wndResolution()));

    fullScreenAct->setShortcut(tr("Ctrl+Shift+F"));
    fullScreenAct->setStatusTip(tr("Put window in full screen mode"));

    exitAct = new QAction(tr("E&xit"), this);
//    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit FEAPB"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About FEAPB"), this);
    aboutAct->setShortcut(tr("Ctrl+Shift+H"));
    aboutAct->setStatusTip(tr("General information about FEAPB"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));


    // FEAPB menu defintion
    geoAct = new QAction(tr("Set Geometry"),this);
    geoAct->setShortcut(tr("Ctrl+G"));
    geoAct->setStatusTip(tr("Specify problem geometry"));
    connect(geoAct,SIGNAL(triggered()),this,SLOT(geom()));

    meshAct = new QAction(tr("Discretise Geometry"),this);
    meshAct->setShortcut(tr("Ctrl+D"));
    meshAct->setStatusTip(tr("Specify mesh for the geometry"));
    connect(meshAct,SIGNAL(triggered()),this,SLOT(mesh()));

    matmAct = new QAction(tr("&Mechanical"), this);
    matmAct->setShortcut(tr("Ctrl+M"));
    matmAct->setStatusTip(tr("Set mechanical properties"));
    connect(matmAct, SIGNAL(triggered()), this, SLOT(matm()));

    mateAct = new QAction(tr("&Electrical"), this);
    mateAct->setShortcut(tr("Ctrl+E"));
    mateAct->setStatusTip(tr("Set electrical properties"));
    connect(mateAct, SIGNAL(triggered()), this, SLOT(mate()));

    bceAct = new QAction(tr("&Loads (Neumann)"), this);
    bceAct->setShortcut(tr("Ctrl+L"));
    bceAct->setStatusTip(tr("Set Neumann boundary conditions"));
    connect(bceAct, SIGNAL(triggered()), this, SLOT(bc_neumann()));

    bcmAct = new QAction(tr("&Fixities (Dirichlet)"), this);
    bcmAct->setShortcut(tr("Ctrl+F"));
    bcmAct->setStatusTip(tr("Set Dirichlet boundary conditions"));
    connect(bcmAct, SIGNAL(triggered()), this, SLOT(bc_dirichlet()));

    an_opts_act = new QAction(tr("&Analysis Options"),this);
    an_opts_act->setShortcut(tr("Ctrl+A"));
    an_opts_act->setStatusTip(tr("Specify analysis options"));
    connect(an_opts_act, SIGNAL(triggered()), this, SLOT(an_opts()));

    solve_act = new QAction(tr("&Run Analysis"),this);
    solve_act->setShortcut(tr("Ctrl+R"));
    solve_act->setStatusTip(tr("Click to solve your problem"));
    connect(solve_act, SIGNAL(triggered()), this, SLOT(solve()));

    plot_act = new QAction(tr("&Plot Results"),this);
    plot_act->setShortcut(tr("Ctrl+P"));
    plot_act->setStatusTip(tr("Plot results"));
    connect(plot_act, SIGNAL(triggered()), this, SLOT(plotFEAPB()));
    plot_act->setEnabled(0); // disabled by default until analysis is performed

    savetxt_act = new QAction(tr("&Save Results"),this);
    savetxt_act->setShortcut(tr("Ctrl+S"));
    savetxt_act->setStatusTip(tr("Exports results to a text file"));
    connect(savetxt_act, SIGNAL(triggered()), this, SLOT(exportFEAPB()));
    savetxt_act->setEnabled(0); // disabled by default until analysis is performed

    genreport_act = new QAction(tr("&Create Report"),this);
    genreport_act->setShortcut(tr("Ctrl+Shift+C"));
    genreport_act->setStatusTip(tr("Creates a short report from your analysis in a portable document format"));
    connect(genreport_act, SIGNAL(triggered()), this, SLOT(reportFEAPB()));
    genreport_act->setEnabled(0); // disabled by default until analysis is performed

    gendetailsAct = new QAction(tr("&Getting Started"),this);
    gendetailsAct->setShortcut(tr("Ctrl+H"));
    gendetailsAct->setStatusTip(tr("Quick start guide"));
    connect(gendetailsAct, SIGNAL(triggered()), this, SLOT(gendetails()));


    runStaticAct = new QAction(tr("&Static Example"),this);
    runStaticAct->setShortcut(tr("Ctrl+Shift+S"));
    runStaticAct->setStatusTip(tr("Run a sample static analysis"));
    connect(runStaticAct, SIGNAL(triggered()), this, SLOT(run_sample_static()));

    runModalAct = new QAction(tr("&Modal Example"),this);
    runModalAct->setShortcut(tr("Ctrl+Shift+M"));
    runModalAct->setStatusTip(tr("Run a sample modal analysis"));
    connect(runModalAct, SIGNAL(triggered()), this, SLOT(run_sample_modal()));

    runDynamicAct = new QAction(tr("&Dynamic Example"),this);
    runDynamicAct->setShortcut(tr("Ctrl+Shift+D"));
    runDynamicAct->setStatusTip(tr("Run a sample dynamic analysis"));
    connect(runDynamicAct, SIGNAL(triggered()), this, SLOT(run_sample_dynamic()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(wndResolutionAct);
    fileMenu->addAction(fullScreenAct);
    fileMenu->addSeparator();
    fileMenu->addAction(savetxt_act);
    fileMenu->addAction(genreport_act);
    fileMenu->addSeparator();
    fileMenu->addAction(gendetailsAct);
    fileMenu->addAction(aboutAct);
    fileMenu->addAction(exitAct);
    fileMenu->setStatusTip("File menu options");
//    fileMenu->setToolTip("File menu options");

    //FEAPB menus
    geomenu = menuBar()->addMenu(tr("&Geometrical Model"));
    geomenu->addAction(geoAct);
    geomenu->addAction(meshAct);
    geomenu->setStatusTip("Lets you specify the geometry of the problem");

    matmenu = menuBar()->addMenu(tr("&Material Properties"));
    matmenu->addAction(matmAct);
    matmenu->addAction(mateAct);
    matmenu->setStatusTip("Lets you specify material properties");

    bcmenu = menuBar()->addMenu(tr("&Boundary Conditions"));
    bcmenu->addAction(bcmAct);
    bcmenu->addAction(bceAct);
    bcmenu->setStatusTip("Lets you specify boundary conditions");

    analysemenu = menuBar()->addMenu("&Analyse");
    analysemenu->addAction(an_opts_act);
    analysemenu->addSeparator();
    analysemenu->addAction(solve_act);
    analysemenu->setStatusTip("Lets you control your analysis process");

    postmenu = menuBar()->addMenu("&Post Process");
    postmenu->addAction(plot_act);
    postmenu->addAction(savetxt_act);
    postmenu->addAction(genreport_act);
    postmenu->setStatusTip("Post process your results");

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(gendetailsAct);
    helpMenu->addSeparator();
    runSampleMenu = helpMenu->addMenu("Run Examples");
    runSampleMenu->addAction(runStaticAct);
    runSampleMenu->addAction(runModalAct);
    runSampleMenu->addAction(runDynamicAct);
    helpMenu->addAction(aboutAct);
    helpMenu->setStatusTip("Help and general guideline about FEAPB");
}






// Subclasses
MainDialog::MainDialog(QWidget *parent) : QDialog(parent)
{
}

MainLabel::MainLabel(QWidget *parent) : QLabel(parent)
{
    this->setStyleSheet("QLabel {min-height: 1.4em; font: 1em; color: #585858; border-style: outset; border-radius: 10px; border-width: 1.4px; border-color: #b0b0b0; border-top-left-radius: 15px; border-bottom-left-radius: 0px; border-bottom-right-radius: 15px; border-top-right-radius: 0px; background-color: #f8f8f8; font-weight: bold; selection-background-color: #585858; selection-color: white;}"
);
}

LabelInfo::LabelInfo(QWidget *parent) : QLabel(parent)
{
    this->setStyleSheet("QLabel {min-height: 1.4em; font: 1em; color: #585858; border-style: inset; border-radius: 10px; border-width: 1px; border-color:  #a0a0a0; border-top-left-radius: 8px; border-bottom-left-radius: 0px; border-bottom-right-radius: 8px; border-top-right-radius: 0px; font-weight: bold; selection-background-color: #585858; selection-color: white;}"
);
}

NextButton::NextButton(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet("QPushButton {min-height: 2em; font: 1em; margin: 0px 1px 0 1px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #e8e8e8); color: #585858; border-style: outset; border-radius: 6px; border-width: 1.25px; border-top-left-radius: 0px; border-bottom-left-radius: 0px; border-bottom-right-radius: 10px; border-top-right-radius: 10px; border-color: #A8A8A8; font-size: 9pt; font-weight: bold;}"
                        "QPushButton:pressed {border-style: inset; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e8e8e8, stop: 1 #ffffff);}"
                        "QPushButton::disabled {border-style: solid; color: darkgray; border-color: darkgray;}"
);
}

PreviousButton::PreviousButton(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet("QPushButton {min-height: 2em; font: 1em; margin: 0px 1px 0 1px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #e8e8e8); color: #585858; border-style: outset; border-radius: 6px; border-width: 1.25px; border-top-left-radius: 10px; border-bottom-left-radius: 10px; border-bottom-right-radius: 0px; border-top-right-radius: 0px; border-color: #A8A8A8; font-size: 9pt; font-weight: bold;}"
                        "QPushButton:pressed {border-style: inset; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e8e8e8, stop: 1 #ffffff);}"
                        "QPushButton::disabled {border-style: solid; color: darkgray; border-color: darkgray;}"
);
}





// Separate Thread
void MainWindow::analysisFinished()
{
    infoLabel->setText("Done...");
}
void MainWindow::runAnalysis()
{
    infoLabel->setText("Busy!");
    // Start the computation
     future = QtConcurrent::run(problem, &DefineProblem::Solve);
     FutureWatcher.setFuture(future);

     progress->setWindowFlags(Qt::FramelessWindowHint);
//     progress->setMinimumSize(300,50);
     progress->setFixedSize(300,50);
     progress->setMinimum(0);
     progress->setMaximum(0);
     progress->setWindowModality(Qt::WindowModal);
     progress->exec();
}
