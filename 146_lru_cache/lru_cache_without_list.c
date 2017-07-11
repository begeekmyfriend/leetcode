#include <stdio.h>
#include <stdlib.h>

static int lru_id;

struct entry {
        int id;
        int key;
        int value;
};

struct key_record {
        int key;
        struct entry *entry;
};

struct id_record {
        int id;
        struct entry *entry;
};

struct lru_cache {
        void *entries;
        void *id_recs;
        void *key_recs;
        int capacity;
        int count;
};

static struct lru_cache cache;

static struct key_record *key_binary_search(int key)
{
        int low = -1;
        int high = cache.count;
        struct key_record *kr;

        while (low + 1 < high) {
                int mid = low + (high - low) / 2;
                kr = cache.key_recs + mid * sizeof(*kr);
                if (kr->key < key) {
                        low = mid;
                } else {
                        high = mid;
                }
        }

        kr = cache.key_recs + high * sizeof(*kr);
        if (high >= cache.count || kr->key != key) {
                return NULL;
        } else {
                return kr;
        }
}

static struct id_record *id_binary_search(int id)
{
        int low = -1;
        int high = cache.count;
        struct id_record *ir;

        while (low + 1 < high) {
                int mid = low + (high - low) / 2;
                ir = cache.id_recs + mid * sizeof(*ir);
                if (ir->id < id) {
                        low = mid;
                } else {
                        high = mid;
                }
        }

        ir = cache.id_recs + high * sizeof(*ir);
        if (high >= cache.count || ir->id != id) {
                return NULL;
        } else {
                return ir;
        }
}

static int key_compare(const void *p1, const void *p2)
{
        const struct key_record *kr1 = p1;
        const struct key_record *kr2 = p2;
        int k1 = kr1->key;
        int k2 = kr2->key;

        if (k1 < k2) {
                return -1;
        } else if (k1 > k2) {
                return 1;
        } else {
                return 0;
        }
}

static int id_compare(const void *p1, const void *p2)
{
        const struct id_record *r1 = p1;
        const struct id_record *r2 = p2;
        int i1 = r1->id;
        int i2 = r2->id;

        if (i1 < i2) {
                return -1;
        } else if (i1 > i2) {
                return 1;
        } else {
                return 0;
        }
}

void lru_cache_init(int capacity)
{
        int i;
        struct entry *e;
        struct id_record *ir;
        struct key_record *kr;

        cache.count = 0;
        cache.capacity = capacity;
        cache.entries = malloc(capacity * sizeof(struct entry));
        cache.id_recs = malloc(capacity * sizeof(struct id_record));
        cache.key_recs = malloc(capacity * sizeof(struct key_record));

        e = cache.entries;
        ir = cache.id_recs;
        kr = cache.key_recs;
        for (i = 0; i < capacity; i++, e++, ir++, kr++) {
                e->id = e->key = e->value = -1;
                kr->entry = ir->entry = e;
                ir->id = -1;
                kr->key = -1;
        }
}

void lru_cache_free(void)
{
        free(cache.entries);
        free(cache.id_recs);
        free(cache.key_recs);
        cache.count = 0;
        cache.capacity = 0;
}

int lru_cache_get(int key)
{
        struct key_record *kr = key_binary_search(key);
        if (kr != NULL) {
                struct entry *e = kr->entry;
                struct id_record *ir = id_binary_search(e->id);
                ir->id = ++lru_id;
                e->id = ir->id;
                qsort(cache.id_recs, cache.count, sizeof(*ir), id_compare);
                return e->value;
        } else {
                return -1;
        }
}

void lru_cache_set(int key, int value)
{
        struct entry *e;
        struct key_record *kr;
        struct id_record *ir;

        kr = key_binary_search(key);
        if (kr != NULL) {
                e = kr->entry;
                ir = id_binary_search(e->id);
        } else {
                if (cache.count == cache.capacity) {
                        ir = cache.id_recs;
                        e = ir->entry;
                        kr = key_binary_search(e->key);
                } else {
                        ir = cache.id_recs + cache.count * sizeof(*ir);
                        kr = cache.key_recs + cache.count * sizeof(*kr);
                        cache.count++;
                        e = ir->entry;
                }
                kr->key = key;
                qsort(cache.key_recs, cache.count, sizeof(*kr), key_compare);
        }

        ir->id = ++lru_id;
        e->id = ir->id;
        qsort(cache.id_recs, cache.count, sizeof(*ir), id_compare);

        e->key = key;
        e->value = value;
}

void lru_cache_dump(void)
{
        int i;
        struct entry *e;
        struct id_record *ir;
        struct key_record *kr;

        printf(">>> dump:\n");
        e = cache.entries;
        for (i = 0; i < cache.capacity; i++, e++) {
                printf("E:%p[%d %d %d]\n", e, e->key, e->value, e->id);
        }

        ir = cache.id_recs;
        for (i = 0; i < cache.capacity; i++, ir++) {
                printf("ID:[%d %p]\n", ir->id, ir->entry);
        }

        kr = cache.key_recs;
        for (i = 0; i < cache.capacity; i++, kr++) {
                printf("KEY:[%d %p]\n", kr->key, kr->entry);
        }
}

int main(void)
{
#if 1
        lru_cache_init(2);
        lru_cache_dump();
        printf("get 2, %d\n", lru_cache_get(2));
        printf("set 2, 6\n");
        lru_cache_set(2, 6);
        lru_cache_dump();
        printf("get 1, %d\n", lru_cache_get(1));
        printf("set 1, 5\n");
        lru_cache_set(1, 5);
        lru_cache_dump();
        printf("set 1, 2\n");
        lru_cache_set(1, 2);
        lru_cache_dump();
        printf("get 1, %d\n", lru_cache_get(1));
        printf("get 2, %d\n", lru_cache_get(2));
        lru_cache_free();
#else
        lru_cache_init(2);
        printf("set 2, 1\n");
        lru_cache_set(2, 1);
        printf("set 1, 1\n");
        lru_cache_set(1, 1);
        lru_cache_dump();
        printf("get 2, %d\n", lru_cache_get(2));
        lru_cache_dump();
        printf("set 4, 1\n");
        lru_cache_set(4, 1);
        lru_cache_dump();
        printf("get 1, %d\n", lru_cache_get(1));
        printf("get 2, %d\n", lru_cache_get(2));
        lru_cache_free();
#endif

        return 0;
}
