#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
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

typedef struct s_dijkstra
{
    int index;
    int steps;
    struct s_dijkstra *next;
}       t_dijkstra;

t_dijkstra  *make_new_dijkstra(int steps, int index)
{
    t_dijkstra  *new;

    new = calloc(sizeof(t_dijkstra), 1);
    new->steps = steps;
    new->index = index;
    new->next = NULL;
    return (new);
}

void    put_back(t_dijkstra **head, t_dijkstra *new)
{
    t_dijkstra *temp;

    temp = *head;
    if (temp == NULL)
        *head = new;
    else
    {
        while (temp->next != NULL)
            temp =temp->next;
        temp->next = new;
    }
}

int check_neigh(int index, t_dijkstra *head)
{
    t_dijkstra  *temp;

    temp = head;
    while (temp != NULL)
    {
        if (temp->index == index)
            return (0);
        temp = temp->next;
    }
    return (1);
}

void    make_new_locations(t_cell cell_array[], int index, int steps, t_dijkstra *head)
{
    if ((cell_array[index]).neigh_0 != -1)
    {
        if (check_neigh((cell_array[index]).neigh_0, head))
            put_back(&head, make_new_dijkstra(steps, (cell_array[index]).neigh_0));
    }
    if ((cell_array[index]).neigh_1 != -1)
    {
        if (check_neigh((cell_array[index]).neigh_1, head))
            put_back(&head, make_new_dijkstra(steps, (cell_array[index]).neigh_1));
    }
    if ((cell_array[index]).neigh_2 != -1)
    {
        if (check_neigh((cell_array[index]).neigh_2, head))
            put_back(&head, make_new_dijkstra(steps, (cell_array[index]).neigh_2));
    }
    if ((cell_array[index]).neigh_3 != -1)
    {
        if (check_neigh((cell_array[index]).neigh_3, head))
            put_back(&head, make_new_dijkstra(steps, (cell_array[index]).neigh_3));
    }
    if ((cell_array[index]).neigh_4 != -1)
    {
        if (check_neigh((cell_array[index]).neigh_4, head))
            put_back(&head, make_new_dijkstra(steps, (cell_array[index]).neigh_4));
    }
    if ((cell_array[index]).neigh_5 != -1)
    {
        if (check_neigh((cell_array[index]).neigh_5, head))
            put_back(&head, make_new_dijkstra(steps, (cell_array[index]).neigh_5));
    }
}

void    free_list(t_dijkstra *head)
{
    t_dijkstra  *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int find_path_between_cells(t_cell cell_array[], int index1, int index2)
{
    int steps = 0;
    t_dijkstra *end_loc = make_new_dijkstra(0, index2);
    t_dijkstra *temp;
    int         index_temp;


    temp = end_loc;
    while (1)
    {
        while (temp != NULL && temp->steps == steps)
        {
            index_temp = temp->index;
            if (temp->index == index1)
                return (free_list(end_loc), steps);
            make_new_locations(cell_array, index_temp, steps + 1, end_loc);
            temp = temp->next;
        }
        steps++;
    }
    return (free_list(end_loc), steps);
}

int find_best_resource(t_cell cell_array[], int type, int number_of_cells, int base)
{
    int steps;
    int best_index;
    int highest_steps = 100000;

    for (int i = 0; i < number_of_cells; i++)
    {
        if ((cell_array[i]).type == type && (cell_array[i]).resources != 0)
        {
            steps = find_path_between_cells(cell_array, base, i);
            fprintf(stderr, "steps %d for index %d\n", steps, i);
            if (steps < highest_steps)
            {
                highest_steps = steps;
                best_index = i;
            }
        }
    }
    fprintf(stderr, "highest steps %d, index %d\n", highest_steps, best_index);
    return (best_index);
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
    int egg_index = find_best_resource(cell_array, 1, number_of_cells, my_base_array[0]);
    int gold_index = find_best_resource(cell_array, 2, number_of_cells, my_base_array[0]);
    // int highest_index_egg;
    int harvested_egg = 0;
    // highest_index_gold = find_highest_gold(cell_array, number_of_cells);
    // highest_index_egg = find_highest_egg(cell_array, number_of_cells);
    
    while (1) {
        for (int i = 0; i < number_of_cells; i++) {
            scanf("%d%d%d", &(cell_array[i]).resources, &(cell_array[i]).my_ants, &(cell_array[i]).opp_ants);
        }
        if ((cell_array[egg_index]).resources == 0 && harvested_egg == 0)
        {
            harvested_egg = 1;
            // highest_index_egg = find_highest_egg(cell_array, number_of_cells);
        }
        if ((cell_array[gold_index]).resources == 0 && harvested_egg == 1)
            gold_index = find_best_resource(cell_array, 2, number_of_cells, my_base_array[0]);
        if (harvested_egg == 0)// WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
            printf("LINE %d %d %d\n", my_base_array[0], egg_index, 1);
        else
            printf("LINE %d %d %d\n", my_base_array[0], gold_index, 1);
    }

    return 0;
}