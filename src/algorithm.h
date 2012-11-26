/*
    algorithm.h - (c) Michael Weber, Jr. (2012)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "steelbars.h"
#include <stdio.h>

class Algorithm
{
public:
    // These are the values that we need for the section
    double b;   // width of the section
    double h;   // height of the section
    bool tied;  // whether we are using tied or spiral reinforcing
    double fc;  // compression strength of concrete
    double fs;  // strength of steel
    double Es;  // young's module of steel
    int steelRows;  // number of reinforcing steel rows
    BarRow* barrows;// the actual rows of steel

    // These are values for the calculations
    double compression_strain;
    double tension_strain;

    // The results
    double results[6][2];

    // For the graph we need to calculate a bunch of points
    int graphCount;                 // The number of points we calculate
    double **unfactoredPoints;    // This is for the outside points
    double **factoredPoints;      // This is for the inside points

    // This runs the calculations and puts the results in results (suprising, right?)
    void calculate();
    // This runs the points for the graph for right now
    void calculate2();
    // For debug purposes
    void dump();
};

#endif // ALGORITHM_H
