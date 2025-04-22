/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <iostream>

#include "Contact.h"

Contact::Contact( const std::string email_ )
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << email_ << std::endl;

}

