#ifndef ENTITY_H
#define ENTITY_H

typedef struct Entity {
    bool m_active;
    size_t m_id;
    char *m_tag;

    //flags
    CFlags flags;

    //componets
    CInput input;
    CTransform transform;
    CCollision collision;
    CShape shape;
    CScore score;
    CLifespan lifespan;

} Entity;

#endif //ENTITY_H
