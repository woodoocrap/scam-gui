#include "colorpicker.hpp"


const char * intensity_colors[] = { "#161b22", "#0e4429", "#006d32", "#26a641", "#39d353" };


ColorCell::ColorCell(Intensity intensity, QWidget * parent)
   : QFrame(parent),
     level(intensity)
{
   setFixedSize(35, 35);
   paintUnselected();
}


void ColorCell::paintUnselected()
{
   setStyleSheet("background: " + QString(intensity_colors[level]) + "; border: 1px solid #005577; border-radius: 5px;");
}


void ColorCell::paintSelected()
{
   setStyleSheet("background: " + QString(intensity_colors[level]) + "; border: 4px solid #005577; border-radius: 5px;");
}


void ColorCell::mousePressEvent(QMouseEvent * event) { emit clicked(); }

Intensity ColorCell::getIntensity() const { return level; }



ColorPicker::ColorPicker(QWidget * parent)
   : QWidget(parent)
{
   for ( int i = 4; i >= 0; i-=1 ) {
      ColorCell * cell = new ColorCell((Intensity)i, this);
      connect(cell, &ColorCell::clicked, this, &ColorPicker::cellSelected);
      vbox.addWidget(cell);
   }

   setLayout(&vbox);
}


void ColorPicker::cellSelected()
{
   if ( selectedCell != nullptr ) { selectedCell->paintUnselected(); }

   selectedCell = qobject_cast<ColorCell*>(sender());
   selectedCell->paintSelected();

   emit colorChanged();
}


Intensity ColorPicker::getIntensity() const
{
   return selectedCell == nullptr ? None : selectedCell->getIntensity();
}
