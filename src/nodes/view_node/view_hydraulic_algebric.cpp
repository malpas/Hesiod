/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewHydraulicAlgebric::ViewHydraulicAlgebric(std::string id)
    : hesiod::cnode::ControlNode(id), ViewNode(id),
      hesiod::cnode::HydraulicAlgebric(id)
{
  this->set_preview_port_id("output");
  this->set_view3d_elevation_port_id("output");
}

bool ViewHydraulicAlgebric::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  ImGui::SliderFloat("talus_global", &this->talus_global, 0.f, 32.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderInt("ir", &this->ir, 1, 128);
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("c_erosion", &this->c_erosion, 0.001f, 0.1f);
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("c_deposition", &this->c_deposition, 0.001f, 0.1f);
  has_changed |= this->trigger_update_after_edit();

  ImGui::InputInt("iterations", &this->iterations);
  has_changed |= this->trigger_update_after_edit();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

} // namespace hesiod::vnode
