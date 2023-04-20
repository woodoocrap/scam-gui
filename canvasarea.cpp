#include "canvasarea.hpp"

#include "QMessageBox"
#include "QScrollBar"

void CanvasArea::setupStyles()
{
   setStyleSheet("font-size: 14px;");
   weeksInput.setStyleSheet("border: solid #005577; border-width: 0 0 1px 0;");
   dateInput.setStyleSheet("border: solid #005577; border-width: 0 0 1px 0;");
   scrollArea.setMinimumHeight(canvas.height()+20);

   scrollArea.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
   scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   
   scrollArea.setAlignment(Qt::AlignCenter);
   vbox.setAlignment(Qt::AlignHCenter);
   vbox.setSpacing(15);
}


void CanvasArea::setupLayout() 
{
   grid.addWidget(&weeksLabel, 0, 0);
   grid.addWidget(&weeksInput, 0, 1);
   grid.addWidget(&setWeeksButton, 0, 2);

   grid.addWidget(&dateLabel, 1, 0);
   grid.addWidget(&dateInput, 1, 1);
   grid.addWidget(&setDateButton, 1, 2);
   
   vbox.addLayout(&grid);

   canvasRow.addWidget(&colorPicker);
   canvasRow.addWidget(&scrollArea);
   scrollArea.setWidget(&canvas);

   vbox.addLayout(&canvasRow);
   setLayout(&vbox);
}


CanvasArea::CanvasArea(QWidget * parent)
 : QWidget(parent),
   canvas(QDate::currentDate().addDays(-56))
{
   setDateButton.setText("Set");
   setWeeksButton.setText("Set");
   dateInput.setCalendarPopup(true);
   weeksLabel.setText("week count: ");
   dateLabel.setText("date: ");
   weeksInput.setText(QString::number(8));

   dateInput.setDate(QDate::currentDate().addDays(-56));
   dateInput.setDisplayFormat("dd-MM-yyyy");

   weeksInput.setMaxLength(2);

   connect(&colorPicker, &ColorPicker::colorChanged, this, &CanvasArea::colorUpdated);
   connect(&setWeeksButton, &QPushButton::clicked, this, &CanvasArea::weekCountUpdated);
   connect(&setDateButton, &QPushButton::clicked, this, &CanvasArea::dateUpdated);

   setupStyles();
   setupLayout();
}


void CanvasArea::colorUpdated() { canvas.setIntensity(colorPicker.getIntensity()); }


void CanvasArea::weekCountUpdated() 
{
   size_t week_count = weeksInput.text().toInt();
   canvas.setWeekCount(week_count);
}


void CanvasArea::dateUpdated() 
{
   QDate date = dateInput.date();

   if ( date.year() < 1970 ) {

      QMessageBox::critical(this, "error", "invalid date");
      dateInput.setDate(QDate::currentDate());

      return;
   }

   canvas.setDate(dateInput.date()); 
}


const std::vector<int>& CanvasArea::getDays() const { return canvas.getDays(); }

QDate CanvasArea::getDate() const { return canvas.getDate(); }
