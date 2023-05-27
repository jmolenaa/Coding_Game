#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef struct  s_cell
{
    int type; // 0 for empty, 1 for eggs, 2 for crystal
    int resources; // the initial amount of eggs/crystals on this cell
    int neigh_0;  // the index of the neighbouring cell for each direction
    int neigh_1;
    int neigh_2;
    int neigh_3;
    int neigh_4;
    int neigh_5;
    int my_ants;
    int opp_ants;
}       t_cell;

int find_highest_gold(t_cell cell_array[], int number_of_cells)
{
    int highest = 0;
    int highest_index = -1;
    for (int i = 0; i < number_of_cells; i++){
        if ((cell_array[i]).resources > highest && \
        (cell_array[i]).type == 2)
        {
            highest = (cell_array[i]).resources;
            highest_index = i;
        }
    }
    return (highest_index);
}

int find_highest_egg(t_cell cell_array[], int number_of_cells)
{
    int highest = 0;
    int highest_index = -1;
    for (int i = 0; i < number_of_cells; i++){
        if ((cell_array[i]).resources > highest && \
        (cell_array[i]).type == 1)
        {
            highest = (cell_array[i]).resources;
            highest_index = i;
        }
    }
    return (highest_index);
}

int main()
{
    // amount of hexagonal cells in this map
    int number_of_cells;
    scanf("%d", &number_of_cells);
	t_cell	cell_array[number_of_cells];
    for (int i = 0; i < number_of_cells; i++) {
        scanf("%d%d%d%d%d%d%d%d", &(cell_array[i]).type, &(cell_array[i]).resources, \
        &(cell_array[i]).neigh_0, &(cell_array[i]).neigh_1, &(cell_array[i]).neigh_2, &(cell_array[i]).neigh_3, &(cell_array[i]).neigh_4, &(cell_array[i]).neigh_5);
    (cell_array[i]).my_ants = 0;
    (cell_array[i]).opp_ants = 0;
    }
    // printf("MESSAGE : %d, %d, %d, %d, %d, %d, %d, %d\n", cell_array[0].type, cell_array[0].initial_resources, \
   // cell_array[0].neigh_0, cell_array[0].neigh_1, cell_array[0].neigh_2, cell_array[0].neigh_3, cell_array[0].neigh_4, cell_array[0].neigh_5);
    int number_of_bases;
    scanf("%d", &number_of_bases);
    int my_base_array[number_of_bases];
    int opp_base_array[number_of_bases];
    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &my_base_array[i]);
    }
    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &opp_base_array[i]);
    }

    // game loop
    int highest_index_gold;
    int highest_index_egg;
    int harvested_egg = 0;
    highest_index_gold = find_highest_gold(cell_array, number_of_cells);
    highest_index_egg = find_highest_egg(cell_array, number_of_cells);

    while (1) {
        for (int i = 0; i < number_of_cells; i++) {
            scanf("%d%d%d", &(cell_array[i]).resources, &(cell_array[i]).my_ants, &(cell_array[i]).opp_ants);
        }
        if ((cell_array[highest_index_egg]).resources == 0 && harvested_egg == 0)
        {
            harvested_egg = 1;
            // highest_index_egg = find_highest_egg(cell_array, number_of_cells);
        }
        if ((cell_array[highest_index_gold]).resources == 0 && harvested_egg == 1)
            highest_index_gold = find_highest_gold(cell_array, number_of_cells);
        if (harvested_egg == 0)// WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
            printf("LINE %d %d %d\n", my_base_array[0], highest_index_egg, 1);
        else
            printf("LINE %d %d %d\n", my_base_array[0], highest_index_gold, 1);
    }

    return 0;
}