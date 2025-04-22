
#include <Wt/WText.h>

#include "Calendar.h"
#include "WeekView.h"
#include "Widget.h"

Wtx::Web::Calendar::WeekView::WeekView( int firstDayOfWeek, Wtx::Web::Calendar::Widget * widget )
: Wtx::Web::Calendar::BaseView( firstDayOfWeek, widget )
{
  addStyleClass( "divTable" );
  addStyleClass( "blueTable" );

  {
    auto cwHeader = addNew<Wt::WContainerWidget>();
    cwHeader-> addStyleClass( "divTableHeading" );

    auto cwRow = cwHeader-> addNew<Wt::WContainerWidget>();
    cwRow-> addStyleClass( "divTableRow" );

    auto cwTime = cwRow-> addNew<Wt::WContainerWidget>();

   for( int weekday = 0; weekday < 7; weekday++ )
    {
      auto cwDay = cwRow-> addNew<Wt::WContainerWidget>();
      cwDay-> addStyleClass( "divTableHead" );

      cwDay-> addNew<Wt::WText>( daynames().at(weekday) );
    }
  }

  for( int hour = 0; hour < 24; hour++ )
  {
    auto cwRow = addNew<Wt::WContainerWidget>();
    cwRow-> addStyleClass( "divTableRow" );

    std::string ap;
    if( hour < 12 )
      ap = "am";
    else
      ap = "pm";

    auto cwTime = cwRow-> addNew<Wt::WContainerWidget>();
    cwTime-> addStyleClass( "divHour" );
    if( hour > 0 )
    {
      if( hour == 12 )
      {
        cwTime-> addNew<Wt::WText>( Wt::WString("noon") );
      }
      else
      {
        cwTime-> addNew<Wt::WText>( Wt::WString("{1} {2}").arg( hour%12 ).arg( ap ) );
      }
    }
    else
    {
      cwTime-> addNew<Wt::WText>( Wt::WString("12am") );
    }


    for( int day = 0; day < 7; day++ )
    {
      auto cwHour = cwRow-> addNew<Wt::WContainerWidget>();
      cwHour-> addStyleClass( "divTableCell" );


    }

  }

}


