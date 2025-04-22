
#ifndef __WTX_DBO_DETAILFORM_H___
#define __WTX_DBO_DETAILFORM_H___

#include <Wtx/MessageBox.h>
#include <Wtx/PopupMessage.h>
#include <Wtx/Dbo/TemplateFormView.h>

namespace Wtx {
  namespace Dbo {

template <class C>
class DetailForm
: public Wtx::Dbo::TemplateFormView<C>
{
  public:

    DetailForm( const std::string & tn )
    : Wtx::Dbo::TemplateFormView<C>
      (
       Wt::WString::tr(tn)
      ),
      m_templateName(tn)
    {
    }

    DetailForm( const std::string & tn, Wt::Dbo::ptr<C> & item )
    : Wtx::Dbo::TemplateFormView<C>
      (
       Wt::WString::tr(tn),
       std::make_unique< Wtx::Dbo::FormModel<C> >( item.id(), item.session() )
      ),
      m_templateName(tn)
    {

      /*
      ** check the item on disk to make sure we've got the
      **  latest copy of the item, and if not, reload it.
      **
      */
      if( Wtx::Dbo::TemplateFormView<C>::formModel()-> isStale() )
      {
        Wtx::Dbo::TemplateFormView<C>::formModel()-> staleRefresh();
      }

//      Wtx::Dbo::TemplateFormView<C>:: template bindNew<Wt::WPushButton>( "submit", "submit" );
//      Wtx::Dbo::TemplateFormView<C>:: template bindNew<Wt::WPushButton>( "close",  "close"  );
//      Wtx::Dbo::TemplateFormView<C>:: template bindNew<Wt::WPushButton>( "print",  "print"  );

      this-> updateView();
      Wtx::Dbo::TemplateFormView<C>::resetEditWidgetChangedFlags();

    } // endDetailForm( const std::string & tn, Wt::Dbo::ptr<C> & item )

    const std::string & templateName() const
    {
      return m_templateName;
    }

    /*!
    ** \brief Allow Change
    **
    **
    */
    virtual bool allowChange() const
    {
      return false;
    }

    /*!
    ** \brief Allow Delete
    **
    **
    */
    virtual bool allowDelete() const
    {
      return false;
    }

    /*!
    ** \brief Allow Print
    **
    **
    */
    virtual bool allowPrint() const
    {
      return false;
    }

    /*!
    ** \brief Allow Unlock
    **
    **
    */
    virtual bool allowUnlock() const
    {
      return false;
    }

    /*!
    ** \brief before update stub
    **
    ** Before the model is updated from the form, this function
    **  is called.  It allows the derived class to perform things
    **  before data is removed from the form and placed in to
    **  the model.
    **
    */
    virtual bool beforeUpdate()
    {
      return true;
    }

    /*!
    ** \brief after update stub
    **
    ** After the model is updated, this procedure can do things
    **  before anything else happens.
    **
    */
    virtual bool afterUpdate()
    {
      return true;
    }

    /*!
    ** \brief before accept stub
    **
    ** This should be handled in a sub-class.  This function should return
    **  .true. that it is ok to save the item.
    **
    */
    virtual bool beforeAccept()
    {
      return true;
    }

    /*!
    ** \brief after accept stub
    **
    ** This should be handled in a sub-class.  This function should return
    **  .true. that everything was completed.
    **
    */
    virtual bool afterAccept()
    {
      return true;
    }

    /*!
    ** \brief refresh underlying table on save
    **
    ** If the detail form was opened from an underlying
    **  table-view, then when the detail item is saved, the
    **  underlying table needs to be refreshed.  Sometimes
    **  this is not always desirable.
    **
    **/
    virtual bool refreshTableOnSave()
    {
      return true;
    }

    /*!
    ** \brief when the delete button is pushed
    **
    **
    */
    virtual bool onDelete()
    {
      return true;
    }

    /*!
    ** \brief when the print button is pushed
    **
    **
    */
    virtual bool onPrint()
    {
      return true;
    }

    /*!
    ** \brief when the unlock button is pushed
    **
    **
    */
    virtual bool onUnlock()
    {
      return true;
    }

    virtual std::string additional()
    {
      return "";
    }

    virtual bool onAdditional( const std::string & buttonText )
    {
      return true;
    }

    virtual void popupMessage( const std::string & message )
    {
      Wt::WObject::addChild( std::make_unique<Wtx::PopupMessage>(message) );
    }

    virtual Wtx::MessageBox *  messageBox( const std::string & message )
    {
      return Wt::WObject::addChild( std::make_unique<Wtx::MessageBox>(message) );
    }

    void save()
    {
      m_doSave.emit();
    }

    void close()
    {
      m_doClose.emit();
    }

    void deleteItem( bool noask = true )
    {
      m_doDeleteItem.emit( noask );
    }

    void refresh()
    {
      m_doRefresh.emit();
    }

    Wt::Signal<>       & doSave()       { return m_doSave       ; }
    Wt::Signal<>       & doClose()      { return m_doClose      ; }
    Wt::Signal< bool > & doDeleteItem() { return m_doDeleteItem ; }
    Wt::Signal<>       & doRefresh()    { return m_doRefresh    ; }

  protected:

    Wt::Signal<>       m_doSave       ;
    Wt::Signal<>       m_doClose      ;
    Wt::Signal< bool > m_doDeleteItem ;
    Wt::Signal<>       m_doRefresh    ;

  private:

    std::string m_templateName;

}; // endclass DetailForm


  } // endnamespace Dbo
} // endnamespace Wtx

#endif // __WTX_DBO_DETAILFORM_H___
