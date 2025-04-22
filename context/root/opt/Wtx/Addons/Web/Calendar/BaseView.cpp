 
#include <Wt/WStandardItemModel.h>

#include "Widget.h"
#include "BaseView.h"

Wtx::Web::Calendar::BaseView::BaseView( int firstDayOfWeek, Wtx::Web::Calendar::Widget * widget )
: m_firstDayOfWeek( firstDayOfWeek ),
  m_widget( widget )
{
}

void Wtx::Web::Calendar::BaseView::setSelectionMode( Wt::SelectionMode mode )
{
}

void Wtx::Web::Calendar::BaseView::browseToPreviousYear()
{
}

void Wtx::Web::Calendar::BaseView::browseToPreviousMonth()
{
}

void Wtx::Web::Calendar::BaseView::browseToNextYear()
{
}

void Wtx::Web::Calendar::BaseView::browseToNextMonth()
{
}

void Wtx::Web::Calendar::BaseView::browseTo( const Wt::WDate & date )
{
}

const Wt::WDate & Wtx::Web::Calendar::BaseView::selectedDate() const
{
  return m_selectedDate;
}

void Wtx::Web::Calendar::BaseView::setSelectedDate( const Wt::WDate & value )
{
  m_selectedDate = value;
}

int Wtx::Web::Calendar::BaseView::currentDay() const
{
  return m_selectedDate.day();
}

int Wtx::Web::Calendar::BaseView::currentMonth() const
{
  return m_selectedDate.month();
}

int Wtx::Web::Calendar::BaseView::currentYear() const
{
  return m_selectedDate.year();
}

void Wtx::Web::Calendar::BaseView::clearSelection()
{
}

void Wtx::Web::Calendar::BaseView::select( const Wt::WDate & value )
{
  m_selectedDate = value;
}

void Wtx::Web::Calendar::BaseView::select( const std::set< Wt::WDate > & dates )
{
}

void Wtx::Web::Calendar::BaseView:: setFirstDayOfWeek( int dayOfWeek )
{
}

const std::set< Wt::WDate > Wtx::Web::Calendar::BaseView::selection() const
{
  return std::set< Wt::WDate >();
}

Wt::Signal<> & Wtx::Web::Calendar::BaseView::selectionChanged()
{
  return m_selectionChanged;
}

Wt::Signal< Wt::WDate > & Wtx::Web::Calendar::BaseView::activated()
{
  return m_activated;
}

Wt::Signal< Wt::WDate > & Wtx::Web::Calendar::BaseView::clicked()
{
  return m_clicked;
}

Wt::Signal< int, int > & Wtx::Web::Calendar::BaseView::currentPageChanged()
{
  return m_currentPageChanged;
}

void Wtx::Web::Calendar::BaseView::setSingleClickSelect( bool single )
{
}

void Wtx::Web::Calendar::BaseView::setBottom( const Wt::WDate & bottom )
{
}

const Wt::WDate Wtx::Web::Calendar::BaseView::bottom() const
{
  return Wt::WDate();
}

void Wtx::Web::Calendar::BaseView::setTop( const Wt::WDate & top )
{
}

const Wt::WDate Wtx::Web::Calendar::BaseView::top() const
{
  return Wt::WDate();
}

Wtx::Web::Calendar::Widget * Wtx::Web::Calendar::BaseView::widget()
{
  return m_widget;
}

std::shared_ptr<Wt::WAbstractItemModel> Wtx::Web::Calendar::BaseView::getModel( const Wt::WDate & date, const std::vector<std::string> & fieldList )
{
  return m_widget-> getModel( date, fieldList );
}


