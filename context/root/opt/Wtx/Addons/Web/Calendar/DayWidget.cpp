
#include <Wt/WAbstractItemModel.h>

#include "Calendar.h"
#include "DayWidget.h"

Wtx::Web::Calendar::DayWidget::DayWidget( int index )
: m_index( index )
{
  addStyleClass( "divTableCell" );

  m_templt = addNew<Wt::WTemplate>( Wt::WString::tr("Wtx.Calendar.day.cell" ) );

  m_day = m_templt-> bindNew<Wt::WText>( "day" );
  m_day-> addStyleClass( "divDay" );

  m_header = m_templt-> bindNew<Wt::WText>( "header" );
  m_header-> addStyleClass( "divHeader" );

  m_body = m_templt-> bindNew<Wt::WContainerWidget>( "body" );
  m_body-> addStyleClass( "divBody" );

  m_footer = m_templt-> bindNew<Wt::WText>( "footer" );
  m_footer-> addStyleClass( "divFooter" );

}

int Wtx::Web::Calendar::DayWidget::index() const
{
  return m_index;
}

void Wtx::Web::Calendar::DayWidget::setDate( const Wt::WDate & value )
{
  m_date = value;

  if( date().day() == 1 )
  {
    m_day-> setText
    (
     Wt::WString("{1} {2} {3}")
     .arg( Wt::WDate::shortMonthName( date().month() ) )
     .arg( date().day() )
     .arg( date().year() )
    );
  }
  else
  {
    m_day-> setText
    (
     Wt::WString("{1}").arg( date().day() )
    );
  }

}

const Wt::WDate & Wtx::Web::Calendar::DayWidget::date() const
{
  return m_date;
}

Wt::WTemplate * Wtx::Web::Calendar::DayWidget::templt()
{
  return m_templt;
}

Wt::WText * Wtx::Web::Calendar::DayWidget::day()
{
  return m_day;
}

Wt::WText * Wtx::Web::Calendar::DayWidget::header()
{
  return m_header;
}

Wt::WContainerWidget * Wtx::Web::Calendar::DayWidget::body()
{
  return m_body;
}

Wt::WText * Wtx::Web::Calendar::DayWidget::footer()
{
  return m_footer;
}

//void Wtx::Web::Calendar::DayWidget::render( Wt::WFlags<Wt::RenderFlag> flags )
//{
//  Wt::WContainerWidget::render( flags );
//}

#ifdef NEVEr
Wt::Signal<> & Wtx::Web::Calendar::DayWidget::clicked()
{
  return m_clicked;
}

Wt::Signal<> & Wtx::Web::Calendar::DayWidget::doubleClicked()
{
  return m_doubleClicked;
}
#endif

