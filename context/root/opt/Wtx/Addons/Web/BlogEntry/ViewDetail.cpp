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


#include <Wt/WTemplate.h>
#include <Wt/WText.h>

#include "Item.h"
#include "ViewDetail.h"

#ifndef ID_DETAIL_ITEM
#define ID_DETAIL_ITEM "Wtx.Web.BlogEntry.Item.DetailForm"
#endif

void Wtx::Web::BlogEntry::ViewDetail::init( const Wt::Dbo::ptr<Wtx::Web::BlogEntry::Item> & item )
{
  if( !item )
  {
    addNew<Wt::WText>( "Oops, I was unable to find that article" );
    return;
  }

  /*
  ** Try to load the template.  If it does not load then
  **  default to one that may be suitable.
  **
  */
  auto tr = Wt::WString::tr( ID_DETAIL_ITEM );
  if( tr.toUTF8().find("??") != std::string::npos )
  {
    tr =
      Wt::WString
      (
       "<div>"
       "  <strong><big>${title}</big></strong><br />"
       "  ${<if-posted>}"
       "    <small>Posted on ${date}</small><br />"
       "  ${</if-posted>}"
       "  ${body}<br />"
       "  <br />"
       "  <br />"
       "</div>"
      );
  }

  /*
  ** Load the template and bind stuff to it.
  **
  */
  auto templt = addNew<Wt::WTemplate>( tr );

  /*
  ** If the date has nothing in it, then just leave it empty
  **
  */
  templt-> setCondition( "if-posted", item-> datePosted.value() != "" );
  templt-> bindNew<Wt::WText>( "date",  item-> datePosted.value() );

  templt-> bindNew<Wt::WText>( "title", item-> keyField().value()   );
  templt-> bindNew<Wt::WText>( "body",  item-> body.value(),      Wt::TextFormat::UnsafeXHTML  );
}

Wtx::Web::BlogEntry::ViewDetail::ViewDetail( const Wt::Dbo::ptr<Wtx::Web::BlogEntry::Item> & item )
: Wt::WContainerWidget()
{
  init( item );
}

#ifdef NEVER
Wtx::Web::BlogEntryViewDetail::BlogEntryViewDetail( const std::string & url )
: Wt::WContainerWidget()
{
  auto key = url.substr( std::string(BLOG_ENTRY_URL).length() );
//      auto key = url.substr( 8 );

 std::cout << __FILE__ << ":" << __LINE__ << " " << url.size() << " " << url << ":" << key << std::endl;

 Wt::Dbo::Transaction t(*kbwSession);
 auto item =
   kbwSession-> find<Wtx::Web::BlogEntry>()
   .where( "\"keyField\" = ?" ).bind( key )
   .resultValue()
   ;

 init( item );
}
#endif


