#include "rlcpong.h"

uint32_t entity_size(Entity *head)
{
    if (!head) return 0;
    uint32_t count = 0;
    while(head) {
        ++count;
        head = head->next;
    }
    return count;
}

Entity *entity_create(Entity **head, EntityTypes tag, size_t id)
{
    if (!head) {
        Entity *e = malloc(sizeof(Entity));
        e->m_id = id;
        e->m_active = true;
        e->m_tag = ENTITY_TYPE_NOTHING;
        e->next = NULL;
        *head = e;
        return *head;
    }
    if (!head) return NULL;
    Entity *e2 = malloc(sizeof(Entity));
    e2->m_id = id;
    e2->m_active = true;
    e2->m_tag = tag;
    e2->next = *head;
    *head = e2;
    return *head;
}

Entity *entity_search_by_tag(Entity *head, EntityTypes tag)
{
    Entity *new_list = NULL;
    Entity *last = NULL;
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

Entity *entity_search_by_id(Entity *head, size_t id)
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

void entity_remove_by_id(Entity **head, size_t id)
{
    if (!head || !*head) return;
    Entity *prev = NULL;
    Entity *curr = *head;
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

void entity_remove_by_tag(Entity **head, EntityTypes tag)
{
    Entity *prev = NULL;
    Entity *curr = *head;
    while(curr != NULL) {
        if(curr->m_tag == tag) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            Entity *temp = curr;
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

Entity *entity_append(Entity **head1, Entity *head2)
{
    if (!head1) return NULL;
    if (!*head1) {
        *head1 = head2;
        return *head1;
    }
    if (!head2) return NULL;
    Entity *curr = *head1;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = head2;
    return *head1;
}

void entity_display(Entity *head)
{
    if (!head) return;
    Entity *ee = malloc(sizeof(Entity));
    *ee = *head;
    while(ee) {
        printf("ID: %ld TAG: %d\n", ee->m_id, ee->m_tag);
        ee = ee->next;
    }
    entity_free(ee);
    free(ee);
}

void entity_free(Entity *head) {
    while (head) {
        Entity *temp = head;
        head = head->next;
        free(temp);
    }
}
