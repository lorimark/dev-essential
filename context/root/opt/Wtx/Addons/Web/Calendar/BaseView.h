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

#ifndef __WTX_CALENDARBASEVIEW_H___
#define __WTX_CALENDARBASEVIEW_H___

#include <Wt/WModelIndex.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>

namespace Wtx {
  namespace Web {
    namespace Calendar {

class Widget;
class BaseView
: public Wt::WContainerWidget
{
  public:

    BaseView( int firstDayOfWeek, Wtx::Web::Calendar::Widget * widget );

    virtual void setSelectionMode( Wt::SelectionMode mode );
    virtual void browseToPreviousYear();
    virtual void browseToPreviousMonth();
    virtual void browseToNextYear();
    virtual void browseToNextMonth();
    virtual void browseTo( const Wt::WDate & date );
    int currentDay() const;
    int currentMonth() const;
    int currentYear() const;
    virtual void clearSelection();
    virtual void select( const Wt::WDate & date );
    virtual void select( const std::set< Wt::WDate > & dates );
    virtual void setFirstDayOfWeek( int dayOfWeek );
    virtual const std::set< Wt::WDate > selection() const;
    virtual Wt::Signal<> & selectionChanged();
    virtual Wt::Signal< Wt::WDate > & activated();
    virtual Wt::Signal< Wt::WDate > & clicked();
    virtual Wt::Signal< int, int > & currentPageChanged();
    virtual void setSingleClickSelect( bool single );
    virtual void setBottom( const Wt::WDate & bottom );
    virtual const Wt::WDate bottom() const;
    virtual void setTop( const Wt::WDate & top );
    virtual const Wt::WDate top() const;

    const Wt::WDate & selectedDate() const;
    virtual void setSelectedDate( const Wt::WDate & date );

    Wtx::Web::Calendar::Widget * widget();

    std::shared_ptr<Wt::WAbstractItemModel> getModel( const Wt::WDate & date, const std::vector<std::string> & fieldList );

  protected:

  private:

    int m_firstDayOfWeek = 1;
    Wtx::Web::Calendar::Widget * m_widget = nullptr;
    Wt::WDate m_selectedDate;
    Wt::Signal<> m_selectionChanged;
    Wt::Signal< Wt::WDate > m_activated;
    Wt::Signal< Wt::WDate > m_clicked;
    Wt::Signal< int, int > m_currentPageChanged;

}; // endclass BaseView

    } // endnamespace Calendar
  } // endnamespace Web
} // endnamespace Wtx


#endif // #ifndef __WTX_CALENDARBASEVIEW_H___


