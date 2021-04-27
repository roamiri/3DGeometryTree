#include <iostream>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 3, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef bg::model::polygon<point> polygon3D;

class node
{
    // Private attribute
public:
    float m_xx;
    float m_yy;
    float m_zz;
    float m_width;
    float m_length;
    float m_height;
    point m_location;
    point m_pmin;  // lower left point
    point m_pmax;  // upper right point
    box m_box;
    uint32_t m_id;
public:
    // Constructor
    node(float x, float y, float z, float width, float length, float height, uint32_t id){
        m_xx = x; m_yy=y; m_zz=z;
        m_width = width; m_length = length;
        m_height = height;
        float w = width/2.; //x
        float l = length/2.; //y
        float h = height/2.; //z
        m_location = point(x,y, z);
        m_pmin = point(x-w, y-l, z-h);
        m_pmax = point(x+w, y+l, z+h);
        m_box = box(m_pmin, m_pmax);
        m_id = id;
    }

    float get_x(){return m_xx;}
    float get_y(){return m_yy;}
    float get_z(){return m_zz;}
    point get_loc(){return m_location;}
    
};

typedef std::pair<point, boost::shared_ptr<node>> value;
typedef boost::shared_ptr<node> an_ptr;

class container
{
public:
    bgi::rtree< value, bgi::quadratic<16> > m_tree;
    float m_centerX;
    float m_centerY;
    float m_centerZ;
    float m_width;
    float m_length;
    float m_height;
    
public:
    container(float x, float y, float z, float width, float length, float height){
        m_centerX = x;
        m_centerY = y;
        m_centerZ = z;
        m_width = width;
        m_length = length;
        m_height = height;
    }
    
    float get_x(){return m_centerX;}
    float get_y(){return m_centerY;}
    float get_z(){return m_centerZ;}
    void add_node(node nn){
        an_ptr anchor = boost::shared_ptr<node>(&nn);
        std::cout << "X = " << anchor->get_x() << std::endl;
        m_tree.insert(std::make_pair(anchor->get_loc(), anchor));
    }
    
    void remove_node(node nn){
    an_ptr anchor = boost::shared_ptr<node>(&nn);
    m_tree.remove(std::make_pair(anchor->get_loc(), anchor));
    }
    
    void circular_query(float x, float y, float z, float radius){
        point sought = point(x,y,z);
        std::vector<value> results;
        m_tree.query(bgi::satisfies([&](value const& v) {return boost::geometry::distance(v.first, sought) < 2*radius;}), std::back_inserter(results));
        std::cout << "size =" << results.size() << std::endl;
    }
    
    
};
