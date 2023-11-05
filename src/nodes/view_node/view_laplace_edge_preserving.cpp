/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewLaplaceEdgePreserving::ViewLaplaceEdgePreserving(std::string id)
    : ViewNode(), hesiod::cnode::LaplaceEdgePreserving(id)
{
  this->set_p_control_node((gnode::Node *)this);
  this->set_preview_port_id("output");
  this->set_view3d_elevation_port_id("output");
}

bool ViewLaplaceEdgePreserving::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  ImGui::SliderFloat("talus_global", &this->talus_global, 0.f, 16.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("sigma", &this->sigma, 0.f, 0.25f);
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderInt("iterations", &this->iterations, 1, 20);
  has_changed |= this->trigger_update_after_edit();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

void ViewLaplaceEdgePreserving::serialize_save(cereal::JSONOutputArchive &ar)
{
  ar(cereal::make_nvp("sigma", this->sigma));
  ar(cereal::make_nvp("iterations", this->iterations));
  ar(cereal::make_nvp("talus_global", this->talus_global));
}

void ViewLaplaceEdgePreserving::serialize_load(cereal::JSONInputArchive &ar)
{
  ar(cereal::make_nvp("sigma", this->sigma));
  ar(cereal::make_nvp("iterations", this->iterations));
  ar(cereal::make_nvp("talus_global", this->talus_global));
}

} // namespace hesiod::vnode
