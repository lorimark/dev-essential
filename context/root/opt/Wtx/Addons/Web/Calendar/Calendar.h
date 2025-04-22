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

#ifndef __WTX_CALENDAR_H___
#define __WTX_CALENDAR_H___

#include <vector>
#include <string>
#include <memory>

namespace Wt {
  class WAbstractItemModel;
  class WDate;
}

namespace Wtx {
  namespace Web {

    /*!
    ** \brief Calendar
    **
    ** This package contains the codes necessary to present to the user
    **  a fully-functional model-driven calendar widget.
    **
    ** \image html WtxWebCalendarMonthView.png
    **
    */
    namespace Calendar {

/*!
** \brief Calendar Result Set
**
** This result set is what should be provided by the model
**  fetchers.
**
*/
typedef std::tuple
<
  std::string, // class
  std::string, // source
  int,         // item-id
  Wt::WDate,   // dateStart
  Wt::WDate,   // dateStop
  Wt::WTime,   // timeStart
  Wt::WTime,   // timeStop
  std::string, // subject
  std::string  // body
> ResultSet;

/*!
** \brief Long Day Names
**
** This is a list of day-names used on the calendar displays.  This is the
**  long (more-than-three-letter) day names.  If you want the 3-letter
**  day names, just trim the result value like this:
**
** \code
**  daynames().at(3).substr(0,3);
** \endcode
**
*/
const std::vector<std::string> & daynames();

    } // endnamespace Calendar {
  } // endnamespace Web {
} // endnamespace Wtx {


#endif


