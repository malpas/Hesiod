/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "highmap.hpp"
#include "highmap/vector.hpp"
#include "macrologger.h"
#include <imgui.h>

#include "hesiod/attribute.hpp"
#include "hesiod/gui.hpp"

namespace hesiod
{

RangeAttribute::RangeAttribute(hmap::Vec2<float> value) : value(value)
{
}

RangeAttribute::RangeAttribute(bool activate) : activate(activate)
{
}

hmap::Vec2<float> RangeAttribute::get()
{
  return value;
}

bool RangeAttribute::render_settings(std::string label)
{
  bool has_changed = false;

  if (ImGui::Checkbox(label.c_str(), &this->activate))
    has_changed = true;

  // if (this->activate)
  {
    ImGui::Indent();
    if (hesiod::gui::slider_vmin_vmax(this->value.x, this->value.y))
      has_changed = true;
    ImGui::Unindent();
  }

  return has_changed;
}

bool RangeAttribute::serialize_json_v2(std::string     field_name,
                                       nlohmann::json &output_data)
{
  output_data[field_name]["x"] = this->value.x;
  output_data[field_name]["y"] = this->value.y;
  output_data[field_name]["activate"] = this->activate;
  return true;
}

bool RangeAttribute::deserialize_json_v2(std::string     field_name,
                                         nlohmann::json &input_data)
{
  if (input_data[field_name].is_object() == false ||
      input_data[field_name]["x"].is_number() == false ||
      input_data[field_name]["y"].is_number() == false ||
      input_data[field_name]["activate"].is_boolean() == false)
  {
    LOG_DEBUG("Attribute %s is invalid.", field_name.data());
    return false;
  }

  this->value = hmap::Vec2<float>(input_data[field_name]["x"].get<float>(),
                                  input_data[field_name]["y"].get<float>());

  this->activate = input_data[field_name]["activate"].get<bool>();
  return true;
}

} // namespace hesiod
