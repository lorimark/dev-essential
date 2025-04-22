
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WCalendar.h>

#include "Calendar.h"
#include "YearView.h"
#include "Widget.h"

Wtx::Web::Calendar::YearView::MiniMonth::MiniMonth( int firstDayOfWeek, const Wt::WDate & date )
{
  /*
  ** The normal WCalendar employs a firstDayOfWeek function that is
  **  1-based, meaning, 1=first day of week which is also Monday.  Since
  **  we have daynames() that are zero-based, meaning 0=Sunday, the logic
  **  works out that 0=Sunday so therefore 1=Monday, but the specification
  **  for WCalendar is that the possible range is 1..7, not 0..6 so we
  **  have to make a slight adjustment to the incoming value so that
  **  7 becomes 0.
  **
  */
  firstDayOfWeek %= 7;

  /*
  ** grab the date but make sure it's properly set to the
  **  beginning of the month, just in case the caller failed
  **  to do so.
  **
  */
  m_date = Wt::WDate(date.year(),date.month(),1);

  /*
  ** put a header up
  **
  */
  addNew<Wt::WText>
  ( //            Month:{1} {2}:Year
   Wt::WString("<center>{1} {2}</center>")
   .arg( Wt::WDate::longMonthName( date.month() ) )
   .arg( date.year() )
  );

  /*
  ** put in a table, and then put another header
  **  in that contains the weekday-names.
  **
  */
  auto table = addNew<Wt::WTable>();
  table-> addStyleClass( "Wtx_MiniMonth" );

  /*
  ** put up a short-day-name based on the (normal)
  **  day names (meaning, sunday is usually the first day)
  **  in the header row.  If a different firstDayOfWeek was
  **  asked for, then the first-day pasted here will be
  **  that day.  If the firstDayOfWeek=3 then the first
  **  day shown in the first column should be wednesday.
  **
  */
  for( int weekday = 0; weekday < 7; weekday++ )
  {
    auto w = std::make_unique<Wt::WText>( daynames().at((weekday+firstDayOfWeek)%7).substr(0,3) );

    w-> addStyleClass( "Wtx_MiniMonth_dayname" );

    table-> elementAt( 0, weekday )-> addWidget( std::move(w) );
  }

//  for( int i=0; i<14; i++ )
//    std::cout << __FILE__ << ":" << __LINE__ << " " << i << " " << i % 7 << std::endl;

  auto dow = (date.dayOfWeek()-firstDayOfWeek)%7;

//  std::cout << __FILE__ << ":" << __LINE__
//    << " dow:" << date.dayOfWeek()
//    << " dow:" << dow
//    << " fdw:" << firstDayOfWeek
//    << " dat:" << date.toString()
//    << std::endl
//    ;

  /*
  ** put out a row for each week.  We are going to
  **  plop down 6 weeks of days
  **
  */
  for( int week = 0; week < 6; week++ )
  {
    /*
    ** put out a column for each day.  There are 7
    **  days in a week.
    **
    */
    for( int day = 0; day < 7; day++ )
    {
      auto d = date.addDays( (dow*-1) + ((week*7)+day) );
      auto w = std::make_unique<DayWidget>(d);
      m_dayWidgets.push_back( w.get() );

      table-> elementAt( week*7, day )-> addWidget( std::move(w) );
    }

  } // endfor( int week = 0; week < 6; week++ )

} // endMiniCalendar::MiniCalendar( const Wt::WDate & date )

void Wtx::Web::Calendar::YearView::MiniMonth::setSelectedDate( const Wt::WDate & date )
{
  for( auto dayWidget : m_dayWidgets )
  {
    if( dayWidget-> date() == date )
    {
      dayWidget-> setSelected( true );
    }
    else
    {
      dayWidget-> setSelected( false );
    }

  }
}

Wtx::Web::Calendar::YearView::DayWidget::DayWidget( const Wt::WDate & date )
: Wt::WText( Wt::WString("{1}").arg( date.day() ) ),
  m_date(date)
{
  addStyleClass( "Wtx_MiniMonth_day" );

  if( date == Wt::WDate::currentDate() )
  {
    addStyleClass( "Wtx_MiniMonth_today" );
  }

}

const Wt::WDate & Wtx::Web::Calendar::YearView::DayWidget::date() const
{
  return m_date;
}

void Wtx::Web::Calendar::YearView::DayWidget::setSelected( bool value )
{
  if( value )
  {
    addStyleClass( "Wtx_MiniMonth_selected" );
  }
  else
  {
    removeStyleClass( "Wtx_MiniMonth_selected" );
  }
}

Wtx::Web::Calendar::YearView::YearView( int firstDayOfWeek, Wtx::Web::Calendar::Widget * widget )
: Wtx::Web::Calendar::BaseView( firstDayOfWeek, widget )
{
  addStyleClass( "divTable" );
  addStyleClass( "blueTable" );

  auto currentYear = Wt::WDate( Wt::WDate::currentDate().year(), 1, 1 );

  for( int row = 0; row < 3; row++ )
  {
    auto cwRow = addNew<Wt::WContainerWidget>();
    cwRow-> addStyleClass( "divTableRow" );

    for( int col = 0; col < 4; col++ )
    {
      auto cwCol = cwRow-> addNew<Wt::WContainerWidget>();
      cwCol-> addStyleClass( "divTableCell" );

//      cwCol-> addNew<Wt::WCalendar>(); <--- this does not work because the WCalendar has too many things on it

      m_months.push_back
      (
        cwCol-> addNew<MiniMonth>( firstDayOfWeek, currentYear.addMonths( (row*4) + col ) )
      );

//      cwCol-> addNew<Wt::WCalendar>();
    }
  }

}


const std::vector< Wtx::Web::Calendar::YearView::MiniMonth * > & Wtx::Web::Calendar::YearView::months() const
{
  return m_months;
}

const std::vector< Wtx::Web::Calendar::YearView::DayWidget * > & Wtx::Web::Calendar::YearView::days() const
{
  return m_days;
}


void Wtx::Web::Calendar::YearView::setSelectedDate( const Wt::WDate & value )
{
  Wtx::Web::Calendar::BaseView::setSelectedDate( value );

  for( auto month : m_months )
  {
    month-> setSelectedDate( value );
  }
}

Wt::Signal< Wt::WDate > & Wtx::Web::Calendar::YearView::clicked()
{
  return m_clicked;
}



