/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/control_node.hpp"

namespace hesiod::cnode
{

WaveSquare::WaveSquare(std::string     id,
                       hmap::Vec2<int> shape,
                       hmap::Vec2<int> tiling,
                       float           overlap)
    : ControlNode(id), Primitive(id, shape, tiling, overlap)
{
  LOG_DEBUG("WaveSquare::WaveSquare()");
  this->node_type = "WaveSquare";
  this->category = category_mapping.at(this->node_type);

  this->attr["kw"] = NEW_ATTR_FLOAT(2.f, 0.01f, 128.f);
  this->attr["angle"] = NEW_ATTR_FLOAT(0.f, -180.f, 180.f);
  this->attr["phase_shift"] = NEW_ATTR_FLOAT(0.f, -180.f, 180.f);

  this->attr_ordered_key = {"kw", "angle", "phase_shift"};

  this->remove_port("dy");
  this->update_inner_bindings();
}

void WaveSquare::compute()
{
  LOG_DEBUG("computing WaveSquare node [%s]", this->id.c_str());

  hmap::fill(this->value_out,
             (hmap::HeightMap *)this->get_p_data("dx"),
             [this](hmap::Vec2<int>   shape,
                    hmap::Vec2<float> shift,
                    hmap::Vec2<float> scale,
                    hmap::Array      *p_noise_x)
             {
               return hmap::wave_square(shape,
                                        GET_ATTR_FLOAT("kw"),
                                        GET_ATTR_FLOAT("angle"),
                                        GET_ATTR_FLOAT("phase_shift"),
                                        p_noise_x,
                                        shift,
                                        scale);
             });

  this->post_process_heightmap(this->value_out);
}

} // namespace hesiod::cnode
