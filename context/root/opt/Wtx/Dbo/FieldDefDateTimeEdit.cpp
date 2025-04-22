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

#include <Wt/WEvent.h>
#include <Wt/WLineEdit.h>
#include <Wt/WRegExpValidator.h>

#include <Wtx/Util/Util.h>
#include <Wtx/Wtx.h>

#include "FieldDefDateTimeEdit.h"

Wtx::Dbo::FieldDefDateTimeEdit::FieldDefDateTimeEdit
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
: Wtx::Dbo::FieldDefBase( td, fn, w, w, f, lb, ph, inf, tt, ht )
{
}

/*
** This object incorporates features such as forceUppercase() and
**  so on.
**
*/
class SmartLineEdit
: public Wt::WLineEdit
{
    void init()
    {
      /*
      ** only hook force-uppercase if it's been asked for.
      **
      */
      if( m_fieldDef.forceUppercase() )
      {
        Wt::WLineEdit::blurred().connect( this, &SmartLineEdit::on_blurred );
      }

      setAutoComplete( false );
    }

  public:

    SmartLineEdit( const Wtx::Dbo::FieldDefBase & fieldDef )
    : Wt::WLineEdit(),
      m_fieldDef(fieldDef)
    {
      init();
    }

    SmartLineEdit( const Wtx::Dbo::FieldDefBase & fieldDef, const Wt::WString & content )
    : Wt::WLineEdit(content),
      m_fieldDef(fieldDef)
    {
      init();
    }


  private:

    /*
    ** Do post-processing of the field input, such as forcing the content
    **  to be all upper-case.
    **
    */
    void on_blurred()
    {
      if( m_fieldDef.forceUppercase() )
      {
        setValueText( Wtx::ucase( valueText().toUTF8() ) );
      }

    }

    const Wtx::Dbo::FieldDefBase & m_fieldDef;

}; // endclass SmartLineEdit



std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefDateTimeEdit::createEditWidget( int sid, Wtx::Dbo::Session & session ) const
{
  auto retVal = std::make_unique<SmartLineEdit>(*this);
//  auto retVal = std::make_unique<Wt::WLineEdit>();

  retVal-> setPlaceholderText( placeholderText() );
  retVal-> setInputMask( inputMask() );

  /*
  ** the validator only 'checks' input for proper content, it does
  **  not ~mask~ the input to prevent typing wrong characters.  What
  **  we want is to simply ~force~ all input to appear as upper-case
  **  characters, so we will use the custom object above until we have
  **  a better solution.
  **
  */
//  if( forceUppercase() )
//  {
//    auto validator = std::make_shared<Wt::WRegExpValidator>("[A-Z0-9]+");
//
//    retVal-> setValidator( validator );
//
//  }

  return retVal;
}



