/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/gui.hpp"
#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewMixRGB::ViewMixRGB(std::string id)
    : hesiod::cnode::ControlNode(id), ViewNode(id), hesiod::cnode::MixRGB(id)
{
  this->set_preview_port_id("RGB");
}

bool ViewMixRGB::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  if (!this->get_p_data("t"))
  {
    ImGui::SliderFloat("t", &this->t, 0.f, 1.f, "%.2f");
    has_changed |= this->trigger_update_after_edit();
  }

  ImGui::Checkbox("sqrt_mix", &this->sqrt_mix);
  has_changed |= this->trigger_update_after_edit();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

} // namespace hesiod::vnode
