/* My Reg Number: 230184136 */
#include <stdio.h>

/* GLOBAL CONSTANTS */
const int min_coord_pairs=4, max_coord_pairs=20; 
const float min_value=0.000005, max_value=1000000.0;

/* GLOBAL VARIABLE */
float coordinates[max_coord_pairs][2]; // An array big enough to hold all coordinate pairs

/* 
   FUNCTION PROTOTYPES 
   [check below main() to find function definitions]
*/
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

/* FUNCTION DEFINITIONS */ 
float validate_input(char item)
{
    /* Purpose: 
        to validate all scanf inputs to ensure they are within range and of the right type.
       Inputs: 
        char item - a character that carries information about the input to be validated.
        ie: char item= 'r' for coord pairs (Rows)
            or
            char item = 'v' for x or y Value 
       Returned value:
        float - The validated input.
    */
    if (item == 'r')
    {
        int coord_pairs;
        int input_check;
        do {
            printf("Enter the number of coordinate pairs (between %d to %d): ", min_coord_pairs, max_coord_pairs);
            input_check = scanf("%d", &coord_pairs); //input_check = 1 when the input is int, otherwise 0

            if (input_check != 1 || coord_pairs < min_coord_pairs || coord_pairs > max_coord_pairs) {
                printf("Invalid input or value out of range. Please enter a valid float between %d and %d (inclusive).\n", min_coord_pairs, max_coord_pairs);
                while (getchar() != '\n'); // Clear the input buffer
                coord_pairs = -1; // Reset value for re-prompting
            }

        } while (coord_pairs < min_coord_pairs || coord_pairs > max_coord_pairs);
        return coord_pairs;
    }
    else if(item == 'v')
    {
        float point;
        int input_check;
        do {
            input_check = scanf("%f", &point); //input_check = 1 when the input matches a float, otherwise 0

            if (input_check != 1 || point < min_value || point > max_value) {
                printf("Invalid input or value out of range. Please enter a valid float between %f and %f.\n   ", min_value, max_value);
                while (getchar() != '\n'); // Clear the input buffer
                point = -1; // Reset value for re-prompting
            }

        } while (point < min_value || point > max_value);
        return point;
    }
    return 0;
}
void collect_coordinates(int rows){
    /* Purpose: 
        Collects X values and Y values and stores them in the 2D coordinates array. 
        It makes use of validate_input('v') to validate each point provided by the user.
       Inputs: 
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
       Returned value:
        void
    */
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
            coordinates[row][col] = validate_input('v'); 
        }
    }
}
void display_table(float coord_list[][2], int rows){
    /* Purpose: 
        Neatly displays X and Y values in a table form.
       Inputs: 
        float coord_list[][2] - The 2D array containing the coordinate value pairs.
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
       Returned value:
        void
    */
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
    /* Purpose: 
        Calculates the sum of all x values.
       Inputs: 
        float coord_list[][2] - The 2D array containing the coordinate value pairs.
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
       Returned value:
        float sum_of_x - The sum of all x values.
    */
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
    /* Purpose: 
        Calculates the sum of all y values.
       Inputs: 
        float coord_list[][2] - The 2D array containing the coordinate value pairs.
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
       Returned value:
        float sum_of_y - The sum of all y values.
    */
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
    /* Purpose: 
        Calculates the sum of the product of each x value and its corresponding y value.
       Inputs: 
        float coord_list[][2] - The 2D array containing the coordinate value pairs.
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
       Returned value:
        float sum_of_pdt - The sum of the product of each x value and its corresponding y value.
    */
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
    /* Purpose: 
        Calculates the sum of each x value squared.
       Inputs: 
        float coord_list[][2] - The 2D array containing the coordinate value pairs.
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
       Returned value:
        float sum_of_x_squared - The sum of each x value squared.
    */
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
    /* Purpose: 
        Calculates gradient.
       Inputs: 
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
        float sum_of_x - The sum of all x values.
        float sum_of_y - The sum of all y values.
        float sum_of_pdt - The sum of the product of each x value and its corresponding y value.
        float sum_of_x_squared - The sum of each x value squared.
       Returned value:
        void. The value calculated is printed directly.
    */
    float gradient;
    gradient = ((rows * sum_of_pdt) - (sum_of_x * sum_of_y)) / ((rows * sum_of_x_squared) - (sum_of_x * sum_of_x));
    printf("\nm = %f", gradient);
}
void calc_offset(int rows, float sum_of_x, float sum_of_y, float sum_of_pdt, float sum_of_x_squared)
{
    /* Purpose: 
        Calculates offset.
       Inputs: 
        int rows - The number of coordinate pairs. This was previously extracted using (int)validate_input('r')
        float sum_of_x - The sum of all x values.
        float sum_of_y - The sum of all y values.
        float sum_of_pdt - The sum of the product of each x value and its corresponding y value.
        float sum_of_x_squared - The sum of each x value squared.
       Returned value:
        void. The value calculated is printed directly.
    */
    float offset;
    offset = ((sum_of_x_squared * sum_of_y) - (sum_of_x * sum_of_pdt)) / ((rows * sum_of_x_squared) - (sum_of_x * sum_of_x));
    printf("\nc = %f", offset);
}
int retry_request()
{
    /* Purpose: 
        Places a retry request. Contains input validation to ensure either y/n.
       Inputs: 
        None
       Returned value:
        int- If = 1, the whole process restarts. 
             Else If = 0, Goodbye is printed.
             A default return value of -1. 
    */
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