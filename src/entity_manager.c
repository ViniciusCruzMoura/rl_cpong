#include "rlcpong.h"

void update_entities(EntityManager *em)
{
    if (entity_size(em->m_toadd) > 0) {
        entity_append(&em->m_list, em->m_toadd);
        em->m_toadd = NULL;
    }
    if (entity_size(em->m_list) > 0) {
        Entity *temp = malloc(sizeof(Entity));
        *temp = *em->m_list;
        while(temp) {
            if (!temp->m_active) {
                printf("EntityID to REMOVE %li\n", temp->m_id);
                entity_remove_by_id(&em->m_list, temp->m_id);
            }
            temp = temp->next;
        }
        entity_free(temp);
    }
}

Entity *add_entity(EntityManager *em, EntityTypes tag)
{
    Entity *e = entity_create(&em->m_toadd, tag, ++em->m_total_entities);
    printf("Entity ID: %zu : Stored in map at: %p\n",
            e->m_id, (void*)e);
    return e;
}

Entity *get_entities(EntityManager *em, EntityTypes etype)
{
    return entity_search_by_tag(em->m_list, etype);
}
