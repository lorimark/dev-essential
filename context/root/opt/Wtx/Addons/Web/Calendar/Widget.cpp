
#include <Wt/WStandardItemModel.h>
#include <Wt/WCalendar.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WTemplate.h>

#include "Widget.h"

#define COUT_(X) std::cout << __FILE__ << "::" << __LINE__ << " " << X << std::endl;
#define COUT_LINE COUT_("");


Wtx::Web::Calendar::Widget::ToolBar::ToolBar()
{
  addStyleClass("form-inline"); // this makes everything on one line
  auto templt = addNew<Wt::WTemplate>( Wt::WString::tr( "Wtx.Calendar.toolBar" ) );

  m_pbNew   = templt-> bindNew<Wt::WPushButton>( "new",      Wt::WString::tr("Wtx.Calendar.Widget.new")      );
  m_pbToday = templt-> bindNew<Wt::WPushButton>( "today",    Wt::WString::tr("Wtx.Calendar.Widget.today")    );
  m_pbPrev  = templt-> bindNew<Wt::WPushButton>( "previous", Wt::WString::tr("Wtx.Calendar.Widget.previous") );
  m_pbNext  = templt-> bindNew<Wt::WPushButton>( "next",     Wt::WString::tr("Wtx.Calendar.Widget.next")     );
  m_pbFind  = templt-> bindNew<Wt::WPushButton>( "find",     Wt::WString::tr("Wtx.Calendar.Widget.find")     );
  m_cbView  = templt-> bindNew<Wt::WComboBox>(   "view"                                                      );
  m_pbSett  = templt-> bindNew<Wt::WPushButton>( "settings", Wt::WString::tr("Wtx.Calendar.Widget.settings") );

  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.day"      ) );
  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.week"     ) );
  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.month"    ) );
  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.year"     ) );
  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.schedule" ) );
  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.4-days"   ) );
  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.5-days"   ) );
  m_cbView-> addItem( Wt::WString::tr( "Wtx.Calendar.Widget.View.table"    ) );

  m_date = templt-> bindNew<Wt::WText>( "date" );

}

Wt::WPushButton * Wtx::Web::Calendar::Widget::ToolBar::pbNew() const
{
  return m_pbNew;
}

Wt::WPushButton * Wtx::Web::Calendar::Widget::ToolBar::pbToday() const
{
  return m_pbToday;
}

Wt::WPushButton * Wtx::Web::Calendar::Widget::ToolBar::pbPrev() const
{
  return m_pbPrev;
}

Wt::WPushButton * Wtx::Web::Calendar::Widget::ToolBar::pbNext() const
{
  return m_pbNext;
}

Wt::WPushButton * Wtx::Web::Calendar::Widget::ToolBar::pbFind() const
{
  return m_pbFind;
}

Wt::WComboBox * Wtx::Web::Calendar::Widget::ToolBar::cbView() const
{
  return m_cbView;
}

Wt::WPushButton * Wtx::Web::Calendar::Widget::ToolBar::pbSett() const
{
  return m_pbSett;
}


Wtx::Web::Calendar::Widget::SideBar::SideBar( int firstDayOfWeek )
{
  m_calendar = addNew<Wt::WCalendar>();
  m_calendar-> addStyleClass( "calendarPicker" );
  m_calendar-> setSelectionMode( Wt::SelectionMode::Single );
  m_calendar-> setFirstDayOfWeek( firstDayOfWeek );
}

Wt::WCalendar * Wtx::Web::Calendar::Widget::SideBar::calendar() const
{
  return m_calendar;
}

int range( int value, int minimum, int maximum )
{
  if( value < minimum )
      value = minimum;

  if( value > maximum )
      value = maximum;

  return value;
}

Wtx::Web::Calendar::Widget::Widget( int firstDayOfWeek, Wtx::Web::Calendar::Database & database )
: m_database( database )
{
  /*
  ** make sure the requested first-day-of-week is properly limited.
  **  the possible values are:
  **
  **   1=mon
  **   2=tue
  **   3=wed
  **   4=thu
  **   5=fri
  **   6=sat
  **   7=sun
  **
  */
  firstDayOfWeek = range( firstDayOfWeek, 1, 7 );

  m_selectedDate = Wt::WDate::currentDate();

  auto u_lw = std::make_unique<Wt::WHBoxLayout>();
  auto lw = u_lw.get();
  setLayout( std::move(u_lw) );

  auto u_sideBar = std::make_unique<Wtx::Web::Calendar::Widget::SideBar>( firstDayOfWeek );
  m_sideBar = u_sideBar.get();
  lw-> addWidget( std::move( u_sideBar ) );
  m_sideBar-> calendar()-> clicked().connect( [=]( /* Wt::WDate & date */ )
  {
    if( m_sideBar-> calendar()-> selection().size() > 0 )
    {
      setSelectedDate( *(m_sideBar-> calendar()-> selection().begin()) );
    }
  });

  auto u_templt = std::make_unique<Wt::WTemplate>( Wt::WString::tr( "Wtx.Calendar.widget" ) );
  auto m_templt = u_templt.get();

  lw-> addWidget( std::move(u_templt), 1 );

  m_toolBar     = m_templt-> bindNew<ToolBar>( "toolBar" );

  m_toolBar-> pbNew()-> clicked().connect( [=]()
  {
    m_itemNew.emit( selectedDate() );
  });

  m_toolBar-> pbToday()-> clicked().connect( [=]()
  {
    setSelectedDate( Wt::WDate::currentDate() );
  });

  m_toolBar-> pbPrev()-> clicked().connect( [=]()
  {
    selectPrevious();
  });

  m_toolBar-> pbNext()-> clicked().connect( [=]()
  {
    selectNext();
  });

  m_toolBar-> cbView()-> activated().connect( [=]( int value )
  {
    setView( value );
  });

  m_stack       = m_templt-> bindNew<Wt::WStackedWidget>( "stack" );

  auto u_dayView = std::make_unique<Wtx::Web::Calendar::DayView>(firstDayOfWeek,this);
  m_dayView = u_dayView.get();
  m_stack-> addWidget( std::move(u_dayView) );

  auto u_weekView = std::make_unique<Wtx::Web::Calendar::WeekView>(firstDayOfWeek,this);
  m_weekView = u_weekView.get();
  m_stack-> addWidget( std::move(u_weekView) );

  auto u_monthView = std::make_unique<Wtx::Web::Calendar::MonthView>(firstDayOfWeek,this);
  m_monthView = u_monthView.get();
  m_stack-> addWidget( std::move(u_monthView) );
  m_monthView-> clicked().connect( [=]( Wt::WDate date )
  {
    setSelectedDate( date );
  });
  m_monthView-> itemClicked().connect( [=]( Wt::WModelIndex index )
  {
    m_itemClicked.emit( index );
  });
  m_monthView-> itemDoubleClicked().connect( [=]( Wt::WModelIndex index )
  {
    m_itemDoubleClicked.emit( index );
  });

  auto u_yearView = std::make_unique<Wtx::Web::Calendar::YearView>(firstDayOfWeek,this);
  m_yearView = u_yearView.get();
  m_stack-> addWidget( std::move(u_yearView) );

  auto u_scheduleView = std::make_unique<Wt::WText>("schedule");
  m_stack-> addWidget( std::move(u_scheduleView) );

  auto u_fourDaysView = std::make_unique<Wt::WText>("4-days");
  m_stack-> addWidget( std::move(u_fourDaysView) );

  auto u_fiveDaysView = std::make_unique<Wt::WText>("5-days");
  m_stack-> addWidget( std::move(u_fiveDaysView) );

  auto u_tableView = std::make_unique<Wt::WText>("Table");
  m_stack-> addWidget( std::move(u_tableView) );

  setView( MONTH );

  std::map< Wt::WDate, std::string > holidays =
  {
    { Wt::WDate( 2018, 5,  5 ), "Cinco de Mayo"         },
    { Wt::WDate( 2018, 5, 10 ), "Ascension Day"         },
    { Wt::WDate( 2018, 5, 13 ), "Mother's Day"          },
    { Wt::WDate( 2018, 5, 21 ), "Victoria Day (Canada)" },
    { Wt::WDate( 2018, 5, 28 ), "Memorial Day (USA)"    }
  };

  for( auto calendarDay : monthView()-> dayWidgets() )
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

  for( auto calendarDay : monthView()-> dayWidgets() )
  {
    auto moonItem = moon.find( calendarDay-> date() );
    if( moonItem != moon.end() )
    {
      calendarDay-> footer()-> setText( moonItem-> second );
    }
  }

  updateView();

} // endWtx::Web::Calendar::Widget::Widget()

void Wtx::Web::Calendar::Widget::setView( int value )
{
  m_toolBar-> cbView()-> setCurrentIndex( value );
  m_stack-> setCurrentIndex( value );
}

int Wtx::Web::Calendar::Widget::view() const
{
  return m_toolBar-> cbView()-> currentIndex();
}


const Wt::WDate & Wtx::Web::Calendar::Widget::selectedDate() const
{
  return m_selectedDate;
}

Wtx::Web::Calendar::YearView * Wtx::Web::Calendar::Widget::yearView() const
{
  return m_yearView;
}

Wtx::Web::Calendar::MonthView * Wtx::Web::Calendar::Widget::monthView() const
{
  return m_monthView;
}

Wtx::Web::Calendar::WeekView * Wtx::Web::Calendar::Widget::weekView() const
{
  return m_weekView;
}

Wtx::Web::Calendar::DayView * Wtx::Web::Calendar::Widget::dayView() const
{
  return m_dayView;
}

Wtx::Web::Calendar::Widget::ToolBar * Wtx::Web::Calendar::Widget::toolBar() const
{
  return m_toolBar;
}

Wtx::Web::Calendar::Widget::SideBar * Wtx::Web::Calendar::Widget::sideBar() const
{
  return m_sideBar;
}

void Wtx::Web::Calendar::Widget::selectPrevious()
{
  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.year" ) )
  {
    setSelectedDate( selectedDate().addMonths(-12) );
  }

  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.month" ) )
  {
    setSelectedDate( selectedDate().addMonths(-1) );
  }

  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.week" ) )
  {
    setSelectedDate( selectedDate().addDays(-7) );
  }

  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.day" ) )
  {
    setSelectedDate( selectedDate().addDays(-1) );
  }

}

void Wtx::Web::Calendar::Widget::selectNext()
{
  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.year" ) )
  {
    setSelectedDate( selectedDate().addMonths(12) );
  }

  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.month" ) )
  {
    setSelectedDate( selectedDate().addMonths(1) );
  }

  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.week" ) )
  {
    setSelectedDate( selectedDate().addDays(7) );
  }

  if( toolBar()-> cbView()-> currentText() == Wt::WString::tr( "Wtx.Calendar.Widget.View.day" ) )
  {
    setSelectedDate( selectedDate().addDays(1) );
  }

}

void Wtx::Web::Calendar::Widget::updateView()
{
  m_modelMaps.clear();
  setSelectedDate( selectedDate() );
}

void Wtx::Web::Calendar::Widget::setSelectedDate( const Wt::WDate & date )
{
  m_selectedDate = date;
  m_sideBar-> calendar()-> browseTo( date );
  m_sideBar-> calendar()-> select( date );
  yearView()->  setSelectedDate( date );
  monthView()-> setSelectedDate( date );
  weekView()->  setSelectedDate( date );
  dayView()->   setSelectedDate( date );
}

Wt::Signal<Wt::WDate> & Wtx::Web::Calendar::Widget::itemNew()
{
  return m_itemNew;
}

Wt::Signal<Wt::WModelIndex> & Wtx::Web::Calendar::Widget::itemClicked()
{
  return m_itemClicked;
}

Wt::Signal<Wt::WModelIndex> & Wtx::Web::Calendar::Widget::itemDoubleClicked()
{
  return m_itemDoubleClicked;
}

/*!
** \brief Get a Model by Date
**
** This will construct - or cache-return - a shared model.
**
*/
std::shared_ptr<Wt::WAbstractItemModel> Wtx::Web::Calendar::Widget::getModel( const Wt::WDate & date, const std::vector<std::string> & fList )
{
  /*
  ** First, try to pull the model from the model cache.
  **  We may have already generated this model for this date,
  **  so we can just reuse it to save time.
  **
  */
  auto retVal = m_modelMaps[date];

  /*
  ** If we did-not get a model from the cache, then
  **  we're going to have to construct it.
  **
  */
  if( !retVal )
  {
    /*
    ** Generate a field-list.  The field-list always begins with
    **  the 'id' of the item.
    **
    */
    std::vector<std::string> fieldList = fList;
    fieldList.insert( fieldList.begin(), "id" );

    retVal = std::make_shared<Wt::WStandardItemModel>();
    retVal-> insertColumns( 0, fieldList.size()+2 );
    retVal-> setHeaderData( 1, Wt::Orientation::Horizontal, "source" );
    for( int i=0; i< fieldList.size(); i++ )
      retVal-> setHeaderData( i+1, Wt::Orientation::Horizontal, fieldList.at(i) );

    for( auto modelProvider : m_database.modelProviders() )
    {
      auto model = modelProvider-> getModel( date, fieldList );

      auto _column = [=]( const Wt::cpp17::any & fieldName )
      {
        for( int i=0; i< model-> columnCount(); i++ )
          if( Wt::asString( model-> headerData( i ) ) == Wt::asString( fieldName ) )
            return i;

        return -1;
      };

      int row = retVal-> rowCount();
      retVal-> insertRows( row, model-> rowCount() );

      for( int i=0; i< model-> rowCount(); i++, row++ )
      {
        retVal-> setData( row, 0, modelProvider-> name() );
        for( int j=0; j< retVal-> columnCount(); j++ )
        {
          int column=_column( retVal-> headerData(j) );
          if( column != -1 )
          {
            retVal-> setData( row, j, model-> data( i, column ) );
          }
        }
      }
    }

    m_modelMaps[date] = retVal;
  }

  return retVal;
}

#ifdef NEVER
Wtx::Web::Calendar::Widget::ToolBar * Wtx::Web::Calendar::Widget::toolBar() const
{
  return m_toolBar;
}

Wtx::Web::Calendar::Widget::SideBar * Wtx::Web::Calendar::Widget::sideBar() const
{
  return m_sideBar;
}
#endif

