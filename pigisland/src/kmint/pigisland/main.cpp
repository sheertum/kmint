#include "kmint/main.hpp" // voor de main loop
#include "kmint/math/intersection.hpp"
#include "kmint/math/rectangle.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/AStar.h"
#include "Evolution.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include "kmint/random.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <functional>

using namespace kmint;

void evaluatePopulation(play::stage& s) {
    double sharkLikeNess = 0;
    double boatLikeNess = 0;
    int actorCount = 0;
    for (const auto& it : s)
    {
        if (typeid(it) == typeid(pigisland::pig))
        {
            actorCount++;
            uint16_t tempSharkLike = ((pigisland::pig&)it)._sharkLikeNess;
            uint16_t tempBoatLike = ((pigisland::pig&)it)._boatFetisj;

            sharkLikeNess += pigisland::pig::toFleeSeekValue(tempSharkLike);
            boatLikeNess += pigisland::pig::toFleeSeekValue(tempBoatLike);
        }
    }

    sharkLikeNess /= actorCount;
    boatLikeNess /= actorCount;

    std::cout << "SharkLikeNess: " << std::to_string(sharkLikeNess) << "\t" << "BoatLikeNess: " << std::to_string(boatLikeNess) << std::endl;
}

std::vector<math::vector2d> new_random_pig_locations(std::size_t n) {
    // 9, 0 --- 24, 0
    // |        |
    // 9, 22    24, 22

    std::vector<math::vector2d> result;
    result.resize(n);

    for (auto& it : result) {
        float x = random_int((9 * 32) + 16, (24 * 32) + 16);
        float y = random_int((0 * 32) + 16, (22 * 32) + 16);
        it = math::vector2d{ x,y };
    }

    return result;
}

int main() {
  // een app object is nodig om
  ui::app app{};

  //  maak een venster aan
  ui::window window{app.create_window({1024, 768}, "pigisland", 1.0)};

  // maak een podium aan
  play::stage s{{1024, 768}};

  auto map = pigisland::map();
  auto &graph = map.graph();
  s.build_actor<play::background>(math::size(1024, 768),
                                  graphics::image{map.background_image()});
  s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());
  s.build_actor<pigisland::boat>(graph,
                                 pigisland::find_node_of_kind(graph, '1'));
  pigisland::shark* shark = &s.build_actor<pigisland::shark>(graph,
                                  pigisland::find_node_of_kind(graph, 'K'));
  shark->resetPigs = [&]() {
      s.reset = true;
  };
  //for (auto& node : path) {
  //    node->tag(kmint::graph::node_tag::path);
  //}



  auto locs = new_random_pig_locations(100);
  for (auto loc : locs) {
    s.build_actor<pigisland::pig>(loc);
  }

  // Maak een event_source aan (hieruit kun je alle events halen, zoals
  // toetsaanslagen)
  ui::events::event_source event_source{};
  
  evaluatePopulation(s);

  // main_loop stuurt alle actors aan.
  main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
    // gebruik dt om te kijken hoeveel tijd versterken is
    // sinds de vorige keer dat deze lambda werd aangeroepen
    // loop controls is een object met eigenschappen die je kunt gebruiken om de
    // main-loop aan te sturen.
      if (s.reset) {
          auto locs = new_random_pig_locations(100);
          std::vector<std::vector<uint16_t>> newPigis = pigisland::Evolution::getInstance().generateGeneration(100);

          for (auto loc : locs) {
              pigisland::pig& piggy = s.build_actor<pigisland::pig>(loc);
              piggy.setData(newPigis.back());
              newPigis.pop_back();
          }
          s.reset = false;
          evaluatePopulation(s);
      }

    

    for (ui::events::event &e : event_source) {
      // event heeft een methode handle_quit die controleert
      // of de gebruiker de applicatie wilt sluiten, en zo ja
      // de meegegeven functie (of lambda) aanroept om met het
      // bijbehorende quit_event
      //
      e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
      e.handle_key_up([&](auto ke) {
        switch (ke.key) {
        case ui::events::key::p:
          ctl.pause = !ctl.pause;
          break;
        case ui::events::key::r:
          ctl.render = !ctl.render;
          break;
        case ui::events::key::n:
          ctl.time_scale /= 2.0;
          break;
        case ui::events::key::m:
          ctl.time_scale *= 2.0;
          break;
        case ui::events::key::d:
          ctl.debug_overlay = !ctl.debug_overlay;
        default:
          break;
        }
      });
    }
  });
}
