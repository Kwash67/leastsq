/* My Reg Number: 230184136 */
#include <stdio.h>

/* GLOBAL CONSTANTS */
const int min_coord_pairs=4, max_coord_pairs=20; 
const float min_value=0.000005, max_value=1000000.0;

/* GLOBAL VARIABLE */
float coordinates[max_coord_pairs][2];

/* FUNCTION PROTOTYPES */
float validate_input(char item);
void collect_coordinates(int rows);
void display_table(float coord_list[][2], int rows);
float calc_sum_of_x(float coord_list[][2], int rows);
float calc_sum_of_y(float coord_list[][2], int rows);
float calc_sum_of_pdt(float coord_list[][2], int rows);
float calc_sum_of_x_squared(float coord_list[][2], int rows);
void calc_gradient(int rows, float sum_of_x, float sum_of_y, float sum_of_pdt, float sum_of_x_squared);
void calc_offset(int rows, float sum_of_x, float sum_of_y, float sum_of_pdt, float sum_of_x_squared);
int retry_request();

int main(void)
{
    int try_again = 0;
    do
    {
        printf("\nThis program calculates gradient and offset.\n");

        /* Collecting the number of data pairs */
        int rows = (int)validate_input('r'); 

        /* Collecting X and Y coordinates */
        collect_coordinates(rows);
        
        /* Displaying collected values */
        display_table(coordinates, rows);

        /* Calculating Sums */
        float sum_of_x= calc_sum_of_x(coordinates, rows);
        float sum_of_y= calc_sum_of_y(coordinates, rows);
        float sum_of_pdt= calc_sum_of_pdt(coordinates, rows);
        float sum_of_x_squared= calc_sum_of_x_squared(coordinates, rows);

        /* Calculating and displaying gradient and offset */
        calc_gradient(rows, sum_of_x, sum_of_y, sum_of_pdt, sum_of_x_squared);
        calc_offset(rows, sum_of_x, sum_of_y, sum_of_pdt, sum_of_x_squared);

        /* Request to try again */
        try_again = retry_request();

    } while (try_again == 1);
    return(0);
}

// FUNCTION DEFINITIONS
float validate_input(char item)
{
    /* item = 'r' for coord pairs, item = 'p' for x or y value */
    if (item == 'r')
    {
        int coordPairs;
        int input_check;
        do {
            printf("Enter the number of coordinate pairs (between %d to %d): ", min_coord_pairs, max_coord_pairs);
            input_check = scanf("%d", &coordPairs); //input_check = 1 when the input is int, otherwise 0

            if (input_check != 1 || coordPairs < min_coord_pairs || coordPairs > max_coord_pairs) {
                printf("Invalid input or value out of range. Please enter a valid float between %d and %d (inclusive).\n", min_coord_pairs, max_coord_pairs);
                // Clear the input buffer
                while (getchar() != '\n');
                coordPairs = -1; // Reset value for re-prompting
            }

        } while (coordPairs < min_coord_pairs || coordPairs > max_coord_pairs);
        return coordPairs;
    }
    else if(item == 'p')
    {
        float point;
        int input_check;
        do {
            input_check = scanf("%f", &point); //input_check = 1 when the input matches a float, otherwise 0

            if (input_check != 1 || point < min_value || point > max_value) {
                printf("Invalid input or value out of range. Please enter a valid float between %f and %f.\n   ", min_value, max_value);
                // Clear the input buffer
                while (getchar() != '\n');
                point = -1; // Reset value for re-prompting
            }

        } while (point < min_value || point > max_value);
        return point;
    }
    return 0;
}
void collect_coordinates(int rows){
    printf("\nEnter the data coordinates in the table below.\n");
    printf("\n");
    int row, col;
    for (col = 0; col < 2; col++)
    {
        if (col == 0)
            printf("X values\n--------\n");
        else if (col == 1)
            printf("Y values\n--------\n");
        for (row = 0; row < rows; row++)
        {
            printf("   ");
            coordinates[row][col] = validate_input('p'); 
        }
    }
}
void display_table(float coord_list[][2], int rows){
    int index;
    printf("\n");
        printf("X values \t|\tY values\n--------------------------------\n");
        for (index = 0; index < rows; index++)
        {
            printf("%f\t|\t%f", coord_list[index][0], coord_list[index][1]);
            printf("\n");
        }
}
float calc_sum_of_x(float coord_list[][2], int rows)
{
    int index;
    float sum_of_x=0;
    for (index = 0; index < rows; index++)
    {
        sum_of_x += coord_list[index][0];
    }
    return sum_of_x;
}
float calc_sum_of_y(float coord_list[][2], int rows)
{
    int index;
    float sum_of_y=0;
    for (index = 0; index < rows; index++)
    {
        sum_of_y += coord_list[index][1];
    }
    return sum_of_y;
}
float calc_sum_of_pdt(float coord_list[][2], int rows)
{
    int index;
    float sum_of_pdt =0;
    for (index = 0; index < rows; index++)
    {
        sum_of_pdt += (coord_list[index][0]) * (coord_list[index][1]);
    }
    return sum_of_pdt;
}
float calc_sum_of_x_squared(float coord_list[][2], int rows)
{
    int index;
    float sum_of_x_squared=0;
    for (index = 0; index < rows; index++)
    {
        sum_of_x_squared += (coord_list[index][0]) * (coord_list[index][0]);
    }
    return sum_of_x_squared;
}
void calc_gradient(int rows, float sum_of_x, float sum_of_y, float sum_of_pdt, float sum_of_x_squared)
{
    float gradient;
    gradient = ((rows * sum_of_pdt) - (sum_of_x * sum_of_y)) / ((rows * sum_of_x_squared) - (sum_of_x * sum_of_x));
    printf("\nm = %f", gradient);
}
void calc_offset(int rows, float sum_of_x, float sum_of_y, float sum_of_pdt, float sum_of_x_squared)
{
    float offset;
    offset = ((sum_of_x_squared * sum_of_y) - (sum_of_x * sum_of_pdt)) / ((rows * sum_of_x_squared) - (sum_of_x * sum_of_x));
    printf("\nc = %f", offset);
}
int retry_request()
{
    int valid = 0;
    do
    {
        char response;
        printf("\nTry again?(y/n): ");
        scanf(" %c", &response);
        if (response == 'y')
        {
            printf("\n");
            valid = 1;
            return 1;
        }
        else if (response == 'n')
        {
            printf("\nGoodbye!\n");
            valid = 1;
            return 0;
        }
        else
        {
            printf("\nEnter either y/n");
            valid = 0;
        }
    } while (valid == 0);
    return -1;
}