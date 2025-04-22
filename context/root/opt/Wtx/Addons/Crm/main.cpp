#include <Wt/WServer.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WTable.h>
#include <Wt/WTableView.h>
#include <Wt/WDate.h>

#define COUT_(X) std::cout << __FILE__ << "::" << __LINE__ << " " << X << std::endl;
#define COUT_LINE COUT_("");

class CalendarActivity
{
  public:


  protected:

  private:

    

};

class Calendar
: public Wt::WContainerWidget
{
  public:

  protected:

  private:

};

/*!
** \brief Calendar Day Widget
**
** This class represents a single day on a calendar view.  This
**  is merely a container for controlling the visual representation
**  of a single day with a date indicator and headers and footers
**  and whatnot.
**
*/
class CalendarDay
: public Calendar
{
  public:

    CalendarDay( const Wt::WDate & date );

    const Wt::WDate & date() const;

    Wt::WTemplate        * templt();
    Wt::WText            * day();
    Wt::WText            * header();
    Wt::WContainerWidget * body();
    Wt::WText            * footer();

  protected:

  private:

    Wt::WDate m_date;
    Wt::WTemplate        * m_templt  = nullptr;
    Wt::WText            * m_day     = nullptr;
    Wt::WText            * m_header  = nullptr;
    Wt::WContainerWidget * m_body    = nullptr;
    Wt::WText            * m_footer  = nullptr;

}; // endclass CalendarDay

CalendarDay::CalendarDay( const Wt::WDate & d )
: m_date( d )
{
  addStyleClass( "divTableCell" );

  m_templt = addNew<Wt::WTemplate>( Wt::WString::tr("Calendar.day.cell" ) );

  m_day = m_templt-> bindNew<Wt::WText>( "day", Wt::WString("{1}").arg( date().day() ) );
  m_day-> addStyleClass( "divDay" );

  m_header = m_templt-> bindNew<Wt::WText>( "header" );
  m_header-> addStyleClass( "divHeader" );

  m_body = m_templt-> bindNew<Wt::WContainerWidget>( "body" );
  m_body-> addStyleClass( "divBody" );

  m_footer = m_templt-> bindNew<Wt::WText>( "footer" );
  m_footer-> addStyleClass( "divFooter" );

}

const Wt::WDate & CalendarDay::date() const
{
  return m_date;
}

Wt::WTemplate * CalendarDay::templt()
{
  return m_templt;
}

Wt::WText * CalendarDay::day()
{
  return m_day;
}

Wt::WText * CalendarDay::header()
{
  return m_header;
}

Wt::WContainerWidget * CalendarDay::body()
{
  return m_body;
}

Wt::WText * CalendarDay::footer()
{
  return m_footer;
}



class CalendarWeek
: public Calendar
{
  public:

    CalendarWeek( const Wt::WDate & date );

  protected:

  private:

};

CalendarWeek::CalendarWeek( const Wt::WDate & date )
{
  addStyleClass( "divTableRow" );
}

class CalendarMonth
: public Calendar
{
  public:

    CalendarMonth( const Wt::WDate & selectedDate );

    const std::vector< CalendarDay * > & days() const;

  protected:

  private:

    std::vector< CalendarDay * > m_days;
};

CalendarMonth::CalendarMonth( const Wt::WDate & selectedDate )
{
  addStyleClass( "divTable" );
  addStyleClass( "blueTable" );

  Wt::WDate first( selectedDate.year(), selectedDate.month(), 1 );
  Wt::WDate start = first.addDays( first.dayOfWeek() * -1 );

  {
    auto cwHeader = addNew<Wt::WContainerWidget>();
    cwHeader-> addStyleClass( "divTableHeading" );

    auto cwRow = cwHeader-> addNew<Wt::WContainerWidget>();
    cwRow-> addStyleClass( "divTableRow" );

    static const std::vector<std::string> daynames =
    {
      "Sun",
      "Mon",
      "Tue",
      "Wed",
      "Thu",
      "Fri",
      "Sat"
    };
    for( int weekday = 0; weekday < 7; weekday++ )
    {
      auto cwDay = cwRow-> addNew<Wt::WContainerWidget>();
      cwDay-> addStyleClass( "divTableHead" );

      cwDay-> addNew<Wt::WText>( daynames.at(weekday) );
    }
  }

  int cellDate = first.dayOfWeek() * -1;

  /*
  ** loop through five weeks of calendar
  **
  */
  for( int week = 0; week < 5; week++ )
  {
    auto currentWeek = start.addDays( week*7 );

    auto cwWeek = addNew<CalendarWeek>( currentWeek );

    /*
    ** loop through 7 days in a week
    **
    */
    for( int day = 0; day < 7; day++ )
    {
      /*
      ** get this day as current WDate
      **
      */
      auto currentDay = start.addDays( (week*7)+day );

      /*
      ** create the container for this day
      **
      */
      auto cwDay = cwWeek-> addNew<CalendarDay>( currentDay );

      /*
      ** if this day is outside of this month then
      **  stick the month abbreviation leader at the
      **  beginning of the 'day date'
      **
      */
      if( currentDay.month() != selectedDate.month() )
      {
        cwDay-> day()-> setText
        (
         Wt::WString("{1} {2}")
         .arg( Wt::WDate::shortMonthName( currentDay.month() ) )
         .arg( currentDay.day() )
        );
      }

      /*
      ** if this day is in the previous month, then change
      **  the background-color
      **
      */
      if( currentDay.month() < selectedDate.month() )
      {
        cwDay-> addStyleClass( "divPreviousMonth" );
      }

      /*
      ** if this day is in the next month, then change
      **  the background-color
      **
      */
      if( currentDay.month() > selectedDate.month() )
      {
        cwDay-> addStyleClass( "divNextMonth" );
      }

      /*
      ** if this day is actually 'today' then change the
      **  background color.
      **
      */
      if( currentDay == selectedDate )
      {
        cwDay-> addStyleClass( "divCurrentDay" );
      }

      /*
      ** remember
      **
      */
      m_days.push_back( cwDay );

    } // endfor( int day = 0; day < 7; day++ )

  } // endfor( int week = 0; week < 5; week++ )

} // endCalendarMonth::CalendarMonth( const Wt::WDate & selectedDate )



const std::vector< CalendarDay * > & CalendarMonth::days() const
{
  return m_days;
}

class CalendarWidget
: public Wt::WContainerWidget
{
  public:

    CalendarWidget();

    CalendarMonth * monthView() const;

  private:

    Wt::WTemplate * m_templt = nullptr;
    CalendarMonth * m_monthView = nullptr;
    Wt::WContainerWidget * m_dayPicker = nullptr;
};

CalendarWidget::CalendarWidget()
{
  m_templt = addNew<Wt::WTemplate>( Wt::WString::tr( "Calendar.widget" ) );

  m_dayPicker = m_templt-> bindNew<Wt::WContainerWidget>( "dayPicker" );
  m_monthView = m_templt-> bindNew<CalendarMonth>( "monthView", Wt::WDate::currentDate() );

  std::map< Wt::WDate, std::string > holidays =
  {
    { Wt::WDate( 2018, 5,  5 ), "Cinco de Mayo"         },
    { Wt::WDate( 2018, 5, 10 ), "Ascension Day"         },
    { Wt::WDate( 2018, 5, 13 ), "Mother's Day"          },
    { Wt::WDate( 2018, 5, 21 ), "Victoria Day (Canada)" },
    { Wt::WDate( 2018, 5, 28 ), "Memorial Day (USA)"    }
  };

  for( auto calendarDay : m_monthView-> days() )
  {
    auto holidayItem = holidays.find( calendarDay-> date() );
    if( holidayItem != holidays.end() )
    {
      calendarDay-> header()-> setText( holidayItem-> second );
    }
  }

  std::map< Wt::WDate, std::string > moon =
  {
    { Wt::WDate( 2018, 5,  7 ), "Last Quarter Moon"     },
    { Wt::WDate( 2018, 5, 15 ), "New Moon"              },
    { Wt::WDate( 2018, 5, 21 ), "New Quarter Moon"      },
    { Wt::WDate( 2018, 5, 29 ), "Full Moon"             }
  };

  for( auto calendarDay : m_monthView-> days() )
  {
    auto moonItem = moon.find( calendarDay-> date() );
    if( moonItem != moon.end() )
    {
      calendarDay-> footer()-> setText( moonItem-> second );
    }
  }
}

CalendarMonth * CalendarWidget::monthView() const
{
  return m_monthView;
}

class DevApp
: public Wt::WApplication
{
  public:
    DevApp(const Wt::WEnvironment &env)
    : Wt::WApplication( env )
    {
      auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
      bootstrapTheme-> setVersion( Wt::BootstrapVersion::v3 );
      bootstrapTheme-> setResponsive(true);
      setTheme( bootstrapTheme );
      useStyleSheet( "resources/themes/bootstrap/3/bootstrap-theme.min.css" );
      useStyleSheet( "styles/calendar.css" );
      messageResourceBundle().use( "calendar" );
      setTitle( "Calendar" );

      auto calendarWidget = root()-> addNew<CalendarWidget>();

      COUT_( calendarWidget-> monthView()-> days().size() );
    }

};

int main(int argc, char** argv)
{
  try
  {
    Wt::WServer server( argc, argv );

    server.addEntryPoint
    (
      Wt::EntryPointType::Application,
      [](const Wt::WEnvironment &env)
      {
        return std::make_unique<DevApp>(env);
      },
      "/calendar"
    );

    server.run();
  }
  catch( Wt::WServer::Exception & e )
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;

}

