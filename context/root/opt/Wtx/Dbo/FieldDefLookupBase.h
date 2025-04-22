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

#ifndef __WTX_DBO_FIELDDEFLOOKUPBASE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_FIELDDEFLOOKUPBASE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Dbo/QueryModel.h>

#include "FieldDefBase.h"

namespace Wtx {
  namespace Dbo {

/*!
** \brief Single-line Editor
**
**
*/
class FieldDefLookupBase
: public Wtx::Dbo::FieldDefBase
{
  public:

#ifdef NEVER
    class Dialog
    : public Wt::WDialog
    {
      public:

        Dialog();

        int m_selectedId = -1;
    };
#endif

    class Provider
    {
      public:

        typedef std::shared_ptr< Wtx::Dbo::QueryModel< std::tuple<int,std::string> > > Model;

        virtual int find_id( const std::string & value );
        virtual std::string get_string( int id );
        virtual std::string get_toolTip( int id );

        virtual std::shared_ptr< Wt::WAbstractItemModel > model( int sid, int tid, const std::string & filter );

        virtual std::unique_ptr<Wt::WTableView> getTableView( int sid, int tid, const std::string & filter );

    };

    /*!
    ** \brief ctor
    **
    **
    */
    FieldDefLookupBase
    (
      TableDef &   td,                /// owning table definition (ro required)
      const char * fn,                /// field name (ro required)
      int          w   = -1,          /// width
      int          h   = -1,          /// height
      Flags        f   = Flags::None, /// flags
      std::string  lb  = "",          /// label
      std::string  ph  = "",          /// placeholder text
      std::string  inf = "",          /// info
      std::string  tt  = "",          /// tooltipText
      int          ht  = -1           /// help topic
    );

    FieldDefLookupBase
    (
      TableDef &   td,                /// owning table definition (ro required)
      const char * fn,                /// field name (ro required)
      std::string  lb  = "",          /// label
      std::string  ph  = "",          /// placeholder text
      std::string  inf = "",          /// info
      std::string  tt  = "",          /// tooltipText
      int          ht  = -1           /// help topic
    );

    Provider * provider() { return m_provider.get(); }

    /*!
    ** \brief create a look-up model
    **
    ** some of the widgets can employ a lookup-model.  This is used to
    **  fill in some of the field values, for combo-boxes and suggestion-boxes
    **  and so on.
    **
    ** the lookup-model is a model based on some other table connection.  the
    **  resulting model values can depend on a source-id (sid) and a target-id (tid).
    **
    ** for instance, a model can be a simple combo-box look-up value, such as,
    **  "all items from look-up table that contain 'container' as a group".  Another
    **  model could contain all "products for customer X".  In this case, it is
    **  necessary to generate a model as a list of things connected to something
    **  else.  in this case the customer is sent as the 'sid' value, and the
    **  creator will generate a model that contains all products for customer 'sid'.,
    **
    ** the target-id (tid) value is used when only that one item should be returned
    **  in the model.  This is used in cases where a form is being pre-loaded, and it
    **  is not necessary to load _every_ item for the model.  This will be an attempt
    **  at lazy loading.  When the edit field receives focus, then the call to create
    **  the model will be re-engaged so that _all_ the items out of the model can
    **  be acquired.
    **
    ** The .sid. and .tid. values are not necessarily required by the model creator,
    **  but they are provided in case they are needed.
    **
    ** \param sid source-id
    ** \param tid target-id
    ** \param session session controller
    **
    ** \code
    **  60 //
    **  61 // this function creates a model for looking
    **  62 //  up a company.  it does not use the .sid. or .tid. values.
    **  63 //
    **  68 std::shared_ptr<Wt::WAbstractItemModel> getCompanyModel( int sid, int tid, Wtx::Dbo::Session & session )
    **  69 {
    **  70   auto retVal = std::make_shared< Wtx::Dbo::QueryModel< std::tuple<int,std::string> > >();
    **  71
    **  72   Wt::Dbo::Transaction t(session);
    **  73
    **  80   auto query =
    **  81    session.query< std::tuple<int,std::string> >( "SELECT id,\"keyField\" || ' ~ ' || \"cfyField\" AS key FROM \"crmCompany\"" )
    **  82    .where("id in (select distinct \"forOwner_crmCompany_id\" from \"mrpProduct\")")
    **  83    ;
    **  85
    **  86   retVal-> setQuery( query );
    **  87   retVal-> addColumn("id");
    **  88   retVal-> addColumn("key");
    **  89
    **  90   return retVal;
    **  91 }
    **  92
    **  95 Mrp::Product::Definition::Definition()
    **  96 : Wtx::Dbo::PermissionTableDef("mrpProduct"),
    **  97   ProductNumberFieldDef( *this, "productNumber"       ),
    ** 111   TaxAuthFieldDef(       *this, "taxAuth"             ),
    ** 131   NoteFieldDef(          *this, "note"                ),
    ** 132   WarnFieldDef(          *this, "warn"                ),
    ** 134   Cost1FieldDef(         *this, "cost1"               ),
    ** 135   Cost10FieldDef(        *this, "cost10"              ),
    ** 136   Cost100FieldDef(       *this, "cost100"             ),
    ** 147   LotTrackingFieldDef(   *this, "lotTracking"         ),
    ** 148   LotNumberFieldDef(     *this, "lotNumber"           ),
    ** 150   ForOwnerFieldDef(      *this, "forOwner_crmCompany" ),
    ** 151 {
    ** 192   ForOwnerFieldDef.setLabel("Owner");
    ** 193   ForOwnerFieldDef.getLookupModel = &getCompanyModel;
    ** 194   ForOwnerFieldDef.setIsReadOnly();
    ** \endcode
    **
    */
    std::shared_ptr<Wt::WAbstractItemModel> (*getLookupModel)( int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session ) = nullptr;

    std::unique_ptr<Wt::WTableView> (*getTableView)( int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session ) = nullptr;

    std::unique_ptr<Provider> m_provider;

}; // endclass Wtx::Dbo::FieldDefLookupBase

  } // endnamespace Dbo
} // endnamespace Wtx

#endif // #ifndef __WTX_DBO_FIELDDEFLOOKUPBASE_H___

