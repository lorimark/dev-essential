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


#include <Wt/WWidget.h>
#include <Wt/WLineEdit.h>

#include "TemplateFormView.h"

#ifdef DEBUG_TRACE
#define COUT_LINE std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl
#define COUT_(x)  std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << " " << x << std::endl;
#else
#define COUT_LINE
#define COUT_(x)
#endif

/*!
** \page templateformview Template Form View operation
**
**
** \par Update View with Model
** \code
** void Wtx::Dbo::TemplateFormView<C>::updateView(Wt::WFormModel*) [with C = BlogEntry]
** virtual void Wtx::TemplateFormView::updateView(Wt::WFormModel*)
** void Wtx::Dbo::TemplateFormView<C>::updateViewField(Wt::WFormModel*, Wt::WFormModel::Field) [with C = BlogEntry; Wt::WFormModel::Field = const char*] datePosted
** virtual void Wtx::TemplateFormView::updateViewField(Wt::WFormModel*, Wt::WFormModel::Field) datePosted
** bool Wtx::Dbo::TemplateFormView<C>::conditionValue(const string&) const [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] if:datePosted
** virtual bool Wtx::TemplateFormView::conditionValue(const string&) const if:datePosted
** virtual bool Wtx::TemplateFormView::conditionValue(const string&) const 0
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] datePosted
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) datePosted
** std::unique_ptr<Wt::WWidget> Wtx::Dbo::TemplateFormView<C>::createFormWidget(Wt::WFormModel::Field) [with C = BlogEntry; Wt::WFormModel::Field = const char*] datePosted
** std::unique_ptr<Wt::WWidget> Wtx::Dbo::TemplateFormView<C>::createEditWidget(Wt::WFormModel::Field) [with C = BlogEntry; Wt::WFormModel::Field = const char*] datePosted
** virtual std::unique_ptr<Wt::WWidget> Wtx::Dbo::FieldDef::createEditWidget(Wtx::Dbo::Session&) const
** void Wtx::Dbo::TemplateFormView<C>::bindWidget(const string&, std::unique_ptr<Wt::WWidget>) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] datePosted
** virtual void Wtx::TemplateFormView::bindWidget(const string&, std::unique_ptr<Wt::WWidget>) datePosted
** void Wtx::Dbo::TemplateFormView<C>::updateViewValue(Wt::WFormModel*, Wt::WFormModel::Field, Wt::WFormWidget*) [with C = BlogEntry; Wt::WFormModel::Field = const char*] datePosted
** virtual void Wtx::TemplateFormView::updateViewValue(Wt::WFormModel*, Wt::WFormModel::Field, Wt::WFormWidget*) datePosted
** bool Wtx::Dbo::TemplateFormView<C>::updateViewValue(Wt::WFormModel*, Wt::WFormModel::Field, Wt::WWidget*) [with C = BlogEntry; Wt::WFormModel::Field = const char*] datePosted
** virtual bool Wtx::TemplateFormView::updateViewValue(Wt::WFormModel*, Wt::WFormModel::Field, Wt::WWidget*) datePosted
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] datePosted-info
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) datePosted-info
** void Wtx::Dbo::TemplateFormView<C>::bindWidget(const string&, std::unique_ptr<Wt::WWidget>) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] datePosted-info
** virtual void Wtx::TemplateFormView::bindWidget(const string&, std::unique_ptr<Wt::WWidget>) datePosted-info
** void Wtx::Dbo::TemplateFormView<C>::bindString(const string&, const Wt::WString&, Wt::TextFormat) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] datePosted-label
** virtual void Wtx::TemplateFormView::bindString(const string&, const Wt::WString&, Wt::TextFormat) datePosted-label
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] datePosted-label
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) datePosted-label
** \endcode
**
**
**
** \par Render View
** \code
** 
** void Wtx::Dbo::TemplateFormView<C>::renderTemplate(std::ostream&) [with C = BlogEntry; std::ostream = std::basic_ostream<char>]
** virtual void Wtx::TemplateFormView::renderTemplate(std::ostream&)
** bool Wtx::Dbo::TemplateFormView<C>::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] block
** virtual bool Wtx::TemplateFormView::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) block
** bool Wtx::Dbo::TemplateFormView<C>::conditionValue(const string&) const [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] if:isActive
** virtual bool Wtx::TemplateFormView::conditionValue(const string&) const if:isActive
** virtual bool Wtx::TemplateFormView::conditionValue(const string&) const 1
** bool Wtx::Dbo::TemplateFormView<C>::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] id
** virtual bool Wtx::TemplateFormView::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) id
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] isActive
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) isActive
** bool Wtx::Dbo::TemplateFormView<C>::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] tr
** virtual bool Wtx::TemplateFormView::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) tr
** void Wtx::Dbo::TemplateFormView<C>::resolveString(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] isActive
** virtual void Wtx::TemplateFormView::resolveString(const string&, const std::vector<Wt::WString>&, std::ostream&) isActive
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] isActive
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) isActive
** void Wtx::Dbo::TemplateFormView<C>::resolveString(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] isActive-info
** virtual void Wtx::TemplateFormView::resolveString(const string&, const std::vector<Wt::WString>&, std::ostream&) isActive-info
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] isActive-info
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) isActive-info
** bool Wtx::Dbo::TemplateFormView<C>::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] block
** virtual bool Wtx::TemplateFormView::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) block
** bool Wtx::Dbo::TemplateFormView<C>::conditionValue(const string&) const [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] if:keyField
** virtual bool Wtx::TemplateFormView::conditionValue(const string&) const if:keyField
** virtual bool Wtx::TemplateFormView::conditionValue(const string&) const 1
** bool Wtx::Dbo::TemplateFormView<C>::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] id
** virtual bool Wtx::TemplateFormView::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) id
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] keyField
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) keyField
** bool Wtx::Dbo::TemplateFormView<C>::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] tr
** virtual bool Wtx::TemplateFormView::resolveFunction(const string&, const std::vector<Wt::WString>&, std::ostream&) tr
** void Wtx::Dbo::TemplateFormView<C>::resolveString(const string&, const std::vector<Wt::WString>&, std::ostream&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>; std::ostream = std::basic_ostream<char>] keyField
** virtual void Wtx::TemplateFormView::resolveString(const string&, const std::vector<Wt::WString>&, std::ostream&) keyField
** Wt::WWidget* Wtx::Dbo::TemplateFormView<C>::resolveWidget(const string&) [with C = BlogEntry; std::__cxx11::string = std::__cxx11::basic_string<char>] keyField
** virtual Wt::WWidget* Wtx::TemplateFormView::resolveWidget(const string&) keyField
** \endcode
**
**
*/

Wtx::TemplateFormView::~TemplateFormView()
{
  COUT_LINE;
}

Wtx::TemplateFormView::TemplateFormView( const Wt::WString & text )
: Wt::WTemplateFormView(text)
{
  COUT_LINE;
}

std::unique_ptr<Wt::WWidget> Wtx::TemplateFormView::createFormWidget( Wt::WFormModel::Field field )
{
  return nullptr;
//  COUT_(field);
//  return createEditWidget( field );
}

std::unique_ptr<Wt::WWidget> Wtx::TemplateFormView::createEditWidget( Wt::WFormModel::Field field )
{
  COUT_(field);
  return std::make_unique<Wt::WLineEdit>();
}

/*
** base class virtual overrides
**
*/
void Wtx::TemplateFormView::updateView( Wt::WFormModel *model )
{
  COUT_LINE;
  Wt::WTemplateFormView::updateView( model );
}


void Wtx::TemplateFormView::updateViewField( Wt::WFormModel *model, Wt::WFormModel::Field field )
{
  COUT_(field);
  Wt::WTemplateFormView::updateViewField( model, field );
}


void Wtx::TemplateFormView::updateViewValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit )
{
  COUT_(field);
  Wt::WTemplateFormView::updateViewValue( model, field, edit );
}


bool Wtx::TemplateFormView::updateViewValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit )
{
  COUT_(field);
  return Wt::WTemplateFormView::updateViewValue( model, field, edit );
}


void Wtx::TemplateFormView::updateModel( Wt::WFormModel *model )
{
  COUT_LINE;
  Wt::WTemplateFormView::updateModel( model );
}


void Wtx::TemplateFormView::updateModelField( Wt::WFormModel *model, Wt::WFormModel::Field field )
{
  COUT_(field);
  Wt::WTemplateFormView::updateModelField( model, field );
}


void Wtx::TemplateFormView::updateModelValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit )
{
  COUT_(field);
  Wt::WTemplateFormView::updateModelValue( model, field, edit );
}


bool Wtx::TemplateFormView::updateModelValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit )
{
  COUT_(field);
  return Wt::WTemplateFormView::updateModelValue( model, field, edit );
}

/*
** Template class overrides
**
*/
void Wtx::TemplateFormView::bindString( const std::string & varName, const Wt::WString & value, Wt::TextFormat textFormat )
{
  COUT_( varName << "=" << value );
  Wt::WTemplateFormView::bindString( varName, value, textFormat );
}

void Wtx::TemplateFormView::bindWidget( const std::string & varName, std::unique_ptr< Wt::WWidget > widget )
{
  COUT_(varName);
  Wt::WTemplateFormView::bindWidget( varName, std::move(widget) );
}

std::unique_ptr< Wt::WWidget > Wtx::TemplateFormView::removeWidget( Wt::WWidget *widget )
{
  COUT_LINE;
  return Wt::WTemplateFormView::removeWidget( widget );
}

bool Wtx::TemplateFormView::conditionValue( const std::string & name ) const
{
  bool retVal = Wt::WTemplateFormView::conditionValue( name );
  COUT_(name);
  COUT_(retVal);
  return retVal;
}

void Wtx::TemplateFormView::resolveString( const std::string & varName, const std::vector< Wt::WString > & args, std::ostream & result )
{
  COUT_(varName);
  Wt::WTemplateFormView::resolveString( varName, args, result );
}

void Wtx::TemplateFormView::handleUnresolvedVariable( const std::string & varName, const std::vector< Wt::WString > & args, std::ostream & result )
{
  COUT_(varName);
  Wt::WTemplateFormView::handleUnresolvedVariable( varName, args, result );
}

Wt::WWidget * Wtx::TemplateFormView::resolveWidget( const std::string & varName )
{
  Wt::WWidget * w = Wt::WTemplateFormView::resolveWidget( varName );

//  if( !w )
//    w = createEditWidget( varName );
//    w = std::make_unique<Wt::WLineEdit>();

  return w;
}

bool Wtx::TemplateFormView::resolveFunction( const std::string & name, const std::vector< Wt::WString > & args, std::ostream & result )
{
  if( name == "widget" )
  {
    if( args.size() > 0 )
    {
      if( args.at(0) == "WTabWidget" )
      {
        return true;
      }
    }
  }

  return Wt::WTemplateFormView::resolveFunction( name, args, result );
}

void Wtx::TemplateFormView::refresh()
{
  COUT_LINE;
  Wt::WTemplateFormView::refresh();
}

void Wtx::TemplateFormView::renderTemplate( std::ostream & result )
{
  COUT_LINE;
  Wt::WTemplateFormView::renderTemplate( result );
}



