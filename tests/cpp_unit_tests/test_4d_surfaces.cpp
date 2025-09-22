#include "openmc/constants.h"
#include "openmc/surface.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>

// Helper: build a TPlane XML node
pugi::xml_node make_tplane_xml(pugi::xml_document& doc, int id, double t0) {
  auto node = doc.append_child("surface");

  // Required <id>
  auto id_node = node.append_child("id");
  id_node.append_child(pugi::node_pcdata).set_value(std::to_string(id).c_str());

  // Required <type>
  auto type_node = node.append_child("type");
  type_node.append_child(pugi::node_pcdata).set_value("t-plane");

  // Coeffs (holds t0)
  auto coeffs_node = node.append_child("coeffs");
  coeffs_node.append_child(pugi::node_pcdata).set_value(std::to_string(t0).c_str());

  return node;
}

// ----------------------
// TPlane Basic Evaluation
// ----------------------
TEST_CASE("TPlane evaluate and sense") {
  pugi::xml_document doc;
  auto node = make_tplane_xml(doc, 1, 5.0);

  openmc::SurfaceTPlane plane(node);

  // A point before the plane in time
  openmc::Position r1{0.0, 0.0, 0.0, 2.0};
  REQUIRE_THAT(plane.evaluate(r1), Catch::Matchers::WithinAbs(-3.0, 1e-12));

  // A point after the plane in time
  openmc::Position r2{0.0, 0.0, 0.0, 7.0};
  REQUIRE_THAT(plane.evaluate(r2), Catch::Matchers::WithinAbs(2.0, 1e-12));
}

// ----------------------
// TPlane Distance
// ----------------------
TEST_CASE("TPlane distance") {
  pugi::xml_document doc;
  auto node = make_tplane_xml(doc, 2, 5.0);

  openmc::SurfaceTPlane plane(node);

  openmc::Position r{0.0, 0.0, 0.0, 2.0};
  openmc::Direction u{0.0, 0.0, 0.0, 1.0}; // moving forward in time

  // Should intersect at t=5 (Δt = 3)
  double d = plane.distance(r, u, false);
  REQUIRE_THAT(d, Catch::Matchers::WithinAbs(3.0, 1e-12));

  // Parallel in space (dt=0) → no intersection
  openmc::Direction u_parallel{0.0, 1.0, 0.0, 0.0};
  double d_par = plane.distance(r, u_parallel, false);
  REQUIRE_THAT(d_par, Catch::Matchers::WithinAbs(openmc::INFTY, 0.0));
}

// ----------------------
// TPlane Normal
// ----------------------
TEST_CASE("TPlane normal") {
  pugi::xml_document doc;
  auto node = make_tplane_xml(doc, 3, 5.0);

  openmc::SurfaceTPlane plane(node);

  openmc::Position r{0.0, 0.0, 0.0, 5.0};
  openmc::Direction n = plane.normal(r);

  // Normal should point in +t direction
  REQUIRE_THAT(n.t, Catch::Matchers::WithinAbs(1.0, 1e-12));
  REQUIRE(n.x == 0.0);
  REQUIRE(n.y == 0.0);
  REQUIRE(n.z == 0.0);
}
