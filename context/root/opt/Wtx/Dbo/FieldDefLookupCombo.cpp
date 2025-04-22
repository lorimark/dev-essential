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
#include <Wt/WComboBox.h>

#include <Wtx/Core/Core.h>
#include <Wtx/Util/Util.h>
#include <Wtx/Dbo/TableDef.h>

#include "FieldDefLookupCombo.h"

class SmartComboEdit
: public Wt::WComboBox
{
  public:

    SmartComboEdit( int sid, std::shared_ptr<Wt::WAbstractItemModel> (*getModel)(int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session), Wtx::Dbo::Session & s )
    : m_session(s),
      m_sourceID(sid),
      m_getModel(getModel)
    {
      setNoSelectionEnabled(true);
      changed().connect( this, &SmartComboEdit::on_changed );
      focussed().connect( this, &SmartComboEdit::on_focussed );

    } // endSmartLineEdit( std::shared_ptr<Wt::WAbstractItemModel> model, Wtx::Dbo::Session & s )

    /*
    ** this returns the ID value of the string
    **
    */
    int get_id( const std::string & value )
    {
      if( m_model )
      {
        for( int i=0; i < m_model-> rowCount(); i++ )
        {
          auto id = Wt::asNumber(m_model-> index( i, 0 ).data());
          auto ky = Wt::asString(m_model-> index( i, 1 ).data()).toUTF8();

          if( value == ky )
          {
            return id;
          }

        }
      }

      return -1;
    }

    /*
    ** this returns the string value of the ID
    **
    */
    std::string get_string( int index )
    {
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

      return "";
    }

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
    void loadModel( int id )
    {
      if( !m_loaded && m_getModel )
      {
        setNoSelectionEnabled(true);
        m_model = m_getModel( m_sourceID, id, "", m_session );
        setModel( m_model );
        setModelColumn(1);

        if( id == -1 )
          m_loaded = true;

#ifdef NEVER
        std::cout << __FILE__ << ":" << __LINE__
          << " Loading Model: " << id
          << " loaded: " << m_loaded
          << " " << m_sourceID << " " << m_targetID
          << std::endl;
#endif
      }
    }

    void on_focussed()
    {
      loadModel(-1);
      refresh();

//      for( int i=0; i< count(); i++ )
//        if( itemText(i) == m_valueText )
//          setCurrentIndex(i);

      setValueText( m_valueText );

    }

#ifndef NEVER
    /*
    ** this fires when the widget looses focus and the value in it
    **  is different than from when it started
    **
    */
    void on_changed()
    {
      auto value = Wt::WComboBox::valueText().toUTF8();

      if( value == "" )
      {
        m_targetID = -1;
        m_valueText = "";
        return;
      }

      m_targetID = get_id( value );
      m_valueText = value;

#ifdef NEVER
      auto dialog = addChild( std::make_unique<Wt::WDialog>() );
      dialog-> rejectWhenEscapePressed();
      dialog-> contents()-> addNew<Wt::WText>("cannot put in false data");
      dialog-> show();
#endif

    } // endvoid on_changed()
#endif


    Wt::WString valueText() const
    {
      auto retVal = Wt::WString("[null]");

      if( m_targetID != -1 )
        retVal = Wt::WString("{1}: {2}]").arg( m_table ).arg( m_targetID );

//      std::cout << __FILE__ << ":" << __LINE__ << " " << m_field << " " << retVal << std::endl;

      return retVal;
    }

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

      else
      {
        if( m_valueText.find(":") != std::string::npos )
        {
          auto v = Wtx::Core::split( m_valueText, ':' );
          m_table = v.at(0);
          m_targetID = std::stoi(v.at(1));
          loadModel(m_targetID);
          m_valueText = get_string( m_targetID );
        }

      }

#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__
        << "\n loaded:   " << m_loaded
        << "\n table:    " << m_table
        << "\n value:    " << value
        << "\n valueText:" << m_valueText
        << std::endl
        ;
#endif

      Wt::WComboBox::setValueText( m_valueText );

    } // endvoid setValueText( const Wt::WString & value )

    std::shared_ptr<Wt::WAbstractItemModel> (*m_getModel)(int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session) = nullptr;
    bool m_loaded = false;
    std::string m_field;
    std::string m_table;
    int m_sourceID = -1;
    int m_targetID = -1;
    std::string m_valueText;
    Wtx::Dbo::Session & m_session;
    std::shared_ptr<Wt::WAbstractItemModel> m_model;

}; // endclass SmartComboEdit

Wtx::Dbo::FieldDefLookupCombo::FieldDefLookupCombo
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

Wtx::Dbo::FieldDefLookupCombo::FieldDefLookupCombo
(
  TableDef &   td,
  const char * fn,
  std::string  lb,
  std::string  ph,
  std::string  inf,
  std::string  tt,
  int          ht
)
: Wtx::Dbo::FieldDefLookupBase( td, fn, lb, ph, inf, tt, ht )
{
}


std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefLookupCombo::createEditWidget( int sid, Wtx::Dbo::Session & session ) const
{
  auto retVal = std::make_unique< SmartComboEdit >( sid, getLookupModel, session );
  retVal-> m_table = "[" + targetTable;
  retVal-> m_field = fieldName();

  if( !m_lazyLoad )
    retVal-> on_focussed();

  return retVal;


}


