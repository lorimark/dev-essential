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


#include "Template.h"

Wt::WString Wtx::Template::templateText() const
{
  return Wt::WTemplate::templateText();
}

void Wtx::Template::bindString( const std::string & varName, const Wt::WString & value, Wt::TextFormat textFormat )
{
  Wt::WTemplate::bindString( varName, value, textFormat );
}


void Wtx::Template::bindWidget( const std::string & varName, std::unique_ptr< Wt::WWidget > widget )
{
  Wt::WTemplate::bindWidget( varName, std::move(widget) );
}


std::unique_ptr< Wt::WWidget > Wtx::Template::removeWidget( Wt::WWidget * widget )
{
  return Wt::WTemplate::removeWidget( widget );
}


bool Wtx::Template::conditionValue( const std::string & name ) const
{
  return Wt::WTemplate::conditionValue( name );
}


void Wtx::Template::resolveString( const std::string & varName, const std::vector< Wt::WString > & args, std::ostream & result )
{
  Wt::WTemplate::resolveString( varName, args, result );
}


void Wtx::Template::handleUnresolvedVariable( const std::string & varName, const std::vector< Wt::WString > & args, std::ostream & result )
{
  Wt::WTemplate::handleUnresolvedVariable( varName, args, result );
}


Wt::WWidget * Wtx::Template::resolveWidget( const std::string & varName )
{
  return Wt::WTemplate::resolveWidget( varName );
}


bool Wtx::Template::resolveFunction( const std::string & name, const std::vector< Wt::WString > & args, std::ostream & result )
{
  return Wt::WTemplate::resolveFunction( name, args, result );
}


void Wtx::Template::clear()
{
  Wt::WTemplate::clear();
}


void Wtx::Template::refresh()
{
  Wt::WTemplate::refresh();
}


void Wtx::Template::renderTemplate( std::ostream & result )
{
  Wt::WTemplate::renderTemplate( result );
}


