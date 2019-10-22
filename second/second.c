#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {

    char name[15] ;
    int * value ;
    struct Node ** inputs  ;
    struct Node ** selectors ;
    struct Node * next ;
    int type ;
    int gate ; // N/A - 0 NOT - 1
    int inps ;
    int ind ;
    int sel ;

};


int getPowerTwo(int) ;
int getLogBaseTwo(int) ;
int * createGreyCode(int, int) ;
int * createStatic(int, int) ;
void insertNode(struct Node **, char *, int, int, int) ;
struct Node * findNode(struct Node *, char *) ;
void processNode(struct Node *, int) ;
int * not(struct Node *, int) ;
int * and(struct Node *, struct Node *, int) ;
int * or(struct Node *, struct Node *, int) ;
int * xor(struct Node *, struct Node *, int) ;


int getPowerTwo(int x) {

    int output = 1 ;
    int a = x ;

    while (a != 0) {

        output = output * 2 ;
        a-- ;

    }

    return output ;

}

int getLogBaseTwo(int x) {

    int i = x ;
    int output = 0 ;

    while (i >>= 1) {

    output++ ;

    }

    return output ;

}

int * createGreyCode(int n, int s) { // index in input variables, s bits of grey code

    int j = getPowerTwo(s) ;

    int * output = (int * )malloc((j * sizeof(int))) ;

    if (n == (s - 1)) {

        output[0] = 0 ;
        output[1] = 1 ;

        if (s > 1) {

            output[2] = 1 ;
            output[3] = 0 ;

        }

        if (s > 2) {

            int i ;

            for (i = 4 ; i < j ; i++) {

                output[i] = output[i % 4] ;

            }

        }

    } else if (n == 0) {

        int i ;
        for (i = 0 ; i < j ; i++) {

            if (i < (j / 2)) {

                output[i] = 0 ;

            } else {

                output[i] = 1 ;

            }

        }

    } else {

    int i = getPowerTwo(s - n) ;
    int k ;

    for (k = 0 ; k < i ; k++) {

        if (k < (i / 2)) {

            output[k] = 0 ;

        } else {

            output[k] = 1 ;

        }

    }

    int l = i - 1 ;


    for (k = i ; k < j ; k++) {

        output[k] = output[l] ;

        if (l == 0) {

            l = k ;

        } else {

            l-- ;

        }

    }

    }

    return output ;

}

int * createStatic(int n, int nob) {

    int * output = (int *)malloc(nob * sizeof(int)) ;

    int i ;
    for (i = 0 ; i < nob ; i++) {

        output[i] = n ;

    }

    return output ;

}

void insertNode(struct Node ** a, char * name, int nob, int o, int g) {

    struct Node * ptr = *a ;

    struct Node * n = (struct Node *)malloc(sizeof(struct Node)) ;
    strcpy(n->name, name) ;
    n->value = NULL ;
    n->next = NULL ;
    n->type = o ;
    n->gate = g ;

    if (ptr->name == '\0' || *a == NULL) {

        *a = n ;
        return ;

    }


    while (ptr->next != NULL) {

        ptr = ptr->next ;

    }

    ptr->next = n ;

    return ;

}

struct Node * findNode(struct Node * n, char * in) {

    if (n == NULL) {

        return NULL ;

    }

    struct Node * output = n ;

    while (output != NULL) {

        if (strcmp(output->name, in) == 0) {

            return output ;

        }

        output = output->next ;

    }

    return NULL ;

}

void processNode(struct Node * n, int nob) {

    struct Node * ptr = n ;

    if (ptr->value == NULL) {

    if (ptr->gate == 1) { // NOT

        if (ptr->inputs[0]->value == NULL) {

            processNode(ptr->inputs[0], nob) ;

        }

        ptr->value = not(ptr->inputs[0], nob) ;

    } else if (ptr->gate == 2) { // AND

        if (ptr->inputs[0]->value == NULL) {

            processNode(ptr->inputs[0], nob) ;

        }

        if (ptr->inputs[1]->value == NULL) {

            processNode(ptr->inputs[1], nob) ;

        }

        ptr->value = and(ptr->inputs[0], ptr->inputs[1], nob) ;

    } else if (ptr->gate == 3) { // OR

        if (ptr->inputs[0]->value == NULL) {

            processNode(ptr->inputs[0], nob) ;

        }

        if (ptr->inputs[1]->value == NULL) {

            processNode(ptr->inputs[1], nob) ;

        }

        ptr->value = or(ptr->inputs[0], ptr->inputs[1], nob) ;

    } else if (ptr->gate == 4) { // XOR

        if (ptr->inputs[0]->value == NULL) {

            processNode(ptr->inputs[0], nob) ;

        }

        if (ptr->inputs[1]->value == NULL) {

            processNode(ptr->inputs[1], nob) ;

        }

        ptr->value = xor(ptr->inputs[0], ptr->inputs[1], nob) ;

    } else if (ptr->gate == 5) { // NAND

        if (ptr->inputs[0]->value == NULL) {

            processNode(ptr->inputs[0], nob) ;

        }

        if (ptr->inputs[1]->value == NULL) {

            processNode(ptr->inputs[1], nob) ;

        }

        ptr->value = and(ptr->inputs[0], ptr->inputs[1], nob) ;
        ptr->value = not(ptr, nob) ;

    } else if (ptr->gate == 6) { // NOR

        if (ptr->inputs[0]->value == NULL) {

            processNode(ptr->inputs[0], nob) ;

        }

        if (ptr->inputs[1]->value == NULL) {

            processNode(ptr->inputs[1], nob) ;

        }

        ptr->value = or(ptr->inputs[0], ptr->inputs[1], nob) ;
        ptr->value = not(ptr, nob) ;

    } else if (ptr->gate == 7) { // DECODER

        ptr->value = (int *)malloc(nob * sizeof(int)) ;

        int i ;
        for (i = 0 ; i < ptr->inps ; i++) {

            if (ptr->inputs[i]->value == NULL) {

                processNode(ptr->inputs[i], nob) ;

            }

        }

        int * inbits = (int *)malloc(ptr->inps * sizeof(int)) ;

        for (i = 0 ; i < nob ; i++) {

            int j = 0 ;

            for (j = 0 ; j < ptr->inps ; j++) {

                inbits[j] = ptr->inputs[j]->value[i] ;

            }

            int b = 0 ;

            for (j = 0 ; j < ptr->inps ; j++) {

                b = b * 2 + inbits[j] ;
            }


            int g = ptr->ind ^ (ptr->ind >> 1) ;

            if (g == b) {

                ptr->value[i] = 1 ;

            } else {

                ptr->value[i] = 0 ;

            }

        }

    } else if (ptr->gate == 8) { // MULTIPLEXER

        ptr->value = (int *)malloc(nob * sizeof(int)) ;

        int i ;
        for (i = 0 ; i < ptr->inps ; i++) {

            if (ptr->inputs[i]->value == NULL) {

                processNode(ptr->inputs[i], nob) ;

            }

        }

        for (i = 0 ; i < ptr->sel ; i++) {

            if (ptr->selectors[i]->value == NULL) {

                processNode(ptr->selectors[i], nob) ;

            }

        }

        int * inbits = (int *)malloc(ptr->sel * sizeof(int)) ;

        for (i = 0 ; i < nob ; i++) {

            int j ;
            int b = 0 ;

            for (j = 0 ; j < ptr->sel ; j++) {

                inbits[j] = ptr->selectors[j]->value[i] ;

                b = b * 2 + inbits[j] ;

            }

            int g = 0 ;

            for (j = 0 ; j < ptr->inps ; j++) {

                g = j ^ (j >> 1) ;

                if (g == b) {

                    break ;

                }

            }

            ptr->value[i] = ptr->inputs[j]->value[i] ;

        }

    }

    }



    return ;

}

int * not(struct Node * A, int nob) { // nob = number of bytes

    int * output = (int *)malloc(nob * sizeof(int)) ;

    int i ;
    for (i = 0 ; i < nob ; i++) {

        if (A->value[i] == 1) {

            output[i] = 0 ;

        } else {

            output[i] = 1 ;

        }

    }

    return output ;
}

int * and(struct Node * A, struct Node * B, int nob) {

    int * output = (int *)malloc(nob * sizeof(int)) ;

    int i ;
    for (i = 0 ; i < nob ; i++) {

            if (A->value[i] == 1 && B->value[i] == 1) {

                output[i] = 1 ;

            } else {

                output[i] = 0 ;

            }

    }

    return output ;

}

int * or(struct Node * A, struct Node * B, int nob) {

    int * output = (int *)malloc(nob * sizeof(int)) ;

    int i ;
    for (i = 0 ; i < nob ; i++) {

            if (A->value[i] == 1 || B->value[i] == 1) {

                output[i] = 1 ;

            } else {

                output[i] = 0 ;

            }

    }

    return output ;


}

int * xor(struct Node * A, struct Node * B, int nob) {

    int * output = (int *)malloc(nob * sizeof(int)) ;

    int i ;
    for (i = 0 ; i < nob ; i++) {

        if (A->value[i] == 1 && B->value[i] == 1) {

            output[i] = 0 ;

        } else if (A->value[i] == 1 || B->value[i] == 1) {

            output[i] = 1 ;

        } else {

            output[i] = 0 ;

        }


    }

    return output ;

}


int main(int argc, char ** argv)
{

    FILE *file ;

    if (fopen(argv[1], "r") == NULL) {

        printf("error") ;
        return 0 ;

    }

    file = fopen(argv[1], "r") ;

    char * read = (char *)malloc(15 * sizeof(char)) ;
    struct Node * vars = (struct Node *)malloc(sizeof(struct Node))  ;
    int numberOfInputs = 0 ;
    int numberOfBits = 0 ;
    int numberOfOutputs = 0 ;

    while (fscanf(file, "%s ", read) != EOF) {

            if (strcmp(read, "INPUTVAR") == 0) {

            fscanf(file, "%s ", read) ;

            numberOfInputs = atoi(read) ;
            numberOfBits = getPowerTwo(numberOfInputs) ;
            struct Node * ptr = vars ;

            int j ;
            for (j = 0 ; j < numberOfInputs ; j++) {
                ptr->value = createGreyCode(j, numberOfInputs) ;
                ptr->type = 0 ;
                ptr->gate = 0 ;
                ptr->inputs = NULL ;
                fscanf(file, "%s ", ptr->name) ;

                if (j != (numberOfInputs - 1)) {

                    ptr->next = (struct Node *)malloc(numberOfInputs * sizeof(struct Node)) ;

                }

                ptr = ptr->next ;

            }

        } else if (strcmp(read, "OUTPUTVAR") == 0) {

                fscanf(file, "%s ", read) ;

                numberOfOutputs = atoi(read) ;

                int j ;
                for (j = 0 ; j < numberOfOutputs ; j++) {

                    fscanf(file, "%s ", read) ;
                    insertNode(&vars, read, numberOfBits, 1, 0) ;

                }


        } else if (strcmp(read, "NOT") == 0 ) {

                fscanf(file, "%s ", read) ;

                struct Node * in = findNode(vars, read) ;

                if (read[0] >= '0' && read[0] <= '9') {

                    in = (struct Node *)malloc(sizeof(struct Node)) ;
                    in->value = createStatic(atoi(read), numberOfBits) ;

                } else if (in == NULL) {

                    insertNode(&vars, read, numberOfBits, 2, 0) ;
                    in = findNode(vars, read) ;

                }

                fscanf(file, "%s ", read) ;

                struct Node * out = findNode(vars, read) ;

                if (out == NULL) {

                    insertNode(&vars, read, numberOfBits, 2, 1) ;
                    out = findNode(vars, read) ;

                }

                out->gate = 1 ;

                out->inputs = (struct Node **)malloc(sizeof(struct Node *)) ;

                out->inputs[0] = in ;

                out->value = NULL ;

        } else if (strcmp(read, "AND") == 0 ) {

            fscanf(file, "%s ", read) ;

            struct Node * ptr1 = findNode(vars, read) ;

                if (read[0] >= '0' && read[0] <= '9') {

                    ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                    ptr1->value = createStatic(atoi(read), numberOfBits) ;

                } else if (ptr1 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr1 = findNode(vars, read) ;

            }

            fscanf(file, "%s ", read) ;

            struct Node * ptr2 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr2->value = createStatic(atoi(read), numberOfBits) ;

            } if (ptr2 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr2 = findNode(vars, read) ;


            }

            fscanf(file, "%s ", read) ;

            struct Node * out = findNode(vars, read) ;

            if (out == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 2) ;
                out = findNode(vars, read) ;

            }

            out->gate = 2 ;

            out->inputs = (struct Node **)malloc(2 * sizeof(struct Node *)) ;

            out->inputs[0] = ptr1 ;
            out->inputs[1] = ptr2 ;

            out->value = NULL ;

        } else if (strcmp(read, "OR") == 0) {

            fscanf(file, "%s ", read) ;

            struct Node * ptr1 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr1->value = createStatic(atoi(read), numberOfBits) ;

            } if (ptr1 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr1 = findNode(vars, read) ;

            }

            fscanf(file, "%s ", read) ;

            struct Node * ptr2 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr2->value = createStatic(atoi(read), numberOfBits) ;

            } else if (ptr2 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr2 = findNode(vars, read) ;

            }

            fscanf(file, "%s ", read) ;

            struct Node * out = findNode(vars, read) ;

            if (out == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 3) ;
                out = findNode(vars, read) ;

            }

            out->gate = 3 ;

            out->inputs = (struct Node **)malloc(2 * sizeof(struct Node *)) ;

            out->inputs[0] = ptr1 ;
            out->inputs[1] = ptr2 ;

            out->value = NULL ;

        } else if (strcmp(read, "NAND") == 0) {

            fscanf(file, "%s ", read) ;

            struct Node * ptr1 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr1->value = createStatic(atoi(read), numberOfBits) ;

            } else if (ptr1 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr1 = findNode(vars, read) ;

            }

            fscanf(file, "%s ", read) ;

            struct Node * ptr2 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr2->value = createStatic(atoi(read), numberOfBits) ;

            } else if (ptr2 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr2 = findNode(vars, read) ;

            }


            fscanf(file, "%s ", read) ;

            struct Node * out = findNode(vars, read) ;

            if (out == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 5) ;
                out = findNode(vars, read) ;

            }

            out->gate = 5 ;

            out->inputs = (struct Node **)malloc(2 * sizeof(struct Node *)) ;

            out->inputs[0] = ptr1 ;
            out->inputs[1] = ptr2 ;

            out->value = NULL ;

        } else if (strcmp(read, "NOR") == 0) {

            fscanf(file, "%s ", read) ;

            struct Node * ptr1 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr1->value = createStatic(atoi(read), numberOfBits) ;

            } else if (ptr1 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr1 = findNode(vars, read) ;

            }


            fscanf(file, "%s ", read) ;

            struct Node * ptr2 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr2->value = createStatic(atoi(read), numberOfBits) ;

            } else if (ptr2 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr2 = findNode(vars, read) ;

            }


            fscanf(file, "%s ", read) ;

            struct Node * out = findNode(vars, read) ;

            if (out == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 6) ;
                out = findNode(vars, read) ;

            }

            out->gate = 6 ;

            out->inputs = (struct Node **)malloc(2 * sizeof(struct Node *)) ;

            out->inputs[0] = ptr1 ;
            out->inputs[1] = ptr2 ;

            out->value = NULL ;

        } else if (strcmp(read, "XOR") == 0) {

            fscanf(file, "%s ", read) ;

            struct Node * ptr1 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr1->value = createStatic(atoi(read), numberOfBits) ;

            } else if (ptr1 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr1 = findNode(vars, read) ;

            }


            fscanf(file, "%s ", read) ;

            struct Node * ptr2 = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                ptr2->value = createStatic(atoi(read), numberOfBits) ;

            } else if (ptr2 == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                ptr2 = findNode(vars, read) ;

            }

            fscanf(file, "%s ", read) ;

            struct Node * out = findNode(vars, read) ;

            if (out == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 4) ;
                out = findNode(vars, read) ;

            }

            out->gate = 4 ;

            out->inputs = (struct Node **)malloc(2 * sizeof(struct Node *)) ;

            out->inputs[0] = ptr1 ;
            out->inputs[1] = ptr2 ;

            out->value = NULL ;

        } else if (strcmp(read, "DECODER") == 0) {

            fscanf(file, "%s ", read) ;

            int noi = atoi(read) ;

            int noo = getPowerTwo(noi) ;

            struct Node ** dIn = (struct Node **)malloc(noi * sizeof(struct Node *)) ;

            struct Node ** dOut = (struct Node **)malloc(noo * sizeof(struct Node *)) ;

            int i ;

            for (i = 0 ; i < noi ; i++) {

                fscanf(file, "%s ", read) ;

                dIn[i] = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                dIn[i] = (struct Node *)malloc(sizeof(struct Node)) ;
                dIn[i]->value = createStatic(atoi(read), numberOfBits) ;

            } else if (dIn[i] == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                dIn[i] = findNode(vars, read) ;

            }

            }

            for (i = 0 ; i < noo ; i++) {

                fscanf(file, "%s ", read) ;

                dOut[i] = findNode(vars, read) ;

                if (dOut[i] == NULL) {

                    insertNode(&vars, read, numberOfBits, 2, 7) ;
                    dOut[i] = findNode(vars, read) ;


                }

                dOut[i]->gate = 7 ;
                dOut[i]->inputs = dIn ;
                dOut[i]->inps = noi ;
                dOut[i]->ind = i ;



            }

        } else if (strcmp(read, "MULTIPLEXER") == 0) {

            fscanf(file, "%s ", read) ;

            int in = atoi(read) ;

            int sel = getLogBaseTwo(in) ;

            int i ;

            struct Node ** mIn = (struct Node **)malloc(in * sizeof(struct Node *)) ;
            struct Node ** selectors = (struct Node **)malloc(sel * sizeof(struct Node *)) ;

            for (i = 0 ; i < in ; i++) {

                fscanf(file, "%s ", read) ;

                mIn[i] = findNode(vars, read) ;

            if (read[0] >= '0' && read[0] <= '9') {

                mIn[i] = (struct Node *)malloc(sizeof(struct Node)) ;
                mIn[i]->value = createStatic(atoi(read), numberOfBits) ;

            } else if (mIn[i] == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 0) ;
                mIn[i] = findNode(vars, read) ;

            }

            }

            for (i = 0 ; i < sel ; i++) {

                fscanf(file, "%s ", read) ;

                selectors[i] = findNode(vars, read) ;

                if (read[0] >= '0' && read[0] <= '9') {

                    selectors[i] = (struct Node *)malloc(sizeof(struct Node)) ;
                    selectors[i]->value = createStatic(atoi(read), numberOfBits) ;

                } else if (selectors[i] == NULL) {

                    insertNode(&vars, read, numberOfBits, 2, 0) ;
                    selectors[i] = findNode(vars, read) ;

                }

            }


            fscanf(file, "%s ", read) ;

            struct Node * output = findNode(vars, read) ;

            if (output == NULL) {

                insertNode(&vars, read, numberOfBits, 2, 8) ;
                output = findNode(vars, read) ;


            }

            output->gate = 8 ;
            output->inputs = mIn ;
            output->selectors = selectors ;
            output->inps = in ;
            output->sel = sel ;;

        }


        }

    struct Node * ptr = vars ;

    while (ptr != NULL) {

        if (ptr->type != 0) {

            processNode(ptr, numberOfBits) ;

        }

        ptr = ptr->next ;

    }

    ptr = vars ;

    int a ;
    for (a = 0 ; a < numberOfBits ; a++) {

        while (ptr != NULL) {

        if (ptr->type == 0 || ptr->type == 1) {

            printf("%d ", ptr->value[a]) ;

        }

        ptr = ptr->next ;

        }

        printf("\n") ;

        ptr = vars ;

    }

    return 0;
}

