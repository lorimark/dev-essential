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

#include <Wt/WText.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WLineEdit.h>
//#include <Wt/WInPlaceEdit.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WTableView.h>
#include <Wt/WModelIndex.h>

#include <Wtx/Core/Core.h>
#include <Wtx/Util/Util.h>

#include "FieldDefLookupManager.h"

#ifdef NEVER
Wt::Signal<> & Wtx::Dbo::FieldDefLookupManager::TableLineEdit::pickered()
{
  return m_pickered;
}
#endif

namespace {

class TabLinEdi
: public Wt::WLineEdit
//: public Wt::WFormWidget
//: public Wtx::Dbo::FieldDefLookupManager::TableLineEdit
//: public Wt::WInPlaceEdit
{
  public:

    TabLinEdi
    (
     int sid,
     Wtx::Dbo::FieldDefLookupManager * fieldDef,
     Wtx::Dbo::Session & s
    )
    : m_session  ( s        ),
      m_sourceID ( sid      ),
      m_fieldDef ( fieldDef )
    {

      changed       ().connect( this, &TabLinEdi::on_changed       );
      focussed      ().connect( this, &TabLinEdi::on_focussed      );
      doubleClicked ().connect( this, &TabLinEdi::on_doubleClicked );
//      lineEdit()-> changed()  .connect( this, &TableLineEdit::on_changed  );
//      lineEdit()-> focussed() .connect( this, &TableLineEdit::on_focussed );

    } // endTabLinEdi()

    /*
    ** this is kind of crummy.  this is supposed to load
    **  the model, but if an .id. value is specified then
    **  its supposed to only load that id.  but if no .id.
    **  is specified (id==-1) then this is supposed to
    **  load the _whole_ model.  The idea being, it should
    **  not load the model until it's absolutely necessary.
    **  the concept is that we only need to load one item
    **  out of the model if we're just loading the widget.
    **  we only need 1 item to get the widget loaded, to
    **  convert the id number in to a string-value.  but
    **  if the user never selects this control, then there's
    **  no reason to load ALL the data, it just slows down
    **  the user interface. this is my best attempt at
    **  lazy-loading.
    **
    */
    void loadModel( int id, const std::string & filter )
    {
      if( !m_loaded && fieldDef() && fieldDef()-> provider() /* m_fieldDef-> getLookupModel */ )
      {
#ifdef NEVER
        std::cout << __FILE__ << ":" << __LINE__
          << " Loading Model id: " << id
          << " sid:" << m_sourceID
          << " tid:" << m_targetID
          << std::endl
          ;
#endif

        m_model = fieldDef()-> provider()-> model( m_sourceID, id, filter );

//        setModel( m_model );
//        setModelColumn(1);

//        std::cout << __FILE__ << ":" << __LINE__ << " " << (void*)m_model.get() << std::endl;
//        std::cout << __FILE__ << ":" << __LINE__ << " " << m_model-> rowCount() << std::endl;

        if( id == -1 )
          m_loaded = true;
      }
    }

    void on_doubleClicked()
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

    }

    void on_focussed()
    {
#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__
        << " " << m_sourceID
        << " " << m_targetID
        << " " << m_valueText
        << " " << m_toolTip
        << std::endl
        ;
#endif

      loadModel( -1, "" );

//      for( int i=0; i< count(); i++ )
//        if( itemText(i) == m_valueText )
//          setCurrentIndex(i);

      setValueText( m_valueText );

    }

//    void on_textInput()
//    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << Wt::WLineEdit::valueText() << std::endl;
//
//      if( !m_table )
//      {
//      }
//    }

    /*
    ** this fires when the widget looses focus and the value in it
    **  is different than from when it started
    **
    */
    void on_changed()
    {
      auto value = Wt::WLineEdit::valueText().toUTF8();
//      auto value = lineEdit()-> valueText().toUTF8();

      /*
      ** If the value is blank, then just zap the
      **  values from the system, so that it doesn't
      **  appear to be connected to anything.
      **
      */
      if( value == "" )
      {
        m_targetID = -1;
        m_valueText = "";
        return;
      }

      /*
      ** If the provider has not been provided then
      **  just quit.
      **
      */
      if( !provider() )
      {
        std::cout << __FILE__ << ":" << __LINE__ << " no provider!" << std::endl;
        return;
      }

      m_targetID = provider()-> find_id( value );

      std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << m_targetID << std::endl;

      if( m_targetID < 1 )
      {
        auto dialog = addChild( std::make_unique<Wt::WDialog>("item pickers") );
        dialog-> rejectWhenEscapePressed(true);
        dialog-> show();
        auto cw = dialog-> contents()-> addNew<Wt::WContainerWidget>();
        auto lw = std::make_unique<Wt::WVBoxLayout>();

        auto u_search = std::make_unique<Wt::WLineEdit>(value);
        auto search = u_search.get();
        search-> setDisabled(true);
        lw-> addWidget( std::move( u_search ) );

        if( fieldDef()-> getTableView )
        {
#ifdef NEVER
          std::cout << __FILE__ << ":" << __LINE__
            << " " << m_sourceID
            << " " << m_targetID
            << " " << search-> valueText().toUTF8()
            << std::endl
            ;
#endif

          auto u_table = fieldDef()-> getTableView( m_sourceID, m_targetID, search-> valueText().toUTF8(), m_session );
          auto table = u_table.get();

          /*
          ** make sure we actually ended up with a table-view
          **
          */
          if( table )
          {
            table-> doubleClicked().connect( dialog, &Wt::WDialog::accept );
            lw-> addWidget( std::move( u_table ), 1 );

            auto u_select = std::make_unique<Wt::WPushButton>("select");
            u_select-> clicked().connect( dialog, &Wt::WDialog::accept );
            lw-> addWidget( std::move( u_select ) );

            dialog-> finished().connect( [=]( Wt::DialogCode code )
            {
              /*
              ** he must hit the 'select' button
              **
              */
              if( dialog-> result() != Wt::DialogCode::Accepted )
                return;

              /*
              ** at most/least one row must be selected
              **
              */
              if( table-> selectedIndexes().size() != 1 )
                return;

              auto index = *table-> selectedIndexes().begin();

              m_targetID = Wt::asNumber( index.data() );
#ifdef NEVER
              std::cout << __FILE__ << ":" << __LINE__
                << " " << index.row()
                << " " << index.column()
                << " " << m_targetID
                << std::endl
                ;
#endif
              setValueText( provider()-> get_string(  m_targetID ) );

//              m_pickered.emit();

            }); // enddialog-> finished().connect( [=]( Wt::DialogCode code )

          }

          /*
          ** even though we asked for a table-vew, we could not get one
          **  so alert the user.
          **
          */
          else
          {
            lw-> addWidget
            (
             std::make_unique<Wt::WText>
             (
              Wt::WString("FieldDefLookupTable.cpp:{1} 'getTableView' not returning view '{2}'")
              .arg( __LINE__ )
              .arg( m_field )
             )
            );

          }

        }

        else // if( !m_getTableView )
        {
          lw-> addWidget
          (
           std::make_unique<Wt::WText>
           (
            Wt::WString("FieldDefLookupTable.cpp:{1} 'getTableView' not set '{2}'")
            .arg( __LINE__ )
            .arg( m_field )
           )
          );
        }

        auto u_cancel = std::make_unique<Wt::WPushButton>("cancel");
        u_cancel-> clicked().connect( dialog, &Wt::WDialog::reject );
        lw-> addWidget( std::move( u_cancel ) );

        cw-> setLayout( std::move(lw) );

      } // endif( m_targetID == -1 )

      else
      {
        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

        setValueText( provider()-> get_string(  m_targetID ) );
        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

        setToolTip(   provider()-> get_toolTip( m_targetID ) );
      }

#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__
        << "\n targetID: " << m_targetID
        << "\n valueText: " << m_valueText
        << std::endl
        ;
#endif

#ifdef NEVER
      auto dialog = addChild( std::make_unique<Wt::WDialog>() );
      dialog-> rejectWhenEscapePressed();
      dialog-> contents()-> addNew<Wt::WText>("cannot put in false data");
      dialog-> show();
#endif

//      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

    } // endvoid on_changed()


    Wt::WString valueText() const
    {
      auto retVal = Wt::WString("[null]");

      if( m_targetID != -1 )
        retVal = Wt::WString("{1}: {2}]").arg( m_table ).arg( m_targetID );

#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__ << "::" << __FUNCTION__ << "()"
        << "\n m_loaded:   " << m_loaded
        << "\n m_field:    " << m_field
        << "\n m_table:    " << m_table
        << "\n m_sourceID: " << m_sourceID
        << "\n m_targetID: " << m_targetID
        << "\n retVal:     " << retVal
        << std::endl
        ;
#endif

      return retVal;

    } // endWt::WString valueText() const

    void setValueText( const Wt::WString & value )
    {
      m_valueText = value.toUTF8();

#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
        << " " << m_valueText
        << std::endl
        ;
#endif

      /*
      ** if the value text is nothing, then wipe
      **  it so that nothing shows.
      **
      */
      if( m_valueText == "[null]" )
          m_valueText = "";

      else
      {
        if( m_valueText.find(":") != std::string::npos )
        {
#ifdef NEVER
          std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << " " << m_valueText << std::endl;
#endif

          auto v = Wtx::Core::split( m_valueText, ':' );
          m_table = v.at(0);
          m_targetID = std::stoi(v.at(1));
          loadModel( m_targetID, "" );

          if( fieldDef()-> provider() )
          {
            m_valueText = fieldDef()-> provider()-> get_string(  m_targetID );
            m_toolTip   = fieldDef()-> provider()-> get_toolTip( m_targetID );
          }

        } // endif( m_valueText.find(":") != std::string::npos )

      } // endif( m_valueText != "[null]" )

      Wt::WLineEdit::setValueText( m_valueText );
      Wt::WLineEdit::setToolTip(   m_toolTip   );
//      lineEdit()-> setValueText( m_valueText );
//      lineEdit()-> setToolTip(   m_toolTip   );

#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
        << "\n loaded:   " << m_loaded
        << "\n sourceID: " << m_sourceID
        << "\n targetID: " << m_targetID
        << "\n table:    " << m_table
        << "\n value:    " << value
        << "\n valueText:" << m_valueText
        << "\n valueText:" << Wt::WLineEdit::valueText()
//        << "\n valueText:" << lineEdit()-> valueText()
        << "\n toolTip:  " << m_toolTip
        << std::endl
        ;
#endif

    } // endvoid setValueText( const Wt::WString & value )

    Wtx::Dbo::FieldDefLookupManager * fieldDef() { return m_fieldDef; }
    Wtx::Dbo::FieldDefLookupBase::Provider * provider() { return fieldDef()-> provider(); }

    Wtx::Dbo::FieldDefLookupManager * m_fieldDef = nullptr;
    bool m_loaded = false;
    std::string m_field;
    std::string m_table;
    int m_sourceID = -1;
    int m_targetID = -1;
    std::string m_valueText;
    std::string m_toolTip;
    Wtx::Dbo::Session & m_session;
    std::shared_ptr<Wt::WAbstractItemModel> m_model = nullptr;

}; // endclass TableLineEdit

} // endnamespace {

Wtx::Dbo::FieldDefLookupManager::FieldDefLookupManager
(
 TableDef & td,
 const char * fn,
 int w,
 int h,
 Flags f,
 std::string lb,
 std::string ph,
 std::string inf,
 std::string tt,
 int ht
)
: Wtx::Dbo::FieldDefLookupBase( td, fn, w, w, f, lb, ph, inf, tt, ht )
{

}

Wtx::Dbo::FieldDefLookupManager::FieldDefLookupManager
(
 TableDef & td,
 const char * fn,
 std::string lb,
 std::string ph,
 std::string inf,
 std::string tt,
 int ht
)
: Wtx::Dbo::FieldDefLookupBase( td, fn, lb, ph, inf, tt, ht )
{

}

std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefLookupManager::createEditWidget( int sid, Wtx::Dbo::Session & session ) const
{
//  std::cout << __FILE__ << ":" << __LINE__
//    << "\n sid: " << sid
//    << std::endl
//    ;


  if( !m_provider )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << fieldName() << ": " << "Model provider not set" << std::endl;
  }


//  auto retVal = std::make_unique< TableLineEdit >( sid, getLookupModel, getTableView, session );
  auto retVal = std::make_unique< TabLinEdi >( sid, const_cast<Wtx::Dbo::FieldDefLookupManager*>(this), session );
  retVal-> m_table = "[" + targetTable;
  retVal-> m_field = fieldName();

  return retVal;

}



