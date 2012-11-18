/*
    steelbars.h - (c) Michael Weber, Jr. (2012)

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

#ifndef STEELBARS_H
#define STEELBARS_H

/*
 * This file defines the steel reinforcing bars
 * The Bar structure holds the basic bar information
 * The BarRow structure holds each row of steel in the concrete section
 * stdBars is the list of ASTM standard bars that are used
 */

struct Bar
{
    const char * name; // Name of the bar
    double d;          // Diameter of the bar (in)
    double area;       // Area of the bar (in^2)

    Bar(char * n_name, double n_d, double n_area)
        : name(n_name), d(n_d), area(n_area)
    {
        // Default constructor doesn't do anthing
    }
};

typedef struct
{
    int count;
    //Bar bar;
    double depth;
    double area;
} BarRow;

#endif // STEELBARS_H

