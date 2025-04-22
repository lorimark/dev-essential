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


#ifndef __WTX_TEMPLATEFORMVIEW_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_TEMPLATEFORMVIEW_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/WTemplateFormView.h>

namespace Wt {
  class WWidget;
}

namespace Wtx {

/*!
** \brief Template Form View
**
** This object replaces the base Wt::WTemplateFormView class with an extended
**  functionality.
**
*/
class TemplateFormView
: public Wt::WTemplateFormView
{

  public:

    virtual ~TemplateFormView();
    TemplateFormView( const Wt::WString & text );

    /*!
    ** \brief Create Form Widget
    **
    ** A 'form widget' is a widget that is used on a detail form.  This
    **  means that at the very least the form widget must derive from
    **  the base class Wt::WWidget.
    **
    **
    */
    std::unique_ptr<Wt::WWidget> createFormWidget( Wt::WFormModel::Field f );

    /*!
    ** \brief Create Edit Widget
    **
    ** An 'edit widget' is any kind of widget that offers editing functionality.
    **  The edit widget must at least derive from an Wt::WWidget but it should
    **  also provide functionality from WFormWidget, which includes the ability
    **  to set the value text and things like that.
    **
    */
    std::unique_ptr<Wt::WWidget> createEditWidget( Wt::WFormModel::Field f );

    /*
    ** base class virtual overrides
    **
    */
    virtual void updateView( Wt::WFormModel *model );
    virtual void updateViewField( Wt::WFormModel *model, Wt::WFormModel::Field field );
    virtual void updateViewValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit );
    virtual bool updateViewValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit );
    virtual void updateModel( Wt::WFormModel *model );
    virtual void updateModelField( Wt::WFormModel *model, Wt::WFormModel::Field field );
    virtual void updateModelValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit );
    virtual bool updateModelValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit );

    /*
    ** Template class overrides
    **
    */
    virtual void bindString( const std::string &varName, const Wt::WString &value, Wt::TextFormat textFormat=Wt::TextFormat::XHTML );
    virtual void bindWidget( const std::string &varName, std::unique_ptr< Wt::WWidget > widget );
    virtual std::unique_ptr< Wt::WWidget > removeWidget( Wt::WWidget *widget ) override;
    virtual bool conditionValue( const std::string &name ) const;
    virtual void resolveString( const std::string &varName, const std::vector< Wt::WString > &args, std::ostream &result );
    virtual void handleUnresolvedVariable( const std::string &varName, const std::vector< Wt::WString > &args, std::ostream &result );
    virtual WWidget * resolveWidget( const std::string &varName );
    virtual bool resolveFunction( const std::string &name, const std::vector< Wt::WString > &args, std::ostream &result );
    virtual void refresh() override;
    virtual void renderTemplate( std::ostream &result );

  protected:

    void show( const std::string & functionName, const std::string & varName, const std::vector< Wt::WString > & args = std::vector<Wt::WString>() )
    {
#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__ << " " << functionName << ": " << varName << std::endl;
      for( auto arg : args )
        std::cout << __FILE__ << ":" << __LINE__ << " --" << arg << std::endl;
#endif
    }

  private:

}; // endclass TemplateFormView

} // endnamespace Wtx {

#endif // __WTX_TEMPLATEFORMVIEW_H___

