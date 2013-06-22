#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItem>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->spinHauteur,SIGNAL(valueChanged(int)),this,SLOT(init()));
    connect(ui->spinLongueur,SIGNAL(valueChanged(int)),this,SLOT(init()));
    connect(ui->codeButton,SIGNAL(clicked()), this, SLOT(getCode()));
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    int longueur = ui->spinHauteur->value();
    int hauteur = ui->spinLongueur->value();
 /*
  * Fill a new table with a model
  */
    QStandardItemModel* tableModel = new QStandardItemModel();
    for(int i=0; i<hauteur; i++){
      for(int j=0; j<longueur; j++){
        tableModel->setItem(i, j, new QStandardItem(""));
      }
    }
    ui->tableau->setModel(tableModel); // add model to tableau item

}


void MainWindow::getCode(){
    int longueur = ui->spinHauteur->value();
    int hauteur = ui->spinLongueur->value();
 /*
  * get Everything
  */
    QString matrix[hauteur][longueur];
    for(int i=0; i<hauteur; i++){
      for(int j=0; j<longueur; j++){
          matrix[i][j] = ui->tableau->model()->data(ui->tableau->model()->index(i,j)).toString();
      }
    }

    /*
     * push everything
     */
    ui->matrixOutput->insertPlainText("\\begin{pmatrix}\n");
    for(int i=0; i<hauteur; i++){
      for(int j=0; j<longueur; j++){
          QString seperator;
          if (j!=longueur-1)
              seperator = "&";
          else
              seperator = "\\\\\n";
          ui->matrixOutput->insertPlainText(" " +matrix[i][j]+" "+seperator);
      }
    }
}

