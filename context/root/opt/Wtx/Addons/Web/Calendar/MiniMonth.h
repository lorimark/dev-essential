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

#ifndef __WTX_MINIMONTH_H___
#define __WTX_MINIMONTH_H___

#include <Wt/WContainerWidget.h>

#include "DayWidget.h"

namespace Wtx {
  namespace Web {
    namespace Calendar {

class MiniMonth
: public Wt::WContainerWidget
{
  public:

    class DayWidget
    : public Wt::WText
    {
      public:

        DayWidget( const Wt::WDate & date );

        const Wt::WDate & date() const;

        void setSelected( bool value );

      private:

        Wt::WDate m_date;
    };

    MiniMonth( int firstDayOfWeek, const Wt::WDate & date );

    void allowPrev( bool value = true );
    void allowNext( bool value = true );
    void allowPrevNext( bool value = true );
    void setSelectedDate( const Wt::WDate & date );

    void browseTo( const Wt::WDate & date );

    Wt::WTemplate * templt()
    {
      return m_templt;
    }

    Wt::WTable * table()
    {
      return m_table;
    }

    Wt::Signal<> & prevClicked()
    {
      return m_prevClicked;
    }

    Wt::Signal<> & nextClicked()
    {
      return m_nextClicked;
    }

  private:

    void updateView();

    int m_firstDayOfWeek = 0;
    Wt::WDate m_date;
    std::vector< DayWidget * > m_dayWidgets;

    Wt::WTemplate * m_templt = nullptr;
    Wt::WText     * m_prev   = nullptr;
    Wt::WText     * m_next   = nullptr;
    Wt::WText     * m_month  = nullptr;
    Wt::WText     * m_year   = nullptr;
    Wt::WTable    * m_table  = nullptr;

    Wt::Signal<> m_prevClicked;
    Wt::Signal<> m_nextClicked;

}; // endclass MiniMonth

    } // endnamespace Calendar
  } // endnamespace Web
} // endnamespace Wtx


#endif // end#ifndef __WTX_MINIMONTH_H___


