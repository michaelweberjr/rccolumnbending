/*
    algorithm.cpp - (c) Michael Weber, Jr. (2012)

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

#include "algorithm.h"

/*
 * This is where all the calculation occurs
 * Each point is calculated in order
 * Point 1: Pure Compression
 * Point 2: Neutral Axis at the section height
 * Point 3: Zero Tension at the highest depth, all steel is still in compression
 * Point 4: Balance Point, half the section is in tension and the other in compression
 * Point 5: Some where in the transition zone, I would prefer at the point at tension controlled
 * Point 6: Pure Moment, not done
 * Point 7: Pure Tension
 *
 * I would like to appoligize in advanced to any OOP folks out there for the non-strictness of the code
 */

void Algorithm::calculate()
{
    // Calculate some values we might need
    double phi = tied ? 0.65 : 0.75; // set the phi factor

    // lets get the total area of steel
    double steelArea = 0.0;
    for(int i = 0; i < steelRows; i++)
            steelArea += barrows[i].area;

    // set beta1
    double beta1 = 0.85;
    if(fc > 4000 && fc < 8000) beta1 -= (fc-4000)/1000*0.05;
    else if(fc >= 8000) beta1 = 0.65;

    // find the largest depth to steel
    double d = 0.0;
    for(int i = 0; i < steelRows; i++)
        if(barrows[i].depth > d) d = barrows[i].depth;

    // Lets start with the first point, pure compression
    results[0][0] = 0.8*phi*(0.85*fc*(b*h-steelArea)+fs*steelArea);
    results[0][1] = 0.0;    // no moment

    // Point 2 - Neutral axis is at the concrete height
    //double es = 0.003 * (h - d) / h; // strain in steel at crushing
    double c = h; // neutral axis
    double a = beta1*c;
    double force_c = 0.85*fc*a*b;

    double *bar_row_strain = new double[steelRows];
    double *bar_row_stress = new double[steelRows];
    double *bar_row_force = new double[steelRows];
    double steel_force = 0.0;

    for(int i = 0; i < steelRows; i++)
    {
        // strain first
        bar_row_strain[i] = 0.003 * (c - barrows[i].depth) / c;

        // then the stress
        bar_row_stress[i] = bar_row_strain[i] * Es;
        if(bar_row_stress[i] > fs) bar_row_stress[i] = fs;
        else if(bar_row_stress[i] < -fs) bar_row_stress[i] = -fs;

        // next is the force
        if(barrows[i].depth < a) bar_row_force[i] = (bar_row_stress[i]-0.85*fc) * barrows[i].area;
        else bar_row_force[i] = bar_row_stress[i] * barrows[i].area;

        // finally we have the total force
        steel_force += bar_row_force[i];
    }

    // Calculate Pn and Mn
    results[1][0] =  phi * (steel_force + force_c);
    results[1][1] = 0.5*force_c*(h-a);
    for(int i = 0; i < steelRows; i++)
        results[1][1] += bar_row_force[i] * (0.5*h - barrows[i].depth);

    // Point 3 - Neutral axis is at the highest depth to steel, d
    c = d; // neutral axis
    a = beta1*c;
    force_c = 0.85*fc*a*b;

    steel_force = 0.0;

    for(int i = 0; i < steelRows; i++)
    {
        // strain first
        bar_row_strain[i] = 0.003 * (c - barrows[i].depth) / c;

        // then the stress
        bar_row_stress[i] = bar_row_strain[i] * Es;
        if(bar_row_stress[i] > fs) bar_row_stress[i] = fs;
        else if(bar_row_stress[i] < -fs) bar_row_stress[i] = -fs;

        // next is the force
        if(barrows[i].depth < a) bar_row_force[i] = (bar_row_stress[i]-0.85*fc) * barrows[i].area;
        else bar_row_force[i] = bar_row_stress[i] * barrows[i].area;

        // finally we have the total force
        steel_force += bar_row_force[i];
    }

    // Calculate Pn and Mn
    results[2][0] =  phi * (steel_force + force_c);
    results[2][1] = 0.5*force_c*(h-a);
    for(int i = 0; i < steelRows; i++)
        results[2][1] += bar_row_force[i] * (0.5*h - barrows[i].depth);

    // Point 4 - Balance Point
    double ey = fs/Es;
    c = 0.003 * d / (ey + 0.003);
    a = beta1*c;
    force_c = 0.85*fc*a*b;

    steel_force = 0.0;

    for(int i = 0; i < steelRows; i++)
    {
        // strain first
        bar_row_strain[i] = 0.003 * (c - barrows[i].depth) / c;

        // then the stress
        bar_row_stress[i] = bar_row_strain[i] * Es;
        if(bar_row_stress[i] > fs) bar_row_stress[i] = fs;
        else if(bar_row_stress[i] < -fs) bar_row_stress[i] = -fs;

        // next is the force
        if(barrows[i].depth < a) bar_row_force[i] = (bar_row_stress[i]-0.85*fc) * barrows[i].area;
        else bar_row_force[i] = bar_row_stress[i] * barrows[i].area;

        // finally we have the total force
        steel_force += bar_row_force[i];
    }

    // Calculate Pn and Mn
    results[3][0] =  phi * (steel_force + force_c);
    results[3][1] = 0.5*force_c*(h-a);
    for(int i = 0; i < steelRows; i++)
        results[3][1] += bar_row_force[i] * (0.5*h - barrows[i].depth);

    // Point 5 - Section becomes tension controlled, roughly
    ey = tension_strain;
    c = 0.003 * d / (ey + 0.003);
    a = beta1*c;
    force_c = 0.85*fc*a*b;

    steel_force = 0.0;

    for(int i = 0; i < steelRows; i++)
    {
        // strain first
        bar_row_strain[i] = 0.003 * (c - barrows[i].depth) / c;

        // then the stress
        bar_row_stress[i] = bar_row_strain[i] * Es;
        if(bar_row_stress[i] > fs) bar_row_stress[i] = fs;
        else if(bar_row_stress[i] < -fs) bar_row_stress[i] = -fs;

        // next is the force
        if(barrows[i].depth < a) bar_row_force[i] = (bar_row_stress[i]-0.85*fc) * barrows[i].area;
        else bar_row_force[i] = bar_row_stress[i] * barrows[i].area;

        // finally we have the total force
        steel_force += bar_row_force[i];
    }

    // Adjust the phi factor if we are more tension controlled
    if(ey > 0.002 && ey < 0.005) phi = (tied ? 0.65 : 0.75) + (ey-0.002) * (tied ? 250/3 : 50);
    if(ey >= 0.005) phi = 0.9;

    // Calculate Pn and Mn
    results[4][0] =  phi * (steel_force + force_c);
    results[4][1] = 0.5*force_c*(h-a);
    for(int i = 0; i < steelRows; i++)
        results[4][1] += bar_row_force[i] * (0.5*h - barrows[i].depth);

    // Point 7 - Pure Tension
    results[5][0] = 0.9 * steelArea * -fs;
    results[5][1] = 0.0;
}

// Debug function
// Checks to make sure the input is correct
void Algorithm::dump()
{
    printf("F'c = %lf\n", fc);
    printf("Fy = %lf\n", fs);
    printf("Ey = %lf\n", Es);
    printf("b = %lf\n", b);
    printf("h = %lf\n", h);
    printf("ties = %s\n", tied ? "true" : "false");
    printf("tension strain = %lf\n", tension_strain);
    printf("Number of rows = %d\n", steelRows);
    for(int i = 0; i < steelRows; i++)
        printf("Row %d: count = %d, depth = %lf, area = %lf\n", i+1, barrows[i].count, barrows[i].depth, barrows[i].area);
}

