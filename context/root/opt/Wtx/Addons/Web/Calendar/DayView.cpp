
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WDate.h>

#include "Widget.h"
#include "DayView.h"

Wtx::Web::Calendar::DayView::DayView( int firstDayOfWeek, Wtx::Web::Calendar::Widget * widget )
: Wtx::Web::Calendar::BaseView( firstDayOfWeek, widget )
{

}

