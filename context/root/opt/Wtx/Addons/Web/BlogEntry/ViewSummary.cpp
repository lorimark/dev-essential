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


#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WLink.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WTable.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

#include "Item.h"
#include "ViewSummary.h"
#include "ViewDetail.h"

#define BLOG_ENTRY_URL "/blog/entry/"

#define ID_ROW_ITEM "Wtx.Web.BlogEntryViewSummary.RowItem"
class RowItem
: public Wt::WContainerWidget
{
  public:

    RowItem( const Wt::Dbo::ptr<Wtx::Web::BlogEntry::Item> & item )
    : Wt::WContainerWidget()
    {
      /*
      ** Try to load the template.  This can be overwritten
      **  by the application, but if the template is not found
      **  then just default to a suitable alternative.
      **
      */
      auto tr = Wt::WString::tr(ID_ROW_ITEM);
      if( tr.toUTF8().find("??") != std::string::npos )
      {
        tr =
          Wt::WString
          (
           "<div>"
           "  <strong><big>${title}</big></strong><br />"
           "  ${<if-date>}"
           "    <small>Posted on ${date}</small><br />"
           "  ${</if-date>}"
           "  ${shortBody}<br />"
           "  ${thumbnail}"
           "  <br />"
           "  <br />"
           "</div>"
          );
      }

      auto templt = addNew<Wt::WTemplate>( tr );
      templt-> setInternalPathEncoding(true);

      auto url = item-> keyField().value();

      auto link = Wt::WLink( Wt::LinkType::InternalPath, BLOG_ENTRY_URL + url );
      auto anchor = std::make_unique<Wt::WAnchor>( link, item-> keyField().value() );

      templt-> bindWidget<Wt::WAnchor>( "title",     std::move(anchor)               );
      templt-> bindNew<Wt::WText>(      "shortBody", item-> summary.value()          );

      templt-> setCondition(            "if-date",   item-> datePosted.value() != "" );
      templt-> bindNew<Wt::WText>(      "date",      item-> datePosted.value()       );

      if( item-> thumbnail.value() == "" )
        templt-> bindEmpty("thumbnail");
      else
        templt-> bindString
        (
         "thumbnail",
         Wt::WString::tr("kbw.thumbnail")
         .arg( item-> thumbnail.value() )
        );
    }

  private:

};

Wtx::Web::BlogEntry::ViewSummary::ViewSummary( Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{
  m_stack = addNew<Wt::WStackedWidget>();

  auto table = m_stack-> addNew<Wt::WTable>();

  Wt::Dbo::Transaction t(*session());
  auto blogEntries =
    session()-> find<Wtx::Web::BlogEntry::Item>()
    .where( "\"isActive\" = 1 AND id > 1" )
    .orderBy( "\"datePosted\" DESC" )
    .resultList()
    ;

  for( auto blogEntry : blogEntries )
    table-> elementAt( table-> rowCount(), 0 )->
      addWidget
      (
       std::make_unique<RowItem>(blogEntry)
      );


  wApp-> internalPathChanged().connect( this, &ViewSummary::on_internalPathChanged );
  on_internalPathChanged();

}

void Wtx::Web::BlogEntry::ViewSummary::on_internalPathChanged()
{
  auto ip = wApp-> internalPath();

  /*
  ** If we are just loading the blog summary, then switch
  **  back to the stack that has the main blog summary list.
  **
  */
  if( ip == "/blog" )
  {
    if( m_stack-> currentIndex() == 0 )
      return;

    /*
    ** to go back to the main blog summary list, we just
    **  remove any subsequent stack pages, and then the
    **  stack will go back to the zero index
    **
    */
    m_stack-> removeWidget( m_stack-> currentWidget() );
    return;
  }

  /*
  ** if we are attempting to load a blog page then do that
  **  now.
  **
  */
  if( ip.find("/blog/entry/") != std::string::npos )
  {
    if( m_stack-> currentIndex() == 1 )
      return;

    auto page = ip.substr( 12 );

    Wt::Dbo::Transaction t(*session());
    auto blogEntry =
      session()-> find<Wtx::Web::BlogEntry::Item>()
      .where( "\"keyField\" = ?" )
      .bind( page )
      .resultValue()
      ;

    if( !blogEntry )
    {
      m_stack-> addWidget( std::make_unique<Wt::WText>( Wt::WString("oh oh, I could not find the article: '{1}'").arg( page ) ) );
    }
    else
    {
      m_stack-> addWidget( std::make_unique<Wtx::Web::BlogEntry::ViewDetail>( blogEntry ) );
    }

    m_stack-> setCurrentIndex( 1 );
  }

}


