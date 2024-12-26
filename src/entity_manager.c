#include "rlcpong.h"

void update_entities(struct entity_manager *em)
{
    if (entity_size(em->m_toadd) > 0) {
        entity_append(&em->m_list, em->m_toadd);
        em->m_toadd = NULL;
    }
    if (entity_size(em->m_list) > 0) {
        struct entity *temp = malloc(sizeof(struct entity));
        *temp = *em->m_list;
        while(temp) {
            if (!temp->m_active) {
                DEBUG_PRINT("entityID to REMOVE %li\n", temp->m_id);
                entity_remove_by_id(&em->m_list, temp->m_id);
            }
            temp = temp->next;
        }
        entity_free(temp);
    }
}

struct entity *add_entity(struct entity_manager *em, enum entity_types tag)
{
    struct entity *e = entity_create(&em->m_toadd, tag, ++em->m_total_entities);
    DEBUG_PRINT("entity ID: %zu : Stored in map at: %p\n",
            e->m_id, (void*)e);
    return e;
}

struct entity *get_entities(struct entity_manager *em, enum entity_types etype)
{
    return entity_search_by_tag(em->m_list, etype);
}
