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

#ifndef __WTX_CALENDARMODELPROVIDER_H___
#define __WTX_CALENDARMODELPROVIDER_H___

#include <Wt/WObject.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WDate.h>

namespace Wtx {
  namespace Web {
    namespace Calendar {

/*!
** \brief Calendar Model Provider
**
** This class should be sub-classed by the application.  It is used to
**  provide for a model for the calendar, and it also provides field-mapping
**  to the model, such that foreign models can be employed, and field
**  mappings from the source model to the calendar model can be given.
**
**
*/
class ModelProvider
: public Wt::WObject
{
  public:

    ModelProvider
    (
      const std::string & name,
      const std::string & dateStart = "dateStart",
      const std::string & dateEnd   = "dateEnd",
      const std::string & timeStart = "timeStart",
      const std::string & timeEnd   = "timeEnd",
      const std::string & subject   = "subject",
      const std::string & body      = "body"
    );

    virtual std::shared_ptr<Wt::WAbstractItemModel> getModel( const Wt::WDate & date, const std::vector<std::string> & fieldList );

    const std::string & name() const;
    const std::string & dateStart() const;
    const std::string & dateEnd() const;
    const std::string & timeStart() const;
    const std::string & timeEnd() const;
    const std::string & subject() const;
    const std::string & body() const;

    void setMapping
    (
      const std::string & dateStart,
      const std::string & dateEnd,
      const std::string & timeStart,
      const std::string & timeEnd,
      const std::string & subject,
      const std::string & body
    );

  protected:

  private:

    std::string m_name;
    std::string m_dateStart;
    std::string m_dateEnd;
    std::string m_timeStart;
    std::string m_timeEnd;
    std::string m_subject;
    std::string m_body;

}; // endclass ModelProvider

    } // endnamespace Calendar
  } // endnamespace Web
} // endnamespace Wtx


#endif // end#ifndef __WTX_CALENDARMODELPROVIDER_H___


