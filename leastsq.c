/* My Reg Number: 230184136 */
#include <stdio.h>

// GLOBAL VARIABLES
int try_again = 0;
float sum_of_pdt = 0;
float sum_of_x = 0;
float sum_of_y = 0;
float sum_of_x_squared = 0;

// FUNCTIONS USED
float accept_value(char item);
void calc_sums(float coord_list[][2], int rows);
void calc_gradient(int rows);
void calc_offset(int rows);
void retry_request();

int main(void)
{
    do
    {
        printf("This program calculates gradient and offset.\n");
        int rows;
        printf("Enter the number of coordinate pairs (between 4 to 20): ");
        rows = (int)accept_value('r'); // Refer to line 63 for details of function
        float coord[rows][2];
        printf("Enter the data coordinates in the table below.\n");
        printf("\n");
        int a, b;
        for (b = 0; b < 2; b++)
        {
            if (b == 0)
            {
                printf("X values\n--------\n");
            }
            if (b == 1)
            {
                printf("Y values\n--------\n");
            }
            for (a = 0; a < rows; a++)
            {
                printf("   ");
                coord[a][b] = accept_value('p'); // Refer to line 63 for details of function
            }
        }
        printf("\n"); // Displaying the collected values
        printf("X values \t|\tY values\n--------------------------------\n");
        for (a = 0; a < rows; a++)
        {
            printf("%f\t|\t%f", coord[a][0], coord[a][1]);
            printf("\n");
        }
        calc_sums(coord, rows);
        calc_gradient(rows);
        calc_offset(rows);
        retry_request();
    } while (try_again == 1);
}

// FUNCTION DEFINITIONS

float accept_value(char item)
{
    /* item = 'r' for coord pairs, item = 'p' for x or y value */
    if (item == 'r')
    {
        float val;
        do
        {
            scanf("%f", &val);
            while(getchar()!='\n');
            if (val < 4 || val > 20)
            {
                printf("The number must be between 4 and 20 (inclusive)\n   ");
            }
        } while (val < 4 || val > 20);
        return val;
    }
    else
    {
        float val2;
        do
        {
            scanf("%f", &val2);
            while(getchar()!='\n');
            if (val2 < 0.000005 || val2 > 1000000.0)
            {
                printf("The number must be between 0.000005 and 1000000.0\n   ");
            }
        } while (val2 < 0.000005 || val2 > 1000000.0);
        return val2;
    }
}
void calc_sums(float coord_list[][2], int rows)
{
    int a;
    for (a = 0; a < rows; a++)
    {
        sum_of_x += coord_list[a][0];
        sum_of_y += coord_list[a][1];
        sum_of_pdt += (coord_list[a][0]) * (coord_list[a][1]);
        sum_of_x_squared += (coord_list[a][0]) * (coord_list[a][0]);
    }
}
void calc_gradient(int rows)
{
    float m;
    m = ((rows * sum_of_pdt) - (sum_of_x * sum_of_y)) / ((rows * sum_of_x_squared) - (sum_of_x * sum_of_x));
    printf("\nm = %f", m);
}
void calc_offset(int rows)
{
    float c;
    c = ((sum_of_x_squared * sum_of_y) - (sum_of_x * sum_of_pdt)) / ((rows * sum_of_x_squared) - (sum_of_x * sum_of_x));
    printf("\nc = %f", c);
}
void retry_request()
{
    int valid = 0;
    do
    {
        char response;
        printf("\nTry again?(y/n): ");
        scanf(" %c", &response);
        if (response == 'y')
        {
            sum_of_pdt = 0;
            sum_of_x = 0;
            sum_of_y = 0;
            sum_of_x_squared = 0;
            printf("\n");
            try_again = 1;
            valid = 1;
        }
        else if (response == 'n')
        {
            printf("\nGoodbye!\n");
            try_again = 0;
            valid = 1;
        }
        else
        {
            printf("\nEnter either y/n");
            valid = 0;
        }
    } while (valid == 0);
}