#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
int n;
FILE *file;

void bubble_sort(int A[], int start, int end)
{
    for (int i = end - start; i > 0; i--)
    {
        for (int j = start; j < start + i; j++)
        {
            if (A[j] > A[j + 1])
            {
                int temp = A[j + 1];
                A[j + 1] = A[j];
                A[j] = temp;
            }
        }
    }
}

int partition(int A[], int start, int end)
{
    int pivot = A[end];
    int index = start - 1;
    for (int i = start; i < end; i++)
    {
        if (A[i] <= pivot)
        {
            index++;
            int temp = A[i];
            A[i] = A[index];
            A[index] = temp;
        }
    }
    index++;
    int temp = A[end];
    A[end] = A[index];
    A[index] = temp;
    return index;
}

void quick_sort(int A[], int start, int end)
{
    if (start < end)
    {
        int q = partition(A, start, end);
        quick_sort(A, start, q - 1);
        quick_sort(A, q + 1, end);
    }
}

void insert_sort(int A[], int start, int end)
{
    for (int i = start + 1; i < end + 1; i++)
    {
        int key = A[i];
        int j = i - 1;
        while (j > start - 1 && A[j] > key)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void merge(int A[], int start, int mid, int end)
{
    int *B = (int *)malloc(sizeof(int) * (mid - start + 1));
    int *C = (int *)malloc(sizeof(int) * (end - mid));
    for (int i = 0; i < mid - start + 1; i++)
    {
        B[i] = A[start + i];
    }
    for (int i = 0; i < end - mid; i++)
    {
        C[i] = A[mid + i + 1];
    }
    int i = 0;
    int j = 0;
    int k = start;
    while (i < mid - start + 1 && j < end - mid)
    {
        if (C[j] >= B[i])
        {
            A[k] = B[i];
            i++;
            k++;
        }
        else
        {
            A[k] = C[j];
            j++;
            k++;
        }
    }
    while (j < end - mid)
    {
        A[k] = C[j];
        k++;
        j++;
    }
    while (i < mid - start + 1)
    {
        A[k] = B[i];
        k++;
        i++;
    }

    free(B);
    free(C);
}

void merge_sort(int A[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        merge_sort(A, start, mid);
        merge_sort(A, mid + 1, end);
        merge(A, start, mid, end);
    }
}

int median_partition(int A[], int start, int end, int mid)
{

    int pivot = A[mid];
    int temp = A[end];
    A[end] = A[mid];
    A[mid] = temp;

    int index = start - 1;
    for (int i = start; i < end; i++)
    {
        if (A[i] <= pivot)
        {
            index++;
            int temp = A[i];
            A[i] = A[index];
            A[index] = temp;
        }
    }
    index++;
    temp = A[end];
    A[end] = A[index];
    A[index] = temp;
    return index;
}

void intro_sort(int A[], int start, int end)
{
    if (start < end)
    {
       
        if (end - start < 16)
        {
            insert_sort(A, start, end);
            return;
        }
        else
        {
            int q2 = start + (end - start) / 2;
            int q1 = start + (q2 - start) / 2;
            int q3 = q2 + (end - q2) / 2;

            int mid = q1;
            if (A[q1] < A[q2])
            {
                if (A[q2] < A[q3])
                    mid = q2;
                else
                    mid = q3;
            }

            else if (A[q1] < A[q3])
            {
                if (A[q3] < A[q2])
                    mid = q3;
                else
                    mid = q2;
            }
            else if (A[q2] < A[q1])
            {
                if (A[q1] < A[q3])
                    mid = q1;
                else
                    mid = q3;
            }
            else if (A[q3] < A[q1])
            {
                if (A[q1] < A[q2])
                    mid = q1;
                else
                    mid = q2;
            }
            int q = median_partition(A, start, end, mid);
            intro_sort(A, start, q - 1);
            intro_sort(A, q + 1, end);
        }
    }
}

void radix_sort(int A[], int n)
{

    int *B = (int *)malloc(sizeof(int) * n);
    int exp = 1;
    int max = A[0];
    int i;
    for (i = 0; i < n; i++)
    {
        if (A[i] > max)
            max = A[i];
    }
    int digit = 10;

    while (max / exp > 0)
    {
        int C[digit];
        for (i = 0; i < digit; i++)
        {
            C[i] = 0;
        }

        for (i = 0; i < n; i++)
            C[(A[i] / exp) % digit]++;

        for (i = 1; i < digit; i++)
        {
            C[i] = C[i] + C[i - 1];
        }
        for (i = n - 1; i >= 0; i--)
        {
            B[C[(A[i] / exp) % digit] - 1] = A[i];
            C[A[i] / exp % digit]--;
        }
        for (i = 0; i < n; i++)
        {
            A[i] = B[i];
        }
        exp = exp * digit;
    }

    free(B);
}

int main(int argc, char **argv)
{
    clock_t start, end;
    if (argc != 3)
    {
        printf("input error! AGAIN INPUT");
        return 0;
    }

    char file_name[100];
    int index;
    strcpy(file_name, argv[1]);
    index = atoi(argv[2]);
    file = fopen(file_name, "r");
    fscanf(file, "%d ", &n);
    int *A; 
    //*B, *C;
  //  int b = 0;
  //  int c = 0;
    A = (int *)malloc(sizeof(int) * n);
   // B = (int *)malloc(sizeof(int) * n);
   // C = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d ", &A[i]);
       // if (A[i] >= 0)
      //      B[b++] = A[i];
      //  else
      //      C[c++] = abs(A[i]);
    }

    if (index == 1) // bubble sort
    {
        start = clock();
         bubble_sort(A, 0, n - 1);
        end = clock();
    }
    else if (index == 2)
    {
        start = clock();
        quick_sort(A, 0, n - 1);
        end = clock();
    }
    else if (index == 3)
    {
        start = clock();
        merge_sort(A, 0, n - 1);
        end = clock();
    }
    else if (index == 4)
    {
start = clock();
       // if(c>0)
      //  radix_sort(C,c);
        
       // radix_sort(B, b);
        
        
    intro_sort(A, 0, n - 1);
        end = clock();
       
   
    }
    char result_filename[100] = "result_";
    char ind[10];
    strcpy(ind, argv[2]);
    strcat(result_filename, ind);
    strcat(result_filename, "_");
    strcat(result_filename, file_name);
    FILE *result_fp = fopen(result_filename, "w");
    fprintf(result_fp, "%s\n%d\n%d\n%f\n", file_name, index, n, (double)(end - start) / CLOCKS_PER_SEC);
    if (index != 5)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(result_fp, "%d", A[i]);
            if (i + 1 < n)
                fprintf(result_fp, " ");
        }
    }
  /*  else
    {
        for (int i = c - 1; i >= 0; i--)
        {
            fprintf(result_fp, "-%d ", C[i]);
        }
        for (int i = 0; i < b; i++)
        {
            fprintf(result_fp, "%d", B[i]);
            if (i + 1 < b)
                fprintf(result_fp, " ");
        }
    }*/
    fclose(file);
    fclose(result_fp);
    free(A);
    //free(B);
    //free(C);
    return 0;
}