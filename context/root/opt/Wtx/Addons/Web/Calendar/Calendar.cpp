
#include <string>
#include <vector>

#include <Wt/WString.h>

#include "Calendar.h"

std::vector<std::string> g_daynames;

const std::vector<std::string> & Wtx::Web::Calendar::daynames()
{
  if( g_daynames.size() == 0 )
  {
    g_daynames.push_back( Wt::WString::tr("Wtx.Calendar.dayname.sun").toUTF8() );
    g_daynames.push_back( Wt::WString::tr("Wtx.Calendar.dayname.mon").toUTF8() );
    g_daynames.push_back( Wt::WString::tr("Wtx.Calendar.dayname.tue").toUTF8() );
    g_daynames.push_back( Wt::WString::tr("Wtx.Calendar.dayname.wed").toUTF8() );
    g_daynames.push_back( Wt::WString::tr("Wtx.Calendar.dayname.thu").toUTF8() );
    g_daynames.push_back( Wt::WString::tr("Wtx.Calendar.dayname.fri").toUTF8() );
    g_daynames.push_back( Wt::WString::tr("Wtx.Calendar.dayname.sat").toUTF8() );
  }

  return g_daynames;
}

