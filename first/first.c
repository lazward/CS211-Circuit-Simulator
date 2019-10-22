#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {

    char name[15] ;
    int * value ;
    struct Node * next ;

};

int getPowerTwo(int) ;
int getLogBaseTwo(int) ;
int * createGreyCode(int, int) ;
int * createStatic(int, int) ;
void insertNode(struct Node **, char *, int) ;
struct Node * findNode(struct Node *, char *) ;
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

void insertNode(struct Node ** a, char * name, int nob) {

    struct Node * ptr = *a ;

    struct Node * n = (struct Node *)malloc(sizeof(struct Node)) ;
    strcpy(n->name, name) ;
    n->value = (int *)malloc(nob * sizeof(int)) ;
    n->next = NULL ;

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

    if (output == NULL){

        return NULL ;

    }

    return output ;

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
    struct Node * inputs = (struct Node *)malloc(sizeof(struct Node)) ;
    struct Node * outputs = NULL ;
    struct Node * tempvars = NULL ;
    int numberOfInputs = 0 ;
    int numberOfBits = 0 ;

    while (fscanf(file, "%s ", read) != EOF) {

        if (strcmp(read, "INPUTVAR") == 0) {

            fscanf(file, "%s ", read) ;

            numberOfInputs = atoi(read) ;
            numberOfBits = getPowerTwo(numberOfInputs) ;
            struct Node * ptr = inputs ;

            int j ;
            for (j = 0 ; j < numberOfInputs ; j++) {
                ptr->value = createGreyCode(j, numberOfInputs) ;
                fscanf(file, "%s ", ptr->name) ;

                if (j != (numberOfInputs - 1)) {

                    ptr->next = (struct Node *)malloc(numberOfInputs * sizeof(struct Node)) ;

                }

                ptr = ptr->next ;

            }

        } else if (strcmp(read, "OUTPUTVAR") == 0) {

                fscanf(file, "%s ", read) ;

                int i = atoi(read) ;

                struct Node * ptr = outputs ; // needed only for testing

                int j ;
                for (j = 0 ; j < i ; j++) {

                    fscanf(file, "%s ", read) ;
                    insertNode(&outputs, read, numberOfBits) ;
                    if (ptr == NULL) {

                        ptr = outputs ;

                    }
                    ptr = ptr->next ;

                }


        } else if (strcmp(read, "NOT") == 0 ) {

                fscanf(file, "%s ", read) ;

                struct Node * ptr = findNode(inputs, read) ;

                if (ptr == NULL) {

                    ptr = findNode(tempvars, read) ;

                }

                fscanf(file, "%s ", read) ;

                struct Node * out = findNode(outputs, read) ;

                if (out == NULL) {

                    out = findNode(tempvars, read) ;

                    if (out == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        out = findNode(tempvars, read) ;

                    }

                }

                out->value = not(ptr, numberOfBits) ;

        } else if (strcmp(read, "AND") == 0 ) {

                fscanf(file, "%s ", read) ;

                struct Node * ptr1 = findNode(inputs, read) ;

                if (ptr1 == NULL) {

                    ptr1 = findNode(tempvars, read) ;

                    if (ptr1 == NULL) {

                        ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr1->value = createStatic(atoi(read), numberOfBits) ;

                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * ptr2 = findNode(inputs, read) ;

                if (ptr2 == NULL) {

                    ptr2 = findNode(tempvars, read) ;

                    if (ptr2 == NULL) {

                        ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr2->value = createStatic(atoi(read), numberOfBits) ;
                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * out = findNode(outputs, read) ;

                if (out == NULL) {

                    out = findNode(tempvars, read) ;

                    if (out == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        out = findNode(tempvars, read) ;

                    }

                }

                out->value = and(ptr1, ptr2, numberOfBits) ;

        } else if (strcmp(read, "OR") == 0) {

                fscanf(file, "%s ", read) ;

                struct Node * ptr1 = findNode(inputs, read) ;

                if (ptr1 == NULL) {

                    ptr1 = findNode(tempvars, read) ;

                    if (ptr1 == NULL) {

                        ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr1->value = createStatic(atoi(read), numberOfBits) ;

                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * ptr2 = findNode(inputs, read) ;

                if (ptr2 == NULL) {

                    ptr2 = findNode(tempvars, read) ;

                    if (ptr2 == NULL) {

                        ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr2->value = createStatic(atoi(read), numberOfBits) ;
                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * out = findNode(outputs, read) ;

                if (out == NULL) {

                    out = findNode(tempvars, read) ;

                    if (out == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        out = findNode(tempvars, read) ;

                    }

                }

                out->value = or(ptr1, ptr2, numberOfBits) ;


        } else if (strcmp(read, "NAND") == 0) {

                fscanf(file, "%s ", read) ;

                struct Node * ptr1 = findNode(inputs, read) ;

                if (ptr1 == NULL) {

                    ptr1 = findNode(tempvars, read) ;

                    if (ptr1 == NULL) {

                        ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr1->value = createStatic(atoi(read), numberOfBits) ;

                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * ptr2 = findNode(inputs, read) ;

                if (ptr2 == NULL) {

                    ptr2 = findNode(tempvars, read) ;

                    if (ptr2 == NULL) {

                        ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr2->value = createStatic(atoi(read), numberOfBits) ;
                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * out = findNode(outputs, read) ;

                if (out == NULL) {

                    out = findNode(tempvars, read) ;

                    if (out == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        out = findNode(tempvars, read) ;

                    }

                }

                out->value = and(ptr1, ptr2, numberOfBits) ;
                out->value = not(out, numberOfBits) ;


        } else if (strcmp(read, "NOR") == 0) {

                fscanf(file, "%s ", read) ;

                struct Node * ptr1 = findNode(inputs, read) ;

                if (ptr1 == NULL) {

                    ptr1 = findNode(tempvars, read) ;

                    if (ptr1 == NULL) {

                        ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr1->value = createStatic(atoi(read), numberOfBits) ;

                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * ptr2 = findNode(inputs, read) ;

                if (ptr2 == NULL) {

                    ptr2 = findNode(tempvars, read) ;

                    if (ptr2 == NULL) {

                        ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr2->value = createStatic(atoi(read), numberOfBits) ;
                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * out = findNode(outputs, read) ;

                if (out == NULL) {

                    out = findNode(tempvars, read) ;

                    if (out == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        out = findNode(tempvars, read) ;

                    }

                }

                out->value = or(ptr1, ptr2, numberOfBits) ;
                out->value = not(out, numberOfBits) ;

        } else if (strcmp(read, "XOR") == 0) {

                fscanf(file, "%s ", read) ;

                struct Node * ptr1 = findNode(inputs, read) ;

                if (ptr1 == NULL) {

                    ptr1 = findNode(tempvars, read) ;

                    if (ptr1 == NULL) {

                        ptr1 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr1->value = createStatic(atoi(read), numberOfBits) ;

                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * ptr2 = findNode(inputs, read) ;

                if (ptr2 == NULL) {

                    ptr2 = findNode(tempvars, read) ;

                    if (ptr2 == NULL) {

                        ptr2 = (struct Node *)malloc(sizeof(struct Node)) ;
                        ptr2->value = createStatic(atoi(read), numberOfBits) ;
                    }

                }

                fscanf(file, "%s ", read) ;

                struct Node * out = findNode(outputs, read) ;

                if (out == NULL) {

                    out = findNode(tempvars, read) ;

                    if (out == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        out = findNode(tempvars, read) ;

                    }

                }

                out->value = xor(ptr1, ptr2, numberOfBits) ; // (A and not B) or (not A and B)

        } else if (strcmp(read, "DECODER") == 0) {

            fscanf(file, "%s ", read) ;

            int noi = atoi(read) ;

            int noo = getPowerTwo(noi) ;

            fscanf(file, "%s ", read) ;

            struct Node * t = findNode(inputs, read) ;

                if (t == NULL) {

                    t = findNode(tempvars, read) ;

                }


            struct Node * decoderInputs = (struct Node *)malloc(sizeof(struct Node)) ;
            strcpy(decoderInputs->name, t->name) ;
            decoderInputs->next = NULL ;
            decoderInputs->value = t->value ;

            struct Node * ptr = decoderInputs ;

            int i ;
            for (i = 1 ; i < noi ; i++) {

                fscanf(file, "%s ", read) ;
                t= findNode(inputs, read) ;

                if (t == NULL) {

                    t = findNode(tempvars, read) ;

                }

                struct Node * temp = (struct Node *)malloc(sizeof(struct Node)) ;
                strcpy(temp->name, t->name) ;
                temp->value = t->value ;
                temp->next = NULL ;
                ptr->next = temp ;
                ptr = ptr->next ;

            }

            fscanf(file, "%s ", read) ;

            struct Node * buf = findNode(outputs, read) ;

                if (buf == NULL) {

                    buf = findNode(tempvars, read) ;

                    if (buf == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        buf = findNode(tempvars, read) ;

                    }

                }

            struct Node * decoderOutputs = (struct Node *)malloc(sizeof(struct Node)) ;
            decoderOutputs->next = NULL ;
            strcpy(decoderOutputs->name, buf->name) ;
            decoderOutputs->value = buf->value ;

            ptr = decoderOutputs ;

            for (i = 1 ; i < noo ; i++) {

                fscanf(file, "%s ", read) ;

                buf = findNode(outputs, read) ;

                if (buf == NULL) {

                    buf = findNode(tempvars, read) ;

                    if (buf == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        buf = findNode(tempvars, read) ;

                    }

                }

                struct Node * temp = (struct Node *)malloc(sizeof(struct Node)) ;
                temp->next = NULL ;
                strcpy(temp->name, buf->name) ;
                temp->value = buf->value ;
                ptr->next = temp ;
                ptr = ptr->next ;


            }

            int * inbits = (int *)malloc(noi * sizeof(int)) ;

            for (i = 0 ; i < numberOfBits ; i++) {

                int j = 0 ;
                ptr = decoderInputs ;
                for (j = 0 ; j < noi ; j++) {

                    inbits[j] = ptr->value[i] ;
                    ptr = ptr->next ;

                }

                int b = 0 ;

                for (j = 0 ; j < noi ; j++) {

                    b = b * 2 + inbits[j] ;
                }

                ptr = decoderOutputs ;

                for (j = 0 ; j < noo ; j++) {

                    int g = j ^ (j >> 1) ;

                    if (g == b) {

                        ptr->value[i] = 1 ;

                    } else {

                        ptr->value[i] = 0 ;

                    }

                    ptr = ptr->next ;

                }

            }

            ptr = decoderOutputs ;

            while (ptr != NULL) {

                struct Node * temp = findNode(tempvars, ptr->name) ;

                if (temp == NULL) {

                    temp = findNode(outputs, ptr->name) ;

                }

                temp->value = ptr->value ;

                ptr = ptr->next ;

            }


        } else if (strcmp(read, "MULTIPLEXER") == 0) {

            fscanf(file, "%s ", read) ;

            int in = atoi(read) ;

            int i ;

            char ** inps = (char **)malloc(in * sizeof(char *)) ;

            for (i = 0 ; i < in ; i++) {

                inps[i] = (char *)malloc(15 * sizeof(char)) ;
                fscanf(file, "%s ", read) ;
                strcpy(inps[i], read) ;

            }

            int sel = getLogBaseTwo(in) ;

            char ** selectors = (char **)malloc(sel * sizeof(char *)) ;

            for (i = 0 ; i < sel ; i++) {

                selectors[i] = (char *)malloc(15 * sizeof(char)) ;
                fscanf(file, "%s ", read) ;
                strcpy(selectors[i], read) ;

            }

            fscanf(file, "%s ", read) ;

            struct Node * out = findNode(outputs, read) ;

            if (out == NULL) {

                    out = findNode(tempvars, read) ;

                    if (out == NULL) {

                        insertNode(&tempvars, read, numberOfBits) ;

                        out = findNode(tempvars, read) ;

                    }

            }

            int * inbits = (int *)malloc(sel * sizeof(int)) ;

            for (i = 0 ; i < numberOfBits ; i++) {

                    int j = 0 ;

                    int b = 0 ;

                    for (j = 0 ; j < sel ; j++) {

                        char * s = selectors[j] ;

                        if (s[0] == '0' || s[0] == '1') {

                            inbits[j] = atoi(s) ;

                        } else {

                            struct Node * temp = findNode(inputs, selectors[j]) ;

                            if (temp == NULL) {

                                temp = findNode(tempvars, selectors[j]) ;

                            }

                            inbits[j] = temp->value[i] ;

                        }

                        b = b * 2 + inbits[j] ;
                    }

                    int g = 0 ;

                    for (j = 0 ; j < in ; j++) {

                        g = j ^ (j >> 1) ;

                        if (g == b) {

                            break ;

                        }

                    }

                    char * selected = (char *)malloc(15 * sizeof(char)) ;
                    strcpy(selected, inps[j]) ;

                    if (selected[0] >= '0' && selected[0] <= '9') {

                        out->value[i] = atoi(selected) ;

                    } else {

                        struct Node * temp = findNode(inputs, selected) ;

                        if (temp == NULL) {

                            temp = findNode(tempvars, selected) ;

                        }

                        out->value[i] = temp->value[i] ;


                    }

                }


        }

        }

    int a, b;
    struct Node * ptr = inputs ;

    for (a = 0 ; a < numberOfBits ; a++) {

        for (b = 0 ; b < numberOfInputs ; b++) {

            printf("%d ", ptr->value[a]) ;

            ptr = ptr->next ;

        }

        ptr = outputs ;

        while (ptr != NULL) {

            printf("%d ", ptr->value[a]) ;
            ptr = ptr->next ;

        }

        printf("\n") ;

        ptr = inputs ;

    }


    return 0;
}

