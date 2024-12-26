#include "rlcpong.h"

uint32_t entity_size(struct entity *head)
{
    if (!head) return 0;
    uint32_t count = 0;
    while(head) {
        ++count;
        head = head->next;
    }
    return count;
}

struct entity *entity_create(struct entity **head, enum entity_types tag, size_t id)
{
    if (!head) {
        struct entity *e = malloc(sizeof(struct entity));
        e->m_id = id;
        e->m_active = true;
        e->m_tag = ENTITY_TYPE_NOTHING;
        e->next = NULL;
        *head = e;
        return *head;
    }
    if (!head) return NULL;
    struct entity *e2 = malloc(sizeof(struct entity));
    e2->m_id = id;
    e2->m_active = true;
    e2->m_tag = tag;
    e2->next = *head;
    *head = e2;
    return *head;
}

struct entity *entity_search_by_tag(struct entity *head, enum entity_types tag)
{
    struct entity *new_list = NULL;
    struct entity *last = NULL;
    while(head) {
        if (head->m_tag == tag) {
            if (!new_list) {
                new_list = head;
            } else {
                last->next = head;
            }
            last = head;
        }
        head = head->next;
    }
    if (last) {
        last->next = NULL;
    }
    return new_list;
}

struct entity *entity_search_by_id(struct entity *head, size_t id)
{
    if (!head) return NULL;
    while(head) {
        if (head->m_id == id ) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void entity_remove_by_id(struct entity **head, size_t id)
{
    if (!head || !*head) return;
    struct entity *prev = NULL;
    struct entity *curr = *head;
    while(curr != NULL) {
        if(curr->m_id == id) {
             if(prev == NULL) {
                 *head = curr->next;
             } else {
                 prev->next = curr->next;
             }
             free(curr);
             return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void entity_remove_by_tag(struct entity **head, enum entity_types tag)
{
    struct entity *prev = NULL;
    struct entity *curr = *head;
    while(curr != NULL) {
        if(curr->m_tag == tag) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            struct entity *temp = curr;
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

struct entity *entity_append(struct entity **head1, struct entity *head2)
{
    if (!head1) return NULL;
    if (!*head1) {
        *head1 = head2;
        return *head1;
    }
    if (!head2) return NULL;
    struct entity *curr = *head1;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = head2;
    return *head1;
}

void entity_display(struct entity *head)
{
    if (!head) return;
    struct entity *ee = malloc(sizeof(struct entity));
    *ee = *head;
    while(ee) {
        printf("ID: %ld TAG: %d\n", ee->m_id, ee->m_tag);
        ee = ee->next;
    }
    entity_free(ee);
    free(ee);
}

void entity_free(struct entity *head) {
    while (head) {
        struct entity *temp = head;
        head = head->next;
        free(temp);
    }
}
