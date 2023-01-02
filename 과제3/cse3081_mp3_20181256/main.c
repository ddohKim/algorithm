#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
int n;
FILE *file;

#define ASCII 128
int count[128] = {
    0,
};

typedef struct _node
{
    // char sym;
    int ascii;
    int cnt;
    struct _node *l_child;
    struct _node *r_child;
} node;

typedef struct _h
{
    node *node;

} h;
h heap[129] = {NULL};

int hn = 0;

void push(node *x)
{
    int current = hn;
    heap[hn].node = x;
    hn++;
    while (current > 0)
    {

        int parent = (current - 1) / 2;
        if (heap[parent].node->cnt > heap[current].node->cnt)
        {

            node *temp = heap[parent].node;
            heap[parent].node = heap[current].node;
            heap[current].node = temp;
        }
        else
            break;
        current = parent;
    }
}

node *pop()
{

    node *data = heap[0].node;
    --hn;

    node *temp = heap[hn].node;
    heap[hn].node = heap[0].node;
    heap[0].node = temp;
    int current = 0;
    int frequency = heap[hn].node->cnt;
    heap[hn].node->cnt = 1e8;
    while (2 * current + 2 <= hn)
    {
        int left = 2 * current + 1, right = 2 * current + 2;
        int next;
        if (heap[left].node->cnt < heap[right].node->cnt)
        {
            next = left;
        }
        else
            next = right;
        if (heap[next].node->cnt < heap[current].node->cnt)
        {
            temp = heap[next].node;
            heap[next].node = heap[current].node;
            heap[current].node = temp;
            current = next;
        }
        else
            break;
    }
    heap[hn].node->cnt = frequency;
    heap[hn].node = NULL;
    return data;
}

node *newNode(int ascii, int cnt, node *l, node *r)
{
    node *new;
    new = (node *)malloc(sizeof(node));
    new->ascii = ascii;
    new->l_child = l;
    new->r_child = r;
    new->cnt = cnt;
    return new;
}

void make_table(node *n, char str[], int len, char *table[])
{
    if (n->l_child == NULL && n->r_child == NULL) 
    {
        str[len] = '\0'; 
                         
       // printf("%c: %s\n", (char)n->ascii, str);
        strcpy(table[n->ascii], str);
    }
    else 
    {
        if (n->l_child != NULL) 
        {
            str[len] = '0'; //0
            make_table(n->l_child, str, len + 1, table);
           
        }
        if (n->r_child != NULL) 
        {
            str[len] = '1'; //1
            make_table(n->r_child, str, len + 1, table);
          
        }
    }
}

int getAbit(unsigned short x, int n)
{ // getbit()
    return (x & (1 << n)) >> n;
}

unsigned char encoding_input = 0;
int eight = 7;
void packing(char *str, FILE *result_fp)
{
    int leng = strlen(str);
    for (int i = leng - 1; i >= 0; i--)
    {
        if (*str == '1')
        {
            encoding_input = encoding_input | (1 << eight);
        }
        str++;
        eight--;
        if (eight == -1)
        {
            fprintf(result_fp, "%c", encoding_input);
            for (int j = 7; j >= 0; j--)
            {
                int k = getAbit(encoding_input, j);
               // printf("%d ",k);
            }
            encoding_input = 0;
            eight = 7;
        }
    }
}

void restore_tree(node *head, char *str, int asci)
{
    node *temp = head;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '0')
        {
            if (temp->l_child == NULL)
            {
                temp->l_child = newNode(asci, 0, NULL, NULL);
                temp = temp->l_child;
            }
            else
                temp = temp->l_child;
        }
        else if (str[i] == '1')
        {
            if (temp->r_child == NULL)
            {

                temp->r_child = newNode(asci, 0, NULL, NULL);
                ;
                temp = temp->r_child;
            }
            else
                temp = temp->r_child;
        }
    }
    temp->ascii = asci;
    temp->cnt = 30;
    temp->l_child = NULL;
    temp->r_child = NULL;
}

int main(int argc, char **argv)
{
    clock_t start, end;
    if (argc != 3)
    {
        printf("input error! AGAIN INPUT\n");
        return 0;
    }

    char file_name[100];
    char check[5];
    strcpy(file_name, argv[2]);
    strcpy(check, argv[1]);
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("\n Error: file is not exist.\n");
        return 0;
    }
    if (strcmp(check, "-c") && strcmp(check, "-d"))
    {
        printf("\n Error: This option is not available\n");
        fclose(file);

        return 0;
    }
    if (!strcmp(check, "-c")) // compresssion
    {

        char c;
        int numbering=0;
        while (EOF != fscanf(file, "%c", &c))
        {
            count[(int)c]++;
            numbering++;

        }

        int check = 0;
        for (int i = 0; i < 128; i++)
        {
            if (count[i] > 0)
            {
                node *input_node = newNode(i, count[i], NULL, NULL);
                check++;
                push(input_node);
            }
        }

        for (int i = 0; i < check - 1; i++)
        {
            node *temp = pop();
            node *temp1 = pop();
            node *input_node = newNode(200, temp->cnt + temp1->cnt, temp, temp1);
            push(input_node);
        }
        node *head = pop();
     //   printf("head: %d ",head->ascii);
        char *code[129];
        char str[1000000];
        for (int i = 0; i < 129; i++)
        {
            code[i] = (char *)malloc(sizeof(char)*80);
        }
        make_table(head, str, 0, code);
        if(head->ascii!=200){
            char headnode[2];
            headnode[0]='0';
            headnode[1]='\0';
            strcpy(code[head->ascii],headnode);
        }


        FILE *file2 = fopen(file_name, "r");
        strcat(file_name, ".zz");
        FILE *result_fp = fopen(file_name, "w");
        fprintf(result_fp,"%d",numbering);
        fprintf(result_fp, " %c", check); //사용한 문자의 총 개수
       
        for (int i = 0; i < 128; i++)
        {
            if (count[i] != 0)
            {

                fprintf(result_fp, "%c", i);                     // ascii
                fprintf(result_fp, "%c", (char)strlen(code[i])); // ascii 2진수 표시 개수
                fprintf(result_fp, "%s", code[i]);               // 2진수
                //printf("%c %s",i ,code[i]);
            }
        }

        while (EOF != fscanf(file2, "%c", &c))
        {
            char *encoding_ptr = code[(int)c];
            packing(encoding_ptr, result_fp);
        }
        int j = eight;
        //printf("eight : %d",j);
        char margin[j + 2];
        for (int i = 0; i <=j; i++)
        {
            margin[i] = '0';
           // printf("s");
            
        }
        j++;
 
        packing(margin, result_fp);


        fclose(file);
        fclose(file2);
        fclose(result_fp);
        for (int i = 0; i < 129; i++)
        {
            free(code[i]);
        }
    }

    else if (!strcmp(check, "-d")) // decompression
    {
        char *code[129] = {
            NULL,
        };

        for (int i = 0; i < 129; i++)
        {
            code[i] = (char *)malloc(sizeof(char)*1000);
        }
        
        int numbering=0;
        fscanf(file,"%d",&numbering);
       // printf("%d",numbering);
        char c;
        fscanf(file, "%c", &c);
        fscanf(file, "%c", &c);
        int num = c;
        node *head = newNode(200, 0, NULL, NULL);
        
        for (int i = 0; i < num; i++)
        {
            char str[1000000];
            fscanf(file, "%c", &c);
            char asci = c;
          
            fscanf(file, "%c", &c);
            int temp = c;
          
            for (int j = 0; j < temp; j++)
            {

                fscanf(file, "%c", &c);
                str[j] = c;
            
                if (j + 1 == temp)
                {
                    str[j + 1] = '\0';
                }
           
            }
            strcpy(code[asci], str);
           
        }
       for (int i = 0; i < 128; i++)
        {
            if (strlen(code[i]) != 0)
            {
                restore_tree(head, code[i], i);
            }
        }
        node *temp = head;
        strcat(file_name, ".yy");
        FILE *result_fp = fopen(file_name, "w");
        // printf("num: %d",num);
        int index = 0;
        while (EOF != fscanf(file, "%c", &c))
        {
            for (int i = 7; i >= index; i--)
            {
               
                int k = getAbit(c, i);
               //printf("%d",k);

              if (k == 0)
                {
                   
                    if (temp->l_child == NULL)
                    {
                        if(numbering==0)
                        break;
                        fprintf(result_fp, "%c", (char)temp->ascii);
                        numbering--;
                        //printf("%c", (char)temp->ascii);
                        temp = head;
                    }
                     temp = temp->l_child;
                }
                if (k == 1)
                {
                    if (temp->r_child == NULL)
                    { if(numbering==0)
                        break;
                        fprintf(result_fp, "%c", (char)temp->ascii);
                        numbering--;
                        //printf("%c", (char)temp->ascii);
                        temp = head;
                       
                    }
                    temp = temp->r_child;
                }
            }
            if(numbering==0)
                        break;
        }

        fclose(file);
        fclose(result_fp);
    }
    return 0;
}