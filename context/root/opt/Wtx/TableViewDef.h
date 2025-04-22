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


#ifndef __WTX_TABLEVIEWDEF_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_TABLEVIEWDEF_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/WObject.h>
#include <Wt/WFormModel.h>
#include <Wt/WSignal.h>
#include <Wt/WLength.h>

#include <Wtx/Dbo/TableDef.h>

namespace Wtx {

extern Wt::WLength g_dialogWidth;
extern Wt::WLength g_dialogHeight;

namespace Dbo {
  class Session;
}

/*!
** \brief Table View Definition
**
** The Table View Definition objet encapsulates all the settings required to
**  build a table view.  In order to build a complete table view, some of the
**  settings must be applied to the data model, and some of the settings must
**  be applied to the table view itself.  This class brings all those settings
**  in to one location, so they can be easily manipulated by the application.
**
** The Table View Definition can be initialized through a number of methods;
**  manually, where each setting is applied one at a time, through a
**  Definition_t structure, where each value is specified in a statically
**  initialized structure, or through a Json string, where each value appears
**  similar to the static structure, but in Json format, making for easy
**  back-end storage.
**
** \code
** 252 Wtx::TableViewDef::Definition_t viewDef =
** 253 {
** 254    "Blog Entries",                // title
** 255    "",                            // tip
** 256    0,                             // headerCount
** 257    Wt::SelectionMode::Single,     // selectionMode
** 258    true,                          // columnResizeEnabled
** 259    true,                          // alternatingRowColors
** 260    "",                            // sql
** 261    "",                            // filter
** 261a   "",                            // idin (ID appears in this sql)
** 262    0,                             // doubleClick
** 263    true,                          // showHeader
** 264    true,                          // showFooter
** 264    false,                         // hideSearch
** 265    false,                         // allowFilter
** 266    false,                         // allowAdd
** 267    false,                         // allowChange
** 268    false,                         // allowDelete
** 269    true,                          // allowExport
** 270    true,                          // allowSearch
** 271    nullptr,                       // itemDelegate
** 272
** 273
** 274   // sortFields
** 275   {
** 276     "id DESC"
** 277   },
** 278
** 279   // search fields
** 280   {
** 281   },
** 282
** 283   // column defs
** 284   {// field           label  width  toolTip   delegate
** 285     { "id",           "",      50,  "",       nullptr  },
** 286     { "isActive",     "",      75,  "",       nullptr  },
** 287     { "datePosted",   "",     125,  "",       nullptr  },
** 288     { "keyField",     "",     350,  "",       nullptr  }
** 289   }
** 290
** 291 };
** \endcode
**
**
** To create the view, it is a simple matter of creating a new view
**  object, and applying the view layout definition to the constructor:
**
** \code
** auto tv = std::make_unique< Wtx::Dbo::TableView<Wtx::Web::BlogEntry::Item> >( viewDef, session() );
** \endcode
*/
class TableViewDef
: Wt::WObject
{

  public:

    /*!
    ** \brief Table View Column Def
    **
    ** This defines attributes related to the columns
    **  of table-views.  This includes the columnn name
    **  and then various other attributes such as alignment
    **  and width, tool tips, delegates, basically anything
    **  related to a column in a table.
    **
    */
    class ColumnDef
    {
      public:

        std::string field;
        std::string label;
        Wt::WLength width;
        Wt::AlignmentFlag alignment;
        std::string toolTip;
        Wt::WItemDelegate * (*delegate)( Wtx::Dbo::Session * );

        void editProperties();
    };

    /*!
    ** \brief Table View Definition
    **
    ** This class defines all the attributes of a table
    **  view.
    **
    */
    class ViewDef
    {
      public:
        std::string title;
        std::string tip;
        int rowHeaderCount;
        Wt::SelectionMode selectionMode;
        bool columnResizeEnabled;
        bool alternatingRowColors;
        std::string sql;
        std::string filter;
        std::string subFilter;
        std::vector<std::string> idin;
        void (*doubleClick)( Wt::WModelIndex, Wt::WMouseEvent );
        bool showHeader;
        bool showFooter;
        bool showPrevNext;
        bool hideSearch;
        bool allowFilter;
        bool allowAdd;
        bool allowChange;
        bool allowDelete;
        bool allowExport;
        bool allowSearch;
        bool allowPrint;
        bool allowUnlock;
        std::string additional;
        Wt::WItemDelegate * (*delegate)();

        std::vector<std::string> sortFields;
        std::vector<std::string> searchFields;
        std::vector<ColumnDef> columnDefs;
        std::vector<std::string> columnNames;

        /*
        ** these flags can do various things.  Such as,
        **  adding "show-sql" causes the table-view
        **  to show the generated sql output.
        **
        */
        std::vector<std::string> flags;

        bool checkBoxSelect;

        Wt::WLength m_dialogWidth  = Wtx::g_dialogWidth;
        Wt::WLength m_dialogHeight = Wtx::g_dialogHeight;

        std::string deleteMessage;
    };


    bool load( const std::string & name, const Wtx::Dbo::TableDef & tableDef, Wtx::Dbo::Session * session );
    bool load( const Wtx::Dbo::TableDef & tableDef, Wtx::Dbo::Session * session );
    bool load( const ViewDef & viewDef, Wtx::Dbo::Session * session );

    bool save( const std::string & name, Wtx::Dbo::Session * session );

    bool hasFlag( const std::string & value );

    void editProperties();

    std::string m_name;
    ViewDef m_def;

    Wt::Signal<> & changed() { return m_changed; }

  private:

    Wt::Signal<> m_changed;

}; // endclass TableViewDef

} // endnamespace Wtx

#endif // __WTX_TABLEVIEWDEF_H___

