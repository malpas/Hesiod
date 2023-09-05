/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/gui.hpp"
#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewRecurve::ViewRecurve(std::string id)
    : ViewNode(), hesiod::cnode::Recurve(id)
{
  this->set_p_control_node((gnode::Node *)this);
  this->set_preview_port_id("output");
  this->set_view2d_port_id("output");
}

bool ViewRecurve::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  ImGui::TextUnformatted("Amplitude curve");
  if (hesiod::gui::drag_float_vector(this->curve, true, true, 0.f, 1.f))
    this->force_update();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

} // namespace hesiod::vnode