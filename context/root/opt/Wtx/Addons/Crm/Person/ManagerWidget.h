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


#ifndef __WTX_CRM_PERSON_MANAGERWIDGET_H_f18dd848_80c3_437a_b635_39c58b1f521c__
#define __WTX_CRM_PERSON_MANAGERWIDGET_H_f18dd848_80c3_437a_b635_39c58b1f521c__

#include <Wt/Dbo/ptr.h>
#include <Wt/WCompositeWidget.h>

#include <Wtx/Dbo/Session.h>
#include <Wtx/TableViewDef.h>
#include <Wtx/Dbo/TableView.h>
#include <Wtx/Addons/Crm/Person/Item.h>

namespace Wtx {
  namespace Crm {
    namespace Person{

class Item;
class Desktop;
class ManagerWidget
: public Wt::WCompositeWidget
{
  public:

    ManagerWidget( Wtx::Dbo::Session * session );
    ManagerWidget( Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * session );

    void setFilter( const std::string & value );
    void clearFilter();
    void openDetail( Wt::Dbo::ptr<Wtx::Crm::Person::Item> & item );

    void setOpenDetail( bool value );

    Wt::Signal< Wtx::Crm::Person::Item::Ptr > & clicked();

    Wt::Signal< Wtx::Crm::Person::Item::Ptr > & doubleClicked();

    Wt::Signal< Wtx::Crm::Person::Item::Ptr > & addClicked();

    Wt::Signal< std::string > & additionalClicked();

    Wtx::Dbo::TableView< Wtx::Crm::Person::Item > * tableView();

  private:

    Desktop * m_desktop;

}; // endclass ManagerWidget

    } // endnamespace Person
  } // endnamespace Crm
} // endnamespace Wtx

#endif // #ifndef __WTX_CRM_PERSON_MANAGERWIDGET_H___


