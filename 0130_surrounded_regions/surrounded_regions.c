#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define	list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define	list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

#define	list_for_each(p, head) \
	for (p = (head)->next; p != (head); p = p->next)

#define	list_for_each_safe(p, n, head) \
	for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

struct list_head {
    struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static inline int list_empty(const struct list_head *head)
{
    return (head->next == head);
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

static inline void list_add_tail(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head->prev, head);
}

static inline void __list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

struct node {
    struct list_head link;
    int x, y;
};

static struct node *node_new(struct list_head *free_list)
{
    struct node *new;
    if (list_empty(free_list)) {
        new = malloc(sizeof(*new));
    } else {
        new = list_first_entry(free_list, struct node, link);
        list_del(&new->link);
    }
    return new;
}

static void bfs(char **board, int row_size, int col_size,
                struct list_head *queue, struct list_head *free_list)
{
    while (!list_empty(queue)) {
        struct node *new;
        struct node *node = list_first_entry(queue, struct node, link);
        board[node->x][node->y] = 'P';

        if (node->x > 0 && board[node->x - 1][node->y] == 'O') {
            new = node_new(free_list);
            new->x = node->x - 1;
            new->y = node->y;
            board[new->x][new->y] = 'P';
            list_add_tail(&new->link, queue);
        }

        if (node->y < col_size - 1 && board[node->x][node->y + 1] == 'O') {
            new = node_new(free_list);
            new->x = node->x;
            new->y = node->y + 1;
            board[new->x][new->y] = 'P';
            list_add_tail(&new->link, queue);
        }

        if (node->x < row_size - 1 && board[node->x + 1][node->y] == 'O') {
            new = node_new(free_list);
            new->x = node->x + 1;
            new->y = node->y;
            board[new->x][new->y] = 'P';
            list_add_tail(&new->link, queue);
        }

        if (node->y > 0 && board[node->x][node->y - 1] == 'O') {
            new = node_new(free_list);
            new->x = node->x;
            new->y = node->y - 1;
            board[new->x][new->y] = 'P';
            list_add_tail(&new->link, queue);
        }

        list_del(&node->link);
        list_add(&node->link, free_list);
    } 
}

void solve(char** board, int boardRowSize, int boardColSize)
{
    int i, j;
    struct node *new;
    struct list_head queue, free_list;

    INIT_LIST_HEAD(&queue);
    INIT_LIST_HEAD(&free_list);

    for (i = 0; i < boardColSize; i++) {
        if (board[0][i] == 'O') {
            new = node_new(&free_list);
            new->x = 0;
            new->y = i;
            list_add_tail(&new->link, &queue);
            bfs(board, boardRowSize, boardColSize, &queue, &free_list);
        }
    }

    for (i = 0; i < boardColSize; i++) {
        if (board[boardRowSize - 1][i] == 'O') {
            new = node_new(&free_list);
            new->x = boardRowSize - 1;
            new->y = i;
            list_add_tail(&new->link, &queue);
            bfs(board, boardRowSize, boardColSize, &queue, &free_list);
        }
    }

    for (i = 0; i < boardRowSize; i++) {
        if (board[i][0] == 'O') {
            new = node_new(&free_list);
            new->x = i;
            new->y = 0;
            list_add_tail(&new->link, &queue);
            bfs(board, boardRowSize, boardColSize, &queue, &free_list);
        }
    }

    for (i = 0; i < boardRowSize; i++) {
        if (board[i][boardColSize - 1] == 'O') {
            new = node_new(&free_list);
            new->x = i;
            new->y = boardColSize - 1;
            list_add_tail(&new->link, &queue);
            bfs(board, boardRowSize, boardColSize, &queue, &free_list);
        }
    }

    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            board[i][j] = board[i][j] == 'P' ? 'O' : 'X';
        }
    }
}

int main(void)
{
    int i, j;
    int row_size = 5;
    int col_size = 5;
    char **board = malloc(row_size * sizeof(char *));
    board[0] = malloc(col_size);
    board[0][0] = 'X';
    board[0][1] = 'X';
    board[0][2] = 'X';
    board[0][3] = 'X';
    board[0][4] = 'X';
    board[1] = malloc(col_size);
    board[1][0] = 'O';
    board[1][1] = 'X';
    board[1][2] = 'O';
    board[1][3] = 'O';
    board[1][4] = 'X';
    board[2] = malloc(col_size);
    board[2][0] = 'O';
    board[2][1] = 'O';
    board[2][2] = 'X';
    board[2][3] = 'O';
    board[2][4] = 'X';
    board[3] = malloc(col_size);
    board[3][0] = 'X';
    board[3][1] = 'X';
    board[3][2] = 'O';
    board[3][3] = 'X';
    board[3][4] = 'X';
    board[4] = malloc(col_size);
    board[4][0] = 'X';
    board[4][1] = 'X';
    board[4][2] = 'O';
    board[4][3] = 'O';
    board[4][4] = 'X';

    for (i = 0; i < row_size; i++) {
        for (j = 0; j < col_size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    solve(board, row_size, col_size);
    for (i = 0; i < row_size; i++) {
        for (j = 0; j < col_size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
