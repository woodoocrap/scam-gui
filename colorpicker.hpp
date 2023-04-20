#ifndef SCAM_GUI_COLOR_PICKER_HEADER
#define SCAM_GUI_COLOR_PICKER_HEADER

#include "QLabel"
#include "QWidget"
#include "QVBoxLayout"

#include "intensity.hpp"

class ColorCell : public QFrame {

   Q_OBJECT

   Intensity level;

 protected:
   void mousePressEvent(QMouseEvent * event);

 signals:
   void clicked();

 public:
   ColorCell(Intensity intensity, QWidget * parent = nullptr);
   
   Intensity getIntensity() const;

   void paintUnselected();
   void paintSelected();
};


class ColorPicker : public QWidget {
   
   Q_OBJECT

   QVBoxLayout vbox;
   ColorCell * selectedCell = nullptr;

 private slots:
   void cellSelected();

 signals:
   void colorChanged();
 
 public:
   explicit ColorPicker(QWidget * parent = nullptr);
   Intensity getIntensity() const;

};

#endif
