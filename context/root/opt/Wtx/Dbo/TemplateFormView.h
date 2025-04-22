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


#ifndef __WTX_DBO_TEMPLATEFORMVIEW_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_TEMPLATEFORMVIEW_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/WFormWidget.h>

#include <Wtx/Dbo/FieldDefBase.h>
#include <Wtx/Dbo/FormModel.h>
#include <Wtx/TemplateFormView.h>

namespace Wtx {
  namespace Dbo {

template <class C> class TemplateFormView
: public Wtx::TemplateFormView
{

  public:

    class FormWidgetWrapper
    : public Wt::WObject
    {
      public:

        FormWidgetWrapper( Wt::WFormModel * model, Wt::WFormModel::Field field, Wt::WFormWidget * widget )
        : Wt::WObject(),
          m_model(model),
          m_field(field),
          m_widget(widget)
        {
          widget-> focussed().connect( this, &FormWidgetWrapper::on_focussed );
          widget-> blurred() .connect( this, &FormWidgetWrapper::on_blurred  );
          widget-> clicked() .connect( this, &FormWidgetWrapper::on_clicked  );
          m_prevValue = widget-> valueText().toUTF8();
        }

        Wt::Signal<FormWidgetWrapper*> & focussed()
        {
          return m_focussed;
        }

        Wt::Signal<FormWidgetWrapper*> & blurred()
        {
          return m_blurred;
        }

        Wt::Signal<FormWidgetWrapper*> & clicked()
        {
          return m_clicked;
        }

        Wt::WFormModel::Field field() const
        {
          return m_field;
        }

        std::string fieldName() const
        {
          return std::string( m_field );
        }

        Wt::WFormWidget * widget() const
        {
          return m_widget;
        }

        const std::string & prevValue() const
        {
          return m_prevValue;
        }

        bool isChanged() const
        {
          return m_prevValue != widget()-> valueText();
        }

        bool is( Wtx::Dbo::FieldDefBase * fieldDef )
        {
          return fieldDef-> fieldName() == fieldName();
        }

        bool is( Wtx::Dbo::FieldDefBase & fieldDef )
        {
          return fieldDef.fieldName() == fieldName();
        }

        void resetChangedFlags()
        {
          m_prevValue = widget()-> valueText().toUTF8();
        }

        Wt::WFormModel * model() const
        {
          return m_model;
        }

      private:

        void on_focussed()
        {
          m_focussed.emit(this);
        }

        void on_blurred()
        {
          m_blurred.emit(this);
        }

        void on_clicked()
        {
          m_clicked.emit(this);
        }

        Wt::WFormModel * m_model = nullptr;
        Wt::WFormModel::Field m_field = nullptr;
        Wt::WFormWidget * m_widget = nullptr;

        Wt::Signal<FormWidgetWrapper*> m_focussed;
        Wt::Signal<FormWidgetWrapper*> m_blurred;
        Wt::Signal<FormWidgetWrapper*> m_clicked;

        std::string m_prevValue;

    }; // endclass FormWidgetWrapper

    TemplateFormView( const Wt::WString & text )
    : Wtx::TemplateFormView(text)
    {
    }

    /*!
    ** \brief Constructor with Model
    **
    */
    TemplateFormView( const Wt::WString & text, std::unique_ptr< Wtx::Dbo::FormModel<C> > model )
    : Wtx::TemplateFormView(text),
      m_formModel( std::move(model) )
    {
//      COUT2_LINE;
    }

    /*!
    ** \brief Internal Form Model
    **
    ** This is the form model that was set using setFormModel() or that was passed
    **  along with the constructor.
    **
    **
    */
    Wtx::Dbo::FormModel<C> * formModel() const
    {
      return m_formModel.get();
    }

    /*!
    ** \brief
    **
    */
    void setFormModel( std::unique_ptr< Wtx::Dbo::FormModel<C> > model )
    {
      m_formModel = std::move(model);
    }

    /*!
    ** \brief
    **
    */
    Wtx::Dbo::FormModel<C> * formModel( Wt::WFormModel * model )
    {
      return dynamic_cast<Wtx::Dbo::FormModel<C>*>( model );
    }

    /*!
    ** \brief
    **
    */
    Wtx::Dbo::FieldDefBase * fieldDef(  Wt::WFormModel * model, Wt::WFormModel::Field field )
    {
      if( auto wtxModel = formModel(model) )
        return wtxModel-> tableDef().fieldDef( field );

      return nullptr;
    }

    /*!
    ** \brief Focussed Stub
    **
    ** This 'virtual' stub does nothing.  It should be reimplemented by
    **  the subclass.
    **
    */
    virtual void on_focussed( FormWidgetWrapper * fww )
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " on_focussed:" << fww-> fieldName() << std::endl;
    }

    /*!
    ** \brief Blurred Stub
    **
    ** This 'virtual' stub does nothing.  It should be reimplemented by
    **  the subclass.
    **
    */
    virtual void on_blurred( FormWidgetWrapper * fww )
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " on_blurred:" << fww-> fieldName() << std::endl;
    }

    /*!
    ** \brief Clicked Stub
    **
    **/
    virtual void on_clicked( FormWidgetWrapper * fww )
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

    }

    /*!
    ** \brief
    **
    */
    std::unique_ptr<Wt::WWidget> createFormWidget( Wt::WFormModel::Field field )
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << field << std::endl;

      auto retVal = createEditWidget( field );

      auto fw = dynamic_cast<Wt::WFormWidget*>(retVal.get());

      if( retVal && formModel() && fw )
      {
        auto fww = std::make_unique<FormWidgetWrapper>( formModel(), field, fw );
        fww-> focussed().connect( this, &TemplateFormView<C>::on_focussed );
        fww-> blurred() .connect( this, &TemplateFormView<C>::on_blurred );
        fww-> clicked() .connect( this, &TemplateFormView<C>::on_clicked );
        m_formWidgets.push_back(std::move(fww));
      }

      return retVal;
    }

    void resetEditWidgetChangedFlags()
    {
      for( auto & fww : m_formWidgets )
      {
        fww-> resetChangedFlags();
      }
    }

    /*!
    ** \brief
    **
    */
    std::unique_ptr<Wt::WWidget> createEditWidget( Wt::WFormModel::Field field )
    {
//      COUT2_( field );
      if( formModel() )
      {
        return formModel()-> createEditWidget( field );
      }

      return Wtx::TemplateFormView::createEditWidget( field );
    }


    /*
    ** base class virtual overridea
    **
    */

    virtual void updateView()
    {
      Wtx::TemplateFormView::updateView( formModel() );

      resetEditWidgetChangedFlags();
    }

    /*!
    ** \brief Update a View from a Model
    **
    ** This will update all the view object based on the field list
    **  from the model.
    **
    **
    */
    virtual void updateView( Wt::WFormModel *model )
    {
//      COUT2_LINE;
      Wtx::TemplateFormView::updateView( model );
      resetEditWidgetChangedFlags();
    }

    /*!
    ** \brief
    **
    */
    virtual void updateViewField( Wt::WFormModel *model, Wt::WFormModel::Field field )
    {
//      COUT2_( field );

      /*
      ** using the enhanced features of the Wtx::Model query the field definition
      **  object to see if there is even supposed to be a UI component to this
      **  model field.
      **
      */
//      if( fieldDef(model,field)-> flags() & Wtx::Dbo::FieldDefBase::NoUi )
//      {
//        COUT_( "no UI" );
//        return;
//      }

      Wtx::TemplateFormView::updateViewField( model, field );
      resetEditWidgetChangedFlags();
    }


    /*!
    ** \brief
    **
    */
    virtual void updateViewValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit )
    {
//      COUT2_( field );
      Wtx::TemplateFormView::updateViewValue( model, field, edit );
      resetEditWidgetChangedFlags();
    }


    /*!
    ** \brief
    **
    */
    virtual bool updateViewValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit )
    {
//      COUT2_( field );
      return Wtx::TemplateFormView::updateViewValue( model, field, edit );
      resetEditWidgetChangedFlags();
    }


    virtual void updateModel()
    {
      updateModel( formModel() );
    }

    /*!
    ** \brief
    **
    */
    virtual void updateModel( Wt::WFormModel *model )
    {
//      COUT2_LINE;
      Wtx::TemplateFormView::updateModel( model );
    }


    /*!
    ** \brief
    **
    */
    virtual void updateModelField( Wt::WFormModel *model, Wt::WFormModel::Field field )
    {
//      COUT2_( field );
      Wtx::TemplateFormView::updateModelField( model, field );
    }


    /*!
    ** \brief
    **
    */
    virtual void updateModelValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit )
    {
//      COUT2_( field );
      Wtx::TemplateFormView::updateModelValue( model, field, edit );
    }


    /*!
    ** \brief
    **
    */
    virtual bool updateModelValue( Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit )
    {
//      COUT2_( field );
      return Wtx::TemplateFormView::updateModelValue( model, field, edit );
    }

    /*
    ** Template class overrides
    **
    */
    virtual void bindString( const std::string & varName, const Wt::WString & value, Wt::TextFormat textFormat=Wt::TextFormat::XHTML )
    {
//      COUT2_( varName << "=" << value );
      Wtx::TemplateFormView::bindString( varName, value, textFormat );
    }

    /*!
    ** \brief
    **
    */
    virtual void bindWidget( const std::string & varName, std::unique_ptr< Wt::WWidget > widget )
    {
//      COUT2_( varName );
      Wtx::TemplateFormView::bindWidget( varName, std::move(widget) );
    }

    /*!
    ** \brief
    **
    */
    virtual std::unique_ptr< Wt::WWidget > removeWidget( Wt::WWidget *widget ) override
    {
//      COUT2_LINE;
      return Wtx::TemplateFormView::removeWidget( widget );
    }

    /*!
    ** \brief
    **
    */
    virtual bool conditionValue( const std::string & name ) const
    {
//      COUT2_( name );
      return Wtx::TemplateFormView::conditionValue( name );
    }

    /*!
    ** \brief
    **
    */
    virtual void resolveString( const std::string & varName, const std::vector< Wt::WString > & args, std::ostream & result )
    {
      show( __FUNCTION__, varName, args );
      Wtx::TemplateFormView::resolveString( varName, args, result );
    }

    /*!
    ** \brief
    **
    */
    virtual void handleUnresolvedVariable( const std::string & varName, const std::vector< Wt::WString > & args, std::ostream & result )
    {
      show( __FUNCTION__, varName, args );
      Wtx::TemplateFormView::handleUnresolvedVariable( varName, args, result );
    }

    /*!
    ** \brief
    **
    */
    virtual WWidget * resolveWidget( const std::string & varName )
    {
      show( __FUNCTION__, varName );
      return Wtx::TemplateFormView::resolveWidget( varName );
    }

    /*!
    ** \brief
    **
    */
    virtual bool resolveFunction( const std::string & name, const std::vector< Wt::WString > & args, std::ostream & result )
    {
      show( __FUNCTION__, name, args );

      return Wtx::TemplateFormView::resolveFunction( name, args, result );
    }

    /*!
    ** \brief
    **
    */
    virtual void refresh() override
    {
//      COUT2_LINE;
      Wtx::TemplateFormView::refresh();
    }

    /*!
    ** \brief
    **
    */
    virtual void renderTemplate( std::ostream & result )
    {
//      COUT2_LINE;
      Wtx::TemplateFormView::renderTemplate( result );
    }


    /*!
    ** \brief Widget Wrapper Collection
    **
    **
    */
    std::vector< std::unique_ptr< FormWidgetWrapper > > & formWidgetWrappers()
    {
      return m_formWidgets;
    }

    /*!
    ** \brief Get Form Widget Wrapper
    **
    ** This will return a form widget wrapper based on the field
    **  def given.
    **
    */
    FormWidgetWrapper * formWidgetWrapper( Wtx::Dbo::FieldDefBase & fieldDef )
    {
      for( auto & fww : m_formWidgets )
      {
        if( fww-> fieldName() == fieldDef.fieldName() )
          return fww.get();
      }

      return nullptr;
    }

    FormWidgetWrapper * formWidgetWrapper( const std::string & fieldName )
    {
      for( auto & fww : m_formWidgets )
      {
        if( fww-> fieldName() == fieldName )
        {
          return fww.get();
        }
      }

      return nullptr;
    }

    /*!
    ** \brief Get Form Widget Wrapper
    **
    ** This will return a form widget wrapper based on the field
    **  def given.
    **
    */
    Wt::WFormWidget * formWidget( Wtx::Dbo::FieldDefBase & fieldDef )
    {
      for( auto & fww : m_formWidgets )
      {
        if( fww-> fieldName() == fieldDef.fieldName() )
          return fww-> widget();
      }

      return nullptr;
    }

  private:

    /*!
    ** \brief
    **
    */
    std::unique_ptr<Wtx::Dbo::FormModel<C>> m_formModel;

    std::vector<std::unique_ptr<FormWidgetWrapper>> m_formWidgets;

}; // endclass Wtx::Dbo::TemplateFormView


  } // endnamespace Dbo {
} // endnamespace Wtx {

#endif // __WTX_DBO_TEMPLATEFORMVIEW_H___


