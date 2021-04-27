
#include <boost/python.hpp>
#include "libIndex.hpp"
// #include "core/node.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(pytree)
{
    class_< node >("node", init<float, float, float, float, float, float, uint32_t>())
      .def_readonly("id", &node::m_id)
      .def_readonly("x", &node::m_xx)
      .def_readonly("y", &node::m_yy)
      .def_readonly("z", &node::m_zz)
      .def_readonly("w", &node::m_width)
      .def_readonly("l", &node::m_length)
      .def_readonly("h", &node::m_height)
      .def("getX", &node::get_x)
      .def("getY", &node::get_y)
      .def("getZ", &node::get_z)
      ;
      
    class_< container >("container", init<float, float, float, float, float, float>())
      .def_readonly("centerX", &container::m_centerX)
      .def_readonly("centerY", &container::m_centerY)
      .def_readonly("w", &container::m_width)
      .def_readonly("h", &container::m_height)
      .def("getcenterX", &container::get_x)
      .def("getcenterY", &container::get_y)
      .def("add_node", &container::add_node)
      .def("remove_node", &container::remove_node)
      .def("circular_query", &container::circular_query)
      ;
      
}
