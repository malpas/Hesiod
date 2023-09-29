/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/gui.hpp"
#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewExpandShrinkDirectional::ViewExpandShrinkDirectional(std::string id)
    : ViewNode(), hesiod::cnode::ExpandShrinkDirectional(id)
{
  this->set_p_control_node((gnode::Node *)this);
  this->set_preview_port_id("output");
}

bool ViewExpandShrinkDirectional::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  ImGui::Checkbox("shrink", &this->shrink);
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderInt("ir", &this->ir, 1, 128);
  has_changed |= this->trigger_update_after_edit();

  float alpha = this->angle / 180.f * M_PI;
  ImGui::SliderAngle("angle", &alpha, -90.f, 90.f);
  this->angle = alpha / M_PI * 180.f;
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("aspect_ratio", &this->aspect_ratio, 0.f, 1.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("anisotropy", &this->anisotropy, 0.f, 1.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

void ViewExpandShrinkDirectional::serialize_save(cereal::JSONOutputArchive &ar)
{
  ar(cereal::make_nvp("ir", this->ir));
  ar(cereal::make_nvp("angle", this->angle));
  ar(cereal::make_nvp("aspect_ratio", this->aspect_ratio));
  ar(cereal::make_nvp("anisotropy", this->anisotropy));
  ar(cereal::make_nvp("shrink", this->shrink));
}

void ViewExpandShrinkDirectional::serialize_load(cereal::JSONInputArchive &ar)
{
  ar(cereal::make_nvp("ir", this->ir));
  ar(cereal::make_nvp("angle", this->angle));
  ar(cereal::make_nvp("aspect_ratio", this->aspect_ratio));
  ar(cereal::make_nvp("anisotropy", this->anisotropy));
  ar(cereal::make_nvp("shrink", this->shrink));
}

} // namespace hesiod::vnode