/**************************************************************************
###########################################################################
##
## $SHOWOFFDB_BEGIN_LICENSE$
## Copyright (C) 2011 Lorimark Solutions, LLC and/or its subsidiary(-ies).
##  All rights reserved.
##  Contact: Lorimark Solutions, LLC (info@showoff-db.org)
##
## This file is part of the Showoff Database Application Framework.
##
##  Commercial Usage
##  Licensees holding valid ShowoffDB Commercial licenses may use this file in
##   accordance with the ShowoffDB Commercial License Agreement provided with the
##   Software or, alternatively, in accordance with the terms contained in
##   a written agreement between you and Lorimark Solutions, LLC.
##
## GNU Lesser General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU Lesser
##   General Public License version 2.1 as published by the Free Software
##   Foundation and appearing in the file LICENSE.LGPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU Lesser General Public License version 2.1 requirements
##   will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Lorimark Solutions, LLC gives
##  you certain additional rights.  These rights are described in the
##  Lorimark Solutions, LLC ShowoffDB LGPL Exception version 1.0, included in
##  the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU
##   General Public License version 3.0 as published by the Free Software
##   Foundation and appearing in the file LICENSE.GPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU General Public License version 3.0 requirements will be
##   met: http://www.gnu.org/copyleft/gpl.html.
##
## If you have questions regarding the use of this file, please contact
##   Lorimark Solutions, LLC at info@showoff-db.org.
## $SHOWOFFDB_END_LICENSE$
##
#############################################################################
****************************************************************************/

#ifndef __WTX_CALENDARMONTHVIEW_H___
#define __WTX_CALENDARMONTHVIEW_H___

#include <Wt/WModelIndex.h>

#include <Wtx/Addons/Web/Calendar/BaseView.h>
#include <Wtx/Addons/Web/Calendar/DayWidget.h>

namespace Wtx {
  namespace Web {
    namespace Calendar {

class Widget;
class MonthView
: public Wtx::Web::Calendar::BaseView
{
  public:

    MonthView( int firstDayOfWeek, Wtx::Web::Calendar::Widget * widget );

    Wtx::Web::Calendar::DayWidget * dayWidget( const Wt::WDate & date ) const;
    const std::vector< Wtx::Web::Calendar::DayWidget * > & dayWidgets() const;

    void setSelectedDate( const Wt::WDate & date );

    const Wt::WDate today() const;

    Wt::Signal< Wt::WDate > & clicked();
    Wt::Signal< Wt::WDate > & doubleClicked();
    Wt::Signal< Wt::WModelIndex > & itemClicked();
    Wt::Signal< Wt::WModelIndex > & itemDoubleClicked();

  protected:

  private:

    virtual void updateView();

    std::vector< Wtx::Web::Calendar::DayWidget * > m_dayWidgets;

    Wt::Signal< Wt::WDate > m_clicked;
    Wt::Signal< Wt::WDate > m_doubleClicked;
    Wt::Signal< Wt::WModelIndex > m_itemClicked;
    Wt::Signal< Wt::WModelIndex > m_itemDoubleClicked;

    int m_firstDayOfWeek = 1;
    Wtx::Web::Calendar::Widget * m_widget = nullptr;

}; // endclass MonthView

    } // endnamespace Calendar
  } // endnamespace Web
} // endnamespace Wtx


#endif // #ifndef __WTX_CALENDARMONTHVIEW_H___


