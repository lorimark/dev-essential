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

#ifndef __WTX_CALENDARITEM_H___
#define __WTX_CALENDARITEM_H___

#include <Wt/WDate.h>
#include <Wt/WTime.h>
#include <Wt/Dbo/Dbo.h>

namespace Wtx {
  namespace Web {
    namespace Calendar {

class Item
: public Wt::Dbo::Dbo<Item>
{
  public:

    template <class Action> void persist( Action & a )
    {
      Wt::Dbo::field( a, source,    "source"    );
      Wt::Dbo::field( a, dateStart, "dateStart" );
      Wt::Dbo::field( a, dateStop,  "dateStop"  );
      Wt::Dbo::field( a, timeStart, "timeStart" );
      Wt::Dbo::field( a, timeStop,  "timeStop"  );
      Wt::Dbo::field( a, subject,   "subject"   );
      Wt::Dbo::field( a, body,      "body"      );
    }

    std::string source;
    Wt::WDate dateStart;
    Wt::WDate dateStop;
    Wt::WTime timeStart;
    Wt::WTime timeStop;
    std::string subject;
    std::string body;

  protected:

  private:

}; // endclass Item

    } // endnamespace Calendar
  } // endnamespace Web
} // endnamespace Wtx

DBO_EXTERN_TEMPLATES(Wtx::Web::Calendar::Item);

#endif // #ifndef __WTX_CALENDARITEM_H___


