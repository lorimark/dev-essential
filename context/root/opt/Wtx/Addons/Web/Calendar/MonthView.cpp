

#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WDate.h>
#include <Wt/WTableView.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WPushButton.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTime.h>

#include "Calendar.h"
#include "MonthView.h"
#include "Widget.h"

#define COUT_(X) std::cout << __FILE__ << "::" << __LINE__ << " " << X << std::endl;
#define COUT_LINE COUT_("");

namespace {

class DayOfMonth
: public Wtx::Web::Calendar::DayWidget
{
  public:

    DayOfMonth( int index, Wtx::Web::Calendar::MonthView * widget )
    : DayWidget( index ),
      m_widget( widget )
    {
      addStyleClass( "divDayOfMonth" );

      m_tableView =
        body()-> addNew<Wt::WTableView>();

      m_tableView-> setHeaderHeight(0);
      m_tableView-> setSelectionMode( Wt::SelectionMode::Single );
      m_tableView-> setHeight( "100px" );
      m_tableView-> setOverflow( Wt::Overflow::Hidden, Wt::Orientation::Horizontal );

      m_tableView-> clicked().connect( [=]( Wt::WModelIndex index, Wt::WMouseEvent event )
      {
        clicked().emit( event );
      });

      m_tableView-> doubleClicked().connect( [=]( Wt::WModelIndex index, Wt::WMouseEvent event )
      {
        doubleClicked().emit( event );
      });

    }

    Wt::WTableView * tableView();

    virtual void setDate( const Wt::WDate & value );

    Wt::WTableView * m_tableView;

    Wtx::Web::Calendar::MonthView * m_widget = nullptr;

};

Wt::WTableView * DayOfMonth::tableView()
{
  return m_tableView;
}

void DayOfMonth::setDate( const Wt::WDate & value )
{
  Wtx::Web::Calendar::DayWidget::setDate( value );

  //                                                2          3           4           5        6
  auto datamodel = m_widget-> getModel( date(), {"keyField","cfyField","timeStart","timeStop","note"} );

  auto model = std::make_shared<Wt::WStandardItemModel>( datamodel-> rowCount(), 3 );

  /*
  ** generate a table of formatted rows
  **
  */
  for( int row=0; row < datamodel-> rowCount(); row++ )
  {
    /*
    ** grab some data from the source model
    **
    */
    auto keyField = Wt::asString( datamodel-> data( row, 2 ) );
    auto cfyField = Wt::asString( datamodel-> data( row, 3 ) );
    auto timeStart = Wt::WTime::fromString( Wt::asString( datamodel-> data( row, 4 ) ), "hh:mm:ss" );
    auto timeStop = Wt::WTime::fromString( Wt::asString( datamodel-> data( row, 5 ) ), "hh:mm:ss" );
    auto note = Wt::asString( datamodel-> data( row, 6 ) );

    /*
    ** if this appointment has a time associated with it
    **  generate some formatting for that
    **
    */
    Wt::WString timepart;
    if( timeStart.isValid() )
    {
      Wt::WString format = "hA";
      if( timeStart.minute() != 0 )
        format = "h:mmA";

      timepart = timeStart.toString(format) + " ";
    }

    /*
    ** set the data in to the model
    **
    */
    model-> setData( row, 0, datamodel-> data( row, 0 ) );
    model-> setData( row, 1, datamodel-> data( row, 1 ) );
    model-> setData( row, 2, timepart + keyField );

    /*
    ** set the tool-tip for this item as well
    **
    */
    auto toolTip =
      Wt::WString("{1}\n{2}\n{3}\n{4}\n{5}")
      .arg( value.toString() )
      .arg( timeStart.toString() + " " + timeStop.toString() )
      .arg( keyField )
      .arg( cfyField )
      .arg( note.toUTF8().substr(0,150) )
      ;

    model-> setData( row, 2, toolTip, Wt::ItemDataRole::ToolTip );

  } // endfor( int row=0; row < datamodel-> rowCount(); row++ )

  m_tableView-> setModel( model );

  m_tableView-> setColumnHidden(0,true);
  m_tableView-> setColumnHidden(1,true);

} // endvoid DayOfMonth::setDate( const Wt::WDate & value )

} // endnamespace {

Wtx::Web::Calendar::MonthView::MonthView( int firstDayOfWeek, Wtx::Web::Calendar::Widget * widget )
: Wtx::Web::Calendar::BaseView( firstDayOfWeek, widget )
{
  addStyleClass( "divTable" );
  addStyleClass( "blueTable" );

  {
    auto cwHeader = addNew<Wt::WContainerWidget>();
    cwHeader-> addStyleClass( "divTableHeading" );

    auto cwRow = cwHeader-> addNew<Wt::WContainerWidget>();
    cwRow-> addStyleClass( "divTableRow" );

    for( int weekday = 0; weekday < 7; weekday++ )
    {
      auto cwDay = cwRow-> addNew<Wt::WContainerWidget>();
      cwDay-> addStyleClass( "divTableHead" );

      cwDay-> addNew<Wt::WText>( daynames().at(weekday) );
    }
  }

  /*
  ** loop through five weeks of calendar
  **
  */
  for( int week = 0; week < 6; week++ )
  {
    auto cwWeek = addNew<Wt::WContainerWidget>();
    cwWeek-> addStyleClass( "divTableRow" );

    /*
    ** loop through 7 days in a week
    **
    */
    for( int day = 0; day < 7; day++ )
    {
      /*
      ** create the container for this day
      **
      */
      auto cwDay = cwWeek-> addNew<DayOfMonth>( (week*7)+day, this );

      cwDay-> clicked().connect( [=]()
      {
        if( cwDay-> tableView()-> selectedIndexes().size() == 1 )
        {
          m_itemClicked.emit( *cwDay-> tableView()-> selectedIndexes().begin() );
        }

        m_clicked.emit( cwDay-> date() );

      });

      cwDay-> doubleClicked().connect( [=]()
      {
        if( cwDay-> tableView()-> selectedIndexes().size() == 1 )
        {
          m_itemDoubleClicked.emit( *cwDay-> tableView()-> selectedIndexes().begin() );
        }

        m_doubleClicked.emit( cwDay-> date() );

      });

      /*
      ** remember
      **
      */
      m_dayWidgets.push_back( cwDay );

    } // endfor( int day = 0; day < 7; day++ )

  } // endfor( int week = 0; week < 5; week++ )

/*!
** \todo not sure if this should be done here or not,
**
** The issue is, we are trying to defer rendering of this
**  widget until it is actually called upon - since it is
**  so model-intensive, we need to wait unti someone is
**  actually ~looking~ at it before we load it all.  This was
**  turned off because it was being called when the date
**  wasn't even set yet - so it was doing nothing.
**
*/
//  updateView();

} // endWtx::Web::Calendar::MonthView::MonthView( const Wt::WDate & selectedDate )

Wt::Signal<Wt::WDate> & Wtx::Web::Calendar::MonthView::clicked()
{
  return m_clicked;
}

Wt::Signal<Wt::WDate> & Wtx::Web::Calendar::MonthView::doubleClicked()
{
  return m_doubleClicked;
}

Wt::Signal<Wt::WModelIndex> & Wtx::Web::Calendar::MonthView::itemClicked()
{
  return m_itemClicked;
}

Wt::Signal<Wt::WModelIndex> & Wtx::Web::Calendar::MonthView::itemDoubleClicked()
{
  return m_itemDoubleClicked;
}

void Wtx::Web::Calendar::MonthView::updateView()
{
  Wt::WDate first( selectedDate().year(), selectedDate().month(), 1 );
  Wt::WDate start = first.addDays( first.dayOfWeek() * -1 );

  int cellDate = first.dayOfWeek() * -1;

  for( auto cwDay : dayWidgets() )
  {
    cwDay-> removeStyleClass( "divPreviousMonth" );
    cwDay-> removeStyleClass( "divNextMonth" );
    cwDay-> removeStyleClass( "divToday" );
    cwDay-> day()-> removeStyleClass( "divSelectedDate" );

    cwDay-> setDate( start.addDays( cwDay-> index() ) );

    /*
    ** if this day is in the previous month, then change
    **  the background-color
    **
    */
    if( cwDay-> date().month() < selectedDate().month() )
    {
      cwDay-> addStyleClass( "divPreviousMonth", true );
    }

    /*
    ** if this day is in the next month, then change
    **  the background-color
    **
    */
    if( cwDay-> date().month() > selectedDate().month() )
    {
      cwDay-> addStyleClass( "divNextMonth", true );
    }

    /*
    ** if this day is actually 'today' then change the
    **  background color.
    **
    */
    if( cwDay-> date() == today() )
    {
      cwDay-> addStyleClass( "divToday", true );
    }

    /*
    ** if this day is the date that is selected
    **  background color.
    **
    */
    if( cwDay-> date() == selectedDate() )
    {
      cwDay-> day()-> addStyleClass( "divSelectedDate", true );
    }

  } // endfor( auto cwDay : days() )

} // endvoid Wtx::Web::Calendar::MonthView::updateView()

void Wtx::Web::Calendar::MonthView::setSelectedDate( const Wt::WDate & date )
{
  Wtx::Web::Calendar::BaseView::setSelectedDate( date );
  updateView();
}

const Wt::WDate Wtx::Web::Calendar::MonthView::today() const
{
  return Wt::WDate::currentDate();
}

Wtx::Web::Calendar::DayWidget * Wtx::Web::Calendar::MonthView::dayWidget( const Wt::WDate & date ) const
{
  for( auto dw : m_dayWidgets )
  {
    if( date == dw-> date() )
      return dw;
  }

  return nullptr;
}

const std::vector< Wtx::Web::Calendar::DayWidget * > & Wtx::Web::Calendar::MonthView::dayWidgets() const
{
  return m_dayWidgets;
}


