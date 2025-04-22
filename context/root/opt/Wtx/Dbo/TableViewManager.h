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


#ifndef __WTX_DBO_TABLEVIEWMANAGER_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_TABLEVIEWMANAGER_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include "TableView.h"

namespace Wtx {

extern Wt::WLength g_dialogWidth;
extern Wt::WLength g_dialogHeight;

  namespace Dbo {

/*!
** \brief Dbo Table View
**
**
*/
template <class C, class D>
class TableViewManager
: public Wt::WContainerWidget
{

  public:

    class SearchWidget
    : public Wt::WContainerWidget
    {
      public:

        SearchWidget( bool autohide );

        void setFilter( const Wt::WString & value );
        void setSearch( const Wt::WString & value );

        void setToolTip( const Wt::WString & value );

        Wt::WHBoxLayout * lw() const { return m_lw; }

        Wt::WHBoxLayout * m_lw = nullptr;
        Wt::WLineEdit * m_filter = nullptr;
        bool m_autohide;
    };

    class FooterWidget
    : public Wt::WContainerWidget
    {
      public:

        FooterWidget();

        void setRowCount( int query, int total );
        void setQueryRowCount( int value );
        void setTotalRowCount( int value );

      private:

        void updateWidgets();

        int m_queryRowCount = 0;
        int m_totalRowCount = 0;

        Wt::WText * m_rowCounts = nullptr;
        Wt::WText * m_center = nullptr;
        Wt::WText * m_right = nullptr;
    };

    class PrevNextWidget
    : public Wt::WContainerWidget
    {
      public:

        PrevNextWidget();

        void setRow( int row, int rowCount );

        Wt::WText       * m_text   ;
        Wt::WPushButton * m_top    ;
        Wt::WPushButton * m_prev   ;
        Wt::WPushButton * m_next   ;
        Wt::WPushButton * m_bottom ;
    };

    TableViewManager( Wtx::Dbo::Session * s );
    TableViewManager( const std::string & viewDefName, Wtx::Dbo::Session * s );
    TableViewManager( const Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s );
    TableViewManager( const std::string & viewDefName, const Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s );

    Wtx::Dbo::TableView<C> * tableView() { return m_tableView; }

    const std::string & filter() const;
    Wtx::Dbo::Session * session() const { return m_session; }
    Wt::WVBoxLayout * lw() const { return m_lw; }
    SearchWidget * searchWidget() const { return m_searchWidget; }
    Wtx::Dbo::TableView<C> * tableView() const { return m_tableView; }

    void updateFooter();

    Wt::WContainerWidget * toolBar();
    Wt::WContainerWidget * buttonBar();

    /*!
    ** \brief Add
    **
    */
    Wt::Signal< typename C::Ptr > & addClicked()        { return m_addClicked        ; }
    Wt::Signal< typename C::Ptr > & deleteClicked()     { return m_deleteClicked     ; }
    Wt::Signal< typename C::Ptr > & itemClicked()       { return m_itemClicked       ; }
    Wt::Signal< typename C::Ptr > & doubleClicked()     { return m_doubleClicked     ; }
    Wt::Signal< typename C::Ptr > & editClicked()       { return m_editClicked       ; }
    Wt::Signal< typename C::Ptr > & itemSaved()         { return m_itemSaved         ; }
    Wt::Signal< std::string     > & exportClicked()     { return m_exportClicked     ; }
    Wt::Signal< std::string     > & printClicked()      { return m_printClicked      ; }
    Wt::Signal< std::string     > & additionalClicked() { return m_additionalClicked ; }

    std::unique_ptr<D> makeDetail( typename C::Ptr item );
    D * openDetail( Wt::WModelIndex index );
    D * openDetail( typename C::Ptr item );

    bool doSave( D * detail );
    void doClose( D * detail );

    void setReadOnly( bool value );

    Wt::WTemplate * buttonTemplt() { return m_buttonTemplt; }

    bool m_openDetail = true;

    Wt::WPushButton * m_pbAdd    = nullptr;
    Wt::WPushButton * m_pbEdit   = nullptr;
    Wt::WPushButton * m_pbDelete = nullptr;
    Wt::WPushButton * m_pbPrint  = nullptr;
    Wt::WPushButton * m_pbExport = nullptr;

    void setDialogSize( Wt::WLength width, Wt::WLength height );

  private:

    void initHead();
    void initFoot();

    void on_clicked( Wt::WModelIndex index, Wt::WMouseEvent event );
    void on_doubleClicked( Wt::WModelIndex index, Wt::WMouseEvent event );
    void on_keyPressed( Wt::WKeyEvent keyEvent );
    void on_keyWentDown( Wt::WKeyEvent keyEvent );
    void on_filterEntered();
    void on_filterTyped();
    void on_add_clicked();
    void on_edit_clicked();
    void do_on_delete_clicked() { on_delete_clicked(false); }
    void on_delete_clicked( bool noask );
    void on_export_clicked();
    void on_print_clicked();
    void on_additional_clicked();
    void on_unlock_clicked();

    Wt::WLength m_dialogWidth  = Wtx::g_dialogWidth  ;
    Wt::WLength m_dialogHeight = Wtx::g_dialogHeight ;

    Wt::WTemplate                 * m_buttonTemplt   = nullptr ;
    Wtx::Dbo::Session             * m_session        = nullptr ;
    Wt::WVBoxLayout               * m_lw             = nullptr ;
    Wtx::Dbo::TableView< C >      * m_tableView      = nullptr ;
    SearchWidget                  * m_searchWidget   = nullptr ;
    FooterWidget                  * m_footerWidget   = nullptr ;
    PrevNextWidget                * m_prevNextWidget = nullptr ;
    Wt::WContainerWidget          * m_toolBar        = nullptr ;
    Wt::WContainerWidget          * m_buttonBar      = nullptr ;
    Wt::Signal< typename C::Ptr >   m_itemClicked              ;
    Wt::Signal< typename C::Ptr >   m_addClicked               ;
    Wt::Signal< typename C::Ptr >   m_deleteClicked            ;
    Wt::Signal< typename C::Ptr >   m_doubleClicked            ;
    Wt::Signal< typename C::Ptr >   m_editClicked              ;
    Wt::Signal< typename C::Ptr >   m_itemSaved                ;
    Wt::Signal< std::string     >   m_exportClicked            ;
    Wt::Signal< std::string     >   m_printClicked             ;
    Wt::Signal< std::string     >   m_additionalClicked        ;

    bool m_readOnly = false;

}; // endclass TableViewManager

  } // endnamespace Dbo
} // endnamespace Wtx

#include "TableViewManager_imp.h"

#endif // __WTX_DBO_TABLEVIEWMANAGER_H___

