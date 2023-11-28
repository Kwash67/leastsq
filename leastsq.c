/* My Reg Number: 230184136 */
#include <stdio.h>

/* GLOBAL CONSTANTS */
const int min_coords=4, max_coords=20; 
const float min_value=0.000005, max_value=1000000.0;

/* GLOBAL VARIABLE */
float coord[max_coords][2];

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
        display_table(coord, rows);

        /* Calculating Sums */
        float sum_of_x= calc_sum_of_x(coord, rows);
        float sum_of_y= calc_sum_of_y(coord, rows);
        float sum_of_pdt= calc_sum_of_pdt(coord, rows);
        float sum_of_x_squared= calc_sum_of_x_squared(coord, rows);

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
        float val;
        do
        {
            printf("Enter the number of coordinate pairs (between 4 to 20): ");
            scanf("%f", &val);
            while(getchar()!='\n');
            if (val < min_coords || val > max_coords)
            {
                printf("The number must be between %d and %d (inclusive)\n", min_coords, max_coords);
            }
        } while (val < min_coords || val > max_coords);
        return val;
    }
    else
    {
        float val2;
        do
        {
            scanf("%f", &val2);
            while(getchar()!='\n');
            if (val2 < min_value || val2 > max_value)
            {
                printf("The number must be between %f and %f\n   ", min_value, max_value);
            }
        } while (val2 < min_value || val2 > max_value);
        return val2;
    }
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
            coord[row][col] = validate_input('p'); 
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