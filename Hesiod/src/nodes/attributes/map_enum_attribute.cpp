/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "highmap.hpp"
#include "macrologger.h"
#include <imgui.h>

#include "hesiod/attribute.hpp"
#include "hesiod/gui.hpp"
#include "nlohmann/json_fwd.hpp"

namespace hesiod
{

MapEnumAttribute::MapEnumAttribute(std::map<std::string, int> value)
    : value(value)
{
  // default choice is first item in the list
  this->choice = this->value.begin()->first;
}

int MapEnumAttribute::get()
{
  return this->value.at(this->choice);
}

std::map<std::string, int> MapEnumAttribute::get_map()
{
  return this->value;
}

void MapEnumAttribute::set(std::string new_choice)
{
  this->choice = new_choice;
}

bool MapEnumAttribute::render_settings(std::string label)
{
  bool has_changed = false;

  int choice_index = this->value.at(this->choice);

  has_changed |= hesiod::gui::listbox_map_enum(this->value,
                                               choice_index,
                                               128.f);

  // reverse map to get the key (string) based on the value chosen (int)
  for (auto &[k, v] : this->value)
    if (v == choice_index)
    {
      this->choice = k;
      break;
    }

  return has_changed;
}

bool MapEnumAttribute::serialize_json_v2(std::string     field_name,
                                         nlohmann::json &output_data)
{
  for (std::map<std::string, int>::iterator current_iterator =
           this->value.begin();
       current_iterator != this->value.end();
       current_iterator++)
  {
    output_data[field_name]["value"][current_iterator->first] =
        current_iterator->second;
  }

  output_data[field_name]["choice"] = this->choice;

  return true;
}

bool MapEnumAttribute::deserialize_json_v2(std::string     field_name,
                                           nlohmann::json &input_data)
{
  if (input_data[field_name].is_object() == false ||
      input_data[field_name]["value"].is_object() == false ||
      input_data[field_name]["choice"].is_string() == false)
  {
    return false;
  }

  this->value.clear();

  for (auto &[currentKey, currentValue] :
       input_data[field_name]["value"].items())
  {
    this->value[currentKey] = currentValue.get<int>();
  }

  this->choice = input_data[field_name]["choice"].get<std::string>();

  return true;
}

} // namespace hesiod
