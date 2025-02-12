#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

// Matriz que representa un Sudoku resuelto
int sudoku[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}};

// Estructura para almacenar los parámetros que se pasarán a los hilos
typedef struct
{
    int row;
    int column;
} parameters;

// Función para validar que una fila del Sudoku contiene los números del 1 al 9 sin repetirse
void *validate_row(void *param)
{
    parameters *params = (parameters *)param;
    int row = params->row;
    int validation[9] = {0}; // Arreglo para verificar la aparición de los números
    for (int i = 0; i < 9; i++)
    {
        int num = sudoku[row][i];
        if (num < 1 || num > 9 || validation[num - 1] == 1)
        {
            return (void *)0; // Retorna 0 si hay un número fuera de rango o repetido
        }
        validation[num - 1] = 1; // Marca el número como encontrado
    }
    return (void *)1; // Retorna 1 si la fila es válida
}

// Función para validar que una columna del Sudoku contiene los números del 1 al 9 sin repetirse
void *validate_column(void *param)
{
    parameters *params = (parameters *)param;
    int col = params->column;
    int validation[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        int num = sudoku[i][col];
        if (num < 1 || num > 9 || validation[num - 1] == 1)
        {
            return (void *)0;
        }
        validation[num - 1] = 1;
    }
    return (void *)1;
}

// Función para validar que una subcuadrícula 3x3 contiene los números del 1 al 9 sin repetirse
void *validate_subgrid(void *param)
{
    parameters *params = (parameters *)param;
    int row = params->row;
    int col = params->column;
    int validation[9] = {0};
    // Itera sobre las cuadrículas 3x3 usando 2 ciclos
    for (int i = row; i < row + 3; i++)
    {
        for (int j = col; j < col + 3; j++)
        {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || validation[num - 1] == 1)
            {
                return (void *)0;
            }
            validation[num - 1] = 1;
        }
    }
    return (void *)1; // Retorna 1 si la subcuadrícula es válida
}

int main()
{
    // Cada hilo que se cree tiene un identificador pthread_t
    pthread_t threads[27];
    // En este arreglo se almacenan los parametros de cada
    parameters *params[27];
    int thread_index = 0;

    // 9 hilos para verificar las filas
    for (int i = 0; i < 9; i++)
    {
        // Asignación de memoria dinámica(en cualquier punto de la memoria)  con
        // espacio para cada hilo con la estructura de parameters.
        params[thread_index] = (parameters *)malloc(sizeof(parameters));
        // Establece la fila a verificar por el hilo con el índice actual
        params[thread_index]->row = i;
        // Ya que es un hilo de verificación de filas no verifica columnas(la establece en 0)
        params[thread_index]->column = 0;
        // Crea un hilo con el indice actual, se le pasa la función de validación y la estructura
        // de sus parametros
        pthread_create(&threads[thread_index], NULL, validate_row, params[thread_index]);
        thread_index++;
    }

    // 9 hilos para verificar las columnas
    for (int i = 0; i < 9; i++)
    {
        params[thread_index] = (parameters *)malloc(sizeof(parameters));
        // Selecciona las columnas a verificar, lo demás es similar a la anterior parte
        params[thread_index]->row = 0;
        params[thread_index]->column = i;
        pthread_create(&threads[thread_index], NULL, validate_column, params[thread_index]);
        thread_index++;
    }

    // 9 hilos para verificar las subcuadrículas
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            params[thread_index] = (parameters *)malloc(sizeof(parameters));
            // Al ser un hilo validador de subcuadriculas se le pasa la fila y
            // columna para que a través de validate_subgrid pueda determinar si
            // una subcuadricula 3x3 en cualquier lugar es valida
            params[thread_index]->row = i;
            params[thread_index]->column = j;
            pthread_create(&threads[thread_index], NULL, validate_subgrid, params[thread_index]);
            thread_index++;
        }
    }

    // Expera a que todos los hilos terminen
    int solucionValida = 1;
    for (int i = 0; i < 11; i++)
    {
        void *result;
        pthread_join(threads[i], &result); // Ejecuta el hilo y espera a que termine
        if ((intptr_t)result == 0)
        {
            solucionValida = 0;
        }
        free(params[i]); // Libera la memoria asignada a los parámetros
    }
    if (solucionValida)
    {
        printf("La solución dada es válida\n");
    }
    else
    {
        printf("La solución dada es inválida.\n");
    }
    // imprimir solucion procesada
    // Imprimir solución procesada con subdivisiones
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            printf("---------------------\n");
        }
        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0 && j != 0)
            {
                printf(" | ");
            }
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }

    return 0;
}
