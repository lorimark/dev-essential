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

#include <Wt/Json/Object.h>
#include <Wt/Json/Value.h>
#include <Wt/Json/Parser.h>
#include <Wt/Json/Serializer.h>

#include "FieldVar.h"

std::string Wtx::Dbo::FieldVar::value( const std::string & field ) const
{
  std::string retVal;

  if( Field::value() != "" )
  {
    Wt::Json::Object jobj;
    try {
      Wt::Json::parse( Field::value(), jobj );
    }
    catch( std::exception & e )
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }

    retVal = jobj.get(field).orIfNull("");

  }

  return retVal;
}

void Wtx::Dbo::FieldVar::setValue( const std::string & value )
{
  Field<std::string>::setValue( value );
}

void Wtx::Dbo::FieldVar::setValue( const std::string & field, const std::string & val )
{
  Wt::Json::Object jobj;
  try {
    Wt::Json::parse( Field::value(), jobj );
  }
  catch( std::exception & e )
  {
//    std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
  }

  jobj[field] = Wt::WString(val);

  setValue( Wt::Json::serialize(jobj) );

} // endvoid Wtx::Dbo::FieldVar::setValue( const std::string & field, const std::string & val )

void Wtx::Dbo::FieldVar::setValue( const std::string & field, int val )
{
  Wt::Json::Object jobj;
  try {
    Wt::Json::parse( Field::value(), jobj );
  }
  catch( std::exception & e )
  {
//    std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
  }

  jobj[field] = Wt::WString("{1}").arg(val);

  setValue( Wt::Json::serialize(jobj) );

} // endvoid Wtx::Dbo::FieldVar::setValue( const std::string & field, const std::string & val )


