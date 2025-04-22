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

#ifndef __WTX_CALENDARWIDGET_H___
#define __WTX_CALENDARWIDGET_H___

namespace Wt {
  class WStackedWidget;
}

#include <Wtx/Addons/Web/Calendar/Database.h>
#include <Wtx/Addons/Web/Calendar/DayView.h>
#include <Wtx/Addons/Web/Calendar/WeekView.h>
#include <Wtx/Addons/Web/Calendar/MonthView.h>
#include <Wtx/Addons/Web/Calendar/YearView.h>

namespace Wtx {
  namespace Web {
    namespace Calendar {

/*!
** \brief Calendar Widget
**
*/
class Widget
: public Wt::WContainerWidget
{
    class ToolBar
    : public Wt::WContainerWidget
    {
      public:
        ToolBar();

        Wt::WPushButton * pbNew() const;
        Wt::WPushButton * pbToday() const;
        Wt::WPushButton * pbPrev() const;
        Wt::WPushButton * pbNext() const;
        Wt::WPushButton * pbFind() const;
        Wt::WComboBox   * cbView() const;
        Wt::WPushButton * pbSett() const;

      public:

        Wt::WText       * m_date    = nullptr;
        Wt::WPushButton * m_pbNew   = nullptr;
        Wt::WPushButton * m_pbToday = nullptr;
        Wt::WPushButton * m_pbPrev  = nullptr;
        Wt::WPushButton * m_pbNext  = nullptr;
        Wt::WPushButton * m_pbFind  = nullptr;
        Wt::WComboBox   * m_cbView  = nullptr;
        Wt::WPushButton * m_pbSett  = nullptr;
    };

    class SideBar
    : public Wt::WContainerWidget
    {
      public:
        SideBar( int firstDayOfWeek );

        Wt::WCalendar * calendar() const;

      private:

        Wt::WCalendar * m_calendar = nullptr;
    };

  public:

    enum View {
      DAY      = 0,
      WEEK     = 1,
      MONTH    = 2,
      YEAR     = 3,
      SCHEDULE = 4,
      FOURDAYS = 5,
      FIVEDAYS = 6,
      TABLE    = 7
    };

    /*!
    ** \brief ctor
    **
    ** Be sure to specify the first day of the week.  Possible
    **  values are 1 to 7. The default value is 1 ("Monday").
    **
    */
    Widget( int firstDayOfWeek, Database & database );

    Wtx::Web::Calendar::YearView  * yearView() const;
    Wtx::Web::Calendar::MonthView * monthView() const;
    Wtx::Web::Calendar::WeekView  * weekView() const;
    Wtx::Web::Calendar::DayView   * dayView() const;

    const Wt::WDate & selectedDate() const;
    void setSelectedDate( const Wt::WDate & date );

    void setView( int value );
    int view() const;

    ToolBar * toolBar() const;
    SideBar * sideBar() const;

    Wt::Signal<Wt::WDate>       & itemNew();
    Wt::Signal<Wt::WModelIndex> & itemClicked();
    Wt::Signal<Wt::WModelIndex> & itemDoubleClicked();

    void updateView();

    std::shared_ptr<Wt::WAbstractItemModel> getModel( const Wt::WDate & date, const std::vector<std::string> & fieldList );

  protected:

  private:

    void selectPrevious();
    void selectNext();

    Wt::WDate m_selectedDate;
    Wt::WTemplate * m_templt = nullptr;
    Wtx::Web::Calendar::YearView  * m_yearView  = nullptr;
    Wtx::Web::Calendar::MonthView * m_monthView = nullptr;
    Wtx::Web::Calendar::WeekView  * m_weekView  = nullptr;
    Wtx::Web::Calendar::DayView   * m_dayView   = nullptr;
    Wt::WStackedWidget * m_stack = nullptr;
    ToolBar * m_toolBar = nullptr;
    SideBar * m_sideBar = nullptr;

    Wt::Signal<Wt::WDate> m_itemNew;
    Wt::Signal<Wt::WModelIndex> m_itemClicked;
    Wt::Signal<Wt::WModelIndex> m_itemDoubleClicked;

    std::map< Wt::WDate, std::shared_ptr<Wt::WAbstractItemModel> > m_modelMaps;

    Database & m_database;

}; // endclass Widget

    } // endnamespace Calendar
  } // endnamespace Web
} // endnamespace Wtx


#endif // #ifndef __WTX_CALENDARWIDGET_H___


