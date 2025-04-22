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

#ifndef __WTX_DBO_TABLEVIEW_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_TABLEVIEW_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Core/Core.h>
#include <Wt/Dbo/Query.h>
#include "QueryModel.h"

#include <Wtx/Dbo/Session.h>
#include <Wtx/Dbo/TableDef.h>
#include <Wtx/TableView.h>
#include <Wtx/TableViewDef.h>



namespace Wtx {
  namespace Dbo {

/*!
** \brief Dbo Table View
**
**
*/
template <class C>
class TableView
: public Wtx::TableView
{
  public:

    virtual ~TableView();
    TableView( Wtx::Dbo::Session * s );
    TableView( const std::string & viewDefName, Wtx::Dbo::Session * s );
    TableView( const Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s );
    TableView( const std::string & viewDefName, const Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s );

    bool loadLayout( const std::string & name );
    void saveLayout( const std::string & name );

    Wtx::Dbo::Session * session() const { return m_session; }

    const std::shared_ptr< Wtx::Dbo::QueryModel< Wt::Dbo::ptr<C> > > & model() const
    {
      return m_model;
    }

    virtual void showHeaderPopup( const Wt::WMouseEvent & event );
    std::string layoutName( const std::string & name ) const;

    void refresh();
    void refreshSelected();

    const std::string & filter() const;
    void setFilter();
    void setFilter( const std::string & filter );
    void setSearch( const std::string & search );
    void setSubFilter( const std::string & filter );

    const std::string & queryValue() const;
    void setQuery( const std::string & search = "" );

    void setupLayout();

    int queryRowCount() const
    {
      return m_queryRowCount;
    }

    int totalRowCount()
    {
      Wt::Dbo::Transaction t(*session());

      std::string filter;
      filter =
        "SELECT COUNT(id) FROM \""
        + std::string( session()-> template tableName<C>() ) + "\""
        ;

      if( viewDef().m_def.filter != "" )
        filter += " WHERE " + viewDef().m_def.filter;

//      std::cout << __FILE__ << ":" << __LINE__ << " " << filter << std::endl;

      int totalRows = -1;
      totalRows =
        session()->
        template query<int>( filter );

      return totalRows;
    }

    Wt::Dbo::ptr<C> item( Wt::WModelIndex index )
    {
      Wt::Dbo::ptr<C> retVal;

      if( index.isValid() )
      {
        retVal = model()-> stableResultRow( index.row() );
      }

      return retVal;

    }

    void selectItem( Wt::Dbo::ptr<C> item );

    Wt::Dbo::ptr<C> selectedItem();

  private:

    void on_keyPressed( Wt::WKeyEvent keyEvent );

    void init();
    void setLayout();

    std::string m_filterValue;
    std::string m_subFilterValue;
    std::string m_queryValue;
    bool colsSet = false;
    Wtx::Dbo::Session * m_session = nullptr;
    std::shared_ptr< Wtx::Dbo::QueryModel< Wt::Dbo::ptr<C> > > m_model;
    int m_queryRowCount = -1;

}; // endclass TableView

  } // endnamespace Dbo
} // endnamespace Wtx

#include "TableView_imp.h"

#endif // __WTX_DBO_TABLEVIEW_H___

