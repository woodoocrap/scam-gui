#include "canvas.hpp"


Canvas::Canvas(QDate date, size_t weeks)
{
   setDate(date);
   setWeekCount(weeks);
}  


void Canvas::setWeekCount(int weeks)
{
   if ( weeks < 1 or weeks > 52 ) { weeks = 8; }
   days.resize(weeks * 7 - week_offset);

   setFixedSize(padded_size * weeks - padding, padded_size * 7 - padding);
   update();
}


void Canvas::setDate(QDate new_date)
{
   date = new_date;
   week_offset = date.dayOfWeek() % 7;
   update();
}


void Canvas::drawGrid(QPainter * painter)
{
   int step = cell_size + padding / 2;

   painter->setPen(QPen(QColor("#0d1117"), padding));
   painter->fillRect(0, 0, width(), height(), "#161b22");

   //horizontall lines
   for ( int i = step; i < height() - cell_size; i+=step) {
      painter->drawLine(0, i, width(), i);
      i += padding / 2;
   } 

   //vertical lines
   for ( int i = step; i < width() - cell_size; i+=step) {
      painter->drawLine(i, 0, i, height());
      i += padding / 2;
   } 
}


void Canvas::fillDay(QPainter * painter, int day)
{
   int x = ((day + week_offset) / 7) * padded_size;
   int y = ((day + week_offset) % 7) * padded_size;

   painter->fillRect(x+2, y+2, cell_size-4, cell_size-4, intensity_colors[days[day]]);
}


void Canvas::paintEvent(QPaintEvent * event)
{
   QPainter painter(this);
   
   drawGrid(&painter);
   //render week offset disabled
   painter.fillRect(0, 0, cell_size, (cell_size + padding) * week_offset, "#0d1117");
   
   for ( int i = 0; i < days.size(); ++i ) {
      if ( days[i] > 0 ) { fillDay(&painter, i); }
   }
}


void Canvas::mousePressEvent(QMouseEvent * event)
{
   //parse click cordinates to locate a day
   int day = event->x() / padded_size * 7 + event->y() / padded_size;
   day -= week_offset;

   if ( day >= 0 ) {
      if ( days[day] == intensity_level ) { days[day] = 0; }
      else { days[day] = intensity_level; }
   }
   
   update();
}


void Canvas::setIntensity(Intensity level) { intensity_level = level; }

const std::vector<int>& Canvas::getDays() const { return days; }

QDate Canvas::getDate() const { return date; }

