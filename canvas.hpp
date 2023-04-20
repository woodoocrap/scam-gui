#ifndef SCAM_GUI_CANVAS_HEADER
#define SCAM_GUI_CANVAS_HEADER

#include "vector"

#include "QDate"
#include "QWidget"
#include "QPainter"

#include "QHBoxLayout"
#include "QMouseEvent"

#include "intensity.hpp"

class Canvas : public QWidget {
   
   QDate date;

   int week_offset;
   std::vector<int> days;

   const int padding = 4;
   const int cell_size = 30;
   const int padded_size = padding + cell_size;

   Intensity intensity_level = None;

   void drawGrid(QPainter * painter);
   void fillDay(QPainter * painter, int day);

 protected:
   void mousePressEvent(QMouseEvent * event);
   void paintEvent(QPaintEvent * event);

 public:
   Canvas(QDate start_date, size_t weeks = 8);
   
   void setIntensity(Intensity level);
   void setWeekCount(int count);
   void setDate(QDate date);

   const std::vector<int> &getDays() const;
   QDate getDate() const;

};

#endif
