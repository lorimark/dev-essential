
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WCalendar.h>

#include <Wtx/Util.h>

#include "Calendar.h"
#include "MiniMonth.h"

Wtx::Web::Calendar::MiniMonth::MiniMonth( int fdow, const Wt::WDate & date )
: Wt::WContainerWidget()
{
  m_firstDayOfWeek = fdow;

  /*
  ** grab the date but make sure it's properly set to the
  **  beginning of the month, just in case the caller failed
  **  to do so.
  **
  */
  m_date = Wt::WDate(date.year(),date.month(),1);

  m_templt =
    addNew< Wt::WTemplate >
    (
     "<div>"
     "  <center>"
     "    ${prev}"
     "    ${month}"
     "    ${year}"
     "    ${next}"
     "  </center>"
     "</div>"
     "<div>"
     "  ${table}"
     "</div>"
    );

  m_prev  = templt()-> bindNew< Wt::WText >( "prev", "" );
  m_next  = templt()-> bindNew< Wt::WText >( "next", "" );
  m_month = templt()-> bindNew< Wt::WText >( "month", Wt::WDate::longMonthName( date.month() ) );
  m_year  = templt()-> bindNew< Wt::WText >( "year",  Wtx::itos( date.year() ) );

  m_prev-> clicked().connect( [=](){ m_prevClicked.emit(); } );
  m_next-> clicked().connect( [=](){ m_nextClicked.emit(); } );

  /*
  ** put in a table, and then put another header
  **  in that contains the weekday-names.
  **
  */
  m_table = templt()-> bindNew<Wt::WTable>( "table" );
  table()-> addStyleClass( "Wtx_MiniMonth" );

  updateView();

} // endMiniCalendar::MiniCalendar( const Wt::WDate & date )


void Wtx::Web::Calendar::MiniMonth::updateView()
{
  table()-> clear();

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
  auto firstDayOfWeek = m_firstDayOfWeek % 7;

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
    auto w = std::make_unique< Wt::WText >( daynames().at((weekday+firstDayOfWeek)%7).substr(0,3) );

    w-> addStyleClass( "Wtx_MiniMonth_dayname" );

    table()-> elementAt( 0, weekday )-> addWidget( std::move(w) );
  }

//  for( int i=0; i<14; i++ )
//    std::cout << __FILE__ << ":" << __LINE__ << " " << i << " " << i % 7 << std::endl;

  auto dow = (m_date.dayOfWeek()-firstDayOfWeek)%7;

#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " dat:" << m_date.toString()
    << " dow:" << m_date.dayOfWeek()
    << " dow:" << dow
    << " fdw:" << firstDayOfWeek
    << std::endl
    ;
#endif

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
      auto d = m_date.addDays( (dow*-1) + ((week*7)+day) );
      auto w = std::make_unique< DayWidget >( d );
      m_dayWidgets.push_back( w.get() );

      table()-> elementAt( week*7, day )-> addWidget( std::move(w) );
    }

  } // endfor( int week = 0; week < 6; week++ )

}

void Wtx::Web::Calendar::MiniMonth::setSelectedDate( const Wt::WDate & date )
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


void Wtx::Web::Calendar::MiniMonth::allowPrev( bool value )
{
  if( value )
    m_prev-> setText( "<<" );
  else
    m_prev-> setText( "" );
}

void Wtx::Web::Calendar::MiniMonth::allowNext( bool value )
{
  if( value )
    m_next-> setText( ">>" );
  else
    m_next-> setText( "" );
}

void Wtx::Web::Calendar::MiniMonth::allowPrevNext( bool value )
{
  allowPrev( value );
  allowNext( value );
}



Wtx::Web::Calendar::MiniMonth::DayWidget::DayWidget( const Wt::WDate & date )
: Wt::WText( Wt::WString("{1}").arg( date.day() ) ),
  m_date(date)
{
  addStyleClass( "Wtx_MiniMonth_day" );

  if( date == Wt::WDate::currentDate() )
  {
    addStyleClass( "Wtx_MiniMonth_today" );
  }

}

const Wt::WDate & Wtx::Web::Calendar::MiniMonth::DayWidget::date() const
{
  return m_date;
}

void Wtx::Web::Calendar::MiniMonth::DayWidget::setSelected( bool value )
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

void Wtx::Web::Calendar::MiniMonth::browseTo( const Wt::WDate & date )
{
  m_date = date;
  updateView();
}


