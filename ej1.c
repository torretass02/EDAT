#include <string.h>

#define MAX_TITLE 128
#define MAX_AUTHOR 64
#define MAX_ISBN 32
#define MAX_BOOKS 1064


typedef enum {
    ERROR=0,
    OK=1     
} Status;


typedef enum {
    FALSE=0, /*!< False value */
    TRUE=1  /*!< True value  */
} Bool;

typedef struct _Book Book;
typedef struct _Library Library;

struct _Book{
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char ISBN[MAX_ISBN];
    int num_copies;
};

struct _Library{
    Book * books[MAX_BOOKS];
    int num_books;
};

Book * book_init(char * descr);
void book_free(Book * b);
char * book_getTitle(Book * b);
char * book_getAuthor(Book * b);
char * book_getIsbn(Book * b);
int book_getNumCopies(Book * b);
Status book_setTitle(Book * b, char * title);
Status book_setAuthor(Book * b, char * author);
Status book_setIsbn(Book * b, char * isbn);
Status book_setNumCopies(Book * b, int n);
Status book_print(Book * b);
int book_cmp(Book * b1, Book *b2);

Library * library_init();
void library_free(Library * l);
int library_getNumBooks(Library * l);
Status library_addBook(Library * l, char * isbn);
Status library_removeBook(Library * l, char * descr);
Bool library_hasBook(Library * l, char * isbn);
Status library_print(Library * l);
Bool library_isEmpty(Library * l);
int library_findBookByIsbn(Library * l, char * isbn);
Bool library_isFull(Library * l);


Book * book_init(char * descr){
    if(!descr) return NULL;
    Book * b = NULL;
    int num;

    b = (Book *)malloc(sizeof(Book));
    if(!b) return NULL;

    num = sscanf(descr, "%s %s %s %d", b->author, b->title, b->ISBN, b->num_copies);

    if(num != 4){
        free(b);
        return NULL;
    }

    return b;
}

int book_cmp(Book * b1, Book *b2){
    if(!b1 || !b2) return 0;
    return strcmp(b1->ISBN, b2->ISBN);
}

void book_free(Book * b){
    free(b);
}

Library * library_init(){
    Library * l = NULL;
    int i;

    l = (Library *)malloc(sizeof(Library));
    if(!l) return NULL;

    for(i=0; i<MAX_BOOKS; i++){
        l->books[i] = NULL;
    }

    l->num_books = 0;
    
    return l;
}

Bool library_isEmpty(Library * l){
    if(l == NULL || l->num_books == 0) return TRUE;
    else return FALSE;
}

Bool library_hasBook(Library * l, char * isbn){
    if(!l || !isbn) return FALSE;
    int i;

    for(i=0; i<l->num_books; i++){
        if(strcmp(book_getIsbn(l->books[i]), isbn) == 0) return TRUE;
    }

    return FALSE;
}

Status library_addBook(Library * l, char * descr){
    if(!l || !descr) return ERROR;

    Book * b;
    int n, f; 

    b = book_init(descr);
    if(!b) return ERROR;

    n = book_getNumCopies(b);

    if(library_hasBook(l, book_getIsbn(b))){
        f = library_findBookByIsbn(l, book_getIsbn(b));
        book_setNumCopies(l->books[f], n+book_getNumCopies(l->books[f]));
        book_free(b);
        return OK;
    }

    if(library_isFull(l) == TRUE){
        book_free(b);
        return ERROR;
    }

    l->books[l->num_books] = b;
    l->num_books++;
    
    return OK;
}

Status library_removeBook(Library * l, char * isbn){
    if(!l || !descr) return ERROR;

    Book * b;
    int f;

    f = library_findBookByIsbn(l, isbn);

    b = l->books[f];

    l->books[f] = l->books[l->num_books-1];
    l->books[l->num_books-1] = NULL;

    l->num_books--;

    book_free(b);

    return OK;
}