/*****************************************************************************
	Emp

    Copyright (C) 2018  German Molina (germolinal@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/

#include <typeinfo>

//#include "api/common.h" //  for filling optionsets with LUA tables
#include "./optionset.h"
#include <fstream>

size_t OptionSet::size() const
{
  return data.size();
}

bool OptionSet::hasOption(std::string opt) const
{
  return (data.find(opt) != data.end());
}

bool OptionSet::isEqual(OptionSet * other)
{

  // return false if both do not have the same size
  if (data.size() != other->size())
    return false;

  // Check if they are empty (we now both sizes are equal)
  if (data.size() == 0)
    return true;

  for (json::iterator it = data.begin(); it != data.end(); ++it) {   

    std::string k = it.key();
    auto v = it.value();
    // If the option does not exists || it is different, return false
    if (!(other->hasOption(k)) || v != other->getOption<decltype(v)>(k)) {
      return false;      
    }
  }
  return true;
}



void OptionSet::print(char * filename)
{
  std::ofstream file;
  if (filename != NULL) {
    file.open(filename);
  }

  for (json::iterator it = data.begin(); it != data.end(); ++it) {
    if (filename == NULL) {
     std::cout << "-" << it.key() << " " << it.value() << "\n";
    }
    else {
      file << "-" << it.key() << " " << it.value() << "\n";
    }
  }

  if (filename != NULL) {
    file.close();
  }
}


std::string OptionSet::getInlineVersion()
{

  std::string res = "";
  for (json::iterator it = data.begin(); it != data.end(); ++it) {
    if (it.value().is_number_integer()) {
      res = res + " -" + it.key() + " " + std::to_string(getOption<int>(it.key()));    
    }
    else {
      res = res + " -" + it.key() + " " + std::to_string(getOption<double>(it.key()));
    }
  }
  return res;
}

json::iterator OptionSet::begin()
{
    return data.begin();
}

json::iterator OptionSet::end()
{
    return data.end();
}
