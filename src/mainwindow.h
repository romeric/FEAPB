
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
//#include <QProgressDialog>
#include "QCustomPlot/qcustomplot.h"

#include"DefineProblem.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QLineEdit;
class QProgressDialog;



// Subclass QDialog
class MainDialog: public QDialog
{
    Q_OBJECT
public:
    explicit MainDialog(QWidget *parent=0);
//protected:
//    // Drag window
//    void mouseMoveEvent(QMouseEvent *e)
//    {
//        move(QCursor::pos());
//    }
};


//Subclass QLabel
class MainLabel: public QLabel
{
    Q_OBJECT
public:
    explicit MainLabel(QWidget *parent=0);
};

class LabelInfo: public QLabel
{
    Q_OBJECT
public:
    explicit LabelInfo(QWidget *parent=0);
};


//Subclass QPushButton
class NextButton: public QPushButton
{
    Q_OBJECT
public:
    explicit NextButton(QWidget *parent=0);
};
class PreviousButton: public QPushButton
{
    Q_OBJECT
public:
    explicit PreviousButton(QWidget *parent=0);
};


// Subclass QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QWidget *widget;

protected:
//    void mouseDoubleClickEvent(QMouseEvent *e);
//    void contextMenuEvent(QContextMenuEvent *event);
//    void keyPressEvent(QKeyEvent *event);

    // Drag window
    void mouseMoveEvent(QMouseEvent *e)
    {
        move(QCursor::pos());
    }

private slots:
    void newFile();
    void fullScreen();
    void wndResolution();
    void about();

    // FEAPB actions within its menus
    void geom();
    void mesh();
    void matm();
    void mate();
    void bc_dirichlet();
    void bc_neumann();
    void an_opts();
    void solve();
    void plotFEAPB();
    void exportFEAPB();
    void reportFEAPB();
    void gendetails();

    void run_sample_static();
    void run_sample_dynamic();
    void run_sample_modal();


    void testSlot(bool blurred){
         QGraphicsBlurEffect *effect = new QGraphicsBlurEffect(this) ;
         setGraphicsEffect(blurred? effect : 0);}

public slots:
    void setScreenWidth(QString w);
    void setScreenHeight(QString h);

    void geom_x1(QString x1);
    void geom_x2(QString x2);
    void geom_x3(QString x3);
    void geom_shearfactor(QString kappa);

    void an_C(QString P);
    void an_n(QString nelem);
    void an_bases(QString bases);
    void an_node_C(QString C);
    void an_node_n(QString n);

    void mat_density(QString density);
    void mat_mu(QString mu);
    void mat_lambda(QString lambda);
    void mat_c33(QString c33);
    void mat_c34(QString c34);
    void mat_c35(QString c35);
    void mat_c44(QString c44);
    void mat_c45(QString c45);
    void mat_c55(QString c55);
    void mat_iso(QString iso);

    void mat_e11(QString e);
    void mat_e12(QString e);
    void mat_e13(QString e);
    void mat_e21(QString e);
    void mat_e22(QString e);
    void mat_e23(QString e);
    void mat_e31(QString e);
    void mat_e32(QString e);
    void mat_e33(QString e);
    void mat_p11(QString p);
    void mat_p12(QString p);
    void mat_p13(QString p);
    void mat_p14(QString p);
    void mat_p15(QString p);
    void mat_p16(QString p);
    void mat_p21(QString p);
    void mat_p22(QString p);
    void mat_p23(QString p);
    void mat_p24(QString p);
    void mat_p25(QString p);
    void mat_p26(QString p);
    void mat_p31(QString p);
    void mat_p32(QString p);
    void mat_p33(QString p);
    void mat_p34(QString p);
    void mat_p35(QString p);
    void mat_p36(QString p);

    void bc_nodes(QString bc);
    void bc_var(QString bc);
    void bc_amnt(QString bc);

    void point_loads(QString loads);
    void point_pos(QString pos);
    void udl(QString loads);

    void an_type(QString analysis);
    void an_numint(QString numint);
    void an_dynint(QString dynint);
    void openFile();

    void updatePlot(int a);
    void nextPlot();
    void previousPlot();
    void updateModalDynamicPlot(QString str);

    void saveImage();


    void analysisFinished();
    void runAnalysis();


signals:
    void FEAPB_close();


private:
    void createActions();
    void createMenus();

    QMenu *fileMenu, *helpMenu, *runSampleMenu;
    QAction *newAct, *fullScreenAct, *wndResolutionAct, *exitAct, *aboutAct,*gendetailsAct, *runStaticAct,*runModalAct,*runDynamicAct;
    QLabel *height_label, *width_label,*openFile_label;
    LabelInfo *infoLabel;
    QLabel *infoLabel_C, *infoLabel_n, *infoLabel_bases, *infoLabel_analysis, *infoLabel_dynint, *infoLabel_numint, *infoLabel_iso, *infoLabel_node_number;
    QLabel *C_label, *n_label, *analysis_label, *numint_label, *bases_label, *dynint_label;
    QLabel *x1_label, *x2_label, *x3_label, *shear_label, *infolabel_x1, *infolabel_x2, *infolabel_x3, *infolabel_shear, *infolabel_geom;
    QLabel *density_label, *mu_label, *lambda_label, *c33_label, *c34_label, *c35_label, *c44_label, *c45_label, *c55_label, *iso_label;
    QLabel *e11_label,*e12_label,*e13_label,*e21_label,*e22_label,*e23_label,*e31_label,*e32_label,*e33_label;
    QLabel *p11_Label,*p12_Label,*p13_Label,*p14_Label,*p15_Label,*p16_Label,*p21_Label,*p22_Label,*p23_Label,*p24_Label,*p25_Label,*p26_Label,*p31_Label,*p32_Label,*p33_Label,*p34_Label,*p35_Label,*p36_Label;
    QLabel *bc_nodes_label,*bc_var_label,*bc_amnt_label;
    QLabel *point_loads_label, *point_pos_label,*udl_label;

    // FEAPB menus
    QMenu *geomenu;
    QAction *geoAct;
    QAction *meshAct;

    QMenu *matmenu;
    QAction *mateAct, *matmAct;

    QMenu *bcmenu;
    QAction *bceAct, *bcmAct;

    QMenu *analysemenu;
    QAction *an_opts_act, *check_an, *solve_act;

    QMenu *postmenu;
    QAction *plot_act, *savetxt_act, *genreport_act;


    // FEAPB dialog boxes
    MainDialog *wndDialog;
    QLineEdit *line_screen_height, *line_screen_width;
    int fullScreenWidth, fullScreenHeight;

    MainDialog *gwdg;
    QLineEdit *line_x1, *line_x2, *line_x3, *line_shear;

    MainDialog *mwdg;
    QSpinBox *box_C;
    QLineEdit *line_n;
    QComboBox *box_bases;

    MainDialog *wdg_matm;
    QComboBox *box_iso;
    QLineEdit *line_density,*line_lambda,*line_mu,*line_c33,*line_c34,*line_c35,*line_c44,*line_c45,*line_c55;

    MainDialog *wdg_mate;
    QLineEdit *line_e11,*line_e12,*line_e13,*line_e21,*line_e22,*line_e23,*line_e31,*line_e32,*line_e33;
    QLineEdit *line_p11,*line_p12,*line_p13,*line_p14,*line_p15,*line_p16,*line_p21,*line_p22,*line_p23,*line_p24,*line_p25,*line_p26,*line_p31,*line_p32,*line_p33,*line_p34,*line_p35,*line_p36;

    MainDialog *wdg_bc_d;
    QLineEdit *line_nodes, *line_var, *line_amnt;

    MainDialog *wdg_bc_n;
    QLineEdit *line_point_loads, *line_point_pos,*line_udl;

    MainDialog *awdg;
    QComboBox *box_analysis, *box_dynint, *box_numint;
    QLineEdit *line_importdyn, *line_nodes_dyn, *line_var_dyn, *line_out_dyn;
    QPushButton *but_importdyn;


    FEAPB::DefineProblem *problem;
    Eigen::MatrixXd sol;
    FEAPB::ReadData InputData;
    Eigen::MatrixXi conc; Eigen::MatrixXd nodx;
    double h;

    MainDialog *pwdg;
    QCustomPlot *plot;
    QComboBox *box_plot_static;
    QVector<double> x_coordinate,y_coordinate;
    double min_sol,max_sol;
    QVector<double> non_bc_eigenmodes;
    NextButton *next;
    PreviousButton *previous;
    QLabel *static_plot_index_label,*modal_plot_index_label, *dynamic_plot_step_index_label,*dynamic_plot_var_index_label;
    int no_update_modal_plot, no_update_dynamic_plot, no_update_static_plot;
    QLineEdit *line_fast_access_index;

    QPushButton *but_save;


    QProgressDialog *progress;
    QFutureWatcher<void> FutureWatcher;
    QFuture<Eigen::MatrixXd> future;
    double runtime;

    QString path;
};

#endif
