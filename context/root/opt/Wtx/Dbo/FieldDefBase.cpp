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


#include <memory>
#include <iostream>
#include <vector>

#include <Wt/WItemDelegate.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>

#include <Wtx/Wtx.h>

#include "TableDef.h"
#include "FieldDefBase.h"

Wtx::Dbo::FieldDefBase::FieldDefBase
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
: Wt::WObject(),
  m_tableDef(td),
  m_fieldName(fn),
  m_width(w),
  m_height(h),
  m_flags(f),
  m_label(lb),
  m_placeholderText(ph),
  m_info(inf),
  m_toolTip(tt),
  m_helpTopic(ht)
{
  init();
}

Wtx::Dbo::FieldDefBase::FieldDefBase
(
 TableDef & td,
 const char * fn,
 std::string lb,
 std::string ph,
 std::string inf,
 std::string tt,
 int ht
)
: Wt::WObject(),
  m_tableDef(td),
  m_fieldName(fn),
  m_width(-1),
  m_height(-1),
  m_label(lb),
  m_placeholderText(ph),
  m_info(inf),
  m_toolTip(tt),
  m_helpTopic(ht)
{
  init();
}

void Wtx::Dbo::FieldDefBase::init()
{
  /*
  ** push this field definition up in to the table
  **  definition.
  **
  */
  tableDef().push_back( *this );
}

Wtx::Dbo::TableDef & Wtx::Dbo::FieldDefBase::tableDef() const
{
  return m_tableDef;
}

const char * Wtx::Dbo::FieldDefBase::fieldName() const
{
  return m_fieldName;
}

const std::string & Wtx::Dbo::FieldDefBase::aliasName() const
{
  return m_aliasName;
}

int Wtx::Dbo::FieldDefBase::width() const
{
  return m_width;
}

void Wtx::Dbo::FieldDefBase::setWidth( int value )
{
  m_width = value;
}

int Wtx::Dbo::FieldDefBase::height() const
{
  return m_height;
}

void Wtx::Dbo::FieldDefBase::setHeight( int value )
{
  m_height = value;
}

bool Wtx::Dbo::FieldDefBase::isReadOnly() const
{
  return m_isReadOnly;
}

void Wtx::Dbo::FieldDefBase::setIsReadOnly( bool value )
{
  m_isReadOnly = value;
}

bool Wtx::Dbo::FieldDefBase::isUnique() const
{
  return m_isUnique;
}

void Wtx::Dbo::FieldDefBase::setIsUnique( bool value )
{
  m_isUnique = value;
}

bool Wtx::Dbo::FieldDefBase::isVisible() const
{
  return m_isVisible;
}

void Wtx::Dbo::FieldDefBase::setIsVisible( bool value )
{
  m_isVisible = value;
}

const std::string & Wtx::Dbo::FieldDefBase::label() const
{
  return m_label;
}

void Wtx::Dbo::FieldDefBase::setLabel( const std::string & value )
{
  m_label = value;
}

const std::string & Wtx::Dbo::FieldDefBase::placeholderText() const
{
  return m_placeholderText;
}

void Wtx::Dbo::FieldDefBase::setPlaceholderText( const std::string & value )
{
  m_placeholderText = value;
}

const std::string & Wtx::Dbo::FieldDefBase::info() const
{
  return m_info;
}

void Wtx::Dbo::FieldDefBase::setInfo( const std::string & value )
{
  m_info = value;
}

const std::string & Wtx::Dbo::FieldDefBase::toolTip() const
{
  return m_toolTip;
}

void Wtx::Dbo::FieldDefBase::setToolTip( const std::string & value )
{
  m_toolTip = value;
}

int Wtx::Dbo::FieldDefBase::helpTopic() const
{
  return m_helpTopic;
}

void Wtx::Dbo::FieldDefBase::setHelpTopic( int value )
{
  m_helpTopic = value;
}

const Wtx::Dbo::FieldDefBase::Flags & Wtx::Dbo::FieldDefBase::flags() const
{
  return m_flags;
}

void Wtx::Dbo::FieldDefBase::setFlags( const Wtx::Dbo::FieldDefBase::Flags value )
{
  m_flags = value;
}

const std::string & Wtx::Dbo::FieldDefBase::defaultValue() const
{
  return m_defaultValue;
}

void Wtx::Dbo::FieldDefBase::setDefaultValue( const std::string & value )
{
  m_defaultValue = value;
}

bool Wtx::Dbo::FieldDefBase::forceUppercase() const
{
  return m_forceUppercase || Wtx::forceUppercase();
}

void Wtx::Dbo::FieldDefBase::setForceUppercase( bool value )
{
  m_forceUppercase = value;
}

const std::string & Wtx::Dbo::FieldDefBase::inputMask() const
{
  return m_inputMask;
}

void Wtx::Dbo::FieldDefBase::setInputMask( const std::string & mask, Wt::WFlags< Wt::InputMaskFlag > flags )
{
  m_inputMask      = mask;
  m_inputMaskFlags = flags;
}

std::unique_ptr<Wt::WItemDelegate> Wtx::Dbo::FieldDefBase::createItemDelegate( int sid, Wtx::Dbo::Session & session ) const
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
  return std::make_unique<Wt::WItemDelegate>();
}

std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefBase::createLabelWidget( int sid, Wtx::Dbo::Session & session ) const
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
  return std::make_unique<Wt::WText>(m_label);
}

std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefBase::createEditWidget( int sid, Wtx::Dbo::Session & session ) const
{
  auto retVal = std::make_unique<Wt::WLineEdit>();

  retVal-> setPlaceholderText( placeholderText() );
  retVal-> setInputMask( inputMask(), m_inputMaskFlags );

  return retVal;
}

std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDefBase::createDisplayWidget( int sid, Wtx::Dbo::Session & session ) const
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
  return std::make_unique<Wt::WText>();
}

std::string Wtx::Dbo::FieldDefBase::toJson() const
{
  std::string retVal;

  retVal += "{";

  retVal += " \"fieldName\":";
  retVal += " \"" + std::string(m_fieldName) + "\"";

  retVal += ",\n \"width\":";
  retVal += " " + std::to_string(m_width);

  retVal += ",\n \"label\":";
  retVal += " \"" + std::string(m_label) + "\"";

  retVal += "}";

  return retVal;
}

void Wtx::Dbo::FieldDefBase::fromJson( const std::string & value )
{
}

