/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/control_node.hpp"

namespace hesiod::cnode
{

ExpandShrinkDirectional::ExpandShrinkDirectional(std::string id) : Filter(id)
{
  LOG_DEBUG("ExpandShrinkDirectional::ExpandShrinkDirectional()");
  this->node_type = "ExpandShrinkDirectional";
  this->category = category_mapping.at(this->node_type);

  this->attr["ir"] = NEW_ATTR_INT(4, 1, 128);
  this->attr["angle"] = NEW_ATTR_FLOAT(0.f, -180.f, 180.f);
  this->attr["shrink"] = NEW_ATTR_BOOL(false);
  this->attr["aspect_ratio"] = NEW_ATTR_FLOAT(0.2f, 0.f, 1.f);
  this->attr["anisotropy"] = NEW_ATTR_FLOAT(1.f, 0.f, 1.f);

  this->attr_ordered_key = {"ir",
                            "angle",
                            "shrink",
                            "aspect_ratio",
                            "anisotropy"};
}

void ExpandShrinkDirectional::compute_filter(hmap::HeightMap &h,
                                             hmap::HeightMap *p_mask)
{
  LOG_DEBUG("computing filter node [%s]", this->id.c_str());

  // core operator
  std::function<void(hmap::Array &, hmap::Array *)> lambda;

  if (GET_ATTR_BOOL("shrink"))
    lambda = [this](hmap::Array &x, hmap::Array *p_mask)
    {
      hmap::shrink_directional(x,
                               GET_ATTR_INT("ir"),
                               GET_ATTR_FLOAT("angle"),
                               GET_ATTR_FLOAT("aspect_ratio"),
                               GET_ATTR_FLOAT("anisotropy"),
                               p_mask);
    };
  else
    lambda = [this](hmap::Array &x, hmap::Array *p_mask)
    {
      hmap::expand_directional(x,
                               GET_ATTR_INT("ir"),
                               GET_ATTR_FLOAT("angle"),
                               GET_ATTR_FLOAT("aspect_ratio"),
                               GET_ATTR_FLOAT("anisotropy"),
                               p_mask);
    };

  hmap::transform(h, p_mask, lambda);
  h.smooth_overlap_buffers();
}

} // namespace hesiod::cnode
