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


#ifndef __WTX_DBO_FORMWIDGETWRAPPER_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_FORMWIDGETWRAPPER_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

namespace Wtx {
  namespace Dbo {

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
      m_prevValue = widget-> valueText().toUTF8();
      std::cout << __FILE__ << ":" << __LINE__ << " " << field() << std::endl;

    }

    Wt::Signal<FormWidgetWrapper*> & focussed()
    {
      return m_focussed;
    }

    Wt::Signal<FormWidgetWrapper*> & blurred()
    {
      return m_blurred;
    }

    Wt::WFormModel * model() const
    {
      return m_model;
    }

    Wt::WFormModel::Field field() const
    {
      return m_field;
    }

    Wt::WFormWidget * widget() const
    {
      return m_widget;
    }

    const std::string & previousValue() const
    {
      return m_prevValue;
    }

  private:

    void on_focussed()
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      m_focussed.emit(this);
    }

    void on_blurred()
    {
      m_blurred.emit(this);
    }

    Wt::WFormModel * m_model = nullptr;
    Wt::WFormModel::Field m_field = nullptr;
    Wt::WFormWidget * m_widget = nullptr;

    Wt::Signal<FormWidgetWrapper*> m_focussed;
    Wt::Signal<FormWidgetWrapper*> m_blurred;

    std::string m_prevValue;

}; // endclass FormWidgetWrapper

  } // endnamespace Dbo {
} // endnamespace Wtx {

#endif // __WTX_DBO_FORMWIDGETWRAPPER_H___


