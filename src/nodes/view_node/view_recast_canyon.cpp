/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/gui.hpp"
#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewRecastCanyon::ViewRecastCanyon(std::string id)
    : ViewNode(), hesiod::cnode::RecastCanyon(id)
{
  this->set_p_control_node((gnode::Node *)this);
  this->set_preview_port_id("output");
}

bool ViewRecastCanyon::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  ImGui::SliderFloat("vcut", &this->vcut, 0.f, 2.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("gamma", &this->gamma, 0.01f, 10.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

void ViewRecastCanyon::serialize_save(cereal::JSONOutputArchive &ar)
{
  ar(cereal::make_nvp("vcut", this->vcut));
  ar(cereal::make_nvp("gamma", this->gamma));
}

void ViewRecastCanyon::serialize_load(cereal::JSONInputArchive &ar)
{
  ar(cereal::make_nvp("vcut", this->vcut));
  ar(cereal::make_nvp("gamma", this->gamma));
}

} // namespace hesiod::vnode