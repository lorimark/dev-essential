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

#include <Wt/WAbstractItemModel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WText.h>

#include <Wtx/Core/Core.h>
#include <Wtx/Util/Util.h>

#include "FieldDefLookupSuggest.h"

Wtx::Dbo::FieldDefLookupSuggest::FieldDefLookupSuggest
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


class SmartSuggest
: public Wt::WSuggestionPopup
{
  public:

    SmartSuggest( const Wt::WSuggestionPopup::Options & options )
    : Wt::WSuggestionPopup( options )
    {
    }


}; // endclass SmartSuggest

class SmartLineEdit
: public Wt::WLineEdit
{
  public:

    void setEdit()
    {
#ifdef NEVER
      EventSignalBase& b = edit->keyPressed();

      connectObjJS(b, "editKeyDown");
      connectObjJS(edit->keyWentDown(), "editKeyDown");
      connectObjJS(edit->keyWentUp(), "editKeyUp");
      connectObjJS(edit->blurred(), "delayHide");

      if (triggers.test(PopupTrigger::Editing))
        edit->addStyleClass("Wt-suggest-onedit");

      if (triggers.test(PopupTrigger::DropDownIcon)) {
        edit->addStyleClass("Wt-suggest-dropdown");
        EventSignalBase& c = edit->clicked();
        connectObjJS(c, "editClick");
        connectObjJS(edit->mouseMoved(), "editMouseMove");
      }
#endif

    }


    SmartLineEdit( int sid, std::shared_ptr<Wt::WAbstractItemModel> (*getModel)(int sid,int tid,const std::string & filter,Wtx::Dbo::Session & session), Wtx::Dbo::Session & s )
    : m_session(s),
      m_sourceID(sid),
      m_getModel(getModel)
    {
      changed().connect( this, &SmartLineEdit::on_changed );
      textInput().connect( this, &SmartLineEdit::on_textInput );

      setAutoComplete( false );

    } // endSmartLineEdit( std::shared_ptr<Wt::WAbstractItemModel> model, Wtx::Dbo::Session & s )

    void setPopup()
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

//      m_model = m_getModel( m_sourceID, m_targetID, "", m_session );

      if( !m_model )
        return;

      if( m_popup )
        return;

      if( m_model-> rowCount() < 100 )
      {
        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

        Wt::WSuggestionPopup::Options options =
        {
          "<b>",         // highlightBeginTag
          "</b>",        // highlightEndTag
          0,             // listSeparator      (for multiple addresses)
          " \\n",        // whitespace
          "-., \"@\\n;", // wordSeparators     (within an address)
          ""             // appendReplacedText (prepare next email address)
        };

        if( m_popup )
          removeChild( m_popup );

        m_popup = addChild( std::make_unique<Wt::WSuggestionPopup>( options ) );
        m_popup-> forEdit( this /*, Wt::PopupTrigger::DropDownIcon */ );

        m_popup-> setModel( m_model );
        m_popup-> setModelColumn(1);
//        popup-> setFilterLength(3);

        m_popup-> activated().connect( [=]( int index, Wt::WFormWidget * widget )
        {
        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

          m_targetID  = Wt::asNumber( m_model-> index( index, 0 ).data() );
          m_valueText = Wt::asNumber( m_model-> index( index, 1 ).data() );

        });

      } // endif( m_model-> rowCount() < 100 )
    }

    /*
    ** this returns the ID value of the string
    **
    */
    int get_id( const std::string & value )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << value << std::endl;

      if( m_model )
      {
        std::cout << __FILE__ << ":" << __LINE__
          << " " << m_model-> rowCount()
          << std::endl
          ;

        for( int i=0; i < m_model-> rowCount(); i++ )
        {
          auto id = Wt::asNumber(m_model-> index( i, 0 ).data());
          auto ky = Wt::asString(m_model-> index( i, 1 ).data()).toUTF8();

          std::cout << __FILE__ << ":" << __LINE__ << " " << ky << std::endl;

          if( value == ky )
          {
            return id;
          }

        }
      }

      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      return -1;
    }

    /*
    ** this returns the string value of the ID
    **
    */
    std::string get_string( int index )
    {
      std::cout << __FILE__ << ":" << __LINE__
        << "\n field: " << m_field
        << "\n index: " << index
        << "\n model: " << (void*)m_model.get()
        << std::endl;

      if( m_model && index > -1 )
      {
        for( int i=0; i < m_model-> rowCount(); i++ )
        {
          auto id = Wt::asNumber(m_model-> index( i, 0 ).data());
          auto ky = Wt::asString(m_model-> index( i, 1 ).data()).toUTF8();

          if( index == id )
          {
            return ky;
          }

        }

      }

      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      return "";
    }

    /*
    ** this fires when the widget looses focus and the value in it
    **  is different than from when it started
    **
    */
    void on_textInput()
    {
      auto value = Wt::WLineEdit::valueText().toUTF8();

      if( !m_model )
      {
        m_model = m_getModel( m_sourceID, -1, value, m_session );
        setPopup();
      }

      std::cout << __FILE__ << ":" << __LINE__
        << "\n value:" << value
        << "\n targetID:" << m_targetID
        << "\n valueText:" << m_valueText
        << "\n model rows:" << m_model-> rowCount()
        << std::endl
        ;

    }

    void on_changed()
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      auto value = Wt::WLineEdit::valueText().toUTF8();

      if( value == "" )
      {
        m_targetID = -1;
        m_valueText = "";
        if( m_popup )
        {
          removeChild( m_popup );
          m_popup = nullptr;
        }

        return;
      }

      m_targetID = get_id( value );
      m_valueText = value;

      std::cout << __FILE__ << ":" << __LINE__
        << "\n targetID:" << m_targetID
        << "\n valueText:" << m_valueText
        << "\n model rows:" << m_model-> rowCount()
        << std::endl
        ;

#ifdef NEVER
      auto dialog = addChild( std::make_unique<Wt::WDialog>() );
      dialog-> rejectWhenEscapePressed();
      dialog-> contents()-> addNew<Wt::WText>("cannot put in false data");
      dialog-> show();
#endif

    } // endvoid on_changed()


    Wt::WString valueText() const
    {
      auto retVal = Wt::WString("[null]");

      if( m_targetID != -1 )
        retVal = Wt::WString("{1}: {2}]").arg( m_table ).arg( m_targetID );

      std::cout << __FILE__ << ":" << __LINE__
        << "\n field" << m_field
        << "\n retVal" << retVal
        << std::endl
        ;

      return retVal;
    }

    /*
    ** this will set the value text
    **
    ** note that the value text comes in as a string, but the
    **  string represents the item using the following format:
    **
    ** "[tableName: itemNumber]"
    **
    ** Therefore, the item can be located by referencing the
    **  table name, and extracting the item number that is
    **  following the colon.
    **
    **
    */
    void setValueText( const Wt::WString & value )
    {
      m_valueText = value.toUTF8();

      /*
      ** if the value text is nothing, then wipe
      **  it so that nothing shows.
      **
      */
      if( m_valueText == "[null]" )
          m_valueText = "";

      /*
      ** the value text is something, so extract the
      **  numeric from it and see if we can fetch the
      **  _actual_ value text that should be in the
      **  text editor.
      **
      */
      else
      {
        if( m_valueText.find(":") != std::string::npos )
        {
          auto v = Wtx::Core::split( m_valueText, ':' );
          m_table = v.at(0);
          m_targetID = std::stoi(v.at(1));
          m_model = m_getModel( m_sourceID, m_targetID, "", m_session );
          m_valueText = get_string( m_targetID );
        }
      }

      /*
      ** update the text edit field
      **
      */
      Wt::WLineEdit::setValueText( m_valueText );

    } // endvoid setValueText( const Wt::WString & value )

    std::string m_field;
    std::string m_table;
    int m_sourceID = -1;
    int m_targetID = -1;
    std::string m_valueText;
    Wtx::Dbo::Session & m_session;
    std::shared_ptr<Wt::WAbstractItemModel> (*m_getModel)(int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session) = nullptr;
    std::shared_ptr<Wt::WAbstractItemModel> m_model = nullptr;
    Wt::WSuggestionPopup * m_popup = nullptr;

}; // endclass SmartLineEdit


std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefLookupSuggest::createEditWidget( int sid, Wtx::Dbo::Session & session ) const
{
  auto retVal = std::make_unique<SmartLineEdit>( sid, getLookupModel, session );

  retVal-> m_field = fieldName();

  return retVal;

} // endstd::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefLookupSuggest::createEditWidget( int sid, Wtx::Dbo::Session & session ) const

