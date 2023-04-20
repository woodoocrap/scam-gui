#ifndef SCAM_GUI_CANVAS_AREA_HEADER
#define SCAM_GUI_CANVAS_AREA_HEADER

#include "QLabel"
#include "QWidget"
#include "QLineEdit"
#include "QDateEdit"
#include "QPushButton"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QGridLayout"
#include "QScrollArea"

#include "canvas.hpp"
#include "colorpicker.hpp"


class CanvasArea : public QWidget {

   QScrollArea scrollArea;

   Canvas canvas;
   ColorPicker colorPicker;

   QLabel dateLabel;
   QLabel weeksLabel;
   QDateEdit dateInput;
   QLineEdit weeksInput;
   QPushButton setDateButton;
   QPushButton setWeeksButton;

   QVBoxLayout vbox;
   QGridLayout grid;
   QHBoxLayout canvasRow;

   void setupLayout();
   void setupStyles();

 private slots:
   void weekCountUpdated();
   void colorUpdated();
   void dateUpdated();

 public:
   explicit CanvasArea(QWidget * parent = nullptr);
   
   const std::vector<int> &getDays() const;
   QDate getDate() const;
};

#endif
