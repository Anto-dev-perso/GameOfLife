#pragma once

#include "Game/Board.hpp"

namespace UTILITIES {

/****************************************  Still lifes patterns ***************************************/

    static gridOfCells blockPattern({{{false}, {false}, {false}, {false}},
                                     {{false}, {true},  {true},  {false}},
                                     {{false}, {true},  {true},  {false}},
                                     {{false}, {false}, {false}, {false}}});

    static gridOfCells beeHivePattern({{{false}, {false}, {false}, {false}, {false}, {false}},
                                       {{false}, {false}, {true},  {true},  {false}, {false}},
                                       {{false}, {true},  {false}, {false}, {true},  {false}},
                                       {{false}, {false}, {true},  {true},  {false}, {false}},
                                       {{false}, {false}, {false}, {false}, {false}, {false}}});

    static gridOfCells loafPattern({{{false}, {false}, {false}, {false}, {false}, {false}},
                                    {{false}, {false}, {true},  {true},  {false}, {false}},
                                    {{false}, {true},  {false}, {false}, {true},  {false}},
                                    {{false}, {false}, {true},  {false}, {true},  {false}},
                                    {{false}, {false}, {false}, {true},  {false}, {false}},
                                    {{false}, {false}, {false}, {false}, {false}, {false}}});

    static gridOfCells boatPattern({{{false}, {false}, {false}, {false}, {false}, {false}},
                                    {{false}, {true},  {true},  {false}, {false}, {false}},
                                    {{false}, {true},  {false}, {true},  {false}, {false}},
                                    {{false}, {false}, {true},  {false}, {false}, {false}},
                                    {{false}, {false}, {false}, {false}, {false}, {false}}});

    static gridOfCells tubPattern({{{false}, {false}, {false}, {false}, {false}},
                                   {{false}, {false}, {true},  {false}, {false}},
                                   {{false}, {true},  {false}, {true},  {false}},
                                   {{false}, {false}, {true},  {false}, {false}},
                                   {{false}, {false}, {false}, {false}, {false}}});


/****************************************  Oscillators patterns ***************************************/

    static gridOfCells blinkerPatternP1({{{false}, {false}, {false}, {false}, {false}},
                                         {{false}, {false}, {true},  {false}, {false}},
                                         {{false}, {false}, {true},  {false}, {false}},
                                         {{false}, {false}, {true},  {false}, {false}},
                                         {{false}, {false}, {false}, {false}, {false}}});
    static gridOfCells blinkerPatternP2({{{false}, {false}, {false}, {false}, {false}},
                                         {{false}, {false}, {false}, {false}, {false}},
                                         {{false}, {true},  {true},  {true},  {false}},
                                         {{false}, {false}, {false}, {false}, {false}},
                                         {{false}, {false}, {false}, {false}, {false}}});

    static gridOfCells toadPatternP1({{{false}, {false}, {false}, {false}, {false}, {false}},
                                      {{false}, {false}, {false}, {false}, {false}, {false}},
                                      {{false}, {false}, {true},  {true},  {true},  {false}},
                                      {{false}, {true},  {true},  {true},  {false}, {false}},
                                      {{false}, {false}, {false}, {false}, {false}, {false}},
                                      {{false}, {false}, {false}, {false}, {false}, {false}}});

    static gridOfCells toadPatternP2({{{false}, {false}, {false}, {false}, {false}, {false}},
                                      {{false}, {false}, {false}, {true},  {false}, {false}},
                                      {{false}, {true},  {false}, {false}, {true},  {false}},
                                      {{false}, {true},  {false}, {false}, {true},  {false}},
                                      {{false}, {false}, {true},  {false}, {false}, {false}},
                                      {{false}, {false}, {false}, {false}, {false}, {false}}});


    static gridOfCells beaconPatternP1({{{false}, {false}, {false}, {false}, {false}, {false}},
                                        {{false}, {true},  {true},  {false}, {false}, {false}},
                                        {{false}, {true},  {true},  {false}, {false}, {false}},
                                        {{false}, {false}, {false}, {true},  {true},  {false}},
                                        {{false}, {false}, {false}, {true},  {true},  {false}},
                                        {{false}, {false}, {false}, {false}, {false}, {false}}});

    static gridOfCells beaconPatternP2({
                                        {{false}, {false}, {false}, {false}, {false}, {false}},
                                        {{false}, {true},  {true},  {false}, {false}, {false}},
                                        {{false}, {true},  {false}, {false}, {false}, {false}},
                                        {{false}, {false}, {false}, {false}, {true},  {false}},
                                        {{false}, {false}, {false}, {true},  {true},  {false}},
                                        {{false}, {false}, {false}, {false}, {false}, {false}}});


    static gridOfCells pulsarPatternP1({
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {false}},
                                               {{false}, {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {false}},
                                               {{false}, {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {false}},
                                               {{false}, {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {false}},
                                               {{false}, {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {true},  {false}, {false}, {false}, {false}, {true},  {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {true},  {true},  {true},  {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}}}});
    static gridOfCells pulsarPatternP3({
   {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {true}, {false}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {false}, {true}, {false}, {false}},
   {{false}, {false}, {true}, {true}, {true}, {false}, {true}, {true}, {false}, {true}, {true}, {false}, {true}, {true}, {true}, {false}, {false}},
   {{false}, {false}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {true}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {true}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {true}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {true}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {false}, {false}},
   {{false}, {false}, {true}, {true}, {true}, {false}, {true}, {true}, {false}, {true}, {true}, {false}, {true}, {true}, {true}, {false}, {false}},
   {{false}, {false}, {true}, {false}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {false}, {true}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}},
   {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
   {{{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}}}});
    static gridOfCells pulsarPatternP2({
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {true}, {true}, {true}, {false}, {false}, {true}, {true}, {false}, {true}, {true}, {false}, {false}, {true}, {true}, {true}, {false}},
                                               {{false}, {false}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {true}, {false}, {false}, {false}},
                                               {{false}, {true}, {true}, {true}, {false}, {false}, {true}, {true}, {false}, {true}, {true}, {false}, {false}, {true}, {true}, {true}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {true}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}, {true}, {false}, {false}, {false}, {false}, {false}},
                                               {{{false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}, {false}}}});
// TODO maybe add the others ?

/****************************************  Functions ***************************************/
    void compareGrid(const gridOfCells &grid, const gridOfCells &expected);

    void dumpGrid(const gridOfCells &grid);
};
