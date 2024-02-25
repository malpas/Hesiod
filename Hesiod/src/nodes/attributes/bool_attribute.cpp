/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "highmap.hpp"
#include "macrologger.h"
#include <imgui.h>

#include "hesiod/attribute.hpp"
#include "hesiod/gui.hpp"

namespace hesiod
{

BoolAttribute::BoolAttribute(bool value) : value(value)
{
}

bool BoolAttribute::get()
{
  return value;
}

bool BoolAttribute::render_settings(std::string label)
{
  bool has_changed = false;
  has_changed |= ImGui::Checkbox(label.c_str(), &this->value);
  return has_changed;
}

bool BoolAttribute::serialize_json_v2(std::string fieldName, nlohmann::json& outputData) 
{ 
  outputData[fieldName] = this->value;
  return true; 
}

bool BoolAttribute::deserialize_json_v2(std::string fieldName, nlohmann::json& inputData) 
{ 
  if(inputData[fieldName].is_boolean() == false)
  {
    LOG_DEBUG("[%s] Attribute %s is not a boolean.", __FUNCTION__, fieldName.data());
    return false;
  }

  this->value = inputData[fieldName].get<bool>();
  return true; 
}

} // namespace hesiod
